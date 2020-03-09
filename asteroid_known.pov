// ---------------------------------------------------------------------------
// Space3D
// Free POV-Ray script for space scenes rendering
// Copyright (C) 2005-2009 Pyramid
// Contact: pyramid@sapo.pt
// Internet: https://openteq.wordpress.com/portfolio/space3d/
// Internet: http://space3d.no.sapo.pt/ (discontinued)
//
// This script is distributed with ABSOLUTELY NO WARRANTY;
// See the GNU General Public License for more details,
// which can be found in doc/SPACE3D_LICENSE.txt
//
// Persistence of Vision Ray Tracer Scene Description File
// @file    : asteroid_known.pov
// @brief   : Space3D known asteroid showcase
// @version : 2019-05-03
// @created : 2005-10-28
// @author  : pyramid
// @internet: https://openteq.wordpress.com/portfolio/space3d/
// @internet: http://space3d.no.sapo.pt/ (discontinued)
// @scale   : 1 POV unit = 1 km
// ---------------------------------------------------------------------------
// Version History
// 2005-12-01 | v0.03 | 
// 2005-10-30 | v0.02 | added map and surface bump
// 2005-10-30 | v0.02 | include files for 12 known asteroids
// 2005-10-30 | v0.01 | basic scene file; include files for 12 known asteroids
// 2005-10-29 | v0.01 | include files for 12 known asteroids
// 2005-10-29 | v0.00 | converted asteroid models from other formats to mesh2
// 2005-10-28 | v0.00 | creation
// ---------------------------------------------------------------------------



// -------------------------------//
// Global Settings                //
// -------------------------------//
#version 3.6;
global_settings {
   assumed_gamma 2.2
   max_trace_level 10
}

// -------------------------------//
// Include Files                  //
// -------------------------------//
#include "colors.inc"
#include "textures.inc"
#include "include/asteroid_known/asteroid_known_almathea.inc"   //1
#include "include/asteroid_known/asteroid_known_castalia.inc"   //2
#include "include/asteroid_known/asteroid_known_deimos.inc"     //3
#include "include/asteroid_known/asteroid_known_epimetheus.inc" //4
#include "include/asteroid_known/asteroid_known_eros.inc"       //5
#include "include/asteroid_known/asteroid_known_gaspra.inc"     //6
#include "include/asteroid_known/asteroid_known_geographos.inc" //7
#include "include/asteroid_known/asteroid_known_hyperion.inc"   //8
#include "include/asteroid_known/asteroid_known_ida.inc"        //9
#include "include/asteroid_known/asteroid_known_ky26.inc"       //10
#include "include/asteroid_known/asteroid_known_phobos.inc"     //11
#include "include/asteroid_known/asteroid_known_toutatis.inc"   //12

// -------------------------------//
// User Settings                  //
// -------------------------------//
#if (frame_number = 0) 
  // change number to activate an example
  #declare ASTEROID_KNOWN_NUMBER = 1; // range 1-12
#else
  #declare ASTEROID_KNOWN_NUMBER = frame_number;
#end

#switch (ASTEROID_KNOWN_NUMBER)

   #case (1)
      #declare ASTEROID_MESH_NAME = asteroid_known_almathea;
      #declare CAMERA_LOCATION = <0, 0, -250>;
   #break

   #case (2)
      #declare ASTEROID_MESH_NAME = asteroid_known_castalia;
      #declare ASTEROID_PIGMENT_MAP = "maps/asteroid/castalia_map.jpg";
      #declare CAMERA_LOCATION = <0, 0, -1800>;
   #break

   #case (3)
      #declare ASTEROID_MESH_NAME = asteroid_known_deimos;
      #declare ASTEROID_PIGMENT_MAP = "maps/asteroid/deimos_cylindrical_hires.jpg";
      #declare CAMERA_LOCATION = <0, 0, -20>;
   #break

   #case (4)
      #declare ASTEROID_MESH_NAME = asteroid_known_epimetheus;
      #declare CAMERA_LOCATION = <0, 0, -200>;
   #break

   #case (5)
      #declare ASTEROID_MESH_NAME = asteroid_known_eros;
      #declare ASTEROID_PIGMENT_MAP = "maps/asteroid/eros_map.jpg";
      #declare CAMERA_LOCATION = <0, 0, -30>;
   #break

   #case (6)
      #declare ASTEROID_MESH_NAME = asteroid_known_gaspra;
      #declare ASTEROID_PIGMENT_MAP = "maps/asteroid/gaspra_map.jpg";
      #declare CAMERA_LOCATION = <0, 0, -40>;
   #break

   #case (7)
      #declare ASTEROID_MESH_NAME = asteroid_known_geographos;
      #declare CAMERA_LOCATION = <0, 0, -30>;
   #break

   #case (8)
      #declare ASTEROID_MESH_NAME = asteroid_known_hyperion;
      #declare ASTEROID_PIGMENT_MAP = "maps/asteroid/hyperion_map.jpg";
      #declare CAMERA_LOCATION = <0, 0, -500>;
   #break

   #case (9)
      #declare ASTEROID_MESH_NAME = asteroid_known_ida;
      #declare ASTEROID_PIGMENT_MAP = "maps/asteroid/ida_mosaic.jpg";
      #declare CAMERA_LOCATION = <0, 0, -80>;
   #break

   #case (10)
      #declare ASTEROID_MESH_NAME = asteroid_known_ky26;
      #declare CAMERA_LOCATION = <0, 0, -0.05>;
   #break

   #case (11)
      #declare ASTEROID_MESH_NAME = asteroid_known_phobos;
      #declare ASTEROID_PIGMENT_MAP = "maps/asteroid/phobos_cylindrical.jpg";
      #declare CAMERA_LOCATION = <0, 0, -50>;
   #break

   #case (12)
      #declare ASTEROID_MESH_NAME = asteroid_known_toutatis;
      #declare CAMERA_LOCATION = <0, 0, -10>;
   #break

   #case (0)
      #declare CAMERA_LOCATION = <0, 0, -10>;
   #break

   #else
      #declare ASTEROID_KNOWN_NUMBER = 0;
      #declare CAMERA_LOCATION = <0, 0, -10>;
   #break

#end

// -------------------------------
// Camera, Lights, Background
// -------------------------------
camera {
   location  CAMERA_LOCATION
   direction <0, 0, 1>
   up        <0, 1, 0>
   right     x*image_width/image_height
   look_at   <0, 0,  0>
}

//light_source {<10000, 0, 100> color White}
light_source {<1000, 5000, 0> color White}

// Starfield texture by Jim Burton
sphere { <0,0,0>, abs(CAMERA_LOCATION.z) * 10000/3
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
			scale abs(CAMERA_LOCATION.z) * 10000/image_width
		}
	}
	//no_reflection
	//rotate <0.0, 90.0, 0.0>
}


// -------------------------------
// artificial surface
// -------------------------------


#local S = seed(1234);
#local DensityCurve =
spline {
    0/2 <0,0,0>
    1/2 <.5,.15,0>
    2/2 <1,1,0>
};

#local PN =
pigment {
    average
    pigment_map {

       #local I=0;#while(I<256)
           #local ScaleFactor = DensityCurve(rand(S)).y;
           [1
               cylindrical
               scale  .15*ScaleFactor
               #local ScaleFactor =  .5*ScaleFactor;
               poly_wave .8
               pigment_map {
                       [0 rgb   .1]
                       [.1 rgb  10*(1-ScaleFactor)]
                       [.2 rgb -20*(1-ScaleFactor)]
                       [1 rgb  -30*(1-ScaleFactor)]
               }
               rotate <rand(S)*180,rand(S)*180,rand(S)*180>
           ]
       #local I=I+1;#end
    }
};

#declare atexture = texture {
    pigment { rgb .6 }
    normal {
       pigment_pattern {
          average
          pigment_map {
             #local Scl  = 1;
             #local I=0;#while(I<12)
                     [1
                         PN
                         scale Scl
                         rotate <rand(S)*180,rand(S)*180,rand(S)*180>
                     ]
                     #local Scl=Scl*.8;
             #local I=I+1;#end
          }
       }
       bump_size 15
    }   
    finish { ambient 0.25 diffuse 0.95 specular 0.01 } //specular 0.05
}
                    
// -------------------------------//
// Asteroid Object                //
// -------------------------------//

#if (ASTEROID_KNOWN_NUMBER > 0)
   mesh2 { ASTEROID_MESH_NAME
     #ifdef (ASTEROID_PIGMENT_MAP) 
      texture {
            pigment { 
               image_map {jpeg ASTEROID_PIGMENT_MAP map_type 1 once }
            }
            normal {
               bump_map {jpeg ASTEROID_PIGMENT_MAP map_type 1 once }
               bump_size 5.0
            }
         //#else // #undef ASTEROID_PIGMENT_MAP
            //pigment { color Grey }
         //   texture { atexture }
         //#end
         finish { ambient 0.25 diffuse 0.95 specular 0.01} //specular 0.05
      }
     #else // not def ASTEROID_PIGMENT_MAP
       //texture { pigment { color Grey } finish { ambient 0.25 diffuse 0.95 specular 0.01} }
       texture { atexture }
     #end
    //rotate <10,0,60>
   }
#else
  sphere { 0, 2
    texture { atexture }
 }
#end