// ---------------------------------------------------------------------------
// Space3D
// Libre POV-Ray script for space scenes rendering
// Copyright (C) 2005-2019 aka pyramid
// Contact: pyramid@sapo.pt
// Internet: https://openteq.wordpress.com/portfolio/space3d/
// Internet: http://space3d.no.sapo.pt/ (discontinued)
//
// This script is distributed with ABSOLUTELY NO WARRANTY;
// See the GNU General Public License for more details,
// which can be found in LICENSE file or here
// https://www.gnu.org/licenses/gpl-3.0.en.html
// ---------------------------------------------------------------------------
// Persistence of Vision Ray Tracer Scene Description File
// @file    : asteroid_catalog.pov
// @brief   : asteroids catalog
// @version : 2019-04-27
// @created : 2005-12-18
// @author  : pyramid
// @internet: https://openteq.wordpress.com/portfolio/space3d/
// @internet: http://space3d.no.sapo.pt/ (discontinued)
// @scale   : 1 POV unit = 1 km
// ---------------------------------------------------------------------------


//-----------------------------------
// POV-Ray Settings and Includes  
//-----------------------------------

#version 3.6;
//#version 3.7;

#include "colors.inc"
// macros for generating various shapes
#include "shapes.inc"
// random number generation macros
#include "rand.inc"

#include "space3d.inc"

global_settings {
  //assumed_gamma 1.0
   assumed_gamma 2.2
   max_trace_level 10
}

// ----------------------------------------
// User Options
// ----------------------------------------
#declare CAMERA_TYPE = 1; //1=perspective; 2=orthographic
#declare ITERATIONS_PER_PATTERN = 1;
#if (frame_number = 0) 
  // change number to activate an example
  #declare PATTERN_TYPE = 13; // range=1-15
#else
  #declare PATTERN_TYPE = frame_number; //1+int((frame_number-1)/ITERATIONS_PER_PATTERN);
#end
#if (frame_number = 0) 
  // change number to activate an example
  #declare ITERATION_NUMBER = 1;
#else
  #declare ITERATION_NUMBER = frame_number - (PATTERN_TYPE-1)*ITERATIONS_PER_PATTERN;
#end

// ----------------------------------------
// Camera and Lights
// ----------------------------------------

#switch (CAMERA_TYPE)
#case (1)
camera {
  location  <image_width/2, -image_height/2, -image_width*1.25>
  direction z
  right     x*image_width/image_height
  look_at   <image_width/2, -image_height/2,  0.0>
  angle 44
}
#break

#case (2)
camera {
  orthographic
  location  <image_width/2, -image_height/2, -1>
  direction z
  look_at   <image_width/2, -image_height/2,  0>
  right     x*image_width
  up        y*image_height
}
#break
#end // switch

light_source {
  <-image_width*2, image_height*4, -1000>
  color rgb <1, 1, 1>*0.5  // light's color
}

// ----------------------------------------
// Background
// ----------------------------------------

sky_sphere {
  pigment {
    gradient y
    color_map {
      [0.0 rgb <0.0,0.2,0.4>]
      [1.0 rgb <0.0,0.0,0.1>]
    }
  }
  rotate <40,0,30>
}

// -------------------------------//
// Macros
// -------------------------------//
#macro IRand(Min,Max,Stream)
   (int(rand(Stream)*(Max-Min+1)) + Min)
#end

// ----------------------------------------
// Repeat of spheres
// ----------------------------------------

// Initialize
// ----------------------------------------
#declare Columns = 6;
#declare Rows = 5;
#declare Space = 10;
#declare cntRow = 1;
#declare cntCol = 1;
#declare Radius = 0.5 * (image_width - (Columns + 1) * Space)/Columns;
#declare SpaceY = (image_height - Radius* 2 * Rows) / (Rows + 1);
#declare SeedA = seed(1234511 + frame_number + PATTERN_TYPE);

//#declare BaseScale = 20;

#declare PatternTypeText = "No pattern";
#switch (PATTERN_TYPE)
   #case (1) #declare PatternTypeText="Asteroid Shape Type 1"; #break
   #case (2) #declare PatternTypeText="Asteroid Shape Type 2"; #break
   #case (3) #declare PatternTypeText="Asteroid Shape Type 3"; #break
   #case (4) #declare PatternTypeText="Asteroid Shape Type 4"; #break
   #case (5) #declare PatternTypeText="Asteroid Shape Type 5"; #break
   #case (6) #declare PatternTypeText="Asteroid Texture 1"; #break
   #case (7) #declare PatternTypeText="Asteroid Texture 2"; #break
   #case (8) #declare PatternTypeText="Asteroid Texture 3"; #break
   #case (9) #declare PatternTypeText="Asteroid Texture 4"; #break
   #case (10) #declare PatternTypeText="Asteroid Texture 5"; #break
   #case (11) #declare PatternTypeText="Asteroid Crater Type"; #break
   #case (12) #declare PatternTypeText="Asteroid Crater Size"; #break
   #case (13) #declare PatternTypeText="Asteroid Texture 1-5"; #break
   #case (14) #declare PatternTypeText="Asteroid Color Psychadelic"; #break
   #case (15) #declare PatternTypeText="Asteroid Color Realistic"; #break
#end

#switch (PATTERN_TYPE)
   #range (1,5)
      #declare TexResultText = "shape";
   #break
   #range (6,10)
      #declare TexResultText = "shape";
   #break
   #case (11)
      #declare TexResultText = "crater";
   #break
   #case (12)
      #declare TexResultText = "size";
   #break
   #case (13)
      #declare TexResultText = "texture";
   #break
   #range (14,15)
      #declare TexResultText = "color";
   #break
#end

#declare Title = concat(PatternTypeText);
#declare TextTexture = texture {
  pigment { rgb <1.0,1.0,1.0> }
  finish { ambient 0.8 diffuse 0.5 }
}

// Generate
// ----------------------------------------

// title
#declare TitleHeight = 20;
#declare TitleWidth = Text_Width("arial.ttf",Title,TitleHeight,0);
text {
  ttf "arial.ttf", Title,
  0.02, // depth
  0  // spacing
  scale TitleHeight
  texture { TextTexture }
  translate <image_width/2-TitleWidth/2, -image_height*0.06, -Radius>
  no_shadow
}

#while (cntRow <= Rows)

#while (cntCol <= Columns)

   //#declare TexResult = (cntRow-1) * Columns + cntCol;

   //#if (TexResult <= 24)
   #declare xloc = Space + Radius + (Space + Radius*2) * (cntCol-1); 
   #declare yloc = SpaceY + Radius + (SpaceY + Radius*2) * (cntRow-1); 
   #declare Texture_Template = texture { pigment { rgb <1.0, 0.5, 0.8> } }
   #declare TexResult = (cntRow-1) * Columns + cntCol;

   #declare BASE_SIZE = 0.5;
   #declare ASTEROID_TYPE_NUMBER = 1; //IRand(1,4,SeedA);
   #declare ASTEROID_SHAPE_NR = TexResult; //IRand(1,100,SeedA); //cntRow * (Rows-1) + cntCol; //IRand(1,100,SeedA);
   #declare ASTEROID_TEXTURE_NUMBER = 1; //frame_number;
   #declare ASTEROID_CRATER_TYPE = 1;
   #declare asteroid_radius = BASE_SIZE*Radius;
   #declare asteroid_translation = <xloc, -yloc, 10>;
   #declare asteroid_rotation = <0,0,0>;
   #declare CRATERS_NUMBER = 50;
   #declare crater_size = 1*asteroid_radius;   
   #declare show_background = false;
   #declare create_logfile = false;
   #declare asteroid_color = rgb <1,1,1>;

   #switch (PATTERN_TYPE)
      #range (1,5) //shape
         #declare ASTEROID_TYPE_NUMBER = PATTERN_TYPE;
      #break   
      #range (6,10) //texture
         #declare ASTEROID_TYPE_NUMBER = 3;
         //#declare ASTEROID_SHAPE_NR = 5;
         #declare ASTEROID_TEXTURE_NUMBER = PATTERN_TYPE - 5;
      #break   
      #case (11)
         #declare ASTEROID_TYPE_NUMBER = 3;
         #declare ASTEROID_SHAPE_NR = 5;
         #declare ASTEROID_TEXTURE_NUMBER = 2;
         #declare ASTEROID_CRATER_TYPE = TexResult;
      #break   
      #case (12)
         #declare ASTEROID_TYPE_NUMBER = 3;
         #declare ASTEROID_SHAPE_NR = 5;
         #declare ASTEROID_TEXTURE_NUMBER = 2;
         #declare ASTEROID_CRATER_TYPE = 1;
         #declare crater_size = 0.2*asteroid_radius*TexResult;   
      #break   
      #case (13)
         #declare ASTEROID_TYPE_NUMBER = cntRow;
         #declare ASTEROID_TEXTURE_NUMBER = cntRow;
         #declare ASTEROID_CRATER_TYPE = TexResult;
         #declare crater_size = 0.4*asteroid_radius*cntCol;   
      #break   
      #case (14)
         #declare ASTEROID_TYPE_NUMBER = cntRow;
         #declare ASTEROID_TEXTURE_NUMBER = cntRow;
         #declare ASTEROID_CRATER_TYPE = TexResult;
         #declare crater_size = 0.4*asteroid_radius*cntCol;
         #declare asteroid_color = rgb <RRand(0.3,0.6,SeedA),RRand(0.1,0.2,SeedA),RRand(0.0,0.3,SeedA)>;
      #break   
      #case (15)
         #declare ASTEROID_TYPE_NUMBER = cntRow;
         #declare ASTEROID_TEXTURE_NUMBER = cntRow;
         #declare ASTEROID_CRATER_TYPE = TexResult;
         #declare crater_size = 0.4*asteroid_radius*cntCol;
         #switch (cntRow)
            #case (1) //brown
               #declare asteroid_color = rgb <RRand(0.3,0.6,SeedA),RRand(0.1,0.4,SeedA),0.0>;
            #break
            #case (2) //grey
               #declare asteroid_color = rgb <RRand(0.9,1.0,SeedA),RRand(0.9,1.0,SeedA),RRand(0.9,1.0,SeedA)>;
            #break
            #case (3) //light blue
               #declare asteroid_color = rgb <RRand(0.5,0.6,SeedA),RRand(0.6,0.7,SeedA),RRand(0.6,1.0,SeedA)>;
            #break
            #case (4) //very light blue
               #declare asteroid_color = rgb <RRand(0.8,0.9,SeedA),RRand(0.8,0.9,SeedA),RRand(0.9,1.0,SeedA)>;
            #break
         #end
      #break   
   #end
   //#include "asteroid_virtual.inc"
   //#include "include/s3d_asteroid.inc"
   //AsteroidObject(iType, iSurface, fRadius, fCraterSize, cBaseColor, rAsteroid)
   object { AsteroidObject(ASTEROID_TYPE_NUMBER, ASTEROID_TEXTURE_NUMBER, asteroid_radius, crater_size, asteroid_color, SeedA) translate asteroid_translation }


   #switch (PATTERN_TYPE)
      #range (1,12)
         #declare SubscriptText = concat(TexResultText,"=",str(TexResult,0,0));
      #break
      #case (13)
         #declare SubscriptText = concat(TexResultText,"=",str(cntRow,0,0));
      #break
      #range (14,15)
         #declare SubscriptText = concat(TexResultText,"=",vstr(3,asteroid_color,",",0,1));
      #break
   #end
   #declare SubscriptHeight = 12;
   #declare SubscriptWidth = Text_Width("arial.ttf", SubscriptText, SubscriptHeight, 0);
   text {
      ttf "arial.ttf", SubscriptText,
      0.01, // depth
      0  // spacing
      texture { TextTexture }
      scale SubscriptHeight
      translate <xloc - SubscriptWidth/2, -image_height*cntRow/Rows + SubscriptHeight*image_height*6e-4*cntRow, -Radius>
      no_shadow
   }

   //#end

// end of loop
#declare cntCol = cntCol + 1;
#end //while col

#declare cntRow = cntRow + 1;
#declare cntCol = 1;
#end //while row

// eof
