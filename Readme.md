# MiniRT

A basic Ray Tracing rendering engine part of 42 School program.
It allow to render many geometrical shape such as sphere, plane, cylinder, triangle and ellipsoid. It handle diffuse  and ambiant light, specular reflection and bump map.
It was created using the Codam MLX, a C graphical library based on the MLX of 42.

# Installation

Clone the repo the use
``` bash
make 
```
to build the binary.

# Usage

``` bash
./miniRT {map}
```
Replace {map} by the path to your map

# Maps

Maps must be written in '.rt' files.
All elements must be specified by their followed by the element specifications.
Lines with wrong ids will be ignored.

***Ambiant light***
```
A Intensity([0-1]) color(RGB)
```

***Spotlight***
```
L coordinates(x, y, z) intensity([0-1]) color(RGB)
```

***Camera***
```
C  coordinates(x, y, z) direction vector(x, y, z) FOV
```

***Sphere***
```
s coordinates (x, y, z) diameter color(RGB)
```

***Plane***
```
p coordinates(x, y, z) direction vector(x, y, z) color(RGB)
```

***Cylinder***
```
cy coordinates (x, y, z) direction vector(x, y, z) diameter height color(RGB)
```
***Triangle***


***Ellipsoid***


Maps must have at one and only one ambiant light and one camera.