# Ray-Tracing

## Basic Ray Tracing Project
The program is sending rays through 640x480 pixels and detecting collisions with spheres. Rays reflect for 1 time and provide calculating light and shadows.
![Image description](https://github.com/EnesTulga/Ray-Tracing/blob/master/Results/rayTracing2.png)

## Formulas
###### Ray Function
**Ro   :** Starting Position of Ray.\
**Rd   :** Direction Vector of Ray\
**t    :** Time variable\
**F(t) :** Ray Function\
**F(t) = Ro + Rd x t**

###### Sphere Function
**r    :** Radius of Sphere\
**Sp   :** Sphere Position (Spx, Spy, Spz)\
**(Spx x Spx) + (Spy x Spy) + (Spz x Spz) = (r x r)**

###### Ray - Sphere Intersect Detection
**F(t)** should equal to **(Spx, Spy, Spz)** vector.\
**Ro = (Rox, Roy, Roz)**\
**Rd x t = (Rdx x t, Rdy x t, Rdz x t)**\
In this case:\
**(Rox + (Rdx x t), Roy + (Rdy x t), Roz + (Rdz x t)) = (Spx, Spy, Spz)**\
If we can find a t value, that means ray intersects with sphere.\
But t should be greater than 0.İf we find two t values, we should choose the t value that the smaller than other and greater than zero.

## Info
Coded in OpenGL Shader Language / C++.\
Coded By **Enes Tulga**
