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
// @file    : s3d_uranus_rings.inc
// @brief   : uranus planetary rings
// @version : 2019-05-25
// @created : 2011-04-05
// @author  : pyramid
// @internet: https://openteq.wordpress.com/portfolio/space3d/
// @scale   : 1 POV unit = 1 km
// ---------------------------------------------------------------------------
// based on dimensions from
// http://www.evildrganymede.net/art/planets/uranus.htm
// ---------------------------------------------------------------------------------------

#declare Tint = colour rgb <0.8, 0.9, 0.9>*1.79;
#declare Filt =0.6;
#declare Trans = 0.0;
#declare USeed = seed(6434591);
#declare URingStep = 0.20;

#declare RingTexture = texture {
   pigment {
      onion
      colour_map {
         #local I=0; #while(I<1)
         [ I color rand(USeed)*Tint transmit Trans*rand(USeed) filter Filt]
         #local I=I+URingStep; #end
      }
   }
   finish {ambient 0.2 diffuse 2.8}
}

// realistic
//------------------------
#declare SixRing = disc {                        
   <0, 0, 0> y,
   41910,   // outer radius
   41900    // inner radius
   texture { RingTexture }
  hollow on
}

#declare FiveRing = disc {                        
   <0, 0, 0> y,
   42305,   // outer radius
   42300    // inner radius
   texture { RingTexture }
  hollow on
}

#declare FourRing = disc {                        
   <0, 0, 0> y,
   42610,   // outer radius
   42600    // inner radius
   texture { RingTexture }
  hollow on
}

#declare ARing = disc {                        
   <0, 0, 0> y,
   44807,   // outer radius
   44800    // inner radius
   texture { RingTexture }
  hollow on
}

#declare BRing = disc {                        
   <0, 0, 0> y,
   45708,   // outer radius
   45700    // inner radius
   texture { RingTexture }
  hollow on
}

#declare EtaRing = disc {                        
   <0, 0, 0> y,
   47260,   // outer radius
   47200    // inner radius
   texture { RingTexture }
  hollow on
}

#declare GammaRing = disc {                        
   <0, 0, 0> y,
   47710,   // outer radius
   47700    // inner radius
   texture { RingTexture }
  hollow on
}

#declare DeltaRing = disc {                        
   <0, 0, 0> y,
   48310,   // outer radius
   48300    // inner radius
   texture { RingTexture }
  hollow on
}

#declare EpsilonRing = disc {                        
   <0, 0, 0> y,
   51300,   // outer radius
   51200    // inner radius
   texture { RingTexture }
  hollow on
}

// fictional
//------------------------
#declare SixRing = disc {                        
   <0, 0, 0> y,
   42410,   // outer radius
   41900    // inner radius
   texture { RingTexture }
  hollow on
}

#declare FiveRing = disc {                        
   <0, 0, 0> y,
   42505,   // outer radius
   42300    // inner radius
   texture { RingTexture }
  hollow on
}

#declare FourRing = disc {                        
   <0, 0, 0> y,
   42710,   // outer radius
   42600    // inner radius
   texture { RingTexture }
  hollow on
}

#declare ARing = disc {                        
   <0, 0, 0> y,
   45607,   // outer radius
   44800    // inner radius
   texture { RingTexture }
  hollow on
}

#declare BRing = disc {                        
   <0, 0, 0> y,
   46908,   // outer radius
   45700    // inner radius
   texture { RingTexture }
  hollow on
}

#declare EtaRing = disc {                        
   <0, 0, 0> y,
   47660,   // outer radius
   47200    // inner radius
   texture { RingTexture }
  hollow on
}

#declare GammaRing = disc {                        
   <0, 0, 0> y,
   47710,   // outer radius
   47700    // inner radius
   texture { RingTexture }
}

#declare DeltaRing = disc {                        
   <0, 0, 0> y,
   50310,   // outer radius
   48300    // inner radius
   texture { RingTexture }
  hollow on
}

#declare EpsilonRing = disc {                        
   <0, 0, 0> y,
   51300,   // outer radius
   51200    // inner radius
   texture { RingTexture }
  hollow on
}

#declare Uranus_Rings = object {
   union {
      disc {SixRing}
      disc {FiveRing}
      disc {FourRing}
      disc {ARing}
      disc {BRing}
      disc {EtaRing}
      disc {GammaRing}
      disc {DeltaRing}
      disc {EpsilonRing}
    hollow on
   }
  hollow on
}

#macro UranusRings()
  object {
    Uranus_Rings 
    //rotate <0,0,2> // inclination 98º
  }
#end
