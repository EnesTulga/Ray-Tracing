# Ray-Tracing

## Basic Ray Tracing Project
The program is sending rays through 640x480 pixels and detecting collisions with spheres. Rays reflect for 1 time and provide calculating light and shadows.\
![Image description](https://github.com/EnesTulga/Ray-Tracing/blob/master/Results/rayTracing2.png)

## Formulas
###### Ray Function
**Ro   :** Starting Position of Ray.\
**Rd   :** Direction Vector of Ray\
**t    :** Time variable\
**F(t) :** Ray Function\
**F(t) = Ro + Rd * t**

###### Sphere Function
**r    :** Radius of Sphere\
**Sp   :** Sphere Position (Spx, Spy, Spz)\
**(Spx * Spx) + (Spy * Spy) + (Spz * Spz) = (r * r)**

###### Ray - Sphere Intersect Detection
**F(t)** should equal to **(Spx, Spy, Spz)** vector.\
**Ro = (Rox, Roy, Roz)**\
**Rd x t = (Rdx * t, Rdy * t, Rdz * t)**\
In this case:\
**Rp = (Rox + (Rdx * t), Roy + (Rdy * t), Roz + (Rdz * t)) = (Spx, Spy, Spz)**\
Then:\
**(Rpx * Rpx) + (Rpy * Rpy) + (Rpz * Rpz) = (r * r)**\
If we can find a t value for that equation, that means ray intersects with sphere.\
But t should be greater than 0.İf we find two t values, we should choose the t value that the smaller than other and greater than zero.

## Info
Coded in OpenGL Shader Language / C++.\
Coded By **Enes Tulga**
