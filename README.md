#**Raytracer**

This is a personal project that renders photo-realistic 3D scenes using optics.

##Initial commit: Detecting Spheres, Specular Reflections, Simple Materials

The initial version of the program traces photon paths with purely specular reflections, ignoring the randomness that should come with diffusive properties of a material. As a result, the images it generates are crisp yet dim, with areas that aren't directly lit by the "sun" receiving almost no light.

At present, the renderer can only detect spheres. However, it fulfills the minimum requirements to be called a raytracer. It can calculate collisions and reflections, and it has materials of different colors and light-emitting properties. With the sky added after the initial commit, it can produce the following fairly simple scene:

<img src="https://user-images.githubusercontent.com/72755125/235942869-4a4f25c0-0620-42f6-ab28-0c91e35a406b.png" width="600" height="400">
