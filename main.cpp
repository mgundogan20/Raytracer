#include <SFML/Graphics.hpp>
#include "tracer.cpp"
#include <iostream>

// Forward declaration of the update function
void update(int width, int height, sf::RectangleShape& box, Tracer& tracer, sf::RenderWindow& window);

int main()
{
    // Set up the window
    int width = 400;
    int height = 300;
    sf::RenderWindow window(sf::VideoMode(width, height), "Mevlut's RTX");

    // Set up the rectangle
    sf::RectangleShape box(sf::Vector2f(1, 1));
    box.setOutlineColor(sf::Color::Transparent);

    // Set up the tracer and materials
    Tracer tracer;
    Material greyMaterial(sf::Color(200,200,40), sf::Color::White, 0.2);
    Material sunMaterial(sf::Color::Black, sf::Color::White, 1);
    Material blueMaterial(sf::Color(30,200,30), sf::Color::White, 0.2);

    // Set up the spheres and add them to the tracer
    Sphere MySphere(sf::Vector3f(-100, 0, 300), 45, greyMaterial, "white");
    Sphere sun(sf::Vector3f(-200, -200, 200), 150, sunMaterial, "sun");
    Sphere MySphere3(sf::Vector3f(100, 0, 300), 90, blueMaterial, "blue");
    tracer.getObjects().push_back(MySphere);
    tracer.getObjects().push_back(sun);
    tracer.getObjects().push_back(MySphere3);

    // Call the update function to render the frame
    update(width, height, box, tracer, window);

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
void update(int width, int height, sf::RectangleShape& box, Tracer& tracer, sf::RenderWindow& window)
{
    // Set up a ray
    sf::Vector3f ray;

    // Loop through every pixel in the window
    for (int i = 0; i < width; i += 1)
    {
        for (int j = 0; j < height; j += 1)
        {
            // Calculate the direction of the ray
            ray.x = i - width / 2;
            ray.y = j - height / 2;
            ray.z = width;
            float rayMag = sqrt(pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2));
            ray.x /= rayMag;
            ray.y /= rayMag;
            ray.z /= rayMag;

            // Trace the ray and set the color of the pixel
            sf::Color color = tracer.trace(ray);
            // std::cout << "tracing " << i << "," << j << std::endl;
            box.setPosition(sf::Vector2f(i, j));
            box.setFillColor(color);
            window.draw(box);
        }
    }
}
