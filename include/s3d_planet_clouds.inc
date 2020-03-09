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
// Persistence of Vision Ray Tracer Scene Description Include File
// @file    : s3d_planet_clouds.inc
// @brief   : Planet weather and clouds generator
// @version : 2019-05-25
// @created : 2011-04-04
// @author  : pyramid
// @internet: https://openteq.wordpress.com/portfolio/space3d/
// @scale   : 1 POV unit = 1 km
// ---------------------------------------------------------------------------
// MACROS
//  Clouds(fDensity, fRadius, cCloudColor, rSeed)
//    Creates a cloud sphere with given density, radius, and cloud color
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
#include "include/s3d_math.inc"
#include "include/s3d_color.inc"

// ---------------------------------------------------------------------------------------
// User Settings
// ---------------------------------------------------------------------------------------

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

// ---------------------------------------------------------------------------------------
// Cloud Pigments
// ---------------------------------------------------------------------------------------

#macro pCloud(cCloudColor, fIntensity) pigment { dents turbulence 3.0 scale 2 color_map {
    #local fPos = 0.0; #while(fPos<=1.0)
        [fPos cCloudColor*fCloudIntensity*RRand(0.9,1.1,rSeed) transmit RRand(0.0,0.1,rSeed) ]
    #local fPos=fPos+0.05; #end
} }
#end

#macro P_Clouds1(fDensity, fCloudIntensity, cCloudColor, rSeed)
    pigment {
    GetPattern(IRand(1,10,rSeed))
    turbulence RRand(3, 5, rSeed)
    lambda RRand(3.0,4.0,rSeed) // controls graininess
    omega RRand(0.45,0.65,rSeed) // controls fineness complexity
    pigment_map {
        [0.00 cCloudColor transmit 1 ]
        [(1-fDensity) cCloudColor transmit 1 ]
        #declare pPgm = pCloud(cCloudColor, 0.9);
        [(1-fDensity+0.09) pPgm ]
        #declare pPgm = pCloud(cCloudColor, 0.95);
        [(1-fDensity+0.10) pPgm ]
        #declare pPgm = pCloud(cCloudColor, 1.0);
        [(1-fDensity+0.15) pPgm ]
        [1.00 pPgm ] // inside
    }
    #declare fScale = RRand(0.6,0.8,rSeed);
    scale <fScale*RRand(0.6,1.4,rSeed), fScale*RRand(0.6,1.4,rSeed), fScale*RRand(0.6,1.4,rSeed)>
    }
#end

#macro P_Clouds2(fDensity, fCloudIntensity, cCloudColor, rSeed)
    pigment {
    wrinkles
    turbulence RRand(3, 5, rSeed)
    lambda RRand(3.0,4.0,rSeed) // controls graininess
    omega RRand(0.45,0.65,rSeed) // controls fineness complexity
    pigment_map {
        [0.00 cCloudColor transmit 1 ]
        [(1-fDensity) cCloudColor transmit 1 ]
        #declare pPgm = pCloud(cCloudColor, 0.9);
        [(1-fDensity+0.09) pPgm ]
        #declare pPgm = pCloud(cCloudColor, 0.95);
        [(1-fDensity+0.10) pPgm ]
        #declare pPgm = pCloud(cCloudColor, 1.0);
        [0.8 pPgm ]
        [1.0 pPgm ]
    }
    #declare fScale = RRand(0.6,0.8,rSeed);
    scale <fScale*RRand(0.6,1.4,rSeed), fScale*RRand(0.6,1.4,rSeed), fScale*RRand(0.6,1.4,rSeed)>
    } 
#end

#macro P_Clouds3(fDensity, fCloudIntensity, cCloudColor, rSeed)
    pigment {
    GetPattern(IRand(1,10,rSeed))
    turbulence RRand(3, 5, rSeed)
    lambda RRand(3.0,5.0,rSeed) // controls graininess
    omega RRand(0.45,0.65,rSeed) // controls fineness complexity
    pigment_map {
        #declare pPgm = pCloud(cCloudColor, 1.0);
        [0.00 pPgm transmit 1 ]
        [(1-fDensity-0.10) pPgm transmit 1 ]
        #declare pPgm = pCloud(cCloudColor, 0.8);
        [(1-fDensity) pPgm ]
        #declare pPgm = pCloud(cCloudColor, 1.0);
        [(1-fDensity+0.10) pPgm ]
    }
    #declare fScale = RRand(0.6,0.8,rSeed);
    scale <fScale*RRand(0.6,1.4,rSeed), fScale*RRand(0.6,1.4,rSeed), fScale*RRand(0.6,1.4,rSeed)>
    }
#end

#macro P_Clouds4(fDensity, fCloudIntensity, cCloudColor, rSeed)
    pigment {
    bozo
    pigment_map {
        [0.0 cCloudColor transmit 1 ]
        [(1-fDensity) cCloudColor transmit 1 ]
        #local color_delta_max = 10;
        #local loop_max = 1.0;
        #local I=(1-fDensity); #while(I<=loop_max) // start loop            
            #local cNewCol = VariateColor(cCloudColor, 10, 1, rSeed);
            //[I cNewCol*RRand(0.8,1.0,rSeed)*fCloudIntensity transmit RRand(0.5,0.9,rSeed) ] //cloud transmit 0.0,0.5
            #declare pPgm = pCloud(cNewCol, fCloudIntensity);
            [I pPgm ] //cloud transmit 0.0,0.5
        #local I=I+0.05; #end // end loop
    } // end of color_map
    turbulence RRand(3, 5, rSeed)
    lambda RRand(3.0, 5.0, rSeed)
    omega RRand(0.45, 0.65, rSeed)
    #declare fScale = RRand(0.2,0.6,rSeed);
    scale <fScale*RRand(0.6,1.4,rSeed), fScale*RRand(0.6,1.4,rSeed), fScale*RRand(0.6,1.4,rSeed)>
    } // end of pigment
#end

#macro P_CloudArea1(fDensity, fIntensity, cCloudColor, rSeed)
    #declare pPigment = array[5];
    #declare pPigment[0] = P_Clouds1(fDensity, fIntensity, cCloudColor, rSeed);
    #declare pPigment[1] = P_Clouds2(fDensity, fIntensity, cCloudColor, rSeed);
    #declare pPigment[2] = P_Clouds3(fDensity, fIntensity, cCloudColor, rSeed);
    #declare pPigment[3] = P_Clouds4(fDensity, fIntensity, cCloudColor, rSeed);
        pigment { gradient y 
          pigment_map {
            [0.00 pPigment[0] ]
            [0.25 pPigment[1] ]
            [0.50 pPigment[2] ]
            [0.75 pPigment[3] ]
            [1.00 pPigment[0] ]
          }
        }
#end

#macro P_CloudArea2(fDensity, fIntensity, cCloudColor, rSeed)
    #declare pPigment = array[5];
    #declare pPigment[0] = P_Clouds1(fDensity, fIntensity, cCloudColor, rSeed);
    #declare pPigment[1] = P_Clouds2(fDensity, fIntensity, cCloudColor, rSeed);
    #declare pPigment[2] = P_Clouds3(fDensity, fIntensity, cCloudColor, rSeed);
    #declare pPigment[3] = P_Clouds4(fDensity, fIntensity, cCloudColor, rSeed);
    
    #declare iLatZones = 4;
    #declare iLonZones = 8;
        pigment { gradient y phase 0.5 scale 2
          pigment_map {
            #local fStepY = 0.0; #while(fStepY<=1.0)
                #declare pLon = pigment { radial pigment_map {
                    #local fStepR = 0.0; #while(fStepR<=1.0)
                        [fStepR pPigment[IRand(0,3,rSeed)] ]
                    #local fStepR=fStepR+iLonZones/4; #end
                } }
                [fStepY pLon ]
            #local fStepY=fStepY+iLatZones/4; #end
          }
        } 
#end

// ---------------------------------------------------------------------------------------
// Weather Clouds
// ---------------------------------------------------------------------------------------

#macro Clouds(fDensity, fRadius, cCloudColor, rSeed)

  //#declare Cloud = array [10];
  #declare layers = fDensity*10+IRand(2,10,rSeed);
  #declare fIntensity = RRand(1.0,1.2,rSeed);

    #ifndef(sun)
    #end
    #ifdef(sun)
        #declare weather_illumination = sun;
        light_group {
            light_source { weather_illumination }
            sphere {< 0, 0, 0>, 1
                #declare iLayer=1; #while (iLayer<=layers)
                    texture {
                        #declare iCloud = IRand(5,6,rSeed);
                        #switch(iCloud)
                            #case(1) P_Clouds1(fDensity, fIntensity, cCloudColor, rSeed) #break
                            #case(2) P_Clouds2(fDensity, fIntensity, cCloudColor, rSeed) #break
                            #case(3) P_Clouds3(fDensity, fIntensity, cCloudColor, rSeed) #break
                            #case(4) P_Clouds4(fDensity, fIntensity, cCloudColor, rSeed) #break
                            #case(5) P_CloudArea1(fDensity, fIntensity, cCloudColor, rSeed) #break
                            #case(6) P_CloudArea2(fDensity, fIntensity, cCloudColor, rSeed) #break
                        #end
                      rotate <RRand(0,360,rSeed),RRand(0,360,rSeed),RRand(0,360,rSeed)>
                      finish { surface_finish } 
                    }
                #declare iLayer=iLayer+1; #end
                scale fRadius
                hollow
                no_reflection
                no_shadow
                //rotate planet_rotation translate planet_translation
            }
            global_lights off
        }
    #end

#end


#if (show_debug)
    #debug "//- END: Debug ----------------------------------------------------------------//\n"
#end

//EOF
