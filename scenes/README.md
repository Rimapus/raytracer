# Scenes

Each scene is a libconfig file with a camera, antialiasing settings, primitives
and lights. Render one with:

```sh
./raytracer scenes/showcase.cfg
```

The preview window opens while the image is rendered. Close it to write
`output.ppm` in the current directory. Convert the PPM with any image tool if
needed.

| Scene | Contents |
| :--- | :--- |
| [`showcase.cfg`](showcase.cfg) | Spheres, torus, tanglecube, two lights, floor reflections |
| [`primitives.cfg`](primitives.cfg) | One of each supported primitive on a reflective floor |
| [`materials.cfg`](materials.cfg) | Torus and three spheres, shadows and specular highlights |
| [`tangle.cfg`](tangle.cfg) | Close-up of a tanglecube |
| [`reflections.cfg`](reflections.cfg) | Glossy spheres, torus and a reflective floor |
| [`lighting.cfg`](lighting.cfg) | Three spheres under red and blue point lights |
| [`antialiasing-off.cfg`](antialiasing-off.cfg) | Tanglecube at 600x600, one sample per pixel |
| [`antialiasing-on.cfg`](antialiasing-on.cfg) | The same view with adaptive 8/16-sample antialiasing |

Positions and primitive sizes are integers. Rotations are in degrees.
Antialiasing sample counts can be 2, 4, 8 or 16.
