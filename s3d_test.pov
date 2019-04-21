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
// File       : space3d_test.pov
// Description: Space3D scenes test suite
// Version    : 0.48
// Date       : 2012-12-21
// Author     : Pyramid
// Scale      : 1 POV Unit = 1km
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Global Settings
// ---------------------------------------------------------------------------
#version 3.6;

// ---------------------------------------------------------------------------
// Prerequisites
// ---------------------------------------------------------------------------

#declare SHOW_LABELS = true;
#declare SCENE_NUMBER = frame_number;
// Quality Settings for test & sample or final rendering
#declare render_quality = 1; // 1=full; 0=fast (mostly unused)
#declare show_debug = false;
#declare create_logfile = false;

// ---------------------------------------------------------------------------
// Include Files
// ---------------------------------------------------------------------------
#include "space3d.inc"

// ---------------------------------------------------------------------------
// Test Cases
// ---------------------------------------------------------------------------

// gas giant showcase
#if (SCENE_NUMBER = 96)

  // syntax: Sun(vPosition, fIntensity)
  Sun(<2000, 0, -100000>, 1)

  // syntax: Camera(vPosition, vLookDirection, fCameraAngle)
  Camera(<0,0,-3000>, <0,200,0>, 45)
  //Camera1(1000)

  //gas giant 2
  #declare show = 1; #if (show) 
    #declare cSurfaceColor = rgb <0.22,0.33,0.66>;
    #declare bMonoColor = 0;
    #declare fColorDev = 20;
    //object { QuickPlanet(1000) translate <4000,-1000,10000> }
    object { GasGiant2(1000, cSurfaceColor, fColorDev, bMonoColor, seed(2345)) translate <4000,-1000,10000> }
  #end

  //gas giant 1
  #declare show = 1; #if (show) 
    #declare cSurfaceColor = rgb <0.22,0.33,0.22>;
    #declare bMonoColor = 0;
    #declare fColorDev = 20;
    //object { QuickPlanet(1000) translate <1000,1000,1000> }
    object { GasGiant1(1000, cSurfaceColor, fColorDev, bMonoColor, seed(2345)) translate <1000,1000,1000> }
  #end

  //gas giant 3
  #declare show = 1; #if (show) 
    #declare cSurfaceColor = rgb <0.11,0.33,0.33>;
    #declare bMonoColor = 0;
    #declare fColorDev = 20;
    //object { QuickPlanet(1000) translate <-1000,-400,100> }
    object { GasGiant3(1000, cSurfaceColor, fColorDev, bMonoColor, seed(2345)) translate <-1000,-400,100> }
  #end

#end //SCENE

// faction color sprites for VegaMapAnd
#if (SCENE_NUMBER = 95)

  #declare fSunRadius = 1e6; //4e6;
  #declare cam_pos = <0, 0, -2.2*fSunRadius>;
  #declare cam_dir = <0.00*fSunRadius, 0.00*fSunRadius, 1>;
  #declare cam_ang = 45;
  camera { location cam_pos right <image_width,0,0> up <0,image_height,0> look_at cam_dir angle cam_ang }    

   #declare sFactionNames = array[47] {
      "Aera",                 "Aeran Merchant Marine",   "Bzbr",              "Rlaan",       "Enforcers",
      "Rlaan Briin",          "Rlaan Hunters",           "Rlaan Merchants",   "Lmpl",        "Nuhln",
      "Saahasayaay",          "Humanity&Confed",         "Andolian",          "Spaceborn",   "Klk'k",
      "Purth",                "Highborn",                "Homeland Security", "IntelSec",    "Confed Navy",
      "Exploratory Service",  "Hunter",                  "GalMisBBS",         "LIHW",        "Mechanist",
      "Merchant Guild",       "Purist",                  "Shaper",            "Dgn",         "Unadorned", 
      "Mishtali",             "CCCAW",                   "CPPTC",             "Forsaken",    "Shmrn", 
      "Uln",                  "Luddites",                "Pirates",           "ISO",         "Unknown", 
      "Lightbearer",          "SuCets",                  "SuSims",            "Ancients A",  "Ancients B",
      "TWHON",                "Hoffman's Blobs"};                  
   #declare cFactionColors = array[52] {
      <0.072, 0.294, 0.065>,  <0.392, 0.527, 0.075>,  <0.320, 0.965, 0.396>,  <0.400, 0.000, 0.600>,  <0.200, 0.000, 1.000>,
      <0.588, 0.137, 0.453>,  <0.600, 0.200, 1.000>,  <0.800, 0.000, 1.000>,  <1.000, 0.078, 0.576>,  <0.545, 0.039, 0.314>, //10
      <0.850, 0.150, 0.350>,  <0.000, 0.000, 1.000>,  <0.000, 0.119, 0.723>,  <0.172, 0.352, 0.937>,  <0.200, 0.300, 0.800>,
      <0.100, 0.200, 0.700>,  <0.000, 0.200, 1.000>,  <0.000, 0.200, 0.400>,  <0.000, 0.400, 1.000>,  <0.000, 0.600, 1.000>, //20
      <0.154, 0.931, 0.987>,  <0.000, 0.209, 0.242>,  <0.000, 0.449, 0.442>,  <0.150, 0.250, 0.450>,  <0.100, 0.100, 0.200>,    
      <0.200, 0.200, 0.550>,  <1.000, 0.200, 0.000>,  <0.200, 0.000, 0.000>,  <0.400, 0.000, 0.000>,  <0.164, 0.034, 0.071>, //30   
      <0.374, 0.137, 0.155>,  <0.544, 0.028, 0.103>,  <0.754, 0.231, 0.287>,  <0.361, 0.200, 0.090>,  <0.840, 0.250, 0.090>,    
      <0.502, 0.502, 0.000>,  <1.000, 0.498, 0.000>,  <1.000, 0.000, 0.000>,  <1.000, 0.100, 0.100>,  <0.300, 0.300, 0.300>, //40   
      <0.520, 0.550, 0.500>,  <0.314, 0.446, 0.264>,  <0.488, 0.796, 0.350>,  <1.000, 0.800, 0.000>,  <1.000, 0.800, 0.200>,
      <1.000, 1.000, 0.000>,  <0.736, 0.467, 0.681>,  <128/255, 0, 255/255>,  <1.000, 1.000, 1.000>,  <0.000, 1.000, 1.000>, 
      <0.100, 0.100, 0.100>,  <0.200, 0.200, 0.200>};

  //#declare iColNumber = frame_number-1;
  #declare iColNumber = 0;
  //Star (Radius); max radius=5e6
  #declare cColor = cFactionColors[iColNumber]*2;
  object { StarColor(fSunRadius, cColor) }

#end //SCENE

// sun sprite for VegaMapAnd
#if (SCENE_NUMBER = 94)

  #declare fSunRadius = 1e6; //4e6;
  #declare cam_pos = <0, 0, -2.2*fSunRadius>;
  #declare cam_dir = <0.00*fSunRadius, 0.00*fSunRadius, 1>;
  #declare cam_ang = 45;
  camera { location cam_pos right <image_width,0,0> up <0,image_height,0> look_at cam_dir angle cam_ang }    

  //Star (Radius); max radius=5e6
  object { StarColor(fSunRadius, rgb <0.5,0.5,0.5>) }

#end //SCENE

// sun sprite for VegaMapAnd
#if (SCENE_NUMBER = 93)

  #declare fSunRadius = 1e6; //4e6;
  #declare cam_pos = <0, 0, -2.2*fSunRadius>;
  #declare cam_dir = <0.00*fSunRadius, 0.00*fSunRadius, 1>;
  #declare cam_ang = 45;
  camera { location cam_pos right <image_width,0,0> up <0,image_height,0> look_at cam_dir angle cam_ang }    

  //Star (Radius); max radius=5e6
  object { Star(fSunRadius) }

#end //SCENE

//  sun closeup
#if (SCENE_NUMBER = 92)

  #declare fSunRadius = 1e6; //4e6;
  #declare cam_pos = <0, 0, -1.1*fSunRadius>;
  #declare cam_dir = <0.35*fSunRadius, 0.35*fSunRadius, 1>;
  #declare cam_ang = 45;
  camera { location cam_pos right <image_width,0,0> up <0,image_height,0> look_at cam_dir angle cam_ang }    

  //Star (Radius); max radius=5e6
  object { Star(fSunRadius) }

  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) }

#end //SCENE

//  ring nebula 5
#if (SCENE_NUMBER = 91)
  #declare STARFIELD_NR = frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (93265 + STARFIELD_NR);

  #declare iColors = IRand(10,40,rColor);
  #declare NEBULA_COLORS = array[iColors];
  #declare I=0; #while (I<iColors)
    #declare NEBULA_COLORS[I] = color rgb <RRand(0.0,1.0,rColor), RRand(0.0,1.0,rColor), RRand(0.0,1.0,rColor)>;
  #declare I=I+1; #end
  #declare NEBULA_COLORS[0] = color rgb <1.0, 0.0, 0.0>; //red
  #declare NEBULA_COLORS[1] = color rgb <1.0, 0.5, 0.0>; //orange
  #declare NEBULA_COLORS[2] = color rgb <1.0, 1.0, 0.0>; //yellow
  #declare NEBULA_COLORS[3] = color rgb <1.0, 1.0, 0.5>; //yellow light
  #declare NEBULA_COLORS[4] = color rgb <1.0, 1.0, 0.5>; //white

  //#include "starfield.inc"
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(1,8,1,NEBULA_COLORS,0,rShape,rColor) rotate V_Rotation translate <0, 0, 4e4> }

  //#include "starfield.inc"
  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) }

#end //SCENE

// experimental background star field "ready to go"
#if (SCENE_NUMBER = 90)

  #declare STARFIELD_NR = 6; //frame_number; //mod(frame_number-1,6)+1; //range [1-6]
  #declare rShape = seed (49825 + STARFIELD_NR);
  #declare cStar = rgb <0.9, 0.9, 0.9>;
  #declare cAura = rgb <0.6, 0.75, 1.0>;
  #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cAura;
  
  //StarConcentration(iType, fSizeMin, fSizeMax, iAmount, cColors, fIntensity, fThicknessPercent, rSeed)
  object { StarConcentration(1, 5,10,2000,STAR_COLORS,1.0,0.2,rShape) rotate <0,0,30> }

  //label
  Camera1(1)
  #if (SHOW_LABELS)
    TitleText("O_StarConcentration01 (experimental)", 6, <0.9,0.9,0.0>)
  #end

#end

// pigment star field
#if (SCENE_NUMBER = 89)

  #declare STARFIELD_NR = 6; //frame_number; //mod(frame_number-1,6)+1; //range [1-6]
  #declare rShape = seed (49825 + STARFIELD_NR);
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  Camera1(1)
  #if (SHOW_LABELS)
    TitleText("P_StarField", 6, <0.9,0.9,0.0>)
  #end

#end

// Random explosion could nebula mCloudNebula08 from outside
#if (SCENE_NUMBER = 88)

  #declare STARFIELD_NR = 6; //frame_number; //mod(frame_number-1,6)+1; //range [1-6]
  #declare rShape = seed (1825 + STARFIELD_NR);
  #declare rColor = seed (88225 + STARFIELD_NR);
  #declare rPosition = seed (8741 + STARFIELD_NR);
  
  #declare iColors = IRand(4,20,rColor);
  #declare NEBULA_COLORS = array[iColors];
  #declare I=0; #while (I<iColors)
    #declare NEBULA_COLORS[I] = color rgb <RRand(0.3,0.5,rColor), RRand(0.3,0.5,rColor), RRand(0.9,1.0,rColor)>;
  #declare I=I+1; #end
  
  #declare show = 1; #if (show) 
    #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
    //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
    object { NebulaSelect(1,8,1,NEBULA_COLORS,0,rShape,rColor) rotate V_Rotation translate <0, 0, 4e4> }
  #end
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  Camera1(1)
  #if (SHOW_LABELS)
    TitleText("Nebula translated to far distance", 6, <0.9,0.9,0.0>)
  #end

#end

// triangle star test
#if (SCENE_NUMBER = 87)

  #declare rStar = seed (561913);
  #declare cStar = rgb <1.0, 1.0, 1.0>;
  #declare cAura = rgb <0.7, 0.7, 1.0>;
  #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cAura;

  #declare show = 1; #if (show)
    //mStarTriangle(fSizeMin, fSizeMax, aStarColors, fIntensity, rSeed) 
    object { mStarTriangle(1,1, STAR_COLORS, 1.0, rStar) scale 1 translate 50*z }
  #end
  
  //label
  Camera1(1)
  #if (SHOW_LABELS)
    TitleText("Single Star closeup", 6, <0.9,0.9,0.0>)
  #end

#end

//milkyway background - skysphere with mapped texture
#if (SCENE_NUMBER = 86)
  // starmap from: http://maps.jpl.nasa.gov/stars.html
  // From the Tycho star catalog, >1 million stars.
  // Courtesy NASA/JPL-Caltech.
  //camera { location <0,0,0> right <image_width,0,0> up <0,image_height,0> look_at <0,0,1> angle 90 rotate <0,0,0>}
  //sky_sphere { pigment { image_map { tiff "maps/tycho8s.tif" map_type 1 interpolate 2 } } }
  sky_sphere { pigment { image_map { jpeg "maps/milky_way.jpg" map_type 1 interpolate 2 } } }

  //label
  Camera1(1)
  #if (SHOW_LABELS)
    TitleText("Tycho Star Map", 6, <0.9,0.9,0.0>)
  #end

#end

//  spiral galaxy
#if (SCENE_NUMBER = 85)

  #declare rShape = seed (5619);
  #declare iArms = IRand(0,5,rShape)*2;
  #declare vTurb = VRand(rShape)*100;
  #declare fSpiral = rand(rShape)*2;
  #declare fGlow = rand(rShape);
  #declare fTurb = rand(rShape)*0.7;
  #declare fColDev = rand(rShape);
  //SpiralGalaxy(arms, Rand, spiralness, glowiness, turb, colShift)
  object { SpiralGalaxy(iArms, vTurb, fSpiral, fGlow, fTurb, fColDev) rotate <40,-30,0> translate <0,0,2> }
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  Camera1(1)
  #if (SHOW_LABELS)
    TitleText("SpiralGalaxy", 6, <0.9,0.9,0.0>)
  #end

#end //SCENE

//  random background scene
#if (SCENE_NUMBER = 84) //ex.30

  Camera1(1)
  #declare STARFIELD_NR = 22; //frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (34825 + STARFIELD_NR);
  #declare rShape = seed (93265 + STARFIELD_NR);
  #declare rStarfield = seed (1000 + STARFIELD_NR);
  
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.8,1.0,rColor), RRand(0.0,0.3,rColor), RRand(0.0,0.1,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.7,1.0,rColor), RRand(0.1,0.2,rColor), RRand(0.0,0.1,rColor)>;
  
  #declare iBackgrounds = 1; //IRand(1,2,rStarfield);
  #declare I=1; #while (I<=iBackgrounds)
    #declare V_Rotation = <0,0,0>; //<RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
    #declare iType = IRand(1,3,rStarfield);
    #declare iBackground = IRand(1,8,rStarfield);
    //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
    object { NebulaSelect(iType,iBackground,1,NEBULA_COLORS,0.05/iBackgrounds,rShape,rColor) rotate V_Rotation translate <-0.01, 0, 0> }
  #declare I=I+1; #end
  
  #declare show = 1; #if (show) 
    sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }
  #end
  
  //label
  #if (SHOW_LABELS)
    TitleText("random NebulaSelect", 6, <0.9,0.9,0.0>)
  #end

#end //SCENE

//  background nebula 2
#if (SCENE_NUMBER = 83)

  #declare STARFIELD_NR = frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (34825 + STARFIELD_NR);
  #declare rShape = seed (93265 + STARFIELD_NR);
  
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.0,0.1,rColor), RRand(0.0,0.2,rColor), RRand(0.2,0.5,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.2,0.3,rColor), RRand(0.2,0.3,rColor), RRand(0.1,0.3,rColor)>;
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(3,2,1,NEBULA_COLORS,0.04,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  Camera1(1)
  #if (SHOW_LABELS)
    TitleText("NebulaSelect type=3 nr=2 (mBackgroundNebula02)", 6, <0.9,0.9,0.0>)
  #end

#end //SCENE

//  background nebula 1
#if (SCENE_NUMBER = 82) //ex.28

  #declare STARFIELD_NR = 1; //frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (34825 + STARFIELD_NR);
  #declare rShape = seed (93265 + STARFIELD_NR);
  
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.5,0.8,rColor), RRand(0.0,0.8,rColor), RRand(0.0,0.1,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.0,0.1,rColor), RRand(0.0,0.3,rColor), RRand(0.5,0.7,rColor)>;
  #declare V_Rotation = <-40,0,30>;
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(3,1,1,NEBULA_COLORS,0.0,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  Camera1(1)
  #if (SHOW_LABELS)
    TitleText("NebulaSelect type=3 nr=1 (mBackgroundNebula01)", 6, <0.9,0.9,0.0>)
  #end

#end //SCENE

//  ring nebula 1
#if (SCENE_NUMBER = 81) //ex.27

  #declare STARFIELD_NR = 1; //frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (34825 + STARFIELD_NR);
  #declare rShape = seed (93265 + STARFIELD_NR);
  
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.5,0.8,rColor), RRand(0.0,0.3,rColor), RRand(0.0,0.1,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.0,0.1,rColor), RRand(0.0,0.3,rColor), RRand(0.5,0.7,rColor)>;
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(2,1,1,NEBULA_COLORS,0,rShape,rColor) rotate V_Rotation translate <0, 0, 5> }
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }
  
  //label
  Camera1(1)
  #if (SHOW_LABELS)
    TitleText("NebulaSelect type=2 nr=1 (mRingNebula01)", 6, <0.9,0.9,0.0>)
  #end

#end //SCENE

//  cloud nebula 8
#if (SCENE_NUMBER = 80)

  Camera1(1)
  #declare STARFIELD_NR = frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (34825 + STARFIELD_NR);
  #declare rShape = seed (93265 + STARFIELD_NR);
  
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.0,0.1,rColor), RRand(0.8,1.0,rColor), RRand(0.0,0.1,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.0,0.1,rColor), RRand(0.1,0.3,rColor), RRand(0.5,0.9,rColor)>;
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(1,8,1,NEBULA_COLORS,1,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  #if (SHOW_LABELS)
    TitleText("NebulaSelect type=1 nr=8 (mCloudNebula08)", 6, <0.9,0.9,0.0>)
  #end

#end //SCENE

//  cloud nebula 7
#if (SCENE_NUMBER = 79) //ex.26

  Camera1(1)
  #declare STARFIELD_NR = 4; //frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (34825 + STARFIELD_NR);
  #declare rShape = seed (93265 + STARFIELD_NR);
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = ColorHSL(200,70,80);
  #declare NEBULA_COLORS[1] = ColorHSL(200,70,80);
  
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(1,7,1500,NEBULA_COLORS,0.1,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  #if (SHOW_LABELS)
    TitleText("NebulaSelect type=1 nr=7 (mCloudNebula07)", 6, <0.9,0.9,0.0>)
  #end

#end //SCENE

//  cloud nebula 6
#if (SCENE_NUMBER = 78) //ex.25

  #declare STARFIELD_NR = frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (34825 + STARFIELD_NR);
  #declare rShape = seed (93265 + STARFIELD_NR);
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.9,1.0,rColor), RRand(0.0,0.3,rColor), RRand(0.0,0.1,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.9,1.0,rColor), RRand(0.0,0.3,rColor), RRand(0.0,0.1,rColor)>;
  
  //#declare USE_OBJECT_NUMBER = 46;
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(1,6,1,NEBULA_COLORS,0.1,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  Camera1(1)
  #if (SHOW_LABELS)
    TitleText("NebulaSelect type=1 nr=6 (mCloudNebula06)", 6, <0.9,0.9,0.0>)
  #end

#end //SCENE

//  ring nebula 5
#if (SCENE_NUMBER = 77) //ex.24

  #declare STARFIELD_NR = 30; //frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (93265 + STARFIELD_NR);
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.9,1.0,rColor), RRand(0.0,0.3,rColor), RRand(0.0,0.1,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.9,1.0,rColor), RRand(0.0,0.3,rColor), RRand(0.0,0.1,rColor)>;
  
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(1,5,1,NEBULA_COLORS,0.1,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  Camera1(1)
  #if (SHOW_LABELS)
    TitleText("NebulaSelect type=1 nr=5 (mCloudNebula05)", 6, <0.9,0.9,0.0>)
  #end

#end //SCENE

//  dense cloud nebula 4
#if (SCENE_NUMBER = 76) //ex.22

  #declare STARFIELD_NR = frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (5619 + STARFIELD_NR);
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.5,1.0,rColor), RRand(0.0,0.5,rColor), RRand(0.0,0.5,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.5,1.0,rColor), RRand(0.0,0.5,rColor), RRand(0.0,0.1,rColor)>;
  
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(1,4,1,NEBULA_COLORS,0.1,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  Camera1(1)
  #if (SHOW_LABELS)
    TitleText("NebulaSelect type=1 nr=4 (mCloudNebula04)", 6, <0.9,0.9,0.0>)
  #end

#end //SCENE

//  dense cloud nebula 3
#if (SCENE_NUMBER = 75)

  Camera1(1)
  #declare STARFIELD_NR = frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (5218 + STARFIELD_NR);
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.5,1.0,rColor), RRand(0.0,0.5,rColor), RRand(0.0,0.5,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.5,1.0,rColor), RRand(0.5,1.0,rColor), RRand(0.0,0.1,rColor)>;
  
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(1,3,1,NEBULA_COLORS,0.1,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  #if (SHOW_LABELS)
    TitleText("NebulaSelect type=1 nr=3 (mCloudNebula03)", 6, <0.9,0.9,0.0>)
  #end

#end //SCENE

//  dense cloud nebula 2
#if (SCENE_NUMBER = 74)

  Camera1(1)
  #declare STARFIELD_NR = frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (2325 + STARFIELD_NR);
  #declare rShape = seed (5218 + STARFIELD_NR);

  //fixed colors  
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.5,1.0,rColor), RRand(0.0,0.5,rColor), RRand(0.0,0.5,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.5,1.0,rColor), RRand(0.5,1.0,rColor), RRand(0.0,0.1,rColor)>;

  //random colors  
  #declare iColors = IRand(4,10,rColor);
  #declare cBaseColor = color rgb <RRand(0.3,0.5,rColor), RRand(0.0,0.5,rColor), RRand(0.0,0.5,rColor)>;
  #declare NEBULA_COLORS = array[iColors];
  #declare I=0; #while (I<iColors)
    #declare NEBULA_COLORS[I] = color rgb <RRand(0.0,0.4,rColor), RRand(0.0,0.4,rColor), RRand(0.0,0.4,rColor)>;
  #declare I=I+1; #end
  
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(1,2,1,NEBULA_COLORS,0.1,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  #if (SHOW_LABELS)
    TitleText("NebulaSelect type=1 nr=2 (mCloudNebula02)", 6, <0.9,0.9,0.0>)
  #end

#end //SCENE

//  dense cloud nebula 1
#if (SCENE_NUMBER = 73)

  Camera1(1)
  #declare STARFIELD_NR = frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (5218 + STARFIELD_NR);

  //random colors  
  #declare iColors = IRand(10,20,rColor);
  #declare NEBULA_COLORS = array[iColors];
  #declare I=0; #while (I<iColors)
    #declare NEBULA_COLORS[I] = color rgb <RRand(0.0,0.4,rColor), RRand(0.0,0.4,rColor), RRand(0.0,0.4,rColor)>;
  #declare I=I+1; #end
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(1,1,1,NEBULA_COLORS,0.1,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  #if (SHOW_LABELS)
    TitleText("NebulaSelect type=1 nr=1 (mCloudNebula01)", 6, <0.9,0.9,0.0>)
  #end
  
#end //SCENE

// galaxy cluster with random colors
#if (SCENE_NUMBER = 72)

  Camera1(1)
  #declare SeedS = seed(3456+frame_number);

  //common parameters
  #declare fDistrAngle = 2; //star cluster size

  //globular galaxy core
  #declare vExcentricity = <1, 1, 1>;
  #declare vOrientation = <0, 0, 0>; //star cluster orientation
  #declare STARFIELD = 1; #while (STARFIELD <= 5)
    #declare cStar = rgb <RRand(0.3,0.7,SeedS), RRand(0.3,0.7,SeedS), 1>; //RandomColor(IRand(1,8,SeedS),SeedS, 30)
    #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cStar;
    #declare fIntensity = 3*RRand(2.8,3.5,SeedS);
    #declare iAmount = 500*fDistrAngle; //pow(STARFIELD,1.5);
    #declare fSizeMin = RRand(2,5,SeedS);
    #declare fSizeMax = fSizeMin*2;
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, SeedS) }
  #declare STARFIELD=STARFIELD+1; #end

  //tubular galaxy rims
  #declare vExcentricity = <5, 0.1, 5>; //<5, 0.01, 5>;
  #declare vOrientation = <-10, 0, 20>; //star cluster orientation
  #declare STARFIELD = 1; #while (STARFIELD <= 10) //50
    #declare cStar = RandomColor(IRand(1,14,SeedS),SeedS, 50)
    #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cStar;
    #declare fIntensity = 2*RRand(2.8,3.5,SeedS);
    #declare iAmount = 100*fDistrAngle; //pow(STARFIELD,2);
    #declare fSizeMin = RRand(2,5,SeedS); //10*STARFIELD/2.5;
    #declare fSizeMax = fSizeMin*2;
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, SeedS) }
  #declare STARFIELD=STARFIELD+1; #end

  //label
  #if (SHOW_LABELS)
    TitleText("StarCluster x10 galaxy", 10, <0.9,0.9,0.0>)
  #end

#end

// galaxy cluster
#if (SCENE_NUMBER = 71)

  Camera1(1)
  #declare SeedS = seed(345+frame_number);

  //common parameters
  #declare cStar = rgb <0.7,0.7,1.0>;
  #declare cAura = rgb <0.7,0.7,1.0>;
  #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cAura;
  #declare fDistrAngle = 2; //star cluster size

  //globular galaxy core
  #declare vExcentricity = <1, 1, 1>;
  #declare vOrientation = <0, 0, 0>; //star cluster orientation
  #declare STARFIELD = 1; #while (STARFIELD <= 5)
    #declare fIntensity = RRand(1.3,2.0,SeedS);
    #declare iAmount = 400*fDistrAngle/pow(STARFIELD,2);
    #declare fSizeMin = 5*STARFIELD/2.5;
    #declare fSizeMax = fSizeMin*2;
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, SeedS) }
  #declare STARFIELD=STARFIELD+1; #end

  //tubular galaxy rims
  #declare vExcentricity = <5, 0.1, 0.1>;
  #declare vOrientation = <0, 0, -60>; //star cluster orientation
  #declare STARFIELD = 1; #while (STARFIELD <= 5)
    #declare fIntensity = RRand(1.3,2.0,SeedS);
    #declare iAmount = 400*fDistrAngle/pow(STARFIELD,2);
    #declare fSizeMin = 10*STARFIELD/3.5;
    #declare fSizeMax = fSizeMin*2;
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, SeedS) }
  #declare STARFIELD=STARFIELD+1; #end

  //label
  #if (SHOW_LABELS)
    TitleText("StarCluster x10 galaxy", 10, <0.9,0.9,0.0>)
  #end

#end

// cloud nebula
#if (SCENE_NUMBER = 70)

  Camera1(1)
   
  #declare SeedS = seed(345+frame_number);

  #declare oStarField = sky_sphere {
    P_StarField(rgb<1,1,1>, 1.0)
    #declare I=0; #while (I<5)
      #declare cStar = rgb <0.0, 0.0, RRand(0.0,1.0,SeedS)>*RRand(0.5,1.5,SeedS);
      #declare cAura = rgb <0.0, RRand(0.0,1.0,SeedS), RRand(0.0,1.0,SeedS)>*RRand(1.0,2.0,SeedS);
      #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cAura;
      #declare fStarIntensity = RRand(1.0,2.0,SeedS);
      #declare fTurbulence = RRand(1.8,2.2,SeedS);
      #declare vPosition = <180,0,0>*RRand(0.95,1.05,SeedS);
      pigment { P_CloudNebula(2, STAR_COLORS,fStarIntensity,fTurbulence,<0,0,0>,SeedS) rotate vPosition }
    #declare I=I+1; #end
  }

  sky_sphere { oStarField }
   
  //label
  #if (SHOW_LABELS)
    TitleText("P_CloudNebula x5 turbulence=1.9", 10, <0.9,0.9,0.0>)
  #end

#end

// cloud nebula
#if (SCENE_NUMBER = 69)

  Camera1(1)
   
  #declare SeedS = seed(345+frame_number);

  #declare oStarField = sky_sphere {
    P_StarField(rgb<1,1,1>, 1.0)
    #declare I=0; #while (I<1)
      #declare cStar = rgb <1.0, RRand(0.0,0.9,SeedS), 0>*0.5; //*RRand(0.2,1.0,SeedS); //<0.9, 0.9, 0.9>;
      #declare cAura = rgb <1.0, RRand(0.0,0.9,SeedS), 0.0>*0.5; //*RRand(1.0,3.0,SeedS);
      #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cAura;
      #declare fStarIntensity = 1.0;
      #declare fTurbulence = 1.9; //RRand(1.8,2.2,SeedS);
      #declare vPosition = <180,0,0>*RRand(0.95,1.05,SeedS);
      pigment { P_CloudNebula(4, STAR_COLORS,fStarIntensity,fTurbulence,<0,0,0>,SeedS) rotate vPosition }
    #declare I=I+1; #end
  }
  sky_sphere { oStarField }
   
  //label
  #if (SHOW_LABELS)
    TitleText("P_CloudNebula type=4 turbulence=1.9", 10, <0.9,0.9,0.0>)
  #end

#end

// star nebula
#if (SCENE_NUMBER = 68)

  Camera1(1)
   
  #declare SeedS = seed(345+frame_number);

  #declare oStarField = sky_sphere {
    P_StarField(rgb<1,1,1>, 1.0)
    #declare I=0; #while (I<5)
      #declare cStar = rgb <1.0, RRand(0.0,0.9,SeedS), 0>*RRand(0.2,1.0,SeedS); //<0.9, 0.9, 0.9>;
      #declare cAura = rgb <1.0, RRand(0.0,0.9,SeedS), 0.0>*RRand(1.0,3.0,SeedS);
      #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cAura;
      #declare fStarIntensity = 2.0;
      #declare fTurbulence = 2.0; //RRand(1.8,2.2,SeedS);
      #declare vPosition = <180,0,0>*RRand(0.95,1.05,SeedS);
      pigment { P_StarNebula(STAR_COLORS,fStarIntensity,fTurbulence,<0,0,0>,SeedS) rotate vPosition }
    #declare I=I+1; #end
  }
  sky_sphere { oStarField }
   
  //label
  #if (SHOW_LABELS)
    TitleText("P_StarNebula x5 turbulence=2.5", 10, <0.9,0.9,0.0>)
  #end

#end

// star nebula
#if (SCENE_NUMBER = 67)

  Camera1(1)
   
  #declare cStar = rgb <1.0, 0.9, 0>*0.5;
  #declare cAura = rgb <1.0, 0.0, 0.0>*1.5;
  #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cAura;
  #declare fStarIntensity = 2.0;
  #declare SeedS = seed(345+frame_number);

  #declare vPosition = <180,0,0>;
  #declare oStarField = sky_sphere {
    P_StarField(rgb<1,1,1>, 1.0) rotate vPosition
    pigment { P_StarNebula(STAR_COLORS,fStarIntensity,1.0,<0,0,0>,SeedS) rotate vPosition }
  }
  sky_sphere { oStarField }
   
  //label
  #if (SHOW_LABELS)
    TitleText("P_StarNebula turbulence=1.0", 10, <0.9,0.9,0.0>)
  #end

#end

// random star clusters
#if (SCENE_NUMBER = 66)
   
  Camera1(1)
  #declare STARFIELD_NR = 4; //frame_number;
  #declare SeedS = seed(123+STARFIELD_NR);
  #declare STARFIELDS_NO = 6; //IRand(2,4,SeedS);

  //common parameters
  #declare cStar = rgb <0.9, 0.9, 0.9>;
  #declare cAura = rgb <0.6, 0.75, 1.0>;
  #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cAura;
  #declare fViewAngle = 30; //star cluster size
  #declare vExcentricity = <1, 1, 1>;
  #declare vOrientation = <0, 0, 0>;

  #declare I=1; #while (I<STARFIELDS_NO)
    //common parameters
    #declare STAR_COLORS[0] = rgb <0.9, 0.9, 0.9>;
    #declare STAR_COLORS[1] = rgb <RRand(0.7,0.8,SeedS), RRand(0.8,0.9,SeedS), RRand(0.9,1.0,SeedS)>;
    #declare fViewAngle = RRand(3,50,SeedS); //star cluster size
    #declare vExcentricity = <RRand(2.0,10.0,SeedS), 1, 1>;
    #declare vOrientation = <0, 0, RRand(-90,90,SeedS)>;
  
    // big stars
    //#declare iAmount = 2000;
    #if (I=1) #declare iAmount = 1000; #else #declare iAmount = IRand(2000,5000,SeedS); #end
    #declare fSizeMin = RRand(2,5,SeedS);
    #declare fSizeMax = RRand(6,12,SeedS);
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 2.0, fViewAngle, vOrientation, vExcentricity, SeedS) }
  #declare I=I+1; #end

  //label
  #if (SHOW_LABELS)
    TitleText("Random StarClusters", 10, <0.9,0.9,0.0>)
  #end

#end

// star cluster triple mix
#if (SCENE_NUMBER = 65)

  Camera1(1)
  #declare STARFIELD_NR = frame_number;
  #declare SeedS = seed(12345+STARFIELD_NR);

  //common parameters
  #declare cStar = rgb <0.9, 0.9, 0.9>;
  #declare cAura = rgb <0.6, 0.75, 1.0>;
  #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cAura;
  #declare fViewAngle = 30; //star cluster size
  #declare vExcentricity = <1, 1, 1>;
  #declare vOrientation = <0, 0, 0>;

  // big stars
  #declare iAmount = 2000;
  #declare fSizeMin = 5;
  #declare fSizeMax = 12;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 2.0, fViewAngle, vOrientation, vExcentricity, SeedS) }

  // small stars
  #declare iAmount = 10000; //10000;
  #declare fSizeMin = 2;
  #declare fSizeMax = 5;
  //O_StarCluster(fSizeMin, fSizeMax, iStarAmount, aStarColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 1.5, fViewAngle, vOrientation, vExcentricity, SeedS) }

  // tiny starsd
  #declare iAmount = 20000; //20000;
  #declare fSizeMin = 1;
  #declare fSizeMax = 3;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 1.0, fViewAngle, vOrientation, vExcentricity, SeedS) }

  //label
  #if (SHOW_LABELS)
    TitleText("StarCluster x3 mix", 10, <0.9,0.9,0.0>)
  #end

#end

// mix: excentric star cluster with small and large background stars
#if (SCENE_NUMBER = 64)

  Camera1(1)
  #declare STARFIELD_NR = frame_number;
  #declare SeedS = seed(1234567+STARFIELD_NR);

  // a red streak
  #declare cStar = rgb <0.9, 0.9, 0.9>*1.5;
  #declare cAura = rgb <1.0, 0.75, 0.6>;
  #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cAura;
  #declare iAmount = 2000;
  #declare fSizeMin = 2;
  #declare fSizeMax = 10;
  #declare fViewAngle = 5; //star cluster size
  #declare vExcentricity = <6, 0.5, 0.5>;
  #declare vOrientation = <0, 0, -45>; //star cluster position
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 3.0, fViewAngle, vOrientation, vExcentricity, SeedS) }
  
  //globular cluster
  #declare cStar = rgb <0.9, 0.9, 0.9>;
  #declare cAura = rgb <0.6, 0.75, 1.0>;
  #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cAura;
  #declare iAmount = 10000;
  #declare fSizeMin = 2;
  #declare fSizeMax = 10;
  #declare fViewAngle = 30; //star cluster size
  #declare vExcentricity = <1, 1, 1>;
  #declare vOrientation = <0, 0, 0>; //star cluster position
  //O_StarCluster(fSizeMin, fSizeMax, iStarAmount, aStarColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 3.0, fViewAngle, vOrientation, vExcentricity, SeedS) }

  //some larger stars
  #declare cStar = rgb <1, 1, 1>;
  #declare cAura = rgb <0.8, 0.85, 1.0>;
  #declare STAR_COLORS[0] = cStar; #declare STAR_COLORS[1] = cAura;
  #declare iAmount = 1000;
  #declare fSizeMin = 2;
  #declare fSizeMax = 12;
  #declare fViewAngle = 30; //star cluster size
  #declare vExcentricity = <1, 1, 1>;
  #declare vOrientation = <0, 0, 0>; //star cluster position
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 3.0, fViewAngle, vOrientation, vExcentricity, SeedS) }

  #if (SHOW_LABELS)
    TitleText("StarCluster x3", 10, <0.9,0.9,0.0>)
  #end

#end

// example of a quick implementation of a star cluster
#if (SCENE_NUMBER = 63)
  Camera1(1)
  //#declare CAMERA = 1;
  #declare STARFIELD_NR = frame_number;
  #declare SeedS = seed(1234567+STARFIELD_NR);
  
  #declare fSizeMin = 2; //*1500/sqrt(image_width*image_height);
  #declare fSizeMax = 10; //*1500/sqrt(image_width*image_height);
  #declare iAmount = 1000;

  #declare STAR_COLORS[0] = color rgb <1,1,0.9>; #declare STAR_COLORS[1] = color rgb <0.9,0.5,0.0>;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 3.0, 25, <0,0,0>, <1,1,1>, SeedS) }

  //label
  #if (SHOW_LABELS)
    TitleText("StarCluster", 10, <0.9,0.9,0.0>)
  #end

#end


// starry sky from planet
#if (SCENE_NUMBER = 62)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 61125; //frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (9876 + STARFIELD_NR);
  #declare NEBULA_COLORS = array[2];
  
  //globular star cluster
  #declare show = 1; #if (show) 
    #declare SF_NUMBERS = array[4] {50, 20, 10, 5}; 
    #declare I=1; #while (I<=4) // the different sizes
      #declare STARFIELD_NR = frame_number;
      #declare STARFIELDS_NO = SF_NUMBERS[I-1];
      #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
        #declare fSizeMin = RRand(1.0,1.5,rShape);
        #declare fSizeMax = fSizeMin;
        #declare iAmount = 50; //1e4/pow(fSizeMin,3);
        //#declare iColor = IRand(2,3,rColor);
        #declare STAR_COLORS[0] = ColorHSL(245,70,100) 
        #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
        #declare fIntensity = RRand(1.0,2.0,rColor); //maximum intensity
        #declare vExcentricity = <RRand(1.0,2.0,rShape), RRand(1.0,2.0,rShape), 1>;
        #declare vOrientation = <RRand(-5,5,rPosition),RRand(-5,5,rPosition), RRand(0,180,rPosition)>;
        #declare fDistrAngle = 20; //RRand(3,20,rPosition);
        //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
        object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,45> translate <-4e3,4e3,0> }
      #declare STARFIELD=STARFIELD+1; #end
    #declare I=I+1; #end
  #end

  Starfield()
  
#end

// test nebula
#if (SCENE_NUMBER = 61)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 65; //frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (9876 + STARFIELD_NR);
  #declare NEBULA_COLORS = array[2];
  
  //nebula
  #declare show = 1; #if (show) 
    #declare iBackgrounds = 1; //IRand(1,2,rShape);
    #declare I=1; #while (I<=iBackgrounds)
       #declare NEBULA_COLORS[0] = color rgb <0.693, 0.288, 0.045>;
       #declare NEBULA_COLORS[1] = color rgb <0.715, 0.383, 0.029>;
       #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
       object { NebulaSelect(1,7,1,NEBULA_COLORS,0.06,rShape,rColor) rotate V_Rotation translate<-0.01*I, 0, 0> }
    #declare I=I+1; #end
  #end
  
  //globular star cluster
  #declare show = 1; #if (show) 
    #declare SF_NUMBERS = array[3] {50, 20, 10}; 
    #declare I=2; #while (I<=4) // the different sizes
      #declare STARFIELD_NR = frame_number;
      #declare STARFIELDS_NO = SF_NUMBERS[I-2];
      #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
        #declare fSizeMin = RRand(3.0,5.0,rShape)*I;
        #declare fSizeMax = fSizeMin*2.0;
        #declare iAmount = 1e4/pow(fSizeMin,3);
        #declare iColor = IRand(2,3,rColor);
        #declare STAR_COLORS[0] = RandomColor(iColor,rColor, 30) 
        #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
        #declare fIntensity = RRand(2.0,5.0,rColor); //maximum intensity
        #declare vExcentricity = <RRand(1.0,2.0,rShape), RRand(1.0,2.0,rShape), 1>;
        #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
        #declare fDistrAngle = RRand(3,20,rPosition);
        //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
        object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,45> translate <-4e3,4e3,0> }
      #declare STARFIELD=STARFIELD+1; #end
    #declare I=I+1; #end
  #end
  
#end

//  scene with two suns
#if (SCENE_NUMBER = 60)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare rNebula = seed (182);
  #declare rStars = seed (1218);
  #declare rShape = seed (1104);
  #declare rColor = seed (1104);

  #declare show = 1; #if (show) 
    //#include "sun.inc"
    #declare fSunRadius = 1e4; //4e6;
    #declare fIntensity = 1+(frame_number-21);
    //Sun (Radius); max radius=5e6
    object { Star(fSunRadius*1.3) translate <-1.3*fSunRadius, -0.3*fSunRadius, 10*fSunRadius> }
    object { Star(fSunRadius) translate <1.1*fSunRadius, 0.3*fSunRadius, 10*fSunRadius> }
  #end

  #declare show = 1; #if (show) 
    sky_sphere {
      P_StarField(rgb <0.8, 0.9, 1.0>, 1.0)

      #declare iColors = 4; //IRand(4,10,rColor);
      #declare NEBULA_COLORS = array[iColors];
      #declare I=0; #while (I<2)
        #declare NEBULA_COLORS[I] = rgb <RRand(0.5,1.0,rNebula), RRand(0.5,1.0,rNebula), RRand(0.0,0.3,rNebula)>*RRand(2.0,3.0,rNebula);
      #declare I=I+1; #end
      #declare I=2; #while (I<iColors)
        #declare NEBULA_COLORS[I] = rgb <RRand(0.5,1.0,rNebula), RRand(0.0,0.3,rNebula), RRand(0.0,0.3,rNebula)>*RRand(2.0,3.0,rNebula);
      #declare I=I+1; #end
      //P_CloudNebula(iType, aColors, fIntensity, fStrength, vExcentricity, rSeed) 
      pigment { P_CloudNebula(1, NEBULA_COLORS, 1.0, 1.6, <1,1,1>, rNebula) }

      #declare iColors = 4;
      #declare I=2; #while (I<iColors)
        #declare NEBULA_COLORS[I] = rgb <1,0.5,0>*RRand(1.0,2.0,rNebula);
      #declare I=I+1; #end
      pigment { P_CloudNebula(1, NEBULA_COLORS, 1.0, 2.2, <1,1,1>, rNebula) }
    }
  #end

  //large blue stars
  #declare show = 1; #if (show) 
    #declare iStarfield=1; #while (iStarfield<=20)
      #declare fSizeMin = RRand(10.0,15.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,500/pow(fSizeMin,2));
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rStars), RRand(0.5,0.6,rStars), 1>; 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <RRand(1,5,rStars), RRand(1,5,rStars), 1>;
      #declare vOrientation = <0,0, RRand(0,180,rStars)>;
      #declare fDistrAngle = 25;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rStars) }
    #declare iStarfield=iStarfield+1; #end
  #end

  //few very large blue stars
  #declare show = 1; #if (show) 
    #declare iStarfield=1; #while (iStarfield<=20)
      #declare fSizeMin = RRand(20.0,55.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 10;
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rStars), RRand(0.5,0.6,rStars), 1>; 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <RRand(1,5,rStars), RRand(1,5,rStars), 1>;
      #declare vOrientation = <0,0, RRand(0,180,rStars)>;
      #declare fDistrAngle = 25;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rStars) }
    #declare iStarfield=iStarfield+1; #end
  #end

  //few very large yellow stars
  #declare show = 1; #if (show) 
    #declare iStarfield=1; #while (iStarfield<=10)
      #declare fSizeMin = RRand(20.0,55.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 10;
      #declare STAR_COLORS[0] = rgb <1, RRand(0.6,0.8,rStars), 0>; 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <RRand(1,5,rStars), RRand(1,5,rStars), 1>;
      #declare vOrientation = <0,0, RRand(0,180,rStars)>;
      #declare fDistrAngle = 25;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rStars) }
    #declare iStarfield=iStarfield+1; #end
  #end

  //many small yellow stars
  #declare show = 1; #if (show) 
    #declare iStarfield=1; #while (iStarfield<=100)
      #declare fSizeMin = RRand(6.0,20.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,5e4/pow(fSizeMin,3));
      #declare STAR_COLORS[0] = rgb <1, RRand(0.6,0.8,rStars), 0>; 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(1.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <RRand(1,5,rStars), RRand(1,5,rStars), 1>;
      #declare vOrientation = <0,0, RRand(0,180,rStars)>;
      #declare fDistrAngle = 25;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rStars) }
    #declare iStarfield=iStarfield+1; #end
  #end

#end //SCENE

// Could nebula view - Space3d download image
#if (SCENE_NUMBER = 59)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 18; //frame_number; //mod(frame_number-1,6)+1; //range [1-6]
  #declare rShape = seed (1825 + STARFIELD_NR);
  #declare rColor = seed (88225 + STARFIELD_NR);
  #declare rPosition = seed (8741 + STARFIELD_NR);
  
  #declare iColors = IRand(4,10,rColor);
  #declare NEBULA_COLORS = array[iColors];
  #declare I=0; #while (I<iColors)
    #declare NEBULA_COLORS[I] = color rgb <RRand(0.9,1.0,rColor), RRand(0.8,1.0,rColor), 0>*RRand(0.1,2.0,rColor);
  #declare I=I+1; #end
  
  #declare show = 1; #if (show) 
    //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
    object { NebulaSelect(1,8,2e4-1,NEBULA_COLORS,0.1,rShape,rColor) rotate <0,0,0> translate <0, 0, 0> }
  #end

  //a streak
  #declare fSizeMin = 1.0;
  #declare fSizeMax = 4.0;
  #declare iAmount = 1000; //5000;
  #declare STAR_COLORS[0] = rgb <0.9, 0.9, 0.9>; #declare STAR_COLORS[1] = rgb <1.0, 0.85, 0.8>;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 5.0, 5, <0,0,15>, <3,1,1>, rShape) rotate <10,-10,0>}

  //uniform - small
  #declare fSizeMin = 1.0;
  #declare fSizeMax = 5.0;
  #declare iAmount = 5000; //10000;
  #declare STAR_COLORS[0] = rgb <0.9, 0.9, 0.9>; #declare STAR_COLORS[1] = rgb <1.0, 0.85, 0.8>;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 3.0, 25, <0,0,0>, <1,1,1>, rShape) }

  //uniform - medium
  #declare fSizeMin = 3.0;
  #declare fSizeMax = 8.0;
  #declare iAmount = 1000;
  #declare STAR_COLORS[0] = rgb <0.9, 0.9, 0.9>; #declare STAR_COLORS[1] = rgb <1.0, 0.85, 0.8>;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 2.0, 25, <0,0,0>, <1,1,1>, rShape) }

  //uniform - large
  #declare fSizeMin = 6.0;
  #declare fSizeMax = 10.0;
  #declare iAmount = 500;
  #declare STAR_COLORS[0] = rgb <1.0, 1.0, 1.0>; #declare STAR_COLORS[1] = rgb <1.0, 0.85, 0.8>;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 4.0, 25, <0,0,0>, <1,1,1>, rShape) }
  
  sky_sphere { P_StarField(rgb<1,1,1>, 1.0) }

  //label
  //#declare rotX = -degrees(asin((cam_dir.y-cam_pos.y)/(cam_dir.z-cam_pos.z))); // asin(vec_y/-vec_z)
  //#declare rotY = degrees(asin((cam_dir.x-cam_pos.x)/(cam_dir.z-cam_pos.z)));    // asin(vec_x/-vec_z)
  #if (SHOW_LABELS)
    TitleText("Nebula", 10, <0.9,0.9,0.0>)
  #end

#end

// another spiral galaxy
#if (SCENE_NUMBER = 58)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 44; //mod(frame_number-1,6)+1; //range [1-6]
  #declare rShape = seed (93265 + STARFIELD_NR);
  #declare rColor = seed (96515 + STARFIELD_NR);
  #declare rPosition = seed (11223 + STARFIELD_NR);

  //galaxy closeup
  #declare show = 1; #if (show) 
    #declare iArms = IRand(0,5,rShape)*2;
    #declare vTurb = VRand(rShape)*100;
    #declare fSpiral = rand(rShape)*2;
    #declare fGlow = rand(rShape);
    #declare fTurb = rand(rShape)*0.7;
    #declare fColDev = rand(rShape);
    //#include "spiral_galaxy.inc"
    #declare V_Rotation = <0,0,0>; //own rotation
    #declare vPosRotation = <0,0,0>; //universe position
    //SpiralGalaxy(arms, Rand, spiralness, glowiness, turb, colShift)
    object { SpiralGalaxy(iArms, vTurb, fSpiral, fGlow, fTurb, fColDev) rotate V_Rotation translate <0,0,2> rotate vPosRotation  }
  #end

  //some distant galaxies
  #declare show = 1; #if (show) 
    #declare I=1; #while (I<=10)
      #declare iArms = IRand(0,5,rShape)*2;
      #declare vTurb = VRand(rShape)*100;
      #declare fSpiral = rand(rShape)*2;
      #declare fGlow = rand(rShape);
      #declare fTurb = rand(rShape)*0.7;
      #declare fColDev = rand(rShape);
      //#include "spiral_galaxy.inc"
      #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>; //own rotation
      #declare vPosRotation = <RRand(-15,15,rPosition), RRand(-25,25,rPosition), 0>; //universe position
      //SpiralGalaxy(arms, Rand, spiralness, glowiness, turb, colShift)
      object { SpiralGalaxy(iArms, vTurb, fSpiral, fGlow, fTurb, fColDev) rotate V_Rotation translate <0,0,10+pow(I,2)> rotate vPosRotation  }
    #declare I=I+1; #end
  #end

  //colored stars
  #declare show = 1; #if (show) 
    #declare iStarfield=1; #while (iStarfield<=50)
      #declare fSizeMin = RRand(4.0,15.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,2));
      #declare STAR_COLORS[0] = RandomColor(IRand(0,14,rColor), rColor, RRand(0,90,rColor)) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.0,rColor); //maximum intensity
      #declare vExcentricity = <RRand(0.1,2.0,rShape), RRand(0.1,2.0,rShape), 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) }
    #declare iStarfield=iStarfield+1; #end
  #end

  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) }

  //label
  #if (SHOW_LABELS)
    TitleText("Spiral galaxy", 8, <0.9,0.9,0.0>)
  #end

#end

//  vegastrike starfield1 background
#if (SCENE_NUMBER = 57)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = frame_number; //mod(frame_number-1,6)+1; //range [1-6]
  #declare rStars = seed (1481 + STARFIELD_NR);
  #declare rColor = seed (9567 + STARFIELD_NR);
  #declare rPosition = seed (94652 + STARFIELD_NR);
  #declare rShape = seed (411 + STARFIELD_NR);

  //plain background
  #declare show = 1; #if (show) 
    #declare iStarfield=1; #while (iStarfield<=10)
      #declare fSizeMin = RRand(2.0,6.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,3));
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rStars), RRand(0.5,0.6,rStars), 1>; 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25/pow(iStarfield,0.2);
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) }
    #declare iStarfield=iStarfield+1; #end
  #end

  //plain background
  #declare show = 1; #if (show) 
    #declare iStarfield=1; #while (iStarfield<=10)
      #declare fSizeMin = RRand(2.0,6.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,3));
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rStars), RRand(0.5,0.6,rStars), 1>; 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <RRand(1,5,rStars), RRand(1,5,rStars), 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25/pow(iStarfield,0.2);
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) }
    #declare iStarfield=iStarfield+1; #end
  #end

  //center stars
  #declare show = 1; #if (show) 
    #declare iStarfield=1; #while (iStarfield<=10)
      #declare fSizeMin = RRand(5.0,20.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,2));
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rStars), RRand(0.5,0.6,rStars), 1>; 
      #declare STAR_COLORS[1] = rgb <0.9,0.5,0.0>; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <RRand(1,5,rStars), RRand(1,5,rStars), 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 10;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) }
    #declare iStarfield=iStarfield+1; #end
  #end

  //distributed stars
  #declare show = 1; #if (show) 
    #declare iStarfield=1; #while (iStarfield<=10)
      #declare fSizeMin = RRand(4.0,12.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,2));
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rStars), RRand(0.5,0.6,rStars), 1>; 
      #declare STAR_COLORS[1] = rgb <0.9,0.5,0.0>; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <RRand(1,5,rStars), RRand(1,5,rStars), 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25/pow(iStarfield,0.2);
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) }
    #declare iStarfield=iStarfield+1; #end
  #end

  //blue stars
  #declare show = 1; #if (show) 
    #declare iStarfield=1; #while (iStarfield<=10)
      #declare fSizeMin = RRand(2.0,7.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,2));
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rStars), RRand(0.5,0.6,rStars), 1>; 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <RRand(1,5,rStars), RRand(1,5,rStars), 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 10;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) }
    #declare iStarfield=iStarfield+1; #end
  #end

  //tiny stars
  #declare show = 1; #if (show) 
    #declare iStarfield=1; #while (iStarfield<=10)
      #declare fSizeMin = RRand(3.0,6.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,2));
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rStars), RRand(0.5,0.6,rStars), 1>; 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <RRand(1,5,rStars), RRand(1,5,rStars), 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25/pow(iStarfield,0.2);
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) }
    #declare iStarfield=iStarfield+1; #end
  #end

  //big stars
  #declare show = 1; #if (show) 
    #declare iStarfield=1; #while (iStarfield<=10)
      #declare fSizeMin = RRand(6.0,10.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,2000/pow(fSizeMin,2));
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rStars), RRand(0.5,0.6,rStars), 1>; 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <RRand(1,5,rStars), RRand(1,5,rStars), 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25/pow(iStarfield,0.2);
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) }
    #declare iStarfield=iStarfield+1; #end
  #end

  //tiny white stars on margins
  #declare show = 1; #if (show) 
    #declare iStarfield=1; #while (iStarfield<=10)
      #declare fSizeMin = RRand(3.5,10.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,2000/pow(fSizeMin,2));
      #declare STAR_COLORS[0] = rgb <1, 1, 1>; 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <RRand(1,5,rStars), RRand(1,5,rStars), 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25/pow(iStarfield,0.2);
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) }
    #declare iStarfield=iStarfield+1; #end
  #end

  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) }

  //label
  #if (SHOW_LABELS)
    TitleText("Starfield", 8, <0.9,0.9,0.0>)
  #end

#end

// Several different distributed mCloudNebula08
#if (SCENE_NUMBER = 56)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 14; //2 + int((frame_number-1)/6);; //step 6

  #declare show = 1; #if (show) 
    #declare N=0; #while(N<2)      

      #declare rShape = seed (71235 + STARFIELD_NR*2 + N);
      #declare rColor = seed (12225 + STARFIELD_NR*2 + N);
      #declare rPosition = seed (82741 + STARFIELD_NR*2 + N);

      #declare iColors = IRand(10,20,rColor);
      #declare cBaseColor = color rgb <RRand(0.0,1.0,rColor), RRand(0.0,1.0,rColor), RRand(0.0,1.0,rColor)>;

      #declare NEBULA_COLORS = array[iColors];
      #declare I=0; #while (I<iColors)
        #declare NEBULA_COLORS[I] = VariateColor_mono(cBaseColor, 90, rColor);
      #declare I=I+1; #end

      #declare V_Rotation = <RRand(-180,180,rPosition), RRand(-180,180,rPosition), RRand(-180,180,rPosition)>;
      object { mCloudNebula08(1,NEBULA_COLORS,0,rShape,rColor) rotate V_Rotation translate<0, 0, 1> rotate <0,0,0>} 
      ///NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
      object { NebulaSelect(1,8,1,NEBULA_COLORS,0,rShape,rColor) rotate V_Rotation translate <0, 0, 1> }
    #declare N=N+1; #end      
  #end

  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) }

  //label
  #if (SHOW_LABELS)
    TitleText("Blue Nebula", 8, <0.9,0.9,0.0>)
  #end

#end

// Several similar distributed mCloudNebula08
#if (SCENE_NUMBER = 55)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 10 + int((frame_number-1)/6);; //step 6
  #declare rShape = seed (1235 + STARFIELD_NR);
  #declare rColor = seed (225 + STARFIELD_NR);
  #declare rPosition = seed (741 + STARFIELD_NR);
  
  #declare iColors = IRand(10,20,rColor);
  #declare NEBULA_COLORS = array[iColors];
  #declare I=0; #while (I<iColors)
    #declare NEBULA_COLORS[I] = color rgb <RRand(0.8,1.0,rColor), RRand(0.4,0.8,rColor), RRand(0.0,0.0,rColor)>;
  #declare I=I+1; #end

  #declare show = 1; #if (show) 
    #declare I=0; #while(I<2)      
      #declare rShape = seed (1235 + STARFIELD_NR + I);
      #declare rColor = seed (12225 + STARFIELD_NR + I);
      #declare rPosition = seed (12741 + STARFIELD_NR + I);
      #declare V_Rotation = <RRand(-180,180,rPosition), RRand(-180,180,rPosition), RRand(-180,180,rPosition)>;
      ///NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
      object { NebulaSelect(1,8,1,NEBULA_COLORS,0,rShape,rColor) rotate V_Rotation translate <0, 0, 1> rotate V_Rotation }
    #declare I=I+1; #end      
  #end

  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) }

  //label
  #if (SHOW_LABELS)
    TitleText("Nebulae", 8, <0.9,0.9,0.0>)
  #end

#end

// Random explosion could nebula mCloudNebula08 from inside
#if (SCENE_NUMBER = 54)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 2; //frame_number; //mod(frame_number-1,6)+1; //range [1-6]
  #declare rShape = seed (1825 + STARFIELD_NR);
  #declare rColor = seed (88225 + STARFIELD_NR);
  #declare rPosition = seed (8741 + STARFIELD_NR);
  
  #declare iColors = IRand(20,100,rColor);
  #declare NEBULA_COLORS = array[iColors];
  #declare I=0; #while (I<iColors)
    #declare NEBULA_COLORS[I] = color rgb <RRand(0.0,1.0,rColor), RRand(0.0,1.0,rColor), RRand(0.0,1.0,rColor)>;
  #declare I=I+1; #end

  #declare show = 1; #if (show) 
    #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
    ///NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
    object { NebulaSelect(1,8,1,NEBULA_COLORS,0,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  #end

  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) }

  //label
  #if (SHOW_LABELS)
    TitleText("Cloud nebula", 8, <0.9,0.9,0.0>)
  #end
  
#end

// Random explosion could nebula mCloudNebula08 from outside
#if (SCENE_NUMBER = 53)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 6; //frame_number; //mod(frame_number-1,6)+1; //range [1-6]
  #declare rShape = seed (1825 + STARFIELD_NR);
  #declare rColor = seed (88225 + STARFIELD_NR);
  #declare rPosition = seed (8741 + STARFIELD_NR);
  
  #declare iColors = IRand(4,20,rColor);
  #declare NEBULA_COLORS = array[iColors];
  #declare I=0; #while (I<iColors)
    #declare NEBULA_COLORS[I] = color rgb <RRand(0.0,1.0,rColor), RRand(0.0,1.0,rColor), RRand(0.0,1.0,rColor)>;
  #declare I=I+1; #end

  #declare show = 1; #if (show) 
    #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
    ///NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
    object { NebulaSelect(1,8,1,NEBULA_COLORS,0,rShape,rColor) rotate V_Rotation rotate <30,0,0> translate <0, 0, 1.5> }
  #end

  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) }

  //label
  #if (SHOW_LABELS)
    TitleText("Random nebula", 8, <0.9,0.9,0.0>)
  #end
  
#end


// vegastrike unused starfield5 background
#if (SCENE_NUMBER = 52)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 44; //mod(frame_number-1,6)+1; //range [1-6]
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (34825 + STARFIELD_NR);
  #declare rShape = seed (93265 + STARFIELD_NR);
  #declare rStarfield = seed (1000 + STARFIELD_NR);
  
  #declare show = 1; #if (show) 
    #declare NEBULA_COLORS = array[2];
    #declare NEBULA_COLORS[0] = color rgb <RRand(0.8,1.0,rColor), RRand(0.0,0.3,rColor), RRand(0.0,0.1,rColor)>;
    #declare NEBULA_COLORS[1] = color rgb <RRand(0.7,1.0,rColor), RRand(0.1,0.2,rColor), RRand(0.0,0.1,rColor)>;
    #declare iBackgrounds = IRand(1,2,rStarfield);
    #declare I=1; #while (I<=iBackgrounds)
      #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
      #declare iType = IRand(1,3,rStarfield);
      #declare iBackground = IRand(1,10,rStarfield);
      ///NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
      object { NebulaSelect(iType,iBackground,1,NEBULA_COLORS,0,rShape,rColor) rotate V_Rotation translate<-0.01, 0, 0> }
    #declare I=I+1; #end
  #end
  
  //some galaxies
  #declare show = 1; #if (show) 
    #declare I=1; #while (I<=10)
      #declare iArms = IRand(0,5,rShape)*2;
      #declare vTurb = VRand(rShape)*100;
      #declare fSpiral = rand(rShape)*2;
      #declare fGlow = rand(rShape);
      #declare fTurb = rand(rShape)*0.7;
      #declare fColDev = rand(rShape);
      //#include "spiral_galaxy.inc"
      #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>; //own rotation
      #declare vPosRotation = <RRand(-25,25,rPosition), RRand(-25,25,rPosition), RRand(-25,25,rPosition)>; //universe position
      //SpiralGalaxy(arms, Rand, spiralness, glowiness, turb, colShift)
      object { SpiralGalaxy(iArms, vTurb, fSpiral, fGlow, fTurb, fColDev) rotate V_Rotation translate <0,0,RRand(30,80,rPosition)> rotate vPosRotation  }
    #declare I=I+1; #end
  #end
  
  //random colored - large
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=50)
      #declare fSizeMin = RRand(6.0,12.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,3));
      #declare STAR_COLORS[0] = RandomColor(IRand(1,6,rColor),rColor, 90) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(3.5,5.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //random colored - middle
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=50)
      #declare fSizeMin = RRand(3.0,8.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,3));
      #declare STAR_COLORS[0] = RandomColor(IRand(1,6,rColor),rColor, 30) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //random colored - small
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=50)
      #declare fSizeMin = RRand(2.0,4.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,3));
      #declare STAR_COLORS[0] = RandomColor(IRand(1,6,rColor),rColor, 10) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.0,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //label
  #if (SHOW_LABELS)
    TitleText("Brown nebula", 8, <0.9,0.9,0.0>)
  #end
  
#end

// vegastrike unused starfield background
// creates too many artifacts with dds compression
#if (SCENE_NUMBER = 51)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 12; //mod(frame_number-1,6)+1; //range [1-6]
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (9876 + STARFIELD_NR);
  
  // a nebula
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor)>;
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  #declare iType = 1;
  #declare iBackground = IRand(1,6,rShape);
  ///NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object {NebulaSelect(iType,iBackground,1,NEBULA_COLORS,0,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  //random colored - large
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=50)
      #declare fSizeMin = RRand(6.0,12.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,3));
      #declare STAR_COLORS[0] = RandomColor(IRand(1,6,rColor),rColor, 90) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(3.5,5.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //random colored - middle
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=50)
      #declare fSizeMin = RRand(3.0,8.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,3));
      #declare STAR_COLORS[0] = RandomColor(IRand(1,6,rColor),rColor, 30) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //random colored - small
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=50)
      #declare fSizeMin = RRand(2.0,4.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,3));
      #declare STAR_COLORS[0] = RandomColor(IRand(1,6,rColor),rColor, 10) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.0,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //label
  #if (SHOW_LABELS)
    TitleText("Blue nebula", 8, <0.9,0.9,0.0>)
  #end
  
#end

// vegastrike starfield4 background
#if (SCENE_NUMBER = 50)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 3; //1,3,6 //frame_number; //mod(frame_number-1,6)+1; //range [1-6]
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (9876 + STARFIELD_NR);
  
  // a nebula
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor)>;
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  #declare iType = 1;
  #declare iBackground = IRand(1,6,rShape);
  ///NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(iType,iBackground,1,NEBULA_COLORS,0,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  //random colored - large
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=20)
      #declare fSizeMin = RRand(6.0,12.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,3));
      #declare STAR_COLORS[0] = RandomColor(IRand(1,6,rColor),rColor, 90) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(3.5,5.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //random colored - middle
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=50)
      #declare fSizeMin = RRand(3.0,8.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,3));
      #declare STAR_COLORS[0] = RandomColor(IRand(1,6,rColor),rColor, 30) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //random colored - small
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=50)
      #declare fSizeMin = RRand(2.0,4.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = max(2,1000/pow(fSizeMin,3));
      #declare STAR_COLORS[0] = RandomColor(IRand(1,6,rColor),rColor, 10) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.0,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //label
  #if (SHOW_LABELS)
    TitleText("Red nebula", 8, <0.9,0.9,0.0>)
  #end
  
#end

//  vegastrike starfield3 background
#if (SCENE_NUMBER = 49)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 1; //1,3,6 //frame_number; //mod(frame_number-1,6)+1; //range [1-6]
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (9876 + STARFIELD_NR);
  
  // a nebula
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor)>;
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  #declare iType = 1;
  #declare iBackground = IRand(1,6,rShape);
  /// NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(iType,iBackground,1,NEBULA_COLORS,0,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  //random colored - large
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=20)
      #declare fSizeMin = RRand(6.0,12.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 1000/pow(fSizeMin,3);
      #declare STAR_COLORS[0] = RandomColor(IRand(1,14,rColor),rColor, 20) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //random colored - middle
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=50)
      #declare fSizeMin = RRand(3.0,8.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 1000/pow(fSizeMin,3);
      #declare STAR_COLORS[0] = RandomColor(IRand(1,14,rColor),rColor, 30) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //random colored - small
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=50)
      #declare fSizeMin = RRand(2.0,4.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 1000/pow(fSizeMin,3);
      #declare STAR_COLORS[0] = RandomColor(IRand(1,14,rColor),rColor, 10) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,3.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //label
  #if (SHOW_LABELS)
    TitleText("Purple nebula", 8,<0.9,0.9,0.0>)
  #end
  
#end

//  vegastrike starfield2 background
#if (SCENE_NUMBER = 48)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 6; //1,3,6 //frame_number; //mod(frame_number-1,6)+1; //range [1-6]
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (9876 + STARFIELD_NR);
  
  // a nebula
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor), RRand(0.0,0.6,rColor)>;
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  #declare iType = 1;
  #declare iBackground = IRand(1,6,rShape);
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(1,7,1,NEBULA_COLORS,0,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  //random colored 1
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=20)
      #declare fSizeMin = RRand(3.5,4.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 100; //1e4/pow(fSizeMin,3);
      #declare STAR_COLORS[0] = RandomColor(IRand(7,14,rColor),rColor, 0) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end
  
  //random colored 2
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=20)
      #declare fSizeMin = RRand(2.5,4.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 100; //1e4/pow(fSizeMin,3);
      #declare STAR_COLORS[0] = RandomColor(IRand(12,14,rColor),rColor, 0) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(1.5,3.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //random colored 3
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=20)
      #declare fSizeMin = RRand(2.5,4.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 100; //1e4/pow(fSizeMin,3);
      #declare STAR_COLORS[0] = RandomColor(IRand(10,14,rColor),rColor, 0) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(1.5,3.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //label
  #if (SHOW_LABELS)
    TitleText("Green nebula", 8, <0.9,0.9,0.0>)
  #end
  
#end

//  starfield background
#if (SCENE_NUMBER = 47)

  Camera1(1)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 22; //frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (9876 + STARFIELD_NR);
  #declare NEBULA_COLORS = array[2];
  
  //full horizon - small blue
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=20)
      #declare fSizeMin = RRand(1.5,3.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 1e4/pow(fSizeMin,3);
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rColor), RRand(0.5,0.6,rColor), 1.0>; 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end
  
  //full horizon - small orange
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=20)
      #declare fSizeMin = RRand(1.5,3.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 20;
      #declare STAR_COLORS[0] = rgb <1.0, 0.6, RRand(0.2,0.4,rColor)>; 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25; //180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end
  
  //smaller clusters
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=20)
      #declare fSizeMin = RRand(2.0,4.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 1e4/pow(fSizeMin,3);
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rColor), RRand(0.5,0.6,rColor), 1.0>; //RandomColor(IRand(12,14,rColor),rColor, 0) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,5.5,rColor); //maximum intensity
      #declare vExcentricity = <RRand(0.5,3.0,rShape), RRand(0.5,3.0,rShape), 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = RRand(2,5,rPosition);
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)> }
    #declare STARFIELD=STARFIELD+1; #end
  #end
  
  //stars concentration in a torus
  #declare show = 1; #if (show) 
    #declare STARFIELD=0; #while (STARFIELD<=10)
      #declare fSizeMin = RRand(2.0,5.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 1e4/pow(fSizeMin,3);
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rColor), RRand(0.5,0.6,rColor), 1.0>;  //RandomColor(IRand(12,13,rColor),rColor, 0) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,5.5,rColor); //maximum intensity
      //StarConcentration(iType, fSizeMin, fSizeMax, iAmount, cColors, fIntensity, fThicknessPercent, rSeed)
      object { StarConcentration(1, fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, 0.3,rPosition) rotate <RRand(-10,-5,rPosition), RRand(-5,5,rPosition), RRand(20,30,rPosition)> }
      #declare iAmount = 1e3/pow(fSizeMin,3);
      object { StarConcentration(1, fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, 0.3,rPosition) rotate <RRand(-10,-5,rPosition),RRand(-5,5,rPosition),RRand(20,30,rPosition)> }
    #declare STARFIELD=STARFIELD+1; #end
  #end
  
  //stars concentration - a spherical cluster
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=2)
      #declare fSizeMin = RRand(3.0,6.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rColor), RRand(0.5,0.6,rColor), 1.0>;  //RandomColor(IRand(12,13,rColor),rColor, 0) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(3.0,5.5,rColor); //maximum intensity
      #declare iAmount = 1000/pow(fSizeMin,3);
      //StarConcentration(iType, fSizeMin, fSizeMax, iAmount, cColors, fIntensity, fThicknessPercent, rSeed)
      object { StarConcentration(2, fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, 0.3,rPosition) rotate <RRand(-10,-5,rPosition), RRand(-5,5,rPosition), RRand(20,30,rPosition)> }
      #declare iAmount = 500/pow(fSizeMin,3);
      object { StarConcentration(2, fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, 0.3,rPosition) rotate <RRand(-10,-5,rPosition), RRand(-5,5,rPosition), RRand(20,30,rPosition)> }
      #declare iAmount = 200/pow(fSizeMin,3);
      object { StarConcentration(2, fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, 0.3,rPosition) rotate <RRand(-10,-5,rPosition), RRand(-5,5,rPosition), RRand(20,30,rPosition)> }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //full horizon - middle yellow
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=1)
      #declare fSizeMin = RRand(2.5,5.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 200;
      #declare STAR_COLORS[0] = rgb <1.0, 1.0, RRand(0.5,0.6,rColor)>; //yellow
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.5,4.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //full horizon - big red
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=20)
      #declare fSizeMin = RRand(4.5,9.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 10;
      #declare STAR_COLORS[0] = rgb <1.0, RRand(0.2,0.4,rColor), RRand(0.2,0.4,rColor)>;
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(1.0,4.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //full horizon - large orange
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=10)
      #declare fSizeMin = RRand(8.5,12.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 10;
      #declare STAR_COLORS[0] = rgb <1.0, 0.6, RRand(0.2,0.4,rColor)>;
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(1.0,4.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  //full horizon - large blue
  #declare show = 1; #if (show) 
    #declare STARFIELD=1; #while (STARFIELD<=10)
      #declare fSizeMin = RRand(8.5,12.0,rShape);
      #declare fSizeMax = fSizeMin*1.5;
      #declare iAmount = 10;
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.6,rColor), RRand(0.5,0.6,rColor), 1.0>;
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(1.0,4.5,rColor); //maximum intensity
      #declare vExcentricity = <1, 1, 1>;
      #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
      #declare fDistrAngle = 25;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,RRand(-180,180,rPosition)> translate -z*8e3 }
    #declare STARFIELD=STARFIELD+1; #end
  #end

  #declare show = 1; #if (show) 
    #declare rPosition = seed (6741 + STARFIELD_NR);
    #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
    sky_sphere {
      P_StarField(rgb<0.9, 0.9, 1.0>, 1.0) rotate V_Rotation
      P_StarField(rgb<0.8, 0.9, 1.0>, 1.0)
    }
  #end

  //label
  #if (SHOW_LABELS)
    TitleText("Full of stars", 8, <0.9,0.9,0.0>)
  #end
  
#end

//  vegastrike plasma_galaxy
#if (SCENE_NUMBER = 46)

  Camera1(1)
  Sun(<0,0,-1000>, 1)


  #declare STARFIELD_NR = 65; //frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (9876 + STARFIELD_NR);
  #declare NEBULA_COLORS = array[2];
  
  //nebula
  #declare show = 1; #if (show) 
    #declare iBackgrounds = 1; //IRand(1,2,rShape);
    #declare I=1; #while (I<=iBackgrounds)
       #declare NEBULA_COLORS[0] = color rgb <0.693, 0.288, 0.045>;
       #declare NEBULA_COLORS[1] = color rgb <0.715, 0.383, 0.029>;
       #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
       object { NebulaSelect(1,7,1,NEBULA_COLORS,0.06,rShape,rColor) rotate V_Rotation translate<-0.01*I, 0, 0> }
    #declare I=I+1; #end
  #end
  
  //small, middle and big stars
  #declare show = 1; #if (show) 
    #declare SF_NUMBERS = array[3] {50,20, 10}; 
    //#declare SF_NUMBERS = array[3] {10,2, 10}; 
    #declare I=2; #while (I<=4) // the different sizes
      #declare STARFIELD_NR = frame_number;
      #declare STARFIELDS_NO = SF_NUMBERS[I-2];
      #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
        #declare fSizeMin = RRand(3.0,5.0,rShape)*I;
        #declare fSizeMax = fSizeMin*2.0;
        #declare iAmount = 1e4/pow(fSizeMin,3);
        #declare iColor = IRand(1,4,rColor);
        #declare STAR_COLORS[0] = RandomColor(iColor,rColor, 30) 
        #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
        #declare fIntensity = RRand(2.0,5.0,rColor); //maximum intensity
        #declare vExcentricity = <RRand(1.0,2.0,rShape), RRand(1.0,2.0,rShape), 1>;
        #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
        #declare fDistrAngle = 180;
        //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
        object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,45> translate <-4e3,4e3,0> }
      #declare STARFIELD=STARFIELD+1; #end
    #declare I=I+1; #end
  #end
  
  //globular star cluster
  #declare show = 1; #if (show) 
    #declare SF_NUMBERS = array[3] {100, 50, 20}; 
    #declare I=2; #while (I<=4) // the different sizes
      #declare STARFIELD_NR = frame_number;
      #declare STARFIELDS_NO = SF_NUMBERS[I-2];
      #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
        #declare fSizeMin = RRand(3.0,5.0,rShape)*I;
        #declare fSizeMax = fSizeMin*2.0;
        #declare iAmount = 1e4/pow(fSizeMin,3);
        #declare iColor = IRand(2,3,rColor);
        #declare STAR_COLORS[0] = RandomColor(iColor,rColor, 30) 
        #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
        #declare fIntensity = RRand(2.0,5.0,rColor); //maximum intensity
        #declare vExcentricity = <RRand(1.0,2.0,rShape), RRand(1.0,2.0,rShape), 1>;
        #declare vOrientation = <0,0, RRand(0,180,rPosition)>;
        #declare fDistrAngle = RRand(3,20,rPosition);
        //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
        object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rShape) rotate <0,0,45> translate <-4e3,4e3,0> }
      #declare STARFIELD=STARFIELD+1; #end
    #declare I=I+1; #end
  #end
  
  //some galaxies
  #declare show = 0; #if (show) 
    #declare I=1; #while (I<=10)
      #declare iArms = IRand(0,5,rShape)*2;
      #declare vTurb = VRand(rShape)*100;
      #declare fSpiral = rand(rShape)*2;
      #declare fGlow = rand(rShape);
      #declare fTurb = rand(rShape)*0.7;
      #declare fColDev = rand(rShape);
      //#include "spiral_galaxy.inc"
      #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>; //own rotation
      #declare vPosRotation = <RRand(-180,180,rPosition), RRand(-180,180,rPosition), RRand(-180,180,rPosition)>; //universe position
      //SpiralGalaxy(arms, Rand, spiralness, glowiness, turb, colShift)
      object { SpiralGalaxy(iArms, vTurb, fSpiral, fGlow, fTurb, fColDev) rotate V_Rotation translate <0,0,RRand(30,60,rPosition)> rotate vPosRotation  }
    #declare I=I+1; #end
  #end
  
  #declare show = 1; #if (show) 
    #declare rPosition = seed (6741 + STARFIELD_NR);
    #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
    sky_sphere { P_StarField(rgb<0.9,0.9,1>, 1.0) rotate V_Rotation }
  #end

  //label
  #if (SHOW_LABELS)
    TitleText("Plasma galaxy", 8, <0.9,0.9,0.0>)
  #end
  
#end

//  vegastrike red_galaxy1
#if (SCENE_NUMBER = 45)

  Camera1(1)
  Sun(<0,0,-1000>, 1)


  #declare STARFIELD_NR = 13; //frame_number;
  #declare rPosition = seed (6741 + STARFIELD_NR);
  #declare rShape = seed (5271 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <0.9235, 0.0754, 0.0375>;
  #declare NEBULA_COLORS[1] = color rgb <0.7243, 0.8491, 0.0180>;
  
  #declare show = 1; #if (show) 
    #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
    //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
    object { NebulaSelect(1,1,1,NEBULA_COLORS,0.02,rShape,rColor) rotate V_Rotation translate <-0.01, 0, 0> }
  
    #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
    //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
    object { NebulaSelect(1,2,1,NEBULA_COLORS,0.02,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  #end
  
  #declare SeedS = seed(16486+STARFIELD_NR);
  
  //star streaks in the nebula - upper left
  #declare show = 1; #if (show) 
    #declare STARFIELD_NR = frame_number;
    #declare STARFIELDS_NO = 1; //IRand(4,8,SeedS);
    #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
      #declare fSizeMin = RRand(3.0,8.0,SeedS);
      #declare fSizeMax = fSizeMin*2.0;
      #declare iAmount = 1e4/pow(fSizeMin,3);
      #declare iColor = IRand(1,4,rColor);
      #declare STAR_COLORS[0] = RandomColor(iColor,rColor, 30) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.0,5.0,SeedS); //maximum intensity
      #declare vExcentricity = <2, 0.5, 1>;
      #declare vOrientation = <0,0, RRand(0,180,SeedS)>;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, 5, vOrientation, vExcentricity, SeedS) rotate <0,0,45> translate <-4e3,4e3,0> }
    #declare STARFIELD=STARFIELD+1; #end
  #end
  
  //star streaks in the nebula - upper right
  #declare STARFIELD_NR = frame_number;
    #declare show = 1; #if (show) 
    #declare STARFIELDS_NO = 1; //IRand(4,8,SeedS);
    #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
      #declare fSizeMin = RRand(3.0,6.0,SeedS);
      #declare fSizeMax = fSizeMin*2.0;
      #declare iAmount = 1e4/pow(fSizeMin,3);
      #declare iColor = IRand(1,4,rColor);
      #declare STAR_COLORS[0] = RandomColor(iColor,rColor, 30) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.0,5.0,SeedS); //maximum intensity
      #declare vExcentricity = <2, 0.5, 1>;
      #declare vOrientation = <0,0, RRand(0,180,SeedS)>;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, 5, vOrientation, vExcentricity, SeedS) rotate <0,0,-45> translate <4e3,4e3,0> }
    #declare STARFIELD=STARFIELD+1; #end
  #end
  
  //star streaks in the nebula - middle
  #declare STARFIELD_NR = frame_number;
    #declare show = 1; #if (show) 
    #declare STARFIELDS_NO = 10; //IRand(4,8,SeedS);
    #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
      #declare fSizeMin = RRand(3.0,6.0,SeedS);
      #declare fSizeMax = fSizeMin*2.0;
      #declare iAmount = 1e4/pow(fSizeMin,3);
      #declare iColor = IRand(1,4,rColor);
      #declare STAR_COLORS[0] = RandomColor(iColor,rColor, 30) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.0,5.0,SeedS); //maximum intensity
      #declare vExcentricity = <RRand(1.0,1.5,SeedS), RRand(1.0,1.5,SeedS), 1>;
      #declare vOrientation = <0,0, RRand(0,180,SeedS)>;
      #declare fDistrAngle = RRand(3,10,SeedS);
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, SeedS) }
    #declare STARFIELD=STARFIELD+1; #end
  #end
  
  //star streaks in the nebula - lower left
  #declare STARFIELD_NR = frame_number;
    #declare show = 1; #if (show) 
    #declare STARFIELDS_NO = 10; //IRand(4,8,SeedS);
    #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
      #declare fSizeMin = RRand(3.0,6.0,SeedS);
      #declare fSizeMax = fSizeMin*2.0;
      #declare iAmount = 1e4/pow(fSizeMin,3);
      #declare iColor = IRand(1,4,rColor);
      #declare STAR_COLORS[0] = RandomColor(iColor,rColor, 30) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.0,5.0,SeedS); //maximum intensity
      #declare vExcentricity = <RRand(1.0,1.5,SeedS), RRand(1.0,1.5,SeedS), 1>;
      #declare vOrientation = <0,0, RRand(0,180,SeedS)>;
      #declare fDistrAngle = RRand(3,10,SeedS);
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, SeedS) rotate <0,0,0> translate <-4e3,-4e3,0> }
    #declare STARFIELD=STARFIELD+1; #end
  #end
  
  //small stars
  #declare show = 1; #if (show) 
    #declare STARFIELD_NR = frame_number;
    #declare STARFIELDS_NO = 100; //IRand(4,8,SeedS);
    #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
      #declare fSizeMin = RRand(3.0,6.0,SeedS);
      #declare fSizeMax = fSizeMin*2.0;
      #declare iAmount = 1e4/pow(fSizeMin,3);
      #declare iColor = IRand(1,4,rColor);
      #declare STAR_COLORS[0] = RandomColor(iColor,rColor, 30) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.0,5.0,SeedS); //maximum intensity
      #declare vExcentricity = <RRand(1.0,2.0,SeedS), RRand(1.0,2.0,SeedS), 1>;
      #declare vOrientation = <0,0, RRand(-180,180,SeedS)>;
      #declare fDistrAngle = 180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, SeedS) }
    #declare STARFIELD=STARFIELD+1; #end
  #end
  
  //middle stars
  #declare show = 1; #if (show) 
    #declare STARFIELD_NR = frame_number;
    #declare STARFIELDS_NO = 10; //IRand(4,8,SeedS);
    #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
      #declare fSizeMin = RRand(5.0,10.0,SeedS);
      #declare fSizeMax = fSizeMin*2.0;
      #declare iAmount = 1e4/pow(fSizeMin,3);
      #declare iColor = IRand(1,4,rColor);
      #declare STAR_COLORS[0] = RandomColor(iColor,rColor, 30) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.0,5.0,SeedS); //maximum intensity
      #declare vExcentricity = <RRand(1.0,2.0,SeedS), RRand(1.0,2.0,SeedS), 1>;
      #declare vOrientation = <0,0, RRand(-180,180,SeedS)>;
      #declare fDistrAngle = 180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, SeedS) }
    #declare STARFIELD=STARFIELD+1; #end
  #end
  
  //big stars
  #declare show = 1; #if (show) 
    #declare STARFIELD_NR = frame_number;
    #declare STARFIELDS_NO = 5; //IRand(4,8,SeedS);
    #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
      #declare fSizeMin = RRand(10.0,15.0,SeedS);
      #declare fSizeMax = fSizeMin*2.0;
      #declare iAmount = 1e4/pow(fSizeMin,3);
      #declare iColor = IRand(1,4,rColor);
      #declare STAR_COLORS[0] = RandomColor(iColor,rColor, 30) 
      #declare STAR_COLORS[1] = STAR_COLORS[0]*0.95; 
      #declare fIntensity = RRand(2.0,5.0,SeedS); //maximum intensity
      #declare vExcentricity = <RRand(1.0,2.0,SeedS), RRand(1.0,2.0,SeedS), 1>;
      #declare vOrientation = <0,0, RRand(-180,180,SeedS)>;
      #declare fDistrAngle = 180;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, SeedS) }
    #declare STARFIELD=STARFIELD+1; #end
  #end
  
  #declare show = 1; #if (show) 
    #declare STARFIELD_NR = frame_number;
    #declare rPosition = seed (6741 + STARFIELD_NR);
    #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
    sky_sphere { P_StarField(rgb<0.9,0.9,1>, 1.0) rotate V_Rotation }
  #end

  //label
  #if (SHOW_LABELS)
    TitleText("Red galaxy", 8, <0.9,0.9,0.0>)
  #end
  
#end //SCENE

//  many spiral galaxies
#if (SCENE_NUMBER = 44)

  Camera1(0)
  #declare STARFIELD_NR = frame_number;
  #declare rShape = seed (5619 + STARFIELD_NR);
  #declare rPosition = seed (126741 + STARFIELD_NR);

  //large and small, distributed until the edge
  #declare iStarfield=1; #while (iStarfield<=20)
    #declare iArms = IRand(0,5,rShape)*2;
    #declare vTurb = VRand(rShape)*100;
    #declare fSpiral = rand(rShape)*2;
    #declare fGlow = rand(rShape);
    #declare fTurb = rand(rShape)*0.7;
    #declare fColDev = rand(rShape);
    #declare vRotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
    #declare vPosition = <0, 0, RRand(10,50,rPosition)>;
    //SpiralGalaxy(arms, Rand, spiralness, glowiness, turb, colShift)
    object { SpiralGalaxy(iArms, vTurb, fSpiral, fGlow, fTurb, fColDev) rotate vRotation translate vPosition rotate <RRand(-20,20,rPosition), RRand(-25,25,rPosition), 0>}
  #declare iStarfield=iStarfield+1; #end

  //middle and small, around the center
  #declare iStarfield=1; #while (iStarfield<=150)
    #declare iArms = IRand(0,5,rShape)*2;
    #declare vTurb = VRand(rShape)*100;
    #declare fSpiral = rand(rShape)*2;
    #declare fGlow = rand(rShape);
    #declare fTurb = rand(rShape)*0.7;
    #declare fColDev = rand(rShape);
    #declare vRotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
    #declare vPosition = <0, 0, RRand(30,100,rPosition)>;
    //SpiralGalaxy(arms, Rand, spiralness, glowiness, turb, colShift)
    object { SpiralGalaxy(iArms, vTurb, fSpiral, fGlow, fTurb, fColDev) rotate vRotation translate vPosition rotate <RRand(-20,20,rPosition), RRand(-25,25,rPosition), 0>}
  #declare iStarfield=iStarfield+1; #end
  
  sky_sphere { P_StarField(rgb<1.0, 0.8, 0.7>, 1.0) }

  //label
  TitleText("Galactic field", 8, <0.9,0.9,0.0>)
  #if (SHOW_LABELS)
    TitleText("Galactic field", 8, <0.9,0.9,0.0>)
  #end

#end //SCENE


//  nebula with stars
#if (SCENE_NUMBER = 43)

  Camera1(6000)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 3;
  #declare rPosition = seed (842 + STARFIELD_NR);
  #declare rColor = seed (1825 + STARFIELD_NR);
  #declare rShape = seed (2134+STARFIELD_NR);
  #declare rStars = seed (23474+STARFIELD_NR);

  //orange large stars
  #declare STARFIELDS_NO = 10;
  #declare iStarfield=1; #while (iStarfield<=STARFIELDS_NO)
    #declare fSizeMax = RRand(10.0,20.0,rStars);
    #declare fSizeMin = fSizeMax*0.8;
    #declare iAmount = 1e5/pow(fSizeMax,3);
    #declare STAR_COLORS[0] = rgb <1, RRand(0.4,0.6,rStars), RRand(0.0,0.1,rStars)>; 
    #declare STAR_COLORS[1] = STAR_COLORS[0]; 
    #declare fIntensity = RRand(1.0,2.0,rStars); //maximum intensity
    #declare vExcentricity = <1, 1, 1>;
    #declare vOrientation = <0, 0, RRand(-180,180,rStars)>;
    #declare fDistribution = 25;
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistribution, vOrientation, vExcentricity, rStars) }
  #declare iStarfield=iStarfield+1; #end

  //orange small stars
  #declare STARFIELDS_NO = 50;
  #declare iStarfield=1; #while (iStarfield<=STARFIELDS_NO)
    #declare fSizeMax = RRand(4.0,10.0,rStars);
    #declare fSizeMin = fSizeMax*0.8;
    #declare iAmount = 1e4/pow(fSizeMax,3);
    #declare STAR_COLORS[0] = rgb <1, RRand(0.4,0.6,rStars), RRand(0.0,0.1,rStars)>; 
    #declare STAR_COLORS[1] = STAR_COLORS[0]; 
    #declare fIntensity = RRand(1.0,1.5,rStars); //maximum intensity
    #declare vExcentricity = <1, 1, 1>;
    #declare vOrientation = <0, 0, RRand(-180,180,rStars)>;
    #declare fDistribution = 25;
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistribution, vOrientation, vExcentricity, rStars) }
  #declare iStarfield=iStarfield+1; #end

  //small clusters - right
  #declare STAR_COLORS[0] = rgb <1.0, 0.4, 0.0>; #declare STAR_COLORS[1] = STAR_COLORS[0]*0.8;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(3.0, 8.0, 100, STAR_COLORS, 1.0, 1.0, <0,0,RRand(-180,180,rStars)>, <1, 1.5, 1>, rStars) rotate <-2,15,0> }
  object { StarCluster(5.0, 7.0, 300, STAR_COLORS, 0.9, 3.0, <0,0,RRand(10,20,rStars)>, <1, 1.1, 1>, rStars) rotate <-2,15,0> }

  //small clusters - left down
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(6.0, 10.0, 100, STAR_COLORS, 2.0, 2.0, <0,0,RRand(-180,180,rStars)>, <1.5, 1.1, 1>, rStars) rotate <8,-18,0> }
  object { StarCluster(5.0, 7.0, 300, STAR_COLORS, 1.0, 3.0, <0,0,30>, <1, 2, 1>, rStars) rotate <8,-18,0> }

  //small clusters - left up
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(10.0, 15.0, 50, STAR_COLORS, 2.0, 1.5, <0,0,RRand(-180,180,rStars)>, <1.5, 1.1, 1>, rStars) rotate <-6,-14,0> }
  object { StarCluster(4.0, 10.0, 300, STAR_COLORS, 2.0, 3.0, <0,0,0>, <1, 2, 1>, rStars) rotate <-6,-14,0> }

  //orange nebula  
  #declare NEBULA_COLORS = array[2];
  #declare NEBULA_COLORS[0] = color rgb <RRand(0.5,0.8,rColor), RRand(0.0,0.3,rColor), RRand(0.0,0.1,rColor)>;
  #declare NEBULA_COLORS[1] = color rgb <RRand(0.5,0.7,rColor), RRand(0.5,0.8,rColor), RRand(0.0,0.1,rColor)>;
  #declare V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;
  //NebulaSelect(iType,iNumber, fSize, cColors, fEmission, rShapeSeed, rColorSeed)
  object { NebulaSelect(1,1,1,NEBULA_COLORS,0.2,rShape,rColor) rotate V_Rotation translate <0, 0, 0> }
  
  sky_sphere { P_StarField(rgb<1.0, 0.6, 0.0>, 1.0) }

  //label
  #if (SHOW_LABELS)
    TitleText("Nebula with stars", 8, <0.9,0.9,0.0>)
  #end

#end //SCENE

// faked omega centauri globular star cluster
// original from Astronomy Picture of the Day, 1st May 2008
// http://apod.nasa.gov/apod/ap080501.html
#if (SCENE_NUMBER = 42)

  Camera1(6000)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = 7;
  #declare rStars = seed (2547 + STARFIELD_NR);
  #declare rColor = seed(1646+STARFIELD_NR);
  
  //whitish center
  #declare STARFIELDS_NO = 10;
  #declare iStarfield=1; #while (iStarfield<=STARFIELDS_NO)
    #declare fSizeMax = RRand(8.0,15.0,rStars);
    #declare fSizeMin = fSizeMax*0.8;
    #declare iAmount = 1e5/pow(fSizeMin,3);
    #declare STAR_COLORS[0] = rgb <RRand(0.9,1.0,rStars), RRand(0.9,1.0,rStars), 1>; 
    #declare STAR_COLORS[1] = rgb <RRand(0.7,0.9,rStars), RRand(0.7,0.9,rStars), 1>; 
    #declare fIntensity = RRand(1.0,2.0,rStars); //maximum intensity
    #declare vExcentricity = <1, 1, 1>;
    #declare vOrientation = <0, 0, RRand(-180,180,rStars)>;
    #declare fDistribution = 3; //3/pow(iStarfield,0.2); //higher exponent -> denser concentration
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistribution, vOrientation, vExcentricity, rStars) }
  #declare iStarfield=iStarfield+1; #end

  //yellowish center larger stars
  #declare STARFIELDS_NO = 10;
  #declare iStarfield=1; #while (iStarfield<=STARFIELDS_NO)
    #declare fSizeMax = RRand(10.0,25.0,rStars);
    #declare fSizeMin = fSizeMax*0.8;
    #declare iAmount = 1e5/pow(fSizeMax,3);
    #declare STAR_COLORS[0] = rgb <1.0, 1.0, 0.9>; 
    #declare STAR_COLORS[1] = rgb <0.9, 0.5, 0.0>; 
    #declare fIntensity = RRand(2.0,3.0,rStars); //maximum intensity
    #declare vExcentricity = <1, 1, 1>;
    #declare vOrientation = <0, 0, RRand(-180,180,rStars)>;
    #declare fDistribution = 25/pow(iStarfield,0.3); //higher exponent -> denser concentration
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistribution, vOrientation, vExcentricity, rStars) }
  #declare iStarfield=iStarfield+1; #end

  //yellowish distributed smaller stars
  #declare STARFIELDS_NO = 10; //10
  #declare iStarfield=1; #while (iStarfield<=STARFIELDS_NO)
    #declare fSizeMax = RRand(3.0,10.0,rStars);
    #declare fSizeMin = fSizeMax*0.8;
    #declare iAmount = 4e4/pow(fSizeMax,3);
    #declare STAR_COLORS[0] = rgb <1.0, 1.0, 0.9>; 
    #declare STAR_COLORS[1] = rgb <0.9, 0.5, 0.0>; 
    #declare fIntensity = RRand(2.0,3.0,rStars); //maximum intensity
    #declare vExcentricity = <1, 1, 1>;
    #declare vOrientation = <0, 0, RRand(-180,180,rStars)>;
    #declare fDistribution = 20/pow(iStarfield,0.2);
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistribution, vOrientation, vExcentricity, rStars) }
  #declare iStarfield=iStarfield+1; #end

  //blue stars
  #declare STARFIELDS_NO = 10;
  #declare iStarfield=1; #while (iStarfield<=STARFIELDS_NO)
    #declare fSizeMax = RRand(5.0,8.0,rStars);
    #declare fSizeMin = fSizeMax*0.8;
    #declare iAmount = 1e4/pow(fSizeMax,2);
    #declare STAR_COLORS[0] = rgb <RRand(0.3,0.4,rStars), RRand(0.3,0.4,rStars), 1>; 
    #declare STAR_COLORS[1] = STAR_COLORS[0]; 
    #declare fIntensity = RRand(3.0,5.0,rStars); //maximum intensity
    #declare vExcentricity = <1, 1, 1>;
    #declare vOrientation = <0, 0, RRand(-180,180,rStars)>;
    #declare fDistribution = 25/pow(iStarfield,0.2);
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistribution, vOrientation, vExcentricity, rStars) }
  #declare iStarfield=iStarfield+1; #end

  //tiny red stars
  #declare STARFIELDS_NO = 10;
  #declare iStarfield=1; #while (iStarfield<=STARFIELDS_NO)
    #declare fSizeMax = RRand(6.0,10.0,rStars);
    #declare fSizeMin = fSizeMax*0.8;
    #declare iAmount = 1e4/pow(fSizeMax,2);
    #declare STAR_COLORS[0] = rgb <1, RRand(0.0,0.1,rStars), RRand(0.0,0.1,rStars)>; 
    #declare STAR_COLORS[1] = STAR_COLORS[0]; 
    #declare fIntensity = RRand(1.0,1.5,rStars); //maximum intensity
    #declare vExcentricity = <1, 1, 1>;
    #declare vOrientation = <0, 0, RRand(-180,180,rStars)>;
    #declare fDistribution = 15*pow(iStarfield,0.3);
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistribution, vOrientation, vExcentricity, rStars) }
  #declare iStarfield=iStarfield+1; #end

  //big red stars
  #declare STARFIELDS_NO = 2;
  #declare iStarfield=1; #while (iStarfield<=STARFIELDS_NO)
    #declare fSizeMax = RRand(15.0,25.0,rStars);
    #declare fSizeMin = fSizeMax*0.8;
    #declare iAmount = 1e4/pow(fSizeMax,2);
    #declare STAR_COLORS[0] = rgb <1, RRand(0.0,0.1,rStars), RRand(0.0,0.1,rStars)>; 
    #declare STAR_COLORS[1] = STAR_COLORS[0]; 
    #declare fIntensity = RRand(1.0,2.0,rStars); //maximum intensity
    #declare vExcentricity = <1, 1, 1>;
    #declare vOrientation = <0, 0, RRand(-180,180,rStars)>;
    #declare fDistribution = 25/pow(iStarfield,0.2);
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistribution, vOrientation, vExcentricity, rStars) }
  #declare iStarfield=iStarfield+1; #end

  //tiny white stars on margins
  #declare STARFIELDS_NO = 10;
  #declare iStarfield=1; #while (iStarfield<=STARFIELDS_NO)
    #declare fSizeMax = RRand(4.0,8.0,rStars);
    #declare fSizeMin = fSizeMax*0.8;
    #declare iAmount = 1e4/pow(fSizeMax,2);
    #declare STAR_COLORS[0] = rgb <1, 1, 1>; 
    #declare STAR_COLORS[1] = rgb <1, 1, 1>; 
    #declare fIntensity = RRand(1.0,2.0,rStars); //maximum intensity
    #declare vExcentricity = <1, 1, 1>;
    #declare vOrientation = <0, 0, RRand(-180,180,rStars)>;
    #declare fDistribution = 25;
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistribution, vOrientation, vExcentricity, rStars) }
  #declare iStarfield=iStarfield+1; #end

  //whitish center haze
  #declare show=1; #if(show)
    triangle {<-1, -.6, 0>, <0, 1, 0>, <1, -.6, 0>
      pigment {onion pigment_map { [0 rgb<0.7,0.7,1> transmit 0.4] [0.25 rgb<0,0,0> transmit 1] }
        scale 4 poly_wave 0.7 }
      finish {ambient 1 diffuse 0 reflection 0 phong 0 specular 0 crand 0}
      scale 200 translate 500*z
    }
  #end    

  //red background haze
  #declare show=1; #if(show)
    #declare pHaze = pigment { bozo color_map { [0 rgb<0.5,0,0> transmit 0.6 filter 1] [0.4 rgb<0,0,0> transmit 1 ] } turbulence 0.5 omega 0.6 lambda 4.5 frequency 5 }
    triangle {<-1, -.6, 0>, <0, 1, 0>, <1, -.6, 0>
      pigment { onion pigment_map { [0 pHaze scale 3e-3] [0.25 rgb<0,0,0> transmit 0 ] }
        scale 4 poly_wave 0.7 }
      finish {ambient 1 diffuse 0 reflection 0 phong 0 specular 0 crand 0}
      scale 4e4 translate (2e4+20)*z
    }
  #end    

  //blue background haze
  #declare show=1; #if(show)
    #declare pHaze = pigment { bozo color_map { [0 rgb<0,0,0.7> transmit 0.6 filter 0] [0.5 rgb<0,0,0> transmit 1 ] } turbulence 0.5 lambda 1.5 }
    triangle {<-1, -.6, 0>, <0, 1, 0>, <1, -.6, 0>
      pigment { onion pigment_map { [0 pHaze scale 1e-3] [0.25 rgb<0,0,0> transmit 0 ] }
        scale 4 poly_wave 0.7 }
      finish {ambient 1 diffuse 0 reflection 0 phong 0 specular 0 crand 0}
      scale 4e4 translate (2e4+30)*z rotate 90*z 
    }
  #end    

  //overall blue haze
  #declare show=1; #if(show)
    triangle {<-1, -.6, 0>, <0, 1, 0>, <1, -.6, 0>
      pigment {onion pigment_map { [0 rgb<0.1,0.1,1> transmit 0.95] [0.25 rgb<0,0,0> transmit 0.99] }
        scale 4 poly_wave 0.7 }
      finish {ambient 1 diffuse 0 reflection 0 phong 0 specular 0 crand 0}
      scale 4e4 translate (2e4+10)*z
    }
  #end    

  //label
  #if (SHOW_LABELS)
    TitleText("Omega Centauri globular star cluster", 8, <0.9,0.9,0.0>)
  #end

#end //SCENE

// galaxy with starfield
#if (SCENE_NUMBER = 41)

  Camera1(6000)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = frame_number;
  #declare SeedS = seed(1647286+STARFIELD_NR);

  //small stars
  #declare fSizeMin = 2.0;
  #declare fSizeMax = 5.0;
  #declare iAmount = 5000;
  #declare STAR_COLORS[0] = rgb <0.9, 0.9, 0.9>; #declare STAR_COLORS[1] = rgb <0.8, 0.75, 1.0>;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 2.5, 25, <0,0,0>, <1,1,1>, SeedS) }

  //large stars
  #declare fSizeMin = 6.0;
  #declare fSizeMax = 10.0;
  #declare iAmount = 2000;
  #declare STAR_COLORS[0] = rgb <0.9, 0.9, 0.9>; #declare STAR_COLORS[1] = rgb <0.8, 0.75, 1.0>;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 2.5, 25, <0,0,0>, <1,1,1>, SeedS) }

  //galaxy center
  #declare STARFIELDS_NO = 5;
  #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
    #declare fSizeMin = RRand(3.0,6.0,SeedS);
    #declare fSizeMax = fSizeMin*2.0;
    #declare iAmount = 1e5/pow(fSizeMin,3);
    #declare STAR_COLORS[0] = rgb <RRand(0.95,1.0,SeedS), RRand(0.95,1.0,SeedS), RRand(0.99,1.0,SeedS)>; 
    #declare STAR_COLORS[1] = rgb <RRand(0.5,0.99,SeedS), RRand(0.5,0.99,SeedS), RRand(0.95,1.0,SeedS)>; 
    #declare fIntensity = RRand(1.5,3.0,SeedS); //maximum intensity
    #declare vExcentricity = <1, 1, 1>;
    #declare vOrientation = <0, 0, RRand(-180,180,SeedS)>;
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, 2.0, vOrientation, vExcentricity, SeedS) }
  #declare STARFIELD=STARFIELD+1; #end
  
  //galaxy rims
  #declare STARFIELDS_NO = 10;
  #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
    #declare fSizeMin = RRand(2.0,5.0,SeedS);
    #declare fSizeMax = fSizeMin*2.0;
    #declare iAmount = 3e4/pow(fSizeMin,3);
    #declare STAR_COLORS[0] = rgb <RRand(0.95,1.0,SeedS), RRand(0.95,1.0,SeedS), RRand(0.99,1.0,SeedS)>; 
    #declare STAR_COLORS[1] = rgb <RRand(0.5,0.99,SeedS), RRand(0.5,0.99,SeedS), RRand(0.95,1.0,SeedS)>; 
    #declare fIntensity = RRand(1.0,2.0,SeedS); //maximum intensity
    #declare vExcentricity = <0.01, 10, 0.01>;
    #declare vOrientation = <0, 0, 30>;
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, 1.0, vOrientation, vExcentricity, SeedS) }
  #declare STARFIELD=STARFIELD+1; #end

  sky_sphere { P_StarField(rgb<0.9,0.9,1>, 1.0) }

  //label
  #if (SHOW_LABELS)
    TitleText("StarCluster galaxy", 8, <0.9,0.9,0.0>)
  #end

#end

// multiple star fields overlayed //75M tokens - 18m render time
#if (SCENE_NUMBER = 40)

  Camera1(6000)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = frame_number;
  #declare SeedS = seed(16486+STARFIELD_NR);
  #declare rColor = seed(16486+STARFIELD_NR);
  
  //small stars
  #declare STARFIELDS_NO = 10; //100
  #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
    #declare fSizeMin = RRand(1.0,5.0,SeedS);
    #declare fSizeMax = fSizeMin*2.0;
    #declare iAmount = 100; //1e4/pow(fSizeMin,3);
    #declare STAR_COLORS[0] = rgb <RRand(0.5,1.0,rColor),RRand(0.5,1.0,rColor),RRand(0.5,1.0,rColor)>; 
    #declare STAR_COLORS[1] = STAR_COLORS[0]*0.8; 
    #declare fIntensity = RRand(2.0,5.0,SeedS); //maximum intensity
    #declare vExcentricity = <RRand(1.0,2.0,SeedS), RRand(1.0,2.0,SeedS), 1>;
    #declare vOrientation = <0,0, RRand(0,180,SeedS)>;
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, 25, vOrientation, vExcentricity, SeedS) }
  #declare STARFIELD=STARFIELD+1; #end

  //large stars
  #declare STARFIELDS_NO = 5; //100
  #declare STARFIELD=1; #while (STARFIELD<=STARFIELDS_NO)
    #declare fSizeMin = RRand(5.0,10.0,SeedS);
    #declare fSizeMax = fSizeMin*2.0;
    #declare iAmount = 100; //1e5/pow(fSizeMin,3);
    #declare STAR_COLORS[0] = rgb <RRand(0.5,1.0,rColor),RRand(0.5,1.0,rColor),RRand(0.5,1.0,rColor)>; 
    #declare STAR_COLORS[1] = STAR_COLORS[0]*0.7; 
    #declare fIntensity = RRand(2.0,5.0,SeedS); //maximum intensity
    #declare vExcentricity = <RRand(1.0,2.0,SeedS), RRand(1.0,2.0,SeedS), 1>;
    #declare vOrientation = <0,0, RRand(0,180,SeedS)>;
    //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
    object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, 25, vOrientation, vExcentricity, SeedS) }
  #declare STARFIELD=STARFIELD+1; #end

  //label
  #if (SHOW_LABELS)
    TitleText("Colored starfield", 8, <0.9,0.9,0.0>)
  #end

#end

// excentric star cluster and background stars
#if (SCENE_NUMBER = 39)

  Camera1(6000)
  Sun(<0,0,-1000>, 1)

  #declare STARFIELD_NR = frame_number;
  #declare SeedS = seed(9357+STARFIELD_NR);

  //a streak
  #declare fSizeMin = 1.0;
  #declare fSizeMax = 4.0;
  #declare iAmount = 5000;
  #declare STAR_COLORS[0] = rgb <0.9, 0.9, 0.9>; #declare STAR_COLORS[1] = rgb <0.8, 0.85, 1.0>;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 5.0, 5, <0,0,-45>, <3,1,1>, SeedS) }

  //uniform - small
  #declare fSizeMin = 1.0;
  #declare fSizeMax = 5.0;
  #declare iAmount = 10000;
  #declare STAR_COLORS[0] = rgb <0.9, 0.9, 0.9>; #declare STAR_COLORS[1] = rgb <0.6, 0.75, 1.0>;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 3.0, 25, <0,0,0>, <1,1,1>, SeedS) }

  //uniform - medium
  #declare fSizeMin = 3.0;
  #declare fSizeMax = 8.0;
  #declare iAmount = 1000;
  #declare STAR_COLORS[0] = rgb <0.9, 0.9, 0.9>; #declare STAR_COLORS[1] = rgb <0.6, 0.75, 1.0>;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 2.0, 25, <0,0,0>, <1,1,1>, SeedS) }

  //uniform - large
  #declare fSizeMin = 6.0;
  #declare fSizeMax = 10.0;
  #declare iAmount = 500;
  #declare STAR_COLORS[0] = rgb <1.0, 1.0, 1.0>; #declare STAR_COLORS[1] = rgb <0.80, 0.85, 1.0>;
  //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
  object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, 4.0, 25, <0,0,0>, <1,1,1>, SeedS) }
  
  //label
  #if (SHOW_LABELS)
    TitleText("Starfield background", 8, <0.9,0.9,0.0>)
  #end

#end

// suns from close
#if (SCENE_NUMBER = 38)
  Sun(<2000, 0, -100000>, 1)
  Camera(<0,0,-20000>, <0,0,0>, 50)
  #declare fSunRadius = 1e4;
  object { Star(fSunRadius*1.3) translate <-1.3*fSunRadius, -0.3*fSunRadius, 10*fSunRadius> }
  object { Star(fSunRadius) translate <1.1*fSunRadius, 0.3*fSunRadius, 10*fSunRadius> }
#end

// a simple scene from the simple_scene file
#if (SCENE_NUMBER = 37)
  Sun(<2000, 0, -100000>, 1)
  Camera(<0,0,-3000>, <100,200,0>, 45)
  GasGiant4(1000, rgb <0.62,0.82,0.26>, 20, 1, seed(8691)) //<0.52,0.82,0.20>
  Nebula(2e4-1, array[1]{rgb <0.1,1,0>}, 0.003, seed(4231), seed(2798))
  Nebula(2e4-1, array[2]{rgb <1,0.8,0.7>,rgb <2,0.6,0>}, 0.003, seed(9999), seed(7777))
  Starfield()
  // yellow big stars
  StarCluster(20, 40, 100, array[1]{rgb<0.9,0.6,0.0>}, 4, 20, <0,0,0>, <1,1,1>, seed(611))
  // orange small stars
  StarCluster(10, 20, 300, array[1]{rgb<0.9,0.4,0.0>}, 3, 20, <0,0,0>, <1,1,1>, seed(618))
#end

// close moon and distant earth
#if (SCENE_NUMBER = 36)

  #declare fPlanetRadius = 6366; //6366 = earth radius;
  
  Sun(<fPlanetRadius*1000, fPlanetRadius*2000, fPlanetRadius*1000>, 1)
  Camera(<0, 0, -fPlanetRadius*20>, <-fPlanetRadius*1.5, -fPlanetRadius*1.5, 0>, 20)

  // syntax: Planet(fPlanetRadius, sTextureMap, sBumpMap)
  Planet(fPlanetRadius, EARTH_MAP, "")
  // syntax: Atmosphere(fBaseRadius, fAtmosphereFactor cAtmosphereColor)
  Atmosphere(fPlanetRadius, 1.02, cAtmosphereColor)

  // moon
  #declare fPlanetRadius = 1737; //1737km = moon radius;
  object { Planet(fPlanetRadius, MOON_MAP, "") translate <-fPlanetRadius*0.7, -fPlanetRadius*0.7, -120000> }
  
  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) scale 0.2 }

#end

// earth on the horizon
#if (SCENE_NUMBER = 35)

  #declare fPlanetRadius = 6366; //6366 = earth radius;
  
  Sun(<fPlanetRadius*1000, fPlanetRadius*2000, fPlanetRadius*1000>, 1)
  Camera(<0, 0, -fPlanetRadius*20>, <0, 0, 0>, 20)

  // syntax: Planet(fPlanetRadius, sTextureMap, sBumpMap)
  Planet(fPlanetRadius, EARTH_MAP, "")
  // syntax: Atmosphere(fBaseRadius, fAtmosphereFactor cAtmosphereColor)
  Atmosphere(fPlanetRadius, 1.02, cAtmosphereColor)

  // moon
  #declare fPlanetRadius = 1737; //1737km = moon radius;
  object { Planet(fPlanetRadius, MOON_MAP, "") translate <0, -fPlanetRadius, -120000> }
  
  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) scale 0.2 }

#end

#if (SCENE_NUMBER = 34)

  #declare fPlanetRadius = 6366; //6366 = earth radius;
  
  Sun(<fPlanetRadius*1000, fPlanetRadius*1000, -fPlanetRadius*500>, 1)
  Camera(<fPlanetRadius, 0, -fPlanetRadius*0.5>, <fPlanetRadius*0.60, fPlanetRadius*0.90, 0>, 40)

  #declare vRotation = <-90, -70, 90>;
  // syntax: Planet(fPlanetRadius, sTextureMap, sBumpMap)
  object { Planet(fPlanetRadius, EARTH_MAP, "") rotate vRotation }
  // syntax: Atmosphere(fBaseRadius, fAtmosphereFactor cAtmosphereColor)
  Atmosphere(fPlanetRadius, 1.02, cAtmosphereColor)
  
  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) scale 0.2 }

#end

// upper earth closeup with continents and cloud map
#if (SCENE_NUMBER = 33)

  #declare fPlanetRadius = 6366; //6366 = earth radius;
  
  Sun(<fPlanetRadius*1000, fPlanetRadius*1000, -fPlanetRadius*500>, 1)
  Camera(<0,fPlanetRadius*0.5,-fPlanetRadius*2>, <0, fPlanetRadius*0.3, 0>, 30)

  #declare vRotation = <-90, -70, 90>;
  // syntax: Planet(fPlanetRadius, sTextureMap, sBumpMap)
  object { Planet(fPlanetRadius, EARTH_MAP, "") rotate vRotation }
  // syntax: Atmosphere(fBaseRadius, fAtmosphereFactor cAtmosphereColor)
  Atmosphere(fPlanetRadius, 1.02, cAtmosphereColor)
  
  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) scale 0.2 }

#end

// extreme closeup with clouds
#if (SCENE_NUMBER = 32)

  #declare fPlanetRadius = 6366; //6366 = earth radius;
  
  Sun(<0, fPlanetRadius*1000, fPlanetRadius*100>, 1)
  CameraRotation(<0,fPlanetRadius,-fPlanetRadius>, <0, fPlanetRadius*1.005, 0>, 5, <0,0,-45>)

  // syntax: Planet(fPlanetRadius, sTextureMap, sBumpMap)
  Planet(fPlanetRadius, EARTH_MAP, "")
  // syntax: Atmosphere(fBaseRadius, fAtmosphereFactor cAtmosphereColor)
  Atmosphere(fPlanetRadius, 1.02, cAtmosphereColor)
  
  sky_sphere { P_StarField(rgb <0.8, 0.9, 1.0>, 1.0) scale 0.2 }

  //label
  #if (SHOW_LABELS)
    TitleText("Planet extreme close up", 8, <0.9,0.9,0.0>)
  #end

#end

// asteroid texture
#if (SCENE_NUMBER = 31)

  Sun(<200, 200, -1000>, 0.5)
  //Camera(<0,0,-10>, <0, 0, 0>, 50)
  CameraTexture()

  #declare cAsteroidColor = rgb <0.9,0.9,0.6>; // brown - preferred
  // syntax: Asteroid(fRadius, cBaseColor, rAsteroid)
  #declare surface_finish = finish { ambient 1.0 diffuse 1.0 specular 0.0 phong 0.0 }
  Asteroid(2, rgb <0.4,0.2,0.0>, seed(31))

  //label
  #if (SHOW_LABELS)
    TitleText("Asteroid Texture", 8, <0.9,0.9,0.0>)
  #end

#end

// large ring shaped asteroid field, bounded by torus
#if (SCENE_NUMBER = 30)

  Camera(<0,0,-4000>, <0, 0, 0>, 50)
  Sun(<10000, 10000, -5000>, 1)
  Sun(<-1e5, 0, -1e4>, 0.1)
   
  #declare oBoundField = torus { 1000, 150
    scale <3,0.3,3> //<2000,100,2000> //scale y min torus_r2 / 1000
    rotate <-20.0, 0.0, 30.0>
    translate <-1800.0, -100.0, 0.0>
  }
  //object { Bound_Field pigment { rgb <1.0, 0.2, 0.5> transmit 0.4} }
  
  #declare iAmount = 1000; //4k
  #declare SeedA = seed(iAmount+frame_number);
  AsteroidField(5*RRand(0.5,1.4,SeedA), rgb <0.9,0.9,0.9> , oBoundField, iAmount, SeedA)

  #declare iAmount = 2000; //14k
  #declare SeedA = seed(iAmount+frame_number);
  AsteroidField(5*RRand(0.5,1.4,SeedA), rgb <0.9,0.9,0.9> , oBoundField, iAmount, SeedA)
  
  #declare oBoundField = torus { 600, 150
    scale <3,0.3,3> //<2000,100,2000> //scale y min torus_r2 / 1000
    rotate <-20.0, 0.0, 30.0>
    translate <-1800.0, -100.0, 0.0>
  }
  //object { Bound_Field pigment { rgb <0.8, 0.2, 0.9> transmit 0.4} }
  
  #declare iAmount = 1000; //6k
  #declare SeedA = seed(iAmount+frame_number);
  AsteroidField(5*RRand(0.5,1.4,SeedA), rgb <0.9,0.9,0.9> , oBoundField, iAmount, SeedA)
  
  Starfield()

  //label
  #if (SHOW_LABELS)
    TitleText("Large Ring shaped Asteroid Field", 8, <0.9,0.9,0.0>)
  #end

#end

// random asteroid field, bounded by cylinder
#if (SCENE_NUMBER = 29)

  Camera(<0,0,-100>, <0, 0, 0>, 50)
  Sun(<2000, 2000, -1000>, 1)
  Sun(<-1e5, 0, -1e4>, 0.1)
   
  //#declare oBoundField = box { <-1.0, -0.1, -0.1>, <1.0, 0.1, 1.5>
  //   scale 100.0
  //   translate <0.0, 13.0, 1.0>
  //   rotate <-60.0, 0.0, 2.0>
  //}
  //object { Bound_Field pigment { rgb <1.0, 0.2, 0.5> transmit 0.1} }
  #declare oBoundField = cylinder { <0.0, -0.05, 0.0>, <0.0, 0.05, 0.0>, 1.0
    scale 80.0
    translate <0.0, 13.0, 1.0>
    rotate <-10.0, 0.0, 2.0>
  }
  //torus { Bound_Field pigment { rgb <1.0, 0.2, 0.5> transmit 0.9} }
  
  #declare SeedA = seed(1029);

  // syntax: AsteroidField(fAsteroidRadius, cAsteroidColor, oBoundingObject, iMaxAsteroids, rAster)
  AsteroidField(RRand(0.2,0.4,SeedA), rgb <0.9,0.9,0.9> , oBoundField, 1000, SeedA)

  //label
  #if (SHOW_LABELS)
    TitleText("Asteroid Field Bounded by Cylinder", 8, <0.9,0.9,0.0>)
  #end

#end

// random field, bounded by torus
#if (SCENE_NUMBER = 28)

  Camera(<0,0,-100>, <0, 0, 0>, 50)
  Sun(<2000, 2000, -1000>, 1)
  Sun(<-1e5, 0, -1e4>, 0.1)
  
  #declare oBoundField = torus { 1.0, 0.2
    scale 50.0
    translate <0.0, 0.0, 1.0>
    rotate <-20.0, 0.0, 2.0>
  }
  //torus { Bound_Field pigment { rgb <1.0, 0.2, 0.5> transmit 0.9} } // test object

  #declare SeedA = seed(1028);
  
  // syntax: AsteroidField(fAsteroidRadius, cAsteroidColor, oBoundingObject, iMaxAsteroids, rAster)
  AsteroidField(RRand(0.2,0.4,SeedA), rgb <0.9,0.9,0.9> , oBoundField, 1000, SeedA)

  //label
  #if (SHOW_LABELS)
    TitleText("Asteroid Field Bounded by Torus", 8, <0.9,0.9,0.0>)
  #end
  
#end

// user defined asteroid color
#if (SCENE_NUMBER = 27)
  Camera(<0,0,-9>, <0, 0, 0>, 50)
  Sun(<2000, 2000, -1000>, 1)
  Sun(<-1e5, 0, -1e4>, 0.1)

  #declare cAsteroidColor = rgb <0.25,0.15,0.0>; // brown - preferred
  AsteroidObject(1, 2, 2, 2, cAsteroidColor, seed(2011))
  //label
  #if (SHOW_LABELS)
    TitleText("Custom Asteroid Color", 8, <0.9,0.9,0.0>)
  #end
#end

// small random asteroid field //former ASTEROID_SCENE_NR = 8
#if (SCENE_NUMBER = 26)
  Camera(<0,0,-30>, <0, 0, 0>, 50)
  Sun(<2000, 2000, -1000>, 1)
  Sun(<-1e5, 0, -1e4>, 0.1)
  
  #declare MAX_NUMBER = 30;
  #declare SeedA = seed(2011);
  #local I=0;#while(I<MAX_NUMBER)
    #declare fAsteroidRadius = RRand(0.8,1.0,SeedA);
    #local xpos = RRand(-10,10,SeedA); 
    #local ypos = RRand(-6,6,SeedA); 
    #local zpos = RRand(-5,10,SeedA); 
    #declare vAsteroidTranslation = <xpos,ypos,zpos>;
    #local xrot = RRand(-1,1,SeedA)*360; 
    #local yrot = RRand(-1,1,SeedA)*360; 
    #local zrot = RRand(-1,1,SeedA)*360; 
    #declare vAsteroidRotation = <xrot,yrot,zrot>;
    object {
      AsteroidObject(IRand(1,5,SeedA), IRand(1,5,SeedA), fAsteroidRadius, 2, rgb <0.9,0.9,0.8>, seed(10))
      rotate vAsteroidRotation
      translate vAsteroidTranslation
    }
  #local I=I+1;#end
  Starfield()
  //label
  #if (SHOW_LABELS)
    TitleText("Small Random Asteroid Field", 8, <0.9,0.9,0.0>)
  #end
#end

// AsteroidObject Type and Surface Test
#if (SCENE_NUMBER = 25)
  Sun(<1e5, 0, -1e4>, 1)
  Sun(<-1e5, 0, -1e4>, 0.1)
  Camera1(2) // this is a wrong definition pos and lookat cannot be the same
  // arguments: iType, iSurface, fRadius, fCraterSize, cBaseColor, rAsteroid
  AsteroidObject(5, 5, 1.5, 0.2, rgb <0.9,0.9,0.8>, seed(10))
  //label
  #if (SHOW_LABELS)
    TitleText("Asteroid Type 5 Surface 5", 8, <0.9,0.9,0.0>)
  #end
#end

// AsteroidObject Type and Surface Test
#if (SCENE_NUMBER = 24)
  Sun(<1e5, 0, -1e4>, 1)
  Sun(<-1e5, 0, -1e4>, 0.1)
  Camera1(2) // this is a wrong definition pos and lookat cannot be the same
  // arguments: iType, iSurface, fRadius, fCraterSize, cBaseColor, rAsteroid
  AsteroidObject(4, 4, 1.5, 0.2, rgb <0.9,0.9,0.8>, seed(10))
  //label
  #if (SHOW_LABELS)
    TitleText("Asteroid Type 4 Surface 4", 8, <0.9,0.9,0.0>)
  #end
#end

// AsteroidObject Type and Surface Test
#if (SCENE_NUMBER = 23)
  Sun(<1e5, 0, -1e4>, 1)
  Sun(<-1e5, 0, -1e4>, 0.1)
  Camera1(2) // this is a wrong definition pos and lookat cannot be the same
  // arguments: iType, iSurface, fRadius, fCraterSize, cBaseColor, rAsteroid
  AsteroidObject(3, 3, 1.5, 0.2, rgb <0.9,0.9,0.8>, seed(10))
  //label
  #if (SHOW_LABELS)
    TitleText("Asteroid Type 3 Surface 3", 8, <0.9,0.9,0.0>)
  #end
#end

// AsteroidObject Type and Surface Test
#if (SCENE_NUMBER = 22)
  Sun(<1e5, 0, -1e4>, 1)
  Sun(<-1e5, 0, -1e4>, 0.1)
  Camera1(2) // this is a wrong definition pos and lookat cannot be the same
  // arguments: iType, iSurface, fRadius, fCraterSize, cBaseColor, rAsteroid
  AsteroidObject(2, 2, 1.5, 0.2, rgb <0.9,0.9,0.8>, seed(10))
  //label
  #if (SHOW_LABELS)
    TitleText("Asteroid Type 2 Surface 2", 8, <0.9,0.9,0.0>)
  #end
#end

// AsteroidObject Type and Surface Test
#if (SCENE_NUMBER = 21)
  Sun(<1e5, 0, -1e4>, 1)
  Sun(<-1e5, 0, -1e4>, 0.1)
  Camera1(2) // this is a wrong definition pos and lookat cannot be the same
  // arguments: iType, iSurface, fRadius, fCraterSize, cBaseColor, rAsteroid
  AsteroidObject(1, 1, 1.5, 0.2, rgb <0.9,0.9,0.8>, seed(10))
  //label
  #if (SHOW_LABELS)
    TitleText("Asteroid Type 1 Surface 1", 8, <0.9,0.9,0.0>)
  #end
#end

// QUICK SKYSPHERE NEBULA 
#if (SCENE_NUMBER = 20)

  Sun(<1e5, 0, -1e4>, 1)
  Camera(<0,0,0>, <0,0,1>, 30) // this is a wrong definition pos and lookat cannot be the same
  QuickNebula()

#end //SCENE

// QUICK STARFIELD & FREE CAMERA ERROR HANDLING
#if (SCENE_NUMBER = 19)

  Sun(<1e5, 0, -1e4>, 1)
  // this is a wrong definition pos and lookat cannot be the same
  // however, the free camera compensates for this case
  Camera(<0,0,0>, <0,0,0>, 30) // this is a wrong definition pos and lookat cannot be the same
  Starfield()

#end //SCENE

//Generic planet randomizer template
#if (SCENE_NUMBER = 18)

  #declare fPlanetRadius = 4500;
  Sun(<fPlanetRadius*20, fPlanetRadius*0, -fPlanetRadius*100>, 1)
  Camera1(fPlanetRadius) // for scene rendering
  //CameraTexture() // for texturing


  #declare iPlanetType = IRand(1,4,seed(123+frame_number));
  #declare n = 20110406 + frame_number;
  #declare cBaseColor = ColorHSL(RRand(0,255,seed(n)), RRand(10,70,seed(n)), RRand(50,70,seed(n)));

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
  // tests for singular planet types
  //QuickPlanet(fPlanetRadius)
  //GasGiant4(fPlanetRadius, cBaseColor, RRand(0,50,seed(n)), IRand(0,1,seed(n)), seed(n))
  //DirtPlanet9(fPlanetRadius, cBaseColor, RRand(0,50,seed(n)), IRand(0,1,seed(n)), seed(n))
  //TerranPlanet8(fPlanetRadius, array[1] {<0,0,0>}, RRand(0,50,seed(n)), IRand(0,1,seed(n)), array[4] {20210+n,20210+n,20210+n,20210+n})
  //TrantorPlanet(fPlanetRadius, array[1] {<0,0,0>}, RRand(0,50,seed(n)), IRand(0,1,seed(n)), array[7] {20210+n,20210+n,20210+n,20210+n,1+n,2+n,3+n})

#end

// TRANTOR PLANET
#if (SCENE_NUMBER = 17)

  Sun(<1e5, 0, -1e4>, 1)
  Camera(<-3000, 0, -2e4>, <0,0,0>, 30)
  //CameraTexture() // texture

  #declare rColor = seed(17);
  #declare aColors = array[6]; 
  #local c=0; #while(c<5)
    //0-red; 21-brown; 30-orange; 59-yellow; 120-green; 179-cyan; 240-blue; 300-magenta;
    #declare aColors[c] = ColorHSL(RRand(10,30,rColor),RRand(10,30,rColor),RRand(50,70,rColor));
  #local c=c+1; #end
  #declare aColors[5]  = rgb <0.149, 0.435, RRand(0.698,0.901,rColor)>; // ocean color

  // seed sequence: rStructure,rTexture,rColor,rOcean,rIce,rRiver,rLight
  #declare s = 34; //frame_number;
  TrantorPlanet(7520, aColors, RRand(10,50,rColor), 1, array[7]{21+21,22+23,23+21,21+21,21+21,21+21,20+s})
  //QuickPlanet(7520)

#end //SCENE

// TERRAN PLANET (without ice, river, lights) & COLOR BY HUE & CAMERA 8
#if (SCENE_NUMBER = 16)

  Sun(<1e5, 1e5, -1e5>, 1)
  Camera8(2120)

  #declare rColor = seed(17);
  #declare aColors = array[6]; 
  #local c=0; #while(c<5)
    //0-red; 21-brown; 30-orange; 59-yellow; 120-green; 179-cyan; 240-blue; 300-magenta;
    #declare aColors[c] = ColorHSL(RRand(10,140,rColor),RRand(10,30,rColor),RRand(30,90,rColor));
  #local c=c+1; #end
  #declare aColors[5]  = rgb <0.149, 0.435, RRand(0.698,0.901,rColor)>; // ocean color

  // seed sequence: rStructure,rTexture,rColor,rOcean,rIce,rRiver,rLight
  #declare s = frame_number;
  TerranPlanet(2125, aColors, 30, 0, array[4]{21+21,22+25,23+25,21+17})
  //QuickPlanet(2120)

#end //SCENE

// TERRAN PLANET (without ice, river, lights) & PRESET COLORS & CAMERA 8
#if (SCENE_NUMBER = 15)

  Sun(<1e5, -1e4, -5e4>, 1)
  Camera8(5340)

  InitColors()
  #declare aColors = array[6]; 
  #local c=0; #while(c<5)
    #declare aColors[c] = cGreen[IRand(0,35,seed(116))];
  #local c=c+1; #end
  #declare aColors[5]  = rgb <0.149, 0.435, 0.698>; // ocean color

  // seed sequence: rStructure,rTexture,rColor,rOcean,rIce,rRiver,rLight
  #declare s = frame_number;
  TerranPlanet(5340, aColors, 30, 0, array[3]{21+s,22+s,23+s})

#end //SCENE

// GREEN TERRAN PLANET WITH PROCEDURAL RANDOM COLORS, RIVERS, ARCTIC CIRCLE, LIGHTS & CAMERA 7
#if (SCENE_NUMBER = 14)

  Sun(<1e3, -1e4, -1e2>, 1)
  Camera7(5000)

  // seed sequence: rStructure,rTexture,rColor,rOcean,rIce,rRiver,rLight
  #declare s = frame_number;
  TerranPlanet(5000, array[1] {rgb <0,0,0>}, 30, 0, array[7] {21,22,23,24,25,26,7+s})

#end //SCENE

// TERRAN PLANET WITH PROCEDURAL RANDOM COLORS & CAMERA 5
#if (SCENE_NUMBER = 13)

  Sun(<2e4, 0, 1e4>, 1)
  Camera5(7000)
  TerranPlanet(7000, array[1] {rgb <0,0,0>}, 30, 0, array[1] {277220})

#end //SCENE

// QUICK PLANET & CAMERA 4
#if (SCENE_NUMBER = 12)

  Sun(<2000, 0, -100000>, 1)
  Camera4(7000)
  QuickPlanet(7000)

#end //SCENE

// DIRT PLANET & CAMERA 3
#if (SCENE_NUMBER = 11)

  Sun(<2000, 0, -100000>, 1)
  Camera3(4000)
  DirtPlanet(4000, rgb <0.92,0.72,0.60>, 10, 1, seed(9823))

#end //SCENE

// GAS GIANT & CAMERA 2
#if (SCENE_NUMBER = 10)

  Sun(<2000, 0, -100000>, 1)
  Camera2(8000)
  GasGiant(8000, rgb <0.92,0.72,0.60>, 10, 1, seed(987123))

#end //SCENE

// NEBULA TYPE 2 SELECT & TEXT
#if (SCENE_NUMBER = 9)

  Sun(<10000, 10000, -10000>,1)
  Camera1(3) // cinema

  //nebula
  #declare show = 1; #if (show) 
    #declare STARFIELD_NR = 10;
    #declare rShape = seed (52815);
    #declare rColor = seed (52287);
    #declare iColors = 2;
    #declare NEBULA_COLORS = array[iColors];
    #declare I=0; #while (I<iColors)
      //#declare NEBULA_COLORS[I] = color rgb <RRand(0.4,1.0,rColor), RRand(0.4,1.0,rColor), RRand(0.4,1.0,rColor)>;
      #declare NEBULA_COLORS[I] = RandomColor(IRand(1,13,rColor), rColor, 10)
    #declare I=I+1; #end
    NebulaSelect(1,IRand(1,8,rShape),1,NEBULA_COLORS,0.0,rShape,rColor)
    #if (SHOW_LABELS)
      TitleText("Nebula Test", 10, rgb <1,1,0.5>)
    #end
  #end

#end //SCENE

// NEBULA TYPE 2 SELECT
#if (SCENE_NUMBER = 8)

  Sun(<10000, 10000, -10000>,1)
  Camera1(0) // cinema

  //nebula
  #declare show = 1; #if (show) 
    #declare STARFIELD_NR = 10;
    #declare rShape = seed (1822);
    #declare rColor = seed (88231);
    #declare iColors = 2;
    #declare NEBULA_COLORS = array[iColors];
    #declare I=0; #while (I<iColors)
      //#declare NEBULA_COLORS[I] = color rgb <RRand(0.4,1.0,rColor), RRand(0.4,1.0,rColor), RRand(0.4,1.0,rColor)>;
      #declare NEBULA_COLORS[I] = RandomColor(IRand(1,13,rColor), rColor, 20)
    #declare I=I+1; #end
    NebulaSelect(2,IRand(1,2,rShape), 1e6,NEBULA_COLORS,0,rShape,rColor)
  #end

#end //SCENE

// TEST CLOUDS
#if (SCENE_NUMBER = 7)

  Sun(<10000, 10000, -10000>,1)
  //Camera6() // texture
  Camera1(6366) // cinema
  #declare cBaseColor = rgb <0.82,0.92,0.60>;
  //GasGiant4(6366, cBaseColor, 40, 0, seed(919293))
  DirtPlanet1(6366, rgb <0.82,0.92,0.60>, 40, 0, seed(255))
  //Clouds(fDensity, fRadius, cCloudColor, rSeed)
  #declare rCloud = seed(76533+frame_number);
  #declare fDensity = RRand(0.05,0.45,rCloud);
  Clouds(fDensity, 6370, rgb <1,1,1>, rCloud)
  //#declare cAtmosphereColor = rgb <0.8, 0.9, 1.0>;
  //Atmosphere(6366, 1.03, cAtmosphereColor)

#end //SCENE

#if (SCENE_NUMBER = 6)
// star cluster

  Sun(<10000, 0, -10000>, 1)
  //Camera6() // texture
  Camera1(1000) // cinema

    //bluish stars
    #declare rStars = seed (2547 + frame_number);
    #declare rColor = seed(1646 + frame_number);
    #declare iStarfields = 10;
    #declare iStarfield=1; #while (iStarfield<=iStarfields)
      #declare fSizeMax = RRand(4.0,8.0,rStars)*2000/sqrt(image_width*image_height);
      #declare fSizeMin = fSizeMax*0.2;
      #declare iAmount = 3000/fSizeMax;
      #declare STAR_COLORS[0] = rgb <RRand(0.5,0.7,rColor),RRand(0.5,0.7,rColor),1>; 
      #declare STAR_COLORS[1] = STAR_COLORS[0]; 
      #declare fIntensity = RRand(4,6,rStars);
      #declare vExcentricity = <1,1,1>;
      #declare vOrientation = <0,0, RRand(-180,180,rStars)>;
      #declare fDistrAngle = 30;
      //O_StarCluster(fSizeMin, fSizeMax, iAmount, aColors, fIntensity, fDistrAngle, vOrientation, vExcentricity, rSeed)
      object { StarCluster(fSizeMin, fSizeMax, iAmount, STAR_COLORS, fIntensity, fDistrAngle, vOrientation, vExcentricity, rStars) }
    #declare iStarfield=iStarfield+1; #end

#end //SCENE

#if (SCENE_NUMBER = 5)
// asteroid field

  Sun(<10000, 0, -10000>, 1)
  //Camera6() // texture
  Camera1(1000) // cinema

  //asteroids in rings
  // max number of asteroids is about 10 - 15 000 per 1 GB RAM

    //inner ring
    #declare oBoundField = torus { 2100, 200 scale <1,0.1,1> rotate <-20, 0, -10> translate <400, 500, 100> hollow }
    //object { Bound_Field pigment { rgb <1.0, 0.2, 0.5> transmit 0.4} } //test
    #declare iMaxAsteroids = 2000;
    #declare rAster = seed(16524);
    //AsteroidField(fAsteroidRadius, cAsteroidColor, oBoundingObject, iMaxAsteroids, rAster)
    AsteroidField(4, rgb <0.6,0.6,0.6>, oBoundField, iMaxAsteroids, rAster)

    //outer ring
    #declare oBoundField = torus { 2670, 330 scale <1,0.1,1> rotate <-20, 0, -10> translate <400, 500, 100> hollow }
    #declare iMaxAsteroids = 3000;
    #declare rAster = seed(998165);
    //AsteroidField(fAsteroidRadius, cAsteroidColor, oBoundingObject, iMaxAsteroids, rAster)
    AsteroidField(4, rgb <0.6,0.6,0.6>, oBoundField, iMaxAsteroids, rAster)

#end //SCENE

// TEST ASTEROID TEXTURE
#if (SCENE_NUMBER = 4)
// camera preset
// texture asteroid
// sun

  //#declare fObjectRadius =  1.0; //0.500;
  Sun(<10000, 0, -10000>, 1)
  //Camera6() // texture
  Camera1(1.0) // cinema
  //DrawAsteroid()
  //Asteroid(iType, iSurface, fRadius, cBaseColor, rAsteroid)
  Asteroid(1.2, rgb <0.7,0.6,0.55>, seed(232+frame_number))

#end //SCENE

// TEXTURE OUTPUT
#if (SCENE_NUMBER = 3)

  //Sun(<10000, 0, -10000>)
  Sun(<10000, 10000, -10000>, 1)
  CameraTexture() //Camera6() // texture
  //Camera1(6366) // cinema
  #declare cBaseColor = rgb <0.82,0.92,0.60>;
  object { DirtPlanet1(6366, rgb <0.82,0.92,0.60>, 40, 0, seed(25)) }
  
#end //SCENE

// TEST 2
#if (SCENE_NUMBER = 2)
// camera preset
// texture planet
// sun

  Camera1(6366) // cinema
  Sun(<2000, 0, -100000>, 1)
  object { Planet(6366, EARTH_MAP, "") rotate <0, -60, 0> }

#end //SCENE

// SUN & GAS GIANT & FREE CAMERA
#if (SCENE_NUMBER = 1)
// free camera
// gas giant 4
// sun

  // syntax: Sun(vPosition, fIntensity)
  Sun(<2000, 0, -100000>, 1)

  // syntax: Camera(vPosition, vLookDirection, fCameraAngle)
  Camera(<0,0,-3000>, <0,200,0>, 45)
  //Camera1(1000)

  //gas giant
  #declare show = 1; #if (show) 
    #declare cSurfaceColor = rgb <0.82,0.52,0.20>;
    #declare bMonoColor = 0;
    #declare fColorDev = 20;
    GasGiant4(1000, cSurfaceColor, fColorDev, bMonoColor, seed(2345))
  #end

#end //SCENE

//EOF