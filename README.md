# **Mevlut's Raytracer**
This is a personal project that aims to render photo-realistic 3D scenes using optics.

<img src="https://user-images.githubusercontent.com/72755125/236655425-e1d31eb9-d25d-49fb-8bba-a18de69ecf40.png" width="400" height="225"><img src="https://user-images.githubusercontent.com/72755125/236655508-17a7ff00-d34a-415f-83f7-5160caab111d.png" width="337" height="225">

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

## Multisampling and better reflections
### Noise reduction by multisampling
The raytracer now samples many randomly offset rays for each pixel. This results in smoother edges and less noise.

<img src="https://user-images.githubusercontent.com/72755125/236655208-9b552787-58da-4c49-9a41-e3da0b55b9c3.png" width="400">
<img src="https://user-images.githubusercontent.com/72755125/236655206-6cefc772-3c86-4529-830b-3381d4093b02.png" width="400">

### Combining reflection types
Unlike previous versions, now the material type determines the behaviour of light bouncing off of it. Depending on the material's properties, an incoming ray might bounce away in varying degrees of diffuse or specular reflection types.

<img src="https://user-images.githubusercontent.com/72755125/236655425-e1d31eb9-d25d-49fb-8bba-a18de69ecf40.png" width="800" height="450">
<img src="https://user-images.githubusercontent.com/72755125/236655508-17a7ff00-d34a-415f-83f7-5160caab111d.png" width="800" height="533">

