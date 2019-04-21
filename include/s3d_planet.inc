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
// File       : s3d_planet.inc
// Description: Planet from space with weather, atmosphere, and simple background
// Version    : 0.50
// Date       : 2012-07-02
// Author     : Pyramid
// Scale      : 1 POV Unit = 1km
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// Planet maps taken from
// http://www.jht.cjb.net/
// Planet info
// planetary factsheet http://nssdc.gsfc.nasa.gov/planetary/factsheet/
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// MACROS
//  Atmosphere(fBaseRadius, fAtmosphereFactor cAtmosphereColor)
//  Planet(fPlanetRadius, sTextureMap, sBumpMap)
//  GasGiant(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanetSeed)
//  DirtPlanet(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanetSeed)
//  TerranPlanet(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aPlanetSeedNumbers)
//  TrantorPlanet(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aPlanetSeedNumbers)
//  QuickPlanet(fPlanetRadius)
//
// PARAMETERS
//  For any XXXPlanet(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanetSeed)
//  - fPlanetRadius: planet radius
//  - aBaseColors: color array for base colors
//  - fColorDev: amount of color deviation 0-255
//  - bMonoColor: mono color deviation or change color?
//  - rPlanetSeed: seed for randomization
//  - aSeedNumbers: integer array[7] of seednumbers for shape, tetxure, color, 
//
// OBJECTS
//  GasGiant1   - replaces surface_type = 4
//  GasGiant2   - replaces surface_type = 5
//  GasGiant3   - replaces surface_type = 6
//  GasGiant4   - replaces surface_type = 7
//  DirtPlanet1 - replaces surface_type = 9
//  DirtPlanet2 - replaces surface_type = 11
//  DirtPlanet3 - replaces surface_type = 12
//  DirtPlanet4 - replaces surface_type = 13
//  DirtPlanet5 - replaces surface_type = 14
//  DirtPlanet6 - replaces surface_type = 15
//  DirtPlanet7 - replaces surface_type = 16
//  DirtPlanet8 - replaces surface_type = 17
//  DirtPlanet9 - replaces surface_type = 18
//  TerranPlanet1
//  TerranPlanet2
//  TerranPlanet3
//  TerranPlanet4 - replaces surface_type = 8
//  TerranPlanet5 - replaces surface_type = 10
//  TerranPlanet6 - replaces surface_type = 19
//  TerranPlanet7 - replaces surface_type = 20
//  TerranPlanet8 - replaces surface_type = 21
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
// Global Settings
// ---------------------------------------------------------------------------------------
#version 3.6;

// ---------------------------------------------------------------------------------------
// Include Files
// ---------------------------------------------------------------------------------------
#include "rand.inc" // random number generation macros
#include "math.inc" // math function macros

// ---------------------------------------------------------------------------------------
// User Settings
// ---------------------------------------------------------------------------------------
// Declare default values

#if (create_logfile)
  #if (defined(LogFile)=false)
    #fopen LogFile "gallery/planet.log"
    #if(frame_number<=1) write
    #else append
    #end
  #end
  #write(LogFile,"\n[Frame_",frame_number,"]\n")
#end

// ---------------------------------------------------------------------------------------
// Quick Planet
// ---------------------------------------------------------------------------------------

//Simple terran planet
#macro QuickPlanet(fPlanetRadius)
  #declare rPlanet = seed(frame_number);
  sphere {<0, 0, 0>, fPlanetRadius
    texture { pigment { bozo
      color_map {
         [0.000 colour rgb <0.0, 0.0, 1.0>   ] // ocean begin
         [0.500 colour rgb <0.0, 0.0, 0.67>  ] // ocean end
         [0.510 colour rgb <0.62, 0.50, 0.4> ] // land outline
         [0.511 colour rgb <0.10, 0.30, 0.0> ] // green land begin
         [0.550 colour rgb <0.09, 0.20, 0.0> ]
         [0.600 colour rgb <0.08, 0.19, 0.0> ]
         [0.650 colour rgb <0.10, 0.21, 0.0> ]
         [0.700 colour rgb <0.15, 0.22, 0.0> ]
         [0.750 colour rgb <0.12, 0.40, 0.0> ]
         [0.800 colour rgb <0.16, 0.25, 0.0> ]
         [0.850 colour rgb <0.15, 0.20, 0.0> ]
         [0.900 colour rgb <0.14, 0.16, 0.0> ]
         [0.950 colour rgb <0.12, 0.05, 0.0> ]
         [1.000 colour rgb <0.10, 0.20, 0.0> ]
      }
      turbulence RRand(2,3,rPlanet)
      omega RRand(0.4,0.65,rPlanet)
      lambda RRand(2,4,rPlanet)
      scale fPlanetRadius
    } }
    finish { surface_finish }
    hollow on
    no_reflection
  }
#end

// ---------------------------------------------------------------------------------------
// Terran Planets
// ---------------------------------------------------------------------------------------
// implements TerranPlanet(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aPlanetSeedNumbers)
// and TerranPlanet1-9 objects 
#include "include/s3d_planet_terran.inc"

// ---------------------------------------------------------------------------------------
// Trantor Planet
// ---------------------------------------------------------------------------------------
// implements TrantorPlanet(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aPlanetSeedNumbers)
#include "include/s3d_planet_trantor.inc"

// ---------------------------------------------------------------------------------------
// Gas Giants
// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 4
#macro GasGiant1(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)

  #declare T_PlanetSurface = texture { pigment { gradient -y
    #local fOctaves = RRand (1, 3, rPlanet); 
    #local fTurb    = RRand (0.005, 0.010, rPlanet); 
    #local fOmega   = RRand (0.2, 0.5, rPlanet); 
    #local fLambda  = RRand (0.0, 2.0, rPlanet); 

    noise_generator IRand(0,3,rPlanet)
    turbulence fTurb
    octaves fOctaves
    lambda fLambda
    omega fOmega

    #local ramp_method = IRand(1,6,rPlanet);
    #switch (ramp_method)
      #case (1) ramp_wave     #break
      #case (2) triangle_wave #break
      #case (3) sine_wave     #break
      #case (4) scallop_wave  #break
      #case (5) cubic_wave    #break
      #case (6) poly_wave RRand(0.1, 5.0, rPlanet) 
      #else     ramp_wave
    #end
    color_map {
      [0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ] // top pole
      #local fStep = 1/IRand(4,100,rPlanet);
      #local I=0; #while(I<=1) // start loop
        [I VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
      #local I=I+fStep; #end            
      [1 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ] // bottom pole
      } scale <0.2,2,0.2>*fPlanetRadius translate fPlanetRadius*y
    }
  }

  sphere {<0, 0, 0>, fPlanetRadius
    texture { T_PlanetSurface }
    finish { surface_finish }
    hollow on
    no_reflection
  }

#end //gas giant macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 5
#macro GasGiant2(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)

  #declare planet_surface = texture { pigment { gradient y
    noise_generator 2
    #local fTurb    = RRand (0.005, 0.010, rPlanet); 
    #local fOctaves = RRand (1, 2, rPlanet); 
    #local fOmega   = RRand (0.3, 0.5, rPlanet); 
    #local fLambda  = RRand (0.0, 2.0, rPlanet); 
    #local fFreq    = RRand(1.0, 2.0, rPlanet); 

    noise_generator IRand(0,3,rPlanet)
    turbulence fTurb
    octaves fOctaves
    lambda fLambda
    omega fOmega
    frequency fFreq

    #local ramp_method = IRand(1,6,rPlanet);
    #switch (ramp_method)
      #case (1) ramp_wave     #break
      #case (2) triangle_wave #break
      #case (3) sine_wave     #break
      #case (4) scallop_wave  #break
      #case (5) cubic_wave    #break
      #case (6) poly_wave RRand(0.1, 5.0, rPlanet) //0.1-5.0 
                              #break
      #else     ramp_wave
    #end

    color_map {
      #local I=0; #while(I<=1.0) // start loop            
        [I VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
      #local I=I+RRand(0.01,0.05,rPlanet); #end // end loop
      } scale <0.2,2,0.2>*fPlanetRadius translate fPlanetRadius*y

    //storms
    #local loop_max = IRand(100,500,rPlanet);
    #declare DensityCurve = spline { 0.0 <0,0.05,0> 0.8 <0,0.10,0> 1.0 <0,0.3,0> };
    #local I=0; #while(I<=loop_max) // start loop            
      warp { black_hole VRand_On_Sphere(rPlanet)*fPlanetRadius,
        DensityCurve(rand(rPlanet)).y*fPlanetRadius
        falloff RRand(1.5,7.5,rPlanet)
        strength RRand(1.2,2.2,rPlanet)
        turbulence RRand(0.0,0.5,rPlanet)
        inverse
      }
    #local I=I+1; #end // end loop
    }
    finish { surface_finish }
  }
  sphere {<0, 0, 0>, fPlanetRadius
    texture { planet_surface }
    finish { surface_finish }
    hollow on
    no_reflection
  }
#end //gas giant macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 6
#macro GasGiant3(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)

  #declare planet_surface = texture { pigment { gradient y
    noise_generator IRand(0,3,rPlanet)

    #local fTurb    = RRand (0.005, 0.010, rPlanet); 
    #local fOctaves = RRand (1, 2, rPlanet); 
    #local fLambda  = RRand (0.0, 2.0, rPlanet); 
    #local fOmega   = RRand (0.3, 0.5, rPlanet); 
    #local fFreq    = RRand(1.0, 2.0, rPlanet); 

    turbulence fTurb
    octaves fOctaves
    lambda fLambda
    omega fOmega
    frequency fFreq

    #local ramp_method = IRand(1,6,rPlanet);
    #switch (ramp_method)
      #case (1) ramp_wave     #break
      #case (2) triangle_wave #break
      #case (3) sine_wave     #break
      #case (4) scallop_wave  #break
      #case (5) cubic_wave    #break
      #case (6) poly_wave RRand(0.1, 5.0, rPlanet) 
      #else     ramp_wave
    #end

    pigment_map {
      #local I=0; #while(I<=1.0) // start loop            
        [I agate pigment_map {
            #local J=0.5; #while(J<=1.0) // start loop
              [J VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
            #local J=J+RRand(0.01,0.05,rPlanet); #end // end loop
          }
          turbulence RRand(0.0,2.0,rPlanet)
          scale <RRand(0.01,0.10,rPlanet),RRand(0.01,0.1,rPlanet),RRand(0.01,0.1,rPlanet)>
        ]
      #local I=I+RRand(0.01,0.10,rPlanet); #end // end loop
    } scale <1,2,1>*fPlanetRadius translate fPlanetRadius*y

    // larger storms
    #local loop_max = IRand(200,1000,rPlanet);
    #declare DensityCurve = spline { 0.0 <0,0.05,0> 0.9 <0,0.10,0> 1.0 <0,0.3,0> };
    #local I=0; #while(I<=loop_max) // start loop            
      warp { black_hole VRand_On_Sphere(rPlanet)*fPlanetRadius,
        DensityCurve(rand(rPlanet)).y*fPlanetRadius
        falloff RRand(1.5,7.5,rPlanet)
        strength RRand(1.2,2.2,rPlanet)
        turbulence RRand(0.0,0.5,rPlanet)
        inverse }
    #local I=I+1; #end // end loop

    // smaller storms
    #local loop_max = IRand(500,10000,rPlanet);
    #declare DensityCurve = spline { 0.0 <0,0.01,0> 0.5 <0,0.03,0> 1.0 <0,0.05,0> };
    #local I=0; #while(I<=loop_max) // start loop            
      warp { black_hole VRand_On_Sphere(rPlanet)*fPlanetRadius,
        DensityCurve(rand(rPlanet)).y*fPlanetRadius
        falloff RRand(1.5,7.5,rPlanet)
        strength RRand(1.2,2.2,rPlanet)
        turbulence RRand(0.0,0.5,rPlanet)
        inverse }
    #local I=I+1; #end // end loop

    }
    finish { surface_finish }
  }

  sphere {<0, 0, 0>, fPlanetRadius
    texture { planet_surface }
    finish { surface_finish }
    hollow on
    no_reflection
  }

#end //gas giant macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 7
#macro GasGiant4(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)

  #declare planet_surface = texture { pigment { gradient y
      noise_generator IRand(0,3,rPlanet)
    
      #local fTurb    = RRand (0.005, 0.010, rPlanet); 
      #local fOctaves = RRand (1, 3, rPlanet); 
      #local fLambda  = RRand (0.0, 2.0, rPlanet); 
      #local fOmega   = RRand (0.1, 0.7, rPlanet); 
      #local fFreq    = RRand(1.0, 2.0, rPlanet); 
  
      turbulence fTurb
      octaves fOctaves
      lambda fLambda
      omega fOmega
      frequency fFreq

      #local ramp_method = IRand(1,6,rPlanet);
      #switch (ramp_method)
        #case (1) ramp_wave     #break
        #case (2) triangle_wave #break
        #case (3) sine_wave     #break
        #case (4) scallop_wave  #break
        #case (5) cubic_wave    #break
        #case (6) poly_wave RRand(0.1, 5.0, rPlanet) 
                                #break
        #else     ramp_wave
      #end
  
      #local luma_factor = RRand(0.5,1.0,rPlanet);
      #local cloud_turbulence = RRand(1.0,2.0,rPlanet);
      pigment_map {
        #local I=0; #while(I<=1.0) // start loop            
          [I wrinkles pigment_map {
               [0.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
               #local J=RRand(0.5,0.9,rPlanet); #while(J<=1.0) // start loop
                  [J bozo pigment_map {
                      [0.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
                      #local K=RRand(0.5,0.9,rPlanet); #while(K<=1.0) // start loop
                      #local lightness = K*3;            
                         [K VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
                      #local K=K+RRand(0.01,0.02,rPlanet); #end // end loop
                    }
                    turbulence RRand(1.0,3.0,rPlanet)
                  ]
               #local J=J+0.05;
               #end // end loop
            }
          #local cloud_turbulence = cloud_turbulence + RRand(-0.2,0.2,rPlanet);
          turbulence cloud_turbulence
          scale <RRand(0.05,0.1,rPlanet),RRand(0.01,0.05,rPlanet),RRand(0.05,0.1,rPlanet)>
        ]
        #local I=I+RRand(0.05,0.20,rPlanet); #end // end loop
      } scale <1,2,1>*fPlanetRadius translate fPlanetRadius*y

      // larger storms
      #local loop_max = IRand(10,500,rPlanet);
      #declare DensityCurve = spline { 0.0 <0,0.05,0> 0.9 <0,0.07,0> 1.0 <0,0.10,0> };
      #local I=0; #while(I<=loop_max) // start loop            
        warp { black_hole VRand_On_Sphere(rPlanet)*fPlanetRadius,
               DensityCurve(rand(rPlanet)).y*fPlanetRadius
               falloff RRand(1.5,7.5,rPlanet)
               strength RRand(1.2,2.2,rPlanet)
               turbulence RRand(0.0,0.5,rPlanet)
               inverse }
      #local I=I+1; #end // end loop

      // smaller storms
      #local loop_max = IRand(500,10000,rPlanet);
      #declare DensityCurve = spline { 0.0 <0,0.01,0> 0.5 <0,0.03,0> 1.0 <0,0.05,0> };
      #local I=0; #while(I<=loop_max) // start loop            
        warp { black_hole VRand_On_Sphere(rPlanet)*fPlanetRadius,
               DensityCurve(rand(rPlanet)).y*fPlanetRadius
               falloff RRand(1.5,7.5,rPlanet)
               strength RRand(1.2,2.2,rPlanet)
               turbulence RRand(0.0,0.5,rPlanet)
               inverse }
      #local I=I+1; #end // end loop
    }
    finish { surface_finish }
  }

  sphere {<0, 0, 0>, fPlanetRadius
    texture { planet_surface }
    finish { surface_finish }
    hollow on
    no_reflection
  }

#end //gas giant macro

#macro GasGiant(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)
  #declare iType = IRand(1,4,rPlanet);
  #switch (iType)
    #case (1) GasGiant1(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet) #break    
    #case (2) GasGiant2(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet) #break    
    #case (3) GasGiant3(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet) #break    
    #case (4) GasGiant4(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet) #break    
  #end
#end

// ---------------------------------------------------------------------------------------
// Dirt Planets
// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 9
#macro DirtPlanet1(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)

  #declare FineDetail_01 = texture { pigment { bumps
    turbulence RRand(1.0, 1.5, rPlanet)
    lambda RRand(2.0,10.0,rPlanet) // controls graininess
    omega RRand(0.5,1.0,rPlanet) // controls finness complexity
    color_map {
      [0.0 transmit 1 ]
      [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
    } }
    scale 0.02*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }

  // soft detail
  #declare FineDetail_02 = texture { pigment { bozo
    turbulence RRand(1.0, 1.5, rPlanet)
    lambda RRand(1.0,3.0,rPlanet) // controls graininess
    omega RRand(0.5,1.0,rPlanet) // controls fineness complexity
    color_map {
      [0.0 transmit 1 ]
      [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
    } }
    scale 0.06*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }

  #declare FineDetail_03 = texture { pigment { dents
    turbulence RRand(1.0, 1.5, rPlanet)
    lambda RRand(2.0,5.0,rPlanet) // controls graininess
    omega RRand(0.2,0.6,rPlanet) // controls fineness complexity
    color_map {
      [0.0 transmit 1 ]
      [0.9 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
    } }
    scale 0.06*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }

  //desert like surface
  #declare FineDetail_04 = texture { pigment { granite
    turbulence RRand(0.5, 0.75, rPlanet)
    lambda RRand(2.0,5.0,rPlanet) // controls graininess
    omega RRand(0.1,0.6,rPlanet) // controls fineness complexity
    color_map {
      [0.0 transmit 1 ]
      [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
    } }
    scale 0.50*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }

  #declare FineDetail_06 = texture { pigment { spotted
    turbulence RRand(0.3, 0.5, rPlanet)
    phase RRand(0.0,1.0,rPlanet) //alternatively don't use
    lambda RRand(2.0,5.0,rPlanet) // controls graininess
    omega RRand(0.2,1.3,rPlanet) // controls fineness complexity
    color_map {
      [0.0 transmit 1 ]
      [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
    } }
    scale 0.10*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }

  // could be a mountain range
  #declare FineDetail_07 = texture { pigment { wrinkles
    turbulence RRand(0.10, 0.15, rPlanet)
    phase RRand(0.0,1.0,rPlanet)
    lambda RRand(2.0,10.0,rPlanet)
    omega RRand(0.0,1.5,rPlanet)
    color_map {
      [0.5 transmit 1 ]
      [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
    } }
    scale 0.60*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }

  //some strange surface
  #declare FineDetail_08 = texture { pigment { wrinkles
    turbulence RRand(1.1,2.25,rPlanet)
    lambda RRand(2.0,5.0,rPlanet)
    omega RRand(0.3,0.9,rPlanet)
    color_map {
      [0.0 transmit 1 ]
      [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
    } }
    scale 0.20*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }

  // macro detail structures
  #declare FineDetail_09 = texture { pigment { waves
    turbulence RRand(10, 16.5, rPlanet)
    phase RRand(0.0,0.4,rPlanet)
    lambda RRand(2.0,5.0,rPlanet) // controls graininess
    omega RRand(0.2,0.6,rPlanet) // controls fineness complexity
    color_map {
      [0.0 transmit 1 ]
      [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
    } }
    scale 2.02*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }

  //create random surface
  #declare incl_detail= array[14];
  #declare incl_detail[0] = 1; //always show  base
  #declare incl_detail[9] = IRand(0,1,rPlanet);
  #declare incl_detail[7] = IRand(0,1,rPlanet);
  #declare incl_detail[6] = IRand(0,1,rPlanet);
  #declare incl_detail[2] = IRand(0,1,rPlanet);
  #declare incl_detail[1] = IRand(0,1,rPlanet);
  #declare incl_detail[4] = IRand(0,1,rPlanet);
  #declare incl_detail[3] = IRand(0,1,rPlanet);
  #declare incl_detail[8] = IRand(0,1,rPlanet);

  sphere {<0, 0, 0>, fPlanetRadius
    // create the texture
    #local detail_num=0;
    #if (incl_detail[detail_num]=1)
       texture { pigment { cBaseColor } }
    #end
    #local detail_num=9;
    #if (incl_detail[detail_num]=1)
       texture { FineDetail_09 } // marble stripes > 1st place
    #end
    #local detail_num=7;
    #if (incl_detail[detail_num]=1)
       texture { FineDetail_07 } //mountain range > low pos
    #end
    #local detail_num=6;
    #if (incl_detail[detail_num]=1)
       texture { FineDetail_06 } // large elevation bumps
    #end
    #local detail_num=2;
    #if (incl_detail[detail_num]=1)
       texture { FineDetail_02 } // thick small clouds
    #end
    #local detail_num=1;
    #if (incl_detail[detail_num]=1)
       texture { FineDetail_01 } //very fine > change in position to achieve effect
    #end
    #local detail_num=4;
    #if (incl_detail[detail_num]=1)
       texture { FineDetail_04 } // large smudges > use sparsely
    #end
    #local detail_num=3;
    #if (incl_detail[detail_num]=1)
       texture { FineDetail_03 } // small foggy spots
    #end
    #local detail_num=8;
    #if (incl_detail[detail_num]=1)
       texture { FineDetail_08 } // large cloudy distribution
    #end
    finish { surface_finish }
    hollow on
    no_reflection
  }
#end //dirt planet macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 11
#macro DirtPlanet2(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)

  //#declare surface_finish = finish { ambient 0.0 diffuse 1.0 }

  #declare turb_dev = RRand(1.0, 1.5, rPlanet);
  
  // macro detail structures
  #declare edge = 0.0;
  #declare Structure_01 = texture { pigment { bozo
       #declare fTurbulence = 6.1*turb_dev;
       #declare fPhase = 0;
       #declare fLambda = RRand(2.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.35,0.60,rPlanet); // controls fineness complexity
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
     }
     scale 2.02*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
   }
  
  // macro detail structures
  #declare edge = 0.8;
  #declare Structure_02 = texture { pigment { waves
       #declare fTurbulence = 10.5*turb_dev;
       #declare fPhase = RRand(0.1,0.4,rPlanet)*turb_dev;
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.35,0.60,rPlanet); // controls fineness complexity
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
    }
    scale 2.02*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }

  // create the texture
  #declare incl_detail= array[14];
  #declare incl_detail[0] = 1; //IRand(0,1,SeedA); //always show  base
  #declare incl_detail[1] = 1; //IRand(0,1,SeedA);
  #declare incl_detail[2] = 1; //IRand(0,1,SeedA);
  #macro mPlanetSurface()
    #local detail_num=0; #if (incl_detail[detail_num]=1)
       texture { pigment { cBaseColor } }
    #end
    #local detail_num=1; #if (incl_detail[detail_num]=1)
       texture { Structure_01 }
    #end
    #local detail_num=2; #if (incl_detail[detail_num]=1)
       texture { Structure_02 }
    #end
  #end // planet_surface_texture

  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    finish { surface_finish }
    hollow on
    no_reflection
  }
#end //dirt planet macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 12
#macro DirtPlanet3(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)

  #declare surface_finish = finish { ambient 0.0 diffuse 1.0 }
  //*** vegastrike rocky planet texture ***
  #declare turb_dev = RRand(1.0, 1.5, rPlanet);
  
  #declare edge = 0.0;
  #declare Structure_01 = texture {
     pigment { bozo
       #declare fTurbulence = 6.1*turb_dev;
       #declare fPhase = 0; //RRand(0.0,0.4,rPlanet)*turb_dev;
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.40,0.60,rPlanet); // controls fineness complexity
       #declare fScale = RRand(1.0,5.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
   }
  
  #declare edge = 0.0;
  #declare Structure_02 = texture {
     pigment { dents
       #declare fTurbulence = 6.1*turb_dev;
       #declare fPhase = 0; //RRand(0.0,0.4,rPlanet)*turb_dev;
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
       #declare fScale = RRand(1.0,10.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
   }
  #if (create_logfile)
    #write(LogFile,"base_color_component = ",base_color_component,"\n")
    #write(LogFile,"surface_color_deviation = ",surface_color_deviation,"\n")
    #write(LogFile,"color_factor = ",color_factor,"\n")
  #end
  
  #declare edge = 0.8;
  #declare Structure_03 = texture {
    pigment { wrinkles
       #declare fTurbulence = 5.5*turb_dev;
       #declare fPhase = RRand(0.1,0.4,rPlanet)*turb_dev;
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.40,0.55,rPlanet); // controls fineness complexity
       #declare fScale = RRand(1.0,5.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
    }
    scale fScale*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }
  
 #declare edge = 0.8;
  #declare Structure_04 = texture {
    pigment { waves
       #declare fTurbulence = 10.5*turb_dev;
       #declare fPhase = RRand(0.2,0.8,rPlanet);
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.45,0.65,rPlanet); // controls fineness complexity
       #declare fScale = RRand(1.0,10.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
    }
    scale fScale*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }
  // create the planet_surface texture
  #declare incl_detail= array[5];
  #declare incl_detail[0] = 1; //IRand(0,1,SeedA); //always show  base
  #declare incl_detail[1] = 1;
  #declare incl_detail[2] = 1;
  #declare incl_detail[3] = 1;
  #declare incl_detail[4] = 1;
  #macro mPlanetSurface()
    #local detail_num=0; #if (incl_detail[detail_num]=1)
      texture { pigment { cBaseColor } }
    #end
    #local detail_num=1; #if (incl_detail[detail_num]=1) texture { Structure_01 } #end
    #local detail_num=2; #if (incl_detail[detail_num]=1) texture { Structure_02 } #end
    #local detail_num=3; #if (incl_detail[detail_num]=1) texture { Structure_03 } #end
    #local detail_num=4; #if (incl_detail[detail_num]=1) texture { Structure_04 } #end
  #end // planet_surface texture

  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    finish { surface_finish }
    hollow on
    no_reflection
  }
#end //dirt planet macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 13
#macro DirtPlanet4(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)

  #declare surface_finish = finish { ambient 0.0 diffuse 1.0 }

  //*** vegastrike rocky planet texture ***
  #declare turb_dev = RRand(1.0, 1.5, rPlanet);
  
  #declare edge = 0.0;
  #declare Structure_01 = texture {
     pigment { bozo
       #declare fTurbulence = 6.1*turb_dev;
       #declare fPhase = 0;
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.40,0.60,rPlanet); // controls fineness complexity
       #declare fScale = RRand(1.0,5.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
   }
  
  #declare edge = 0.0;
  #declare Structure_02 = texture {
     pigment { dents
       #declare fTurbulence = 6.1*turb_dev;
       #declare fPhase = 0;
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
       #declare fScale = RRand(1.0,10.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
   }
  
  #declare edge = 0.8;
  #declare Structure_03 = texture {
    pigment { wrinkles
       #declare fTurbulence = 5.5*turb_dev;
       #declare fPhase = RRand(0.1,0.4,rPlanet)*turb_dev;
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.40,0.55,rPlanet); // controls fineness complexity
       #declare fScale = RRand(1.0,5.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
    }
    scale fScale*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }
  
  #declare edge = 0.8;
  #declare Structure_04 = texture {
    pigment { waves
       #declare fTurbulence = 10.5*turb_dev;
       #declare fPhase = RRand(0.2,0.8,rPlanet);
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.45,0.65,rPlanet); // controls fineness complexity
       #declare fScale = RRand(1.0,10.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
    }
    scale fScale*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }
  
  #declare Structure_05 = texture {
    pigment { agate
       #declare fEdge = RRand(0.10,0.70,rPlanet);
       #declare fTurbulence = RRand(2.0,5.0,rPlanet);
       #declare fPhase = RRand(0.0,1.0,rPlanet);
       #declare fLambda = RRand(2.8,4.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
       #declare fScale = RRand(1.0,10.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [fEdge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
    }
    scale fScale*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }
  
  // create the planet_surface texture
  #declare incl_detail= array[10];
  #declare incl_detail[0] = 1; //always show  base
  #declare incl_detail[1] = 1;
  #declare incl_detail[2] = 1;
  #declare incl_detail[3] = 1;
  #declare incl_detail[4] = 1;
  #declare incl_detail[5] = 1;
  #macro mPlanetSurface()
    #local detail_num=0; #if (incl_detail[detail_num]=1)
      texture { pigment { cBaseColor } }
    #end
    #local detail_num=1; #if (incl_detail[detail_num]=1) texture { Structure_01 } #end
    #local detail_num=2; #if (incl_detail[detail_num]=1) texture { Structure_02 } #end
    #local detail_num=3; #if (incl_detail[detail_num]=1) texture { Structure_03 } #end
    #local detail_num=4; #if (incl_detail[detail_num]=1) texture { Structure_04 } #end
    #local detail_num=5; #if (incl_detail[detail_num]=1) texture { Structure_05 } #end
  #end // planet_surface texture

  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    finish { surface_finish }
    hollow on
    no_reflection
  }
#end //dirt planet macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 14
#macro DirtPlanet5(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)

  #declare surface_finish = finish { ambient 0.0 diffuse 1.0 }

  //*** vegastrike waterlava planet texture ***
  #declare turb_dev = RRand(1.0, 1.5, rPlanet);
  
  #declare edge = 0.0;
  #declare Structure_01 = texture {
     pigment { bozo
       #declare fTurbulence = 6.1*turb_dev;
       #declare fPhase = 0;
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.40,0.60,rPlanet); // controls fineness complexity
       #declare fScale = RRand(1.0,5.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
   }
  
  #declare edge = 0.0;
  #declare Structure_02 = texture {
     pigment { dents
       #declare fTurbulence = 6.1*turb_dev;
       #declare fPhase = 0;
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
       #declare fScale = RRand(1.0,10.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
   }
  
  #declare edge = 0.8;
  #declare Structure_03 = texture {
    pigment { wrinkles
       #declare fTurbulence = 5.5*turb_dev;
       #declare fPhase = RRand(0.1,0.4,rPlanet);
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.40,0.55,rPlanet); // controls fineness complexity
       #declare fScale = RRand(2.0,5.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
    }
    scale fScale*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }
  
  #declare edge = 0.8;
  #declare Structure_04 = texture {
    pigment { waves
       #declare fTurbulence = 10.5*turb_dev;
       #declare fPhase = RRand(0.2,0.8,rPlanet);
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.45,0.65,rPlanet); // controls fineness complexity
       #declare fScale = RRand(1.0,10.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [edge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
    }
    scale fScale*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }
  
  #declare Structure_05 = texture {
    pigment { agate
       #declare fEdge = RRand(0.10,0.70,rPlanet);
       #declare fTurbulence = RRand(2.0,5.0,rPlanet);
       #declare fPhase = RRand(0.0,1.0,rPlanet);
       #declare fLambda = RRand(2.8,4.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
       #declare fScale = RRand(1.0,10.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map {
          [0.0 transmit 1 ] [fEdge transmit 1 ]
          [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ]
       }
    }
    scale fScale*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }
  
  #declare Structure_06 = texture {
    pigment { waves
       #declare fEdge = RRand(0.10,0.70,rPlanet);
       #declare fTurbulence = RRand(2.0,9.0,rPlanet);
       #declare fPhase = RRand(0.2,0.8,rPlanet);
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.45,0.55,rPlanet); // controls fineness complexity
       #declare fScale = RRand(2.0,5.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
       color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 cBaseColor ] }
    }
    scale fScale*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
    finish { surface_finish }
  }

  // create the planet_surface texture
  #declare incl_detail= array[10];
  #declare incl_detail[0] = 1; //always show  base
  #declare incl_detail[1] = 1;
  #declare incl_detail[2] = 1;
  #declare incl_detail[3] = 0; // needs improvement
  #declare incl_detail[4] = 1;
  #declare incl_detail[5] = 1; // sometimes too grainy
  #declare incl_detail[6] = 1;
  #macro mPlanetSurface()
    #local detail_num=0; #if (incl_detail[detail_num]=1)
      texture { pigment { cBaseColor } }
    #end
    #local detail_num=1; #if (incl_detail[detail_num]=1) texture { Structure_01 } #end
    #local detail_num=2; #if (incl_detail[detail_num]=1) texture { Structure_02 } #end
    #local detail_num=3; #if (incl_detail[detail_num]=1) texture { Structure_03 } #end
    #local detail_num=4; #if (incl_detail[detail_num]=1) texture { Structure_04 } #end
    #local detail_num=5; #if (incl_detail[detail_num]=1) texture { Structure_05 } #end
    #local detail_num=6; #if (incl_detail[detail_num]=1) texture { Structure_06 } #end
  #end // planet_surface texture

  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    finish { surface_finish }
    hollow on
    no_reflection
  }
#end //dirt planet macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 15
//*** vegastrike n_class planet texture ***
#macro DirtPlanet6(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)

  #declare surface_finish = finish { ambient 0.0 diffuse 1.0 }
  #declare turb_dev = RRand(1.0, 1.1, rPlanet);

  #declare Structure_01 = texture {
        pigment { bozo
        #declare fEdge = 0.0; //RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = 6.1*turb_dev;
        #declare fPhase = 0; //RRand(0.0,0.4,rPlanet)*turb_dev;
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.40,0.60,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,5.0,rPlanet);
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
     }
  
  #declare Structure_02 = texture {
        pigment { dents
        #declare fEdge = 0.0; //RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = 6.1*turb_dev;
        #declare fPhase = 0; //RRand(0.0,0.4,rPlanet)*turb_dev;
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,10.0,rPlanet);
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ] }
        }
        scale fScale*fPlanetRadius
        rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
        finish { surface_finish }
     }
  
  #declare edge = 0.8;
  #declare Structure_03 = texture {
     pigment { wrinkles
        #declare fEdge = 0.8; //RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = 5.5*turb_dev;
        #declare fPhase = RRand(0.1,0.4,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.40,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,5.0,rPlanet);
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare Structure_04 = texture {
     pigment { waves
        #declare fEdge = 0.8; //RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = 10.5*turb_dev;
        #declare fPhase = RRand(0.2,0.8,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.65,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,10.0,rPlanet);
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare Structure_05 = texture {
     pigment { agate
        #declare fEdge = RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,5.0,rPlanet);
        #declare fPhase = RRand(0.0,1.0,rPlanet);
        #declare fLambda = RRand(2.8,4.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,10.0,rPlanet);
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare Structure_06 = texture {
     pigment { waves
        #declare fEdge = RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,9.0,rPlanet);
        #declare fPhase = RRand(0.2,0.8,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,5.0,rPlanet);
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare Structure_07 = texture {
     pigment { granite
        #declare fEdge = RRand(0.00,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,3.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(4.0,6.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(20.0,50.0,rPlanet);
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) ] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  // create the planet_surface texture
  #declare incl_detail= array[10];
  #declare incl_detail[0] = 1; //IRand(0,1,SeedA); //always show  base
  #declare incl_detail[1] = 1;
  #declare incl_detail[2] = 1;
  #declare incl_detail[3] = 0; // needs improvement
  #declare incl_detail[4] = 1;
  #declare incl_detail[5] = 0; // sometimes too grainy
  #declare incl_detail[6] = 1;
  #declare incl_detail[7] = 1;
  
  #macro mPlanetSurface()
    #local detail_num=0; #if (incl_detail[detail_num]=1)
     texture { pigment { cBaseColor } }
    #end
    #local detail_num=7; #if (incl_detail[detail_num]=1) texture { Structure_07 } #end
    #local detail_num=1; #if (incl_detail[detail_num]=1) texture { Structure_01 } #end
    #local detail_num=2; #if (incl_detail[detail_num]=1) texture { Structure_02 } #end
    #local detail_num=3; #if (incl_detail[detail_num]=1) texture { Structure_03 } #end
    #local detail_num=4; #if (incl_detail[detail_num]=1) texture { Structure_04 } #end
    #local detail_num=5; #if (incl_detail[detail_num]=1) texture { Structure_05 } #end
    #local detail_num=6; #if (incl_detail[detail_num]=1) texture { Structure_06 } #end
  #end // planet_surface texture

  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    finish { surface_finish }
    hollow on
    no_reflection
  }
#end //dirt planet macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 16
//*** vegastrike tkirsa planet texture ***
#macro DirtPlanet7(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)

  #declare surface_finish = finish { ambient 0.0 diffuse 1.0 }
  #declare turb_dev = RRand(1.0, 1.1, rPlanet);
  #declare transparency_global = RRand(0.5,0.9,rPlanet);
  #declare transparency_local_on = IRand(0,1,rPlanet);
  #declare transparency_local_min = 0.2;
  #declare transparency_local_max = 0.95;

  #declare iSurfaceTextures = 7;
  #declare SurfaceTexture = array[iSurfaceTextures+1];
  
  #declare SurfaceTexture[1] = texture {
        pigment { bozo
        #declare fEdge = 0.0;
        #declare fTurbulence = 6.1*turb_dev;
        #declare fPhase = 0;
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.40,0.60,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,5.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[2] = texture {
        pigment { dents
        #declare fEdge = 0.0; //RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = 6.1*turb_dev;
        #declare fPhase = 0; //RRand(0.0,0.4,rPlanet)*turb_dev;
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,10.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare edge = 0.8;
  #declare SurfaceTexture[3] = texture {
     pigment { wrinkles
        #declare fEdge = 0.8; //RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = 5.5*turb_dev;
        #declare fPhase = RRand(0.1,0.4,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.40,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,5.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[4] = texture {
     pigment { waves
        #declare fEdge = 0.8; //RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = 10.5*turb_dev;
        #declare fPhase = RRand(0.2,0.8,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.65,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,10.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[5] = texture {
     pigment { agate
        #declare fEdge = RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,5.0,rPlanet);
        #declare fPhase = RRand(0.0,1.0,rPlanet);
        #declare fLambda = RRand(2.8,4.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,10.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[6] = texture {
     pigment { waves
        #declare fEdge = RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,9.0,rPlanet);
        #declare fPhase = RRand(0.2,0.8,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,5.0,rPlanet);
        #declare fTransparency = transparency_global;
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[7] = texture {
     pigment { granite
        #declare fEdge = RRand(0.00,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,3.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(4.0,6.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(20.0,50.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare layers_number = IRand(3,10,rPlanet);
  #macro mPlanetSurface()
     texture { pigment { cBaseColor } }
     #local i=1; #while(i<layers_number)
       texture { SurfaceTexture[IRand(1,iSurfaceTextures,rPlanet)] }
     #local i=i+1; #end
  #end // planet_surface texture

  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    finish { surface_finish }
    hollow on
    no_reflection
  }

#end //dirt planet macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 17
//*** vegastrike toxic_disaster planet texture ***
#macro DirtPlanet8(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)

  #declare surface_finish = finish { ambient 0.0 diffuse 1.0 }

  #declare iSurfaceTextures = 11;
  #declare SurfaceTexture = array[iSurfaceTextures+1];
  
  #declare transparency_local_on = IRand(0,1,rPlanet);
  #declare transparency_local_min = RRand(0.5,0.8,rPlanet);
  #declare transparency_local_max = RRand(0.8,0.99,rPlanet);
  #declare transparency_global = RRand(transparency_local_min,transparency_local_max,rPlanet);
  
  #declare SurfaceTexture[1] = texture {
        pigment { bozo
        #declare fEdge = 0.0;
        #declare fTurbulence = RRand(5.0, 8.1, rPlanet);
        #declare fPhase = 0;
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,5.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[2] = texture {
        pigment { dents
        #declare fEdge = 0.0;
        #declare fTurbulence = RRand(5.0, 8.1, rPlanet);
        #declare fPhase = RRand(0.0,0.4,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,10.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[3] = texture {
     pigment { wrinkles
        #declare fEdge = RRand(0.50,0.80,rPlanet);
        #declare fTurbulence = RRand(4.0, 5.0, rPlanet);
        #declare fPhase = RRand(0.10,0.40,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.35,0.50,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,6.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[4] = texture {
     pigment { waves
        #declare fEdge = RRand(0.50,0.80,rPlanet);
        #declare fTurbulence = RRand(5.0, 8.1, rPlanet);
        #declare fPhase = RRand(0.2,0.7,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,6.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[5] = texture {
     pigment { agate
        #declare fEdge = RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = RRand(3.5,5.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(3.0,4.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.50,rPlanet); // controls fineness complexity
        #declare fScale = RRand(10.0,20.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[6] = texture {
     pigment { waves
        #declare fEdge = RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,9.0,rPlanet);
        #declare fPhase = RRand(0.2,0.8,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,5.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[7] = texture {
     pigment { granite
        #declare fEdge = RRand(0.00,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,3.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(4.0,6.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(20.0,50.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[8] = texture {
     pigment { bumps
        #declare fEdge = RRand(0.00,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,4.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(4.0,6.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.50,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(5.0,10.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[9] = texture {
     pigment { cells
        #declare fEdge = RRand(0.00,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,4.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(4.0,6.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.50,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,2.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[10] = texture {
     pigment { crackle
        #declare fEdge = RRand(0.00,0.50,rPlanet);
        #declare fTurbulence = RRand(2.0,4.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.40,0.50,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,10.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[11] = texture {
     pigment { marble
        #declare fEdge = RRand(0.00,0.50,rPlanet);
        #declare fTurbulence = RRand(2.0,4.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(3.0,4.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,5.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  // Surface Texture 
  #declare layers_number = IRand(3,20,rPlanet);
  #macro mPlanetSurface()
    texture { pigment { cBaseColor } }
    #local i=1; #while(i<layers_number)
     texture { SurfaceTexture[IRand(1,iSurfaceTextures,rPlanet)] }
    #local i=i+1; #end
  #end // planet_surface texture

  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    finish { surface_finish }
    hollow on
    no_reflection
  }

#end //dirt planet macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 18
//*** vegastrike toxic_disaster planet texture ***
#macro DirtPlanet9(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)

  #declare surface_finish = finish { ambient 0.0 diffuse 1.0 }

  #declare iSurfaceTextures = 11;
  #declare SurfaceTexture = array[iSurfaceTextures+1];
  
  #declare transparency_local_on = IRand(0,1,rPlanet);
  #declare transparency_local_min = RRand(0.8,0.9,rPlanet);
  #declare transparency_local_max = RRand(0.9,0.99,rPlanet);
  #declare transparency_global = RRand(transparency_local_min,transparency_local_max,rPlanet);
  
  #declare SurfaceTexture[1] = texture {
        pigment { bozo
        #declare fEdge = 0.0;
        #declare fTurbulence = RRand(5.0, 8.1, rPlanet);
        #declare fPhase = 0;
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,5.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[2] = texture {
        pigment { dents
        #declare fEdge = 0.0;
        #declare fTurbulence = RRand(5.0, 8.1, rPlanet);
        #declare fPhase = RRand(0.0,0.4,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,10.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[3] = texture {
     pigment { wrinkles
        #declare fEdge = RRand(0.50,0.80,rPlanet);
        #declare fTurbulence = RRand(4.0, 5.0, rPlanet);
        #declare fPhase = RRand(0.10,0.40,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.35,0.50,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,6.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        #declare bDirection = 1; //IRand(0,1,rPlanet);
        #if (bDirection)
           color_map { [0.0 transmit 1] [fEdge transmit 1] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
        #else
           color_map { [0.0 surface_color transmit fTransparency] [fEdge transmit 1] [1.0 transmit 1] }
        #end
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[4] = texture {
     pigment { waves
        #declare fEdge = RRand(0.50,0.80,rPlanet); //0.8
        #declare fTurbulence = RRand(5.0, 8.1, rPlanet);
        #declare fPhase = RRand(0.2,0.7,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,6.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[5] = texture {
     pigment { agate
        #declare fEdge = RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = RRand(3.5,5.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(3.0,4.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.50,rPlanet); // controls fineness complexity
        #declare fScale = RRand(10.0,20.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[6] = texture {
     pigment { waves
        #declare fEdge = RRand(0.10,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,9.0,rPlanet);
        #declare fPhase = RRand(0.2,0.8,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,5.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[7] = texture {
     pigment { granite
        #declare fEdge = RRand(0.00,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,3.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(4.0,6.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(20.0,50.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[8] = texture {
     pigment { bumps
        #declare fEdge = RRand(0.00,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,4.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(4.0,6.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.50,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(5.0,10.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[9] = texture {
     pigment { cells
        #declare fEdge = RRand(0.00,0.70,rPlanet);
        #declare fTurbulence = RRand(2.0,4.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(4.0,6.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.50,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(1.0,2.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[10] = texture {
     pigment { crackle
        #declare fEdge = RRand(0.00,0.50,rPlanet);
        #declare fTurbulence = RRand(2.0,4.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.40,0.50,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,10.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }
  
  #declare SurfaceTexture[11] = texture {
     pigment { marble
        #declare fEdge = RRand(0.00,0.50,rPlanet);
        #declare fTurbulence = RRand(2.0,4.0,rPlanet);
        #declare fPhase = RRand(0.0,0.5,rPlanet);
        #declare fLambda = RRand(3.0,4.0,rPlanet); // controls graininess
        #declare fOmega = RRand(0.45,0.55,rPlanet); // controls fineness complexity
        #declare fScale = RRand(2.0,5.0,rPlanet);
        #if(transparency_local_on) #declare fTransparency = RRand(transparency_local_min,transparency_local_max,rPlanet); #else #declare fTransparency = transparency_global; #end
        turbulence fTurbulence phase fPhase lambda fLambda omega fOmega 
        color_map { [0.0 transmit 1 ] [fEdge transmit 1 ] [1.0 VariateColor(cBaseColor, fColorDev, bMonoColor, rPlanet) transmit fTransparency] }
     }
     scale fScale*fPlanetRadius
     rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
     finish { surface_finish }
  }

  #declare layers_number = IRand(3,20,rPlanet);
  #macro mPlanetSurface()
    texture { pigment { cBaseColor } }
      #local i=1; #while(i<layers_number)
        texture { SurfaceTexture[IRand(1,iSurfaceTextures,rPlanet)] }
      #local i=i+1; #end
  #end // planet_surface texture

  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    finish { surface_finish }
    hollow on
    no_reflection
  }

#end //dirt planet macro

#macro DirtPlanet(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet)
  #declare iType = IRand(1,9,rPlanet);
  #switch (iType)
    #case (1) DirtPlanet1(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet) #break    
    #case (2) DirtPlanet2(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet) #break    
    #case (3) DirtPlanet3(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet) #break    
    #case (4) DirtPlanet4(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet) #break    
    #case (5) DirtPlanet5(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet) #break    
    #case (6) DirtPlanet6(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet) #break    
    #case (7) DirtPlanet7(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet) #break    
    #case (8) DirtPlanet8(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet) #break    
    #case (9) DirtPlanet9(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanet) #break    
  #end
#end

// ---------------------------------------------------------------------------------------
// Mapped Planets
// ---------------------------------------------------------------------------------------

#macro Planet(fPlanetRadius, sTextureMap, sBumpMap)

  sphere {<0, 0, 0>, fPlanetRadius

    #if (strlen(sTextureMap)!=0)
      #declare file_type = substr(sTextureMap,strlen(sTextureMap)-3,4);
      //#debug concat("File type = ",file_type,"\n")
      #if (strcmp(file_type,".jpg")=0) #declare texture_type = 1; #end
      #if (strcmp(file_type,"jpeg")=0) #declare texture_type = 1; #end
      #if (strcmp(file_type,".png")=0) #declare texture_type = 2; #end
      #if (strcmp(file_type,".gif")=0) #declare texture_type = 3; #end
      #if (strcmp(file_type,".tga")=0) #declare texture_type = 4; #end
      #if (strcmp(file_type,".tif")=0) #declare texture_type = 5; #end
      #if (strcmp(file_type,"tiff")=0) #declare texture_type = 5; #end
      pigment { image_map { 
        #switch (texture_type)
          #case (1) jpeg sTextureMap #break
          #case (2) png  sTextureMap #break
          #case (3) gif  sTextureMap #break
          #case (4) tga  sTextureMap #break
          #case (5) tiff sTextureMap #break
        #end
  		  map_type 1 interpolate 4
  	    } scale fPlanetRadius
  	  }
  	#else //dummy texture
  	  pigment { rgb <0.1,0.1,1.0> }
  	#end

    #if (strlen(sBumpMap)!=0)
      #declare file_type = substr(sBumpMap,strlen(sBumpMap)-3,4);
      //#debug concat("File type = ",file_type,"\n")
      #if (strcmp(file_type,".jpg")=0) #declare bump_type = 1; #end
      #if (strcmp(file_type,"jpeg")=0) #declare bump_type = 1; #end
      #if (strcmp(file_type,".png")=0) #declare bump_type = 2; #end
      #if (strcmp(file_type,".gif")=0) #declare bump_type = 3; #end
      #if (strcmp(file_type,".tga")=0) #declare bump_type = 4; #end
      #if (strcmp(file_type,".tif")=0) #declare bump_type = 5; #end
      #if (strcmp(file_type,"tiff")=0) #declare bump_type = 5; #end
      normal { bump_map {
        #switch (bump_type)
          #case (1) jpeg sBumpMap #break
          #case (2) png  sBumpMap #break
          #case (3) gif  sBumpMap #break
          #case (4) tga  sBumpMap #break
          #case (5) tiff sBumpMap #break
        #end
        map_type 1 interpolate 4 bump_size 1.1 use_color
      } scale fPlanetRadius }
    #end

    //finish { ambient 1.0 diffuse 0.0 }
    //finish { ambient 0.0 diffuse 1.0 }
    finish { surface_finish }
    hollow on
    no_reflection
  }
#end //macro

// ---------------------------------------------------------------------------------------
// Atmosphere
// ---------------------------------------------------------------------------------------

#macro Atmosphere(fBaseRadius, fAtmoFactor cAtmoColor)

  #declare sunset_color = rgb <210/255,150/255,90/255>;
  #declare P_EmittingAtmo = pigment { slope { vSunPosition altitude vSunPosition, 0.9, -0.9 }
  	  color_map {
        [0.00 color rgb 0 transmit 1 ] // opposite to sun
        [0.49 color sunset_color transmit 1 ] // perpendicular to sun
        [0.50 color rgb 0 transmit 1] //color rgb <0.6, 0.8, 1> filter 0 transmit 1]
        [1.00 color rgb 0 transmit 1] // facing the sun
      }
  }

  // media for emitting atmosphere
  //------------------------------
  #switch (render_quality)
     #case (1)
        #declare M_Atmosphere_Intervals = 20;
        #declare M_Atmosphere_Samples = 20;
     #break
     #else
        #declare M_Atmosphere_Intervals = 10;
        #declare M_Atmosphere_Samples = 10;
     #break
  #end

  //atmosphere emission with fade formula
  #declare ATMO_STEPS = 9;
  #declare ATMO_EXPONENT = -1.7; // realistic = -2.0; cinematographic = -1.5
  #declare ATMO_STRENGTH = 20;
  #declare M_Atmosphere = media { 
  	emission 0.30
  	intervals M_Atmosphere_Intervals
  	samples M_Atmosphere_Samples     // more: e.g.100 => smoother
  	method 3
  	density { spherical
  		color_map {
  			[0.0 color rgb <0, 0, 0> filter 0 transmit 1] // outside
          #local I=1;#while(I<ATMO_STEPS)
            #local POS = log(10*(I+1)/(ATMO_STEPS+1));
            #local VAL = ATMO_STRENGTH-ATMO_STRENGTH*pow(1-POS,exp(ATMO_EXPONENT));
            [(fAtmoFactor-1)*POS color cAtmoColor*VAL/fBaseRadius filter 1 transmit 1]
          #local I=I+1;#end
  			[(fAtmoFactor-1) color cAtmoColor*ATMO_STRENGTH/fBaseRadius filter 0 transmit 1] // surface
  			[(fAtmoFactor-1) color cAtmoColor*0/fBaseRadius filter 0 transmit 1] // surface
  			[1.0 color rgb 0 filter 0 transmit 1]// <0, 0, 0>] // inside
  		}
  	}
  }

  sphere { < 0, 0, 0>, 1
        no_shadow
        hollow off
        
        texture { pigment { P_EmittingAtmo } } // sun-side emission
        
        no_shadow
        hollow on
        
        interior { media { M_Atmosphere } }
        
        finish { surface_finish }
        scale fBaseRadius * fAtmoFactor
  }

#end //macro

//EOF