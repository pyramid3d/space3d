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
// File       : virtual_rings.inc
// Description: Planet from space with weather, atmosphere, and simple background
// Version    : 0.47
// Date       : 2011-04-05
// Author     : Pyramid
// Scale      : 1 POV Unit = 1km
// ---------------------------------------------------------------------------------------

// Randomize Color
// ---------------------------------------------------------------------------
/*
#macro surface_color_mono(base_color_tone, color_deviation, rSeed)
   #local base_color_dev = RRand(-color_deviation/255,color_deviation/255,rSeed);
   #local r = base_color_tone.red+base_color_dev;
   #local g = base_color_tone.green+base_color_dev;
   #local b = base_color_tone.blue+base_color_dev;
   color rgb <r, g, b>
#end
#macro surface_color_chromo(base_color_tone, color_deviation, rSeed)
   #local base_color_dev = color_deviation/100;
   #local base_color_component = IRand(1,3,rSeed);
   #local r = base_color_tone.red;
   #local g = base_color_tone.green;
   #local b = base_color_tone.blue;
   #if (base_color_component=1)
      #local r = base_color_tone.red+RRand(-base_color_dev,base_color_dev,rSeed);
   #end
   #if (base_color_component=2)
      #local g = base_color_tone.green+RRand(-base_color_dev,base_color_dev,rSeed);
   #end
   #if (base_color_component=3)
      #local b = base_color_tone.blue+RRand(-base_color_dev,base_color_dev,rSeed);
   #end
   color rgb <r, g, b>
#end
*/

// ---------------------------------------------------------------------------------------
// Texture Objects
// ---------------------------------------------------------------------------------------

#macro RingMap(cRingBase, bMonoColor, fColorDev, rColor)
  #ifndef (cRingBase) #declare cRingBase = color rgb <0.557, 0.490, 0.460>; #end
  #ifndef (fColorDev) #declare fColorDev = 10; #end
  #declare fFilt     = 0;
  #declare fSteps    = IRand(20,254,rColor);
   #local I=0; #while(I<1)
      #if (bMonoColor)
         #local cColor     = surface_color_mono(cRingBase, fColorDev, rColor);
      #else
         #local cColor     = surface_color_chromo(cRingBase, fColorDev, rColor);
      #end
      #local fIntensity = RRand(2,4,rColor);
      #local fTransp    = RRand(0.1,0.7,rColor);
      #local fJitter    = RRand(-0.9*1/fSteps,2.9*1/fSteps,rColor);
      [min(1,I+fJitter) cColor*fIntensity transmit fTransp filter fFilt ]
   #local I=I+1/fSteps; #end
#end

#macro VRingTexture(fRadiusInner, fRadiusOuter, fRings, cRingBase, bMonoColor, fColorDev, rRing)
  #declare rStructure = seed(82376+frame_number);
  #declare rColor     = seed(9987765+frame_number);
  object {
    union {
      #declare fRingWidth = fRadiusOuter-fRadiusInner; // The width of the ring system, inner radius being 1 unit.
      #declare iNoRings = fRings;
       #local I=0; #while(I<iNoRings)
          box { <-fRadiusOuter, 0, -fRadiusInner-I*fRingWidth/iNoRings> <fRadiusOuter, 1e-10, -fRadiusInner-(I+1)*fRingWidth/iNoRings>
            pigment { gradient z color_map { RingMap(cRingBase, bMonoColor, fColorDev, rRing) }
            scale fRadiusInner+(I+1)*fRingWidth/iNoRings }
          finish {ambient 0 diffuse 4} }
       #local I=I+1; #end
    }
  }
#end

// ---------------------------------------------------------------------------------------
// Ring Object
// ---------------------------------------------------------------------------------------

#macro VRing(fRadiusInner, fRadiusOuter, fRings, cRingBase, bMonoColor, fColorDev, rRing)
  #declare fFilt  = 0;
  #if (fRings>254) #declare fRings = 254; #end
  #if (fRings=0) #declare fRings = IRand(10,254,rRing); #end
  disc { <0, 0, 0> y,
    1, fRadiusInner/fRadiusOuter // outer radius, inner radius
    pigment { onion
      color_map {
        #local I=0; #while(I<=1)
          #if (bMonoColor)
             #local cColor = surface_color_mono(cRingBase, fColorDev, rRing);
          #else
             #local cColor = surface_color_chromo(cRingBase, fColorDev, rRing);
          #end
          #local fIntensity = RRand(0.5,1.5,rRing);
          #local fTransp    = RRand(0.1,0.5,rRing);
          #local fJitter    = RRand(-0.9*1/fRings,2.9*1/fRings,rRing);
          [ min(1,I+fJitter) cColor*fIntensity transmit fTransp ] //filter fFilt
        #local I=I+1/fRings; #end
      }
    }
    finish {ambient 0 diffuse 1}
    scale fRadiusOuter
    hollow on
  }
#end
