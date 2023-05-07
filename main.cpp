#include <SFML/Graphics.hpp>
#include "tracer.cpp"
#include <iostream>
#define RAYS_PER_PIXEL 5
// Forward declaration of the update function
void update(int width, int height, int depthOfField, sf::RectangleShape& box, Tracer& tracer, sf::RenderWindow& window);
sf::Vector3f colorAdd(const sf::Vector3f color1, const sf::Vector3f color2);

int main()
{
    // Set up the window
    const int width = 900;
    const int height = 600;
    const int depthOfField = 500;
    sf::RenderWindow window(sf::VideoMode(width, height), "Mevlut's RTX");

    // Set up the rectangle
    sf::RectangleShape box(sf::Vector2f(1, 1));
    box.setOutlineColor(sf::Color::Transparent);

    // Set up the tracer and materials
    Tracer tracer;
    Material sunMaterial(sf::Vector3f(255,160,40), sf::Vector3f(255,255,255), 0, 0.9);
    Material yellowMaterial(sf::Vector3f(200,200,40), sf::Vector3f(255,255,255), 0, 1);
    Material greenMaterial(sf::Vector3f(30,200,30), sf::Vector3f(255,255,255), 0, 0.9);
    Material blueMaterial(sf::Vector3f(30,30,200), sf::Vector3f(255,255,255), 0, 0);
    Material greyMaterial(sf::Vector3f(200,200,200), sf::Vector3f(255,255,255), 0, 0);
    Material lampMaterial(sf::Vector3f(0,0,0), sf::Vector3f(255,255,255), 5, 0);

    // Set up the spheres and add them to the tracer
    Sphere sun(sf::Vector3f(-200, -200, 200), 150, sunMaterial, "sun");
    Sphere MySphere(sf::Vector3f(-80, 0, 300), 80, yellowMaterial, "yellow");
    Sphere MySphere3(sf::Vector3f(80, 0, 300), 80, greenMaterial, "green");
    Sphere MySphere4(sf::Vector3f(0, 1000, 300), 950, blueMaterial, "ground");
    Sphere background(sf::Vector3f(0, 0, 20000), 19500, greyMaterial, "background");
    Sphere lamp(sf::Vector3f(0, 40, 250), 10, lampMaterial, "lamp");
    tracer.getObjects().push_back(MySphere);
    tracer.getObjects().push_back(sun);
    tracer.getObjects().push_back(MySphere3);
    tracer.getObjects().push_back(MySphere4);
    tracer.getObjects().push_back(background);
    tracer.getObjects().push_back(lamp);

    // Call the update function to render the frame
    update(width, height, depthOfField, box, tracer, window);
    std::cout << "done\n";
    window.display();

    // Create and save an image when the rendering is done
    sf::Vector2u windowSize = window.getSize();
    sf::Texture texture;
    texture.create(windowSize.x, windowSize.y);
    texture.update(window);
    sf::Image screenshot = texture.copyToImage();
    if (screenshot.saveToFile("./output.png"))
    {
        std::cout << "screenshot saved\n";
    }

    // Event loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Handle window events
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Display the window
        window.display();
    
    }

    return 0;
}

// Update function to render the scene
void update(int width, int height, int depthOfField, sf::RectangleShape& box, Tracer& tracer, sf::RenderWindow& window)
{
    // Set up a ray
    sf::Vector3f ray;

    // Loop through every pixel in the window
    for (int i = 0; i < width; i += 1)
    {
        for (int j = 0; j < height; j += 1)
        {
            // Trace some rays and set the color of the pixel
            sf::Vector3f color;
            sf::Vector3f rayOutput;
            for(int k=0; k<RAYS_PER_PIXEL ;k++){
                // Calculate the direction of the ray
                ray.x = i - width/2 + ((rand()%1000)/500.f - 1);
                ray.y = j - height/2 + ((rand()%1000)/500.f - 1);
                ray.z = depthOfField;
                float rayMag = sqrt(pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2));
                ray.x /= rayMag;
                ray.y /= rayMag;
                ray.z /= rayMag;

                rayOutput = tracer.trace(ray);
                color = colorAdd(color, sf::Vector3f(rayOutput.x/RAYS_PER_PIXEL, rayOutput.y/RAYS_PER_PIXEL, rayOutput.z/RAYS_PER_PIXEL));
            }
            color = colorAdd(color,color);
            box.setPosition(sf::Vector2f(i, j));
            box.setFillColor(sf::Color(color.x, color.y, color.z));
            window.draw(box);
        }
    }
}


sf::Vector3f colorAdd(const sf::Vector3f color1, const sf::Vector3f color2) {
    return sf::Vector3f(std::min(color1.x+color2.x,255.f),std::min(color1.y+color2.y,255.f),std::min(color1.z+color2.z,255.f));
}
