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
// @file    : space3d_random.pov
// @brief   : Space3D random scenes
// @version : 2019-05-26
// @created : 2014-03-10
// @author  : pyramid
// @internet: https://openteq.wordpress.com/portfolio/space3d/
// @internet: http://space3d.no.sapo.pt/ (discontinued)
// @scale   : 1 POV unit = 1 km
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// Prerequisites
// ---------------------------------------------------------------------------

// set fixed scene number to randomize one scene aspect
// for example planet, or star background
#declare SCENE_NUMBER = 1;

#declare SHOW_LABEL = true;
#declare SHOW_WATERMARK = true;

// Quality Settings for test & sample or final rendering
#declare RENDER_QUALITY = 1; // 1=full; 0=fast (mostly unused)
#declare SHOW_DEBUG = false;
#declare CREATE_LOGFILE = false;

// ---------------------------------------------------------------------------
// Include Files
// ---------------------------------------------------------------------------
#include "space3d.inc"


// ---------------------------------------------------------------------------
// Generic planet randomizer template
// Space3D Test 104
// Space3D Random 3
// ---------------------------------------------------------------------------
#if (SCENE_NUMBER = 3)

  #declare fPlanetRadius = 4500;
  Sun(<fPlanetRadius*20, fPlanetRadius*0, -fPlanetRadius*100>, 1)
  Camera1(fPlanetRadius) // for scene rendering
  //Camera6() // for texturing
  //CameraTexture() // for texturing


  #declare iPlanetType = IRand(1,4,seed(123+frame_number));
  #declare n = 2011 + frame_number;
  #declare cBaseColor = ColorHSL(RRand(0,255,seed(n)), RRand(10,30,seed(n)), RRand(50,70,seed(n)));

  #switch(iPlanetType)
    #case(1)
      // syntax: GasGiant(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanetSeed)
      GasGiant(fPlanetRadius, cBaseColor, RRand(0,50,seed(n)), IRand(0,1,seed(n)), seed(n))
    #break
    #case(2)
      // syntax: DirtPlanet(fPlanetRadius, cBaseColor, fColorDev, bMonoColor, rPlanetSeed)
      DirtPlanet(fPlanetRadius, cBaseColor, RRand(0,50,seed(n)), IRand(0,1,seed(n)), seed(n))
    #break
    #case(3)
      // syntax: TerranPlanet(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aPlanetSeedNumbers)
      TerranPlanet(fPlanetRadius, array[1] {<0,0,0>}, RRand(0,50,seed(n)), IRand(0,1,seed(n)), array[4] {20210+n,20210+n,20210+n,20210+n})
    #break
    #case(4)
      // syntax: TrantorPlanet(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aPlanetSeedNumbers)
      TrantorPlanet(fPlanetRadius, array[1] {<0,0,0>}, RRand(0,50,seed(n)), IRand(0,1,seed(n)), array[7] {20210+n,20210+n,20210+n,20210+n,1+n,2+n,3+n})
    #break
  #end
  //QuickPlanet(fPlanetRadius)
  //GasGiant1(fPlanetRadius, rgb <0.8,0.7,0.5>, 20, 1, seed(n))
  //DirtPlanet(fPlanetRadius, cBaseColor, RRand(0,50,seed(n)), IRand(0,1,seed(n)), seed(n))
  //TerranPlanet(fPlanetRadius, array[1] {<0,0,0>}, RRand(0,50,seed(n)), IRand(0,1,seed(n)), array[4] {20210+n,20210+n,20210+n,20210+n})
  //TrantorPlanet(fPlanetRadius, array[1] {<0,0,0>}, RRand(0,50,seed(n)), IRand(0,1,seed(n)), array[7] {20210+n,20210+n,20210+n,20210+n,1+n,2+n,3+n})

  //Starfield()

  //label
  #if (SHOW_LABEL)
    TitleText("Random Planet", 10, rgb <0.3,0.9,0.6>)
  #end
  
#end


// ---------------------------------------------------------------------------
// terran planet selector
// Space3D Gallery 34
// Space3D Random 2
// ---------------------------------------------------------------------------
#if (SCENE_NUMBER = 2)

  #declare fPlanetRadius = 8000;

  //label camera
  #declare vCamPos = <0, 0, -3.5*fPlanetRadius>;
  #declare vCamRot = <3, -6.5, 0>; // x-: text moves up; y+: text moves right
  #declare fCamAng = 50;
  Camera(<0, 0, -3.5*fPlanetRadius>, <-fPlanetRadius*0.4, -fPlanetRadius*0.2, 0>, fCamAng) //full
  Sun(<fPlanetRadius*20, fPlanetRadius*0, -fPlanetRadius*100>, 1)

  #declare vPlanetRotation = <0,0,0>;
  #declare vPlanetPosition = <0,0,0>;
  #declare show = 1; #if (show)
    InitColors()
    #declare rPlanet = seed(20210+frame_number); //6,43
    #declare cSurfaceColor = array[5]; 
    /*#local c=0; #while(c<5)
      #declare cSurfaceColor[c] = cStone[IRand(0,52,rPlanet)];
      //#declare cSurfaceColor[c] = cSand[frame_number-1];
    #local c=c+1; #end*/
    #local c=0; #while(c<5)
      //0-red; 21-brown; 30-orange; 59-yellow; 120-green; 179-cyan; 240-blue; 300-magenta;
      #declare cSurfaceColor[c] = ColorHSL(RRand(10,140,rPlanet),RRand(10,70,rPlanet),RRand(30,90,rPlanet));
      //#declare cSurfaceColor[c] = ColorHSL(36*frame_number,RRand(90,100,rPlanet),RRand(50,50,rPlanet));
    #local c=c+1; #end
    // use set surface colors
    //#declare cSurfaceColor = array[5] {rgb <0.4392, 0.3686, 0.0902>, rgb <0.6824, 0.8098, 0.2510>, rgb <0.7020, 0.6588, 0.4824>, rgb <0.0924, 0.3098, 0.0510>, rgb <0.5392, 0.4686, 0.0902>}; 
    //#declare cSurfaceColor = array[5] {rgb <0.4392, 0.3686, 0.0902>, rgb <0.6824, 0.8098, 0.2510>, rgb <0.7020, 0.6588, 0.4824>, rgb <0.0924, 0.3098, 0.0510>, rgb <0.5392, 0.4686, 0.0902>}; 
    //#declare cSurfaceColor = array[1] {rgb <0,0,0>};
    //params: TerranPlanet(fPlanetRadius, aBaseColors[6]{Field,Forrest,Hill,Desert,Jungle,Ocean}, fColorDev, bMonoColor, aPlanetSeed[7]{1:rStructure,2:rTexture,3:rColor,4:rOcean,5:rIce,6:rRiver,7:rLight})
    object { TerranPlanet(fPlanetRadius, cSurfaceColor, RRand(0,50,rPlanet), 1, array[7] {20210+frame_number,888112+frame_number,237221+frame_number,1118+frame_number,2019+frame_number,20191118+frame_number,18192021+frame_number}) rotate vPlanetRotation translate vPlanetPosition }
  #end
  #declare show = 0; #if (show)
    #declare cAtmosphereColor = rgb <0.880, 0.750, 0.650>;
    #declare vPlanetRotation = <0,0,0>;
    object { Atmosphere(fPlanetRadius, 1.04, cAtmosphereColor) rotate vPlanetRotation translate vPlanetPosition }
  #end

  Starfield()

  //label
  #declare locSHOW_LABEL = 1; // override global; 0-false, 1-true
  #if (SHOW_LABEL & locSHOW_LABEL)
    //#declare cLabel = rgb <0.9,0.9,0.0>; // yellow
    #declare cLabel = rgb <0.3,0.9,0.6>; // turqoise
    #declare sTitle = "Terran Planet"
    object { TitleText(sTitle, 8, cLabel) translate <0,0,0> } //1024, 2048
  #end
  #declare locSHOW_WATERMARK = 1; // override global; 0-false, 1-true
  #if (SHOW_WATERMARK & locSHOW_WATERMARK)
    #declare cMark = rgb 1; // for testing position
    #declare cMark = rgb <0.3,0.3,0.3>; // almost invisible
    object { WaterMark("2009 pedrabella Space3D", 3.0, cMark) translate <0.01,-0.02,0> }
  #end

#end


// ---------------------------------------------------------------------------
// Random Quick Planet
// ---------------------------------------------------------------------------

#if (SCENE_NUMBER = 1)

  #declare fPlanetRadius = 8900;
  CameraPos(<0,0,-fPlanetRadius*2.5>)
  Sun(<-1e6,0,-1e6>, 1)

  // planet
  #declare show = 1; #if (show) 
    #declare vPlanetRotation = <0, -40, 0>;
    #declare vPlanetPosition = <0, 0, 0>;

    // seed sequence: rStructure,rTexture,rColor,rOcean,rIce,rRiver,rLight
    #declare s = frame_number;
    #declare rPlanet = seed(2021+s);
    #declare aSurface = array[4] {87670+s,888112+s,637237+s,1118+s};
    #declare rColor = seed(1116+s);

    // colors
    InitColors()
    #declare cSurfaceColors = array[6]; 
    #local c=0; #while(c<5)
      #declare cSurfaceColors[c] = cGreen[IRand(0,35,rColor)];
    #local c=c+1; #end
    #declare cSurfaceColors[5]  = rgb <0.149, 0.435, 0.698>; // ocean color
    //#local c=3; #while(c<5)
    //  #declare cSurfaceColors[c] = ColorHSL(RRand(10,60,rPlanet),RRand(20,50,rPlanet),RRand(30,70,rPlanet));
    //#local c=c+1; #end
    
    // planet
    //object { TerranPlanet(fPlanetRadius, cSurfaceColors, RRand(0,50,rPlanet), 1, aSurface) rotate vPlanetRotation translate vPlanetPosition }
    object { QuickPlanet(fPlanetRadius) rotate vPlanetRotation translate vPlanetPosition }
  #end

  // clouds
  // interesting seeds 2021+: 9, 19, 23 (light), 24, 37, 42, 99 (heavy)
  #declare show = 0; #if (show)
    #declare rCloud = seed(2021+23);
    object { Clouds(0.05, fPlanetRadius+5, rgb <1,1,1>, rCloud) rotate vPlanetRotation translate vPlanetPosition }
  #end

  // atmpsphere
  #declare show = 0; #if (show)
    #declare cAtmosphereColor = rgb <0.4, 0.7, 0.9>;
    #declare vPlanetRotation = <0,0,0>;
    object { Atmosphere(fPlanetRadius, 1.05, cAtmosphereColor) translate vPlanetPosition }
  #end

#end //SCENE

//EOF
