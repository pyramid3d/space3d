```bash
#====================================
# @file   : README.md (Space3D)
# @version: 0.55
# @version: 2020-03-09
# @created: 2019-04-19
# @author : pyramid
# @brief  : documentation for space3d
#====================================
```



=====================================
# **Space3D**
## **Pov-Ray Space Rendering**
### **create space scenes, star backgrounds, planetary maps with Space3D (space3d) for pov-ray**
=====================================

=====================================
# Installation
=====================================

Copy the space3d.inc file and the include and maps directories to your working folder.
For solar system planet rendering, place the textures in the maps directory and update the file names in include/s3d_planet_maps.inc

=====================================
# Rendering
=====================================

Render the simple scene first (default or square aspect as intended for the scene)

```
> povray simple_scene.pov
> povray simple_scene.pov +W1024 +H1024
```

Continue rendering some tests.
There are 96 simple test scenes included which should give you a
nice overview of the script capabilities.
You may need to create a gallery directory first.
You will also need the arial.ttf font to be installed on your system.

```
> mkdir gallery
> povray s3d_test.ini
```


=====================================
# Arial Font on Linux
=====================================

Try installing fetchmsttfonts package on your Linux distro.
You should have arial.ttf available in /usr/share/fonts/truetype/

If necessary, do edit your povray.ini file and append the font path to the
Library_Path="/usr/share/fonts/truetype/"

```
> nano ~/povray/3.7/povray.ini
```

add the following line

```
Library_Path="/usr/share/fonts/truetype/"
```


=====================================
# Tutorials
=====================================

You can probably learn a lot just by analyzing the simple scene descriptions, looking oat the rendered image, and just playing with the different parameters.

The code is documented, and you may see the parameters description by searching for the respective function.#
For example:

```
> grep -r grep -r "#macro P_StarField"
include/s3d_starfield.inc:#macro P_StarField(cColor, fIntensity)
```


Tutorials are available on openTeq/Space3D blog (https://openteq.wordpress.com/portfolio/space3d/).

Pov-Ray documentation is available here

- http://www.povray.org/
- http://wiki.povray.org/


=====================================
# Solar System Object Texture Maps
=====================================

## Collections

http://planetpixelemporium.com/earth8081.html


## Solar System Planets

Mercury


Venus


Earth

http://planetpixelemporium.com/download/download.php?earthmap1k.jpg
license: public domain


Mars


Jupiter


Saturn


Uranus


Neptune


Pluto


## Solar System Moons



## Solar System Objects




