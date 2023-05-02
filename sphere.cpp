#include <SFML/System/Vector3.hpp>
#include "material.cpp"
#include <string.h>

class Sphere{
	private:
		sf::Vector3f position;
		float radius;
		Material sphereMat;
		std::string name;

	public:

		Sphere(sf::Vector3f pos, float rad, Material mat, std::string objName){
			position = pos;
			radius = rad;
			sphereMat = mat;
			name = objName;
		}

		void setPosition(sf::Vector3f pos) {
        	position = pos;
		}

		sf::Vector3f getPosition() const {
			return position;
		}

		void setRadius(float rad) {
			radius = rad;
		}

		float getRadius() const {
			return radius;
		}

		void setSphereMat(Material mat) {
			sphereMat = mat;
		}

		Material getSphereMat() const {
			return sphereMat;
		}
};