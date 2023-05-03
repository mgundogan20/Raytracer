#include <SFML/Graphics.hpp>
#include "tracer.cpp"
#include <iostream>
#define RAYS_PER_PIXEL = 5
// Forward declaration of the update function
void update(int width, int height, int depthOfField, sf::RectangleShape& box, Tracer& tracer, sf::RenderWindow& window);

int main()
{
    // Set up the window
    const int width = 900;
    const int height = 600;
    const int depthOfField = 300;
    sf::RenderWindow window(sf::VideoMode(width, height), "Mevlut's RTX");

    // Set up the rectangle
    sf::RectangleShape box(sf::Vector2f(1, 1));
    box.setOutlineColor(sf::Color::Transparent);

    // Set up the tracer and materials
    Tracer tracer;
    Material greyMaterial(sf::Color(200,200,40), sf::Color::White, 0);
    Material sunMaterial(sf::Color::Black, sf::Color::White, 1);
    Material greenMaterial(sf::Color(30,200,30), sf::Color::White, 0);
    Material blueMaterial(sf::Color(30,30,200), sf::Color::White, 0);

    // Set up the spheres and add them to the tracer
    Sphere MySphere(sf::Vector3f(-80, 0, 300), 45, greyMaterial, "white");
    Sphere sun(sf::Vector3f(-200, -200, 200), 150, sunMaterial, "sun");
    Sphere MySphere3(sf::Vector3f(80, 0, 300), 90, greenMaterial, "green");
    Sphere MySphere4(sf::Vector3f(0, 1000, 300), 950, blueMaterial, "ground");
    tracer.getObjects().push_back(MySphere);
    tracer.getObjects().push_back(sun);
    tracer.getObjects().push_back(MySphere3);
    tracer.getObjects().push_back(MySphere4);

    // Call the update function to render the frame
    update(width, height, depthOfField, box, tracer, window);
    std::cout << "done\n";
    window.display();

    sf::Vector2u windowSize = window.getSize();
    sf::Texture texture;
    texture.create(windowSize.x, windowSize.y);
    texture.update(window);
    sf::Image screenshot = texture.copyToImage();
    
    if (screenshot.saveToFile("./output.png"))
    {
        std::cout << "screenshot saved to " << "output.png" << std::endl;
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
            // Calculate the direction of the ray
            ray.x = i - width / 2;
            ray.y = j - height / 2;
            ray.z = depthOfField;
            float rayMag = sqrt(pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2));
            ray.x /= rayMag;
            ray.y /= rayMag;
            ray.z /= rayMag;

            // Trace the ray and set the color of the pixel
            sf::Color color;
            sf::Color rayOutput;
            for(int k=0; k<200 ;k++){
                rayOutput = tracer.trace(ray);
                color += sf::Color(rayOutput.r/20, rayOutput.g/20, rayOutput.b/20);
            }
            // std::cout << "tracing " << i << "," << j << std::endl;
            box.setPosition(sf::Vector2f(i, j));
            box.setFillColor(color);
            window.draw(box);
        }
    }
}
