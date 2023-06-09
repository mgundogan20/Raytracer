#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "sphere.cpp"

// A struct to store information about a ray hit
struct HitInfo{
    bool didHit = false;                    // whether the ray hit an object
    sf::Vector3f hitLocation = sf::Vector3f(0,0,0);    // the location of the hit in 3D space
    float hitDistance = INFINITY;            // the distance from the ray origin to the hit
    sf::Vector3f hitNormal;                 // the surface normal at the hit location
    Material hitMaterial;                   // the material of the object that was hit
};

class Tracer {
public:
    // A vector of Sphere objects that can be hit by rays
    std::vector<Sphere> objects = {};

    // Trace a ray through the scene and return the accumulated color
    const sf::Vector3f trace(const sf::Vector3f& ray) const {
        sf::Vector3f rayColor = sf::Vector3f(255,255,255);
        sf::Vector3f accumulatedColor = sf::Vector3f(0,0,0);

        // Maximum number of times a ray can bounce off objects
        const int MAX_BOUNCE = 10;
        sf::Vector3f rayOrigin = sf::Vector3f(0,0,0);
        sf::Vector3f rayDir = ray;

        int bounceCount = 0;
        HitInfo closestHit;
        closestHit.hitDistance = 0;

        // Keep bouncing the ray until it reaches the maximum number of bounces
        // or it doesn't hit anything
        while(bounceCount < MAX_BOUNCE && closestHit.hitDistance < INFINITY){
            closestHit.hitDistance = INFINITY;
            closestHit.didHit = false;

            // Check for intersections between the ray and all objects in the scene
            for(Sphere current : objects){
                HitInfo currentHit = calculateHitInfo(current, rayOrigin, rayDir);
                if(currentHit.didHit && currentHit.hitDistance < closestHit.hitDistance && currentHit.hitDistance > 0){
                    closestHit = currentHit;
                }
            }

            // If the ray hit an object, calculate the color of the hit point
            if(closestHit.didHit){
                Material hitMat = closestHit.hitMaterial;
                accumulatedColor = colorAdd(accumulatedColor, colorMult(hitMat.getEmissionStrength()*hitMat.getEmissionColor(), rayColor));
                rayColor = colorMult(rayColor, hitMat.getMaterialColor());
            
            }
            else{ 
                accumulatedColor = colorAdd(accumulatedColor, colorMult(sf::Vector3f(4*(dotProduct(3.f*rayDir,sf::Vector3f(-1,-1,1))+9),4*(dotProduct(3.f*rayDir,sf::Vector3f(-1,-1,1))+9),7*(dotProduct(3.f*rayDir,sf::Vector3f(-1,-1,1))+9)), rayColor));
                
                break;
            }

            // Update the ray origin and direction for the next bounce
            rayOrigin = closestHit.hitLocation;

            // Specular reflection
            rayDir -= (2 * dotProduct(closestHit.hitNormal, rayDir)) * closestHit.hitNormal;
            rayDir = (float)(closestHit.hitMaterial.getReflectionFrac()/sqrt(dotProduct(rayDir, rayDir))) * rayDir;
            
            // Diffuse reflection
            rayDir +=  (1-closestHit.hitMaterial.getReflectionFrac()) * diffusiveRayCalc(closestHit.hitNormal, closestHit.hitMaterial);
            bounceCount++;
        }

        return accumulatedColor;
    }

    // Return a reference to the vector of objects in the scene
    // TODO: Handle this without sending a reference to the actual vector
    std::vector<Sphere>& getObjects() {
        return objects;
    }

private:
    // 
    sf::Vector3f colorMult(const sf::Vector3f color1, const sf::Vector3f color2) const {
        return sf::Vector3f(color1.x*color2.x/255, color1.y*color2.y/255, color1.z*color2.z/255);
    }

    sf::Vector3f colorAdd(const sf::Vector3f color1, const sf::Vector3f color2) const {
        return sf::Vector3f(std::min(color1.x+color2.x,255.f),std::min(color1.y+color2.y,255.f),std::min(color1.z+color2.z,255.f));
    }

    // Calculate the dot product of two vectors
    float dotProduct(const sf::Vector3f& first, const sf::Vector3f& second) const {
        return (first.x * second.x) + (first.y * second.y) + (first.z * second.z);
    }

    // Calculate information about a ray-object intersection
    HitInfo calculateHitInfo(const Sphere& sphere, const sf::Vector3f& rayOrigin, const sf::Vector3f& rayDirection) const {
        HitInfo hit;

        // Calculate coefficients of the quadratic equation for the ray-sphere intersection
        float a = dotProduct(rayDirection, rayDirection);
        sf::Vector3f centerToOrigin = rayOrigin - sphere.getPosition();
        float b = 2 * dotProduct(rayDirection, centerToOrigin);
        float c = dotProduct(centerToOrigin, centerToOrigin) - std::pow(sphere.getRadius(), 2);

        // Calculate the determinant of the quadratic equation
        float determinant = std::pow(b, 2) - (4 * a * c);

        if (determinant >= 0) {
            // Calculate the distance from the ray origin to the hit location
            float distance = -(b + sqrt(determinant)) / (2 * a);
            if(distance < 0){
                distance += sqrt(determinant) / a;
            }

            // Check if the hit is in front of the ray origin
            if (distance > 0.1) {
                hit.didHit = true;
                hit.hitLocation = rayOrigin + (distance * rayDirection);
                hit.hitDistance = distance;
                hit.hitMaterial = sphere.getSphereMat();
                hit.hitNormal = (hit.hitLocation - sphere.getPosition()) / sphere.getRadius();
            }
        } else {
            hit.didHit = false;
        }

        return hit;
    }

    sf::Vector3f diffusiveRayCalc(const sf::Vector3f normal, const Material mat) const {
        // Generate two random numbers between 0-1
        double phi = 3.14 * (rand() % 100000) / 100000;
        double theta = 3.14 * (rand() % 100000) / 50000;

        // Generate a random direction vector using the two random numbers
        sf::Vector3f randDir = sf::Vector3f(
            sin(phi) * cos(theta),
            sin(phi) * sin(theta),
            cos(phi)
        );

        // If the dot product between the random direction and the normal is negative,
        // invert the random direction vector to make sure ray reflects AWAY from object
        if (dotProduct(randDir, normal) < 0) {
            randDir = (-1.f) * randDir;
        }

        return randDir;
    }

};