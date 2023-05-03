# **Raytracer**
This is a personal project that renders photo-realistic 3D scenes using optics.

## Initial commit: Detecting Spheres, Specular Reflections, Simple Materials
The initial version of the program traces photon paths with purely specular reflections, ignoring the randomness that should come with diffusive properties of a material. As a result, the images it generates are crisp yet dim, with areas that aren't directly lit by the "sun" receiving almost no light.

At present, the renderer can only detect spheres. However, it fulfills the minimum requirements to be called a raytracer. It can calculate collisions and reflections, and it has materials of different colors and light-emitting properties. With the sky added after the initial commit, it can produce the following fairly simple scene:

<img src="https://user-images.githubusercontent.com/72755125/235942869-4a4f25c0-0620-42f6-ab28-0c91e35a406b.png" width="600" height="400">

## Diffuse reflections
In this updated version of the raytracer, we have implemented diffuse reflections. This means that rays from objects are now scattered in random directions, simulating the effect of rough surfaces. As a result, scenes look more realistically lit, as light can now bounce off objects and illuminate areas that are not directly in the line of sight from the source.

However, this randomness also introduces noise into the image. To overcome this, we have implemented a technique called multi-sampling, where we shoot multiple rays per pixel and average over their results. This produces a smoother and cleaner final image.

At this point, the raytracer can still only detect spheres, but it can now simulate both specular and diffuse reflections. With these capabilities, it can generate images that are a significant improvement over the initial version.

Single photon:

<img src ="https://user-images.githubusercontent.com/72755125/235988216-dc44428c-1791-4fbd-a155-5ddb23f35492.png" width="600" height="400">
100 photons:

<img src ="https://user-images.githubusercontent.com/72755125/235988237-7d0a15ba-03a7-41ca-b94e-578e84e24c53.png" width="600" height="400">
200 photons:

<img src ="https://user-images.githubusercontent.com/72755125/235988251-7f2f6fc6-5231-4f06-8e3e-e13432428bab.png" width="600" height="400">
