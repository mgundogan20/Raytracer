#include <SFML/Graphics/Color.hpp>

class Material{
	public:
		sf::Color materialColor;
		sf::Color emissionColor;
		float emissionStrength;
		Material(sf::Color matColor, sf::Color lightColor, float intensity){
			materialColor = matColor;
			emissionColor = lightColor;
			emissionStrength = intensity;
		}
		Material(sf::Color matColor){
			matColor = matColor;
			emissionColor = sf::Color::Black;
			emissionStrength = 0;
		}
		Material(){
			
		}
};