# MiniRT  

A basic Ray Tracing rendering engine part of 42 School program.  
It allow to render many geometrical shape such as sphere, plane, cylinder, triangle and ellipsoid. It handle diffuse  and ambiant light, specular reflection and bump map.  
It was created using the Codam MLX, a C graphical library based on the MLX of 42.  

This project has been made in collaboration with Gabriel Touzalin(https://github.com/TheEmperorPenguin)
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

You can modify the resolution by modifying the WIDTH et HEIGHT variables in config.h and use 
```
make re
```
Large resolution can be long to load

# Commands

You can move the camera using the following keys (QWERTY):
*     Forward: W
*     Backward: S
*     Left: A
*     Right: D
*     Up: spacebar
*     Down: Shift
*     Rotation on vertical axis: Up key - Down key
*     Rotation on horizontal rule axis: Left key - Right key
*     Rotation on frontal axis: Q - E

You can also select an object by clicking on it and move it with the numeric keypad


# Maps  

Maps must be written in '.rt' files.  
All elements must be specified by their code followed by the element specifications.  
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
C  coordinates(x, y, z) direction vector(x, y, z) FOV  
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

```  
tr first summit coordinates(x, y, z) second summit coordinates (x, y, x)  third summit coordinates (x, y, x)color(RGB)  
```  

***Ellipsoid***  
```  
el origin coordinates(x, y, z)  direction vector(x, y, z) semi-axes a length(float) semi-axes b length(float) semi-axes c length(float) color(RGB)  
```  

***Object specifications***  

Every object definition can be followed by specifications common to all objects:  
 - specular light ratio  
 - texture  

**Specular light**

The specular light is using the Phong reflection model
You can choose to specify by adding 'specular' after the definiton of an element and precising n coefficient and Ks coefficient following the Phong model.

**Textures**

You can also precise texture to add to element. There is 3 possibilities: 
    - Checkerboard:
        You can add a checkeboard effect on an element by adding 'checkerboad' after it's definition
    - PNG texture:
        You can apply a PNG image as a texture on an element by adding his relative path after the element definition
    - Bump map:
        You can apply a bump map as a texture on an element by adding 'bump' followed by the absolute path to the file

Maps must have at one and only one ambiant light and one camera.

# Examples
![image](https://hackmd.io/_uploads/r1yGhOsnp.png)

![image](https://hackmd.io/_uploads/SkqX3OjnT.png)

![image](https://hackmd.io/_uploads/SyQH3Osn6.png)



# Ressources 
- https://www.scratchapixel.com/index.html
- https://raytracing.github.io/books/RayTracingInOneWeekend.html
