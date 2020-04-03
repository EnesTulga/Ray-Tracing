# Ray-Tracing

## Basic Ray Tracing Project
The program is sending rays through 640x480 pixels and detecting collisions with spheres. Rays reflect for 1 time and provide calculating light and shadows.\
![Image description](https://github.com/EnesTulga/Ray-Tracing/blob/master/Results/rayTracing2.png)

## Formulas
###### Ray Function
**RO   :** Starting Position of Ray.\
**RD   :** Direction Vector of Ray\
**t    :** Time variable\
**F(t) :** Ray Function\
**F(t) = RO + RD * t**

###### Sphere Function
**r    :** Radius of Sphere\
**SP   :** Sphere Position (Spx, Spy, Spz)\
**(SPx * SPx) + (SPy * SPy) + (SPz * SPz) = (r * r)**

###### Ray - Sphere Intersect Detection
**F(t)** should equal to **(SPx, SPy, SPz)** vector.\
**RO = (ROx, ROy, ROz)**\
**RD x t = (RDx * t, RDy * t, RDz * t)**\
In this case:\
**RP = (ROx + (RDx * t), ROy + (RDy * t), ROz + (RDz * t)) = (SPx, SPy, SPz)**\
Then:\
**(RPx * RPx) + (RPy * RPy) + (RPz * RPz) = (r * r)**\
If we can find a t value for that equation, that means ray intersects with sphere.\
But t should be greater than 0.İf we find two t values, we should choose the t value that is minimum positive one.\
In this case :\
**(RPx * RPx) = (ROx * ROx) + (2 * ROx * RDx * t) + (RDx * RDx * t * t)**\
**(RPy * RPy) = (ROy * ROy) + (2 * ROy * RDy * t) + (RDy * RDy * t * t)**\
**(RPz * RPz) = (ROz * ROz) + (2 * ROz * RDz * t) + (RDz * RDz * t * t)**

If we gather all equations as:\
**A (t * t) + B (t) + C**\
**A = (RDx * RDx) + (RDy * RDy) + (RDz * RDz)**\
**B = 2 * ((ROx * RDx) + (ROy * RDy) + (ROz * RDz))**\
**C = (ROx * ROx) + (ROy * ROy) + (ROz * ROz)**

Now we should find discriminant cause we are searching for a t value:\
**Discriminant: DC = (B * B) - (4 * A * C)**\

Now we should examine discriminant:\
**1) If DC > 0 => There are two roots. We should choose the root that is minimum positive one.**\
**2) If DC = 0 => There is 1 root. If it is not negative, our ray intersects. If it is negative, it intersects on opposite direction.**\
**3) If DC < 0 => There is no root. Ray does not intersect.**

For first situation:\
**t = (-B + SquareRoot(DC)) / (2 * A) or t = (-B - SquareRoot(DC)) / (2 * A)**

For second situation, it doesn't matter the formula which one you choose on the above. Both of them give same result.\
After putting t value into F(t) function, we can find the position of ray and sphere's intersection:\
**F(t) = RO + RD * t**

## Info
Coded in OpenGL Shader Language / C++.\
Coded By **Enes Tulga**
