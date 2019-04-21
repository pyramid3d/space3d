// ---------------------------------------------------------------------------------------
// Space3D
// Free POV-Ray script for space scenes rendering
// Copyright (C) 2005-2008 Pyramid
// Contact: pedrabella@sapo.pt
// Internet: http://space3d.no.sapo.pt/
//
// This script is distributed with ABSOLUTELY NO WARRANTY;
// See the GNU General Public License for more details,
// which can be found in doc/SPACE3D_LICENSE.txt
//
// Persistence of Vision Ray Tracer Scene Description Include File
// File       : s3d_planet_legacy.inc
// Description: Planet from space with weather, atmosphere, and simple background
// Version    : 0.45
// Date       : 2009-08-07
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

// ---------------------------------------------------------------------------------------
// Global Settings
// ---------------------------------------------------------------------------------------
#version 3.6;

// ---------------------------------------------------------------------------------------
// Include Files
// ---------------------------------------------------------------------------------------
#include "rand.inc" // random number generation macros
#include "math.inc" // math function macros

#include "s3d_math.inc"
#include "s3d_color.inc"
#include "s3d_scene.inc"

// ---------------------------------------------------------------------------------------
// User Settings
// ---------------------------------------------------------------------------------------
// Declare default values

#ifndef (show_atmosphere) #declare show_atmosphere = false; #end
#ifndef (planet_radius) #declare planet_radius = 6366; #end //earth's radius
#ifndef (atmosphere_factor) #declare atmosphere_factor = 1.04; #end
#ifndef (radius_factor_weather) #declare radius_factor_weather = 1.00001; #end
#ifndef (radius_factor_surface_emission) #declare radius_factor_surface_emission = 1.00002; #end
#ifndef (show_map) #declare show_map = false; #end
#ifndef (surface_map)
  #declare surface_map_type = 1; // 1=jpeg; 2=gif; 3=tga; 4=bmp
  #declare surface_map = "maps/earthmap1k.jpg";
#end
#ifndef (cAtmosphereColor) #declare cAtmosphereColor = rgb <0.6, 0.8, 1.0>; #end
#ifndef (atmosphere_color) #declare atmosphere_color = rgb <0.6, 0.8, 1.0>; #end
#ifndef (planet_rotation) #declare planet_rotation = <0, 0, 0>; #end
#ifndef (planet_translation) #declare planet_translation = <0, 0, 0>; #end
#ifndef (cloud_type) #declare cloud_type = 1; #end
#ifndef (cloud_intensity) #declare cloud_intensity = 1; #end
#ifndef (cloud_base_color) #declare cloud_base_color = color rgb <1.0, 1.0, 1.0>; #end
#ifndef (surface_type) #declare surface_type = 1; #end
#ifndef (SeedA) #declare SeedA = seed(14735+frame_number); #end
#ifndef (surface_base_color) #declare surface_base_color = color rgb <0.5, 0.7, 0.9>; #end
#ifndef (ocean_base_color) #declare ocean_base_color = rgb <0.063, 0.149, 0.322>; #end
#ifndef (surface_mono_color) #declare surface_mono_color = false; #end
#ifndef (surface_color_deviation) #declare surface_color_deviation = 80; #end
#ifndef (surface_texture_number) #declare surface_texture_number = frame_number; #end
#ifndef (surface_shape_number) #declare surface_shape_number = frame_number; #end
#ifndef (show_planet) #declare show_planet = true; #end
#ifndef (show_continents) #declare show_continents = false; #end
#ifndef (show_weather) #declare show_weather = false; #end
#ifndef (show_surface_emission) #declare show_surface_emission = false; #end
#ifndef (show_atmosphere_type)
  #declare show_atmosphere_type = 1; // 1=default; 2= sunside emission non-transparent; 3= all directions emission but transparent; 
#end
#ifndef (show_background) #declare show_background = false; #end
#ifndef (surface_type) #declare surface_type = 0; #end
#ifndef (SURFACE_TEXTURE_NUMBER) #declare SURFACE_TEXTURE_NUMBER = 1; #end
#ifndef (SURFACE_SHAPE_NUMBER) #declare SURFACE_SHAPE_NUMBER = 1; #end
#ifndef (OCEAN_TEXTURE_NUMBER) #declare OCEAN_TEXTURE_NUMBER = 7; #end
#ifndef (ICE_SHAPE_NUMBER) #declare ICE_SHAPE_NUMBER = 4; #end

// Quality Settings for test & sample or final rendering
#ifndef (render_quality)
   #declare render_quality = 1; // 0=fast; 1=full
#else
   #if (render_quality = 1)
      #declare render_quality = 1; // 0=fast; 1=full
   #else
      #declare render_quality = 0; // 0=fast; 1=full
   #end
#end
#ifndef (show_debug)
  #declare show_debug = false;
#end
#if (show_debug)
  #debug "//- INI: Debug --------------------------------------------------------------------//\n"
  #debug concat("Planet.inc: planet_radius defined as ", str(planet_radius,4,4),"\n")
#end
#ifndef (create_logfile)
   #declare create_logfile = false;
#end
#if (create_logfile)
   #if (defined(LogFile)=false)
      #fopen LogFile "gallery/planet.log"
      #if(frame_number<=1) write
      #else append
      #end
   #end
   #write(LogFile,"\n[Frame_",frame_number,"]\n")
#end

// ---------------------------------------------------------------------------
// OLD UNTIL VERSION 0.44
// ---------------------------------------------------------------------------
// maintained for compatibility reasons
// might be removed in later versions
                       
// ---------------------------------------------------------------------------------------
// Continents
// ---------------------------------------------------------------------------------------
#if (show_continents)

//#declare planet_surface = texture { pigment { rgb <0,0,1>*10 } }; //RichBlue

// ---------------------------------------------------------------------------------------
//TerranPlanet1
#if (surface_type=1)
   #declare planet_surface = texture { pigment {
      bozo
      colour_map {
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
      turbulence 2
      scale planet_radius
   } }
#end

//*** vegastrike m_class planet texture ***
// ---------------------------------------------------------------------------------------
//TerranPlanet2
#if (surface_type=2)
  #include "planet_surface_02.inc"
#end // end surface 10

// ---------------------------------------------------------------------------------------
//TerranPlanet3
#if (surface_type=3)
   #declare planet_texture_base = texture {
      pigment { bumps
         color_map {
            #local pigm_max = 1.00;
            #local I=0; #while(I<=pigm_max)            
               #local pigm_delta = RRand(-60/255,60/255,RdmA);
               [I color rgb <(245/255)+pigm_delta, (220/255)+pigm_delta, (180/255)+pigm_delta> ] 
               //[I color rgb <(245/255)+pigm_delta, (190/255)+pigm_delta, (120/255)+pigm_delta> ] 
            #local I=I+0.05; #end
            }
      //phase 0.01
      turbulence 0.3
      scale 0.9*planet_radius //0.5
      }
      finish { surface_finish }
   }
   #declare planet_texture_soil = texture {
      pigment { bumps
        color_map {
            #local pigm_max = 0.60;
            #local I=0; #while(I<=pigm_max)            
               #local pigm_delta = RRand(-20/255,40/255,RdmA);
               [I color rgb <(180/255)+pigm_delta, (120/255)+pigm_delta, (70/255)+pigm_delta> transmit RRand(0.4,0.7,rPlanet) ] 
               //[I color rgb <(190/255)+pigm_delta, (90/255)+pigm_delta, (64/255)+pigm_delta> transmit RRand(0.4,0.7,rPlanet) ] 
            #local I=I+0.025; #end
            [pigm_max  color rgbf <1,1,1,1> ]
            [1.0  color rgbf <1,1,1,1> ]
        }
        frequency 1
        turbulence 4
        phase RRand(0.0, 0.2, rPlanet)
        omega 0.7
        scale 0.4*<1,1.2,1>*planet_radius
      }
      finish { surface_finish }
    }
   #declare planet_texture_forest = texture {
      pigment { bumps
        color_map {
            //#local pigm_max = 0.40;
            //#local I=0; #while(I<=pigm_max)            
            //   #local pigm_delta = RRand(-10/255,100/255,rPlanet);
            //   [I color rgb <(12/255)+pigm_delta, (29/255)+pigm_delta, (37/255)+pigm_delta> filter I ] 
            //#local I=I+0.05; #end
            [0.00 color rgbf <1, 1, 1, 1> ]
            [0.60 color rgbf <1, 1, 1, 1> ]
            #local pigm_max = 1.0;
            #local I=0.60; #while(I<=pigm_max)            
               #local pigm_delta = RRand(-0/255,30/255,SeedA);
               [I color rgb <(67/255)+pigm_delta, (79/255)+pigm_delta, (37/255)+pigm_delta> filter 1 ] 
            #local I=I+0.05; #end
         }
      frequency 1
      turbulence 0.5
      phase 0.05
      omega 0.7
      scale 0.12*planet_radius
      }
      finish { surface_finish }
   } 
   #declare planet_texture_water = texture {
      pigment { bozo
         color_map {
            #local pigm_max = 0.60;
            #local I=0; #while(I<=pigm_max)            
               [I color rgb <RRand(0/255,10/255,SeedA), RRand(10/255,30/255,SeedA), RRand(180/255,255/255,SeedA)> filter 0 ]
               //[I color rgb <10/255, 30/255, 120/255> filter 0 ]  // ocean 
            #local I=I+0.10; #end
            [0.60 color rgbf <1, 1, 1, 1> ] // land ini
            [1.00  color rgbf <1, 1, 1, 1> ] // land end
         }
      omega 0.55
      turbulence 0.5
      phase 0.1
      scale 0.4*planet_radius
      //translate <24,-6,-13>  // interesting place in texture space
      }
      finish { surface_finish brilliance 2.2 }
   }
   #declare planet_surface =
      texture {planet_texture_base}
      texture {planet_texture_soil}
      texture {planet_texture_forest}
      texture {planet_texture_water}
#end

// simple gas giant surface
// ---------------------------------------------------------------------------------------
//GasGiant1
#if (surface_type=4)
   #declare planet_surface = texture {
      pigment { gradient y turbulence .05 frequency -1
         color_map {
            [0 color rgb <.85,.8,.725>] // poles
            [.05 color rgb <.875,.875,.775>]
            [.15 color rgb <.925,.875,.825>]
            [.25 color rgb <.9,.875,.85>]
            [.275 color rgb <.825,.8,.775>]
            [.33 color rgb <.925,.85,.875>]
            [.45 color rgb <.975,.95,.925>]
            [.54 color rgb <.85,.6,.75>]
            [.55 color rgb <.95,.55,.4>] // Great Red Spot
            [.56 color rgb <.9,.95,.85>]
            [.6 color rgb <.85,.8,.875>]
            [.65 color rgb <.8,.45,.55>]
            [.725 color rgb <.725,.55,.4>] // dark bands
            [.8 color rgb <.725,.575,.425>]
            [.9 color rgb <.85,.7,.725>]
            [.95 color rgb <.75,.725,.775>]
            [1 color rgb <.95,.8,.75>] // equator
         } scale <.2,1,.2>*planet_radius rotate 15*y translate -.05*y
         warp {black_hole <.5,-.5,-.8>,.25 falloff .3 strength 1.2 turbulence 0 inverse}
      }
      finish { surface_finish }
   }
#end

//gas giant
// ---------------------------------------------------------------------------------------
//GasGiant2
#if (surface_type=5)
   #declare planet_surface = texture {
      pigment { gradient y
         noise_generator 2 //IRand(0,3,SeedA) //2 //0-3
         turbulence RRand(0.02, 0.15, SeedA) //0.05 //0.05-0.5
         lambda RRand(0.0, 2.0, SeedA) //0.0-2.0
         omega 0.5 //RRand (0.0, 0.7, SeedA) //0.0-0.7
         octaves 6 //RRand(5, 7, SeedA) //1-1000
         frequency RRand(1.0, 3.0, SeedA) //3.0 //1.0-3.0
         #local ramp_method = IRand(1,6,SeedA);
         #switch (ramp_method)
            #case (1) ramp_wave     #break
            #case (2) triangle_wave #break
            #case (3) sine_wave     #break
            #case (4) scallop_wave  #break
            #case (5) cubic_wave    #break
            #case (6) poly_wave RRand(0.1, 5.0, SeedA) //0.1-5.0 
                                    #break
            #else     ramp_wave
         #end
         color_map {
            #local pigm_max = 1.0;
            #local color_delta_max = surface_color_deviation;
            #local I=0; #while(I<=pigm_max) // start loop            
               #local color_base_r = surface_base_color.red;
               #local color_base_g = surface_base_color.green;
               #local color_base_b = surface_base_color.blue;
               #if (surface_mono_color)
                  #local pigm_delta = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #local pigm_delta_r = pigm_delta;
                  #local pigm_delta_g = pigm_delta;
                  #local pigm_delta_b = pigm_delta;
               #else
                  #local pigm_delta_r = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #local pigm_delta_g = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #local pigm_delta_b = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
               #end
                  [I color rgb <color_base_r+pigm_delta_r, color_base_g+pigm_delta_g, color_base_b+pigm_delta_b> ]
            #local I=I+RRand(0.01,0.05,SeedA); #end // end loop //RRand(0.01,0.10,SeedA)
         }
         scale planet_radius //translate -100*y
         #local loop_max = IRand(100,500,SeedA);
         #declare DensityCurve = spline { 0.0 <0,0.05,0> 0.8 <0,.0.10,0> 1.0 <0,0.3,0> };

         #local I=0; #while(I<=loop_max) // start loop            
            warp { black_hole VRand_On_Sphere(SeedA)*planet_radius,
                   DensityCurve(rand(SeedA)).y*planet_radius //RRand(0.05,0.3,SeedA)*planet_radius
                   falloff RRand(1.5,7.5,SeedA)
                   strength RRand(1.2,2.2,SeedA)
                   turbulence RRand(0.0,0.5,SeedA)
                   inverse }
         #local I=I+1; #end // end loop
      }
      finish { surface_finish }
   }
#end

//gas giant
// ---------------------------------------------------------------------------------------
//GasGiant3
#if (surface_type=6)
   #declare planet_surface = texture {
      pigment { gradient y
         noise_generator IRand(0,3,SeedA) //0-3
         turbulence RRand(0.02, 0.15, SeedA) //0.05 //0.05-0.5
         lambda RRand(0.0, 2.0, SeedA) //0.0-2.0
         #local param_omega = RRand (0.0, 0.7, SeedA); 
         omega param_omega //0.5 //RRand (0.0, 0.7, SeedA) //0.0-0.7
         #local param_octaves = IRand (5, 7, SeedA); 
         octaves param_octaves //RRand(5, 7, SeedA) //1-1000
         frequency RRand(1.0, 3.0, SeedA) //3.0 //1.0-3.0
         #local ramp_method = IRand(1,6,SeedA);
         #switch (ramp_method)
            #case (1) ramp_wave     #break
            #case (2) triangle_wave #break
            #case (3) sine_wave     #break
            #case (4) scallop_wave  #break
            #case (5) cubic_wave    #break
            #case (6) poly_wave RRand(0.1, 5.0, SeedA) //0.1-5.0 
                                    #break
            #else     ramp_wave
         #end
         pigment_map {
            #local color_delta_max = surface_color_deviation;
            #local pigm_max = 1.0;
            #local I=0; #while(I<=pigm_max) // start loop            
               #local color_base_r = surface_base_color.red;
               #local color_base_g = surface_base_color.green;
               #local color_base_b = surface_base_color.blue;
               #if (surface_mono_color)
                  #local pigm_delta = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #local pigm_delta_r = pigm_delta;
                  #local pigm_delta_g = pigm_delta;
                  #local pigm_delta_b = pigm_delta;
               #else
                  #local pigm_delta_r = 0;
                  #local pigm_delta_g = 0;
                  #local pigm_delta_b = 0;
                  #local choose_pigment = IRand(1,3,SeedA);
                  #if (choose_pigment = 1)
                     #local pigm_delta_r = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #end
                  #if (choose_pigment = 2)
                     #local pigm_delta_g = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #end
                  #if (choose_pigment = 3)
                     #local pigm_delta_b = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #end
               #end
                  //[I color rgb <color_base_r+pigm_delta_r, color_base_g+pigm_delta_b, color_base_b+pigm_delta_b> ]
                  [I agate //wrinkles //agate //
                     pigment_map {
                        //[0.00 color rgb <color_base_r+pigm_delta_r, color_base_g+pigm_delta_b, color_base_b+pigm_delta_b> ] //rgb <1,0,0> ] // outside color
                        //[0.50 color rgb <color_base_r+pigm_delta_r, color_base_g+pigm_delta_b, color_base_b+pigm_delta_b>*0.5] // crater curve
                        //[1.00 color rgb <color_base_r+pigm_delta_r, color_base_g+pigm_delta_b, color_base_b+pigm_delta_b>] // edge extension to center
                        #local turb_max = 1.0;
                        #local J=0.5; #while(J<=turb_max) // start loop
                           #local turb_factor = RRand(0.5,1.5,SeedA);            
                           [J color rgb < (color_base_r+pigm_delta_r)*turb_factor,
                                          (color_base_g+pigm_delta_g)*turb_factor,
                                          (color_base_b+pigm_delta_b)*turb_factor>
                           ] //rgb <1,0,0> ] // outside color
                        #local J=J+RRand(0.02,0.10,SeedA); #end // end loop
                     }
                   turbulence RRand(0.0,2.0,SeedA)
                   scale <RRand(0.01,0.1,SeedA),RRand(0.01,0.1,SeedA),RRand(0.01,0.1,SeedA)>
                 ]
            #local I=I+RRand(0.02,0.30,SeedA); #end // end loop //RRand(0.01,0.10,SeedA)
         }
         scale planet_radius translate -planet_radius*RRand(0.1,0.9,SeedA)*y
         // larger storms
         #local loop_max = IRand(100,1000,SeedA);
         #declare DensityCurve = spline { 0.0 <0,0.05,0> 0.9 <0,.0.10,0> 1.0 <0,0.3,0> };
         #local I=0; #while(I<=loop_max) // start loop            
            warp { black_hole VRand_On_Sphere(SeedA)*planet_radius,
                   DensityCurve(rand(SeedA)).y*planet_radius
                   falloff RRand(1.5,7.5,SeedA)
                   strength RRand(1.2,2.2,SeedA)
                   turbulence RRand(0.0,0.5,SeedA)
                   inverse }
         #local I=I+1; #end // end loop
         // smaller storms
         #local loop_max = IRand(500,10000,SeedA);
         #declare DensityCurve = spline { 0.0 <0,0.01,0> 0.5 <0,0.03,0> 1.0 <0,0.05,0> };
         #local I=0; #while(I<=loop_max) // start loop            
            warp { black_hole VRand_On_Sphere(SeedA)*planet_radius,
                   DensityCurve(rand(SeedA)).y*planet_radius
                   falloff RRand(1.5,7.5,SeedA)
                   strength RRand(1.2,2.2,SeedA)
                   turbulence RRand(0.0,0.5,SeedA)
                   inverse }
         #local I=I+1; #end // end loop
      }
      finish { surface_finish }
   }
#end

//gas giant
// ---------------------------------------------------------------------------------------
//GasGiant4
#if (surface_type=7)
   #declare planet_surface = texture {
      pigment { gradient y
         noise_generator IRand(0,3,SeedA) //0-3
         turbulence RRand(0.02, 0.15, SeedA) //0.05 //0.05-0.5
         //lambda RRand(0.0, 2.0, SeedA) //0.0-2.0
         #local param_omega = RRand(0.0, 0.7, SeedA); 
         //omega param_omega //0.5 //RRand (0.0, 0.7, SeedA) //0.0-0.7
         #local param_octaves = IRand (5, 7, SeedA); 
         //octaves param_octaves //RRand(5, 7, SeedA) //1-1000
         //frequency RRand(0.1, 1.0, SeedA) //3.0 //1.0-3.0
         #local ramp_method = IRand(1,6,SeedA);
         #switch (ramp_method)
            #case (1) ramp_wave     #break
            #case (2) triangle_wave #break
            #case (3) sine_wave     #break
            #case (4) scallop_wave  #break
            #case (5) cubic_wave    #break
            #case (6) poly_wave RRand(0.1, 5.0, SeedA) //0.1-5.0 
                                    #break
            #else     ramp_wave
         #end
         #local luma_factor = RRand(0.5,1.0,SeedA);
         #local cloud_turbulence = RRand(1.0,2.0,SeedA);
         pigment_map {
            #local color_delta_max = surface_color_deviation;
            #local pigm_max = 1.0;
            #local I=0; #while(I<=pigm_max) // start loop            
               #local color_base_r = surface_base_color.red;
               #local color_base_g = surface_base_color.green;
               #local color_base_b = surface_base_color.blue;
               #if (surface_mono_color)
                  #local pigm_delta = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #local pigm_delta_r = pigm_delta;
                  #local pigm_delta_g = pigm_delta;
                  #local pigm_delta_b = pigm_delta;
               #else
                  #local pigm_delta_r = 0;
                  #local pigm_delta_g = 0;
                  #local pigm_delta_b = 0;
                  #local choose_pigment = IRand(1,3,SeedA);
                  #if (choose_pigment = 1)
                     #local pigm_delta_r = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #end
                  #if (choose_pigment = 2)
                     #local pigm_delta_g = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #end
                  #if (choose_pigment = 3)
                     #local pigm_delta_b = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #end
               #end
               [I wrinkles //agate //
                  pigment_map {
                     [0.0 color rgb < (color_base_r+pigm_delta_r),
                           (color_base_g+pigm_delta_g),
                           (color_base_b+pigm_delta_b)>
                     ]
                     #local turb_max = 1.0;
                     #local J=RRand(0.5,0.9,SeedA); #while(J<=turb_max) // start loop
                        //#local luma_factor = RRand(0.5,1.5,SeedA);            
                        //#local luma_factor = RRand(1.0,1.0,SeedA);            
                        [J bozo
                           pigment_map {
                                 [0.0 color rgb < (color_base_r+pigm_delta_r)*luma_factor,
                                       (color_base_g+pigm_delta_g)*luma_factor,
                                       (color_base_b+pigm_delta_b)*luma_factor>
                                 ]
                              #local turb_max = 1.0;
                              #local K=RRand(0.5,0.9,SeedA); #while(K<=turb_max) // start loop
                              #local lightness = K*3;            
                                 [K color rgb < (color_base_r+pigm_delta_r)*luma_factor*lightness,
                                          (color_base_g+pigm_delta_g)*luma_factor*lightness,
                                          (color_base_b+pigm_delta_b)*luma_factor*lightness>
                                 ]
                              #local K=K+RRand(0.01,0.02,SeedA); #end // end loop
                           }
                           turbulence RRand(1.0,3.0,SeedA)
                        ] //rgb <1,0,0> ] // outside color
                     #local J=J+0.05; //RRand(0.02,0.10,SeedA);
                     #end // end loop
                  }
               #local cloud_turbulence = cloud_turbulence + RRand(-0.2,0.2,SeedA);
               turbulence cloud_turbulence //RRand(1.0,2.0,SeedA)
               scale <RRand(0.05,0.1,SeedA),RRand(0.01,0.05,SeedA),RRand(0.05,0.1,SeedA)>
            ]
            #local I=I+RRand(0.05,0.20,SeedA); #end // end loop //RRand(0.01,0.10,SeedA)
         }
         scale planet_radius //translate -planet_radius*RRand(0.1,0.9,SeedA)*y
         // larger storms
         #local loop_max = IRand(10,500,SeedA);
         #declare DensityCurve = spline { 0.0 <0,0.05,0> 0.9 <0,.0.07,0> 1.0 <0,0.10,0> };
         #local I=0; #while(I<=loop_max) // start loop            
            warp { black_hole VRand_On_Sphere(SeedA)*planet_radius,
                   DensityCurve(rand(SeedA)).y*planet_radius
                   falloff RRand(1.5,7.5,SeedA)
                   strength RRand(1.2,2.2,SeedA)
                   turbulence RRand(0.0,0.5,SeedA)
                   inverse }
         #local I=I+1; #end // end loop
         // smaller storms
         #local loop_max = IRand(500,10000,SeedA);
         #declare DensityCurve = spline { 0.0 <0,0.01,0> 0.5 <0,0.03,0> 1.0 <0,0.05,0> };
         #local I=0; #while(I<=loop_max) // start loop            
            warp { black_hole VRand_On_Sphere(SeedA)*planet_radius,
                   DensityCurve(rand(SeedA)).y*planet_radius
                   falloff RRand(1.5,7.5,SeedA)
                   strength RRand(1.2,2.2,SeedA)
                   turbulence RRand(0.0,0.5,SeedA)
                   inverse }
         #local I=I+1; #end // end loop
      }
      finish { surface_finish }
   }
#end

#if (surface_type=8)
   #declare planet_texture_base = texture {
      pigment { wrinkles //agate //bozo //bumps
         pigment_map {
            #local color_delta_max = surface_color_deviation;
            #local pigm_max = 1.00;
            #local I=0; #while(I<=pigm_max)            
               //#local pigm_delta = RRand(-60/255,60/255,RdmA);
               #local color_base_r = surface_base_color.red;
               #local color_base_g = surface_base_color.green;
               #local color_base_b = surface_base_color.blue;
               #if (surface_mono_color)
                  #local pigm_delta = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #local pigm_delta_r = pigm_delta;
                  #local pigm_delta_g = pigm_delta;
                  #local pigm_delta_b = pigm_delta;
               #else
                  #local pigm_delta_r = 0;
                  #local pigm_delta_g = 0;
                  #local pigm_delta_b = 0;
                  #local choose_pigment = IRand(1,3,SeedA);
                  #if (choose_pigment = 1)
                     #local pigm_delta_r = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #end
                  #if (choose_pigment = 2)
                     #local pigm_delta_g = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #end
                  #if (choose_pigment = 3)
                     #local pigm_delta_b = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #end
               #end
               [I color rgb <color_base_r+pigm_delta_r, color_base_g+pigm_delta_g, color_base_b+pigm_delta_b> ] 
               //[I color rgb <(245/255)+pigm_delta, (220/255)+pigm_delta, (180/255)+pigm_delta> ] 
            #local I=I+RRand(0.05,0.05,SeedA); #end //0.15
            }
      //phase 0.01 //RRand(0.01,3.0,SeedA) //0.01
      turbulence RRand(0.9,3.0,SeedA) //0.3
      scale <RRand(0.05,0.20,SeedA),RRand(0.05,0.20,SeedA),RRand(0.05,0.20,SeedA)>*planet_radius //0.5
      }
      finish { surface_finish }
   }
   #declare planet_texture_soil = texture {
      pigment { bozo //wrinkles //bumps
         pigment_map {
            #local color_delta_max = surface_color_deviation;
            #local surface_base_color = color rgb <(180/255), (120/255), (70/255)>;
            #local pigm_max = 0.40;
            #local I=0; #while(I<=pigm_max)            
               #local color_base_r = surface_base_color.red;
               #local color_base_g = surface_base_color.green;
               #local color_base_b = surface_base_color.blue;
               #if (surface_mono_color)
                  #local pigm_delta = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #local pigm_delta_r = pigm_delta;
                  #local pigm_delta_g = pigm_delta;
                  #local pigm_delta_b = pigm_delta;
               #else
                  #local pigm_delta_r = 0;
                  #local pigm_delta_g = 0;
                  #local pigm_delta_b = 0;
                  #local choose_pigment = IRand(1,3,SeedA);
                  #if (choose_pigment = 1)
                     #local pigm_delta_r = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #end
                  #if (choose_pigment = 2)
                     #local pigm_delta_g = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #end
                  #if (choose_pigment = 3)
                     #local pigm_delta_b = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #end
               #end
               [I color rgb <color_base_r+pigm_delta_r, color_base_g+pigm_delta_g, color_base_b+pigm_delta_b> transmit RRand(0.4,0.7,SeedA) ] 
               //#local pigm_delta = RRand(-20/255,40/255,RdmA);
               //[I color rgb <(180/255)+pigm_delta, (120/255)+pigm_delta, (70/255)+pigm_delta> transmit RRand(0.4,0.7,SeedA) ] 
            #local I=I+RRand(0.005,0.025,SeedA); #end //0.025
            [pigm_max  color rgbf <1,1,1,1> ]
            [1.0  color rgbf <1,1,1,1> ]
         }
         omega RRand(0.4, 0.7, SeedA) //0.7
         turbulence RRand(2,7,SeedA) //4
         phase RRand(0.0, 0.2, SeedA) //0.0-0.2
         frequency 1 //RRand(1, 2, SeedA) //1
         //scale 0.4*<1,1.2,1>*planet_radius
         scale <RRand(0.1,0.5,SeedA),RRand(0.1,0.6,SeedA),RRand(0.1,0.5,SeedA)>*planet_radius //0.5
      }
      finish { surface_finish }
    }
   #declare planet_texture_forest = texture {
      pigment { bumps
        pigment_map {
            [0.00 color rgbf <1, 1, 1, 1> ]
            [0.60 color rgbf <1, 1, 1, 1> ]
            #local pigm_max = 1.0;
            #local I=0.60; #while(I<=pigm_max)            
               #local pigm_delta = RRand(-0/255,30/255,SeedA);
               [I color rgb <(67/255)+pigm_delta, (79/255)+pigm_delta, (37/255)+pigm_delta> filter 1 ] 
            #local I=I+RRand(0.01,0.10,SeedA); #end //0.05
         }
      frequency RRand(0.5, 2.0, SeedA) //1
      turbulence RRand(0.3, 0.9, SeedA) //0.5
      phase RRand(0.05, 0.2, SeedA) //0.05
      omega RRand(0.6, 0.75, SeedA) //0.7
      scale 0.12*planet_radius
      }
      finish { surface_finish }
   } 
   #declare planet_texture_water = texture {
      pigment { bozo
         color_map {
            #local pigm_max = 0.60; //RRand(0.5, 0.8, SeedA); //0.60;
            #local I=0; #while(I<=pigm_max)            
               [I color rgb <RRand(0/255,10/255,SeedA), RRand(10/255,30/255,SeedA), RRand(180/255,255/255,SeedA)> filter 0 ]
            #local I=I+RRand(0.1,0.1,SeedA); #end //0.1
            [pigm_max color rgbf <1, 1, 1, 1> ] // land ini
            [1.00  color rgbf <1, 1, 1, 1> ] // land end
         }
      omega RRand(0.5, 0.6, SeedA) //0.55
      turbulence RRand(0.5, 0.9, SeedA) //0.5
      phase RRand(0.0, 1.0, SeedA) //0.1
      scale 0.4*planet_radius
      }
      finish { surface_finish brilliance 2.2 }
   }
   #declare planet_surface =
      texture {planet_texture_base}
      texture {planet_texture_soil}
      texture {planet_texture_forest}
      texture {planet_texture_water}
#end

//*** vegastrike - dirt planet texture
// ---------------------------------------------------------------------------------------
#if (surface_type=9)
   #declare detail_lightness = RRand(1.0, 2.0, SeedA); //1.0-3.0
   #declare color_factor = 1; //RRand(1.0, 1.01, SeedA); //1.1-1.5
   #declare turb_dev = RRand(1.0, 1.5, SeedA); //(1.0,1.5)
   #declare base_color_tone = surface_base_color;
   #declare base_color_dev = surface_color_deviation;
   #declare bcdev_r = base_color_tone.red + RRand(-0.2,0.2,SeedA);
   #declare bcdev_g = base_color_tone.green + RRand(-0.2,0.2,SeedA);
   #declare bcdev_b = base_color_tone.blue + RRand(-0.2,0.2,SeedA);
   #declare base_color = color rgb<bcdev_r,bcdev_g,bcdev_b>;
   #declare FineDetail_01 = texture {
      #declare r = base_color.red*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
      #declare g = base_color.green*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
      #declare b = base_color.blue*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
       pigment { bumps
         turbulence 1*turb_dev
         lambda RRand(2.0,10.0,SeedA) // controls graininess
         omega RRand(0.5,1.0,SeedA) // controls finness complexity
         color_map {
           [0.0 transmit 1 ]
           [1.0 color <r, g, b> ]
         }
       }
       scale 0.02*planet_radius
       rotate <RRand(0,360,SeedA),RRand(0,360,SeedA),RRand(0,360,SeedA)>
       finish { surface_finish }
     }
   // soft detail
   #declare r = base_color.red*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare g = base_color.green*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare b = base_color.blue*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare FineDetail_02 = texture {
       pigment {
         bozo
         turbulence 1*turb_dev
         lambda RRand(1.0,3.0,SeedA) // controls graininess
         omega RRand(0.5,1.0,SeedA) // controls fineness complexity
         color_map {
           [0.0 transmit 1 ]
           [1.0 color <r, g, b> ]
         }
       }
       scale 0.06*planet_radius
       rotate <RRand(0,360,SeedA),RRand(0,360,SeedA),RRand(0,360,SeedA)>
       finish { surface_finish }
     }
   #declare r = base_color.red*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare g = base_color.green*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare b = base_color.blue*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare FineDetail_03 = texture {
       pigment {
         dents
         turbulence 1*turb_dev
         lambda RRand(2.0,5.0,SeedA) // controls graininess
         omega RRand(0.2,0.6,SeedA) // controls fineness complexity
         color_map {
           [0.0 transmit 1 ]
           [0.9 color <r, g, b> ]
         }
       }
       scale 0.06*planet_radius
       rotate <RRand(0,360,SeedA),RRand(0,360,SeedA),RRand(0,360,SeedA)>
       finish { surface_finish }
     }
   //desert like surface
   #declare r = base_color.red*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare g = base_color.green*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare b = base_color.blue*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare FineDetail_04 = texture {
       pigment {
         granite
         turbulence 0.5*turb_dev
         lambda RRand(2.0,5.0,SeedA) // controls graininess
         omega RRand(0.1,0.6,SeedA) // controls fineness complexity
         color_map {
           [0.0 transmit 1 ]
           [1.0 color <r, g, b> ]
         }
       }
       scale 0.50*planet_radius
       rotate <RRand(0,360,SeedA),RRand(0,360,SeedA),RRand(0,360,SeedA)>
       finish { surface_finish }
     }
   // the line is to align the usage of the seed with the inherited planet_surface_v0.03      
   #local i=0; #while (i<=6) #declare rn = RRand(0,1,SeedA); #local i=i+1; #end
   #declare r = base_color.red*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare g = base_color.green*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare b = base_color.blue*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare FineDetail_06 = texture {
       pigment { spotted
         turbulence 0.3*turb_dev
         phase RRand(0.0,1.0,SeedA)*turb_dev //alternatively don't use
         lambda RRand(2.0,5.0,SeedA) // controls graininess
         omega RRand(0.2,1.3,SeedA) // controls fineness complexity
         color_map {
           [0.0 transmit 1 ]
           [1.0 color <r, g, b> ]
         }
       }
       scale 0.10*planet_radius
       rotate <RRand(0,360,SeedA),RRand(0,360,SeedA),RRand(0,360,SeedA)>
       finish { surface_finish }
     }
   // could be a mountain range
   #declare r = base_color.red*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare g = base_color.green*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare b = base_color.blue*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare FineDetail_07 = texture {
       pigment { wrinkles
         turbulence 0.1*turb_dev
         phase RRand(0.0,1.0,SeedA)*turb_dev
         lambda RRand(2.0,10.0,SeedA)
         omega RRand(0.0,1.5,SeedA)
         color_map {
           [0.5 transmit 1 ]
           [1.0 color <r, g, b> ]
         }
       }
       scale 0.60*planet_radius
       rotate <RRand(0,360,SeedA),RRand(0,360,SeedA),RRand(0,360,SeedA)>
       finish { surface_finish }
     }
   //some strange surface
   #declare r = base_color.red*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare g = base_color.green*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare b = base_color.blue*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare FineDetail_08 = texture {
       pigment { wrinkles
         turbulence RRand(1.1,1.5,SeedA)*turb_dev
         lambda RRand(2.0,5.0,SeedA)
         omega RRand(0.3,0.9,SeedA)
         color_map {
           [0.0 transmit 1 ]
           [1.0 color <r, g, b> ]
         }
       }
       scale 0.20*planet_radius
       rotate <RRand(0,360,SeedA),RRand(0,360,SeedA),RRand(0,360,SeedA)>
       finish { surface_finish }
     }
   // macro detail structures
   #declare r = base_color.red*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare g = base_color.green*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare b = base_color.blue*detail_lightness*RRand(1/color_factor,color_factor,SeedA);
   #declare FineDetail_09 = texture {
       pigment { waves
         turbulence 10.1*turb_dev
         phase RRand(0.0,0.4,SeedA)*turb_dev
         lambda RRand(2.0,5.0,SeedA) // controls graininess
         omega RRand(0.2,0.6,SeedA) // controls fineness complexity
         color_map {
           [0.0 transmit 1 ]
           [1.0 color <r, g, b> ]
         }
       }
       scale 2.02*planet_radius
       rotate <RRand(0,360,SeedA),RRand(0,360,SeedA),RRand(0,360,SeedA)>
       finish { surface_finish }
     }
   // the line is to align the usage of the seed with the inherited planet_surface_v0.03      
   #local i=0; #while (i<=30) #declare rn = RRand(0,1,SeedA); #local i=i+1; #end
   #declare incl_detail= array[14];
   #declare incl_detail[0] = 1; //IRand(0,1,SeedA); //always show  base
   #declare incl_detail[9] = IRand(0,1,SeedA);
   #declare incl_detail[7] = IRand(0,1,SeedA);
   #declare incl_detail[6] = IRand(0,1,SeedA);
   #declare incl_detail[2] = IRand(0,1,SeedA);
   #declare incl_detail[1] = IRand(0,1,SeedA);
   #declare incl_detail[4] = IRand(0,1,SeedA);
   #declare incl_detail[3] = IRand(0,1,SeedA);
   #declare incl_detail[8] = IRand(0,1,SeedA);
   // create the texture
   #macro planet_surface()
      #local detail_num=0;
      #if (incl_detail[detail_num]=1)
         texture { pigment { base_color } }
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
   #end // planet_surface_texture
#end // end surface 9

// m-class ocean planet surface
// ---------------------------------------------------------------------------------------

//*** vegastrike university planet texture ***
//TerranPlanet5
#if (surface_type=10)
   #include "planet_surface_10.inc"
#end // end surface 10

//DirtPlanet2
//*** vegastrike frigid_mud planet texture ***
#if (surface_type=11)
   #include "planet_surface_11.inc"
#end // end surface 11

//DirtPlanet3
//*** vegastrike rocky planet texture ***
#if (surface_type=12)
   #include "planet_surface_12.inc"
#end // end surface 12

//DirtPlanet4
//*** vegastrike wasteland planet texture ***
#if (surface_type=13)
   #include "planet_surface_13.inc"
#end // end surface 13

//DirtPlanet5
//*** vegastrike waterlava planet texture ***
#if (surface_type=14)
   #include "planet_surface_14.inc"
#end // end surface 14

//DirtPlanet6
//*** vegastrike n_class planet texture ***
#if (surface_type=15)
   #include "planet_surface_15.inc"
#end // end surface 15

//DirtPlanet7
//*** vegastrike tkirsa planet texture ***
#if (surface_type=16)
   #include "planet_surface_16.inc"
#end // end surface 16

//DirtPlanet8
//*** vegastrike toxic_disaster planet texture ***
#if (surface_type=17) #include "planet_surface_17.inc" #end

//DirtPlanet9
//*** vegastrike planet texture ***
#if (surface_type=18) #include "planet_surface_18.inc" #end

//TerranPlanet6
//*** vegastrike k_class (carribean) planet texture ***
#if (surface_type=19) #include "planet_surface_19.inc" #end

//TerranPlanet7
//*** vegastrike m_class (carribean) planet texture ***
#if (surface_type=20) #include "planet_surface_20.inc" #end

//*** vegastrike carribean planet texture ***
#if (surface_type=21) #include "planet_surface_21.inc" #end

//*** vegastrike carribean planet texture ***
#if (surface_type=22) #include "planet_surface_22.inc" #end

//*** vegastrike trantor class planet texture ***
#if (surface_type=23) #include "planet_surface_23.inc" #end

// ocean planet surface
// ---------------------------------------------------------------------------
// under development
#if (surface_type=99)
   #declare steps_number = IRand(0,10,SeedA); //number of steps
   #declare SurfaceDetail_01 = texture {
      pigment { gradient y
         turbulence RRand(0.00, 0.05, SeedA)
         lambda RRand(2.0,5.0,SeedA) // controls graininess
         omega RRand(0.2,0.6,SeedA) // controls fineness complexity
         color_map {
            #local I=1/(steps_number+1); #while (I<=1.0)
               #declare r = surface_base_color.red;
               #declare g = surface_base_color.green;
               #declare b = surface_base_color.blue;
               #declare bChangeStripe = Rand_Binomial(1,0.3,SeedA); //IRand(0,1,SeedA); //probability function
               #if (bChangeStripe)
               #if (surface_mono_color=0)
                  #declare r = surface_base_color.red+RRand(-surface_color_deviation,surface_color_deviation,SeedA);
                  #declare g = surface_base_color.green+RRand(-surface_color_deviation,surface_color_deviation,SeedA);
                  #declare b = surface_base_color.blue+RRand(-surface_color_deviation,surface_color_deviation,SeedA);
               #else
                  #declare color_deviation = RRand(-surface_color_deviation,surface_color_deviation,SeedA);
                  #declare r = clip(surface_base_color.red+color_deviation,0,1);
                  #declare g = clip(surface_base_color.green+color_deviation,0,1);
                  #declare b = clip(surface_base_color.blue+color_deviation,0,1);
               #end
               #end
               #if(show_debug)
                  #debug concat("position: ",str(I,4,4),"\n")
                  #debug concat(" color.red: ",str(r,4,4),"\n")
                  #debug concat(" color.green: ",str(g,4,4),"\n")
                  #debug concat(" color.blue: ",str(b,4,4),"\n")
               #end
               [I color rgb<r,g,b>]
            #local I=I+(1/(steps_number+1)); #end
            [1.00 color rgb<r,g,b>] // south pole
         }
         scale 2*planet_radius
         translate y*planet_radius
         // larger storms
         #local loop_max = IRand(10,100,SeedA);
         #declare DensityCurve = spline { 0.0 <0,0.10,0> 0.9 <0,.0.20,0> 1.0 <0,0.50,0> };
         #local I=0; #while(I<=loop_max) // start loop            
            warp { black_hole VRand_On_Sphere(SeedA)*planet_radius,
                   DensityCurve(rand(SeedA)).y*planet_radius
                   falloff RRand(1.5,7.5,SeedA)
                   strength RRand(1.2,2.2,SeedA)
                   turbulence RRand(0.0,0.5,SeedA)
                   inverse }
         #local I=I+1; #end // end loop
         // smaller storms
         #local loop_max = IRand(100,200,SeedA);
         #declare DensityCurve = spline { 0.0 <0,0.05,0> 0.5 <0,0.07,0> 1.0 <0,0.10,0> };
         #local I=0; #while(I<=loop_max) // start loop            
            warp { black_hole VRand_On_Sphere(SeedA)*planet_radius,
                   DensityCurve(rand(SeedA)).y*planet_radius
                   falloff RRand(1.5,7.5,SeedA)
                   strength RRand(1.2,2.2,SeedA)
                   turbulence RRand(0.0,0.5,SeedA)
                   inverse }
         #local I=I+1; #end // end loop
      }
   }
   #macro planet_surface()
         texture { pigment { surface_base_color } }
         texture { SurfaceDetail_01 }
   #end // surface macro
#end // end surface 99

#else // if show_continents is false
	#declare planet_surface = texture { pigment { rgb <0.1,0.2,0.3> } }; //RichBlue
#end // show_continents

// ---------------------------------------------------------------------------------------
// Planet Object
// ---------------------------------------------------------------------------------------

#if (show_planet)

#declare show_map = false;
#if (show_map)
#declare map=
pigment{
  average
	pigment_map{
	  [1 image_map{ 
      #switch (surface_map_type)
        #case (1) jpeg surface_map #break
        #case (2) gif surface_map #break
        #case (3) tga surface_map #break
        #case (4) sys surface_map #break
        #case (5) tiff surface_map #break
      #end
		  map_type 1
		  interpolate 4
	    }
	  scale planet_radius //planet_radius
	  ]
  }
}

#ifdef (surface_bump_map)
   #declare object_bump =
   normal {
      bump_map {
         #switch (surface_map_type)
            #case (1) jpeg surface_bump_map #break
            #case (2) gif surface_bump_map #break
            #case (3) tga surface_bump_map #break/data/svn/vegastrike/masters/textures/planets
            #case (4) sys surface_bump_map #break
            #case (5) tiff surface_bump_map #break
         #end
         map_type 1
         interpolate 4
         bump_size 5.0
      }
   }
#end
#end

#if (surface_type>0)
  #declare planet = sphere {<0, 0, 0>, planet_radius
     #if (show_map)
        //pigment { map }
        //#ifdef (surface_bump_map) normal { object_bump } #end
        finish { surface_finish }
     # else
        #switch (surface_type) //surface_type
           #range (2,2)  planet_surface() #break 
           #range (9,30) planet_surface() #break
           #else texture { planet_surface }
        #end
        #switch (surface_type) //surface_type
           //#case (1)    finish { surface_finish } #break
           #range (3,9) finish { surface_finish } #break
           //#else texture { planet_surface }
        #end
     #end
     hollow no
     no_reflection
  }

  #ifdef (CAMERA)
     #if ((CAMERA=6) & (show_weather=true))
     #else
        object{planet rotate planet_rotation translate planet_translation}
     #end
  #else
     object{planet rotate planet_rotation translate planet_translation}
  #end
#end

#end

// ---------------------------------------------------------------------------------------
// Weather Clouds
// ---------------------------------------------------------------------------------------

#if (show_weather)

//#local cloud_intensity = 1;

#switch (cloud_type)
   #case (1)
      #declare Clouds1 = pigment {
        bozo
        turbulence 2
        color_map {
          [0.0 cloud_base_color filter 1 ]
          [0.45 cloud_base_color filter 1 ]
          [0.54 cloud_base_color*0.90*cloud_intensity]
          [0.55 cloud_base_color*0.95*cloud_intensity]
          [0.60 cloud_base_color*cloud_intensity]
          [1.0 cloud_base_color*cloud_intensity] // inside
        }
        scale 0.2
      }
      
      #declare Clouds2 = pigment {
        crackle
        turbulence 2
        color_map {
          [0.0 cloud_base_color filter 1]
          [0.10 cloud_base_color filter 1]
          [0.60 cloud_base_color*0.90*cloud_intensity]
          [0.65 cloud_base_color*cloud_intensity]
          [0.90 cloud_base_color filter 1]
          [1.0 cloud_base_color filter 1]
          }
        scale 0.8
      }
      
      #declare Clouds3 = pigment {
        dents
        turbulence 3
        color_map {
          [0.0 cloud_base_color filter 1 ]
          [0.5 cloud_base_color*cloud_intensity]
          [0.7 cloud_base_color*cloud_intensity]
          [0.8 cloud_base_color filter 1]
          [1.0 cloud_base_color filter 1]
        }
        scale 0.5
      }
      
      #declare Clouds4 = pigment {
        granite
        turbulence 0.5
        color_map {
          [0.0 cloud_base_color filter 1]
          [0.4 cloud_base_color filter 1]
          [0.6 cloud_base_color*cloud_intensity]
          [0.8 cloud_base_color*cloud_intensity]
          [1.0 cloud_base_color filter 1]
        }
        scale 0.5
      }
      
      #declare CloudArea = texture {
        pigment {
          gradient y
          pigment_map {
            [0.00 Clouds1]
            [0.25 Clouds2]
            [0.50 Clouds3]
            [0.75 Clouds4]
            [1.00 Clouds1]
          }
        }
      }
   #break
   #case (2)
      #declare global02 =
        pigment {
           wrinkles
             color_map {
               [0.00 cloud_base_color*cloud_intensity transmit 0] //cloud
               [0.35 cloud_base_color*0.8*cloud_intensity transmit 0.5]
               [0.55 cloud_base_color transmit 1.0]
             }
             turbulence 0.65
             scale 0.5
             phase 0.9
      }
      #declare continental01 = texture {
        pigment {
          granite
          color_map {
            [0.0 cloud_base_color*cloud_intensity transmit 0]
            [0.3 cloud_base_color*0.8*cloud_intensity transmit 0.9]
            [0.4 cloud_base_color transmit 1]
          }
          scale 1.2
          turbulence 0.1
        }
        finish { surface_finish }
      }
      #declare continental02 = texture {
        pigment {
          granite
          color_map {
            [0.0 cloud_base_color*cloud_intensity transmit 0]
            [0.15 cloud_base_color*0.8*cloud_intensity transmit 0.9]
            [0.20 cloud_base_color transmit 1]
          }
          scale 1
          turbulence 0.2
        }
        finish { surface_finish }
      }
      #declare continental03 = texture {
        pigment {
           bozo
             color_map {
               [0.0 cloud_base_color*cloud_intensity transmit 0] //cloud
               [0.18 cloud_base_color*cloud_intensity transmit 0.8] //cloud
               [0.45 cloud_base_color transmit 1]
             }
             turbulence 2.9
             scale 0.4
        }
        finish { surface_finish }
      }
      #declare continental04 =
        pigment {
           bumps
             color_map {
               [0.00 cloud_base_color*cloud_intensity transmit 0] //cloud
               [0.25 cloud_base_color*0.8*cloud_intensity transmit 0.9]
               [0.35 cloud_base_color transmit 1]
             }
             turbulence 2
             scale 0.4
      }
      #declare continental05 = texture {
        pigment {
          granite
          color_map {
            [0.0 cloud_base_color*cloud_intensity transmit 0]
            [0.35 cloud_base_color*0.8*cloud_intensity transmit 0.9]
            [0.45 cloud_base_color transmit 1]
          }
          scale 2
          turbulence 0.5
        }
        finish { surface_finish }
      }
      #declare local01 =
        pigment {
           bumps
             color_map {
               [0.00 cloud_base_color*cloud_intensity transmit 0] //cloud
               [0.45 cloud_base_color*0.8*cloud_intensity transmit 0.9]
               [0.65 cloud_base_color transmit 1]
             }
             turbulence 2
             scale 0.1
      }
      #declare local02 = texture {
        pigment {
          granite
          color_map {
            [0.0 cloud_base_color*cloud_intensity transmit 0] //cloud
            [0.20 cloud_base_color*cloud_intensity transmit 0.9] //cloud
            [0.35 cloud_base_color transmit 1]
          }
          turbulence 0.2
          phase 0.01
        }
        finish { surface_finish }
      }
      #declare local03 = texture {
        pigment {
           bozo
             color_map {
               [0.0 cloud_base_color*cloud_intensity transmit 0] //cloud
               [0.20 cloud_base_color*cloud_intensity transmit 0.9] //cloud
               [0.25 cloud_base_color transmit 1.0]
             }
             turbulence 5.0
             scale 0.4
             phase 0.01
        }
        finish { surface_finish }
      }
      #declare CloudArea = 
         texture { local01 }
         texture { local02 }
         texture { local03 }
         texture { continental01 }
         texture { continental02 }
         texture { continental03 }
         texture { continental04 }
         texture { continental05 }
         texture { global02 }
   #break
   #case (3) //global stripe clouds
      #declare cloud = texture {
         pigment {
            bozo
            color_map {
               [0.0 cloud_base_color transmit 1.0]
               [0.5 cloud_base_color transmit 1.0]
               [0.6 cloud_base_color*cloud_intensity] //cloud edges
               [1.0 cloud_base_color*0.5*cloud_intensity] //cloud interior
            } // end of color_map
            turbulence RRand(0.1, 1.5, SeedA)
            scale <0.4, 0.02, 0.4>
            //phase 0.01
         } // end of pigment
         finish { surface_finish }
      }
      #declare CloudArea = 
         texture { cloud }
   #break
   #case (4) //global stripe clouds with varying color
      #declare cloud = texture {
         pigment {
            bozo
            color_map {
               [0.0 cloud_base_color transmit 1.0]
               [0.5 cloud_base_color transmit 1.0]
               //[0.6 color rgb cloud_base_color*cloud_intensity] //cloud edges
               //[1.0 color rgb cloud_base_color*0.5*cloud_intensity] //cloud interior
               #local color_delta_max = 10;
               #local loop_max = 1.0;
               #local I=0.6; #while(I<=loop_max) // start loop            
                  #local pigm_delta_r = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #local pigm_delta_g = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #local pigm_delta_b = RRand(-color_delta_max/255, color_delta_max/255, SeedA);
                  #local cloud_new_color_r = cloud_base_color.red + pigm_delta_r;
                  #local cloud_new_color_g = cloud_base_color.green + pigm_delta_g;
                  #local cloud_new_color_b = cloud_base_color.blue + pigm_delta_b;
                  #local cloud_new_color = color rgb <cloud_new_color_r,cloud_new_color_g,cloud_new_color_b>;
                  [I cloud_new_color*RRand(0.8,1.0,SeedA)*cloud_intensity transmit RRand(0.5,0.9,SeedA) ] //cloud transmit 0.0,0.5
               #local I=I+0.05; #end // end loop
            } // end of color_map
            turbulence RRand(0.1, 1.0, SeedA)
            scale <0.4, RRand(0.01,0.03,SeedA), 0.4>
            //phase 0.01
         } // end of pigment
         finish { surface_finish }
      }
      #declare CloudArea = 
         texture { cloud }
   #break
   #case (5) //user-defined cloud sequence of random clouds
      #declare Clouds01 = texture { 
         pigment {
            bozo
            turbulence 2
            color_map {
               [0.0 cloud_base_color filter 1 ]
               [0.45 cloud_base_color filter 1 ]
               [0.54 cloud_base_color*0.90*cloud_intensity]
               [0.55 cloud_base_color*0.95*cloud_intensity]
               [0.60 cloud_base_color*cloud_intensity]
               [1.0 cloud_base_color*cloud_intensity] // inside
            }
            scale 0.2
         }
         finish { surface_finish }
       }
      
      #declare Clouds02 = texture {
         pigment {
            crackle
            turbulence 2
            color_map {
               [0.0 cloud_base_color filter 1]
               [0.10 cloud_base_color filter 1]
               [0.60 cloud_base_color*0.90*cloud_intensity]
               [0.65 cloud_base_color*cloud_intensity]
               [0.90 cloud_base_color filter 1]
               [1.0 cloud_base_color filter 1]
            }
            scale 0.8
         }
         finish { surface_finish }
       }
      
      #declare Clouds03 = texture {
         pigment {
            dents
            turbulence 3
            color_map {
               [0.0 cloud_base_color filter 1 ]
               [0.5 cloud_base_color*cloud_intensity]
               [0.7 cloud_base_color*cloud_intensity]
               [0.8 cloud_base_color filter 1]
               [1.0 cloud_base_color filter 1]
            }
            scale 0.5
         }
         finish { surface_finish }
       }
      
      #declare Clouds04 = texture {
         pigment {
            granite
            turbulence 0.5
            color_map {
               [0.0 cloud_base_color filter 1]
               [0.4 cloud_base_color filter 1]
               [0.6 cloud_base_color*cloud_intensity]
               [0.8 cloud_base_color*cloud_intensity]
               [1.0 cloud_base_color filter 1]
            }
            scale 0.5
         }
         finish { surface_finish }
       }

      #declare Clouds05 =
        pigment {
           wrinkles
             color_map {
               [0.00 cloud_base_color*cloud_intensity transmit 0] //cloud
               [0.35 cloud_base_color*0.8*cloud_intensity transmit 0.5]
               [0.55 cloud_base_color transmit 1.0]
             }
             turbulence 0.65
             scale 0.5
             phase 0.9
      }
      #declare Clouds06 = texture {
        pigment {
          granite
          color_map {
            [0.0 cloud_base_color*cloud_intensity transmit 0]
            [0.3 cloud_base_color*0.8*cloud_intensity transmit 0.9]
            [0.4 cloud_base_color transmit 1]
          }
          scale 1.2
          turbulence 0.1
        }
        finish { surface_finish }
      }
      #declare Clouds07 = texture {
        pigment {
          granite
          color_map {
            [0.0 cloud_base_color*cloud_intensity transmit 0]
            [0.15 cloud_base_color*0.8*cloud_intensity transmit 0.9]
            [0.20 cloud_base_color transmit 1]
          }
          scale 1
          turbulence 0.2
        }
        finish { surface_finish }
      }
      #declare Clouds08 = texture {
        pigment {
           bozo
             color_map {
               [0.0 cloud_base_color*cloud_intensity transmit 0] //cloud
               [0.18 cloud_base_color*cloud_intensity transmit 0.8] //cloud
               [0.45 cloud_base_color transmit 1]
             }
             turbulence 2.9
             scale 0.4
        }
        finish { surface_finish }
      }
      #declare Clouds09 =
        pigment {
           bumps
             color_map {
               [0.00 cloud_base_color*cloud_intensity transmit 0] //cloud
               [0.25 cloud_base_color*0.8*cloud_intensity transmit 0.9]
               [0.35 cloud_base_color transmit 1]
             }
             turbulence 2
             scale 0.4
      }
      #declare Clouds10 = texture {
        pigment {
          granite
          color_map {
            [0.0 cloud_base_color*cloud_intensity transmit 0]
            [0.35 cloud_base_color*0.8*cloud_intensity transmit 0.9]
            [0.45 cloud_base_color transmit 1]
          }
          scale 2
          turbulence 0.5
        }
        finish { surface_finish }
      }
      #declare Clouds11 =
        pigment {
           bumps
             color_map {
               [0.00 cloud_base_color*cloud_intensity transmit 0] //cloud
               [0.45 cloud_base_color*0.8*cloud_intensity transmit 0.9]
               [0.65 cloud_base_color transmit 1]
             }
             turbulence 2
             scale 0.1
      }
      #declare Clouds12 = texture {
        pigment {
          granite
          color_map {
            [0.0 cloud_base_color*cloud_intensity transmit 0] //cloud
            [0.20 cloud_base_color*cloud_intensity transmit 0.9] //cloud
            [0.35 cloud_base_color transmit 1]
          }
          turbulence 0.2
          phase 0.01
        }
        finish { surface_finish }
      }
      #declare Clouds13 = texture {
        pigment {
           bozo
             color_map {
               [0.0 cloud_base_color*cloud_intensity transmit 0] //cloud
               [0.20 cloud_base_color*cloud_intensity transmit 0.9] //cloud
               [0.25 cloud_base_color transmit 1.0]
             }
             turbulence 5.0
             scale 0.4
             phase 0.01
        }
        finish { surface_finish }
      }

      //#declare CloudArea = 
         //texture { Clouds13 }
         #local I=0;#while(I<dimension_size(cloud_sequence,1))
            #declare CloudArea = 
               texture { Clouds13 rotate <RRand(0,360,SeedA),RRand(0,360,SeedA),RRand(0,360,SeedA)> }
         #local I=I+1;#end

   #break
   #else //no or too high number given
      #declare cloud = texture {
         pigment {
            bozo
            color_map {
               [0.0 cloud_base_color transmit 1.0]
               [0.5 cloud_base_color transmit 1.0]
               [0.6 cloud_base_color*cloud_intensity] //cloud edges
               [1.0 cloud_base_color*0.5*cloud_intensity] //cloud interior
            } // end of color_map
            turbulence 1.56
            scale <0.4, 0.01, 0.4>
            phase 0.01
         } // end of pigment
         finish { surface_finish }
      }
      #declare CloudArea = 
         texture { cloud }
#end //cloud_type

#declare weather_illumination = sun;

light_group {
  	light_source { weather_illumination }
	sphere {< 0, 0, 0>, 1
		texture { CloudArea }
		//finish { surface_finish }
		scale planet_radius * radius_factor_weather
		hollow
		no_reflection
		no_shadow
		rotate planet_rotation translate planet_translation
	}
  	global_lights off
}

#end

// ---------------------------------------------------------------------------------------
// Atmosphere
// ---------------------------------------------------------------------------------------

#if (show_atmosphere)

// emitting atmosphere with slope
#declare P_EmittingAtmo_2 =
	pigment {
   slope sun_location
	  color_map {
      [0.00 rgbft <0,0,0,1,0> ] // opposite to sun
      [0.50 rgbft <0,0,0,1,0> ] // perpendicular to sun
      [0.55 rgbt <1,1,1,1> ] //color rgb <0.6, 0.8, 1> filter 0 transmit 1]
      [1.00 rgbt <1,1,1,1> ] // facing the sun
    }
	}

// emitting atmosphere with slope and altitude
#declare sunset_color = rgb <210/255,150/255,90/255>;
#declare P_EmittingAtmo =
	pigment {
   slope { sun_location
    altitude sun_location, 0.9, -0.9
  }
	  color_map {
      [0.00 color rgbt 1 ] // opposite to sun
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

#declare M_Atmosphere_POLY =
media {
	emission 0.30 //<0.05,0.05,0.10>
	intervals M_Atmosphere_Intervals
	samples M_Atmosphere_Samples // more: e.g.100 => smoother
	method 3
	density {
	  spherical
		color_map {
			[0.0 color rgb <0, 0, 0> filter 0 transmit 1] // outside
			[(atmosphere_factor-1)*0.25 color atmosphere_color*1.2/planet_radius filter 1 transmit 1] // surface
			[(atmosphere_factor-1)*0.40 color atmosphere_color*2.1/planet_radius filter 1 transmit 1] // surface
			[(atmosphere_factor-1)*0.65 color atmosphere_color*4.2/planet_radius filter 1 transmit 1] // surface
			[(atmosphere_factor-1)*0.80 color atmosphere_color*6.0/planet_radius filter 1 transmit 1] // surface
			[(atmosphere_factor-1)*0.90 color atmosphere_color*10.0/planet_radius filter 1 transmit 1] // surface
			[(atmosphere_factor-1)*0.95 color atmosphere_color*13.3/planet_radius filter 1 transmit 1] // surface
			[(atmosphere_factor-1)+0.001 color atmosphere_color*20/planet_radius filter 1 transmit 1] // surface
			[(atmosphere_factor-1) color atmosphere_color*0/planet_radius filter 1 transmit 1] // surface
			[1.0 color rgb 0 transmit 1]// <0, 0, 0>] // inside
		}
		poly_wave 0.99
	}
}

//atmosphere emission with fade formula
#declare ATMO_STEPS = 9;
#declare ATMO_EXPONENT = -1.5; // realistic = -2.0; cinematographic = -1.5
#declare ATMO_STRENGTH = 20;
#declare M_Atmosphere =
media {
	emission 0.30 //<0.05,0.05,0.10>
	intervals M_Atmosphere_Intervals
	samples M_Atmosphere_Samples     // more: e.g.100 => smoother
	method 3
	density {
	  spherical
		color_map {
			[0.0 color rgb <0, 0, 0> filter 0 transmit 1] // outside
         #local I=1;#while(I<ATMO_STEPS)
            #local POS = log(10*(I+1)/(ATMO_STEPS+1));
            #local VAL = ATMO_STRENGTH-ATMO_STRENGTH*pow(1-POS,exp(ATMO_EXPONENT));
            [(atmosphere_factor-1)*POS color atmosphere_color*VAL/planet_radius filter 1 transmit 1]
         #local I=I+1;#end
			[(atmosphere_factor-1) color atmosphere_color*ATMO_STRENGTH/planet_radius filter 1 transmit 1] // surface
			[(atmosphere_factor-1) color atmosphere_color*0/planet_radius filter 1 transmit 1] // surface
			[1.0 color rgb 0 transmit 1]// <0, 0, 0>] // inside
		}
	}
}

// sphere for atmosphere
sphere { < 0, 0, 0>, 1
	no_shadow
	hollow off
  #if (show_atmosphere_type = 1)
  texture {
  // general
    pigment { P_EmittingAtmo }
  }
  #else 
  #if (show_atmosphere_type = 2)
    texture {
    // sun-side emission
      pigment { P_EmittingAtmo_2 }
    }
	#else
    // all-sides emission
	  pigment { color atmosphere_color transmit 1}
    // all-sides emission
    //texture { pigment { rgbt 1 } }
	#end
	#end
	no_shadow
	hollow on
	interior { media { M_Atmosphere } }
	finish { surface_finish }
	scale planet_radius * atmosphere_factor
   translate planet_translation
}

#end

// ---------------------------------------------------------------------------------------
// surface emitting atmosphere
// ---------------------------------------------------------------------------------------

#if (show_surface_emission)
#local transmit_value = 0.3;
sphere {< 0, 0, 0>, 1
  texture {
	pigment {
	  slope { <0,0,1> } // slope direction: z = away from camera
    color_map {
      [0.0 color atmosphere_color filter 0 transmit 1] // opposite to direction (view)
      [0.3 color atmosphere_color filter 0 transmit 1] 
      [0.5 color atmosphere_color filter 0 transmit transmit_value] // perpendicular to direction, on the edges
      [1.0 color atmosphere_color filter 0 transmit 1] // parallel to direction (hidden)
    }
	}
  }
  finish { surface_finish }
	scale planet_radius * radius_factor_surface_emission
   translate planet_translation
	hollow
	no_shadow
} 
#end

// ---------------------------------------------------------------------------------------
// Background
// ---------------------------------------------------------------------------------------

#if (show_background)

/*
sky_sphere {
pigment { average pigment_map { 
    [1.0 pigment {
        granite
        color_map {
            [ 0.000  0.270 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.270  0.280 color rgb <.5,.5,.4> color rgb <.8,.8,.4> ]
            [ 0.280  0.470 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.470  0.480 color rgb <.4,.4,.5> color rgb <.4,.4,.8> ]
            [ 0.480  0.680 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.680  0.690 color rgb <.5,.4,.4> color rgb <.8,.4,.4> ]
            [ 0.690  0.880 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.880  0.890 color rgb <.5,.5,.5> color rgb < 1, 1, 1> ]
            [ 0.890  1.000 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
        }
    turbulence 10
    sine_wave
    scale 1e-8 * image_width * image_height
    } ]
    [1.0 pigment {
        granite
        color_map {
            [ 0.000  0.270 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.270  0.280 color rgb <.5,.5,.4> color rgb <.8,.8,.4> ]
            [ 0.280  0.470 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.470  0.480 color rgb <.4,.4,.5> color rgb <.4,.4,.8> ]
            [ 0.480  0.680 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.680  0.690 color rgb <.5,.4,.4> color rgb <.8,.4,.4> ]
            [ 0.690  0.880 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.880  0.890 color rgb <.5,.5,.5> color rgb < 1, 1, 1> ]
            [ 0.890  1.000 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
        }
    turbulence 20
    poly_wave 0.5
    scale 1e-6 * image_width * image_height
    } ]
    } }
}
*/

#declare SKY_PIGMENT_LOW = pigment {
        granite
        color_map {
            [ 0.000  0.270 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.270  0.280 color rgb <.5,.5,.4> color rgb <.8,.8,.4> ]
            [ 0.280  0.470 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.470  0.480 color rgb <.4,.4,.5> color rgb <.4,.4,.8> ]
            [ 0.480  0.680 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.680  0.690 color rgb <.5,.4,.4> color rgb <.8,.4,.4> ]
            [ 0.690  0.880 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.880  0.890 color rgb <.5,.5,.5> color rgb < 1, 1, 1> ]
            [ 0.890  1.000 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
        }
    turbulence 10
    sine_wave
    scale 1e-8 * image_width * image_height
    }

#declare SKY_PIGMENT_HIGH = pigment {
        granite
        color_map {
            [ 0.000  0.270 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.270  0.280 color rgb <.5,.5,.4> color rgb <.8,.8,.4> ]
            [ 0.280  0.470 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.470  0.480 color rgb <.4,.4,.5> color rgb <.4,.4,.8> ]
            [ 0.480  0.680 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.680  0.690 color rgb <.5,.4,.4> color rgb <.8,.4,.4> ]
            [ 0.690  0.880 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
            [ 0.880  0.890 color rgb <.5,.5,.5> color rgb < 1, 1, 1> ]
            [ 0.890  1.000 color rgb < 0, 0, 0> color rgb < 0, 0, 0> ]
        }
    turbulence 20
    poly_wave 0.5
    scale 1e-7 * image_width * image_height
    }


sky_sphere {
   pigment {
      bozo
      pigment_map { 
         [0.00 SKY_PIGMENT_LOW ]
         [0.45 SKY_PIGMENT_HIGH ]
      }
   }
}

#end

#if (show_debug)
    #debug "//- END: Debug ----------------------------------------------------------------//\n"
#end

//EOF