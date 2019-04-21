// ---------------------------------------------------------------------------------------
// Space3D
// Free POV-Ray script for space scenes rendering
// Copyright (C) 2005-2011 Pyramid
// Contact: pyramid@sapo.pt
// Internet: http://space3d.no.sapo.pt/
//
// This script is distributed with ABSOLUTELY NO WARRANTY;
// See the GNU General Public License for more details,
// which can be found in doc/SPACE3D_LICENSE.txt
//
// Persistence of Vision Ray Tracer Scene Description Include File
// File       : s3d_asteroid.inc
// Description: Creates virtual asteroids with texture maps
// Version    : 0.47
// Date       : 2011-04-07
// Author     : Pyramid
// Scale      : 1 POV Unit = 1km
// ---------------------------------------------------------------------------------------
// MACROS:
//   Asteroid(fRadius, cBaseColor, rAsteroid)
//   AsteroidField(fAsteroidRadius, cAsteroidColor, oBoundingObject, iMaxAsteroids, rAster)
// Internal objects:
//   AsteroidObject(iType, iSurface, fRadius, fCraterSize, cBaseColor, rAsteroid)
//      iType: 1-5
//      iSurface: 1-5
//        1: is a simple and fast texture - good for very distant asteroids
//        2: is a complex texture with craters and bumps - good for close ups   
//        3: is a more rocky looking complex texture
//        4: is an even more rocky complex texture
//        5: is a rocky but somehow flatter complex texture
//
// Old, obsolete parameters:
//  ASTEROID_TYPE_NUMBER 1-5
//    Determines the asteroid shape function used
//  ASTEROID_TEXTURE_NUMBER 1-5
//    1: is a simple and fast texture - good for very distant asteroids
//    2: is a complex texture with craters and bumps - good for close ups   
//    3: is a more rocky looking complex texture
//    4: is an even more rocky complex texture
//    5: is a rocky but somehow flatter complex texture
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
// Global Settings
// ---------------------------------------------------------------------------------------
#version 3.6;

// ---------------------------------------------------------------------------------------
// Include Files
// ---------------------------------------------------------------------------------------
#include "colors.inc"
#include "functions.inc"
#include "rand.inc" // random number generation macros

// ---------------------------------------------------------------------------------------
// User Settings
// ---------------------------------------------------------------------------------------
/*
#ifndef (ASTEROID_TYPE_NUMBER) 
  #declare ASTEROID_TYPE_NUMBER = 4; // range 1-5
#end
#ifndef (ASTEROID_TEXTURE_NUMBER) 
  #declare ASTEROID_TEXTURE_NUMBER = 1; // range 1-3
#end
#ifndef (ASTEROID_SHAPE_NR) 
   #declare ASTEROID_SHAPE_NR = 1;
#end
#ifndef (ASTEROID_CRATER_TYPE) 
   #declare ASTEROID_CRATER_TYPE = 0;
#end
#ifndef (asteroid_radius)
   #declare asteroid_radius = 1.0;
#end
#ifndef (asteroid_rotation)
   #declare asteroid_rotation = <0,0,0>;
#end
#ifndef (asteroid_translation)
   #declare asteroid_translation = <0,0,0>;
#end
#ifndef (asteroid_color)
   #declare asteroid_color = rgb <1,1,1>;
#end
#ifndef (crater_size)
   #declare crater_size = 1.0;
#end
#ifndef (show_background)
   #declare show_background = false;
#end
#ifndef (create_logfile)
   #declare create_logfile = false;
#end
*/

// -------------------------------//
// Camera, Lights, Background     //
// -------------------------------//

// -----------//
// Camera     //
// -----------//

// the following code is for stand-alone rendering only
/*
#ifndef (CAMERA)
  #debug "Earth.inc: camera not defined"
  #declare CAMERA = 4; // 1= full; 2= quarter; 3= closeup; 4= top; 5=right very close
  #debug concat("Earth.inc: camera ", str(CAMERA,4,4),"\n")
#end
*/

/*#ifdef (CAMERA)

#if (CAMERA = 1)
   // asteroid total
   camera {
     location <0, 0, -5*asteroid_radius>
     direction z
     right     x*image_width/image_height
     look_at <0, 0, 0>
     angle 50
   }    
#end

#if (CAMERA = 2)
   // asteroid surface closeup
   camera {
     location <0, 0, -asteroid_radius>
     direction z
     right     x*image_width/image_height
     look_at <0, 0, 0>
     angle 50
   }
#end

#end //def camera
*/

// -----------//
// Lights
// -----------//
/*
#ifndef (sun)
  #declare sun_location = <asteroid_radius*2000, asteroid_radius*2000, -asteroid_radius*1000>;
  #declare sun = light_source {
      sun_location
      color White
  }
light_source { sun }
#end
*/

// -----------//
// Background
// -----------//
/*
#if (show_background) 

   #ifndef (Starfield)

      // Adapted from starfield texture by Jim Burton
      #declare Starfield = sky_sphere { //<0,0,0>, CamZPos * 10000/3
      		pigment {
       			granite
      			color_map {
      				[ 0.00  0.72 color Black  color Black ]  // No Stars in this area
       				[ 0.72  0.75 color Gray20 color Gray40 ] // Very Very Faints
       				[ 0.75  0.78 color Gray40 color Gray60 ] // Very Faint Stars
      				[ 0.78  0.81 color Gray60 color Gray80 ] // Faint Stars
      				[ 0.81  0.85 color Gray80 color Gray95 ] // Medium White Stars
      				[ 0.85  0.91 color Gray95 color White  ] // White Stars
      				[ 0.91  1.00 color Black  color Black ]  // No Stars in this area
      			}
      			scale 2e-3
      		}
      }
      sky_sphere { Starfield }
*/   
   /*// Adapted from starfield texture by Jim Burton
   #declare CamZPos = 10;
   sphere { <0,0,0>, CamZPos * 10000/3
   	texture {
   		finish { ambient 1 diffuse 0 }
   		pigment {
    			granite
   			color_map {
   				[ 0.00  0.72 color Black  color Black ]  // No Stars in this area
    				[ 0.72  0.75 color Gray20 color Gray40 ] // Very Very Faints
    				[ 0.75  0.78 color Gray40 color Gray60 ] // Very Faint Stars
   				[ 0.78  0.81 color Gray60 color Gray80 ] // Faint Stars
   				[ 0.81  0.85 color Gray80 color Gray95 ] // Medium White Stars
   				[ 0.85  0.91 color Gray95 color White  ] // White Stars
   				[ 0.91  1.00 color Black  color Black ]  // No Stars in this area
   			}
   			scale CamZPos * 10000/image_width
   		}
   	}
   }
   */
   
  // #end

//#end

// -------------------------------//
// Asteroid Object                //
// -------------------------------//

//#ifndef (function_counter)
//   #declare function_counter = 0;
//#end
#ifdef (Asteroid_Shape_Function)
      #undef Asteroid_Shape_Function
#end

// ---------------------------------------------------------------------------------------
// Logging
// ---------------------------------------------------------------------------------------

#if (create_logfile)
   #if (defined(LogFile)=false)
      #fopen LogFile "s3d_asteroid_inc.log"
      #if(frame_number<=1) write
      #else append
      #end
   #end
   #write(LogFile,"[Frame_",frame_number,"]\n")
#end

// ---------------------------------------------------------------------------------------
// Asteroid Functions
// ---------------------------------------------------------------------------------------

#macro F_Asteroid1(S)
      //#declare S = seed(ASTEROID_SHAPE_NR);
      #declare s_x = RRand(0.5,1.0,S); //0.5-2.0
      #declare s_y = RRand(0.3,2.0,S); //0.3-3.0
      #declare s_z = RRand(0.3,2.0,S);
      #declare s_r = RRand(0.5,1.0,S); //0.5-1.0
      #declare n_x = RRand(0.9*s_x,1.5*s_x,S); //0.9-1.5
      #declare n_y = RRand(0.9*s_y,1.5*s_y,S);
      #declare n_z = RRand(0.9*s_z,1.5*s_z,S);
      #declare n_f = RRand(0.3,0.8,S); //0.3-0.8
      #if (create_logfile)
         #write(LogFile,"sphere x,y,z,radius = ",s_x,", ",s_y,", ",s_z,", ",s_r,", ","\n")
         #write(LogFile,"noise x,y,z,factor = ",n_x,", ",n_y,", ",n_z,", ",n_f,", ","\n")
      #end      
      //#declare function_counter = function_counter + 1;     
      //#declare Asteroid_Shape_Function[function_counter] = function { f_sphere(x*s_x , y*s_y , z*s_z , s_r)  - f_noise3d(x * n_x, y * n_y, z * n_z) * n_f };
      //#declare Asteroid_Shape_Function = function { f_sphere(x*s_x , y*s_y , z*s_z , s_r)  - f_noise3d(x * n_x, y * n_y, z * n_z) * n_f };
      function { f_sphere(x*s_x , y*s_y , z*s_z , s_r)  - f_noise3d(x * n_x, y * n_y, z * n_z) * n_f }
#end

#macro F_Asteroid2(S)
      //#declare S = seed(ASTEROID_SHAPE_NR);
      #declare s_x = RRand(0.2,0.8,S); // 0.2-0.8
      #declare s_y = RRand(0.3,0.8,S);
      #declare s_z = RRand(0.3,0.8,S);
      #declare s_r = 1/RRand(0.8,1.2,S); //0.8-1.2
      #declare n_x = RRand(0.2*s_r,0.5,S); //0.2-0.5 // reduces shape variety and size, increases blobs
      #declare n_y = RRand(0.2*s_r,0.5,S);
      #declare n_z = RRand(0.2*s_r,0.5,S);
      #declare n_f = RRand(0.8,1.2,S); //0.8-1.2 // reduces global shape noise, increases size
      #if (create_logfile)
         #write(LogFile,"sphere x,y,z,radius = ",s_x,", ",s_y,", ",s_z,", ",s_r,", ","\n")
         #write(LogFile,"noise x,y,z,factor = ",n_x,", ",n_y,", ",n_z,", ",n_f,", ","\n")
      #end      
      //#declare function_counter = function_counter + 1;
      // parameters: x,y,z & x,y,z scale (inverse)
      //#ifndef (Asteroid_Shape_Function)
         //#declare Asteroid_Shape_Function = array[20001];
      //#end
      //#declare Asteroid_Shape_Function = function { f_ellipsoid(x*s_x , y*s_y , z*s_z, s_r, s_r, s_r) - f_noise3d(x * n_x, y * n_y, z * n_z) * n_f };
      //#declare Asteroid_Shape_Function[function_counter] = function { f_ellipsoid(x*s_x , y*s_y , z*s_z, s_r, s_r, s_r) - f_noise3d(x * n_x, y * n_y, z * n_z) * n_f };
      //#declare Asteroid_Shape_Function[function_counter] = function { f_ellipsoid(x*s_x , y*s_y , z*s_z, 1, 1, 1) - f_noise3d(x*s_x, y*s_x, z*s_x) * 1.05 };
      function { f_ellipsoid(x*s_x , y*s_y , z*s_z, s_r, s_r, s_r) - f_noise3d(x * n_x, y * n_y, z * n_z) * n_f }
#end

#macro F_Asteroid3(S)
      //#declare S = seed(ASTEROID_SHAPE_NR);
      #declare s_x = RRand(0.5,2.0,S); //0.2-2.0
      #declare s_y = RRand(0.3*s_x,2*s_x,S);
      #declare s_z = RRand(0.3*s_y,2*s_y,S);
      #declare s_r = RRand(0.8,1.0,S);
      #declare n_x = RRand(0.9*s_x,1.5*s_x,S);
      #declare n_y = RRand(0.9*s_y,1.5*s_y,S);
      #declare n_z = RRand(0.9*s_z,1.5*s_z,S);
      #declare n_f = RRand(0.3,0.8,S); // relative noise strength
      #if (create_logfile)
         #write(LogFile,"sphere x,y,z,radius = ",s_x,", ",s_y,", ",s_z,", ",s_r,", ","\n")
         #write(LogFile,"noise x,y,z,factor = ",n_x,", ",n_y,", ",n_z,", ",n_f,", ","\n")
      #end
      //#declare function_counter = function_counter + 1;     
      //#declare Asteroid_Shape_Function = function { f_sphere(x*s_x , y*s_y , z*s_z , s_r)  - f_noise3d(x * n_x, y * n_y, z * n_z) * n_f };
      //#declare Asteroid_Shape_Function[function_counter] = function { f_sphere(x*s_x , y*s_y , z*s_z , s_r)  - f_noise3d(x * n_x, y * n_y, z * n_z) * n_f };
      function { f_sphere(x*s_x , y*s_y , z*s_z , s_r)  - f_noise3d(x * n_x, y * n_y, z * n_z) * n_f }
#end

#macro F_Asteroid4(S)
    //#declare S = seed(ASTEROID_SHAPE_NR);
    #declare s_x = RRand(0.5,1.5,S); //0.2-0.5 > size
    #declare s_y = RRand(0.5,1.5,S);
    #declare s_z = RRand(0.5,1.5,S);
    #declare s_r = RRand(0.75,0.85,S); //0.75-0.85 > edge rounding
    #declare n_x = RRand(0.5,1.1,S); //0.5-1.1 > noise size
    #declare n_y = RRand(0.5,1.1,S);
    #declare n_z = RRand(0.5,1.1,S);
    #declare n_f = RRand(0.15,0.3,S); // 0.1-0.3 > noise strength
    #if (create_logfile)
        #write(LogFile,"sphere x,y,z,radius = ",s_x,", ",s_y,", ",s_z,", ",s_r,", ","\n")
        #write(LogFile,"noise x,y,z,factor = ",n_x,", ",n_y,", ",n_z,", ",n_f,", ","\n")
    #end
    //#declare function_counter = function_counter + 1;     
    //#declare Asteroid_Shape_Function = function { -f_superellipsoid(x*s_x, y*s_y, z*s_z, s_r, s_r) + f_noise3d(x*n_x, y*n_y, z*n_z) * n_f };
    //#declare Asteroid_Shape_Function[function_counter] = function { -f_superellipsoid(x*s_x, y*s_y, z*s_z, s_r, s_r) + f_noise3d(x*n_x, y*n_y, z*n_z) * n_f };
    //#declare Asteroid_Shape_Function[function_counter] = function { -f_superellipsoid(x*0.3, y*0.3, z*0.3, 0.8, 0.8) + f_noise3d(x*0.99, y*0.99, z*0.99) * 0.2 };
    function { -f_superellipsoid(x*s_x, y*s_y, z*s_z, s_r, s_r) + f_noise3d(x*n_x, y*n_y, z*n_z) * n_f }
#end

#macro F_Asteroid5(S)
      //#declare S = seed(ASTEROID_SHAPE_NR);
      #declare s_x = RRand(0.5,1.5,S); //0.2-0.5 > size
      #declare s_y = RRand(0.5,1.5,S);
      #declare s_z = RRand(0.5,1.5,S);
      #declare s_r = RRand(0.75,0.85,S); //0.75-0.85 > edge rounding
      #declare n_x = RRand(0.5,1.1,S); //0.5-1.1 > noise size
      #declare n_y = RRand(0.5,1.1,S);
      #declare n_z = RRand(0.5,1.1,S);
      #declare n_f = RRand(0.15,0.3,S); // 0.1-0.3 > noise strength
      #declare b_x = RRand(10,30,S); //5-20 > ratio radius / noise size
      #declare b_y = RRand(10,30,S);
      #declare b_z = RRand(10,30,S);
      #declare b_f = RRand(0.015,0.025,S); // 0.01-0.10 > noise strength
      #if (create_logfile)
         #write(LogFile,"sphere x,y,z,radius = ",s_x,", ",s_y,", ",s_z,", ",s_r,", ","\n")
         #write(LogFile,"shape x,y,z,factor = ",n_x,", ",n_y,", ",n_z,", ",n_f,", ","\n")
         #write(LogFile,"noise x,y,z,factor = ",b_x,", ",b_y,", ",b_z,", ",b_f,", ","\n")
      #end
      //#declare function_counter = function_counter + 1;     
      //#declare Asteroid_Shape_Function = function { -f_superellipsoid(x*s_x, y*s_y, z*s_z, s_r, s_r) + f_noise3d(x*n_x, y*n_y, z*n_z) * n_f - f_noise3d(x*b_x, y*b_y, z*b_z) * b_f };
      //#declare Asteroid_Shape_Function[function_counter] = function { -f_superellipsoid(x*s_x, y*s_y, z*s_z, s_r, s_r) + f_noise3d(x*n_x, y*n_y, z*n_z) * n_f - f_noise3d(x*b_x, y*b_y, z*b_z) * b_f };
      //#declare Asteroid_Shape_Function[function_counter] = function { -f_superellipsoid(x*0.3, y*0.3, z*0.3, 0.8, 0.8) + f_noise3d(x*0.99, y*0.99, z*0.99) * 0.2 };
      function { -f_superellipsoid(x*s_x, y*s_y, z*s_z, s_r, s_r) + f_noise3d(x*n_x, y*n_y, z*n_z) * n_f - f_noise3d(x*b_x, y*b_y, z*b_z) * b_f }
#end

// ---------------------------------------------------------------------------------------
// Asteroid Textures
// ---------------------------------------------------------------------------------------

// simple stone surface
// ASTEROID_TEXTURE_NUMBER = 1
#macro T_AsteroidTexture1(cColor)
  texture {
    pigment { cColor }
    normal {
        pigment_pattern { granite } -0.2
        accuracy 1/5000
    }
    //finish {  surface_finish }
  }
#end

// absolute size craters, relative size local bump
// ASTEROID_TEXTURE_NUMBER = 2
#macro T_AsteroidTexture2(fRadius, fCraterSize, cColor, S)
  //#declare S = seed(ASTEROID_SHAPE_NR + ASTEROID_CRATER_TYPE);
  #declare DensityCurve =
  spline {
     0.0 <0,0.15,0>
     // position controls the amount of big vs small craters
     // 0.1 => more large craters
     // 0.9 => more small craters
     0.7 <.5,.55,0> // 0.9 * rand(S) <.5,.15,0>
     1.0 <1,1,0>
  };
  #if (s_r > 0)
    #declare CR_AS_RADIUS_FIX = s_r*fCraterSize;
  #else
    #declare CR_AS_RADIUS_FIX = 1.0*fCraterSize;
  #end
  #ifndef (CRATERS_NUMBER)
    #declare CRATERS_NUMBER = IRand(10, 150, S); //range 1-256
  #end
  #declare CRATER_BUMP = pigment {
     average
     pigment_map {
        #local I=0;#while(I<CRATERS_NUMBER)
            //#local ScaleFactor = DensityCurve(rand(S)).y; // asteroid_radius;
            #local ScaleFactor = DensityCurve(rand(S)).y / fRadius;
            [1 cylindrical
                // scale defines the global size of craters
                scale 0.25 * ScaleFactor * CR_AS_RADIUS_FIX // 0.25 - 0.45
                #local ScaleFactor = 0.5 * ScaleFactor;
                cubic_wave
                turbulence 0.1*ScaleFactor // 0.0 - 0.8
                pigment_map {
                   //[0.0 pigment_pattern { granite scale 10 turbulence 0} color_map { [0.1 rgb <1,0,0>] [0.91 rgb <1,0,0>] } ] // outside color
                   // pigment map parameters: [radius from outer edge, rgb crater depth]
                   [0.00 rgb 0.95 ] // outside color
                   [0.05 rgb 1.0] // thickness of outer edge
                   [0.10 rgb 0.79] // crater curve
                   [0.20 rgb 0.61] // crater curve
                   [0.41 rgb 0.29] // crater curve
                   [0.69 rgb 0.15] // crater curve
                   [1.00 rgb 0.0] // edge extension to center
                }
                rotate <rand(S)*180,rand(S)*180,rand(S)*180>
            ]
        #local I=I+1;#end
     }
  }; // crater pigment
  
  // defines both size and impression of craters
  // small number = less impression depth, but more overlap
  // small number > have to increase crater bump scale size
  // best for 1.0 radius sphere: CRATERS_ITERATIONS = rand(S)*10, scale 0.55*ScaleFactor
  #ifndef (CRATERS_ITERATIONS)
    #declare CRATERS_ITERATIONS = 2; //range 1-12
  #end
  texture {
  pigment { pigment_pattern { granite } color_map { [0.1 cColor] [0.9 cColor] } scale 0.1 }
  normal {
    average
    normal_map {
       [ 1.0 pigment_pattern {
          average
          pigment_map {
          #local Scl = 1;
          #local I=0;#while(I<CRATERS_ITERATIONS)
             // weight defines the prominence of craters in relation with surface bump
             [CRATERS_NUMBER CRATER_BUMP
                scale Scl
                rotate <rand(S)*180,rand(S)*180,rand(S)*180>
             ]
          #local Scl=Scl*.8;
          #local I=I+1;#end
             // global bumps (for totals)
             // weight defines bump depth (~0.2-1.0)
             // scale defines the amount of bumps (~10-100) // -2-50
             // turbulence defines the prominence of global bumps
             [rand(S)*0.6*CRATERS_ITERATIONS pigment_pattern { granite } pigment_map { [0.1 cColor] [0.9 rgb 0] } scale 20 turbulence 0.2 ]
          } //p_m
       } //p_p 
       //bump_size 1.0*CRATERS_NUMBER // 5-10
       bump_size 1.0*CRATERS_NUMBER*CRATERS_ITERATIONS // 5-10
       ]
       //local bumps (for close ups)
       // weigth defines prominence against craters //0.05-0.50
       // scale defines the spacing of bumps
       // bump size defines depth //0.1-1.0
       [ 1.0 pigment_pattern { granite } scale 0.1*RRand(0.8,1.2,S) turbulence rand(S)*0.15 // the closer the smaller the scale
       //bump_size -0.3 //0.1-1.0 
       bump_size -0.3*CRATERS_ITERATIONS //-0.3-1.0 
       ] 
  } //n_m
  bump_size 5*CRATERS_ITERATIONS //5-10
  } //normal
  } // texture
#end

// absolute size craters, relative size local bump
// as texture 2, but more rocky strength
// ASTEROID_TEXTURE_NUMBER = 3
#macro T_AsteroidTexture3(fRadius, fCraterSize, cColor, S)
  //#declare S = seed(ASTEROID_SHAPE_NR + ASTEROID_CRATER_TYPE);
  #declare DensityCurve = spline { 0.0 <0,0.15,0> 0.7 <.5,.55,0> 1.0 <1,1,0> };
  #if (s_r > 0)
    #declare CR_AS_RADIUS_FIX = s_r*fCraterSize;
  #else
    #declare CR_AS_RADIUS_FIX = 1.0*fCraterSize;
  #end
  #ifndef (CRATERS_NUMBER)
    #declare CRATERS_NUMBER = IRand(10, 150, S); //range 1-256
  #end
  #declare CRATER_BUMP =
  pigment {
     average
     pigment_map {
        #local I=0;#while(I<CRATERS_NUMBER)
            #local ScaleFactor = DensityCurve(rand(S)).y / fRadius;
            [1 cylindrical
                scale 0.25*ScaleFactor*CR_AS_RADIUS_FIX // 0.25 - 0.45
                #local ScaleFactor =  .5*ScaleFactor;
                cubic_wave
                turbulence 0.1*ScaleFactor // 0.0 - 0.8
                pigment_map {
                   [0.00 rgb 0.95 ] // outside color
                   [0.05 rgb 1.0] // thickness of outer edge
                   [0.10 rgb 0.79] // crater curve
                   [0.20 rgb 0.61] // crater curve
                   [0.41 rgb 0.29] // crater curve
                   [0.69 rgb 0.15] // crater curve
                   [1.00 rgb 0.0] // edge extension to center
                }
                rotate <rand(S)*180,rand(S)*180,rand(S)*180>
            ]
        #local I=I+1;#end
     }
  };
  
  #ifndef (CRATERS_ITERATIONS)
    #declare CRATERS_ITERATIONS = 2; //range 1-12
  #end
  texture {
  pigment { pigment_pattern { granite } color_map { [0.1 cColor] [0.9 cColor] } scale 0.1 }
  normal {
    average
    normal_map {
       [ 1.0 pigment_pattern {
          average
          pigment_map {
          #local Scl = 1;
          #local I=0;#while(I<CRATERS_ITERATIONS)
             [CRATERS_NUMBER CRATER_BUMP
                scale Scl
                rotate <rand(S)*180,rand(S)*180,rand(S)*180>
             ]
          #local Scl=Scl*.8;
          #local I=I+1;#end
             // global bumps (for totals)
             [rand(S)*0.6*CRATERS_ITERATIONS pigment_pattern { granite } pigment_map { [0.1 cColor] [0.9 rgb 0] } scale 20 turbulence 0.20 ]
          } //p_m
       } //p_p 
       bump_size 1.0*CRATERS_NUMBER*CRATERS_ITERATIONS // 5-10
       ]
       //local bumps (for close ups)
       [ 1.0 pigment_pattern { granite } scale 0.15*RRand(0.8,1.2,S) turbulence rand(S)*0.35 // the closer the smaller the scale
       bump_size -2.0*CRATERS_ITERATIONS //0.1-1.0 
       ] 
  } //n_m
  bump_size 5*CRATERS_ITERATIONS //*CRATERS_NUMBER //5-10                                                
  } //normal
  } // texture
#end

// absolute size craters, relative size local bump
// as texture 3, but even more rocky strength
// ASTEROID_TEXTURE_NUMBER = 4
#macro T_AsteroidTexture4(fRadius, fCraterSize, cColor, S)
  //#declare S = seed(ASTEROID_SHAPE_NR + ASTEROID_CRATER_TYPE);
  #declare DensityCurve = spline { 0.0 <0,0.15,0> 0.7 <.5,.55,0> 1.0 <1,1,0> };
  #if (s_r > 0)
    #declare CR_AS_RADIUS_FIX = s_r*fCraterSize;
  #else
    #declare CR_AS_RADIUS_FIX = 1.0*fCraterSize;
  #end
  #ifndef (CRATERS_NUMBER)
    #declare CRATERS_NUMBER = IRand(10, 150, S); //range 1-256
  #end
  #declare CRATER_BUMP =
  pigment {
     average
     pigment_map {
        #local I=0;#while(I<CRATERS_NUMBER)
            #local ScaleFactor = DensityCurve(rand(S)).y / fRadius;
            [1 cylindrical
                scale 0.25*ScaleFactor*CR_AS_RADIUS_FIX // 0.25 - 0.45
                #local ScaleFactor =  .5*ScaleFactor;
                cubic_wave
                turbulence 0.1*ScaleFactor // 0.0 - 0.8
                pigment_map {
                   [0.00 rgb 0.95 ] // outside color
                   [0.05 rgb 1.0] // thickness of outer edge
                   [0.10 rgb 0.79] // crater curve
                   [0.20 rgb 0.61] // crater curve
                   [0.41 rgb 0.29] // crater curve
                   [0.69 rgb 0.15] // crater curve
                   [1.00 rgb 0.0] // edge extension to center
                }
                rotate <rand(S)*180,rand(S)*180,rand(S)*180>
            ]
        #local I=I+1;#end
     }
  };
  
  #ifndef (CRATERS_ITERATIONS)
    #declare CRATERS_ITERATIONS = 2; //range 1-12
  #end
  texture {
  pigment { pigment_pattern { granite } color_map { [0.1 cColor] [0.9 cColor] } scale 0.1 }
  normal {
    average
    normal_map {
       [ 1.0 pigment_pattern {
          average
          pigment_map {
          #local Scl = 1;
          #local I=0;#while(I<CRATERS_ITERATIONS)
             [CRATERS_NUMBER CRATER_BUMP
                scale Scl
                rotate <rand(S)*180,rand(S)*180,rand(S)*180>
             ]
          #local Scl=Scl*.8;
          #local I=I+1;#end
             // global bumps (for totals)
             [rand(S)*1.0*CRATERS_ITERATIONS pigment_pattern { granite } pigment_map { [0.2 cColor] [0.8 rgb 0] } scale 20 turbulence 1.0 ]
          } //p_m
       } //p_p 
       bump_size 1.0*CRATERS_NUMBER*CRATERS_ITERATIONS // 5-10
       ]
       //local bumps (for close ups)
       [ 1.0 pigment_pattern { granite } scale 0.1*RRand(0.8,1.2,S) turbulence rand(S)*0.55 // the closer the smaller the scale
       bump_size -1.0*CRATERS_ITERATIONS //0.1-1.0 
       ] 
  } //n_m
  bump_size 5*CRATERS_ITERATIONS //*CRATERS_NUMBER //5-10                                                
  } //normal
  //finish {  surface_finish }
  } // texture
#end

// absolute size craters, relative size local bump
// as texture 4, almost flat surface
// ASTEROID_TEXTURE_NUMBER = 5
#macro T_AsteroidTexture5(fRadius, fCraterSize, cColor, S)
  //#declare S = seed(ASTEROID_SHAPE_NR + ASTEROID_CRATER_TYPE);
  #declare DensityCurve = spline { 0.0 <0,0.55,0> 0.7 <.5,.75,0> 1.0 <1,1,0> };
  #if (s_r > 0)
    #declare CR_AS_RADIUS_FIX = s_r*fCraterSize;
  #else
    #declare CR_AS_RADIUS_FIX = 1.0*fCraterSize;
  #end
  #ifndef (CRATERS_NUMBER)
    #declare CRATERS_NUMBER = IRand(10, 150, S); //range 1-256
  #end
  #declare CRATER_BUMP =
  pigment {
     average
     pigment_map {
        #local I=0;#while(I<CRATERS_NUMBER)
            #local ScaleFactor = DensityCurve(rand(S)).y / fRadius;
            [1 cylindrical
                scale 0.25*ScaleFactor*CR_AS_RADIUS_FIX // 0.25 - 0.45
                #local ScaleFactor =  .5*ScaleFactor;
                cubic_wave
                turbulence 0.1*ScaleFactor // 0.0 - 0.8
                pigment_map {
                   [0.00 rgb 0.95 ] // outside color
                   [0.05 rgb 1.0] // thickness of outer edge
                   [0.10 rgb 0.79] // crater curve
                   [0.20 rgb 0.61] // crater curve
                   [0.41 rgb 0.29] // crater curve
                   [0.69 rgb 0.15] // crater curve
                   [1.00 rgb 0.0] // edge extension to center
                }
                rotate <rand(S)*180,rand(S)*180,rand(S)*180>
            ]
        #local I=I+1;#end
     }
  };
  
  #ifndef (CRATERS_ITERATIONS)
    #declare CRATERS_ITERATIONS = 2; //range 1-12
  #end
  texture {
    pigment { pigment_pattern { granite } color_map { [0.1 cColor] [0.9 cColor] } scale 0.1 }
      normal {
        average
        normal_map {
           [ 1.0 pigment_pattern {
              average
              pigment_map {
              #local Scl = 1;
              #local I=0;#while(I<CRATERS_ITERATIONS)
                 [CRATERS_NUMBER CRATER_BUMP
                    scale Scl
                    rotate <rand(S)*180,rand(S)*180,rand(S)*180>
                 ]
              #local Scl=Scl*.8;
              #local I=I+1;#end
                 // global bumps (for totals)
                 [1.0*CRATERS_ITERATIONS pigment_pattern { bumps } pigment_map { [0.3 rgb 1] [1.0 rgb 0] } scale 1.5 turbulence 2.5 ]
                 //[1.0*CRATERS_ITERATIONS pigment_pattern { bumps } pigment_map { [0.3 rgb 1] [1.0 rgb 0] } scale 5 turbulence 0.5 ]
              } //p_m
           } //p_p 
           bump_size 1.0*CRATERS_NUMBER*CRATERS_ITERATIONS // 5-10
           ]
           //local bumps (for close ups)
           [ 1.0 pigment_pattern { granite } scale 0.1*RRand(0.8,1.2,S) turbulence rand(S)*20 // the closer the smaller the scale
           //[ 1.0 pigment_pattern { granite } scale 0.1*pow(asteroid_radius,0.5)*RRand(0.8,1.2,S) turbulence rand(S)*0.15 // the closer the smaller the scale
           bump_size -0.8*CRATERS_ITERATIONS //0.1-1.0 
           ] 
     } //n_m
     bump_size 5*CRATERS_ITERATIONS //*CRATERS_NUMBER //5-10                                                
     } //normal
  } // texture
#end

// ---------------------------------------------------------------------------------------
// Asteroid Objects
// ---------------------------------------------------------------------------------------

#macro AsteroidObject(iType, iSurface, fRadius, fCraterSize, cBaseColor, rAsteroid)
  isosurface {
    //function { Asteroid_Shape_Function(x,y,z) }
    #if(iType=0)
      #declare iType = IRand(1,5,rAsteroid);
    #end
    #switch (iType)
      #case(1) F_Asteroid1(rAsteroid) #break
      #case(2) F_Asteroid2(rAsteroid) #break
      #case(3) F_Asteroid3(rAsteroid) #break
      #case(4) F_Asteroid4(rAsteroid) #break
      #case(5) F_Asteroid5(rAsteroid) #break
    #end

    contained_by{sphere{0,5}}
    accuracy 0.001
    max_gradient 2.000 // for scenes
    //max_gradient 5.000 // for catalog
    
    #if(iSurface=0)
      #declare iSurface = IRand(1,5,rAsteroid);
    #end
    #switch (iSurface)
      #case(1) T_AsteroidTexture1(cBaseColor) #break
      #case(2) T_AsteroidTexture2(fRadius, fCraterSize, cBaseColor, rAsteroid) #break
      #case(3) T_AsteroidTexture3(fRadius, fCraterSize, cBaseColor, rAsteroid) #break
      #case(4) T_AsteroidTexture4(fRadius, fCraterSize, cBaseColor, rAsteroid) #break
      #case(5) T_AsteroidTexture5(fRadius, fCraterSize, cBaseColor, rAsteroid) #break
    #end
    finish {  surface_finish }
    
    scale fRadius
    
    #if (create_logfile)
      #write(LogFile,"fRadius = ",fRadius,"\n")
    #end
    hollow
  }

#end

#macro Asteroid(fRadius, cAsteroidColor, rAsteroid)
  AsteroidObject(0, 0, fRadius, RRand(0.5, 1.5, rAsteroid), cAsteroidColor, rAsteroid)  
#end

// ---------------------------------------------------------------------------------------
//  Ateroid Field
// ---------------------------------------------------------------------------------------

#macro AsteroidField(fAsteroidRadius, cAsteroidColor, oBoundingObject, iMaxAsteroids, rAster)  
  #local I=0;#while(I<iMaxAsteroids)
    #declare asteroid_radius = fAsteroidRadius * RRand(0.1,2,rAster);
    #declare asteroid_translation = VRand_In_Obj(oBoundingObject,rAster);
    #local xrot = RRand(-1,1,rAster)*360; 
    #local yrot = RRand(-1,1,rAster)*360; 
    #local zrot = RRand(-1,1,rAster)*360; 
    #declare asteroid_rotation = <xrot,yrot,zrot>;
    object { Asteroid(asteroid_radius, cAsteroidColor, rAster) rotate asteroid_rotation translate asteroid_translation }
  #local I=I+1;#end
#end

// close log
#if (create_logfile)
   #write(LogFile,"\n")
   #fclose LogFile
#end

// EOF