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
// @file    : s3d_stafield.inc
// @brief   : Background skysphere starfields
// @version : 2019-05-30
// @created : 2011-04-14
// @author  : pyramid
// @internet: https://openteq.wordpress.com/portfolio/space3d/
// @scale   : 1 POV unit = 1 km
// ---------------------------------------------------------------------------
//
// OBJECT TYPES
//     QuickNebula()
//     Starfield()
//     Nebula(fSize, cColors, fEmission, rShapeSeed, rColorSeed)
//
// (1) Nebula Objects:
//     - NebulaSelect(iType, iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
//        iType: 1 - CloudNebula(iNumber=1-8); 2-BackgroundNebula(iNumber=1-2); 3-RingNebula(iNumber=1)
//        cColors: an array of input colors; can use predefined NEBULA_COLORS
//        fEmission: emission strength (0.1-1.0)
//        rShapeSeed, rColorSeed: random seeds
//     You can also use directly the macros mCloudNebula01-08, mRingNebula01, mBackgroundNebula01-02
// (2) Star Cluster Objects:
//     - StarCluster(fSizeMin, fSizeMax, iStarAmount, aStarColors, fIntensity, fDistributionAngle, vOrientation, vExcentricity, rSeed) 
//       to use as distant background star objects
//       replaces O_StarCluster01-07
//     - StarConcentration(iType, fSizeMin, fSizeMax, iAmount, cColors, fIntensity, fThicknessPercent, rSeed)
//       replaces O_StarConcentration01 to O_StarConcentration02 to use as star concentrations
//       replaces O_StarField01 to O_StarField03
// (3) sky_shpere Pigments:
//     - P_StarFieldNN(cColor, fIntensity)
//          replaces P_StarField01-05
//     - P_StarNebulaNN(aColors, fIntensity, vExcentricity, rSeed)
//          replaces P_StarNebula01 to P_StarNebula04 to use with sky_sphere
//     - P_CloudNebulaNN(aColors, fIntensity, vExcentricity, rSeed)
//          replaces P_CloudNebula01 to P_CloudNebula04 to use with sky_sphere
//     - obsolete P_StarCluster01 to P_StarCluster03 (very slow)
//          use O_StarCluster instead
//
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Global Settings
// ---------------------------------------------------------------------------
#version 3.6;

// ---------------------------------------------------------------------------
// Include Files
// ---------------------------------------------------------------------------
#include "rand.inc" // random number generation macros
#include "math.inc" // math function macros
#include "shapes.inc"
#include "include/s3d_color.inc" //random color macros

// ---------------------------------------------------------------------------
// User Settings
// ---------------------------------------------------------------------------

// Quality Settings for test & sample or final rendering
#ifndef (RENDER_QUALITY)
  #declare RENDER_QUALITY = 1; // 0=fast; 1=full
#else
  #if (RENDER_QUALITY = 1)
    #declare RENDER_QUALITY = 1; // 0=fast; 1=full
  #else
    #declare RENDER_QUALITY = 0; // 0=fast; 1=full
  #end
#end

#ifndef (STARFIELD_STAR_INTENSITY) #declare STARFIELD_STAR_INTENSITY = 1.0; #end
#ifndef (STARFIELD_STAR_AURA) #declare STARFIELD_STAR_AURA = rgb <0.4, 0.45, 1.0>; #end
#ifndef (STARFIELD_STAR_COLOR) #declare STARFIELD_STAR_COLOR = rgb <0.9, 0.95, 1.0>; #end
#ifndef (STARFIELD_STARSIZE_MIN) #declare STARFIELD_STARSIZE_MIN = 0.5; #end
#ifndef (STARFIELD_STARSIZE_MAX) #declare STARFIELD_STARSIZE_MAX = 1.0; #end
#ifndef (STARFIELD_STAR_AMOUNT) #declare STARFIELD_STAR_AMOUNT = 10; 
  #else #declare _SF_star_amount = STARFIELD_STAR_AMOUNT; #end
#ifndef (STARFIELD_DISTRIBU_ANGLE) #declare STARFIELD_DISTRIBU_ANGLE = 20; #end
#ifndef (STARCLUSTER_EXCENTRICITY) #declare STARCLUSTER_EXCENTRICITY = <1, 1, 1>; #end
#ifndef (STARCLUSTER_DISTRIBU_ANGLE) #declare STARCLUSTER_DISTRIBU_ANGLE = <90, 0, 0>; #end    
#ifndef (STARFIELD_STAR_TYPE) #declare STARFIELD_STAR_TYPE = 3; #end
#ifndef (STAR_COLORS) #declare STAR_COLORS = array[2]; #end

#ifndef (create_logfile)                                             
  #declare create_logfile = false;
#end
#if (create_logfile)
   #if (defined(LogFile)=false)
      #fopen LogFile "gallery/starfield.txt"
      #if(frame_number<=1) write
      #else append
      #end
   #end
   #write(LogFile,"\n[Frame_",frame_number,"]\n")
#end

// ---------------------------------------------------------------------------
// Quick Backgrounds
// ---------------------------------------------------------------------------

#macro Starfield()
  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) }
#end

#macro QuickNebula()
  #declare rSeed = seed(7777+frame_number);
  #declare rColor = seed(1102+frame_number);
  
  #declare iNumColors = IRand(1,10,rSeed);
  #declare aColors = array[iNumColors]; 
  #local c=0; #while(c<iNumColors)
    //0-red; 21-brown; 30-orange; 59-yellow; 120-green; 179-cyan; 240-blue; 300-magenta;
    #declare aColors[c] = ColorHSL(RRand(0,255,rColor),RRand(50,100,rColor),RRand(50,100,rColor));
  #local c=c+1; #end
  #declare cStarColor = rgb <0.95,0.95,1.0>;
  #declare fIntensity = RRand(0.8,1.3,rColor);
  #declare vExcentricity = <RRand(0.5,2.0,rSeed), RRand(0.5,2.0,rSeed), RRand(0.5,2.0,rSeed)>;

  #declare bStarNebula = IRand(0,1,rSeed);
  #if(bStarNebula) #declare aColors[0] = rgb <0.95,0.95,1.0>; #end
  #declare fStep = 1/iNumColors;
  #local starmap = pigment_map { // cloud
    #local c=0; #while(c<iNumColors)
      [fStep*c aColors[c] ]
    #local c=c+1; #end
    [1.0 cStarColor*10*fIntensity ] // controls star density; 0.1 =high, 0.9=low
  }

  #declare iPatternMethod = IRand(1,20,rSeed);
  #local cloudmap = pigment_map {
    [ 0.0 GetPattern(iPatternMethod) pigment_map { starmap }
      scale RRand(0.8,1.2,rSeed)
      turbulence RRand(1.0,2.0,rSeed)
      omega RRand(0.5,0.65,rSeed)
      lambda RRand(2,4,rSeed) 
    ] // controls spread
    [ 1.0 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no ext, 1=full ext
  }

  sky_sphere {
    pigment {
      #declare iPatternMethod = IRand(1,20,rSeed);
      GetPattern(iPatternMethod)
      pigment_map {
        [ 0.0 GetPattern(iPatternMethod) pigment_map { cloudmap } scale 20 turbulence 0] // controls spread
        [ RRand(0.7,1.0,rSeed) rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no ext, 1=full ext
      }
      scale RRand(0.5,5,rSeed)*vExcentricity
      turbulence RRand(1.0,2.0,rSeed)
      omega RRand(0.5,0.7,rSeed)
      lambda RRand(2,4,rSeed) 
      rotate <RRand(0,180,rSeed), RRand(0,180,rSeed), RRand(0,180,rSeed)>
    }
  }

  /*
  #declare iNebulaPigment = IRand(1,8,rSeed);
  #switch (iNebulaPigment)
    // syntax: P_StarNebulaNN(aColors, fIntensity, vExcentricity, rSeed)
    #case (1) sky_sphere { P_StarNebula01(aColors, fIntensity, vExcentricity, rSeed) } #break
    #case (2) sky_sphere { P_StarNebula02(aColors, fIntensity, vExcentricity, rSeed) } #break
    #case (3) sky_sphere { P_StarNebula03(aColors, fIntensity, vExcentricity, rSeed) } #break
    #case (4) sky_sphere { P_StarNebula04(aColors, fIntensity, vExcentricity, rSeed) } #break
    #case (5) sky_sphere { P_CloudNebula01(aColors, fIntensity, vExcentricity, rSeed) } #break
    #case (6) sky_sphere { P_CloudNebula02(aColors, fIntensity, vExcentricity, rSeed) } #break
    #case (7) sky_sphere { P_CloudNebula03(aColors, fIntensity, vExcentricity, rSeed) } #break
    #case (8) sky_sphere { P_CloudNebula04(aColors, fIntensity, vExcentricity, rSeed) } #break
  #end
  */
#end

// ---------------------------------------------------------------------------
// Star Field Pigment
// ---------------------------------------------------------------------------
#macro P_StarField(cColor, fIntensity)
  pigment {
   bozo pigment_map { 
      [ 3.0 spotted color_map {
         [0.1 cColor*2*fIntensity ] // intensity variance=(0.1 & *2); color=rgb
         [0.3 rgb 0 transmit 1 ] // density
         } scale 1e-3
      ]
      [ 3.0 granite color_map {
         [0.70 rgb 0 transmit 1]
         [1.00 cColor ]
         } scale 1e-2
      ]
      [ 3.0 leopard color_map {
         [0.50 rgb 0 transmit 1 ] // density=0.5
         [1.00 cColor ]
         } scale 1e-5 ]
   } }
#end

// ---------------------------------------------------------------------------
// Star Nebula Pigment - like a cloud nebula with embedded stars
// ---------------------------------------------------------------------------
#macro P_StarNebula(aColors, fIntensity, fStrength, vExcentricity, rSeed)
  #local star4 = pigment { wood color_map {
    [ 0.00 aColors[0]*fIntensity ]
    [ 0.10 aColors[0]*fIntensity ]
    [ 0.40 rgb 0 transmit 1 ] }
  }
  #local smap4 = pigment_map { // cloud
    [ 0.00 aColors[1] ] // cloud color
    [ RRand(0.65,0.90,rSeed) star4 ] // controls star density; 0.1 =high, 0.9=low
    [ 1.00 aColors[0]*10*fIntensity ] // controls star intensity
  }
  bozo pigment_map {
    [ 0.00 granite pigment_map { smap4 } scale 1e-4 turbulence 1] // controls spread
    [ RRand(0.50,0.70,rSeed) rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no ext, 1=full ext
  }
  turbulence fStrength*RRand(1.05,1.5,rSeed) //1.0-3.0
  lambda fStrength*RRand(1.1,1.5,rSeed) //1.1-4.5
  omega RRand(0.51,0.60+fStrength*0.07,rSeed) //0.51-0.75
  scale RRand(0.4,0.6,rSeed)*vExcentricity
#end

// ---------------------------------------------------------------------------
// Cloud Nebula Pigment
// ---------------------------------------------------------------------------
#macro P_CloudNebula(iType, aColors, fIntensity, fStrength, vExcentricity, rSeed)
// iType = 1-4
  #if (iType>4) #declare iType = 1; #end
  #if (iType<1) #declare iType = 1; #end
  #local smap = pigment_map { // cloud
    //[0.0 aColors[1] ] // cloud color
    //[1.0 aColors[1]*fIntensity ] // controls star density; 0.1 =high, 0.9=low
    //[0.00 aColors[0] ]
    #local fStart = 0.00;
    #local fStep = (1-fStart)/dimension_size(aColors,1);
    #local I=fStart; #while(I<1)      
      #local iColor = IRand(0,dimension_size(aColors,1)-1,rSeed);
      //#local iColor = int(fStart+(I-fStart)*dimension_size(aNebulaColors,1));
      [I aColors[iColor]*fIntensity ]
    #local I=I+fStep; #end      
    //[1.00 aColors[iColor] ]
  }
  #local cmap = pigment_map {
    [ 0.0 granite pigment_map { smap } scale 10 turbulence 1] // controls spread
    [ 1.0 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no ext, 1=full ext
  }
  //GetPattern2(iType)
  #switch (iType)
    #case (1)  bozo       scale 1   #break
    #case (2)  bumps      scale 1   #break
    #case (3)  spotted    scale 1   #break
    #case (4)  quilted    scale 3   #break
  #end
  pigment_map {
    [ 0.0 bozo pigment_map { cmap } scale 20 turbulence 0] // controls spread
    [ 0.7 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no ext, 1=full ext
  }
  turbulence fStrength*RRand(0.5,1.5,rSeed) //1.0-3.0
  lambda fStrength*RRand(1.1,1.5,rSeed) //1.1-4.5
  omega RRand(0.51,0.60+fStrength*0.07,rSeed) //0.51-0.75
  scale RRand(0.4,0.6,rSeed)*vExcentricity
#end

// ---------------------------------------------------------------------------
// Star Cluster Object
// ---------------------------------------------------------------------------
#macro StarCluster(fSizeMin, fSizeMax, iStarAmount, aStarColors, fIntensity, fDistributionAngle, vOrientation, vExcentricity, rSeed)
  #local fStarFieldDistance = 2e4;
  #local fTranslationRadius = fStarFieldDistance*pi*fDistributionAngle/360;
  #local iDistributionMethod = 3;
  //#local iDistributionMethod = 1;
  #if (dimension_size(aStarColors,1)<2)
    #declare cTmp = array[2];
    #declare cTmp[0] = aStarColors[0];
    #declare cTmp[1] = aStarColors[0];
    #declare aStarColors = array[2];
    #declare aStarColors = cTmp;
  #end
  union {
    #local I=0; #while (I < iStarAmount)
    triangle {<-1, -.6, 0>, <0, 1, 0>, <1, -.6, 0>
      pigment { onion pigment_map {
        #local fIntFx = RRand(0.5,1.5,rSeed);
        [0.00 aStarColors[0]*fIntensity*fIntFx transmit 0 ]
        [0.09 aStarColors[0]*aStarColors[1]*fIntensity*fIntFx transmit 0.5]
        [0.12 aStarColors[1] transmit 0.8]
        [0.19 aStarColors[1] transmit 0.93]
        [0.25 aStarColors[1] transmit 1] } poly_wave 0.5 scale 4
      }
      hollow on
      no_shadow 
      finish {ambient 1 diffuse 0 reflection 0 phong 0 specular 0 crand 0}
      // adjust scale according to screen resolution
      scale RRand(fSizeMin, fSizeMax, rSeed)*40*pow(8e3/image_width,0.4) //*40
      // produces cubic distribution with small angles
      #if (iDistributionMethod = 1)
        translate <0,0,fStarFieldDistance>
        #local r_x = RRand(-fDistributionAngle*vExcentricity.x, fDistributionAngle*vExcentricity.x, rSeed);
        #local r_y = RRand(-fDistributionAngle*vExcentricity.y, fDistributionAngle*vExcentricity.y, rSeed);
        #local r_z = RRand(-fDistributionAngle*vExcentricity.z, fDistributionAngle*vExcentricity.z, rSeed);
        rotate <r_x, r_y, r_z> rotate vOrientation
      #end
      // second distribution code
      #if (iDistributionMethod>1 & vOrientation.x=0 & vOrientation.y=0)
        #local fTranslation = RRand(0.5*fTranslationRadius, 2*fTranslationRadius, rSeed);
        #local t_x = RRand(-fTranslation, fTranslation, rSeed);
        #local t_y = RRand(-fTranslation, fTranslation, rSeed);
        #local t_z = fStarFieldDistance * RRand(0.9,1.1,rSeed);
        translate <t_x, t_y, t_z>
        #local fRotation = RRand(fDistributionAngle/2, fDistributionAngle*2,rSeed);
        #local rot_x = fRotation*RRand(-vExcentricity.x, vExcentricity.x, rSeed);
        #local rot_y = fRotation*RRand(-vExcentricity.y, vExcentricity.y, rSeed);
        #local rot_z = fRotation*RRand(-vExcentricity.z, vExcentricity.z, rSeed);
        rotate <rot_x,rot_y,rot_z> rotate vOrientation
      #end
      // third distribution code
      #if (iDistributionMethod>1 & (vOrientation.x!=0 | vOrientation.y!=0)) 
        #declare vVectorStart = <0,0,RRand(0.5,2.0,rSeed)>*sin(radians(fDistributionAngle))*fStarFieldDistance;
        #local rot_x = RRand(-180, 180,rSeed);
        #local rot_y = RRand(-180, 180,rSeed);
        #local rot_z = RRand(-180, 180,rSeed);
        #declare vVectorRotate = vrotate(vVectorStart,<rot_x,rot_y,rot_z>);
        #declare vVectorPosition = vVectorRotate*vExcentricity;
        translate vVectorStart rotate <rot_x,rot_y,rot_z>
        translate -vVectorRotate translate vVectorPosition rotate vOrientation translate <0,0,fStarFieldDistance>
      #end
    }
  #local I=I+1; #end
  }
#end


// ---------------------------------------------------------------------------
// Nebula 1
// ---------------------------------------------------------------------------
#macro mCloudNebula01(fSize, aNebulaColors, fEmission, rShapeSeed, rColorSeed)
   #if (fEmission = 0) #local fEmission=RRand(0.02,0.15,rColorSeed); #end
   sphere { < 0, 0, 0>, 2 pigment { rgbt 1 } // surface of sphere is transparent
   	interior { media { emission fEmission intervals 10 samples 25 method 3
			density { spherical ramp_wave
          turbulence RRand(1.5,6,rShapeSeed)
          octaves RRand(5,50,rShapeSeed)
          frequency RRand(1,10,rShapeSeed)
          lambda RRand(3,6,rShapeSeed)
          omega RRand(0.50,0.80,rShapeSeed)
        #local fStart = RRand(0.10, 0.50, rShapeSeed);
        #local fStep = (1-fStart)/(dimension_size(aNebulaColors,1)-1);
				color_map {
					[0.0 color rgb <0, 0, 0> transmit 1 filter 0]
          #local I=fStart; #while(I<=1)      
            #local iColor = int(fStart+(I-fStart)*dimension_size(aNebulaColors,1));
            [I aNebulaColors[iColor] transmit 1 filter 0 ]
          #local I=I+fStep; #end      
				}
			}
		} }
   	hollow
   	scale 25
   }
#end

// ---------------------------------------------------------------------------
// Nebula 2
// ---------------------------------------------------------------------------
#macro mCloudNebula02(fSize, aNebulaColors, fEmission, rShapeSeed, rColorSeed)
   #if (fEmission = 0) #local fEmission=RRand(0.015,0.110,rColorSeed); #end
   sphere { < 0, 0, 0>, 2 pigment { rgbt 1 } // surface of sphere is transparent
   	interior { media { emission fEmission intervals 1 samples 25 method 3
   		density { spherical ramp_wave
        turbulence RRand(1.5,3.5,rShapeSeed)
        octaves RRand(5,10,rShapeSeed)
        lambda RRand(2,4,rShapeSeed)
        omega RRand(0.50,0.80,rShapeSeed)
        #local fStart = RRand(0.10, 0.50, rShapeSeed);
        #local fStep = (1-fStart)/dimension_size(aNebulaColors,1);
   			color_map {
   				[0.0 color rgb <0, 0, 0> transmit 1 filter 0]
          #local I=fStart; #while(I<1)      
            #local iColor = IRand(0,dimension_size(aNebulaColors,1)-1,rColorSeed);
            [I aNebulaColors[iColor] ]
          #local I=I+fStep; #end      
   			}
   		}
   		density { spherical ramp_wave
        turbulence RRand(1.5,3.5,rShapeSeed)
        octaves RRand(5,10,rShapeSeed)
        lambda RRand(2,4,rShapeSeed)
        omega RRand(0.50,0.80,rShapeSeed)
   			color_map {
   				[0.0 color rgb 1 transmit 0 filter 0]
   				[0.2 color rgb 1 transmit 0 filter 0]
   				[0.3 color rgb 0 transmit 1 filter 0]
   				[1.0 color rgb 0 transmit 1 filter 0]
   			}
   		}
   	} }
   scale 25
   hollow
   }
#end

// ---------------------------------------------------------------------------
// Nebula 3
// ---------------------------------------------------------------------------
#macro mCloudNebula03(fSize, aNebulaColors, fEmission, rShapeSeed, rColorSeed)
  #if (fEmission = 0) #local fEmission=RRand(0.05,0.15,rColorSeed); #end
  #local fIntensity = RRand(0.2,0.5,rColorSeed);
  sphere { < 0, 0, 0>, 2 pigment { rgbt 1 } // surface of sphere is transparent
   	interior { media { emission fEmission intervals 10 samples 25 method 3 jitter 0.0 aa_threshold 0.01 aa_level 10 //scattering {1, 0.3} //samples 25
   	//interior { media { emission fEmission intervals 10 samples 2 method 3 jitter 0.0 aa_threshold 0.1 aa_level 4 //dev
   		density { spherical ramp_wave //cubic_wave //scallop_wave //sine_wave //triangle_wave //poly_wave //ramp_wave
        //translate RRand(0.0,1.0,rShapeSeed)*y  // (t*y) -> t = animation clock
        warp { turbulence RRand(1.5,5.0,rShapeSeed) } // 1.5-4.5
        //translate -RRand(0.0,1.0,rShapeSeed)*y
        turbulence RRand(1.5,3.5,rShapeSeed) //1.1-3.5
        octaves RRand(1,3,rShapeSeed) //1-5
        frequency RRand(1.5,5,rShapeSeed) //1.1-3.0
        lambda RRand(4,8,rShapeSeed) //2-8
        omega RRand(0.60,0.80,rShapeSeed) //0.5-0.8
        #local fStart = 0.01; //RRand(0.30, 0.50, rShapeSeed); //0.3-0.5
        #local fStep = (1-fStart)/dimension_size(aNebulaColors,1);
   			color_map {
           [0.00 color rgb <0, 0, 0> transmit 1 filter 0] [fStart color rgb <0, 0, 0> transmit 1]
          #local I=fStart; #while(I<=1)      
            #local iColor = IRand(0,dimension_size(aNebulaColors,1)-1,rColorSeed);
            [I aNebulaColors[iColor]*fIntensity ]
          #local I=I+fStep; #end      
   			}
   		}
  	} } //interior
  scale 25
  hollow no_shadow
  }
#end

// ---------------------------------------------------------------------------
// Nebula 4
// ---------------------------------------------------------------------------
#macro mCloudNebula04(fSize, cColors, fEmission, rShapeSeed, rColorSeed)
   #if (fEmission = 0) #local fEmission = RRand(0.02,0.11,rColorSeed); #end
   #local fStep = RRand(0.01,0.10,rShapeSeed);
   sphere { < 0, 0, 0>, 1 pigment { rgbt 1 } // surface of sphere is transparent
   	interior { media { emission fEmission intervals 1 samples 25 method 3
   		density { spherical ramp_wave
            turbulence RRand(1.5,2.5,rShapeSeed)
            octaves RRand(5,50,rShapeSeed)
            frequency RRand(1,10,rShapeSeed)
            lambda RRand(2,4,rShapeSeed)
            omega RRand(0.50,0.80,rShapeSeed)
            color_map {
               [ 0.0  color rgbft <0.0, 0.0, 0.0, 0.0, 1.0> ]
               #local I=0.15; #while (I<=1)
                  //#local rColor = color rgb <RRand(0.2,0.6,rColorSeed), RRand(0.2,0.5,rColorSeed), 1.0>; //blueish
                  //[ I rColor transmit RRand(0.0,0.5,rShapeSeed) filter RRand(0.0,1.0,rShapeSeed) ]
                  #local iColor = IRand(0,1,rColorSeed);
                  [ I cColors[iColor] transmit RRand(0.0,0.5,rShapeSeed) filter RRand(0.0,1.0,rShapeSeed) ]
               #local I=I+fStep; #end
            }
         //scale 0.5/sqrt(fSize) //0.07
         scale 0.5/sqrt(fSize)
   		}
   	} } //interior
   scale 40*fSize
   hollow
   } //object
#end

// ---------------------------------------------------------------------------
// Nebula 5
// ---------------------------------------------------------------------------
#macro mCloudNebula05(fSize, cColors, fEmission, rShapeSeed, rColorSeed)
   #if (fEmission = 0) #local fEmission = RRand(0.02,0.10,rColorSeed); #end
   #local fStrength = 1.0; 
   #local fStep = RRand(0.02,0.15,rShapeSeed);
   sphere { < 0, 0, 0>, 4 pigment { rgbt 1 } // transparent surface
   	//interior { media { emission fEmission intervals 1 samples 33 method 3 jitter 0.5
   	interior { media { emission fEmission intervals 1 samples 25 method 3 jitter 0.001
   		density { spherical ramp_wave
            translate RRand(0.0,1.0,rShapeSeed)*y  // (t*y) -> t = animation clock
            warp { turbulence RRand(1.5,5.0,rShapeSeed) }
            translate -RRand(0.0,1.0,rShapeSeed)*y
            turbulence RRand(2.55,3.60,rShapeSeed)*fStrength
            octaves RRand(2,5,rShapeSeed)*fStrength
            frequency RRand(2,15,rShapeSeed)*fStrength
            lambda RRand(4.1,8.5,rShapeSeed)*fStrength
            omega RRand(0.75,0.95,rShapeSeed)*fStrength
            color_map {
               [ 0.0  color rgb <0,0,0> transmit 1 ] [ 0.1  color rgb 1 transmit 1 ]
               #local I=0.1; #while (I<=1.0)
                  #local iColor = IRand(0,1,rColorSeed);
                  [ I cColors[iColor] transmit 0 filter 0 ]
               #local I=I+fStep; #end
            }
   		} //density
      scale 0.7/sqrt(fSize)
			density { spherical ramp_wave
            turbulence RRand(2.45,3.30,rShapeSeed)*fStrength
            octaves RRand(2,4,rShapeSeed)*fStrength
            frequency RRand(2,4,rShapeSeed)*fStrength
            lambda RRand(4.1,8.5,rShapeSeed)*fStrength
            omega RRand(0.75,0.95,rShapeSeed)*fStrength
            color_map {
               [ 0.0  color rgb 1 transmit 1] [ 0.2  color rgb 1 transmit 1 ]
               #local I=0.2; #while (I<=1)
                  #local iColor = IRand(0,1,rColorSeed);
                  [ I cColors[iColor] transmit 0 filter 0 ]
               #local I=I+fStep; #end
            }
   		} //density
			density { spherical ramp_wave
            turbulence RRand(2.55,3.0,rShapeSeed)
            octaves RRand(2,10,rShapeSeed)*fStrength
            frequency RRand(2,10,rShapeSeed)*fStrength
            lambda RRand(4.1,8.0,rShapeSeed)*fStrength
            omega RRand(0.75,0.95,rShapeSeed)*fStrength
            color_map {
               [ 0.0  color rgb 1 ] [ 0.1  color rgb 1 transmit 1]
               #local I=0.1; #while (I<=1)
                  #local iColor = IRand(0,1,rColorSeed);
                  [ I cColors[iColor] transmit 0 filter 0 ]
               #local I=I+fStep; #end
            }
   		} //density
   	} } //interior
   scale 20*fSize
   hollow
   } //object
#end

// ---------------------------------------------------------------------------
// Nebula 6
// ---------------------------------------------------------------------------
/*Demo scene showing usage of CIE.inc and LightsysIV for space scenes. 
Creates a starfield with colors of known kelvin temperatures, and a 
planetary nebulae with real elements colors.
Jaime Vives Piqueres, Apr-2003. */
//#undef f_Nebulae
#macro mCloudNebula06(fSize, cColors, fEmission, r_u, rColorSeed)
   // nebulae shape functions
   #declare dp=100*rand(r_u);
   #declare f_Nebulae = function { pigment {
   //  spherical
     spiral1 4
     pigment_map {
      [0 crackle 
         translate dp 
         scale 25 warp{turbulence 1} scale 1/25
         warp{spherical}
      ]
      [dp*.1 marble 
         translate dp*2 
         scale 25 warp{turbulence 1} scale 1/25
         warp{spherical}
      ]
      [1 bumps 
         translate dp/2 
         scale 25 warp{turbulence 1} scale 1/25
         warp{spherical}
      ]
     }
    // scale .5
    }
   }
   
   // basic nebulae density
   #declare d_nebulae_emission=
   density { function { f_Nebulae(abs(x),abs(y),abs(z)).gray}
      density_map {
         [0.00 rgb 0]
         [.10 rgb <1.0, 0.4518, 0.1368>] //LS_Carbon
            #if (rand(r_u)>.5) [.1+.05*rand(r_u) rgb 0] #end
            #if (rand(r_u)>.5) [.15+.10*rand(r_u) rgb 0] #end
         [.25 rgb <1.0, 0.4594, 0.5463>] //LS_Helium
            #if (rand(r_u)>.5) [.25+.05*rand(r_u) rgb 0] #end
            #if (rand(r_u)>.5) [.30+.10*rand(r_u) rgb 0] #end
         [.40 rgb <1.0, 0.2313, 0.9852>] //LS_Hydrogen
            #if (rand(r_u)>.5) [.40+.05*rand(r_u) rgb 0] #end
            #if (rand(r_u)>.5) [.45+.10*rand(r_u) rgb 0] #end
         [.55 rgb <1.0, 0.2378, 0.0300>] //LS_Neon
            #if (rand(r_u)>.5) [.55+.05*rand(r_u) rgb 0] #end
            #if (rand(r_u)>.5) [.60+.10*rand(r_u) rgb 0] #end
         [.70 rgb <0.6617, 0.5097, 1.0>] //LS_Krypton
            #if (rand(r_u)>.5) [.70+.05*rand(r_u) rgb 0] #end
            #if (rand(r_u)>.5) [.75+.10*rand(r_u) rgb 0] #end
         [.85 rgb <1.0, 0.3007, 0.0494>] //LS_Oxygen
            #if (rand(r_u)>.5) [.85+.15*rand(r_u) rgb 0] #end
         [1.00 rgb 0]
      } 
      phase rand(r_u)
   }
   
   // fade basic density spherically
   #declare ttmp=100*rand(r_u);
   #declare d_sph_neb_emission = density { spherical
       density_map{
        [0.0 rgb 0]
        [1.0 d_nebulae_emission]
       }
       scale 25 warp{turbulence .2+.2*rand(r_u) lambda 3} scale 1/25
      }
   
   // nebulae object
   //#declare Nebulae =
   sphere { 0, 1 hollow //no_shadow
      pigment{rgbt 1} 
      interior { media { emission 2.0/fSize intervals 3 //scattering{4,.00005}
         density { d_sph_neb_emission }
         scale .5
      } } //interior
      scale fSize
      finish {ambient 0 diffuse 0 brilliance 0}
   }
   //object{Nebulae scale fSize 
   // rotate <360*rand(r_u),360*rand(r_u),360*rand(r_u)>
   // translate <0,0,1000>
   //}
#end

// ---------------------------------------------------------------------------
// Nebula 7
// ---------------------------------------------------------------------------
// original author unknown
#macro mCloudNebula07(fSize, cColors, fEmission, rShapeSeed, rColorSeed)
   #if (fEmission = 0) #declare fDensity=RRand(1,10,rShapeSeed); #else #declare fDensity=fEmission*50; #end //normalized to input max 0.20
   #declare fTransmit = 1; //RRand(0.0,0.5,rColorSeed); //0.0

   #local m_pNebula = density { spotted scale 3
   	colour_map {
   		//[0.0 rgb <1.0, 0.6, 0.1> transmit fTransmit] [0.4 rgb <1.0, 0.1, 0.1> transmit fTransmit] [1.0 rgb <0.1, 0.1, 1.0> transmit fTransmit]
   		[0.0 cColors[0] transmit fTransmit filter 1]
   		[0.4 cColors[1] transmit fTransmit filter 1]
   		[1.0 cColors[0] transmit fTransmit filter 1]
   	}
   }

   #macro m_pNebulaForm(fThreshold,rShapeSeed)
   	pigment_pattern {	spherical scale 6 poly_wave 2 //CHANGE THE OTHER ONE! NOT THIS!!
   	   turbulence RRand(0.5,1.5,rShapeSeed) //0.8
   		pigment_map { 
   			[0 rgb 0]
   			[1 granite scale 1/3 translate RRand(1,3,rShapeSeed) //2
   				scale 6 poly_wave fThreshold
   				//pigment_map { [0.0 rgb 1 filter 1] [0.8 rgb 0.02 filter 1] [1.0 rgb 0 filter 1] }
   				pigment_map { [0.0 rgb 1] [0.8 rgb 0.02] [1.0 rgb 0] }
   			] } //pigment_map
   	}
   #end

  #declare fThreshold = RRand(0.1,0.3,rShapeSeed);
	sphere { 0, 10 hollow on pigment { rgbt 1 } 
		interior { media { scattering { 1, rgb fDensity	//set base density here, set colour in the density section. The two get multiplied together when used.
			extinction RRand(0.5,1.5,rColorSeed) //1 let it glow a little
		   } absorption 0 emission 0
			density { m_pNebulaForm(fThreshold,rShapeSeed)
				//density_map { [0 rgb 0 filter 1] [1 m_pNebula] }
				density_map { [0 rgb 0 ] [1 m_pNebula] }
			} //density
		} } //media //interior
		scale 40 //no_shadow //no_reflection
	} //sphere
#end //macro


// ---------------------------------------------------------------------------
// Cloud Nebula 8
// ---------------------------------------------------------------------------
#macro mCloudNebula08(fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  // @param fEmission [0..10]; 0 - random; > 0.0 - set value
  // @param fSize - default = 1
  //   if > 1, then fEmission needs probably to be adjusted too
  //   though a simple adjustment is integrated
  // it is best to place object at z*4e4 to avoid artifacts
  // with stars (at default distance 2e4)

  #if (fSize=0)
    #declare fSize = RRand(0.1, 10, rShapeSeed);
  #end
  #if (fEmission=0)
    #declare fIntensity = RRand(5e-5, 2e-4, rColorSeed);
  #else
    #declare fIntensity = 5e-5 + 4e-5*fEmission;
  #end
  #declare fIntensity = fIntensity / fSize;

  // make the edges smooth
  #declare dDensityEdgeBlend = density { spherical density_map {
    [0.0 rgb <0.0, 0.0, 0.0>] //exterior
    [1.0 rgb <1.0, 1.0, 1.0>] //interior
  } }

  // make the core brighter
  #declare dDensityCenterEnforce = density { spherical density_map {
      [0.7 rgb <1.0, 1.0, 1.0>] //exterior
      [1.0 rgb <8.0, 8.0, 8.0>] //interior
  } }              

  // make the cloud macro shape
  #declare dDensityCloudMacro = density { spherical 
    density_map {
      #local fStep = 1/dimension_size(NEBULA_COLORS,1);
      #local I=0; #while(I<1)      
        [I NEBULA_COLORS[IRand(0,dimension_size(NEBULA_COLORS,1)-1,rColorSeed)]*fIntensity ]
      #local I=I+fStep; #end      
    }      
    warp {
        turbulence RRand(0.5,2.5,rShapeSeed) //0.6
        lambda RRand(1.5,4.5,rShapeSeed) //1.5  
        omega RRand(0.25,0.75,rShapeSeed) //0.25 //low-blurry; high-wrinkly
    }
    // make gas explosion
    warp {
        black_hole <0.0, 0.0, 0.0>, 2.0
        strength RRand(0.5,2.0,rShapeSeed) //0.95 // compression of the cloud
        falloff 2.5  //2.5 //extension of explosion
    }
  }

  // fine cloud gases
  #declare dDensityCloudMicro = density { spherical
    density_map {
      #local fStart = RRand(0.80, 0.95, rShapeSeed);
      #local fStep = (1-fStart)/dimension_size(NEBULA_COLORS,1);
      [0.0 rgb <0.0, 0.0, 0.0>]       //exterior
      [0.1 NEBULA_COLORS[IRand(0,dimension_size(NEBULA_COLORS,1)-1,rColorSeed)] * 0.75]
      [0.2 NEBULA_COLORS[IRand(0,dimension_size(NEBULA_COLORS,1)-1,rColorSeed)] * 0.75]
      #local I=fStart; #while(I<1)      
        [I NEBULA_COLORS[IRand(0,dimension_size(NEBULA_COLORS,1)-1,rColorSeed)] * RRand(2.5, 3.5, rShapeSeed) ] //with increasing intensity toward interior
      #local I=I+fStep; #end      
      [1.0 NEBULA_COLORS[IRand(0,dimension_size(NEBULA_COLORS,1)-1,rColorSeed)] * 2.5]
    }     
    warp {
      turbulence RRand(1.0,2.5,rShapeSeed) //1.5
      lambda RRand(2.0,4.5,rShapeSeed)   //2.5
      omega RRand(0.35,0.65,rShapeSeed)  //0.55
      octaves IRand(5,10,rShapeSeed) //7
    }
    scale RRand(0.75,2.0,rShapeSeed) //0.75
    warp {
      black_hole <0.0, 0.0, 0.0>, 2.0
      strength RRand(0.8,2.0,rShapeSeed) //0.8
      falloff 2.0
    }
  }

  /*
   * Legacy implementation has artifacts with the star tirangles
   * which, when present, prevent the nebula density to be drawn
   * inside the triangles, and therefore makes those visible
   * as artifacts
   */
  /*
  sphere { 0, 2.0*fSize pigment { color rgbt <1, 1, 1, 1> } hollow      
    interior {
      media {         
        emission RRand(0.1,0.5,rShapeSeed) //1.0
        absorption 0.2   
        
        density { dDensityEdgeBlend scale fSize }
        density { dDensityCenterEnforce scale fSize }
        density { dDensityCloudMacro scale fSize }
        density { dDensityCloudMicro scale fSize }
        
        samples 20
        scale 1.25
      }
    } 
  }
  */
  // TESTS: Substitute sphere with box
  /*#declare fDenScale = 8*fSize; //80;
  #declare oNebulaInterior = interior {
    media {         
      emission RRand(0.1,0.5,rShapeSeed) * 10 //1.0
      absorption 0.2   
      
      density { dDensityEdgeBlend scale fDenScale }
      density { dDensityCenterEnforce scale fDenScale }
      density { dDensityCloudMacro scale fDenScale }
      density { dDensityCloudMicro scale fDenScale }
      
      samples 20 //20
      scale fDenScale // 1.25*4 (*4 sphere>box)
    }
  }*/
  /*box {
    // corner 1, corner 2
    <-image_width*fSize, -image_height*fSize, 0> <image_width*fSize, image_height*fSize, fSize>
    pigment { color rgbt <1, 1, 1, 1> } hollow
    //pigment { color rgbt <0.7, 0.7, 1, 0.9> } hollow // testing
    interior { oNebulaInterior }
  } */

  // Substitute sphere with box
  #declare fDenScale = 2e4*fSize;
  #declare oNebulaInterior = interior {
    media {         
      emission RRand(0.1,0.5,rShapeSeed)
      absorption 0.2   
      
      density { dDensityEdgeBlend scale fDenScale }
      density { dDensityCenterEnforce scale fDenScale }
      density { dDensityCloudMacro scale fDenScale }
      density { dDensityCloudMicro scale fDenScale }
      
      samples 20 //20
      scale 1.25
    }
  }
  #declare fSize = 2e4;
  #declare isBox = 1;
  #if (isBox)
  box {
      // corner 1, corner 2
      <-image_width*fSize, -image_height*fSize, 0> <image_width*fSize, image_height*fSize, fSize>
      pigment { color rgbt <1, 1, 1, 1> } hollow
      //pigment { color rgbt <0.7, 0.7, 1, 0.9> } hollow // testing
      interior { oNebulaInterior }
  } #else
  sphere { 0, 2.0*fSize pigment { color rgbt <1, 1, 1, 1> } hollow      
    pigment { color rgbt <1, 1, 1, 1> } hollow
    //pigment { color rgbt <0.7, 0.7, 1, 0.9> } hollow // testing
    interior { oNebulaInterior }
  } #end

#end

// ---------------------------------------------------------------------------
// Ring Nebula Objects
// ---------------------------------------------------------------------------
#macro RingNebula(fSize, cColors, fEmission, rShapeSeed, rColorSeed)
   #if (fEmission = 0) #local fEmission = RRand(0.50,1.50,rColorSeed); #end
   #local fStep = RRand(0.02,0.10,rShapeSeed);
   torus { 1, 0.5 pigment { rgbt 1 } // transparent surface
   	interior { media { emission fEmission
   	 intervals 1 samples 25 method 3 jitter 0.5
   		density { spherical poly_wave RRand(0.5,1.5,rShapeSeed)
            turbulence RRand(0.15,0.60,rShapeSeed)
            octaves RRand(2,5,rShapeSeed)
            //frequency RRand(1,5,rShapeSeed)
            lambda RRand(2.1,3.5,rShapeSeed)
            omega RRand(0.50,0.65,rShapeSeed)
            color_map {
               [ 0.0  color rgbft <0.0, 0.0, 0.0, 0.0, 1.0> ]
               [ 0.1  color rgbft <0.0, 0.0, 0.0, 0.0, 1.0> ]
               #local I=0.1; #while (I<=0.2)
                  #local iColor = IRand(0,1,rColorSeed);
                  [ I cColors[iColor] transmit 0 filter 0 ]
               #local I=I+fStep; #end
               [ 0.2 color rgbft <0.0, 0.0, 0.0, 0.0, 1.0> ]
               [ 1.0 color rgbft <0.0, 0.0, 0.0, 0.0, 1.0> ]
            }
         scale 1.2/sqrt(fSize)
         //scale 1/fSize
   		}
   	} } //interior
   scale 1*fSize
   hollow
   } //object
#end

// ---------------------------------------------------------------------------
// Background Nebula Objects
// ---------------------------------------------------------------------------
// The edges of this nebulae are not smoothed
// Please use this nebulae only with camera inside them

#macro mBackgroundNebula01(fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  #if (fEmission = 0) #local fEmission = RRand(0.008,0.020,rColorSeed); #end
  #if (fSize>8.33e4) #declare fSize = 8.33e4; #end
  #if (dimension_size(cColors,1)<2)
    #declare cTmp = array[2];
    #declare cTmp[0] = cColors[0];
    #declare cTmp[1] = cColors[0];
    #declare cColors = array[2];
    #declare cColors = cTmp;
  #end
  //#declare NEBULA_COLORS[0] = color rgb <RRand(0.1,1.0,rColor), RRand(0.1,1.0,rColor), RRand(0.1,1.0,rColor)>;
  //#declare NEBULA_COLORS[1] = color rgb <RRand(0.1,1.0,rColor), RRand(0.1,1.0,rColor), RRand(0.1,1.0,rColor)>;
  sphere { 0, 1.5 pigment { color rgbf<1, 1, 1,1> } finish { ambient 0.0 diffuse 0.0 }
    interior { media { intervals 10 samples 1, 5 confidence 0.9999 variance 1/1000 emission fEmission/fSize //0.008
       density { GetPattern(IRand(1,20,rShapeSeed)) scale 0.2 //dents
          turbulence RRand(0.50,2.00,rShapeSeed)
          octaves RRand(2,40,rShapeSeed)
          frequency RRand(1,2,rShapeSeed)
          lambda RRand(2.1,4.5,rShapeSeed)
          omega RRand(0.51,0.65,rShapeSeed)
          color_map { [0.0 rgb <0,0,0> transmit 1 ] [0.8 cColors[0] ] [1.0 cColors[1] ] }
       } 
    } }
    no_shadow
    scale 80*fSize
    hollow
  }
#end //macro

#macro mBackgroundNebula02(fSize, cColors, fEmission, rShapeSeed, rColorSeed, iPattern)
   #if (fEmission = 0) #local fEmission=RRand(0.015,0.06,rColorSeed); #end
   #if (iPattern=0) #local iPattern = IRand(1,20,rShapeSeed); #end
   #if (fSize>3.33e5) #declare fSize=3.33e5; #end
   #local fEdge = RRand(0.1,0.9,rShapeSeed);
   #local fStep = RRand(0.001,0.2,rShapeSeed);
   sphere { 0, 1.5 pigment { color rgbf<1, 1, 1,1> } finish { ambient 0.0 diffuse 0.0 }
      interior { media { intervals 10 samples 1, 5 confidence 0.9999 variance 1/1000 emission fEmission/fSize
         density { GetPattern(iPattern) scale 0.2 
            turbulence RRand(0.50,1.30,rShapeSeed)
            octaves RRand(2,20,rShapeSeed)
            frequency RRand(1,2,rShapeSeed)
            lambda RRand(2.1,3.5,rShapeSeed)
            omega RRand(0.51,0.65,rShapeSeed)
            color_map { [0.0 rgb <0,0,0> transmit 1 ]
               #local I=fEdge; #while (I<=1)
                  #local iColor = IRand(0,dimension_size(cColors,1)-1,rColorSeed);
                  [ I cColors[iColor] transmit 0 filter 0 ]
               #local I=I+fStep; #end
            }
         } 
      } }
      no_shadow
      scale 20*fSize
      hollow
   }
#end //macro

// ---------------------------------------------------------------------------
// Nebula Selector
// ---------------------------------------------------------------------------

#macro NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
// iType: 1-cloud, 2-background, 3-ring
// iNumber: nebula number within type
// cColors: array of colors
// fIntensity: 0=random, f=emission value
// rXSeed: seeds for randomization
   #if (iType=1)
      #local iNumber = mod(iNumber-1,8)+1; //maximum 8 different nebulae
      #switch (iNumber)
         #case (1) mCloudNebula01(fSize, cColors, fEmission, rShapeSeed, rColorSeed) #break
         #case (2) mCloudNebula02(fSize, cColors, fEmission, rShapeSeed, rColorSeed) #break
         #case (3) mCloudNebula03(fSize, cColors, fEmission, rShapeSeed, rColorSeed) #break
         #case (4) mCloudNebula04(fSize, cColors, fEmission, rShapeSeed, rColorSeed) #break
         #case (5) mCloudNebula05(fSize, cColors, fEmission, rShapeSeed, rColorSeed) #break
         #case (6) mCloudNebula06(fSize, cColors, fEmission, rShapeSeed, rColorSeed) #break
         #case (7) mCloudNebula07(fSize, cColors, fEmission, rShapeSeed, rColorSeed) #break
         #case (8) mCloudNebula08(fSize, cColors, fEmission, rShapeSeed, rColorSeed) #break
      #end
   #end //iType
   #if (iType=2)
      #local iNumber = mod(iNumber-1,2)+1; //maximum 2 different nebulae
      #switch (iNumber)
         #case (1) mBackgroundNebula01(fSize, cColors, fEmission, rShapeSeed, rColorSeed) #break
         #case (2) mBackgroundNebula02(fSize, cColors, fEmission, rShapeSeed, rColorSeed, 0) #break
      #end
   #end //iType
   #if (iType=3)
      #local iNumber = mod(iNumber-1,1)+1; //maximum 1 different nebulae
      #switch (iNumber)
         #case (1) RingNebula(fSize, cColors, fEmission, rShapeSeed, rColorSeed) #break
      #end
   #end //iType
#end //macro

// ---------------------------------------------------------------------------
// Nebula
// ---------------------------------------------------------------------------

#macro Nebula(fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  #declare iType = IRand(1,3,rShapeSeed);
  #declare iNumber = IRand(1,8,rShapeSeed);
  NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
#end

// ---------------------------------------------------------------------------
// Star Concentration
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Star Concentration 1 - Torus contained
// ---------------------------------------------------------------------------
#macro O_StarConcentration01(fSizeMin, fSizeMax, iAmount, cColors, fIntensity, fThicknessPercent, rSeed)
  #local fStarFieldDistance = 2e4;
  #if (fThicknessPercent=0) #declare fThicknessPercent=1; #end
  #local oBoundingObject = torus { fStarFieldDistance, fThicknessPercent*fStarFieldDistance*0.2 }
  union {
    #local I=0; #while (I < iAmount)
      object { mStarTriangle(fSizeMin,fSizeMax,cColors,fIntensity,rSeed)
        #local oRandomPoint = VRand_In_Obj(oBoundingObject, rSeed);
        translate oRandomPoint
      }
    #local I=I+1; #end
  }
#end

// ---------------------------------------------------------------------------
// Star Concentration 2 - Sphere contained
// ---------------------------------------------------------------------------
#macro O_StarConcentration02(fSizeMin, fSizeMax, iAmount, cColors, fIntensity, fThicknessPercent, rSeed)
  #local fStarFieldDistance = 2e4;
  #if (fThicknessPercent=0) #declare fThicknessPercent=1; #end
  #local oBoundingObject = sphere { <0,0,0>, fThicknessPercent*fStarFieldDistance*0.2 scale STARCLUSTER_EXCENTRICITY translate z*fStarFieldDistance}
  union {
    #local I=0; #while (I < STARFIELD_STAR_AMOUNT)
      object { mStarTriangle(fSizeMin,fSizeMax,cColors,fIntensity,rSeed)
        #local oRandomPoint = VRand_In_Obj(oBoundingObject, rSeed);
        translate oRandomPoint
      }
    #local I=I+1; #end
  }
#end

// ---------------------------------------------------------------------------
// Star Concentration
// ---------------------------------------------------------------------------
#macro StarConcentration(iType, fSizeMin, fSizeMax, iAmount, cColors, fIntensity, fThicknessPercent, rSeed)
  #switch (iType)
    #case (1)
      O_StarConcentration01(fSizeMin, fSizeMax, iAmount, cColors, fIntensity, fThicknessPercent, rSeed)
    #break
    #case (2)
      O_StarConcentration02(fSizeMin, fSizeMax, iAmount, cColors, fIntensity, fThicknessPercent, rSeed)
    #break
    
  #end
#end

// ---------------------------------------------------------------------------------------
// OLD UNTIL VERSION 0.23
// ---------------------------------------------------------------------------------------
// maintained for compatibility reasons
// might be removed in later versions
                       
// ---------------------------------------------------------------------------------------
// Star Field Pigments
// ---------------------------------------------------------------------------------------

// Star Field 1
// ---------------------------------------------------------------------------------------
// plain star fields
#macro P_StarField01()
   #if (STARFIELD_STAR_INTENSITY<2) #local STARFIELD_STAR_INTENSITY = 2; #end
   leopard color_map {
      [.74 rgb 0 transmit 1] [.75 STARFIELD_STAR_COLOR * STARFIELD_STAR_INTENSITY]
      [.84 rgb 0 transmit 1] [.85 STARFIELD_STAR_COLOR * STARFIELD_STAR_INTENSITY]
      [.95 rgb 0 transmit 1] [1 STARFIELD_STAR_COLOR * STARFIELD_STAR_INTENSITY] }
   scale 1e-17 translate <0,0,0> //1e-17
#end

// Star Field 2
// ---------------------------------------------------------------------------------------
// looks promising
// second map entry defines density
#macro P_StarField02()
   #if (STARFIELD_STAR_INTENSITY<5) #local STARFIELD_STAR_INTENSITY = 5; #end
   granite color_map {
      [0.00 rgb 0 transmit 1] [0.80 rgb 0 transmit 1] [1.00 STARFIELD_STAR_COLOR*STARFIELD_STAR_INTENSITY] }
   scale 1e-2
#end

// Star Field 3
// ---------------------------------------------------------------------------------------
// very flat and uniform
#macro P_StarField03()
   #if (STARFIELD_STAR_INTENSITY<3) #local STARFIELD_STAR_INTENSITY = 3; #end
   #ifndef (P_Stafield_Pattern1)
      #local P_Stafield_Pattern1 = function(x,y,z) { pow(x,2) + pow(y,2) + pow(z,2) }
   #end
   function { P_Stafield_Pattern1 (x,y,z) } color_map {
     [0.00 rgb 0 transmit 1] [0.65 rgb 0 transmit 1] [0.65 STARFIELD_STAR_COLOR*STARFIELD_STAR_INTENSITY] [0.66 rgb 0 transmit 1]}
   scale 1e-3 turbulence 1
#end

// Star Field 4
// ---------------------------------------------------------------------------------------
#macro P_StarField04()
   #if (STARFIELD_STAR_INTENSITY<5) #local STARFIELD_STAR_INTENSITY = 5; #end
   #local star6c = pigment {spotted color_map {
     [0.0 rgb <0.9,1,1>*STARFIELD_STAR_INTENSITY ] [0.1 rgb <0.8,1,1>*STARFIELD_STAR_INTENSITY ] [0.3 rgb 0 transmit 1] }
     scale .1
   }
   #local star6c2 = pigment { granite color_map {
     [0.80 rgb 0 transmit 1] [1.00 rgb <1,1,1>] }
     scale 1
   }
   average pigment_map {
      [ 2.0 star6c2 ] // controls spread
      [ 2.0 star6c  ] // space; controls extension of the cloud field; 0=no, 1=full
   }
   scale 1e-2 noise_generator 3 turbulence 0.3
#end

// Star Field 5
// ---------------------------------------------------------------------------------------
#macro P_StarField05()
   bozo pigment_map { 
      [ 3.0 spotted color_map {
         [0.1 STARFIELD_STAR_COLOR*2*STARFIELD_STAR_INTENSITY ] // intensity variance=(0.1 & *2); color=rgb
         [0.3 rgb 0 transmit 1 ] // density
         } scale 1e-3
      ]
      [ 3.0 granite color_map {
         [0.70 rgb 0 transmit 1]
         [1.00 STARFIELD_STAR_COLOR ]
         } scale 1e-2
      ]
      [ 3.0 leopard color_map {
         [0.50 rgb 0 transmit 1 ] // density=0.5
         [1.00 STARFIELD_STAR_COLOR ]
         } scale 1e-5 ]
   }
#end

// ---------------------------------------------------------------------------------------
// Star Cluster Pigments
// ---------------------------------------------------------------------------------------

// Star Cluster 1
// ---------------------------------------------------------------------------------------
// planar cluster
// ---------------------------------------------------------------------------------------

#macro P_StarCluster01()
  #declare S = seed(123456);
   #local STAR_SHAPE = pigment { cylindrical
      pigment_map { // pigment map parameters: [radius from outer edge, rgb crater depth]
         [0.00 rgb 0 filter 0] // outside color
         [0.00 STARFIELD_STAR_AURA*STARFIELD_STAR_AMOUNT filter 1] // outside color
         [RRand(0.70,0.9,S) STARFIELD_STAR_AURA*STARFIELD_STAR_AMOUNT*STARFIELD_STAR_AMOUNT filter 1] // outside color
         [1.00 STARFIELD_STAR_COLOR*5*STARFIELD_STAR_AURA*STARFIELD_STAR_AMOUNT*STARFIELD_STAR_AMOUNT filter 1] // edge extension to center
      }
      scale RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX,S) //basic star size
      poly_wave 1.5
   }
   #local P_Stars1 =
   pigment { average
      pigment_map { 
         #local I=0; #while (I<=STARFIELD_STAR_AMOUNT)
         [1 STAR_SHAPE scale RRand(0.1,0.5,S) rotate <rand(S)*180,rand(S)*180,rand(S)*180> ]
         #local I=I+1; #end
      }
   }
   average pigment_map { 
      #local I=0; #while (I<=STARFIELD_STAR_AMOUNT)
      [0.1*STARFIELD_STAR_AMOUNT P_Stars1 scale RRand(0.1,0.5,S) rotate <rand(S)*180,rand(S)*180,rand(S)*180> ]
      #local I=I+1; #end
   }
#end

// Star Cluster 2
// ---------------------------------------------------------------------------------------
// globular star clusters
// ---------------------------------------------------------------------------------------
#macro P_StarCluster02()
  #declare S = seed(123456);
   #local STAR_SHAPE = pigment { cylindrical
      pigment_map {
         // pigment map parameters: [radius from outer edge, rgb crater depth]
         [0.00 rgb 0 filter 0] // outside color
         [0.00 STARFIELD_STAR_AURA*STARFIELD_STAR_AMOUNT filter 1] // outside color
         [RRand(0.70,0.9,S) STARFIELD_STAR_AURA*STARFIELD_STAR_AMOUNT*STARFIELD_STAR_AMOUNT filter 1] // outside color
         [1.00 STARFIELD_STAR_COLOR*5*STARFIELD_STAR_AURA*STARFIELD_STAR_AMOUNT*STARFIELD_STAR_AMOUNT filter 1] // edge extension to center
      }
      scale RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX,S) //basic star size
      poly_wave 1.5
   }
   #local P_Stars2 =
   pigment { average
      pigment_map { 
         #local I=0; #while (I<=STARFIELD_STAR_AMOUNT)
         #local star_cluster_rotate = RRand(STARFIELD_DISTRIBU_ANGLE/2, STARFIELD_DISTRIBU_ANGLE*2,S);
         #local rot_x = RRand(-star_cluster_rotate,star_cluster_rotate,S);
         #local rot_y = RRand(-star_cluster_rotate,star_cluster_rotate,S);
         #local rot_z = RRand(-star_cluster_rotate,star_cluster_rotate,S);
         [1 STAR_SHAPE scale RRand(0.1,0.5,S) rotate <rot_x,rot_y,rot_z> ]
         #local I=I+1; #end
      }
   }
   average pigment_map { 
      #local I=0; #while (I<=STARFIELD_STAR_AMOUNT)
      #local star_cluster_rotate = RRand(STARFIELD_DISTRIBU_ANGLE/2, STARFIELD_DISTRIBU_ANGLE*2,S);
      #local rot_x = RRand(-star_cluster_rotate,star_cluster_rotate,S);
      #local rot_y = RRand(-star_cluster_rotate,star_cluster_rotate,S);
      #local rot_z = RRand(-star_cluster_rotate,star_cluster_rotate,S);
      [0.1*STARFIELD_STAR_AMOUNT P_Stars2 scale RRand(0.1,0.5,S) rotate <rot_x,rot_y,rot_z> ]
      #local I=I+1; #end
   }
#end

// Star Cluster 3
// ---------------------------------------------------------------------------------------
// non-uniform star clusters
// ---------------------------------------------------------------------------------------
#macro P_StarCluster03()
  #declare S = seed(123456);
   #local STAR_SHAPE = pigment { cylindrical
      pigment_map {
         // pigment map parameters: [radius from outer edge, rgb crater depth]
         [0.00 rgb 0 filter 0] // outside color
         [0.00 STARFIELD_STAR_AURA*STARFIELD_STAR_AMOUNT filter 1] // outside color
         [RRand(0.70,0.9,S) STARFIELD_STAR_AURA*STARFIELD_STAR_AMOUNT*STARFIELD_STAR_AMOUNT filter 1] // outside color
         [1.00 STARFIELD_STAR_COLOR*5*STARFIELD_STAR_AURA*STARFIELD_STAR_AMOUNT*STARFIELD_STAR_AMOUNT filter 1] // edge extension to center
      }
      scale RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX,S) //basic star size
      poly_wave 1.5
   }
   #local P_Stars3 = pigment { average
      pigment_map { 
         #local I=0; #while (I<=STARFIELD_STAR_AMOUNT)
         #local star_cluster_rotate = RRand(STARFIELD_DISTRIBU_ANGLE/2, STARFIELD_DISTRIBU_ANGLE*2,S);
         #local rot_x = RRand(-star_cluster_rotate,star_cluster_rotate,S);
         #local rot_y = RRand(-star_cluster_rotate,star_cluster_rotate,S);
         #local rot_z = RRand(-star_cluster_rotate,star_cluster_rotate,S);
         [1 STAR_SHAPE scale RRand(0.1,0.5,S) rotate <rot_x,rot_y,rot_z> ]
         #local I=I+1; #end
      }
   }
   //pigment { 
   average pigment_map { 
      #local I=0; #while (I<=STARFIELD_STAR_AMOUNT)
      #local star_cluster_rotate = RRand(STARFIELD_DISTRIBU_ANGLE/2, STARFIELD_DISTRIBU_ANGLE*2,S);
      #local rot_x = RRand(-star_cluster_rotate*STARCLUSTER_EXCENTRICITY.x,star_cluster_rotate*STARCLUSTER_EXCENTRICITY.x,S);
      #local rot_y = RRand(-star_cluster_rotate,star_cluster_rotate,S);
      #local rot_z = RRand(-star_cluster_rotate,star_cluster_rotate,S);
      [0.1*STARFIELD_STAR_AMOUNT P_Stars3 scale RRand(0.1,0.5,S) rotate <rot_x,rot_y,rot_z> ]
      #local I=I+1; #end
   }
   //}
#end

// ---------------------------------------------------------------------------------------
// Star Cluster Objects
// ---------------------------------------------------------------------------------------
// Essentially obsolete and replaced by StarCluster macro.
// They have previously been used inline to experiment with different concepts.
// Mostly to determine the best way of making a picture of the universe look as
// realistic as possible by creating diversity in randomness, star sizes, luminosity,
// and distribution, also forming tiny clusters.
// Not an easy task at it may seem. It ultimately partialy failed. The small star
// clusters must be made by hand still.
// They have not been updated to the macro use approach and may not work at all.
// The code is still kept around for historical reference.
// Just in case someone may need to recall the development and experimenation stages.


// ---------------------------------------------------------------------------------------
// Star Cluster Object 1
// ---------------------------------------------------------------------------------------
// simple triangle star cluster object
//#declare S = seed(starfield_seed_no);
//#ifdef (_SF_star_amount)
//   #declare STARFIELD_STAR_AMOUNT = _SF_star_amount;
//#end

#macro O_StarCluster01(fSizeMin, fSizeMax, iAmount, fIntensity, rSeed) 
  #declare fStarDistance = 2e4;
  #declare fDistributionAngle = fStarDistance*pi*STARFIELD_DISTRIBU_ANGLE/360;
  #declare fStarSize = 2e2;
  union {
    #local I=0; #while (I < iAmount)
      triangle {<-1, -.6, 0>, <0, 1, 0>, <1, -.6, 0>
        pigment {onion pigment_map { 
          [0 STARFIELD_STAR_COLOR*fIntensity transmit 0 ]
          [0.09 STARFIELD_STAR_COLOR*STARFIELD_STAR_AURA transmit 0.5] 
          [0.25 STARFIELD_STAR_AURA transmit 1] } scale 2 }
        finish { ambient 1 diffuse 0 reflection 0 phong 0 specular 0 crand 0 }
        scale RRand(fStarSize*fSizeMin, fStarSize*fSizeMax, rSeed)
        #local _SC_TRANSLATION = RRand(0.5*fDistributionAngle, 2*fDistributionAngle, rSeed);
        #local t_x = RRand(-_SC_TRANSLATION, _SC_TRANSLATION, rSeed);
        #local t_y = RRand(-_SC_TRANSLATION, _SC_TRANSLATION, rSeed);
        #local t_z = (fStarDistance) + I;
        translate <t_x, t_y, t_z>
        #local _SC_ROTATE = RRand(STARFIELD_DISTRIBU_ANGLE/2, STARFIELD_DISTRIBU_ANGLE*2, rSeed);
        #local rot_x = RRand(-_SC_ROTATE*STARCLUSTER_EXCENTRICITY.x, _SC_ROTATE*STARCLUSTER_EXCENTRICITY.x, rSeed);
        #local rot_y = RRand(-_SC_ROTATE*STARCLUSTER_EXCENTRICITY.y, _SC_ROTATE*STARCLUSTER_EXCENTRICITY.y, rSeed);
        #local rot_z = RRand(-_SC_ROTATE*STARCLUSTER_EXCENTRICITY.z, _SC_ROTATE*STARCLUSTER_EXCENTRICITY.z, rSeed);
        rotate <rot_x,rot_y,rot_z>
        rotate STARCLUSTER_DISTRIBU_ANGLE
      }
    #local I=I+1; #end
  }
#end

// ---------------------------------------------------------------------------------------
// Star Cluster Object 2
// ---------------------------------------------------------------------------------------
// triangle star cluster object with aura
//#declare S = seed(starfield_seed_no);

//#ifdef (_SF_star_amount)
//   #declare STARFIELD_STAR_AMOUNT = _SF_star_amount;
//#end

#macro O_StarCluster02(fSizeMin, fSizeMax, iAmount, fIntensity, rSeed)
  #declare fStarDistance = 2e4;
  #declare fDistributionAngle = fStarDistance*pi*STARFIELD_DISTRIBU_ANGLE/360;
  #declare fStarSize = 2e2; //2e2;
  union {
    #local I=0; #while (I < iAmount)
      triangle {<-1, -.6, 0>, <0, 1, 0>, <1, -.6, 0>
        pigment {onion pigment_map {
          [0.00 STARFIELD_STAR_COLOR*fIntensity filter 0 transmit 0]
          [0.15 STARFIELD_STAR_AURA filter 1 transmit 0]
          [0.25 STARFIELD_STAR_AURA filter 0 transmit 1] 
        } scale 2 }
        finish {ambient 1 diffuse 0 reflection 0 phong 0 specular 0 crand 0}
        scale RRand(fStarSize*fSizeMin, fStarSize*fSizeMax, rSeed)
        #local _SC_TRANSLATION = RRand(0.5*fDistributionAngle, 2*fDistributionAngle, rSeed);
        #local t_x = RRand(-_SC_TRANSLATION, _SC_TRANSLATION, rSeed);
        #local t_y = RRand(-_SC_TRANSLATION, _SC_TRANSLATION, rSeed);
        #local t_z = (fStarDistance) + I;
        translate <t_x, t_y, t_z>
        #local _SC_ROTATE = RRand(STARFIELD_DISTRIBU_ANGLE/2, STARFIELD_DISTRIBU_ANGLE*2,S);
        #local rot_x = RRand(-_SC_ROTATE*STARCLUSTER_EXCENTRICITY.x, _SC_ROTATE*STARCLUSTER_EXCENTRICITY.x, rSeed);
        #local rot_y = RRand(-_SC_ROTATE*STARCLUSTER_EXCENTRICITY.y, _SC_ROTATE*STARCLUSTER_EXCENTRICITY.y, rSeed);
        #local rot_z = RRand(-_SC_ROTATE*STARCLUSTER_EXCENTRICITY.z, _SC_ROTATE*STARCLUSTER_EXCENTRICITY.z, rSeed);
        rotate <rot_x,rot_y,rot_z>
        rotate STARCLUSTER_DISTRIBU_ANGLE
      }
    #local I=I+1; #end
  }
#end

// ---------------------------------------------------------------------------------------
// Triangles for Star Cluster Object 3 & 5
// ---------------------------------------------------------------------------------------
// sphere based star objects
//#declare fStarSize = 2e2;
//#declare S = seed(123456);

#declare oStarTriangle_BaseObject = triangle {<-1, -.6, 0>, <0, 1, 0>, <1, -.6, 0>
   pigment {onion pigment_map {
      [0.00 STARFIELD_STAR_COLOR*STARFIELD_STAR_INTENSITY filter 0 transmit 0]
      [0.15 STARFIELD_STAR_AURA filter 0 transmit 0.5]
      [0.25 STARFIELD_STAR_AURA filter 0 transmit 1] 
   } scale 2 }
   finish {ambient 1 diffuse 0 reflection 0 phong 0 specular 0 crand 0}
}

#macro oStarTriangle_Tiny() //STARFIELD_STAR_TYPE = 1; recommended size min/max = 0.2/0.5
   triangle { oStarTriangle_BaseObject
      #local STARFIELD_STARSIZE_MIN = 0.02; #local STARFIELD_STARSIZE_MAX = 0.05;
      scale fStarSize*RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX, rSeed)
   }
#end

#macro oStarTriangle_Small() //STARFIELD_STAR_TYPE = 2; recommended size min/max = 0.5/1.0
   triangle { oStarTriangle_BaseObject
      #local STARFIELD_STARSIZE_MIN = 0.5; #local STARFIELD_STARSIZE_MAX = 1.0;
      scale fStarSize*RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX, rSeed)
   }
#end

#macro oStarTriangle_Medium(rSeed) //STARFIELD_STAR_TYPE = 3; recommended size min/max = 1/2 
   triangle { oStarTriangle_BaseObject
      #local STARFIELD_STARSIZE_MIN = 1.0; #local STARFIELD_STARSIZE_MAX = 2;
      #local fStarSize = RRand(STARFIELD_STARSIZE_MIN, STARFIELD_STARSIZE_MAX, rSeed)
      scale fStarSize*RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX, rSeed)
   }
#end

#macro oStarTriangle_Big() //STARFIELD_STAR_TYPE = 4 / recommended size min/max = 2/3 
   triangle { oStarTriangle_BaseObject
      #local STARFIELD_STARSIZE_MIN = 2; #local STARFIELD_STARSIZE_MAX = 3;
      scale fStarSize*RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX, rSeed)
   }
#end

#macro oStarTriangle_Large() //STARFIELD_STAR_TYPE = 5 / recommended size min/max = 3/5
   triangle { oStarTriangle_BaseObject
      #local STARFIELD_STARSIZE_MIN = 3; #local STARFIELD_STARSIZE_MAX = 5;
      scale fStarSize*RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX, rSeed)
   }
#end

// ---------------------------------------------------------------------------------------
// Star Cluster Object 3
// ---------------------------------------------------------------------------------------
// non-uniform triangle based star cluster object
#declare fStarFieldDistance = 2e4;
#declare fTranslationRadius = fStarFieldDistance*pi*STARFIELD_DISTRIBU_ANGLE/360;
   
//#macro O_StarCluster03()
#macro O_StarCluster03(fSizeMin, fSizeMax, iAmount, fIntensity, rSeed)
   union {
      #local I=0; #while (I < STARFIELD_STAR_AMOUNT)
         object {
            #switch (STARFIELD_STAR_TYPE)
               #case (1) oStarTriangle_Tiny()   #break  
               #case (2) oStarTriangle_Small()  #break  
               #case (3) oStarTriangle_Medium(rSeed) #break  
               #case (4) oStarTriangle_Big()    #break  
               #case (5) oStarTriangle_Large()  #break  
            #end
            #local fTranslation = RRand(0.5*fTranslationRadius, 2*fTranslationRadius, rSeed);
            #local t_x = RRand(-fTranslation, fTranslation, rSeed);
            #local t_y = RRand(-fTranslation, fTranslation, rSeed);
            #local t_z = fStarFieldDistance * RRand(0.9,1.1,rSeed);
            translate <t_x, t_y, t_z>
            #local fRotation = RRand(STARFIELD_DISTRIBU_ANGLE/2, STARFIELD_DISTRIBU_ANGLE*2,rSeed);
            #local rot_x = fRotation*RRand(-STARCLUSTER_EXCENTRICITY.x, STARCLUSTER_EXCENTRICITY.x, rSeed);
            #local rot_y = fRotation*RRand(-STARCLUSTER_EXCENTRICITY.y, STARCLUSTER_EXCENTRICITY.y, rSeed);
            #local rot_z = fRotation*RRand(-STARCLUSTER_EXCENTRICITY.z, STARCLUSTER_EXCENTRICITY.z, rSeed);
            rotate <rot_x,rot_y,rot_z> rotate STARCLUSTER_DISTRIBU_ANGLE
         }
      #local I=I+1; #end
   }
#end

// ---------------------------------------------------------------------------------------
// Spheres for Star Cluster Object 4 & 6
// ---------------------------------------------------------------------------------------
// sphere based star objects
//#declare S = seed(123456);
//#declare fStarSize = 2e2;
   
#declare oStarSphere_BaseObject = sphere { 0, 1
   pigment { color rgb <0,0,0> transmit 1 }
   interior { media {
   	emission 0.002 intervals 3 method 2 samples 3 // more: e.g.100 => smoother
   	density { spherical color_map {
   		[0.0 color rgb <0,0,0> transmit 1] // outside
   		[0.5 color STARFIELD_STAR_AURA*0.25 transmit 1] // star limit
   		[1.0 color STARFIELD_STAR_COLOR*STARFIELD_STAR_INTENSITY transmit 1] // inside
		} poly_wave 2 } } } //interior
   hollow on no_shadow
}
   
#macro oStarSphere_Tiny() //STARFIELD_STAR_TYPE = 1; recommended size min/max = 0.02/0.05
   sphere { 0, 1
      pigment { color STARFIELD_STAR_COLOR*RRand(STARFIELD_STAR_INTENSITY*0.75,STARFIELD_STAR_INTENSITY,S) }
      #local STARFIELD_STARSIZE_MIN = 0.02; #local STARFIELD_STARSIZE_MAX = 0.05;
      scale fStarSize*RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX,S)
   }
#end

#macro oStarSphere_Small() //STARFIELD_STAR_TYPE = 2; recommended size min/max = 0.2/1.0
   sphere { oStarSphere_BaseObject
      #local STARFIELD_STARSIZE_MIN = 0.2; #local STARFIELD_STARSIZE_MAX = 1.0;
      scale fStarSize*RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX,S)
   }
#end

#macro oStarSphere_Medium() //STARFIELD_STAR_TYPE = 3; recommended size min/max = 0.5/2 
   sphere { oStarSphere_BaseObject
      #local STARFIELD_STARSIZE_MIN = 0.5; #local STARFIELD_STARSIZE_MAX = 2;
      scale fStarSize*RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX,S)
   }
#end

#macro oStarSphere_Big() //STARFIELD_STAR_TYPE = 4 / recommended size min/max = 2/3 
   sphere { oStarSphere_BaseObject
      #local STARFIELD_STARSIZE_MIN = 2; #local STARFIELD_STARSIZE_MAX = 3;
      scale fStarSize*RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX,S)
   }
#end

#macro oStarSphere_Large() //STARFIELD_STAR_TYPE = 5 / recommended size min/max = 3/5
   sphere { oStarSphere_BaseObject
      #local STARFIELD_STARSIZE_MIN = 3; #local STARFIELD_STARSIZE_MAX = 5;
      scale fStarSize*RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX,S)
   }
#end

// ---------------------------------------------------------------------------------------
// Star Cluster Object 4
// ---------------------------------------------------------------------------------------
// uniform sphere based star cluster object
#macro O_StarCluster04()
   #local fStarFieldDistance = 2e4;
   union {
      #local I=0; #while (I < STARFIELD_STAR_AMOUNT)
         object {
            #switch (STARFIELD_STAR_TYPE)
               #case (1) oStarSphere_Tiny()   #break  
               #case (2) oStarSphere_Small()  #break  
               #case (3) oStarSphere_Medium() #break  
               #case (4) oStarSphere_Big()    #break  
               #case (5) oStarSphere_Large()  #break  
            #end
            translate <0,0,fStarFieldDistance>
            #local r_x = RRand(-STARCLUSTER_DISTRIBU_ANGLE.x*STARCLUSTER_EXCENTRICITY.x, STARCLUSTER_DISTRIBU_ANGLE.x*STARCLUSTER_EXCENTRICITY.x, S);
            #local r_y = RRand(-STARCLUSTER_DISTRIBU_ANGLE.y*STARCLUSTER_EXCENTRICITY.y, STARCLUSTER_DISTRIBU_ANGLE.y*STARCLUSTER_EXCENTRICITY.y, S);
            #local r_z = RRand(-STARCLUSTER_DISTRIBU_ANGLE.z*STARCLUSTER_EXCENTRICITY.z, STARCLUSTER_DISTRIBU_ANGLE.z*STARCLUSTER_EXCENTRICITY.z, S);
            rotate <r_x, r_y, r_z>
         }
      #local I=I+1; #end
   }
#end

// ---------------------------------------------------------------------------------------
// Star Cluster Object 5
// ---------------------------------------------------------------------------------------
// uniform triangle based star cluster object
//#declare S = seed(starfield_seed_no);
//#declare fStarSize = 50; //2e2;

#macro mStarTriangle_BaseObject(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX)
   triangle { <-1, -.6, 0>, <0, 1, 0>, <1, -.6, 0> hollow on
      texture { pigment { onion poly_wave 1 pigment_map {
         [0.00 STARFIELD_STAR_COLOR*STARFIELD_STAR_INTENSITY transmit 0 ] //inside
         [0.10 STARFIELD_STAR_AURA*STARFIELD_STAR_INTENSITY transmit 0.5 ]  
         [0.25 STARFIELD_STAR_AURA transmit 1 ] //outside  
      } scale 2 }
      finish { ambient 1 } } //diffuse 0 reflection 0 phong 0 specular 0 crand 0} }
      scale fStarSize*RRand(STARFIELD_STARSIZE_MIN,STARFIELD_STARSIZE_MAX,S)
   no_shadow no_reflection }
#end

#declare fStarFieldDistance = 2e4;

#macro O_StarCluster05(iDistributionMethod, rSeed)
   #local fStarFieldDistance = 2e4;
   #local fTranslationRadius = fStarFieldDistance*pi*STARFIELD_DISTRIBU_ANGLE/360;
   union {
      #local I=0; #while (I < STARFIELD_STAR_AMOUNT)
         object {
            #switch (STARFIELD_STAR_TYPE)
               #case (1) mStarTriangle_BaseObject(0.2,0.5) #break //STARFIELD_STAR_TYPE = 1; recommended size min/max = 0.2/0.5 
               #case (2) mStarTriangle_BaseObject(0.5,1.0) #break //STARFIELD_STAR_TYPE = 2; recommended size min/max = 0.5/1.0 
               #case (3) mStarTriangle_BaseObject(1,2)     #break //STARFIELD_STAR_TYPE = 3; recommended size min/max = 1/2 
               #case (4) mStarTriangle_BaseObject(2,3)     #break //STARFIELD_STAR_TYPE = 4; recommended size min/max = 2/3 
               #case (5) mStarTriangle_BaseObject(3,5)     #break //STARFIELD_STAR_TYPE = 5; recommended size min/max = 3/5 
            #end
            #if (iDistributionMethod=1)
               // previous distribution, produces somewhat cubic distribution with small angles
               translate <0,0,fStarFieldDistance>
               #local r_x = RRand(-STARCLUSTER_DISTRIBU_ANGLE.x*STARCLUSTER_EXCENTRICITY.x, STARCLUSTER_DISTRIBU_ANGLE.x*STARCLUSTER_EXCENTRICITY.x, rSeed);
               #local r_y = RRand(-STARCLUSTER_DISTRIBU_ANGLE.y*STARCLUSTER_EXCENTRICITY.y, STARCLUSTER_DISTRIBU_ANGLE.y*STARCLUSTER_EXCENTRICITY.y, rSeed);
               #local r_z = RRand(-STARCLUSTER_DISTRIBU_ANGLE.z*STARCLUSTER_EXCENTRICITY.z, STARCLUSTER_DISTRIBU_ANGLE.z*STARCLUSTER_EXCENTRICITY.z, rSeed);
               rotate <r_x, r_y, r_z>
            #end
            #if (iDistributionMethod=2)
               // second distribution code
               #local fTranslation = RRand(0.5*fTranslationRadius, 2*fTranslationRadius, rSeed);
               #local t_x = RRand(-fTranslation, fTranslation, rSeed);
               #local t_y = RRand(-fTranslation, fTranslation, rSeed);
               #local t_z = fStarFieldDistance * RRand(0.9,1.1,rSeed);
               translate <t_x, t_y, t_z>
               #local fRotation = RRand(STARFIELD_DISTRIBU_ANGLE/2, STARFIELD_DISTRIBU_ANGLE*2,rSeed);
               #local rot_x = fRotation*RRand(-STARCLUSTER_EXCENTRICITY.x, STARCLUSTER_EXCENTRICITY.x, rSeed);
               #local rot_y = fRotation*RRand(-STARCLUSTER_EXCENTRICITY.y, STARCLUSTER_EXCENTRICITY.y, rSeed);
               #local rot_z = fRotation*RRand(-STARCLUSTER_EXCENTRICITY.z, STARCLUSTER_EXCENTRICITY.z, rSeed);
               rotate <rot_x,rot_y,rot_z> rotate STARCLUSTER_DISTRIBU_ANGLE
            #end
            /*#if (iDistributionMethod=3)
               // sphere based
               translate VRand_In_Sphere(rSeed)
               scale 10*<STARCLUSTER_EXCENTRICITY.x, STARCLUSTER_EXCENTRICITY.y, STARCLUSTER_EXCENTRICITY.z>
               translate <0, 0, fStarFieldDistance>
            #end*/
         }
      #local I=I+1; #end
   }
#end

// ---------------------------------------------------------------------------------------
// Star Cluster Object 6
// ---------------------------------------------------------------------------------------
// non-uniform sphere based star cluster object
#macro O_StarCluster06()
   #local fStarFieldDistance = 2e4;
   #local fTranslationRadius = fStarFieldDistance*pi*STARFIELD_DISTRIBU_ANGLE/360;
   union {
      #local I=0; #while (I < STARFIELD_STAR_AMOUNT)
         object {
            #switch (STARFIELD_STAR_TYPE)
               #case (1) oStarSphere_Tiny()   #break  
               #case (2) oStarSphere_Small()  #break  
               #case (3) oStarSphere_Medium() #break  
               #case (4) oStarSphere_Big()    #break  
               #case (5) oStarSphere_Large()  #break  
            #end
            #local fTranslation = RRand(0.5*fTranslationRadius, 2*fTranslationRadius, S);
            #local t_x = RRand(-fTranslation, fTranslation, S);
            #local t_y = RRand(-fTranslation, fTranslation, S);
            #local t_z = fStarFieldDistance * RRand(0.9,1.1,S);
            translate <t_x, t_y, t_z>
            #local fRotation = RRand(STARFIELD_DISTRIBU_ANGLE/2, STARFIELD_DISTRIBU_ANGLE*2,S);
            #local rot_x = fRotation*RRand(-STARCLUSTER_EXCENTRICITY.x, STARCLUSTER_EXCENTRICITY.x, S);
            #local rot_y = fRotation*RRand(-STARCLUSTER_EXCENTRICITY.y, STARCLUSTER_EXCENTRICITY.y, S);
            #local rot_z = fRotation*RRand(-STARCLUSTER_EXCENTRICITY.z, STARCLUSTER_EXCENTRICITY.z, S);
            rotate <rot_x,rot_y,rot_z> rotate STARCLUSTER_DISTRIBU_ANGLE
         }
      #local I=I+1; #end
   }
#end

// ---------------------------------------------------------------------------------------
// Star Cluster Object 7
// ---------------------------------------------------------------------------------------
#macro O_StarCluster07(iType, iStarAmount, fSizeMin, fSizeMax, rDistSeed) 
  #local fStarFieldDistance = 2e4;
  #local fTranslationRadius = fStarFieldDistance*pi*STARFIELD_DISTRIBU_ANGLE/360;
  #if (iType=1)
    #local fStarSize = 0.8e2;
  #else
    #local fStarSize = 2e2;
  #end
  union {
    #local I=0; #while (I < iStarAmount)
      triangle {<-1, -.6, 0>, <0, 1, 0>, <1, -.6, 0>
        #if (iType=1)
          pigment { onion pigment_map {
            [0 STARFIELD_STAR_COLOR*STARFIELD_STAR_INTENSITY transmit 0 ]
            [0.09 STARFIELD_STAR_COLOR*STARFIELD_STAR_AURA transmit 0.5]
            [0.25 STARFIELD_STAR_AURA transmit 1]
          } scale 2 }
        #else
          pigment {onion pigment_map {
            [0.00 STARFIELD_STAR_COLOR*STARFIELD_STAR_INTENSITY transmit 0 ]
            [0.09 STARFIELD_STAR_COLOR*STARFIELD_STAR_AURA*STARFIELD_STAR_INTENSITY transmit 0.5]
            [0.12 STARFIELD_STAR_AURA transmit 0.8]
            [0.19 STARFIELD_STAR_AURA transmit 0.93]
            [0.25 STARFIELD_STAR_AURA transmit 1] } poly_wave 0.5 scale 4 
          }
        #end
        finish {ambient 1 diffuse 0 reflection 0 phong 0 specular 0 crand 0}
        scale RRand(fStarSize*fSizeMin, fStarSize*fSizeMax, rDistSeed)
        // distribute position
        #local fTranslation = RRand(0.5*fTranslationRadius, 2*fTranslationRadius, rDistSeed);
        #local t_x = RRand(-fTranslation, fTranslation, rDistSeed);
        #local t_y = RRand(-fTranslation, fTranslation, rDistSeed);
        #local t_z = fStarFieldDistance * RRand(0.9,1.1,rDistSeed);
        translate <t_x, t_y, t_z>
        #local fRotation = RRand(STARFIELD_DISTRIBU_ANGLE/2, STARFIELD_DISTRIBU_ANGLE*2,rDistSeed);
        #local rot_x = fRotation*RRand(-STARCLUSTER_EXCENTRICITY.x, STARCLUSTER_EXCENTRICITY.x, rDistSeed);
        #local rot_y = fRotation*RRand(-STARCLUSTER_EXCENTRICITY.y, STARCLUSTER_EXCENTRICITY.y, rDistSeed);
        #local rot_z = fRotation*RRand(-STARCLUSTER_EXCENTRICITY.z, STARCLUSTER_EXCENTRICITY.z, rDistSeed);
        rotate <rot_x,rot_y,rot_z> rotate STARCLUSTER_DISTRIBU_ANGLE
      }
    #local I=I+1; #end
  }
#end

// ---------------------------------------------------------------------------------------
// Star Cluster Triangle Object
// ---------------------------------------------------------------------------------------
// uniform triangle based star cluster object
//#declare S = seed(starfield_seed_no);

#macro mStarTriangle(fSizeMin, fSizeMax, aStarColors, fIntensity, rSeed)
  #declare fStarSize = 50; //2e2;
  triangle { <-1, -.6, 0>, <0, 1, 0>, <1, -.6, 0> hollow on
    texture { 
      //pigment { onion poly_wave 1 pigment_map {
      //  [0.00 aStarColors[0]*fIntensity transmit 0 ] //inside
      //  [0.10 aStarColors[1]*fIntensity transmit 0.5 ]  
      //  [0.25 aStarColors[1] transmit 1 ] //outside  
      //} scale 2 }
      pigment { onion pigment_map {
        #local fIntFx = RRand(0.5,1.5,rSeed);
        [0.00 aStarColors[0]*fIntensity*fIntFx transmit 0 ]
        [0.09 aStarColors[0]*aStarColors[1]*fIntensity*fIntFx transmit 0.5]
        [0.12 aStarColors[1] transmit 0.8]
        [0.19 aStarColors[1] transmit 0.93]
        [0.25 aStarColors[1] transmit 1] } poly_wave 0.5 scale 4 
      }
    finish { ambient 1 } } //diffuse 0 reflection 0 phong 0 specular 0 crand 0} }
    scale fStarSize*RRand(fSizeMin,fSizeMax,rSeed)
  no_shadow no_reflection }
#end

// ---------------------------------------------------------------------------------------
// Star Fields
// ---------------------------------------------------------------------------------------

// Star Field 1 - distant stars base background
// ---------------------------------------------------------------------------------------
#macro O_StarField01(SF_NUMBERS, fIntensityFactor, fBaseAmount, fDistribution, aColorRange, fColorDev)
   #ifndef(rPosition) #declare rPosition = seed (1234+frame_number); #end
   #declare I=1; #while (I<=4) // the different sizes
      #declare STARFIELDS_NR = SF_NUMBERS[I-1];
      #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NR)
         #declare STARFIELD_STAR_TYPE = I; //2-4 //1=tiny 2=small 3=medium 4=big 5=large      
         #declare STARFIELD_STAR_INTENSITY = fIntensityFactor*RRand(0.9,1.1,rColor); //(1+STARFIELD*fIntensityFactor)*RRand(0.9,1.1,rColor); //maximum intensity
         #declare STARFIELD_STAR_COLOR = RandomColor(IRand(aColorRange[0], aColorRange[1], rColor), rColor, fColorDev)
         //#declare starfield_seed_no = starfield_seed_no + STARFIELD;
         #declare STARCLUSTER_EXCENTRICITY = <RRand(1.0,2.0,rShape), RRand(1.0,2.0,rShape), RRand(1.0,2.0,rShape)>;
         #declare STARFIELD_DISTRIBU_ANGLE = fDistribution;
         #declare STARCLUSTER_DISTRIBU_ANGLE = <RRand(-STARFIELD_DISTRIBU_ANGLE,STARFIELD_DISTRIBU_ANGLE,rPosition), RRand(-STARFIELD_DISTRIBU_ANGLE,STARFIELD_DISTRIBU_ANGLE,rPosition), RRand(-STARFIELD_DISTRIBU_ANGLE,STARFIELD_DISTRIBU_ANGLE,rPosition)>;
         #declare STARFIELD_STAR_AMOUNT = fBaseAmount/min(1,pow(STARFIELD_STAR_TYPE,3));
         //object { O_StarCluster05(2,rPosition) rotate <0,0,RRand(-180,180,rPosition)> }
         object { O_StarCluster05(2,rPosition) rotate <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)> }
      #declare STARFIELD=STARFIELD+1; #end
   #declare I=I+1; #end
#end

// Star Field 2 - star streak horizontal plane
// ---------------------------------------------------------------------------------------
#macro O_StarField02(SF_NUMBERS, fIntensityFactor, fBaseAmount, vRotation, aColorRange, fColorDev)
   #ifndef(rPosition) #declare rPosition = seed (1234+frame_number); #end
   #declare I=1; #while (I<=4) // the different sizes
      #declare STARFIELDS_NR = SF_NUMBERS[I-1];
      #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NR)
         #declare STARFIELD_STAR_TYPE = I; //2-4 //1=tiny 2=small 3=medium 4=big 5=large      
         #declare STARFIELD_STAR_INTENSITY = fIntensityFactor*RRand(0.9,1.1,rColor); //(1+STARFIELD*fIntensityFactor)*RRand(0.9,1.1,rColor); //maximum intensity
         #declare STARFIELD_STAR_COLOR = RandomColor(IRand(aColorRange[0],aColorRange[1], rColor), rColor, fColorDev) //1=red 2=orange 3=yellow 4=greenish 5=blueish
         //#declare starfield_seed_no = starfield_seed_no + STARFIELD;
         #declare STARCLUSTER_EXCENTRICITY = <RRand(1.0,5.0,rPosition), 1.0, 1.0>;
         #declare STARFIELD_DISTRIBU_ANGLE = 180;
         #declare STARCLUSTER_DISTRIBU_ANGLE = <RRand(-STARFIELD_DISTRIBU_ANGLE,STARFIELD_DISTRIBU_ANGLE,rPosition), RRand(-STARFIELD_DISTRIBU_ANGLE,STARFIELD_DISTRIBU_ANGLE,rPosition), RRand(-STARFIELD_DISTRIBU_ANGLE,STARFIELD_DISTRIBU_ANGLE,rPosition)>;
         #declare STARFIELD_STAR_AMOUNT = fBaseAmount/pow(STARFIELD_STAR_TYPE,3);
         //object { O_StarConcentration01(0.3, rPosition) rotate vRotation+<RRand(-5,5,rPosition),RRand(-5,5,rPosition),RRand(-5,5,rPosition)> }
         object { StarConcentration(1, STARFIELD_STAR_TYPE*2.0,STARFIELD_STAR_TYPE*4.0,STARFIELD_STAR_AMOUNT,array[2]{STARFIELD_STAR_COLOR,STARFIELD_STAR_COLOR}, 2.0, 0.3, rPosition) rotate vRotation+<RRand(-5,5,rPosition),RRand(-5,5,rPosition),RRand(-5,5,rPosition)> }
         #declare STARFIELD_STAR_AMOUNT = fBaseAmount/min(1,pow(STARFIELD_STAR_TYPE,3));
         //object { O_StarConcentration01(1, rPosition) rotate vRotation+<RRand(-5,5,rPosition),RRand(-5,5,rPosition),RRand(-5,5,rPosition)> }
         object { StarConcentration(1, STARFIELD_STAR_TYPE*2.0,STARFIELD_STAR_TYPE*4.0,STARFIELD_STAR_AMOUNT,array[2]{STARFIELD_STAR_COLOR,STARFIELD_STAR_COLOR}, 2.0, 0.3, rPosition) rotate vRotation+<RRand(-5,5,rPosition),RRand(-5,5,rPosition),RRand(-5,5,rPosition)> }
      #declare STARFIELD=STARFIELD+1; #end
   #declare I=I+1; #end
#end

// Star Field 3 - one star concentration
// ---------------------------------------------------------------------------------------
#macro O_StarField03(SF_NUMBERS, fIntensityFactor, fBaseAmount, vRotation, aColorRange, fColorDev)
   #ifndef(rPosition) #declare rPosition = seed (1234+frame_number); #end
   #declare I=1; #while (I<=4) // the different sizes
      #declare STARFIELDS_NR = SF_NUMBERS[I-1];
      #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NR)
         #declare STARFIELD_STAR_TYPE = I; //2-4 //1=tiny 2=small 3=medium 4=big 5=large      
         #declare STARFIELD_STAR_INTENSITY = fIntensityFactor*RRand(0.9,1.1,rColor); //(1+STARFIELD*fIntensityFactor)*RRand(0.9,1.1,rColor); //maximum intensity
         #declare STARFIELD_STAR_COLOR = RandomColor(IRand(aColorRange[0],aColorRange[1], rColor), rColor, fColorDev) //1=red 2=orange 3=yellow 4=greenish 5=blueish
         //#declare starfield_seed_no = starfield_seed_no + STARFIELD;
         #declare STARCLUSTER_EXCENTRICITY = <RRand(1.0,5.0,rPosition), 1.0, 1.0>;
         #declare STARFIELD_DISTRIBU_ANGLE = 180;
         #declare STARCLUSTER_DISTRIBU_ANGLE = <RRand(-STARFIELD_DISTRIBU_ANGLE,STARFIELD_DISTRIBU_ANGLE,rPosition), RRand(-STARFIELD_DISTRIBU_ANGLE,STARFIELD_DISTRIBU_ANGLE,rPosition), RRand(-STARFIELD_DISTRIBU_ANGLE,STARFIELD_DISTRIBU_ANGLE,rPosition)>;
         #declare STARFIELD_STAR_AMOUNT = fBaseAmount/min(1,pow(STARFIELD_STAR_TYPE,3));
         //object { O_StarConcentration02(0.3,rPosition) rotate vRotation+<RRand(-5,5,rPosition),RRand(-5,5,rPosition),RRand(-5,5,rPosition)> }
         object { StarConcentration(2, STARFIELD_STAR_TYPE*2.0,STARFIELD_STAR_TYPE*4.0,STARFIELD_STAR_AMOUNT,array[2]{STARFIELD_STAR_COLOR,STARFIELD_STAR_COLOR}, 2.0, 0.3, rPosition) rotate vRotation+<RRand(-5,5,rPosition),RRand(-5,5,rPosition),RRand(-5,5,rPosition)> }
         #declare STARFIELD_STAR_AMOUNT = 0.3*fBaseAmount/min(1,pow(STARFIELD_STAR_TYPE,3));
         //object { O_StarConcentration02(0.5,rPosition) rotate vRotation+<RRand(-5,5,rPosition),RRand(-5,5,rPosition),RRand(-5,5,rPosition)> }
         object { StarConcentration(2, STARFIELD_STAR_TYPE*2.0,STARFIELD_STAR_TYPE*4.0,STARFIELD_STAR_AMOUNT,array[2]{STARFIELD_STAR_COLOR,STARFIELD_STAR_COLOR}, 2.0, 0.3, rPosition) rotate vRotation+<RRand(-5,5,rPosition),RRand(-5,5,rPosition),RRand(-5,5,rPosition)> }
         #declare STARFIELD_STAR_AMOUNT = 0.1*fBaseAmount/min(1,pow(STARFIELD_STAR_TYPE,3));
         //object { O_StarConcentration02(1,rPosition) rotate vRotation+<RRand(-5,5,rPosition),RRand(-5,5,rPosition),RRand(-5,5,rPosition)> }
         object { StarConcentration(2, STARFIELD_STAR_TYPE*2.0,STARFIELD_STAR_TYPE*4.0,STARFIELD_STAR_AMOUNT,array[2]{STARFIELD_STAR_COLOR,STARFIELD_STAR_COLOR}, 2.0, 0.3, rPosition) rotate vRotation+<RRand(-5,5,rPosition),RRand(-5,5,rPosition),RRand(-5,5,rPosition)> }
      #declare STARFIELD=STARFIELD+1; #end
   #declare I=I+1; #end
#end

// ---------------------------------------------------------------------------------------
// Star Nebula Pigments for SkySphere
// ---------------------------------------------------------------------------------------

// Star Nebula 1
// ---------------------------------------------------------------------------------------
// cloud nebula with stars
#macro P_StarNebula01(aColors, fIntensity, vExcentricity, rSeed)
  #declare STARFIELD_STAR_COLOR = rgb <0.9, 0.95, 1.0>;
  #declare smap1 = pigment_map {
    [0.0 aColors[0] ] // cloud color
    [RRand(0.5,0.9,rSeed) aColors[0] ] // star density = 0.7; 0.1 =high, 0.9=low
    [1.0 STARFIELD_STAR_COLOR*10*fIntensity ] // star intensity
  }
  pigment {
    bozo pigment_map {
      [ 0.0 granite pigment_map { smap1 } scale 1e-3 turbulence 1] // controls spread
      [ 0.8 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no, 1=full
    }
    turbulence 1 scale 0.5*vExcentricity
    rotate <RRand(0,180,rSeed), RRand(0,180,rSeed), RRand(0,180,rSeed)>
  }
#end

// Star Nebula 2
// ---------------------------------------------------------------------------------------
// string nebula with stars
#macro P_StarNebula02(aColors, fIntensity, vExcentricity, rSeed)
  #declare STARFIELD_STAR_COLOR = rgb <0.9, 0.95, 1.0>;
  #declare star5 = pigment { bozo color_map {
    [0.0 STARFIELD_STAR_COLOR*fIntensity ]
    [0.015 STARFIELD_STAR_COLOR*fIntensity ]
    [0.8 rgb 0 transmit 1 ] }
  }
  #declare smap5 = pigment_map { // cloud
    [0.0 aColors[0] ] // cloud color
    [RRand(0.55,0.9,rSeed) star5 ] // controls star density=0.75; 0.1 =high, 0.9=low
    [1.0 STARFIELD_STAR_COLOR*10*fIntensity ] // controls intensity
  }
  pigment {
    wood pigment_map {
      [ 0.0 granite pigment_map { smap5 } scale 1e-4] // controls spread, scale>star size
      [ 0.5 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no, 1=full
    }
    turbulence 0.5 scale vExcentricity
    rotate <RRand(0,180,rSeed), RRand(0,180,rSeed), RRand(0,180,rSeed)>
  }
#end

// Star Nebula 3
// ---------------------------------------------------------------------------------------
// globular cloud nebula with stars
#macro P_StarNebula03(aColors, fIntensity, vExcentricity, rSeed)
  #declare STARFIELD_STAR_COLOR = rgb <0.9, 0.95, 1.0>;
  #declare star5c = pigment { wood color_map {
    [0.0 STARFIELD_STAR_COLOR*fIntensity ]
    [0.10 STARFIELD_STAR_COLOR*fIntensity ]
    [0.3 rgb 0 transmit 1 ] }
  }
  #declare smap5c = pigment_map { // cloud
    [0.0 aColors[0] ] // cloud color
    [RRand(0.1,0.4,rSeed) star5c ] // controls star density=0.6; 0.1 =high, 0.9=low
    [1.0 STARFIELD_STAR_COLOR*10*fIntensity ] // controls intensity
  }
  pigment {
    bozo pigment_map {
      [ 0.0 granite pigment_map { smap5c } scale 1e-5 turbulence 1] // controls spread
      [ 0.6 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no, 1=full
    }
    turbulence 0.2 scale vExcentricity
    rotate <RRand(0,180,rSeed), RRand(0,180,rSeed), RRand(0,180,rSeed)>
  }
#end

// Star Nebula 4
// ---------------------------------------------------------------------------------------
// faint cloud nebula with stars
#macro P_StarNebula04(aColors, fIntensity, vExcentricity, rSeed)
  #declare STARFIELD_STAR_COLOR = rgb <0.9, 0.95, 1.0>;
  #local star4 = pigment { wood color_map {
    [0.0 STARFIELD_STAR_COLOR*fIntensity ]
    [0.10 STARFIELD_STAR_COLOR*fIntensity ]
    [0.4 rgb 0 transmit 1 ] }
  }
  #local smap4 = pigment_map { // cloud
    [0.0 aColors[0] ] // cloud color
    [RRand(0.35,0.65,rSeed) star4 ] // controls star density=0.65; 0.1 =high, 0.9=low
    [1.0 STARFIELD_STAR_COLOR*10*fIntensity ] // controls star intensity
  }
  pigment {
    bozo pigment_map {
      [ 0.0 granite pigment_map { smap4 } scale 1e-4 turbulence 1] // controls spread
      [ 0.5 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no ext, 1=full ext
    }
    turbulence 1 scale 0.5*vExcentricity
    rotate <RRand(0,180,rSeed), RRand(0,180,rSeed), RRand(0,180,rSeed)>
  }
#end

// ---------------------------------------------------------------------------------------
// Cloud Nebula Pigments for SkySphere
// ---------------------------------------------------------------------------------------

// Cloud Nebula 1
// ---------------------------------------------------------------------------------------
// string nebula with stars
#macro P_CloudNebula01(aColors, fIntensity, vExcentricity, rSeed)
  #local cmap011 = pigment_map { // cloud
    [0.0 aColors[0] ] // cloud color
    [0.9 aColors[1]*fIntensity ] // controls star density; 0.1 =high, 0.9=low
  }
  #local cmap01 = pigment_map {
    [ 0.0 granite pigment_map { cmap011 } turbulence 1] // controls spread
    [ 0.8 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no, 1=full
  }
  pigment {
    wood pigment_map {
      [ 0.0 granite pigment_map { cmap01 } scale 2] // controls spread, scale>star size
      [ 1.0 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no, 1=full
    }
    turbulence 0.5 scale vExcentricity
    rotate <RRand(0,180,rSeed), RRand(0,180,rSeed), RRand(0,180,rSeed)>
  }
#end

// Cloud Nebula 2
// ---------------------------------------------------------------------------------------
// dense nebula
#macro P_CloudNebula02(aColors, fIntensity, vExcentricity, rSeed)
  #local cmap021 = pigment_map { // cloud
    [0.0 aColors[0] ] // cloud color
    [1.0 aColors[1]*4*fIntensity ] // controls star density; 0.1 =high, 0.9=low
  }
  #local cmap02 = pigment_map {
    [ 0.0 bozo pigment_map { cmap021 } scale 1 turbulence 1] // controls spread
    [ 1.0 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no, 1=full
  }
  pigment {
    bozo pigment_map {
      [ 0.0 bozo pigment_map { cmap02 } scale 4 turbulence 0.1] // controls spread
      [ 0.5 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no, 1=full
    }
    turbulence 1.1 //0.2
    scale vExcentricity
    rotate <RRand(0,180,rSeed), RRand(0,180,rSeed), RRand(0,180,rSeed)>
  }
#end

// Cloud Nebula 3
// ---------------------------------------------------------------------------------------
// cloud nebula with strings
#macro P_CloudNebula03(aColors, fIntensity, vExcentricity, rSeed)
  #local cmap031 = pigment_map { // cloud
    [0.0 aColors[0] ] // cloud color
    [1.0 aColors[1]*4*fIntensity ] // controls star density; 0.1 =high, 0.9=low
  }
  #local cmap03 = pigment_map {
    [ 0.0 granite pigment_map { cmap031 } scale 20 turbulence 0] // controls spread
    [ 1.0 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no, 1=full
  }
  pigment {
    granite pigment_map {
      [ 0.0 bozo pigment_map { cmap03 } scale 20 turbulence 0] // controls spread
      [ 0.3 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no, 1=full
    }
    turbulence 0.02 scale 5*vExcentricity
    rotate <RRand(0,180,rSeed), RRand(0,180,rSeed), RRand(0,180,rSeed)>
  }
#end

// Cloud Nebula 4
// ---------------------------------------------------------------------------------------
// faint cloud nebula with stars
#macro P_CloudNebula04(aColors, fIntensity, vExcentricity, rSeed)
  #local cmap041 = pigment_map { // cloud
    [0.0 aColors[0] ] // cloud color
    [1.0 aColors[1]*10*fIntensity ] // controls star density; 0.1 =high, 0.9=low
  }
  #local cmap04 = pigment_map {
    [ 0.0 granite pigment_map { cmap041 } scale 10 turbulence 1] // controls spread
    [ 1.0 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no ext, 1=full ext
  }
  pigment {
    bozo pigment_map {
      [ 0.0 granite pigment_map { cmap04 } scale 20 turbulence 0] // controls spread
      [ 0.7 rgb 0 transmit 1 ] // space; controls extension of the cloud field; 0=no ext, 1=full ext
    }
    turbulence 0 scale 0.5*vExcentricity
    rotate <RRand(0,180,rSeed), RRand(0,180,rSeed), RRand(0,180,rSeed)>
  }
#end

// ---------------------------------------------------------------------------------------
// Dense Cloud Nebula Objects
// ---------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------
// Development Objects
// ---------------------------------------------------------------------------------------

#ifndef (starfield_show_box)
   #declare starfield_show_box=false; 
   #if (starfield_show_box)
      #declare BOX_SIZE = 10;
      #declare S_Box = box { <-BOX_SIZE,-BOX_SIZE,-BOX_SIZE> <BOX_SIZE,BOX_SIZE,BOX_SIZE> }
      object { S_Box
         pigment { P_StarCluster01 }
         rotate <30,30,0>
         finish {ambient 0.5}
         }
   #end
#end

// ---------------------------------------------------------------------------------------
// Sky Sphere Objects
// ---------------------------------------------------------------------------------------

#declare scol01 = rgb <0.3,0.6,0.95>;
#declare scol02 = rgb <0.5,0.8,0.95>;
#declare scol03 = rgb <0.6,0.8,1.0>;
#declare scol04 = rgb <0.7,1.0,1.0>;
#declare scol05 = rgb <0.9,0.95,1.0>;
#declare scol06 = rgb <0.9,1.0,1.0>;

// Small stars with high varying intensity
#declare stars01 = pigment { spotted color_map {
     [0.1 rgb <0.6,0.8,1.0>*2 ] // intensity variance=(0.1 & *2); color=rgb
     [0.3 rgb 0 transmit 1 ]             // density
     }
   scale 1e-3
}

// Tiny stars with low varying intensity
#declare stars02 = pigment {granite color_map {
  [0.70 rgb 0 transmit 1]
  [1.00 scol05]
  }
  scale 1e-2
}

// Tiny stars with high intensity
#declare stars03 = pigment {leopard color_map {
  [0.50 rgb 0 transmit 1 ]       // density=0.5
  [1.00 scol05]
  }
  scale 1e-5        // size,amount
}

// SKYSPHERE
// ---------------------------------------------------------------------------------------
/*
#declare S_Seed_1 = seed(starfield_seed_no);
#declare S_Seed_2 = seed(starfield_seed_no+324);
#declare S_Seed_3 = seed(starfield_seed_no+1);
#declare tx = rand(S_Seed_1);
#declare ty = rand(S_Seed_2);
#declare tz = rand(S_Seed_3);



#declare smap7 = pigment_map {
      [ 3.0 stars01 ]
      [ 3.0 stars02 ]
      [ 3.0 stars03 ]
    }

// Sky Sphere Object 1
// ---------------------------------------------------------------------------------------
#declare O_SkySphere_1 = sky_sphere {
  pigment { stars03 scale 0.1}
  pigment { average pigment_map { smap7 } scale 0.1 }
  pigment { star4 }
  pigment { bozo pigment_map { pmap4 } scale 0.5 turbulence 1 }
  pigment { average pigment_map { pmap6 } scale 0.1 noise_generator 3 turbulence 0 translate <tx,ty,tz>}
  pigment { average pigment_map { smap7 } scale 0.1 }
  pigment { bozo pigment_map { pmap3 } scale 0.5 turbulence 1 }
}

// Sky Sphere Object 2
// ---------------------------------------------------------------------------------------
#declare O_SkySphere_2 = sky_sphere {
   pigment { average
      pigment_map {
         [3 stars03 scale 0.1 ]
         [3 P_StarNebula01 ]
         [3 P_StarNebula04 ]
      }
   }
}

// Sky Sphere Object 3
// ---------------------------------------------------------------------------------------
#declare O_SkySphere_3 = sky_sphere {
  pigment { P_StarCluster01 scale 0.1 }
}

// Sky Sphere Object 4
// ---------------------------------------------------------------------------------------
#declare O_SkySphere_4 = sky_sphere {
pigment { average
   pigment_map {
     [2 stars03 scale 1.0 ]
     [2 P_StarCluster01 scale 0.1 ]
     }
   }
}

// Sky Sphere Object 5
// ---------------------------------------------------------------------------------------
#declare O_SkySphere_5 = sky_sphere {
  pigment { P_StarCluster02 scale 0.1 rotate <0, 0, 0> }
}

// Sky Sphere Object 6
// ---------------------------------------------------------------------------------------
#declare O_SkySphere_6 = sky_sphere {
pigment { average
   pigment_map {
     [3 P_StarCluster02 scale 0.1 rotate <90, 0, 0> ]
     [3 P_StarCluster01 scale 0.1 ]
     [3 stars03 scale 0.1 ]
     }
   }
}
*/
// Sky Sphere Object 7
// ---------------------------------------------------------------------------------------
/*
#declare O_SkySphere_7 = sky_sphere {
  pigment { P_StarCluster03 scale 0.1 rotate STARCLUSTER_DISTRIBU_ANGLE }
}

#switch (STARFIELD_SKYSPHERE_NR)
   #case (1) sky_sphere {O_SkySphere_1} #break
   #case (2) sky_sphere {O_SkySphere_2} #break
   #case (3) sky_sphere {O_SkySphere_3} #break
   #case (4) sky_sphere {O_SkySphere_4} #break
   #case (5) sky_sphere {O_SkySphere_5} #break
   #case (6) sky_sphere {O_SkySphere_6} #break
   #case (7) sky_sphere {O_SkySphere_7} #break
   #case (8) sky_sphere { pigment { rgb 0.1 } } #break
#end
*/


//#end
//#ifdef (USE_OBJECT_NUMBER)

//EOF
