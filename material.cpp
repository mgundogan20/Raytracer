#include <SFML/Graphics/Color.hpp>

class Material{
	private:
		sf::Color materialColor;
		sf::Color emissionColor;
		float solidAngleOfReflection;
		float emissionStrength;
	public:
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
		
		void setMaterialColor(const sf::Color& color) {
			materialColor = color;
		}

		sf::Color getMaterialColor() const {
			return materialColor;
		}

		void setEmissionColor(const sf::Color& color) {
			emissionColor = color;
		}

		sf::Color getEmissionColor() const {
			return emissionColor;
		}

		void setSolidAngleOfReflection(const float& angle) {
			solidAngleOfReflection = angle;
		}

		float getSolidAngleOfReflection() const {
			return solidAngleOfReflection;
		}

		void setEmissionStrength(const float& strength) {
			emissionStrength = strength;
		}

		float getEmissionStrength() const {
			return emissionStrength;
		}

};