// ---------------------------------------------------------------------------
// Space3D
// Free POV-Ray script for space scenes rendering
// Copyright (C) 2005-2009 Pyramid
// Contact: pyramid@sapo.pt
// Internet: http://space3d.no.sapo.pt/
//
// This script is distributed with ABSOLUTELY NO WARRANTY;
// See the GNU General Public License for more details,
// which can be found in doc/SPACE3D_LICENSE.txt
//
// Persistence of Vision Ray Tracer Scene Description File
// File       : starfield_gallery.pov
// Description: Implementation examples for starfield.inc
// Version    : 0.25
// Date       : 2012-04-19
// Author     : Pyramid
// Internet   : http://space3d.no.sapo.pt/
// Scale      : 1 POV Unit = 1km
// ---------------------------------------------------------------------------
// Adapted from SunChange.pov for POV-Ray Version: 3.1 or MegaPOV
// Desc: The Sun, with flares and corona.  Animatable to an extent.
// Date: 2000-08
// Auth: Bob Hughes
// Mail: persistenceofv@aol.com?subject=PoV-Scene&body=Concerning%20POV-Ray
// omniVerse http://users.aol.com/persistenceofv/all.htm
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------------------
// User Settings
// ---------------------------------------------------------------------------------------

#declare Use_MegaPOV=no;
#if (Use_MegaPOV=yes)
  #version unofficial MegaPov 0.6;
#end

// ---------------------------------------------------------------------------------------
// Close Star Macro
// ---------------------------------------------------------------------------------------

#macro Star(fRadius)
// max fRadius = 5e6

  #if (fRadius=0) //|(fRadius>5e6)
    #declare fRadius = 1e6;
    //#declare fRadius = 6.955*10e8;
  #end
  //#if (fIntensity=0) //|(fRadius>5e6)
  #declare fIntensity = 3.0;
  //#end
  
  // variable for Sun changes (can change this manually: use 0 to 1)
  //#declare TimeLapse=clock;
  #declare TimeLapse = 1.0; //0.9;
  
  // variables for Sunlight fading or filtering
  #declare EXT=TimeLapse; // extinction, smaller is brighter
  #declare Sc=TimeLapse; // emission, smaller is brighter
  #declare Si=TimeLapse/2.5; //intensity, smaller number is brighter


  union {
    // may want to use other than the "4" below or something else altogether
    // be warned the light color changes the media appearance
    light_source { 0, fIntensity-(Si*4)
      // area_light <.432,0,0>, <0,.432,0>, 3, 3 jitter adaptive 1
      // orient circular
      media_interaction on media_attenuation off
    }
  
    // Sun
    #declare Space = density {rgb 0}

    #declare Corona = density {
      radial turbulence .15 frequency 15
      density_map {
        [0 rgb <.125,.5,1.33>*.025*(1/fRadius)]
        [1 rgb <.25,.67,1.25>*(.033+(Si/15))*(1/fRadius)]
      }
      sine_wave scale <.25,.125,.25> rotate <5,0,5>
    }

    #declare Flares = density {
      marble phase (.55+(TimeLapse/10)) turbulence 5 frequency 1.5
      density_map {
        [0 rgb .025*(1/fRadius)]
        [.75 rgb .05*(1/fRadius)]
        [.85 rgb <.5,.33,.25>*(.1+(Si/1.33))*(1/fRadius)]
        [.925 rgb <.5,.33,.25>*(.1+(Si/2))*(1/fRadius)]
        [1 rgb <.5,.33,.25>*(.1+(Si/.33))*(1/fRadius)]
      }
      triangle_wave scale .67 rotate <60,45,15>
    }

    #declare Photosphere = density {
      bozo phase (TimeLapse/100) turbulence <1,.5,.25>*1.3
      //warp {turbulence <1,.5,.25>*1.3 octaves 2 lambda 1.5 omega 0.5}
      density_map {
        [0 rgb 0]
        [.95 rgb <1.125,1,.9>*(1.3+(Si/3))*(1/fRadius)]
        [1 rgb <1.125,1,.9>*(.9+(Si/6))*(1/fRadius)]
      }
      ramp_wave scale .015
    }

    #declare Surface = density {
      crackle phase (TimeLapse/50)
      //warp {turbulence <1,.5,.25> octaves 2 lambda 1.25 omega 0.3}
      density_map {
        [.025*TimeLapse rgb .15*(1/fRadius)]
        [.05*(.75+TimeLapse) rgb .3*(1/fRadius)]
        [1 rgb <.75,.5,.33>*(2.5-(Si/1.25))*(1/fRadius)]
      }
      scallop_wave scale .005
    }

    #declare Interior = density {
      bozo phase (TimeLapse/100) turbulence <1,.5,.25>*.3
      //warp {turbulence <1,.5,.25>*.3 octaves 2 lambda 1 omega 0.2}
      density_map {
        [0 rgb 0]
        [.09 rgb <1.125,1,.9>*(.3+(Si/3))*(1/fRadius)]
        [1 rgb <1.125,1,.9>*(.9+(Si/6))*(1/fRadius)]
      }
      ramp_wave scale .15
    }
    
    sphere { 0, 1 pigment {rgbt 1}
      interior { media {
        #if (Use_MegaPOV=yes)
         method 2 intervals 2 samples 2,2
        #else
         intervals 8 samples 5,10
        #end
        emission <1,.75,.25>*((2-(Si/.25))+(1-Sc))
        absorption <.33,.5,.67>*(.1+(Si*10))
        scattering {4,<1,.67,.33>*1.33 extinction (EXT/20)}
        density {
          spherical turbulence <.000125,.00015,.0002>
          density_map {
            [.025 Space] // end of Sun atmosphere
            [.25 Corona] // solar corona
            [.45 Corona] // solar corona inner edge
            [.5 Flares] // solar flares
            [.515 Photosphere] // solar photosphere
            [.5167+(TimeLapse/30) Photosphere] // solar photosphere
            [.568+(TimeLapse/15) Surface] // solar surface
            [.75+(TimeLapse/7.5) Surface] // solar subsurface
            [1 Interior] // solar interior
          }
        }
      } }
      rotate 5*TimeLapse*y // a little rotation for animation
      hollow
      no_shadow
    }
    scale fRadius
  } // union

#end //macro

#macro StarColor(fRadius, cColor)
// max fRadius = 5e6

  #if (fRadius=0) //|(fRadius>5e6)
    #declare fRadius = 1e6;
    //#declare fRadius = 6.955*10e8;
  #end
  //#if (fIntensity=0) //|(fRadius>5e6)
  #declare fIntensity = 3.0;
  //#end
  
  // variable for Sun changes (can change this manually: use 0 to 1)
  //#declare TimeLapse=clock;
  #declare TimeLapse = 1.0; //0.9;
  
  // variables for Sunlight fading or filtering
  #declare EXT=TimeLapse; // extinction, smaller is brighter
  #declare Sc=TimeLapse; // emission, smaller is brighter
  #declare Si=TimeLapse/2.5; //intensity, smaller number is brighter


  union {
    // may want to use other than the "4" below or something else altogether
    // be warned the light color changes the media appearance
    light_source { 0, fIntensity-(Si*4)
      // area_light <.432,0,0>, <0,.432,0>, 3, 3 jitter adaptive 1
      // orient circular
      media_interaction on media_attenuation off
    }
  
    // Sun
    #declare Space = density {rgb 0}

    #declare Corona = density {
      radial turbulence .15 frequency 15
      density_map {
        [0 rgb cColor*.025*(1/fRadius)]
        [1 rgb cColor*(.033+(Si/15))*(1/fRadius)]
      }
      sine_wave scale <.25,.125,.25> rotate <5,0,5>
    }

    #declare Flares = density {
      marble phase (.55+(TimeLapse/10)) turbulence 5 frequency 1.5
      density_map {
        [0 rgb .025*(1/fRadius)]
        [.75 rgb .05*(1/fRadius)]
        [.85 rgb cColor*(.1+(Si/1.33))*(1/fRadius)]
        [.925 rgb cColor*(.1+(Si/2))*(1/fRadius)]
        [1 rgb cColor*(.1+(Si/.33))*(1/fRadius)]
      }
      triangle_wave scale .67 rotate <60,45,15>
    }

    #declare Photosphere = density {
      bozo phase (TimeLapse/100) turbulence <1,.5,.25>*1.3
      //warp {turbulence <1,.5,.25>*1.3 octaves 2 lambda 1.5 omega 0.5}
      density_map {
        [0 rgb 0]
        [.95 rgb cColor*(1.3+(Si/3))*(1/fRadius)]
        [1 rgb cColor*(.9+(Si/6))*(1/fRadius)]
      }
      ramp_wave scale .015
    }

    #declare Surface = density {
      crackle phase (TimeLapse/50)
      //warp {turbulence <1,.5,.25> octaves 2 lambda 1.25 omega 0.3}
      density_map {
        [.025*TimeLapse rgb .15*(1/fRadius)]
        [.05*(.75+TimeLapse) rgb .3*(1/fRadius)]
        [1 rgb cColor*(2.5-(Si/1.25))*(1/fRadius)]
      }
      scallop_wave scale .005
    }

    #declare Interior = density {
      bozo phase (TimeLapse/100) turbulence <1,.5,.25>*.3
      //warp {turbulence <1,.5,.25>*.3 octaves 2 lambda 1 omega 0.2}
      density_map {
        [0 rgb 0]
        [.09 rgb cColor*(.3+(Si/3))*(1/fRadius)]
        [1 rgb cColor*(.9+(Si/6))*(1/fRadius)]
      }
      ramp_wave scale .15
    }
    
    sphere { 0, 1 pigment {rgbt 1}
      interior { media {
        #if (Use_MegaPOV=yes)
         method 2 intervals 2 samples 2,2
        #else
         intervals 8 samples 5,10
        #end
        emission cColor*((2-(Si/.25))+(1-Sc))
        absorption cColor*(.1+(Si*10))
        scattering {4,cColor*1.33 extinction (EXT/20)}
        density {
          spherical turbulence <.000125,.00015,.0002>
          density_map {
            [.025 Space] // end of Sun atmosphere
            [.25 Corona] // solar corona
            [.45 Corona] // solar corona inner edge
            [.5 Flares] // solar flares
            [.515 Photosphere] // solar photosphere
            [.5167+(TimeLapse/30) Photosphere] // solar photosphere
            [.568+(TimeLapse/15) Surface] // solar surface
            [.75+(TimeLapse/7.5) Surface] // solar subsurface
            [1 Interior] // solar interior
          }
        }
      } }
      rotate 5*TimeLapse*y // a little rotation for animation
      hollow
      no_shadow
    }
    scale fRadius
  } // union

#end //macro

