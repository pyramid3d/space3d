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
// @file    : s3d_planet_terran.inc
// @brief   : Random planet surface generation
// @version : 2019-05-25
// @created : 2011-04-06
// @author  : pyramid
// @internet: https://openteq.wordpress.com/portfolio/space3d/
// @scale   : 1 POV unit = 1 km
// ---------------------------------------------------------------------------
// MACROS
//    TerranPlanet(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet)
//
// PARAMETER
// > fPlanetRadius  - planet radius
// > aBaseColors    - array with base colors; use array[1] {rgb <0,0,0>} for random colors
//                    or array[6] {...} for defined colors
//                    color sequence: Field,Forrest,Hill,Desert,Jungle,Ocean
// > fColorDev      - strength of color deviation
// > bMonoColor     - boolean for mono color daviation (=true) or hue change (=false)
// > aSeedNum       - array of planet seed numbers; use array[1] {s} for random seed,
//                    e.g.g array[1] {123}
//                    or array[7] {...} for defined structures with 
//                    numbers for seed sequence:
//                    rStructure,rTexture,rColor,rOcean,rIce,rRiver,rLight
//
// OBJECTS
//    TerranPlanet(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet)
//    TerranPlanet1(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet)
//    TerranPlanet2(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet)
//    TerranPlanet3(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet)
//    TerranPlanet4(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet)
//    TerranPlanet5(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet)
//    TerranPlanet6(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet)
//    TerranPlanet7(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet)
//    TerranPlanet8(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet)
//    TerranPlanetSelector(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet)
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
//#include "include/s3d_math.inc"
//#include "include/s3d_color.inc"

// ---------------------------------------------------------------------------
// Terran Planet Macro
// ---------------------------------------------------------------------------

//formerly planet_surface_type 22
#macro TerranPlanet(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aSeedNum)
  // Internal parameters: DRAW_ICE, NUM_RIVERS, NUM_LIGHTMAPS
  // ice, rivers, and lightmaps are drawn if the seed numbers are given
  // numbers for seed sequence: rStructure,rTexture,rColor,rOcean,rIce,rRiver,rLight

  // ---------------------------------------------------------------------------
  // User Settings
  // ---------------------------------------------------------------------------
  
  #local iSeedNum = dimension_size(aSeedNum,1);
  #declare rPlanet = seed(aSeedNum[0]);
  #if (iSeedNum>=1) #declare rStructure = seed(aSeedNum[0]); // terrain shape
  #else #declare rStructure = rPlanet; #end
  #if (iSeedNum>=2) #declare rTexture   = seed(aSeedNum[1]);
  #else #declare rTexture   = rPlanet;  #end // texture seed
  #if (iSeedNum>=3) #declare rColor     = seed(aSeedNum[2]);
  #else #declare rColor     = rPlanet;  #end // color seed
  #if (iSeedNum>=4) #declare rOcean     = seed(aSeedNum[3]);
  #else #declare rOcean     = rPlanet; #end // ocean texture seed

  #declare DRAW_ICE = 0; #declare rIce = seed(0);
  #if (iSeedNum>=5)
    #if (aSeedNum[4]>0)
      #declare rIce       = seed(aSeedNum[4]);
      #declare DRAW_ICE   = 1;
    #end
  #end // arctic ice texture seed

  #declare NUM_RIVERS = 0;
  #if (iSeedNum>=6)
    #if (aSeedNum[5]>0)
      #declare rRiver     = seed(aSeedNum[5]);
      #declare NUM_RIVERS = IRand(5,20,rRiver);
    #end
  #end // river seed

  #declare NUM_LIGHTMAPS = 0; // light seed
  #if (iSeedNum>=7)
    #if (aSeedNum[6]>0)
      #declare rLight        = seed(aSeedNum[6]);
      #declare NUM_LIGHTMAPS = IRand(3,10,rLight);
    #end
  #end

/*  
  #declare rStructure = rPlanet;
  #declare rTexture   = rPlanet;
  #declare rColor     = rPlanet;
  #declare rOcean     = rPlanet; // ocean texture seed
  #declare rIce       = rPlanet; // arctic ice texture seed
  #declare rRiver     = rPlanet;
  #declare rLight     = rPlanet;
*/
  
  // Internal parameters
  //#declare SURFACE_COLOR_SET = IRand(1,5,rPlanet);
  //#declare COLOR_REVISION = IRand(1,2,rPlanet);
  //#declare SURFACE_SHAPE_NUMBER = 3;
  //#declare SURFACE_TEXTURE_NUMBER = 1; //frame_number; //texture
  //#declare SURFACE_COLOR_NUMBER = 32; //frame_number; //color //27,32,34 
  //#declare OCEAN_TEXTURE_NUMBER = 12; //8,38; frame_number; //ocean //72
  //#declare NUM_RIVERS = IRand(5,20,rPlanet);
  //#declare NUM_LIGHTMAPS = IRand(3,10,rPlanet);
  #declare MAX_LANDSCAPE_ITERATION = IRand(10,20,rPlanet);
  #declare MAX_LANDSCAPE_ZONES = IRand(8,20,rPlanet);
  #declare MAX_CLIMATE_ZONES = IRand(8,20,rPlanet);
  #declare LANDSCAPE_ZONES = IRand(6,20,rPlanet);
  #declare LIGHT_BASE_COLOR = rgb <1, 1, 0.99>;
  #declare LANDSCAPE_ZONES = IRand(6,20,rPlanet);
  #declare SHALLOW_COASTLINE = IRand(0,1,rPlanet);

  // ---------------------------------------------------------------------------
  // Surface Colors and Pigments
  // ---------------------------------------------------------------------------
  // If first color is <0,0,0> then all colors will be randomized
  // Otherwise supplied colors will be used
  // Color sequence: Field,Forrest,Hill,Desert,Jungle,Ocean

  #declare fIntensity = 1.0; //RRand(0.9,1.1,rColor);
  #ifndef (LIGHT_BASE_COLOR) #declare cLightsBase = color rgb <1.0,1.0,0.2>; #else #declare cLightsBase = LIGHT_BASE_COLOR; #end

  GeneratePlanetColorSet(aBaseColors)

  // Below code was replaced by GeneratePlanetColorSet macro.
  //
/*  #if (iColNum>=1) //soil
    #declare Soil  = VariateColor(aBaseColors[0], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Soil  = VariateColor(rgb <0.2392, 0.1686, 0.0902>, fColorDev, bMonoColor, rPlanet);
  #end
  #if (iColNum>=2) //forrest
    #declare Forrest  = VariateColor(aBaseColors[1], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Forrest  = VariateColor(rgb <0.2627, 0.3098, 0.1451>, fColorDev, bMonoColor, rPlanet);
  #end
  #if (iColNum>=3) //hills
    #declare Hill  = VariateColor(aBaseColors[2], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Hill  = VariateColor(rgb <0.7020, 0.6588, 0.4824>, fColorDev, bMonoColor, rPlanet);
  #end
  #if (iColNum>=4) //desert
    #declare Desert  = VariateColor(aBaseColors[3], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Desert  = VariateColor(rgb <0.7020, 0.6588, 0.1224>, fColorDev, bMonoColor, rPlanet);
  #end
  #if (iColNum>=5) //ocean
    #declare Ocean  = VariateColor(aBaseColors[4], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Ocean  = VariateColor(rgb <0.1020, 0.1588, 0.9224>, fColorDev, bMonoColor, rPlanet);
  #end
*/

// Color Set
// ---------------------------------------------------------------------------
/*#if (COLOR_REVISION=1)
   // Greens
   #declare cGreen = array [30];
   #declare cGreen[0]  = color rgb <0.288, 0.687, 0.263>;
   #declare cGreen[1]  = color rgb <0.127, 0.976, 0.043>;
   #declare cGreen[2]  = color rgb <0.243, 0.588, 0.024>;
   #declare cGreen[3]  = color rgb <0.141, 0.840, 0.016>; //green forest
   #declare cGreen[4]  = color rgb <0.200, 0.478, 0.000>;
   #declare cGreen[5]  = color rgb <0.192, 0.541, 0.000>;
   #declare cGreen[6]  = color rgb <0.289, 0.588, 0.164>; //green grass
   #declare cGreen[7]  = color rgb <0.249, 0.435, 0.088>;
   #declare cGreen[8]  = color rgb <0.102, 0.302, 0.029>;
   #declare cGreen[9]  = color rgb <0.075, 0.465, 0.090>;
   #declare cGreen[10] = color rgb <0.118, 0.391, 0.073>;
   #declare cGreen[11] = color rgb <0.298, 0.710, 0.220>;
   #declare cGreen[12] = color rgb <0.263, 0.482, 0.196>;
   #declare cGreen[13] = color rgb <0.263, 0.455, 0.145>;
   #declare cGreen[14] = color rgb <0.212, 0.341, 0.024>;
   #declare cGreen[15] = color rgb <0.188, 0.286, 0.031>;
   #declare cGreen[16] = color rgb <0.153, 0.329, 0.100>;
   #declare cGreen[17] = color rgb <0.127, 0.251, 0.000>;
   #declare cGreen[18] = color rgb <0.000, 0.540, 0.000>; //very green
   #declare cGreen[19] = color rgb <0.329, 0.514, 0.208>;
   #declare cGreen[20] = color rgb <0.318, 0.391, 0.173>;
   #declare cGreen[21] = color rgb <0.298, 0.710, 0.220>;
   #declare cGreen[22] = color rgb <0.263, 0.482, 0.196>;
   #declare cGreen[23] = color rgb <0.263, 0.455, 0.145>;
   #declare cGreen[24] = color rgb <0.212, 0.341, 0.024>;
   #declare cGreen[25] = color rgb <0.188, 0.286, 0.031>;
   #declare cGreen[26] = color rgb <0.153, 0.329, 0.100>;
   #declare cGreen[27] = color rgb <0.127, 0.251, 0.000>;
   #declare cGreen[28] = color rgb <0.000, 0.540, 0.000>; //very green
   //Stone/Earth/Fields
   #declare cStone = array [30];
   #declare cStone[0]  = color rgb <0.188, 0.196, 0.163>;
   #declare cStone[1]  = color rgb <0.257, 0.241, 0.065>;
   #declare cStone[2]  = color rgb <0.154, 0.153, 0.029>;
   #declare cStone[3]  = color rgb <0.234, 0.233, 0.109>;
   #declare cStone[4]  = color rgb <0.194, 0.139, 0.055>;
   #declare cStone[5]  = color rgb <0.275, 0.184, 0.012>;
   #declare cStone[6]  = color rgb <0.316, 0.265, 0.092>;
   #declare cStone[7]  = color rgb <0.212, 0.173, 0.018>;
   #declare cStone[8]  = color rgb <0.108, 0.116, 0.031>;
   #declare cStone[9]  = color rgb <0.200, 0.190, 0.043>;
   #declare cStone[10] = color rgb <0.380, 0.310, 0.122>;
   #declare cStone[11] = color rgb <0.349, 0.357, 0.212>;
   #declare cStone[12] = color rgb <0.322, 0.235, 0.090>;
   #declare cStone[13] = color rgb <0.279, 0.178, 0.054>;
   #declare cStone[14] = color rgb <0.255, 0.235, 0.071>;
   #declare cStone[15] = color rgb <0.255, 0.200, 0.055>;
   #declare cStone[16] = color rgb <0.200, 0.184, 0.078>;
   #declare cStone[17] = color rgb <0.373, 0.341, 0.275>;
   #declare cStone[18] = color rgb <0.333, 0.310, 0.169>;
   #declare cStone[19] = color rgb <0.318, 0.329, 0.224>;
   #declare cStone[20] = color rgb <0.282, 0.302, 0.212>;
   #declare cStone[21] = color rgb <0.259, 0.224, 0.071>;
   #declare cStone[22] = color rgb <0.161, 0.165, 0.143>;
   #declare cStone[23] = color rgb <0.420, 0.402, 0.160>;
   #declare cStone[24] = color rgb <0.165, 0.141, 0.016>;
   //Sand
   #declare cSand = array [20];
   #declare cSand[0]  = color rgb <0.569, 0.375, 0.239>;
   #declare cSand[1]  = color rgb <0.494, 0.249, 0.178>;
   #declare cSand[2]  = color rgb <0.479, 0.278, 0.054>;
   #declare cSand[3]  = color rgb <0.465, 0.265, 0.140>;
   #declare cSand[4]  = color rgb <0.455, 0.306, 0.124>;
   #declare cSand[5]  = color rgb <0.450, 0.200, 0.100>;
   #declare cSand[6]  = color rgb <0.308, 0.167, 0.080>;
   #declare cSand[7]  = color rgb <0.388, 0.235, 0.063>;
   #declare cSand[8]  = color rgb <0.280, 0.175, 0.039>;
   #declare cSand[9]  = color rgb <0.461, 0.329, 0.139>;
   #declare cSand[10] = color rgb <0.322, 0.204, 0.110>;
   #declare cSand[11] = color rgb <0.369, 0.218, 0.092>;
   #declare cSand[12] = color rgb <0.206, 0.090, 0.008>;
   #declare cSand[13] = color rgb <0.249, 0.193, 0.084>;
   #declare cSand[14] = color rgb <0.241, 0.182, 0.053>;
   #declare cSand[15] = color rgb <0.190, 0.108, 0.002>;
   #declare cSand[16] = color rgb <0.104, 0.033, 0.004>;
#end // COLOR_REVISION=1

#if (COLOR_REVISION=2)
   // Greens
   #declare cGreen = array [30];
   #declare cGreen[0]  = color rgb <0.788, 0.987, 0.663>;
   #declare cGreen[1]  = color rgb <0.727, 0.976, 0.643>;
   #declare cGreen[2]  = color rgb <0.643, 0.788, 0.424>;
   #declare cGreen[3]  = color rgb <0.641, 0.840, 0.516>; //green forest
   #declare cGreen[4]  = color rgb <0.600, 0.678, 0.400>;
   #declare cGreen[5]  = color rgb <0.592, 0.741, 0.400>;
   #declare cGreen[6]  = color rgb <0.589, 0.788, 0.464>; //green grass
   #declare cGreen[7]  = color rgb <0.549, 0.635, 0.388>;
   #declare cGreen[8]  = color rgb <0.502, 0.702, 0.329>;
   #declare cGreen[9]  = color rgb <0.475, 0.565, 0.290>;
   #declare cGreen[10] = color rgb <0.472, 0.771, 0.447>; //green fade
   #declare cGreen[11] = color rgb <0.451, 0.573, 0.353>;
   #declare cGreen[12] = color rgb <0.420, 0.588, 0.224>;
   #declare cGreen[13] = color rgb <0.408, 0.627, 0.341>;
   #declare cGreen[14] = color rgb <0.404, 0.588, 0.212>;
   #declare cGreen[15] = color rgb <0.402, 0.808, 0.290>;
   #declare cGreen[16] = color rgb <0.388, 0.573, 0.259>;
   #declare cGreen[17] = color rgb <0.388, 0.498, 0.204>;
   #declare cGreen[18] = color rgb <0.369, 0.541, 0.208>;
   #declare cGreen[19] = color rgb <0.329, 0.514, 0.208>;
   #declare cGreen[20] = color rgb <0.318, 0.391, 0.173>;
   #declare cGreen[21] = color rgb <0.298, 0.710, 0.220>;
   #declare cGreen[22] = color rgb <0.263, 0.482, 0.196>;
   #declare cGreen[23] = color rgb <0.263, 0.455, 0.145>;
   #declare cGreen[24] = color rgb <0.212, 0.341, 0.024>;
   #declare cGreen[25] = color rgb <0.188, 0.286, 0.031>;
   #declare cGreen[26] = color rgb <0.153, 0.329, 0.100>;
   #declare cGreen[27] = color rgb <0.127, 0.251, 0.000>;
   #declare cGreen[28] = color rgb <0.000, 0.540, 0.000>; //very green
   //Stone/Erath/Fields
   #declare cStone = array [30];
   #declare cStone[0]  = color rgb <0.788, 0.696, 0.663>;
   #declare cStone[1]  = color rgb <0.757, 0.741, 0.565>;
   #declare cStone[2]  = color rgb <0.754, 0.653, 0.629>;
   #declare cStone[3]  = color rgb <0.734, 0.733, 0.609>;
   #declare cStone[4]  = color rgb <0.694, 0.639, 0.455>;
   #declare cStone[5]  = color rgb <0.675, 0.584, 0.412>;
   #declare cStone[6]  = color rgb <0.616, 0.565, 0.392>;
   #declare cStone[7]  = color rgb <0.612, 0.573, 0.518>;
   #declare cStone[8]  = color rgb <0.608, 0.616, 0.431>;
   #declare cStone[9]  = color rgb <0.600, 0.490, 0.443>;
   #declare cStone[10] = color rgb <0.580, 0.510, 0.322>;
   #declare cStone[11] = color rgb <0.549, 0.557, 0.412>;
   #declare cStone[12] = color rgb <0.522, 0.435, 0.290>;
   #declare cStone[13] = color rgb <0.479, 0.378, 0.254>;
   #declare cStone[14] = color rgb <0.455, 0.435, 0.271>;
   #declare cStone[15] = color rgb <0.455, 0.400, 0.255>;
   #declare cStone[16] = color rgb <0.400, 0.384, 0.278>;
   #declare cStone[17] = color rgb <0.373, 0.341, 0.275>;
   #declare cStone[18] = color rgb <0.333, 0.310, 0.169>;
   #declare cStone[19] = color rgb <0.318, 0.329, 0.224>;
   #declare cStone[20] = color rgb <0.282, 0.302, 0.212>;
   #declare cStone[21] = color rgb <0.259, 0.224, 0.071>;
   #declare cStone[22] = color rgb <0.161, 0.165, 0.143>;
   #declare cStone[23] = color rgb <0.420, 0.402, 0.360>;
   #declare cStone[24] = color rgb <0.165, 0.141, 0.016>;
   //Sand
   #declare cSand = array [20];
   #declare cSand[0]  = color rgb <0.969, 0.875, 0.839>;
   #declare cSand[1]  = color rgb <0.894, 0.749, 0.678>;
   #declare cSand[2]  = color rgb <0.879, 0.778, 0.454>;
   #declare cSand[3]  = color rgb <0.865, 0.765, 0.740>;
   #declare cSand[4]  = color rgb <0.855, 0.706, 0.624>;
   #declare cSand[5]  = color rgb <0.850, 0.600, 0.400>;
   #declare cSand[6]  = color rgb <0.808, 0.667, 0.580>;
   #declare cSand[7]  = color rgb <0.788, 0.635, 0.463>;
   #declare cSand[8]  = color rgb <0.780, 0.675, 0.639>;
   #declare cSand[9]  = color rgb <0.761, 0.629, 0.539>;
   #declare cSand[10] = color rgb <0.722, 0.604, 0.510>;
   #declare cSand[11] = color rgb <0.669, 0.518, 0.392>;
   #declare cSand[12] = color rgb <0.596, 0.490, 0.408>;
   #declare cSand[13] = color rgb <0.549, 0.443, 0.384>;
   #declare cSand[14] = color rgb <0.541, 0.412, 0.353>;
   #declare cSand[15] = color rgb <0.490, 0.408, 0.302>;
   #declare cSand[16] = color rgb <0.404, 0.333, 0.294>;
#end // COLOR_REVISION=2

#if (SURFACE_COLOR_SET>=5)
   #declare aBaseColors = array [150];
   #declare aBaseColors[0]  = color rgb <0.288, 0.687, 0.263>;
   #declare aBaseColors[1]  = color rgb <0.127, 0.976, 0.043>;
   #declare aBaseColors[2]  = color rgb <0.243, 0.588, 0.024>;
   #declare aBaseColors[3]  = color rgb <0.141, 0.840, 0.016>; //green forest
   #declare aBaseColors[4]  = color rgb <0.200, 0.478, 0.000>;
   #declare aBaseColors[5]  = color rgb <0.192, 0.541, 0.000>;
   #declare aBaseColors[6]  = color rgb <0.289, 0.588, 0.164>; //green grass
   #declare aBaseColors[7]  = color rgb <0.249, 0.435, 0.088>;
   #declare aBaseColors[8]  = color rgb <0.102, 0.302, 0.029>;
   #declare aBaseColors[9]  = color rgb <0.075, 0.465, 0.090>;
   #declare aBaseColors[10] = color rgb <0.118, 0.391, 0.073>;
   #declare aBaseColors[11] = color rgb <0.298, 0.710, 0.220>;
   #declare aBaseColors[12] = color rgb <0.263, 0.482, 0.196>;
   #declare aBaseColors[13] = color rgb <0.263, 0.455, 0.145>;
   #declare aBaseColors[14] = color rgb <0.212, 0.341, 0.024>;
   #declare aBaseColors[15] = color rgb <0.188, 0.286, 0.031>;
   #declare aBaseColors[16] = color rgb <0.153, 0.329, 0.100>;
   #declare aBaseColors[17] = color rgb <0.127, 0.251, 0.000>;
   #declare aBaseColors[18] = color rgb <0.000, 0.540, 0.000>; //very green
   #declare aBaseColors[19] = color rgb <0.329, 0.514, 0.208>;
   #declare aBaseColors[20] = color rgb <0.318, 0.391, 0.173>;
   #declare aBaseColors[21] = color rgb <0.298, 0.710, 0.220>;
   #declare aBaseColors[22] = color rgb <0.263, 0.482, 0.196>;
   #declare aBaseColors[23] = color rgb <0.263, 0.455, 0.145>;
   #declare aBaseColors[24] = color rgb <0.212, 0.341, 0.024>;
   #declare aBaseColors[25] = color rgb <0.188, 0.286, 0.031>;
   #declare aBaseColors[26] = color rgb <0.153, 0.329, 0.100>;
   #declare aBaseColors[27] = color rgb <0.127, 0.251, 0.000>;
   #declare aBaseColors[28] = color rgb <0.000, 0.540, 0.000>; //very green
   #declare aBaseColors[29]  = color rgb <0.200, 0.190, 0.043>;
   #declare aBaseColors[30]  = color rgb <0.188, 0.196, 0.163>;
   #declare aBaseColors[31]  = color rgb <0.257, 0.241, 0.065>;
   #declare aBaseColors[32]  = color rgb <0.154, 0.153, 0.029>;
   #declare aBaseColors[33]  = color rgb <0.234, 0.233, 0.109>;
   #declare aBaseColors[34]  = color rgb <0.194, 0.139, 0.055>;
   #declare aBaseColors[35]  = color rgb <0.275, 0.184, 0.012>;
   #declare aBaseColors[36]  = color rgb <0.316, 0.265, 0.092>;
   #declare aBaseColors[37]  = color rgb <0.212, 0.173, 0.018>;
   #declare aBaseColors[38]  = color rgb <0.108, 0.116, 0.031>;
   #declare aBaseColors[39] = color rgb <0.380, 0.310, 0.122>;
   #declare aBaseColors[40] = color rgb <0.165, 0.141, 0.016>;
   #declare aBaseColors[41] = color rgb <0.349, 0.357, 0.212>;
   #declare aBaseColors[42] = color rgb <0.322, 0.235, 0.090>;
   #declare aBaseColors[43] = color rgb <0.279, 0.178, 0.054>;
   #declare aBaseColors[44] = color rgb <0.255, 0.235, 0.071>;
   #declare aBaseColors[45] = color rgb <0.255, 0.200, 0.055>;
   #declare aBaseColors[46] = color rgb <0.200, 0.184, 0.078>;
   #declare aBaseColors[47] = color rgb <0.373, 0.341, 0.275>;
   #declare aBaseColors[48] = color rgb <0.333, 0.310, 0.169>;
   #declare aBaseColors[49] = color rgb <0.318, 0.329, 0.224>;
   #declare aBaseColors[50] = color rgb <0.282, 0.302, 0.212>;
   #declare aBaseColors[51] = color rgb <0.259, 0.224, 0.071>;
   #declare aBaseColors[52] = color rgb <0.161, 0.165, 0.143>;
   #declare aBaseColors[53] = color rgb <0.420, 0.402, 0.160>;
   #declare aBaseColors[54] = color rgb <0.369, 0.218, 0.092>;
   #declare aBaseColors[55] = color rgb <0.206, 0.090, 0.008>;
   #declare aBaseColors[56] = color rgb <0.249, 0.193, 0.084>;
   #declare aBaseColors[57] = color rgb <0.241, 0.182, 0.053>;
   #declare aBaseColors[58] = color rgb <0.190, 0.108, 0.002>;
   #declare aBaseColors[59] = color rgb <0.104, 0.033, 0.004>;
   #declare aBaseColors[60]  = color rgb <0.569, 0.375, 0.239>;
   #declare aBaseColors[61]  = color rgb <0.494, 0.249, 0.178>;
   #declare aBaseColors[62]  = color rgb <0.479, 0.278, 0.054>;
   #declare aBaseColors[63]  = color rgb <0.465, 0.265, 0.140>;
   #declare aBaseColors[64]  = color rgb <0.455, 0.306, 0.124>;
   #declare aBaseColors[65]  = color rgb <0.450, 0.200, 0.100>;
   #declare aBaseColors[66]  = color rgb <0.308, 0.167, 0.080>;
   #declare aBaseColors[67]  = color rgb <0.388, 0.235, 0.063>;
   #declare aBaseColors[68]  = color rgb <0.280, 0.175, 0.039>;
   #declare aBaseColors[69]  = color rgb <0.461, 0.329, 0.139>;
   #declare aBaseColors[70] = color rgb <0.322, 0.204, 0.110>;
   #declare aBaseColors[71]  = color rgb <0.727, 0.976, 0.643>;
   #declare aBaseColors[72]  = color rgb <0.643, 0.788, 0.424>;
   #declare aBaseColors[73]  = color rgb <0.641, 0.840, 0.516>; //green forest
   #declare aBaseColors[74]  = color rgb <0.600, 0.678, 0.400>;
   #declare aBaseColors[75]  = color rgb <0.592, 0.741, 0.400>;
   #declare aBaseColors[76]  = color rgb <0.589, 0.788, 0.464>; //green grass
   #declare aBaseColors[77]  = color rgb <0.549, 0.635, 0.388>;
   #declare aBaseColors[78]  = color rgb <0.502, 0.702, 0.329>;
   #declare aBaseColors[79]  = color rgb <0.475, 0.565, 0.290>;
   #declare aBaseColors[80] = color rgb <0.472, 0.771, 0.447>; //green fade
   #declare aBaseColors[81] = color rgb <0.451, 0.573, 0.353>;
   #declare aBaseColors[82] = color rgb <0.420, 0.588, 0.224>;
   #declare aBaseColors[83] = color rgb <0.408, 0.627, 0.341>;
   #declare aBaseColors[84] = color rgb <0.404, 0.588, 0.212>;
   #declare aBaseColors[85] = color rgb <0.402, 0.808, 0.290>;
   #declare aBaseColors[86] = color rgb <0.388, 0.573, 0.259>;
   #declare aBaseColors[87] = color rgb <0.388, 0.498, 0.204>;
   #declare aBaseColors[88] = color rgb <0.369, 0.541, 0.208>;
   #declare aBaseColors[89] = color rgb <0.329, 0.514, 0.208>;
   #declare aBaseColors[90] = color rgb <0.318, 0.391, 0.173>;
   #declare aBaseColors[91] = color rgb <0.298, 0.710, 0.220>;
   #declare aBaseColors[92] = color rgb <0.263, 0.482, 0.196>;
   #declare aBaseColors[93] = color rgb <0.263, 0.455, 0.145>;
   #declare aBaseColors[94] = color rgb <0.212, 0.341, 0.024>;
   #declare aBaseColors[95] = color rgb <0.188, 0.286, 0.031>;
   #declare aBaseColors[96] = color rgb <0.153, 0.329, 0.100>;
   #declare aBaseColors[97] = color rgb <0.127, 0.251, 0.000>;
   #declare aBaseColors[98] = color rgb <0.000, 0.540, 0.000>; //very green
   #declare aBaseColors[99]  = color rgb <0.788, 0.987, 0.663>;
   #declare aBaseColors[100]  = color rgb <0.788, 0.696, 0.663>;
   #declare aBaseColors[101]  = color rgb <0.757, 0.741, 0.565>;
   #declare aBaseColors[102]  = color rgb <0.754, 0.653, 0.629>;
   #declare aBaseColors[103]  = color rgb <0.734, 0.733, 0.609>;
   #declare aBaseColors[104]  = color rgb <0.694, 0.639, 0.455>;
   #declare aBaseColors[105]  = color rgb <0.675, 0.584, 0.412>;
   #declare aBaseColors[106]  = color rgb <0.616, 0.565, 0.392>;
   #declare aBaseColors[107]  = color rgb <0.612, 0.573, 0.518>;
   #declare aBaseColors[108]  = color rgb <0.608, 0.616, 0.431>;
   #declare aBaseColors[109]  = color rgb <0.600, 0.490, 0.443>;
   #declare aBaseColors[110] = color rgb <0.580, 0.510, 0.322>;
   #declare aBaseColors[111] = color rgb <0.549, 0.557, 0.412>;
   #declare aBaseColors[112] = color rgb <0.522, 0.435, 0.290>;
   #declare aBaseColors[113] = color rgb <0.479, 0.378, 0.254>;
   #declare aBaseColors[114] = color rgb <0.455, 0.435, 0.271>;
   #declare aBaseColors[115] = color rgb <0.455, 0.400, 0.255>;
   #declare aBaseColors[116] = color rgb <0.400, 0.384, 0.278>;
   #declare aBaseColors[117] = color rgb <0.373, 0.341, 0.275>;
   #declare aBaseColors[118] = color rgb <0.333, 0.310, 0.169>;
   #declare aBaseColors[119] = color rgb <0.318, 0.329, 0.224>;
   #declare aBaseColors[120] = color rgb <0.282, 0.302, 0.212>;
   #declare aBaseColors[121] = color rgb <0.259, 0.224, 0.071>;
   #declare aBaseColors[122] = color rgb <0.161, 0.165, 0.143>;
   #declare aBaseColors[123] = color rgb <0.420, 0.402, 0.360>;
   #declare aBaseColors[124] = color rgb <0.165, 0.141, 0.016>;
   #declare aBaseColors[125] = color rgb <0.596, 0.490, 0.408>;
   #declare aBaseColors[126] = color rgb <0.549, 0.443, 0.384>;
   #declare aBaseColors[127] = color rgb <0.541, 0.412, 0.353>;
   #declare aBaseColors[128] = color rgb <0.490, 0.408, 0.302>;
   #declare aBaseColors[129] = color rgb <0.404, 0.333, 0.294>;
   #declare aBaseColors[130]  = color rgb <0.969, 0.875, 0.839>;
   #declare aBaseColors[131]  = color rgb <0.894, 0.749, 0.678>;
   #declare aBaseColors[132]  = color rgb <0.879, 0.778, 0.454>;
   #declare aBaseColors[133]  = color rgb <0.865, 0.765, 0.740>;
   #declare aBaseColors[134]  = color rgb <0.855, 0.706, 0.624>;
   #declare aBaseColors[135]  = color rgb <0.850, 0.600, 0.400>;
   #declare aBaseColors[136]  = color rgb <0.808, 0.667, 0.580>;
   #declare aBaseColors[137]  = color rgb <0.788, 0.635, 0.463>;
   #declare aBaseColors[138]  = color rgb <0.780, 0.675, 0.639>;
   #declare aBaseColors[139]  = color rgb <0.761, 0.629, 0.539>;
   #declare aBaseColors[140] = color rgb <0.722, 0.604, 0.510>;
   #declare aBaseColors[141] = color rgb <0.669, 0.518, 0.392>;
#end

// Color Definitions
// ---------------------------------------------------------------------------
#if (SURFACE_COLOR_SET=1)
   //Soil
   #declare cSoil = array [10];
   #declare cSoil[0] = color rgb <0.934, 0.933, 0.609>; //brown light fields
   #declare cSoil[1] = color rgb <0.580, 0.510, 0.322>;
   #declare cSoil[2] = color rgb <0.612, 0.573, 0.518>;
   #declare cSoil[3] = color rgb <0.659, 0.324, 0.071>;
   #declare cSoil[4] = color rgb <0.675, 0.484, 0.412>;
   #declare cSoil[5] = color rgb <0.694, 0.639, 0.455>;
   #declare cSoil[6] = color rgb <0.455, 0.400, 0.255>;
   #declare cSoil[7] = color rgb <0.522, 0.435, 0.290>;
   #declare cSoil[8] = color rgb <0.865, 0.741, 0.316>;
   #declare cSoil[9] = color rgb <0.533, 0.310, 0.169>;
   // Forrest
   #declare cForrest = array [10];
   #declare cForrest[0] = color rgb <0.212, 0.341, 0.024>;
   #declare cForrest[1] = color rgb <0.127, 0.251, 0.000>;
   #declare cForrest[2] = color rgb <0.475, 0.565, 0.290>;
   #declare cForrest[3] = color rgb <0.388, 0.573, 0.259>;
   #declare cForrest[4] = color rgb <0.600, 0.678, 0.400>;
   #declare cForrest[5] = color rgb <0.153, 0.329, 0.000>;
   #declare cForrest[6] = color rgb <0.369, 0.541, 0.208>;
   #declare cForrest[7] = color rgb <0.408, 0.627, 0.341>;
   #declare cForrest[8] = color rgb <0.263, 0.482, 0.196>;
   #declare cForrest[9] = color rgb <0.188, 0.286, 0.031>;
   // Fields
   #declare cFields = array [10];
   #declare cFields[0] = color rgb <0.757, 0.741, 0.565>;
   #declare cFields[1] = color rgb <0.616, 0.565, 0.392>;
   #declare cFields[2] = color rgb <0.608, 0.616, 0.431>;
   #declare cFields[3] = color rgb <0.549, 0.557, 0.412>;
   #declare cFields[4] = color rgb <0.455, 0.435, 0.271>;
   #declare cFields[5] = color rgb <0.400, 0.384, 0.278>;
   #declare cFields[6] = color rgb <0.600, 0.490, 0.443>;
   #declare cFields[7] = color rgb <0.261, 0.165, 0.043>;
   #declare cFields[8] = color rgb <0.282, 0.302, 0.212>;
   #declare cFields[9] = color rgb <0.318, 0.229, 0.124>;
   // Desert
   #declare cDesert = array [10];
   #declare cDesert[0] = color rgb <0.961, 0.929, 0.839>;
   #declare cDesert[1] = color rgb <0.541, 0.412, 0.353>;
   #declare cDesert[2] = color rgb <0.855, 0.706, 0.624>;
   #declare cDesert[3] = color rgb <0.596, 0.490, 0.408>;
   #declare cDesert[4] = color rgb <0.404, 0.333, 0.294>;
   #declare cDesert[5] = color rgb <0.490, 0.408, 0.302>;
   #declare cDesert[6] = color rgb <0.894, 0.749, 0.678>;
   #declare cDesert[7] = color rgb <0.780, 0.675, 0.639>;
   #declare cDesert[8] = color rgb <0.969, 0.918, 0.792>;
   #declare cDesert[9] = color rgb <0.822, 0.604, 0.410>;
   // Jungle
   #declare cJungle = array [10];
   #declare cJungle[0] = color rgb <0.827, 0.976, 0.643>;
   #declare cJungle[1] = color rgb <0.702, 0.808, 0.490>;
   #declare cJungle[2] = color rgb <0.643, 0.788, 0.424>;
   #declare cJungle[3] = color rgb <0.592, 0.741, 0.400>;
   #declare cJungle[4] = color rgb <0.502, 0.702, 0.329>;
   #declare cJungle[5] = color rgb <0.404, 0.588, 0.212>;
   #declare cJungle[6] = color rgb <0.388, 0.498, 0.204>;
   #declare cJungle[7] = color rgb <0.329, 0.514, 0.208>;
   #declare cJungle[8] = color rgb <0.263, 0.455, 0.145>;
   #declare cJungle[9] = color rgb <0.298, 0.710, 0.220>;
#end //SURFACE_COLOR_SET=1

#if (SURFACE_COLOR_SET=2)
   //Soil
   #declare cSoil = array [10];
   #declare cSoil[0] = color rgb <0.934, 0.933, 0.609>; //brown light fields
   #declare cSoil[1] = color rgb <0.580, 0.510, 0.322>;
   #declare cSoil[2] = color rgb <0.612, 0.573, 0.518>;
   #declare cSoil[3] = color rgb <0.659, 0.324, 0.071>;
   #declare cSoil[4] = color rgb <0.675, 0.484, 0.412>;
   #declare cSoil[5] = color rgb <0.694, 0.639, 0.455>;
   #declare cSoil[6] = color rgb <0.455, 0.400, 0.255>;
   #declare cSoil[7] = color rgb <0.522, 0.435, 0.290>;
   #declare cSoil[8] = color rgb <0.865, 0.741, 0.316>;
   #declare cSoil[9] = color rgb <0.533, 0.310, 0.169>;
   // Forrest
   #declare cForrest = array [10];
   #declare cForrest[0] = color rgb <0.212, 0.341, 0.024>;
   #declare cForrest[1] = color rgb <0.127, 0.251, 0.000>;
   #declare cForrest[2] = color rgb <0.475, 0.565, 0.290>;
   #declare cForrest[3] = color rgb <0.388, 0.573, 0.259>;
   #declare cForrest[4] = color rgb <0.600, 0.678, 0.400>;
   #declare cForrest[5] = color rgb <0.153, 0.329, 0.000>;
   #declare cForrest[6] = color rgb <0.369, 0.541, 0.208>;
   #declare cForrest[7] = color rgb <0.408, 0.627, 0.341>;
   #declare cForrest[8] = color rgb <0.263, 0.482, 0.196>;
   #declare cForrest[9] = color rgb <0.188, 0.286, 0.031>;
   // Fields
   #declare cFields = array [10];
   #declare cFields[0] = color rgb <0.757, 0.741, 0.565>;
   #declare cFields[1] = color rgb <0.616, 0.565, 0.392>;
   #declare cFields[2] = color rgb <0.608, 0.616, 0.431>;
   #declare cFields[3] = color rgb <0.549, 0.557, 0.412>;
   #declare cFields[4] = color rgb <0.455, 0.435, 0.271>;
   #declare cFields[5] = color rgb <0.400, 0.384, 0.278>;
   #declare cFields[6] = color rgb <0.600, 0.490, 0.443>;
   #declare cFields[7] = color rgb <0.261, 0.165, 0.043>;
   #declare cFields[8] = color rgb <0.282, 0.302, 0.212>;
   #declare cFields[9] = color rgb <0.318, 0.229, 0.124>;
   // Desert
   #declare cDesert = array [10];
   #declare cDesert[0] = color rgb <0.961, 0.929, 0.839>;
   #declare cDesert[1] = color rgb <0.541, 0.412, 0.353>;
   #declare cDesert[2] = color rgb <0.855, 0.706, 0.624>;
   #declare cDesert[3] = color rgb <0.596, 0.490, 0.408>;
   #declare cDesert[4] = color rgb <0.404, 0.333, 0.294>;
   #declare cDesert[5] = color rgb <0.490, 0.408, 0.302>;
   #declare cDesert[6] = color rgb <0.894, 0.749, 0.678>;
   #declare cDesert[7] = color rgb <0.780, 0.675, 0.639>;
   #declare cDesert[8] = color rgb <0.969, 0.918, 0.792>;
   #declare cDesert[9] = color rgb <0.822, 0.604, 0.410>;
   // Jungle
   #declare cJungle = array [10];
   #declare cJungle[0] = color rgb <0.827, 0.976, 0.643>;
   #declare cJungle[1] = color rgb <0.702, 0.808, 0.490>;
   #declare cJungle[2] = color rgb <0.643, 0.788, 0.424>;
   #declare cJungle[3] = color rgb <0.592, 0.741, 0.400>;
   #declare cJungle[4] = color rgb <0.502, 0.702, 0.329>;
   #declare cJungle[5] = color rgb <0.404, 0.588, 0.212>;
   #declare cJungle[6] = color rgb <0.388, 0.498, 0.204>;
   #declare cJungle[7] = color rgb <0.329, 0.514, 0.208>;
   #declare cJungle[8] = color rgb <0.263, 0.455, 0.145>;
   #declare cJungle[9] = color rgb <0.298, 0.710, 0.220>;
   //Soil
   //#declare cSoil = array [10];
   #declare cBase = cSoil[IRand(0,9,rColor)];
   #local c=0; #while (c<10)
      #declare cBaseNew = VariateColor(cBase,fColorDev,bMonoColor,rColor);
      #declare cBaseR = cBaseNew.red;     
      #declare cBaseG = cBaseR - RRand(0.050,0.100,rColor);
      #declare cBaseB = cBaseG - RRand(0.100,0.200,rColor);
      #declare cSoil[c] = color rgb <cBaseR, cBaseG, cBaseB>;
   #local c=c+1; #end
   // Forest
   //#declare cForrest = array [10];
   #declare cBase = cForrest[IRand(0,9,rColor)];
   #local c=0; #while (c<10)
      #declare cBaseNew = VariateColor(cBase,fColorDev,bMonoColor,rColor);
      #declare cBaseG = cBaseNew.green;     
      #declare cBaseR = cBaseG - RRand(0.050,0.150,rColor);
      #declare cBaseB = cBaseG - RRand(0.100,0.200,rColor);
      #declare cForrest[c] = color rgb <cBaseR, cBaseG, cBaseB>;
   #local c=c+1; #end
   // Fields
   //#declare cFields = array [10];
   #declare cBase = cFields[IRand(0,9,rColor)];
   #local c=0; #while (c<10)
      #declare cBaseNew = VariateColor(cBase,fColorDev,bMonoColor,rColor);
      #declare cBaseR = cBaseNew.red;     
      #declare cBaseG = cBaseR - RRand(0.050,0.100,rColor);
      #declare cBaseB = cBaseG - RRand(0.050,0.150,rColor);
      #declare cFields[c] = color rgb <cBaseR, cBaseG, cBaseB>;
   #local c=c+1; #end
   // Desert
   //#declare cDesert = array [10];
   #declare cBase = cDesert[IRand(0,9,rColor)];
   #local c=0; #while (c<10)
      #declare cBaseNew = VariateColor(cBase,fColorDev,bMonoColor,rColor);
      #declare cBaseR = cBaseNew.red;     
      #declare cBaseG = cBaseR - RRand(0.050,0.150,rColor);
      #declare cBaseB = cBaseG - RRand(0.100,0.150,rColor);
      #declare cDesert[c] = color rgb <cBaseR, cBaseG, cBaseB>;
   #local c=c+1; #end
   // Jungle
   //#declare cJungle = array [10];
   #declare cBase = cJungle[IRand(0,9,rColor)];
   #local c=0; #while (c<10)
      #declare cBaseNew = VariateColor(cBase,fColorDev,bMonoColor,rColor);
      #declare cBaseG = cBaseNew.green;     
      #declare cBaseR = cBaseG - RRand(0.100,0.200,rColor);
      #declare cBaseB = cBaseG - RRand(0.150,0.300,rColor);
      #declare cJungle[c] = color rgb <cBaseR, cBaseG, cBaseB>;
   #local c=c+1; #end
#end //SURFACE_COLOR_SET=2

#if (SURFACE_COLOR_SET=3)
   #declare rIntensity = RRand(0.9,1.1,rColor);
   //Soil
   #declare cSoil = array [10];
   #declare cBase = cSand[IRand(0,16,rColor)]*rIntensity;
   #local c=0; #while (c<10)
      #declare cSoil[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
   #local c=c+1; #end
   
   // Forest
   #declare cForrest = array [10];
   #declare cBase = cGreen[IRand(0,28,rColor)]*rIntensity;
   #local c=0; #while (c<10)
      #declare cForrest[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
   #local c=c+1; #end

   // Fields
   #declare cFields = array [10];
   #declare cBase = cStone[IRand(0,24,rColor)]*rIntensity;
   #local c=0; #while (c<10)
      #declare cFields[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
   #local c=c+1; #end

   // Desert
   #declare cDesert = array [10];
   #declare cBase = cSand[IRand(0,16,rColor)]*rIntensity;
   #local c=0; #while (c<10)
      #declare cDesert[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
   #local c=c+1; #end

   // Jungle
   #declare cJungle = array [10];
   #declare cBase = cGreen[IRand(0,28,rColor)]*rIntensity;
   #local c=0; #while (c<10)
      #declare cJungle[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
   #local c=c+1; #end

#end //SURFACE_COLOR_SET=3

#if (SURFACE_COLOR_SET=4)
  #declare cBase = cGreen[IRand(0,dimension_size(cGreen,1)-1,rColor)];
  #declare local_color_deviation = RRand(0,20,rColor);
  //Soil
  #declare cSoil = array [10];
  #declare cBase = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=0; #while (c<10)
    #declare cSoil[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end
  
  // Forrest
  #declare cForrest = array [10];
  #declare cBase = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=0; #while (c<10)
    #declare cForrest[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end
  
  // Fields
  #declare cFields = array [10];
  #declare cBase = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=0; #while (c<10)
    #declare cFields[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end
  
  // Desert
  #declare cDesert = array [10];
  #declare cBase = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=0; #while (c<10)
    #declare cDesert[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end
  
  // Jungle
  #declare cJungle = array [10];
  #declare cBase = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=0; #while (c<10)
    #declare cJungle[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end
  
#end //SURFACE_COLOR_SET=4

#if (SURFACE_COLOR_SET>=5)
   //Soil
   #declare cSoil = array [10];
   #declare cBase = aBaseColors[IRand(0,141,rColor)];
   #local c=0; #while (c<10)
      #declare cSoil[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
   #local c=c+1; #end
   // Forest
   #declare cForrest = array [10];
   #declare cBase = aBaseColors[IRand(0,141,rColor)];
   #local c=0; #while (c<10)
      #declare cForrest[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
   #local c=c+1; #end
   // Fields
   #declare cFields = array [10];
   #declare cBase = aBaseColors[IRand(0,141,rColor)];
   #local c=0; #while (c<10)
      #declare cFields[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
   #local c=c+1; #end
   // Desert
   #declare cDesert = array [10];
   #declare cBase = aBaseColors[IRand(0,141,rColor)];
   #local c=0; #while (c<10)
      #declare cDesert[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
   #local c=c+1; #end
   // Jungle
   #declare cJungle = array [10];
   #declare cBase = aBaseColors[IRand(0,141,rColor)];
   #local c=0; #while (c<10)
      #declare cJungle[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
   #local c=c+1; #end
#end //SURFACE_COLOR_SET=5
*/

// ---------------------------------------------------------------------------
// Surface Pigments and Textures
// ---------------------------------------------------------------------------

// Base pigments
// ---------------------------------------------------------------------------
#declare P_SurfaceBase    = pigment { cSoil[IRand(0,9,rColor)] }
#declare P_OceanBase      = pigment { Ocean filter 1 }
#declare P_ArcticBase     = pigment { color rgb <1,1,1> filter 0 }
#declare P_BaseTrasparent = pigment { color rgb <1,1,1> filter 1 } //transparent

// Landscape Zones pigment macro
// ---------------------------------------------------------------------------
#macro mMicroStructure_Arid()
   #local fTurbulence = RRand(4.0, 7.0, rTexture);
   #local fPhase = RRand(0.20, 0.9, rTexture);
   #local fLambda = RRand(5.0,7.0,rTexture); // controls coastline
   #local fOmega = RRand(0.50,0.60,rTexture); // controls islands
   #local fScale = RRand(0.001, 0.01, rTexture);
   #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rTexture);
   #local iPattern = IRand(6, 12, rTexture);
   GetPattern(iPattern) 
   turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
   color_map {
      #local iZone  = IRand(1,3,rColor);
      #local iColor = IRand(0,9,rColor);
      #switch(iZone)
         #case (1) #declare cColor = cDesert[iColor];  #break
         #case (2) #declare cColor = cForrest[iColor]; #break
         #case (3) #declare cColor = cJungle[iColor];  #break
      #end
      #local I=0; #while(I<1)
         #local cPigmentColor = VariateColor(cColor,fColorDev,bMonoColor,rColor);
         [I cPigmentColor ]
      #local I=I+1/fSteps; #end
   } scale fScale*fPlanetRadius rotate <RRand(0,360,rTexture),RRand(0,360,rTexture),RRand(0,360,rTexture)> //}
#end //macro

#macro mMicroStructure_Mediterran()
   #local fTurbulence = RRand(4.0, 7.0, rTexture);
   #local fPhase = RRand(0.20, 0.9, rTexture);
   #local fLambda = RRand(4.0,10.0,rTexture); // controls coastline
   #local fOmega = RRand(0.50,0.70,rTexture); // controls islands
   #local fScale = RRand(0.001, 0.01, rTexture);
   #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rTexture);
   #local iPattern = IRand(6, 12, rTexture);
   GetPattern(iPattern) 
   turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
   color_map {
      #local iZone  = IRand(1,3,rColor);
      #local iColor = IRand(0,9,rColor);
      #switch(iZone)
        #case (1) #declare cColor = cForrest[iColor]; #break
        #case (2) #declare cColor = cSoil[iColor];    #break
        #case (3) #declare cColor = cHill[iColor];  #break
      #end
      #local I=0; #while(I<1)
         #local cPigmentColor = VariateColor(cColor,fColorDev,bMonoColor,rColor);
         [I cPigmentColor ]
      #local I=I+1/fSteps; #end
   } scale fScale*fPlanetRadius rotate <RRand(0,360,rTexture),RRand(0,360,rTexture),RRand(0,360,rTexture)> //}
#end //macro

#macro mMicroStructure_Moderate()
   #local fTurbulence = RRand(4.0, 7.0, rTexture);
   #local fPhase = RRand(0.20, 0.9, rTexture);
   #local fLambda = RRand(4.0,10.0,rTexture); // controls coastline
   #local fOmega = RRand(0.50,0.70,rTexture); // controls islands
   #local fScale = RRand(0.001, 0.01, rTexture);
   #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rTexture);
   #local iPattern = IRand(6, 12, rTexture);
   GetPattern(iPattern) 
   turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
   color_map {
      #local iZone  = IRand(1,3,rColor);
      #local iColor = IRand(0,9,rColor);
      #switch(iZone)
         #case (1) #declare cColor = cForrest[iColor]; #break
         #case (2) #declare cColor = cSoil[iColor];    #break
         #case (3) #declare cColor = cHill[iColor];  #break
      #end
      #local I=0; #while(I<1)
         #local cPigmentColor = VariateColor(cColor,fColorDev,bMonoColor,rColor);
         [I cPigmentColor ]
      #local I=I+1/fSteps; #end
   } scale fScale*fPlanetRadius rotate <RRand(0,360,rTexture),RRand(0,360,rTexture),RRand(0,360,rTexture)> //}
#end //macro

// Landscape Zones gradient (longitudonal)
// ---------------------------------------------------------------------------
#macro mArid()
   #local fSteps           = LANDSCAPE_ZONES; //RRand(MAX_LANDSCAPE_ZONES/2, MAX_LANDSCAPE_ZONES, rTexture);
   #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rTexture);
   #local fGradXTurbulence = RRand(2, 4, rTexture);
   #local fGradXOmega      = RRand(0.50, 0.60, rTexture);
   #local fGradXLambda     = RRand(3, 4, rTexture);
   #local fGradScale       = fPlanetRadius;
   #local fRotateX         = RRand(0,360,rTexture);
   #local fRotateY         = RRand(0,360,rTexture);
   #local fRotateZ         = RRand(0,360,rTexture);
   gradient x pigment_map {
      #local I=0; #while(I<1)
         #local P_MicroStructure_Arid = pigment { mMicroStructure_Arid() };
         //[I+fJitter P_MicroStructure_Arid ] 
         [min(1,I+1/fSteps-fJitter) P_MicroStructure_Arid ]
      #local I=I+1/fSteps; #end
   } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
   rotate <fRotateX, fRotateY, fRotateZ>
#end

#macro mMediterran()
   #local fSteps           = LANDSCAPE_ZONES; //RRand(MAX_LANDSCAPE_ZONES/2, MAX_LANDSCAPE_ZONES, rTexture);
   #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rTexture);
   #local fGradXTurbulence = RRand(2, 4, rTexture);
   #local fGradXOmega      = RRand(0.50, 0.60, rTexture);
   #local fGradXLambda     = RRand(3, 4, rTexture);
   #local fGradScale       = fPlanetRadius;
   #local fRotateX         = RRand(0,360,rTexture);
   #local fRotateY         = RRand(0,360,rTexture);
   #local fRotateZ         = RRand(0,360,rTexture);
   gradient x pigment_map {
      #local I=0; #while(I<1)
         #local P_MicroStructure_Mediterran = pigment { mMicroStructure_Mediterran() };
         //[I+fJitter P_MicroStructure_Mediterran ]
         [min(1,I+1/fSteps-fJitter) P_MicroStructure_Mediterran ]
      #local I=I+1/fSteps; #end
   } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
   rotate <fRotateX, fRotateY, fRotateZ>
#end

#macro mModerate()
   #local fSteps           = LANDSCAPE_ZONES; //RRand(MAX_LANDSCAPE_ZONES/2, MAX_LANDSCAPE_ZONES, rTexture);
   #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rTexture);
   #local fGradXTurbulence = RRand(2, 4, rTexture);
   #local fGradXOmega      = RRand(0.50, 0.60, rTexture);
   #local fGradXLambda     = RRand(3, 4, rTexture);
   #local fGradScale       = fPlanetRadius;
   #local fRotateX         = RRand(0,360,rTexture);
   #local fRotateY         = RRand(0,360,rTexture);
   #local fRotateZ         = RRand(0,360,rTexture);
   gradient x pigment_map {
      #local I=0; #while(I<1)
         #local P_MicroStructure_Moderate = pigment { mMicroStructure_Moderate() };
         //[I+fJitter P_MicroStructure_Moderate ]
         [min(1,I+1/fSteps-fJitter) P_MicroStructure_Moderate ]
      #local I=I+1/fSteps; #end
   } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
   rotate <fRotateX, fRotateY, fRotateZ>
#end

// Climate Zones gradient (latitudonal)
// ---------------------------------------------------------------------------
#declare fClimateZones    = LANDSCAPE_ZONES; //RRand(MAX_CLIMATE_ZONES/2, MAX_CLIMATE_ZONES, rTexture);
#declare fGradYTurbulence = RRand(0.02, 0.09, rTexture);
#declare fGradYOmega      = RRand(0.35, 0.55, rTexture);
#declare fGradYLambda     = RRand(3, 4, rTexture);
#declare fGradScale       = 2*fPlanetRadius;
#declare fJitter          = RRand(0.05,0.10,rTexture);
#declare P_SurfaceClimateGradient = pigment { gradient y pigment_map { //step 1/5=0.2; transition step/4=0.05
   #local I=0; #while(I<1)
      #local iZone  = IRand(1,3,rTexture);
      #switch(iZone)
         #case (1) #declare P_Surface = pigment { mModerate() };   #break
         #case (2) #declare P_Surface = pigment { mMediterran() }; #break
         #case (3) #declare P_Surface = pigment { mArid() };       #break
      #end
      //[I+fJitter P_Surface scale 1/fGradScale ]
      [min(1,I+1/fClimateZones-fJitter) P_Surface scale 1/fGradScale ]
   #local I=I+1/fClimateZones; #end
} turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda scale fGradScale phase 0.5 }

// Planet texture
// ---------------------------------------------------------------------------
#declare fSurfaceTurbulence = RRand(0.30, 0.90, rStructure); // complexity of continents
#declare fSurfaceOmega = RRand(0.30, 0.45, rStructure); // increses disconnected continents
#declare fSurfaceLambda = RRand(3.5, 6.5, rStructure); // increses coastline roughness
#declare fSurfacePhase = RRand(0.0, 0.4, rStructure); // different ocean shape
#declare fSurfacePercent = RRand(0.4, 0.8, rStructure); // approximate portion of land versus ocean
#declare fSurfaceScale = 0.5*fPlanetRadius;
#declare iSurfacePattern = IRand(4,18,rStructure); //4-18
#declare fSurfaceRotation = RRand(0, 360, rStructure);
#declare fRotateX = RRand(0,360,rStructure);
#declare fRotateY = RRand(0,360,rStructure);
#declare fRotateZ = RRand(0,360,rStructure);
#declare T_PlanetSurface = texture { pigment { //1-bozo; 2-bumps; 3-dents; 4-spotted; 5-wrinkles
   GetPattern(iSurfacePattern)
   pigment_map {
      [0.00 P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land ini
      [fSurfacePercent P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land end
      [fSurfacePercent transmit 1 ] //ocean ini
      [1.00 transmit 1 ] //ocean end
   }
turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }

#declare T_TestContinents = texture { pigment {
   GetPattern(iSurfacePattern)
   pigment_map {
      [0.00 P_SurfaceBase scale 1/fSurfaceScale ] //land ini
      [fSurfacePercent P_SurfaceBase scale 1/fSurfaceScale ] //land end
      [fSurfacePercent color rgb <0,0,0> ] //ocean ini
      [1.00 color rgb <0,0,0> ] //ocean end
   }
turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }

// Ocean texture
// ---------------------------------------------------------------------------
#declare ocean_base_color = Ocean*RRand(0.3,0.8,rOcean);

#declare fSteps      = RRand(3, 10, rOcean);
#declare fJitter     = RRand(1/fSteps/4,1/fSteps/3,rOcean);
#declare fTurbulence = RRand(1, 5, rOcean);
#declare fOmega      = RRand(0.30, 0.60, rOcean);
#declare fLambda     = RRand(3, 4, rOcean);
#declare fScale      = RRand(10, 50, rOcean);
#declare fColorDev   = RRand(0.1,4,rOcean);
#declare iPattern    = IRand(5, 17, rOcean); //6-bumps
#declare P_OceanTexture = pigment { //bumps
   GetPattern(iPattern)  
   color_map { 
   #local I=0; #while(I<1)
      #local cColor = surface_color_chromo(ocean_base_color,fColorDev,rOcean)*(1-I);
      [min(1,I) color cColor ]
   #local I=I+1/fSteps; #end
} turbulence fTurbulence omega fOmega lambda fLambda scale fScale*fPlanetRadius }

#declare T_OceanSurface = texture { pigment { GetPattern(iSurfacePattern)
   pigment_map {
      [0.00 transmit 1 ] //land ini
      [fSurfacePercent transmit 1 ] //land end
      [fSurfacePercent P_OceanTexture scale 1/fSurfaceScale ] //ocean ini
      [1.00 P_OceanTexture scale 1/fSurfaceScale ] //ocean end
   }
turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }

#declare fOceanDarkness = RRand(0.8, 1.0, rOcean);
#declare fSteps      = RRand(3, 10, rOcean);
#declare fJitter     = RRand(1/fSteps/4,1/fSteps/3,rOcean);
#declare fTurbulence = RRand(1, 5, rOcean);
#declare fOmega      = RRand(0.30, 0.60, rOcean);
#declare fLambda     = RRand(3, 4, rOcean);
#declare fScale      = RRand(10, 50, rOcean);
#declare iPattern    = IRand(5, 17, rOcean); //6-bumps
#declare P_OceanDarken = pigment { GetPattern(iPattern)  
   color_map { 
   #local I=0; #while(I<1)
      #local cColor = ocean_base_color*(1-I)*fOceanDarkness;
      [min(1,I) color cColor transmit RRand(0.5,1,rOcean)]
   #local I=I+1/fSteps; #end
} turbulence fTurbulence omega fOmega lambda fLambda scale fScale*fPlanetRadius }

#declare T_OceanDepth = texture { pigment {
   GetPattern(iSurfacePattern)
   pigment_map {
      [0.00 transmit 1 ] //land ini
      [fSurfacePercent transmit 1 ] //land end
      #if (SHALLOW_COASTLINE)
         [fSurfacePercent rgb ocean_base_color+<0,1.5,0.5> filter 0 transmit 0.5 scale 1/fSurfaceScale ] //coastline
         [fSurfacePercent+0.01 P_OceanDarken scale 1/fSurfaceScale ] //coastline
      #end
      [1.00 P_OceanDarken scale 1/fSurfaceScale ] //deep ocean
   }
turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }

// Arctic Pattern
// ---------------------------------------------------------------------------
#macro mMicroStructure_Arctic()
   #local fTurbulence = RRand(4.0, 7.0, rIce);
   #local fPhase      = RRand(0.20, 1.0, rIce);
   #local fLambda     = RRand(5.0,7.0,rIce); // controls coastline
   #local fOmega      = RRand(0.50,0.60,rIce); // controls islands
   #local fScale      = RRand(0.01, 0.1, rIce);
   #local fSteps      = RRand(20, 40, rIce);
   #local iPattern    = IRand(4, 18, rIce);
   #local fColorDev   = RRand(30,90,rIce);
   GetPattern(iPattern) 
   turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
   color_map {
      #local I=0; #while(I<1)
         #local vColor = color rgb <0.95, 0.95, 1.00>;
         #local cColor = surface_color_mono(vColor, fColorDev, rIce);
         [I cColor ]
      #local I=I+1/fSteps; #end
   } scale fScale*fPlanetRadius rotate <RRand(0,360,rIce),RRand(0,360,rIce),RRand(0,360,rIce)> //}
#end //macro

#macro mArctic()
   #local fSteps           = RRand(3, 5, rIce);
   #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rIce);
   #local fGradXTurbulence = RRand(0.10, 1.00, rIce);
   #local fGradXOmega      = RRand(0.45, 0.55, rIce);
   #local fGradXLambda     = RRand(3, 5, rIce);
   #local fGradScale       = fPlanetRadius;
   gradient x pigment_map {
      #local I=0; #while(I<1)
         #local P_MicroStructure_Arctic = pigment { mMicroStructure_Arctic() };
         [I+fJitter P_MicroStructure_Arctic ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Arctic ]
      #local I=I+1/fSteps; #end
   } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
#end

// Arctic texture
#declare fGradYTurbulence = RRand(0.01, 0.10, rIce);
#declare fGradYOmega      = RRand(0.35, 0.45, rIce);
#declare fGradYLambda     = RRand(4, 6, rIce);
#declare fArcticExtension = RRand(0.02 , 0.05, rIce);
#declare fGradScale       = 2.1*fPlanetRadius;
#declare T_ArcticTexture  = texture { pigment { gradient y pigment_map {
   #local P_Surface_Arctic  = pigment { mArctic() }
   [0.00 P_Surface_Arctic scale 1/fGradScale]                [fArcticExtension P_Surface_Arctic scale 1/fGradScale] //arctic
   [fArcticExtension   P_BaseTrasparent scale 1/fGradScale ] [1-fArcticExtension P_BaseTrasparent scale 1/fGradScale ] //transparent
   #local P_Surface_Arctic  = pigment { mArctic() }
   [1-fArcticExtension P_Surface_Arctic scale 1/fGradScale]  [1.00 P_Surface_Arctic scale 1/fGradScale] //arctic
} turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda scale fGradScale phase 0.5 }
finish { surface_finish } }

// River texture
// ---------------------------------------------------------------------------
#declare oRiver = sphere { 0, 1 } 

#macro mRiver(iSteps, fRiverRadius)
   #declare fAngularDistance = 360/((fPlanetRadius*2*pi)/(fRiverRadius/2));
   object { union {
      #local fAngleX = 0;
      #local fAngleY = 0;
      #local vDirectionUV = vnormalize(<RRand(-1,1,rRiver),RRand(-1,1,rRiver)>); //initial direction
	   #local fDirectionChangeMax = 1;
	   #local i=0; #while (i<iSteps/(fRiverRadius/50)) //river length
	      #if ( (render_quality=1) | ((render_quality=0) & (mod(i,2)=0)) ) //render samples only
	      //#else //render full
   	      #if (mod(i,10)=0) //change in river direction
               #local vDirectionUV = vnormalize(<vDirectionUV.u+RRand(0,fDirectionChangeMax,rRiver),vDirectionUV.v+RRand(0,fDirectionChangeMax,rRiver)>); //curvature
            #end
   	      #if (mod(i,50)=0) //change in river direction
               #local vDirectionUV = vnormalize(<vDirectionUV.u+RRand(-fDirectionChangeMax,fDirectionChangeMax,rRiver),vDirectionUV.v+RRand(-fDirectionChangeMax,fDirectionChangeMax,rRiver)>); //curvature
            #end
         #end //render samples
	      #local fJitter = RRand(0.5,1.0,rRiver); //irregularity
	      #local fAngleX = fAngleX+RRand(0.9,1.1,rRiver)*fAngularDistance*vDirectionUV.x*fJitter; //advancement
	      #local fAngleY = fAngleY+RRand(0.9,1.1,rRiver)*fAngularDistance*vDirectionUV.y*fJitter;
         object { oRiver scale fRiverRadius*RRand(0.1,1.5,rRiver) translate <0,0,fPlanetRadius> rotate <fAngleX, fAngleY, 0> }
      #local i=i+1; #end         
   }
   color rgb <0,0,0> transmit 1 // outside object = surface
   ocean_base_color transmit 0 // inside object = river
   } 
   #local fRotateX = RRand(-45,45,rRiver);
   #local fRotateY = RRand(-180,180,rRiver);
   #local fRotateZ = RRand(-180,180,rRiver);
   rotate fRotateZ*z rotate fRotateY*y rotate fRotateX*x //geographical position
#end //macro

#macro T_River()
   #local I=0; #while(I<NUM_RIVERS)
      #local iRiverLength = IRand(200,400,rRiver);
      #local fRiverWidth = RRand(10,30, rRiver); 
      #local P_River = pigment { mRiver(iRiverLength, fRiverWidth) };
      texture { pigment { P_River } finish { surface_finish } }
   #local I=I+1; #end
#end //macro

// Lights texture
// ---------------------------------------------------------------------------
#ifndef (LIGHT_BASE_COLOR) #declare cLightsBase = color rgb <1,1,0>; #else #declare cLightsBase = LIGHT_BASE_COLOR; #end

#macro mLightBase()
   #local fIntensity = RRand(10,30,rLight);
   #local fDensity = RRand(0.5,0.9,rLight);
   [0.0 transmit 1 ] // unlit area
   [fDensity cLightsBase*fIntensity ] // controls light density; 0.1 =high, 0.9=low
#end

#macro mLightmap(fExtension)
   #local fScale = RRand(20,40,rLight);
   #local iPattern = IRand(1, 20, rLight);
   [0.0 GetPattern(iPattern) pigment_map { mLightBase() } scale fScale turbulence 0]  // controls spread
   [fExtension rgb 0 transmit 1 ] // controls max lights extension; 0=no lights; 1=full lights
#end

#macro mLight()
   #local fPercent = RRand(0.5,0.6,rLight);
   #local fScale = RRand(0.01, 0.2, rLight);
   #local fExtension = RRand(0.01,0.3,rLight);
   #local iPattern = IRand(6, 12, rLight);
   #local fTurbulence = 0; //RRand(0.0, 7.0, rLight);
   #local fPhase = 0; //RRand(0.20, 0.90, rLight);
   #local fLambda = 0; //RRand(0.0,1.0,rLight); // controls coastline
   #local fOmega = 0; //RRand(0.00,0.30,rLight); // controls islands
   GetPattern(iPattern)
      pigment_map {
         [0.00 bozo pigment_map {mLightmap(fExtension)} scale 1/fSurfaceScale ] //lights ini
         [fPercent bozo pigment_map {mLightmap(fExtension/3)} scale 1/fSurfaceScale] //lights end
         [fPercent transmit 1 ] //ocean ini
         [1.00 transmit 1 ] //ocean end
      }
   turbulence fTurbulence omega fOmega lambda fLambda phase fPhase scale fScale*fPlanetRadius
   #local fRotateX = RRand(0,90,rLight);
   #local fRotateY = RRand(0,360,rLight);
   #local fRotateZ = RRand(0,360,rLight);
   rotate <fRotateX, fRotateY, fRotateZ> 
#end

#macro T_Lights() // non-transparent, not limited to continents
   #local I=0; #while(I<NUM_LIGHTMAPS)
      texture { pigment { mLight() } finish { surface_finish } }
   #local I=I+1; #end
#end //macro

#macro T_SurfaceLights() // transparent, limited to continents
   #local I=0; #while(I<NUM_LIGHTMAPS)
      texture { pigment {
      GetPattern(iSurfacePattern)
      #local P_SurfaceLights = pigment { mLight() };
      pigment_map {
         [0.00 P_SurfaceLights scale 1/fSurfaceScale ] //land ini
         [fSurfacePercent P_SurfaceLights scale 1/fSurfaceScale ] //land end
         [fSurfacePercent transmit 1 ] //ocean ini
         [1.00 transmit 1 ] //ocean end
      }
      turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
      rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }
   #local I=I+1; #end
#end

  // ---------------------------------------------------------------------------
  // Final Surface Texture Macro
  // ---------------------------------------------------------------------------
#declare debug_mode = -1; //0-custom; 1-planet; 2-lights

#macro mDebugSurface()
   #if (debug_mode=0) // just for debugging different things separately
      //#declare cColor = <RRand(0,1,rColor), RRand(0,1,rColor), RRand(0,1,rColor)>;
      //texture { pigment { color rgb <0.3,0.6,0.2> } finish { surface_finish } }
      //texture { pigment { cSoil[frame_number-1] } finish { surface_finish } }
      //texture { pigment { cForrest[frame_number-1] } finish { surface_finish } }
      //texture { pigment { cFields[frame_number-1] } finish { surface_finish } }
      //texture { pigment { cDesert[frame_number-1] } finish { surface_finish } }
      //texture { pigment { cJungle[frame_number-1] } finish { surface_finish } }
      //texture { pigment { P_OceanTexture } finish { surface_finish } }
      //texture { T_PlanetSurface }
      texture { T_TestContinents }
      //T_River()
      T_SurfaceLights()
      //texture { T_OceanSurface }
      //texture { T_OceanDepth }
   #end
   #if (debug_mode=1) // this is the real rendering, without lights
      texture { pigment { P_OceanTexture } finish { surface_finish } }
      texture { T_PlanetSurface }
      #if (NUM_RIVERS>0) T_River() #end
      T_SurfaceLights()
      texture { T_OceanSurface }
      texture { T_OceanDepth }
      #if (ice_shape_number>0 | frame_number=0) texture { T_ArcticTexture } #end
   #end
   #if (debug_mode=2) // rendering the lights only, use +UA to render transparent image
      T_SurfaceLights()
   #end //debug_mode
#end // planet_surface texture

  // ---------------------------------------------------------------------------
  // Final Surface Texture Macro
  // ---------------------------------------------------------------------------

  // Final Surface Texture Macro
  /*
  #macro mPlanetSurface()
    texture { pigment { P_OceanTexture } finish { surface_finish } }
    texture { T_PlanetSurface }
    texture { T_OceanSurface }
    texture { T_OceanDepth }
    //T_SurfaceLights()
    texture { T_ArcticTexture }
  #end // planet_surface texture
  */

  // Final Surface Texture Macro
  #macro mPlanetSurface()
    texture { pigment { P_OceanTexture } finish { surface_finish } }
    texture { T_PlanetSurface }
    #if (NUM_RIVERS!=0) T_River() #end
    texture { T_OceanSurface }
    texture { T_OceanDepth }
    #if (DRAW_ICE!=0) texture { T_ArcticTexture } #end
    #if (NUM_LIGHTMAPS!=0) T_SurfaceLights() #end
  #end // planet_surface texture
  
  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    finish { surface_finish }
    hollow on
    no_reflection
  }

  // ---------------------------------------------------------------------------
  // Debugging and Logging
  // ---------------------------------------------------------------------------

  #if (create_logfile)
     //#write(LogFile,"fExtension = ",fExtension,"\n")
     //#write(LogFile,"fScale = ",fScale,"\n")
     //#write(LogFile,"iPattern = ",iPattern,"\n")
     //#write(LogFile,"fTurbulence = ",fTurbulence,"\n")
     //#write(LogFile,"fOmega = ",fOmega,"\n")
     //#write(LogFile,"fLambda = ",fLambda,"\n")
     //#write(LogFile,"fPhase = ",fPhase,"\n")
     //#write(LogFile,"fPercent = ",fPercent,"\n")
  #end
  #if (create_logfile)
     //#write(LogFile,"fArcticExtension = ",fArcticExtension,"\n")
     //#write(LogFile,"fGradScale = ",fGradScale,"\n")
     //#write(LogFile,"iSurfacePattern = ",iSurfacePattern,"\n")
     //#write(LogFile,"fSurfaceTurbulence = ",fSurfaceTurbulence,"\n")
     //#write(LogFile,"fSurfaceOmega = ",fSurfaceOmega,"\n")
     //#write(LogFile,"fSurfaceLambda = ",fSurfaceLambda,"\n")
     //#write(LogFile,"fSurfacePhase = ",fSurfacePhase,"\n")
     //#write(LogFile,"fSurfacePercent = ",fSurfacePercent,"\n")
  #end
  #if (create_logfile)
     //#write(LogFile,"surface_base_color = ",vstr(3,cColor,", ",0,3),"\n")
     //#write(LogFile,"layers_number = ",layers_number,"\n")
     //#write(LogFile,"surface_base_color = ",vstr(3,surface_base_color,", ",0,2),"\n")
     //#write(LogFile,"surface_color_deviation = ",surface_color_deviation,"\n")
     //#write(LogFile,"color_mono_factor = ",color_mono_factor,"\n")
     //#write(LogFile,"detail_intensity = ",detail_intensity,"\n")
     //#write(LogFile,"edge = ",fEdge,"\n")
  #end

#end //planet

// ---------------------------------------------------------------------------
// Terran Planet Macros
// ---------------------------------------------------------------------------

#macro TerranPlanet1(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aSeedNum)
// Parameter
// > fPlanetRadius  - planet radius
// > aBaseColors    - array with base colors; use array[1] {rgb <0,0,0>} for random colors
//                    or array[6] {...} for defined colors
//                    color sequence: Field,Forrest,Hill,Desert,Jungle,Ocean
// > fColorDev      - strength of color deviation
// > bMonoColor     - boolean for mono color daviation (=true) or hue change (=false)
// > aSeedNum       - array of planet seed numbers; use array[1] {s} for random seed;
//                    or array[7] {...} for defined structures with 
//                    seed sequence: rStructure,rTexture,rColor,rOcean,rIce,rRiver,rLight

  // ---------------------------------------------------------------------------
  // User Settings
  // ---------------------------------------------------------------------------
  // Seed sequence: rStructure,rTexture,rColor,rOcean,rIce,rRiver,rLight
  
  #local iSeedNum = dimension_size(aSeedNum,1);
  #declare rPlanet = seed(aSeedNum[0]);
  #if (iSeedNum>=1) #declare rStructure = seed(aSeedNum[0]); // terrain shape
  #else #declare rStructure = rPlanet; #end
  #if (iSeedNum>=2) #declare rTexture   = seed(aSeedNum[1]);
  #else #declare rTexture   = rPlanet;  #end // texture seed
  #if (iSeedNum>=3) #declare rColor     = seed(aSeedNum[2]);
  #else #declare rColor     = rPlanet;  #end // color seed
  #if (iSeedNum>=4) #declare rOcean     = seed(aSeedNum[3]);
  #else #declare rOcean     = rPlanet; #end // ocean texture seed

  #declare DRAW_ICE = 0; #declare rIce = seed(0);
  #if (iSeedNum>=5)
    #if (aSeedNum[4]>0)
      #declare rIce       = seed(aSeedNum[4]);
      #declare DRAW_ICE   = 1;
    #end
  #end // arctic ice texture seed

  #declare NUM_RIVERS = 0;
  #if (iSeedNum>=6)
    #if (aSeedNum[5]>0)
      #declare rRiver     = seed(aSeedNum[5]);
      #declare NUM_RIVERS = IRand(5,20,rRiver);
    #end
  #end // river seed

  #declare NUM_LIGHTMAPS = 0; // light seed
  #if (iSeedNum>=7)
    #if (aSeedNum[6]>0)
      #declare rLight        = seed(aSeedNum[6]);
      #declare NUM_LIGHTMAPS = IRand(3,10,rLight);
    #end
  #end

  // ---------------------------------------------------------------------------
  // Surface Colors and Pigments
  // ---------------------------------------------------------------------------
  // If first color is <0,0,0> then all colors will be randomized
  // Otherwise supplied colors will be used
  // Color sequence: Field,Forrest,Hill,Desert,Jungle,Ocean

  #declare fIntensity = 1.0; //RRand(0.9,1.1,rColor);
  #ifndef (LIGHT_BASE_COLOR) #declare cLightsBase = color rgb <1.0,1.0,0.2>; #else #declare cLightsBase = LIGHT_BASE_COLOR; #end
  InitColors()

  #if (aBaseColors[0].red=0 & aBaseColors[0].green=0 & aBaseColors[0].blue=0)
    #local iColNum = 0;
  #else
    #local iColNum = dimension_size(aBaseColors,1);
  #end

  #declare iMinIntensity = 37; //min(dimension_size(cGreen,1),dimension_size(cStone,1),dimension_size(cSand,1)); 
  #declare iRelativeIntensity = IRand(0, iMinIntensity-1,rColor); 
  #declare cSoil = array [10]; #local c=0; #while (c<10)
    #if (iColNum>=1) //Soil
      #declare cBase  = VariateColor(aBaseColors[0], fColorDev, bMonoColor, rColor);
    #else
      #declare cBase = cStone[iRelativeIntensity]*fIntensity;
    #end
    #declare cSoil[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end

  #declare cForrest = array [10]; #local c=0; #while (c<10)
    #if (iColNum>=2) //Forrest
      #declare cBase  = VariateColor(aBaseColors[1], fColorDev, bMonoColor, rColor);
    #else
      #declare cBase = cGreen[iRelativeIntensity]*fIntensity;
    #end
    #declare cForrest[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end

  #declare cHill = array [10]; #local c=0; #while (c<10)
    #if (iColNum>=3) //Hills
      #declare cBase  = VariateColor(aBaseColors[2], fColorDev, bMonoColor, rColor);
    #else
      #declare cBase = cStone[iRelativeIntensity]*fIntensity;
    #end
    #declare cHill[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end

  #declare cDesert = array [10]; #local c=0; #while (c<10)
    #if (iColNum>=4) //Desert
      #declare cBase  = VariateColor(aBaseColors[3], fColorDev, bMonoColor, rColor);
    #else
      #declare cBase = cSand[iRelativeIntensity]*fIntensity;
    #end
    #declare cDesert[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end

  #declare cJungle = array [10]; #local c=0; #while (c<10)
    #if (iColNum>=5) //Jungle
      #declare cBase  = VariateColor(aBaseColors[4], fColorDev, bMonoColor, rColor);
    #else
      #declare cBase = cGreen[iRelativeIntensity]*fIntensity;
    #end
    #declare cJungle[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end

  #if (iColNum>=6) //Ocean
    #declare Ocean  = VariateColor(aBaseColors[5], fColorDev, bMonoColor, rOcean);
  #else
    #local cColor = cOcean[IRand(0,dimension_size(cOcean,1)-1,rOcean)];
    #declare Ocean  = VariateColor(cColor, fColorDev, bMonoColor, rOcean);
  #end

  // Base pigments
  // ---------------------------------------------------------------------------
  #declare P_SurfaceBase    = pigment { cSoil[IRand(0,9,rColor)] }
  #declare P_OceanBase      = pigment { Ocean filter 1 }
  #declare P_ArcticBase     = pigment { color rgb <1,1,1> filter 0 }
  #declare P_BaseTrasparent = pigment { color rgb <1,1,1> filter 1 } //transparent

  // ---------------------------------------------------------------------------
  // Surface Textures
  // ---------------------------------------------------------------------------
  // Declare default values
  #declare MAX_LANDSCAPE_ITERATION = IRand(4,10,rTexture);
  #declare LANDSCAPE_ZONES         = IRand(6,12,rTexture);
  
  // Landscape Zones pigment
  // ---------------------------------------------------------------------------
  #macro mMicroStructure()
    #local fTurbulence = RRand(2.0, 4.0, rTexture);
    #local fLambda     = RRand(6.0,7.0,rTexture); // controls coastline
    #local fOmega      = RRand(0.65,0.70,rTexture); // controls islands
    #local fScale      = RRand(1e-3, 1e-2, rTexture);
    #local fSteps      = MAX_LANDSCAPE_ITERATION;
    #local iPattern    = IRand(1,6,rTexture);
    GetPattern(iPattern) 
    turbulence fTurbulence lambda fLambda omega fOmega
    color_map {
      #local iZoneType = IRand(1,5,rTexture); // different climate zones
      #switch(iZoneType)
        #local iColor = IRand(0,9,rColor);
        #case (1) #declare cColor = cSoil[iColor];    #break
        #case (2) #declare cColor = cForrest[iColor]; #break
        #case (3) #declare cColor = cHill[iColor];    #break
        #case (4) #declare cColor = cDesert[iColor];  #break
        #case (5) #declare cColor = cJungle[iColor];  #break
      #end
      #local I=0; #while(I<=1)
        #local cPigmentColor = VariateColor(cColor,fColorDev,1,rColor);
        [I cPigmentColor ]
      #local I=I+1/fSteps; #end
    } scale fScale*fPlanetRadius
  #end //macro

  // Landscape Zones gradient (longitudonal)
  // ---------------------------------------------------------------------------
  #macro mZoneGradient(fTurb, fOmega, fLambda)
    #local fStep       = 0.67/LANDSCAPE_ZONES;
    #local fJitter     = fStep*RRand(0.010,0.020,rTexture); //defines the sharpness between landscape zones
    radial pigment_map {
      #local P_MicroStructure = pigment { mMicroStructure() };
      #local I=0; #while(I<=1)
        [min(1,I-fJitter) P_MicroStructure ]
        #local P_MicroStructure = pigment { mMicroStructure() };
        [min(1,I+fJitter) P_MicroStructure ]
      #local I=I+fStep; #end
    } turbulence fTurb omega fOmega lambda fLambda scale 2*fPlanetRadius phase 0.5
  #end

  // Climate Zones gradient (latitudonal)
  // ---------------------------------------------------------------------------
  #declare P_SurfaceClimateGradient = pigment { gradient y pigment_map {
    #declare fStep       = 0.5/LANDSCAPE_ZONES;
    #declare fJitter     = fStep*RRand(0.010,0.020,rTexture); //defines the sharpness between landscape zones
    #declare fTurbulence = RRand(0.30, 1.50, rTexture);
    #declare fOmega      = RRand(0.40, 0.65, rTexture);
    #declare fLambda     = RRand(2.1, 3.5, rTexture);
    #declare fGradScale  = 2*fPlanetRadius;
    #declare P_Surface = pigment { mZoneGradient(fTurbulence,fOmega,fLambda) };
    #local I=0; #while(I<=1)
      [min(1,I-fJitter) P_Surface scale 1/fGradScale ]
      #declare P_Surface = pigment { mZoneGradient(fTurbulence,fOmega,fLambda) };
      [min(1,I+fJitter) P_Surface scale 1/fGradScale ]
    #local I=I+fStep; #end
  } turbulence fTurbulence omega fOmega lambda fLambda scale fGradScale phase 0.5 }

  // Planet texture
  // ---------------------------------------------------------------------------
  // defaults: lambda=2.0; omega=0.5; turbulence=0.0; phase=0.0;
  #declare fSurfaceTurbulence = RRand(0.30, 1.50, rTexture); // complexity
  #declare fSurfaceOmega      = RRand(0.45, 0.65, rTexture); // increses islands
  #declare fSurfaceLambda     = RRand(2.1, 3.5, rTexture); // coastline roughness
  #declare fSurfaceScale      = 0.5*fPlanetRadius;
  #declare T_PlanetSurface    = texture { pigment {
    GetPattern(6)
    pigment_map {
      [0.00 P_SurfaceClimateGradient scale 1/fSurfaceScale ]
      [1.00 P_SurfaceClimateGradient scale 1/fSurfaceScale ]
    }
  turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda scale fSurfaceScale
   } finish { surface_finish } }

  // Ocean texture
  // ---------------------------------------------------------------------------
  #declare fSurfaceTurbulence = RRand(0.30, 0.90, rStructure); // complexity of continents
  #declare fSurfaceOmega      = RRand(0.40, 0.65, rStructure); // increses disconnected continents
  #declare fSurfaceLambda     = RRand(3.5, 6.5, rStructure); // increses coastline roughness
  #declare fSurfacePhase      = RRand(0.0, 0.4, rStructure); // different ocean shape
  #declare fSurfacePercent    = RRand(0.4, 0.8, rStructure); // approximate portion of land versus ocean
  #declare fSurfaceScale      = 0.5*fPlanetRadius;
  #declare iSurfacePattern    = IRand(1,6,rStructure);
  #declare fRotateX           = RRand(0,360,rStructure);
  #declare fRotateY           = RRand(0,360,rStructure);
  #declare fRotateZ           = RRand(0,360,rStructure);

  #declare fSteps      = RRand(3, 10, rOcean);
  #declare fJitter     = RRand(1/fSteps/4,1/fSteps/3,rOcean);
  #declare fTurbulence = RRand(1, 5, rOcean);
  #declare fOmega      = RRand(0.30, 0.60, rOcean);
  #declare fLambda     = RRand(3, 4, rOcean);
  #declare fScale      = RRand(10, 50, rOcean);
  #declare fColorDev   = RRand(0.1,4,rOcean);
  #declare iPattern    = IRand(5, 17, rOcean); //6-bumps
  #declare P_OceanTexture = pigment { //bumps
    GetPattern(iPattern)  
    color_map { 
    #local I=0; #while(I<=1)
      #local cColor = VariateColor(Ocean,RRand(1,10,rOcean),0,rOcean)*(1-I*0.2);
      [min(1,I) color cColor ]
    #local I=I+1/fSteps; #end
  } turbulence fTurbulence omega fOmega lambda fLambda scale fScale*fPlanetRadius }
  
  #declare T_OceanSurface = texture { pigment { GetPattern(iSurfacePattern)
    pigment_map {
      [0.00 transmit 1 scale 1/fSurfaceScale ] //land ini
      [fSurfacePercent transmit 1 scale 1/fSurfaceScale ] //land end
      [fSurfacePercent P_OceanTexture scale 1/fSurfaceScale ] //ocean ini
      [1.00 P_OceanTexture scale 1/fSurfaceScale ] //ocean end
    }
  turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
  rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }

  #declare fOceanDarkness = RRand(0.8, 1.0, rOcean);
  #declare fSteps         = RRand(3, 10, rOcean);
  #declare fJitter        = RRand(1/fSteps/4,1/fSteps/3,rOcean);
  #declare fTurbulence    = RRand(1, 5, rOcean);
  #declare fOmega         = RRand(0.30, 0.60, rOcean);
  #declare fLambda        = RRand(3, 4, rOcean);
  #declare fScale         = RRand(10, 50, rOcean);
  #declare iPattern       = IRand(5, 17, rOcean); //6-bumps
  #declare P_OceanDarken = pigment { GetPattern(iPattern)  
     color_map { 
     #local I=0; #while(I<1)
        #local cColor = Ocean*(1-I)*fOceanDarkness;
        [min(1,I) color cColor transmit RRand(0.5,1,rOcean)]
     #local I=I+1/fSteps; #end
  } turbulence fTurbulence omega fOmega lambda fLambda scale fScale*fPlanetRadius }
  
  #declare SHALLOW_COASTLINE = IRand(0,1,rOcean);
  #declare T_OceanDepth = texture { pigment {
    GetPattern(iSurfacePattern)
    pigment_map {
      [0.00 transmit 1 ] //land ini
      [fSurfacePercent transmit 1 ] //land end
      #if (SHALLOW_COASTLINE)
        [fSurfacePercent Ocean+<0,1.5,0.5> filter 0 transmit 0.5 scale 1/fSurfaceScale ] //coastline
        [fSurfacePercent+0.01 P_OceanDarken scale 1/fSurfaceScale ] //coastline
      #end
      [1.00 P_OceanDarken scale 1/fSurfaceScale ] //deep ocean
    }
  turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
  rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }

  // Arctic Pattern
  // ---------------------------------------------------------------------------
  #macro mMicroStructure_Arctic()
     #local fTurbulence = RRand(4.0, 7.0, rIce);
     #local fPhase      = RRand(0.20, 1.0, rIce);
     #local fLambda     = RRand(5.0,7.0,rIce); // controls coastline
     #local fOmega      = RRand(0.50,0.60,rIce); // controls islands
     #local fScale      = RRand(0.01, 0.1, rIce);
     #local fSteps      = RRand(20, 40, rIce);
     #local iPattern    = IRand(4, 18, rIce);
     #local fColorDev   = RRand(30,90,rIce);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           #local vColor = color rgb <0.95, 0.95, 1.00>;
           #local cColor = VariateColor(vColor, fColorDev, 1, rIce);
           [I cColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius rotate <RRand(0,360,rIce),RRand(0,360,rIce),RRand(0,360,rIce)> //}
  #end //macro
  
  #macro mArctic()
     #local fSteps           = RRand(3, 5, rIce);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rIce);
     #local fGradXTurbulence = RRand(0.10, 1.00, rIce);
     #local fGradXOmega      = RRand(0.45, 0.55, rIce);
     #local fGradXLambda     = RRand(3, 5, rIce);
     #local fGradScale       = fPlanetRadius;
     gradient x pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Arctic = pigment { mMicroStructure_Arctic() };
           [I+fJitter P_MicroStructure_Arctic ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Arctic ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
  #end
  
  // Arctic texture
  #declare fGradYTurbulence = RRand(0.05, 0.20, rIce);
  #declare fGradYOmega      = RRand(0.35, 0.45, rIce);
  #declare fGradYLambda     = RRand(4, 6, rIce);
  #declare fArcticExtension = RRand(0.05 , 0.25, rIce);
  #declare fGradScale       = 2.1*fPlanetRadius;
  #declare T_ArcticTexture  = texture { pigment { gradient y pigment_map {
     #local P_Surface_Arctic  = pigment { mArctic() }
     [0.00 P_Surface_Arctic scale 1/fGradScale]                [fArcticExtension P_Surface_Arctic scale 1/fGradScale] //arctic
     [fArcticExtension   P_BaseTrasparent scale 1/fGradScale ] [1-fArcticExtension P_BaseTrasparent scale 1/fGradScale ] //transparent
     #local P_Surface_Arctic  = pigment { mArctic() }
     [1-fArcticExtension P_Surface_Arctic scale 1/fGradScale]  [1.00 P_Surface_Arctic scale 1/fGradScale] //arctic
  } turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda scale fGradScale phase 0.5 }
  finish { surface_finish } }

  // River texture
  // ---------------------------------------------------------------------------
  #declare oRiver = sphere { 0, 1 } 
  
  #macro mRiver(iSteps, fRiverRadius) //pigment
    #declare fAngularDistance = 360/((fPlanetRadius*2*pi)/(fRiverRadius/2));
    object { union {
      #local fAngleX = 0;
      #local fAngleY = 0;
      #local vDirectionUV = vnormalize(<RRand(-1,1,rRiver),RRand(-1,1,rRiver)>); //initial direction
      #local fDirectionChangeMax = 1;
      #local i=0; #while (i<iSteps/(fRiverRadius/50)) //river length
        #if ( (render_quality=1) | ((render_quality=0) & (mod(i,2)=0)) ) //render samples only
        //#else //render full
          #if (mod(i,10)=0) //change in river direction
             #local vDirectionUV = vnormalize(<vDirectionUV.u+RRand(0,fDirectionChangeMax,rRiver),vDirectionUV.v+RRand(0,fDirectionChangeMax,rRiver)>); //curvature
          #end
          #if (mod(i,50)=0) //change in river direction
             #local vDirectionUV = vnormalize(<vDirectionUV.u+RRand(-fDirectionChangeMax,fDirectionChangeMax,rRiver),vDirectionUV.v+RRand(-fDirectionChangeMax,fDirectionChangeMax,rRiver)>); //curvature
          #end
        #end //render samples
        #local fJitter = RRand(0.5,1.0,rRiver); //irregularity
        #local fAngleX = fAngleX+RRand(0.9,1.1,rRiver)*fAngularDistance*vDirectionUV.x*fJitter; //advancement
        #local fAngleY = fAngleY+RRand(0.9,1.1,rRiver)*fAngularDistance*vDirectionUV.y*fJitter;
          object { oRiver scale fRiverRadius*RRand(0.1,1.5,rRiver) translate <0,0,fPlanetRadius> rotate <fAngleX, fAngleY, 0> }
      #local i=i+1; #end         
    }
    color rgb <0,0,0> transmit 1 // outside object = surface
    Ocean transmit 0 // inside object = river
    } 
    #local fRotateX = RRand(-45,45,rRiver);
    #local fRotateY = RRand(-180,180,rRiver);
    #local fRotateZ = RRand(-180,180,rRiver);
    rotate fRotateZ*z rotate fRotateY*y rotate fRotateX*x //geographical position
  #end //macro

  #macro T_River()
    #local I=0; #while(I<NUM_RIVERS)
      #local iRiverLength = IRand(200,400,rRiver);
      #local fRiverWidth = RRand(10,30, rRiver); 
      #local P_River = pigment { mRiver(iRiverLength, fRiverWidth) };
      texture { pigment { P_River } finish { surface_finish } }
    #local I=I+1; #end
  #end //macro

  // Lights texture
  // ---------------------------------------------------------------------------
  
  #macro mLightBase()
    #local fIntensity = RRand(10,30,rLight);
    #local fDensity = RRand(0.1,0.5,rLight); //light density; 0.1 =high, 0.9=low
    [0.0 transmit 1 ] // unlit area
    [fDensity cLightsBase*fIntensity ]
  #end
  
  #macro mLightmap(fExtension)
    #local fScale = RRand(20,40,rLight);
    #local iPattern = IRand(1, 20, rLight);
    [0.0 GetPattern(iPattern) pigment_map { mLightBase() } scale fScale turbulence 0]  // controls spread
    [fExtension rgb 0 transmit 1 ] // controls max lights extension; 0=no lights; 1=full lights
  #end

  #macro mLight() // pigment
    #local fPercent    = RRand(0.5,0.6,rLight);
    #local fScale      = RRand(0.01, 0.2, rLight);
    #local fExtension  = RRand(0.30,0.40,rLight);
    #local iPattern    = IRand(6, 12, rLight);
    #local fTurbulence = 0;
    #local fPhase      = 0;
    #local fLambda     = 0; // controls coastline
    #local fOmega      = 0; // controls islands
    GetPattern(iPattern)
      pigment_map {
        [0.00 bozo pigment_map {mLightmap(fExtension)} scale 1/fSurfaceScale ] //lights ini
        [fPercent bozo pigment_map {mLightmap(fExtension/3)} scale 1/fSurfaceScale] //lights end
        [fPercent transmit 1 ] //ocean ini
        [1.00 transmit 1 ] //ocean end
      }
    turbulence fTurbulence omega fOmega lambda fLambda phase fPhase scale fScale*fPlanetRadius
    #local fRotateX = RRand(0,90,rLight);
    #local fRotateY = RRand(0,360,rLight);
    #local fRotateZ = RRand(0,360,rLight);
    rotate <fRotateX, fRotateY, fRotateZ> 
  #end

  //macro T_LightsTest() // non-transparent, not limited to continents
  //  #local I=0; #while(I<NUM_LIGHTMAPS)
  //    texture { pigment { mLight() } finish { surface_finish } }
  //  #local I=I+1; #end
  //#end //macro
  
  #macro T_SurfaceFullLights() // transparent, limited to continents
    #local I=0; #while(I<NUM_LIGHTMAPS)
      texture { pigment {
        GetPattern(iSurfacePattern)
        #local P_SurfaceLights = pigment { mLight() };
        pigment_map {
          [0.00 P_SurfaceLights scale 1/fSurfaceScale ] //land ini
          [fSurfacePercent P_SurfaceLights scale 1/fSurfaceScale ] //land end
          [fSurfacePercent transmit 1 ] //ocean ini
          [1.00 transmit 1 ] //ocean end
        }
        turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
        //rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }
      rotate <fRotateX, fRotateY, fRotateZ> } finish { ambient 1 diffuse 0 } }
    #local I=I+1; #end
  #end //macro

  #macro T_SurfaceUnlitLights() // transparent, limited to continents and shadow side (opposite sunside)
    #local I=0; #while(I<NUM_LIGHTMAPS)
      texture { 
        #declare P_Lights = pigment {
          GetPattern(iSurfacePattern)
          #local P_SurfaceLights = pigment { mLight() };
          pigment_map {
            [0.00 P_SurfaceLights scale 1/fSurfaceScale ] //land ini
            [fSurfacePercent P_SurfaceLights scale 1/fSurfaceScale ] //land end
            [fSurfacePercent transmit 1 ] //ocean ini
            [1.00 transmit 1 ] //ocean end
          }
          turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
        } //end pigment
        pigment { slope vSunPosition
          pigment_map {
            [0.00 P_Lights ] // opposite to sun
            [0.50 P_Lights ] // perpendicular to sun
            [0.55 rgbt 1 ] // perpendicular to sun
            [1.00 rgbt 1 ] // facing the sun
          }
      rotate <fRotateX, fRotateY, fRotateZ> } finish { ambient 1 diffuse 0 } }
    #local I=I+1; #end
  #end //macro

  #macro T_SurfaceLights()
    #ifndef (vSunPosition)
      T_SurfaceFullLights()
    #else
      T_SurfaceUnlitLights()
    #end
  #end //macro

  // ---------------------------------------------------------------------------
  // Final Surface Texture Macro
  // ---------------------------------------------------------------------------

  // Final Surface Texture Macro
  #macro mPlanetSurface()
    texture { T_PlanetSurface }
    #if (NUM_RIVERS!=0) T_River() #end
    texture { T_OceanSurface }
    texture { T_OceanDepth }
    #if (DRAW_ICE!=0) texture { T_ArcticTexture } #end
    #if (NUM_LIGHTMAPS!=0) T_SurfaceLights() #end
  #end // planet_surface texture
  
  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    finish { surface_finish }
    hollow no
    no_reflection
  }

  // ---------------------------------------------------------------------------
  // Debugging and Logging
  // ---------------------------------------------------------------------------
  #if (create_logfile)
    //#write(LogFile,"fExtension = ",fExtension,"\n")
    //#write(LogFile,"surface_base_color = ",vstr(3,cColor,", ",0,3),"\n")
  #end
  
#end //TerranPlanet1 macro

// ---------------------------------------------------------------------------
// Terran Planet Macro
// ---------------------------------------------------------------------------

//M-Class planet
#macro TerranPlanet2(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aSeedNum)

  #local iSeedNum = dimension_size(aSeedNum,1);
  #declare rPlanet = seed(aSeedNum[0]);
  #if (iSeedNum>=1) #declare rStructure = seed(aSeedNum[0]); // terrain shape
  #else #declare rStructure = rPlanet; #end
  #if (iSeedNum>=2) #declare rTexture   = seed(aSeedNum[1]);
  #else #declare rTexture   = rPlanet;  #end // texture seed
  #if (iSeedNum>=3) #declare rColor     = seed(aSeedNum[2]);
  #else #declare rColor     = rPlanet;  #end // color seed
  #if (iSeedNum>=4) #declare rOcean     = seed(aSeedNum[3]);
  #else #declare rOcean     = rPlanet; #end // ocean texture seed

  #declare DRAW_ICE = 0; #declare rIce = seed(0);
  #if (iSeedNum>=5)
    #if (aSeedNum[4]>0)
      #declare rIce       = seed(aSeedNum[4]);
      #declare DRAW_ICE   = 1;
    #end
  #end // arctic ice texture seed

  #declare NUM_RIVERS = 0;
  #if (iSeedNum>=6)
    #if (aSeedNum[5]>0)
      #declare rRiver     = seed(aSeedNum[5]);
      #declare NUM_RIVERS = IRand(5,20,rRiver);
    #end
  #end // river seed

  #declare NUM_LIGHTMAPS = 0; // light seed
  #if (iSeedNum>=7)
    #if (aSeedNum[6]>0)
      #declare rLight        = seed(aSeedNum[6]);
      #declare NUM_LIGHTMAPS = IRand(3,10,rLight);
    #end
  #end
  
  #if (aBaseColors[0].red=0 & aBaseColors[0].green=0 & aBaseColors[0].blue=0)
    #local iColNum = 0;
  #else
    #local iColNum = dimension_size(aBaseColors,1);
  #end

  #if (iColNum>=1)
    #declare Crest  = VariateColor(aBaseColors[0], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Crest  = VariateColor(rgb <0.2392, 0.1686, 0.0902>, fColorDev, bMonoColor, rPlanet);
  #end
  #if (iColNum>=2)
    #declare Hill  = VariateColor(aBaseColors[1], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Hill  = VariateColor(rgb <0.4824, 0.5098, 0.2510>, fColorDev, bMonoColor, rPlanet);
  #end
  #if (iColNum>=3)
    #declare Valley  = VariateColor(aBaseColors[2], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Valley  = VariateColor(rgb <0.7020, 0.6588, 0.4824>, fColorDev, bMonoColor, rPlanet);
  #end

  #declare T_LandBase = texture {  // land base
    pigment { bozo
       #declare fEdge = 0.0;
       #declare fTurbulence = RRand(1.0, 5.0, rPlanet);
       #declare fPhase = 0;
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
       #declare fScale = RRand(0.2,0.4,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
       color_map {
          [0.0  color Crest ]
          [0.08 color Hill ]
          [0.5  color Valley ]
          [0.9 color Hill ]
          [1.0  color Crest ]
       }
    }
    scale fScale*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
  }
  
  #declare iTextureSteps = 5;
  #declare T_Soil = texture {  // different soil 
    pigment { bozo
       #declare fEdge = 0.0;
       #declare fTurbulence = RRand(0.5, 5.0, rPlanet);
       #declare fPhase = 0;
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
       #declare fScale = RRand(0.05,0.4,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
       color_map {
          #local I=0; #while(I<=2/iTextureSteps)
             #declare cColor = VariateColor(Valley, fColorDev, bMonoColor, rPlanet);
             [I/iTextureSteps color cColor filter RRand(0.35,0.40,rPlanet)]
          #local I=I+1; #end
          [0.4 color rgbf <1, 1, 1, 1> ]
          [0.6 color rgbf <1, 1, 1, 1> ]
          #local I=4/iTextureSteps; #while(I<=iTextureSteps)
             #declare cColor = VariateColor(Crest, fColorDev, bMonoColor, rPlanet);
             [I/iTextureSteps color cColor filter RRand(0.35,0.40,rPlanet)]
          #local I=I+1; #end
      }
    }
    scale fScale*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
  } 
  
  #declare iTextureSteps = 40;
  #declare T_Forest = texture {  // greesnish forests
    pigment { gradient y
       #declare fEdge = 0.0;
       #declare fTurbulence = RRand(3.0, 8.0, rPlanet);
       #declare fPhase = 0;
       #declare fLambda = RRand(3.0,5.0,rPlanet); // controls graininess
       #declare fOmega = RRand(0.45,0.60,rPlanet); // controls fineness complexity
       #declare fScale = RRand(0.0005,0.002,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
       color_map {
          #local I=0; #while(I<0.40)
             #declare cColor = VariateColor(Valley, fColorDev, bMonoColor, rPlanet);
             [I color cColor filter RRand(0.35,0.40,rPlanet)]
          #local I=I+1/iTextureSteps; #end
          [0.4  color rgbf <1,1,1,1> ]
          [1.0  color rgbf <1,1,1,1> ]
       }
    }
    scale fScale*<1,1.2,1>*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
  }
  
  #declare T_Ocean = texture {  // water on surface
    pigment { bozo
       #declare fEdge = 0.0;
       #declare fTurbulence = RRand(1.8, 2.5, rPlanet);
       #declare fPhase = RRand(0.3,0.6,rPlanet);
       #declare fLambda = RRand(1.9,2.8,rPlanet); // controls coastline
       #declare fOmega = RRand(0.50,0.60,rPlanet); // controls islands
       #declare fScale = RRand(0.7,1.0,rPlanet);
       turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
       color_map {
          [0.0  color rgbf <0.17, 0.21, 0.47, 0> ]  // deep ocean 
          [0.1  color rgbf <0.18, 0.22, 0.48, 0> ]
          [0.58 color rgbf <0.21, 0.25, 0.60, 0> ]  // flat ocean
          [0.58 color rgbf <1, 1, 1, 1> ] // land ini
          [1.0  color rgbf <1, 1, 1, 1> ] // land end
       }
    }
    scale fScale*<1,1.2,1>*fPlanetRadius
    rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)>
  }

  sphere {<0, 0, 0>, fPlanetRadius
    texture { T_LandBase }
    texture { T_Soil }
    texture { T_Forest }
    texture { T_Ocean }
    finish { surface_finish }
    hollow on
    no_reflection
  }
#end

// ---------------------------------------------------------------------------------------

#macro TerranPlanet3(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aSeedNum)

  #local iSeedNum = dimension_size(aSeedNum,1);
  #declare rPlanet = seed(aSeedNum[0]);
  #if (iSeedNum>=1) #declare rStructure = seed(aSeedNum[0]); // terrain shape
  #else #declare rStructure = rPlanet; #end
  #if (iSeedNum>=2) #declare rTexture   = seed(aSeedNum[1]);
  #else #declare rTexture   = rPlanet;  #end // texture seed
  #if (iSeedNum>=3) #declare rColor     = seed(aSeedNum[2]);
  #else #declare rColor     = rPlanet;  #end // color seed
  #if (iSeedNum>=4) #declare rOcean     = seed(aSeedNum[3]);
  #else #declare rOcean     = rPlanet; #end // ocean texture seed

  #declare DRAW_ICE = 0; #declare rIce = seed(0);
  #if (iSeedNum>=5)
    #if (aSeedNum[4]>0)
      #declare rIce       = seed(aSeedNum[4]);
      #declare DRAW_ICE   = 1;
    #end
  #end // arctic ice texture seed

  #declare NUM_RIVERS = 0;
  #if (iSeedNum>=6)
    #if (aSeedNum[5]>0)
      #declare rRiver     = seed(aSeedNum[5]);
      #declare NUM_RIVERS = IRand(5,20,rRiver);
    #end
  #end // river seed

  #declare NUM_LIGHTMAPS = 0; // light seed
  #if (iSeedNum>=7)
    #if (aSeedNum[6]>0)
      #declare rLight        = seed(aSeedNum[6]);
      #declare NUM_LIGHTMAPS = IRand(3,10,rLight);
    #end
  #end
  
  #declare planet_texture_base = texture {
    pigment { bumps
       color_map {
          #local pigm_max = 1.00;
          #local I=0; #while(I<=pigm_max)            
             #local pigm_delta = RRand(-fColorDev/255,fColorDev/255,rPlanet);
             [I color rgb <(205/255)+pigm_delta, (180/255)+pigm_delta, (140/255)+pigm_delta> ] 
          #local I=I+0.05; #end
          }
    turbulence RRand(0.2, 0.4, rPlanet) //0.3
    scale 0.9*fPlanetRadius //0.5
    }
    finish { surface_finish }
  }
  #declare planet_texture_soil = texture {
    pigment { bumps
      color_map {
          #local pigm_max = 0.60;
          #local I=0; #while(I<=pigm_max)            
             #local pigm_delta = RRand(-fColorDev/255,fColorDev/255,rPlanet);
             [I color rgb <(180/255)+pigm_delta, (120/255)+pigm_delta, (70/255)+pigm_delta> transmit RRand(0.4,0.7,rPlanet) ] 
          #local I=I+0.025; #end
          [pigm_max  color rgbf <1,1,1,1> ]
          [1.0  color rgbf <1,1,1,1> ]
      }
      frequency 1
      turbulence  RRand(3, 5, rPlanet) //4
      phase RRand(0.0, 0.2, rPlanet)
      lambda RRand(2, 4, rPlanet)
      omega RRand(0.5, 0.7, rPlanet) //0.7
      scale 0.4*<1,1.2,1>*fPlanetRadius
    }
    finish { surface_finish }
  }
  #declare planet_texture_forest = texture {
    pigment { bumps
      color_map {
          [0.00 color rgbf <1, 1, 1, 1> ]
          [0.60 color rgbf <1, 1, 1, 1> ]
          #local pigm_max = 1.0;
          #local I=0.60; #while(I<=pigm_max)            
             #local pigm_delta = RRand(-fColorDev/255,fColorDev/255,rPlanet);
             [I color rgb <(67/255)+pigm_delta, (79/255)+pigm_delta, (37/255)+pigm_delta> filter 1 ] 
          #local I=I+0.05; #end
       }
    frequency 1
    turbulence  RRand(0.4, 0.6, rPlanet) //0.5
    phase 0.05
    lambda RRand(2, 4, rPlanet)
    omega RRand(0.5, 0.7, rPlanet) //0.7
    scale 0.12*fPlanetRadius
    }
    finish { surface_finish }
  } 
  #declare planet_texture_water = texture {
    pigment { bozo
       color_map {
          #local pigm_max = 0.60;
          #local I=0; #while(I<=pigm_max)            
             [I color rgb <RRand(0/255,10/255,rPlanet), RRand(10/255,30/255,rPlanet), RRand(180/255,255/255,rPlanet)> filter 0 ]
          #local I=I+0.10; #end
          [0.60 color rgbf <1, 1, 1, 1> ] // land ini
          [1.00  color rgbf <1, 1, 1, 1> ] // land end
       }
    omega RRand(0.55, 0.65, rPlanet)
    turbulence RRand(0.45, 0.65, rPlanet)
    lambda RRand(1.1, 3.65, rPlanet)
    omega RRand(0.5, 0.7, rPlanet) //0.7
    phase 0.1
    scale 0.4*fPlanetRadius
    }
    finish { surface_finish brilliance 2.2 }
  }

  sphere {<0, 0, 0>, fPlanetRadius
    texture {planet_texture_base}
    texture {planet_texture_soil}
    texture {planet_texture_forest}
    texture {planet_texture_water}
    finish { surface_finish }
    hollow on
    no_reflection
  }

#end //planet macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 8
#macro TerranPlanet4(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aSeedNum)

  #local iSeedNum = dimension_size(aSeedNum,1);
  #declare rPlanet = seed(aSeedNum[0]);
  #if (iSeedNum>=1) #declare rStructure = seed(aSeedNum[0]); // terrain shape
  #else #declare rStructure = rPlanet; #end
  #if (iSeedNum>=2) #declare rTexture   = seed(aSeedNum[1]);
  #else #declare rTexture   = rPlanet;  #end // texture seed
  #if (iSeedNum>=3) #declare rColor     = seed(aSeedNum[2]);
  #else #declare rColor     = rPlanet;  #end // color seed
  #if (iSeedNum>=4) #declare rOcean     = seed(aSeedNum[3]);
  #else #declare rOcean     = rPlanet; #end // ocean texture seed

  #declare DRAW_ICE = 0; #declare rIce = seed(0);
  #if (iSeedNum>=5)
    #if (aSeedNum[4]>0)
      #declare rIce       = seed(aSeedNum[4]);
      #declare DRAW_ICE   = 1;
    #end
  #end // arctic ice texture seed

  #declare NUM_RIVERS = 0;
  #if (iSeedNum>=6)
    #if (aSeedNum[5]>0)
      #declare rRiver     = seed(aSeedNum[5]);
      #declare NUM_RIVERS = IRand(5,20,rRiver);
    #end
  #end // river seed

  #declare NUM_LIGHTMAPS = 0; // light seed
  #if (iSeedNum>=7)
    #if (aSeedNum[6]>0)
      #declare rLight        = seed(aSeedNum[6]);
      #declare NUM_LIGHTMAPS = IRand(3,10,rLight);
    #end
  #end

  InitColors()

  #if (aBaseColors[0].red=0 & aBaseColors[0].green=0 & aBaseColors[0].blue=0)
    #local iColNum = 0;
  #else
    #local iColNum = dimension_size(aBaseColors,1);
  #end
  
  #declare rColor = rPlanet;
  #if (iColNum>=1) //soil
    #declare Soil  = VariateColor(aBaseColors[0], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Soil = cSand[IRand(0,dimension_size(cSand,1)-1,rColor)];
  #end
  #if (iColNum>=2) //forrest
    #declare Forrest  = VariateColor(aBaseColors[1], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Forrest = cGreen[IRand(0,dimension_size(cGreen,1)-1,rColor)];
  #end
  #if (iColNum>=3) //fields
    #declare Field  = VariateColor(aBaseColors[2], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Field = cStone[IRand(0,dimension_size(cStone,1)-1,rColor)];
  #end
  #if (iColNum>=4) //desert
    #declare Desert  = VariateColor(aBaseColors[3], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Desert = cSand[IRand(0,dimension_size(cSand,1)-1,rColor)];
  #end
  #if (iColNum>=5) //Jungle
    #declare Jungle  = VariateColor(aBaseColors[4], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Jungle = cGreen[IRand(0,dimension_size(cGreen,1)-1,rColor)];
  #end

  #declare planet_texture_base = texture { pigment { wrinkles
    pigment_map {
      #local I=0; #while(I<=1.0)            
        [I VariateColor(Soil, fColorDev, bMonoColor, rPlanet) ] 
      #local I=I+RRand(0.05,0.05,rPlanet); #end //0.15
      }
    turbulence RRand(0.9,3.0,rPlanet)
    scale <RRand(0.05,0.20,rPlanet),RRand(0.05,0.20,rPlanet),RRand(0.05,0.20,rPlanet)>*fPlanetRadius
    } finish { surface_finish }
  }

  #declare planet_texture_soil = texture { pigment { bozo
    pigment_map {
      #local I=0; #while(I<=0.40)            
        [I VariateColor(Desert, fColorDev, bMonoColor, rPlanet) ] 
      #local I=I+RRand(0.005,0.025,rPlanet); #end //0.025
      [0.4  color rgbf <1,1,1,1> ]
      [1.0  color rgbf <1,1,1,1> ]
      }
    omega RRand(0.4, 0.7, rPlanet)
    turbulence RRand(2,7,rPlanet)
    phase RRand(0.0, 0.2, rPlanet)
    frequency 1
    scale <RRand(0.1,0.5,rPlanet),RRand(0.1,0.6,rPlanet),RRand(0.1,0.5,rPlanet)>*fPlanetRadius //0.5
    } finish { surface_finish }
  }

  #declare planet_texture_forrest = texture { pigment { bumps
    pigment_map {
      [0.00 color rgbf <1, 1, 1, 1> ]
      [0.60 color rgbf <1, 1, 1, 1> ]
      #local I=0.60; #while(I<=1.0)            
        [I VariateColor(Forrest, fColorDev, bMonoColor, rPlanet) ] 
      #local I=I+RRand(0.01,0.10,rPlanet); #end
      }
    frequency RRand(0.5, 2.0, rPlanet)
    turbulence RRand(0.3, 0.9, rPlanet)
    phase RRand(0.05, 0.2, rPlanet)
    omega RRand(0.6, 0.75, rPlanet)
    scale 0.12*fPlanetRadius
    } finish { surface_finish }
  } 
  #declare planet_texture_water = texture { pigment { bozo
    color_map {
      #local I=0; #while(I<=0.60)            
         [I rgb <RRand(0/255,10/255,rPlanet), RRand(10/255,30/255,rPlanet), RRand(180/255,255/255,rPlanet)> filter 0 ]
      #local I=I+RRand(0.1,0.1,rPlanet); #end
      [0.60 color rgbf <1, 1, 1, 1> ] // land ini
      [1.00  color rgbf <1, 1, 1, 1> ] // land end
    }
    turbulence RRand(0.5, 1.9, rPlanet)
    omega RRand(0.50, 0.65, rPlanet)
    lambda RRand(1.5, 2.65, rPlanet)
    phase RRand(0.1, 0.6, rPlanet)
    scale 0.4*fPlanetRadius
    } finish { surface_finish brilliance 2.2 }
  }

  sphere {<0, 0, 0>, fPlanetRadius
    texture {planet_texture_base}
    texture {planet_texture_soil}
    texture {planet_texture_forrest}
    texture {planet_texture_water}
    finish { surface_finish }
    hollow on
    no_reflection
  }

#end //terran planet macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 10
#macro TerranPlanet5(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aSeedNum)

  #local iSeedNum = dimension_size(aSeedNum,1);
  #declare rPlanet = seed(aSeedNum[0]);
  #if (iSeedNum>=1) #declare rStructure = seed(aSeedNum[0]); // terrain shape
  #else #declare rStructure = rPlanet; #end
  #if (iSeedNum>=2) #declare rTexture   = seed(aSeedNum[1]);
  #else #declare rTexture   = rPlanet;  #end // texture seed
  #if (iSeedNum>=3) #declare rColor     = seed(aSeedNum[2]);
  #else #declare rColor     = rPlanet;  #end // color seed
  #if (iSeedNum>=4) #declare rOcean     = seed(aSeedNum[3]);
  #else #declare rOcean     = rPlanet; #end // ocean texture seed

  #declare DRAW_ICE = 0; #declare rIce = seed(0);
  #if (iSeedNum>=5)
    #if (aSeedNum[4]>0)
      #declare rIce       = seed(aSeedNum[4]);
      #declare DRAW_ICE   = 1;
    #end
  #end // arctic ice texture seed

  #declare NUM_RIVERS = 0;
  #if (iSeedNum>=6)
    #if (aSeedNum[5]>0)
      #declare rRiver     = seed(aSeedNum[5]);
      #declare NUM_RIVERS = IRand(5,20,rRiver);
    #end
  #end // river seed

  #declare NUM_LIGHTMAPS = 0; // light seed
  #if (iSeedNum>=7)
    #if (aSeedNum[6]>0)
      #declare rLight        = seed(aSeedNum[6]);
      #declare NUM_LIGHTMAPS = IRand(3,10,rLight);
    #end
  #end

  InitColors()

  #if (aBaseColors[0].red=0 & aBaseColors[0].green=0 & aBaseColors[0].blue=0)
    #local iColNum = 0;
  #else
    #local iColNum = dimension_size(aBaseColors,1);
  #end

  #if (iColNum>=1) //soil
    #declare Soil  = VariateColor(aBaseColors[0], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Soil  = VariateColor(rgb <0.2392, 0.1686, 0.0902>, fColorDev, bMonoColor, rPlanet);
  #end
  #if (iColNum>=2) //forrest
    #declare Forrest  = VariateColor(aBaseColors[1], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Forrest  = VariateColor(rgb <0.2627, 0.3098, 0.1451>, fColorDev, bMonoColor, rPlanet);
  #end
  #if (iColNum>=3) //hills
    #declare Hill  = VariateColor(aBaseColors[2], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Hill  = VariateColor(rgb <0.7020, 0.6588, 0.4824>, fColorDev, bMonoColor, rPlanet);
  #end
  #if (iColNum>=4) //desert
    #declare Desert  = VariateColor(aBaseColors[3], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Desert  = VariateColor(rgb <0.7020, 0.6588, 0.1224>, fColorDev, bMonoColor, rPlanet);
  #end
  #if (iColNum>=5) //ocean
    #declare Ocean  = VariateColor(aBaseColors[4], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Ocean  = VariateColor(rgb <0.1020, 0.1588, 0.9224>, fColorDev, bMonoColor, rPlanet);
  #end

  // Base pigments
  // ---------------------------------------------------------------------------
  #declare P_SurfaceBase    = pigment { Soil filter 0 } //finish { surface_finish } }
  #declare P_OceanBase      = pigment { Ocean filter 1 }
  #declare P_ArcticBase     = pigment { color rgb <1,1,1> filter 0 }
  #declare P_BaseTrasparent = pigment { color rgb <1,1,1> filter 1 } //transparent
  
  // Landscape Zones pigment macro
  // ---------------------------------------------------------------------------
  #macro mMicroStructure_Arid()
     #local fTurbulence = RRand(4.0, 6.0, rPlanet);
     #local fPhase = RRand(0.20, 1.0, rPlanet);
     #local fLambda = RRand(5.0,7.0,rPlanet); // controls coastline
     #local fOmega = RRand(0.45,0.60,rPlanet); // controls islands
     #local fScale = RRand(30, 150,rPlanet);
     #local fSteps = RRand(4, 10, rPlanet);
        agate turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
        color_map {
           #local I=0; #while(I<1)
              #local iZone  = IRand(1,3,rPlanet);
              #switch(iZone)
                 #case (1) #local iColor = cSand[IRand(0,9,rPlanet)];  #break
                 #case (2) #local iColor = cGreen[IRand(0,9,rPlanet)]; #break
                 #case (3) #local iColor = cGreen[IRand(0,1,rPlanet)]; #break
              #end
              //#local cColor = surface_color_random(iColor, surface_color_deviation);
              [I VariateColor(Soil, fColorDev, bMonoColor, rPlanet) ]
           #local I=I+1/fSteps; #end
        } scale fScale*fPlanetRadius rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)> //}
  #end //macro
  
  #macro mMicroStructure_Mediterran()
     #local fTurbulence = RRand(4.0, 7.0, rPlanet);
     #local fPhase = RRand(0.20, 1.0, rPlanet);
     #local fLambda = RRand(4.0,10.0,rPlanet); // controls coastline
     #local fOmega = RRand(0.50,0.70,rPlanet); // controls islands
     #local fScale = RRand(20, 95,rPlanet);
     #local fSteps = RRand(4, 10, rPlanet);
        agate turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
        color_map {
           #local I=0; #while(I<1)
              #local iZone  = IRand(1,2,rPlanet);
              #switch(iZone)
                 #case (1) #local iColor = cGreen[IRand(0,9,rPlanet)]; #break
                 #case (2) #local iColor = cStone[IRand(0,9,rPlanet)]; #break
                 #case (3) #local iColor = cSand[IRand(0,9,rPlanet)];  #break
              #end
              //#local cColor = surface_color_random(iColor, surface_color_deviation);
              [I VariateColor(Forrest, fColorDev, bMonoColor, rPlanet) ]
           #local I=I+1/fSteps; #end
        } scale fScale*fPlanetRadius rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)> //}
  #end //macro
  
  #macro mMicroStructure_Moderate()
     #local fTurbulence = RRand(4.0, 7.0, rPlanet);
     #local fPhase = RRand(0.20, 1.0, rPlanet);
     #local fLambda = RRand(4.0,10.0,rPlanet); // controls coastline
     #local fOmega = RRand(0.50,0.70,rPlanet); // controls islands
     #local fScale = RRand(20, 95,rPlanet);
     #local fSteps = RRand(4, 10, rPlanet);
        agate turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
        color_map {
           #local I=0; #while(I<1)
              #local iZone  = IRand(1,3,rPlanet);
              #switch(iZone)
                 #case (1) #local iColor = cGreen[IRand(0,9,rPlanet)]; #break
                 #case (2) #local iColor = cStone[IRand(0,9,rPlanet)]; #break
                 #case (3) #local iColor = cStone[IRand(0,9,rPlanet)]; #break
              #end
              //#local cColor = surface_color_random(iColor, surface_color_deviation);
              [I VariateColor(iColor, fColorDev, bMonoColor, rPlanet) ]
           #local I=I+1/fSteps; #end
        } scale fScale*fPlanetRadius rotate <RRand(0,360,rPlanet),RRand(0,360,rPlanet),RRand(0,360,rPlanet)> //}
  #end //macro
  
  // Landscape Zones gradient (longitudonal)
  // ---------------------------------------------------------------------------
  #macro mArid()
     #local fSteps           = RRand(3, 5, rPlanet);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/2,rPlanet);
     #local fGradXTurbulence = RRand(0.01, 0.09, rPlanet);
     #local fGradXOmega      = RRand(0.35, 0.55, rPlanet);
     #local fGradXLambda     = RRand(3, 4, rPlanet);
     #local fGradScale       = fPlanetRadius;
     gradient x pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Arid = pigment { mMicroStructure_Arid() };
           [I+fJitter P_MicroStructure_Arid ] [I+1/fSteps-fJitter P_MicroStructure_Arid ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
  #end
  #declare P_Surface_Arid  = pigment { mArid() }
  
  #macro mMediterran()
     #local fSteps           = RRand(3, 5, rPlanet);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/2,rPlanet);
     #local fGradXTurbulence = RRand(0.01, 0.09, rPlanet);
     #local fGradXOmega      = RRand(0.35, 0.55, rPlanet);
     #local fGradXLambda     = RRand(3, 4, rPlanet);
     #local fGradScale       = fPlanetRadius;
     gradient x pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Mediterran = pigment { mMicroStructure_Mediterran() };
           [I+fJitter P_MicroStructure_Mediterran ] [I+1/fSteps-fJitter P_MicroStructure_Mediterran ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
  #end
  #declare P_Surface_Mediterran  = pigment { mMediterran() }
  
  #macro mModerate()
     #local fSteps           = RRand(3, 5, rPlanet);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/2,rPlanet);
     #local fGradXTurbulence = RRand(0.01, 0.09, rPlanet);
     #local fGradXOmega      = RRand(0.35, 0.55, rPlanet);
     #local fGradXLambda     = RRand(3, 4, rPlanet);
     #local fGradScale       = fPlanetRadius;
     gradient x pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Moderate = pigment { mMicroStructure_Moderate() };
           [I+fJitter P_MicroStructure_Moderate ] [I+1/fSteps-fJitter P_MicroStructure_Moderate ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
  #end
  #declare P_Surface_Moderate  = pigment { mModerate() }
  
  // Climate Zones gradient (latitudonal)
  // ---------------------------------------------------------------------------
  #declare fGradYTurbulence = RRand(0.01, 0.09, rPlanet);
  #declare fGradYOmega      = RRand(0.35, 0.55, rPlanet);
  #declare fGradYLambda     = RRand(3, 4, rPlanet);
  #declare fGradScale       = 2*fPlanetRadius;
  #declare fJitter          = RRand(0.05,0.10,rPlanet);
  #declare P_SurfaceClimateGradient = pigment { gradient y pigment_map { //step 1/5=0.2; transition step/4=0.05
     [0.00 P_Surface_Moderate scale 1/fGradScale ] [0.15-fJitter P_Surface_Moderate scale 1/fGradScale ] //moderate
     [0.15+fJitter P_Surface_Mediterran  scale 1/fGradScale ] [0.35-fJitter P_Surface_Mediterran scale 1/fGradScale ] //mediterranean
     [0.35+fJitter P_Surface_Arid scale 1/fGradScale ] [0.65-fJitter P_Surface_Arid scale 1/fGradScale ] //equatorial
     [0.65+fJitter P_Surface_Mediterran scale 1/fGradScale ] [0.85-fJitter P_Surface_Mediterran scale 1/fGradScale ] //mediterranean
     [0.85+fJitter P_Surface_Moderate scale 1/fGradScale ] [1.00 P_Surface_Moderate scale 1/fGradScale ] //moderate
  } turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda scale fGradScale phase 0.5 }
  
  // Ocean pigment
  // ---------------------------------------------------------------------------
  #declare ocean_base_color = rgb <16/255, 38/255, 82/255>;
  #declare ocean_color_deviation = RRand(0,0.05,rPlanet);
  #declare ocdev_r        = ocean_base_color.red + RRand(-ocean_color_deviation,ocean_color_deviation,rPlanet);
  #declare ocdev_g        = ocean_base_color.green + RRand(-ocean_color_deviation,ocean_color_deviation,rPlanet);
  #declare ocdev_b        = ocean_base_color.blue + RRand(-ocean_color_deviation,ocean_color_deviation,rPlanet);
  #declare P_OceanTexture = pigment { bumps color_map { 
    [0.0 ocean_base_color*RRand(0.7,1.5,rPlanet) ]
    [1.0 rgb <ocdev_r, ocdev_g, ocdev_b>*RRand(0.5,0.8,rPlanet) ]
  } turbulence 1 lambda 3 scale RRand(0.25,1.0,rPlanet)*fPlanetRadius }
  
  // Planet texture
  // ---------------------------------------------------------------------------
  #declare fSurfaceTurbulence = RRand(0.3, 0.90, rPlanet); // complexity of continents
  #declare fSurfaceOmega = RRand(0.30, 0.55, rPlanet); // increses disconnected continents
  #declare fSurfaceLambda = RRand(3.0, 4.5, rPlanet); // increses coastline roughness
  #declare fSurfacePhase = RRand(0.1, 0.5, rPlanet); // different ocean shape
  #declare fSurfacePercent = RRand(0.3, 0.8, rPlanet); // approximate portion of land versus ocean
  #declare fSurfaceScale = 0.5*fPlanetRadius;
  #declare iSurfacePattern = IRand(1,5,rPlanet);
  #declare fSurfaceRotation = RRand(0, 360, rPlanet);
  #declare T_PlanetSurface = texture { pigment { //1-bozo; 2-bumps; 3-dents; 4-spotted; 5-wrinkles
        #if(iSurfacePattern=1) bozo #end
        #if(iSurfacePattern=2) bumps #end
        #if(iSurfacePattern=3) dents #end
        #if(iSurfacePattern=4) spotted #end
        #if(iSurfacePattern=5) wrinkles #end
        pigment_map {
           [0.00 P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land ini
           [fSurfacePercent P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land end
           [fSurfacePercent P_OceanTexture scale 1/fSurfaceScale ] //ocean ini
           [1.00 P_OceanTexture scale 1/fSurfaceScale ] //ocean end
        }
     turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale 
  } finish { surface_finish } }
  
  // Arctic texture
  // ---------------------------------------------------------------------------
  #declare fGradYTurbulence = RRand(0.01, 0.09, rPlanet);
  #declare fGradYOmega      = RRand(0.35, 0.55, rPlanet);
  #declare fGradYLambda     = RRand(4, 6, rPlanet);
  #declare fArcticExtension = RRand(0.01, 0.03, rPlanet);
  #declare fGradScale       = (2.1-(1*fArcticExtension))*fPlanetRadius;
  #declare T_ArcticTexture  = texture { pigment { gradient y pigment_map {
     [0.00 P_ArcticBase scale 1/fGradScale] [fArcticExtension P_ArcticBase scale 1/fGradScale]
     [fArcticExtension   P_BaseTrasparent scale 1/fGradScale ] [1-fArcticExtension P_BaseTrasparent scale 1/fGradScale ]
     [1-fArcticExtension P_ArcticBase scale 1/fGradScale]      [1.00 P_ArcticBase scale 1/fGradScale] //moderate
  } turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda scale fGradScale phase 0.5 }
  finish { surface_finish } }
  
  // Final Surface Texture
  // ---------------------------------------------------------------------------

  sphere {<0, 0, 0>, fPlanetRadius
    texture { T_PlanetSurface }
    texture { T_ArcticTexture }
    finish { surface_finish }
    hollow on
    no_reflection
  }

#end //terran planet macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 19
#macro TerranPlanet6(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aSeedNum)

  #local iSeedNum = dimension_size(aSeedNum,1);
  #declare rPlanet = seed(aSeedNum[0]);
  #if (iSeedNum>=1) #declare rStructure = seed(aSeedNum[0]); // terrain shape
  #else #declare rStructure = rPlanet; #end
  #if (iSeedNum>=2) #declare rTexture   = seed(aSeedNum[1]);
  #else #declare rTexture   = rPlanet;  #end // texture seed
  #if (iSeedNum>=3) #declare rColor     = seed(aSeedNum[2]);
  #else #declare rColor     = rPlanet;  #end // color seed
  #if (iSeedNum>=4) #declare rOcean     = seed(aSeedNum[3]);
  #else #declare rOcean     = rPlanet; #end // ocean texture seed

  #declare DRAW_ICE = 0; #declare rIce = seed(0);
  #if (iSeedNum>=5)
    #if (aSeedNum[4]>0)
      #declare rIce       = seed(aSeedNum[4]);
      #declare DRAW_ICE   = 1;
    #end
  #end // arctic ice texture seed

  #declare NUM_RIVERS = 0;
  #if (iSeedNum>=6)
    #if (aSeedNum[5]>0)
      #declare rRiver     = seed(aSeedNum[5]);
      #declare NUM_RIVERS = IRand(5,20,rRiver);
    #end
  #end // river seed

  #declare NUM_LIGHTMAPS = 0; // light seed
  #if (iSeedNum>=7)
    #if (aSeedNum[6]>0)
      #declare rLight        = seed(aSeedNum[6]);
      #declare NUM_LIGHTMAPS = IRand(3,10,rLight);
    #end
  #end

  InitColors()

  #if (aBaseColors[0].red=0 & aBaseColors[0].green=0 & aBaseColors[0].blue=0)
    #local iColNum = 0;
  #else
    #local iColNum = dimension_size(aBaseColors,1);
  #end

  #if (iColNum>=1) //soil
    #declare Soil  = VariateColor(aBaseColors[0], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Soil = cSand[RRand(0,dimension_size(cSand,1),rColor)];
  #end
  #if (iColNum>=2) //forrest
    #declare Forrest  = VariateColor(aBaseColors[1], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Forrest = cGreen[RRand(0,dimension_size(cGreen,1),rColor)];
  #end
  #if (iColNum>=3) //fields
    #declare Field  = VariateColor(aBaseColors[2], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Field = cStone[RRand(0,dimension_size(cStone,1),rColor)];
  #end
  #if (iColNum>=4) //desert
    #declare Desert  = VariateColor(aBaseColors[3], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Desert = cSand[RRand(0,dimension_size(cSand,1),rColor)];
  #end
  #if (iColNum>=5) //Jungle
    #declare Jungle  = VariateColor(aBaseColors[4], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Jungle = cGreen[RRand(0,dimension_size(cGreen,1),rColor)];
  #end

  //Soil
  #declare cSoil = array [10];
  #local c=0; #while (c<10)
    #declare cSoil[c] = VariateColor(Soil, fColorDev, bMonoColor, rPlanet);
  #local c=c+1; #end
  // Forest
  #declare cForrest = array [10];
  #local c=0; #while (c<10)
    #declare cForrest[c] = VariateColor(Forrest, fColorDev, bMonoColor, rPlanet);
  #local c=c+1; #end
  // Fields
  #declare cFields = array [10];
  #local c=0; #while (c<10)
    #declare cFields[c] = VariateColor(Field, fColorDev, bMonoColor, rPlanet);
  #local c=c+1; #end
  // Desert
  #declare cDesert = array [10];
  #local c=0; #while (c<10)
    #declare cDesert[c] = VariateColor(Desert, fColorDev, bMonoColor, rPlanet);
  #local c=c+1; #end
  // Jungle
  #declare cJungle = array [10];
  #local c=0; #while (c<10)
    #declare cJungle[c] = VariateColor(Jungle, fColorDev, bMonoColor, rPlanet);
  #local c=c+1; #end

  // Base pigments
  // ---------------------------------------------------------------------------
  #declare P_SurfaceBase    = pigment { Soil filter 0 }
  #declare P_OceanBase      = pigment { Soil filter 1 }
  #declare P_ArcticBase     = pigment { color rgb <1,1,1> filter 0 }
  #declare P_BaseTrasparent = pigment { color rgb <1,1,1> filter 1 } //transparent
  
  // Landscape Zones pigment macro
  // ---------------------------------------------------------------------------
  #macro mMicroStructure_Arid()
     #local fTurbulence = RRand(4.0, 7.0, rColor);
     #local fPhase = RRand(0.20, 1.0, rColor);
     #local fLambda = RRand(5.0,7.0,rColor); // controls coastline
     #local fOmega = RRand(0.50,0.60,rColor); // controls islands
     #local fScale = RRand(0.01, 1, rColor);
     #local fSteps = RRand(2, 40, rColor);
     #local iPattern = IRand(4, 15, rColor);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           #local iZone  = IRand(1,3,rColor);
           #switch(iZone)
              #case (1) #local iColor = cDesert[IRand(0,9,rColor)];  #break
              #case (2) #local iColor = cForrest[IRand(0,9,rColor)]; #break
              #case (3) #local iColor = cJungle[IRand(0,1,rColor)];  #break
           #end
           #local cColor = VariateColor(iColor, fColorDev, bMonoColor, rPlanet);
           [I cColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
  #end //macro
  
  #macro mMicroStructure_Mediterran()
     #local fTurbulence = RRand(4.0, 7.0, rColor);
     #local fPhase = RRand(0.20, 1.0, rColor);
     #local fLambda = RRand(4.0,10.0,rColor); // controls coastline
     #local fOmega = RRand(0.50,0.70,rColor); // controls islands
     #local fScale = RRand(0.01, 1, rColor);
     #local fSteps = RRand(2, 40, rColor);
     #local iPattern = IRand(4, 15, rColor);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           #local iZone  = IRand(1,2,rColor);
           #switch(iZone)
              #case (1) #local iColor = cForrest[IRand(0,9,rColor)]; #break
              #case (2) #local iColor = cSoil[IRand(0,9,rColor)];    #break
              #case (3) #local iColor = cFields[IRand(0,9,rColor)];  #break
           #end
           #local cColor = VariateColor(iColor, fColorDev, bMonoColor, rPlanet);
           [I cColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
  #end //macro
  
  #macro mMicroStructure_Moderate()
     #local fTurbulence = RRand(4.0, 7.0, rColor);
     #local fPhase = RRand(0.20, 0.9, rColor);
     #local fLambda = RRand(4.0,10.0,rColor); // controls coastline
     #local fOmega = RRand(0.50,0.70,rColor); // controls islands
     #local fScale = RRand(0.01, 1, rColor);
     #local fSteps = RRand(2, 40, rColor);
     #local iPattern = IRand(4, 15, rColor);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           #local iZone  = IRand(1,3,rColor);
           #switch(iZone)
              #case (1) #local iColor = cForrest[IRand(0,9,rColor)]; #break
              #case (2) #local iColor = cSoil[IRand(0,9,rColor)];    #break
              #case (3) #local iColor = cFields[IRand(0,9,rColor)];  #break
           #end
           #local cColor = VariateColor(iColor, fColorDev, bMonoColor, rPlanet);
           [I cColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
  #end //macro
  
  // Landscape Zones gradient (longitudonal)
  // ---------------------------------------------------------------------------
  #macro mArid()
     #local fSteps           = RRand(2, 4, rColor);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
     #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
     #local fGradXOmega      = RRand(0.50, 0.60, rColor);
     #local fGradXLambda     = RRand(3, 5, rColor);
     #local fGradScale       = fPlanetRadius;
     gradient x pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Arid = pigment { mMicroStructure_Arid() };
           [I+fJitter P_MicroStructure_Arid ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Arid ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
  #end
  #declare P_Surface_Arid  = pigment { mArid() }
  
  #macro mMediterran()
     #local fSteps           = RRand(2, 4, rColor);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
     #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
     #local fGradXOmega      = RRand(0.50, 0.60, rColor);
     #local fGradXLambda     = RRand(3, 5, rColor);
     #local fGradScale       = fPlanetRadius;
     gradient x pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Mediterran = pigment { mMicroStructure_Mediterran() };
           [I+fJitter P_MicroStructure_Mediterran ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Mediterran ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
  #end
  #declare P_Surface_Mediterran  = pigment { mMediterran() }
  
  #macro mModerate()
     #local fSteps           = RRand(2, 4, rColor);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
     #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
     #local fGradXOmega      = RRand(0.50, 0.60, rColor);
     #local fGradXLambda     = RRand(3, 5, rColor);
     #local fGradScale       = fPlanetRadius;
     gradient x pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Moderate = pigment { mMicroStructure_Moderate() };
           [I+fJitter P_MicroStructure_Moderate ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Moderate ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
  #end
  //#declare P_Surface_Moderate  = pigment { mModerate() }
  
  // Climate Zones gradient (latitudonal)
  // ---------------------------------------------------------------------------
  #declare fGradYTurbulence = RRand(0.01, 0.09, rColor);
  #declare fGradYOmega      = RRand(0.35, 0.55, rColor);
  #declare fGradYLambda     = RRand(3, 4, rColor);
  #declare fGradScale       = 2*fPlanetRadius;
  #declare fJitter          = RRand(0.05,0.10,rColor);
  #declare P_SurfaceClimateGradient = pigment { gradient y pigment_map { //step 1/5=0.2; transition step/4=0.05
     #local P_Surface_Moderate  = pigment { mModerate() }
     [0.00 P_Surface_Moderate scale 1/fGradScale ] [0.15-fJitter P_Surface_Moderate scale 1/fGradScale ] //moderate
     [0.15+fJitter P_Surface_Mediterran  scale 1/fGradScale ] [0.35-fJitter P_Surface_Mediterran scale 1/fGradScale ] //mediterranean
     [0.35+fJitter P_Surface_Arid scale 1/fGradScale ] [0.65-fJitter P_Surface_Arid scale 1/fGradScale ] //equatorial
     [0.65+fJitter P_Surface_Mediterran scale 1/fGradScale ] [0.85-fJitter P_Surface_Mediterran scale 1/fGradScale ] //mediterranean
     #local P_Surface_Moderate  = pigment { mModerate() }
     [0.85+fJitter P_Surface_Moderate scale 1/fGradScale ] [1.00 P_Surface_Moderate scale 1/fGradScale ] //moderate
  } turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda scale fGradScale phase 0.5 }
  
  // Ocean pigment
  // ---------------------------------------------------------------------------
  #declare ocean_base_color = rgb <0.063, 0.149, 0.322>;
  #declare ocean_color_deviation = RRand(0,0.05,rOcean);
  #declare ocdev_r        = ocean_base_color.red + RRand(-ocean_color_deviation,ocean_color_deviation,rOcean);
  #declare ocdev_g        = ocean_base_color.green + RRand(-ocean_color_deviation,ocean_color_deviation,rOcean);
  #declare ocdev_b        = ocean_base_color.blue + RRand(-ocean_color_deviation,ocean_color_deviation,rOcean);
  #declare P_OceanTexture = pigment { bumps color_map { 
        [0.0 ocean_base_color*RRand(0.7,1.5,rOcean) ]
        [1.0 rgb <ocdev_r, ocdev_g, ocdev_b>*RRand(0.5,0.8,rOcean) ]
  } turbulence 1 lambda 3 scale RRand(0.25,1.0,rOcean)*fPlanetRadius }
  
  // Planet texture
  // ---------------------------------------------------------------------------
  #declare fSurfaceTurbulence = RRand(0.30, 0.90, rStructure); // complexity of continents
  #declare fSurfaceOmega = RRand(0.30, 0.45, rStructure); // increses disconnected continents
  #declare fSurfaceLambda = RRand(3.0, 4.5, rStructure); // increses coastline roughness
  #declare fSurfacePhase = RRand(0.0, 0.4, rStructure); // different ocean shape
  #declare fSurfacePercent = RRand(0.4, 0.8, rOcean); // approximate portion of land versus ocean
  #declare fSurfaceScale = 0.5*fPlanetRadius;
  #declare iSurfacePattern = IRand(1,5,rStructure);
  #declare fSurfaceRotation = RRand(0, 360, rStructure);
  #declare fRotateX = RRand(0,360,rStructure);
  #declare fRotateY = RRand(0,360,rStructure);
  #declare fRotateZ = RRand(0,360,rStructure);
  #declare T_PlanetSurface = texture { pigment { //1-bozo; 2-bumps; 3-dents; 4-spotted; 5-wrinkles
        #if(iSurfacePattern=1) bozo #end
        #if(iSurfacePattern=2) bumps #end
        #if(iSurfacePattern=3) dents #end
        #if(iSurfacePattern=4) spotted #end
        #if(iSurfacePattern=5) wrinkles #end
        pigment_map {
           [0.00 P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land ini
           [fSurfacePercent P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land end
           [fSurfacePercent P_OceanTexture scale 1/fSurfaceScale ] //ocean ini
           [1.00 P_OceanTexture scale 1/fSurfaceScale ] //ocean end
        }
     turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
     rotate <fRotateX, fRotateY, fRotateZ> 
  } finish { surface_finish } }
  
  #declare T_TestContinents = texture { pigment {
        #if(iSurfacePattern=1) bozo #end
        #if(iSurfacePattern=2) bumps #end
        #if(iSurfacePattern=3) dents #end
        #if(iSurfacePattern=4) spotted #end
        #if(iSurfacePattern=5) wrinkles #end
        pigment_map {
           [0.00 P_SurfaceBase scale 1/fSurfaceScale ] //land ini
           [fSurfacePercent P_SurfaceBase scale 1/fSurfaceScale ] //land end
           [fSurfacePercent P_OceanBase scale 1/fSurfaceScale ] //ocean ini
           [1.00 P_OceanBase scale 1/fSurfaceScale ] //ocean end
        }
     turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
     rotate <fRotateX, fRotateY, fRotateZ> 
  } finish { surface_finish } }
  
  #declare shallow_coastline = 0;
  #declare fOceanDarkness = RRand(0.3, 1.0, rOcean);
  #declare T_OceanDepth = texture { pigment {
        #if(iSurfacePattern=1) bozo #end
        #if(iSurfacePattern=2) bumps #end
        #if(iSurfacePattern=3) dents #end
        #if(iSurfacePattern=4) spotted #end
        #if(iSurfacePattern=5) wrinkles #end
        pigment_map {
           [0.00 color rgbft<0,0,0,0,1> ] //land ini
           [fSurfacePercent color rgbft<0,0,0,0,1> scale 1/fSurfaceScale ] //land end
           #if (shallow_coastline)
              [fSurfacePercent rgb ocean_base_color+<0,1.5,0> filter 0 transmit 0.5 scale 1/fSurfaceScale ] //coastline
              [fSurfacePercent+0.01 rgb ocean_base_color filter 0 transmit 0 scale 1/fSurfaceScale ] //coastline
           #end
           [1.00 color rgb ocean_base_color*0.3 filter 0 transmit 0 scale 1/fSurfaceScale ] //deep ocean
        }
     turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
     rotate <fRotateX, fRotateY, fRotateZ> 
  } finish { surface_finish } }
  
  // Arctic Pattern
  // ---------------------------------------------------------------------------
  #macro mMicroStructure_Arctic()
     #local fTurbulence = RRand(4.0, 7.0, rColor);
     #local fPhase = RRand(0.20, 1.0, rColor);
     #local fLambda = RRand(5.0,7.0,rColor); // controls coastline
     #local fOmega = RRand(0.50,0.60,rColor); // controls islands
     #local fScale = RRand(0.01, 0.1, rColor);
     #local fSteps = RRand(20, 40, rColor);
     #local iPattern = IRand(4, 20, rColor);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           #local iColor = color rgb <0.95, 0.95, 1.00>;
           #local cColor = VariateColor(iColor, fColorDev, bMonoColor, rPlanet);
           [I cColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
  #end //macro
  
  #macro mArctic()
     #local fSteps           = RRand(3, 5, rColor);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
     #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
     #local fGradXOmega      = RRand(0.45, 0.55, rColor);
     #local fGradXLambda     = RRand(3, 5, rColor);
     #local fGradScale       = fPlanetRadius;
     gradient x pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Arctic = pigment { mMicroStructure_Arctic() };
           [I+fJitter P_MicroStructure_Arctic ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Arctic ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
  #end
  
  // Arctic texture
  // ---------------------------------------------------------------------------
  #declare fGradYTurbulence = RRand(0.01, 0.10, rIce);
  #declare fGradYOmega      = RRand(0.35, 0.45, rIce);
  #declare fGradYLambda     = RRand(4, 6, rIce);
  #declare fArcticExtension = 0; //RRand(0.00 , 0.03, rIce);
  #declare fGradScale       = 2.1*fPlanetRadius;
  #declare T_ArcticTexture  = texture { pigment { gradient y pigment_map {
     #local P_Surface_Arctic  = pigment { mArctic() }
     [0.00 P_Surface_Arctic scale 1/fGradScale]                [fArcticExtension P_Surface_Arctic scale 1/fGradScale] //arctic
     [fArcticExtension   P_BaseTrasparent scale 1/fGradScale ] [1-fArcticExtension P_BaseTrasparent scale 1/fGradScale ] //transparent
     #local P_Surface_Arctic  = pigment { mArctic() }
     [1-fArcticExtension P_Surface_Arctic scale 1/fGradScale]  [1.00 P_Surface_Arctic scale 1/fGradScale] //arctic
  } turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda scale fGradScale phase 0.5 }
  finish { surface_finish } }
  
  // Final Surface Texture Macro
  #macro mPlanetSurface()
    texture { T_PlanetSurface }
    texture { T_OceanDepth }
    texture { T_ArcticTexture }
  #end // planet_surface texture

  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    finish { surface_finish }
    hollow on
    no_reflection
  }

#end //terran planet macro

// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 20
#macro TerranPlanet7(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aSeedNum)

  #local iSeedNum = dimension_size(aSeedNum,1);
  #declare rPlanet = seed(aSeedNum[0]);
  #if (iSeedNum>=1) #declare rStructure = seed(aSeedNum[0]); // terrain shape
  #else #declare rStructure = rPlanet; #end
  #if (iSeedNum>=2) #declare rTexture   = seed(aSeedNum[1]);
  #else #declare rTexture   = rPlanet;  #end // texture seed
  #if (iSeedNum>=3) #declare rColor     = seed(aSeedNum[2]);
  #else #declare rColor     = rPlanet;  #end // color seed
  #if (iSeedNum>=4) #declare rOcean     = seed(aSeedNum[3]);
  #else #declare rOcean     = rPlanet; #end // ocean texture seed

  #declare DRAW_ICE = 0; #declare rIce = seed(0);
  #if (iSeedNum>=5)
    #if (aSeedNum[4]>0)
      #declare rIce       = seed(aSeedNum[4]);
      #declare DRAW_ICE   = 1;
    #end
  #end // arctic ice texture seed

  #declare NUM_RIVERS = 0;
  #if (iSeedNum>=6)
    #if (aSeedNum[5]>0)
      #declare rRiver     = seed(aSeedNum[5]);
      #declare NUM_RIVERS = IRand(5,20,rRiver);
    #end
  #end // river seed

  #declare NUM_LIGHTMAPS = 0; // light seed
  #if (iSeedNum>=7)
    #if (aSeedNum[6]>0)
      #declare rLight        = seed(aSeedNum[6]);
      #declare NUM_LIGHTMAPS = IRand(3,10,rLight);
    #end
  #end

  InitColors()

  #if (aBaseColors[0].red=0 & aBaseColors[0].green=0 & aBaseColors[0].blue=0)
    #local iColNum = 0;
  #else
    #local iColNum = dimension_size(aBaseColors,1);
  #end

  #if (iColNum>=1) //soil
    #declare Soil  = VariateColor(aBaseColors[0], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Soil = cSand[RRand(0,dimension_size(cSand,1),rColor)];
  #end
  #if (iColNum>=2) //forrest
    #declare Forrest  = VariateColor(aBaseColors[1], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Forrest = cGreen[RRand(0,dimension_size(cGreen,1),rColor)];
  #end
  #if (iColNum>=3) //fields
    #declare Field  = VariateColor(aBaseColors[2], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Field = cStone[RRand(0,dimension_size(cStone,1),rColor)];
  #end
  #if (iColNum>=4) //desert
    #declare Desert  = VariateColor(aBaseColors[3], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Desert = cSand[RRand(0,dimension_size(cSand,1),rColor)];
  #end
  #if (iColNum>=5) //Jungle
    #declare Jungle  = VariateColor(aBaseColors[4], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Jungle = cGreen[RRand(0,dimension_size(cGreen,1),rColor)];
  #end

  //Soil
  #declare cSoil = array [10];
  #local c=0; #while (c<10)
    #declare cSoil[c] = VariateColor(Soil, fColorDev, bMonoColor, rPlanet);
  #local c=c+1; #end
  // Forest
  #declare cForrest = array [10];
  #local c=0; #while (c<10)
    #declare cForrest[c] = VariateColor(Forrest, fColorDev, bMonoColor, rPlanet);
  #local c=c+1; #end
  // Fields
  #declare cFields = array [10];
  #local c=0; #while (c<10)
    #declare cFields[c] = VariateColor(Field, fColorDev, bMonoColor, rPlanet);
  #local c=c+1; #end
  // Desert
  #declare cDesert = array [10];
  #local c=0; #while (c<10)
    #declare cDesert[c] = VariateColor(Desert, fColorDev, bMonoColor, rPlanet);
  #local c=c+1; #end
  // Jungle
  #declare cJungle = array [10];
  #local c=0; #while (c<10)
    #declare cJungle[c] = VariateColor(Jungle, fColorDev, bMonoColor, rPlanet);
  #local c=c+1; #end

  // Base pigments
  // ---------------------------------------------------------------------------
  #declare P_SurfaceBase    = pigment { Soil filter 0 }
  #declare P_OceanBase      = pigment { Soil filter 1 }
  #declare P_ArcticBase     = pigment { color rgb <1,1,1> filter 0 }
  #declare P_BaseTrasparent = pigment { color rgb <1,1,1> filter 1 } //transparent
  
  // Landscape Zones pigment macro
  // ---------------------------------------------------------------------------
  #macro mMicroStructure_Arid()
     #local fTurbulence = RRand(4.0, 7.0, rColor);
     #local fPhase = RRand(0.20, 0.9, rColor);
     #local fLambda = RRand(5.0,7.0,rColor); // controls coastline
     #local fOmega = RRand(0.50,0.60,rColor); // controls islands
     #local fScale = RRand(0.001, 0.01, rColor);
     #local fSteps = RRand(4, 20, rColor);
     #local iPattern = IRand(4, 18, rColor);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           #local iZone  = IRand(1,3,rColor);
           #local iColor = IRand(0,9,rColor);
     #if (create_logfile)
        #write(LogFile,"iZone = ",iZone,"\n")
        #write(LogFile," iColor = ",iColor,"\n")
     #end
           #switch(iZone)
              #case (1) #local iColor = cDesert[iColor];  #break
              #case (2) #local iColor = cForrest[iColor]; #break
              #case (3) #local iColor = cJungle[iColor];  #break
           #end
           #local cColor = VariateColor(iColor, fColorDev, bMonoColor, rColor);
           [I cColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
  #end //macro
  
  #macro mMicroStructure_Mediterran()
     #local fTurbulence = RRand(4.0, 7.0, rColor);
     #local fPhase = RRand(0.20, 0.9, rColor);
     #local fLambda = RRand(4.0,10.0,rColor); // controls coastline
     #local fOmega = RRand(0.50,0.70,rColor); // controls islands
     #local fScale = RRand(0.001, 0.01, rColor);
     #local fSteps = RRand(4, 20, rColor);
     #local iPattern = IRand(4, 18, rColor);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           #local iZone  = IRand(1,3,rColor);
           #local iColor = IRand(0,9,rColor);
           #switch(iZone)
              #case (1) #local iColor = cForrest[iColor]; #break
              #case (2) #local iColor = cSoil[iColor];    #break
              #case (3) #local iColor = cFields[iColor];  #break
           #end
           #local cColor = VariateColor(iColor, fColorDev, bMonoColor, rColor);
           [I cColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
  #end //macro
  
  #macro mMicroStructure_Moderate()
     #local fTurbulence = RRand(4.0, 7.0, rColor);
     #local fPhase = RRand(0.20, 0.9, rColor);
     #local fLambda = RRand(4.0,10.0,rColor); // controls coastline
     #local fOmega = RRand(0.50,0.70,rColor); // controls islands
     #local fScale = RRand(0.001, 0.01, rColor);
     #local fSteps = RRand(4, 20, rColor);
     #local iPattern = IRand(4, 18, rColor);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           #local iZone  = IRand(1,3,rColor);
           #switch(iZone)
              #case (1) #local iColor = cForrest[IRand(0,9,rColor)]; #break
              #case (2) #local iColor = cSoil[IRand(0,9,rColor)];    #break
              #case (3) #local iColor = cFields[IRand(0,9,rColor)];  #break
           #end
           #local cColor = VariateColor(iColor, fColorDev, bMonoColor, rColor);
           [I cColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
  #end //macro
  
  // Landscape Zones gradient (longitudonal)
  // ---------------------------------------------------------------------------
  #macro mArid()
     #local fSteps           = RRand(2, 4, rColor);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
     #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
     #local fGradXOmega      = RRand(0.50, 0.60, rColor);
     #local fGradXLambda     = RRand(3, 5, rColor);
     #local fGradScale       = fPlanetRadius;
     gradient x pigment_map {
        #local I=0; #while(I<1)
     #if (create_logfile)
        #write(LogFile,"Arid Step = ",I,"\n")
     #end
           #local P_MicroStructure_Arid = pigment { mMicroStructure_Arid() };
           [I+fJitter P_MicroStructure_Arid ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Arid ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
  #end
  
  #macro mMediterran()
     #local fSteps           = RRand(2, 4, rColor);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
     #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
     #local fGradXOmega      = RRand(0.50, 0.60, rColor);
     #local fGradXLambda     = RRand(3, 5, rColor);
     #local fGradScale       = fPlanetRadius;
     gradient x pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Mediterran = pigment { mMicroStructure_Mediterran() };
           [I+fJitter P_MicroStructure_Mediterran ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Mediterran ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
  #end
  
  #macro mModerate()
     #local fSteps           = RRand(2, 4, rColor);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
     #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
     #local fGradXOmega      = RRand(0.50, 0.60, rColor);
     #local fGradXLambda     = RRand(3, 5, rColor);
     #local fGradScale       = fPlanetRadius;
     gradient x pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Moderate = pigment { mMicroStructure_Moderate() };
           [I+fJitter P_MicroStructure_Moderate ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Moderate ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
  #end
  
  // Climate Zones gradient (latitudonal)
  // ---------------------------------------------------------------------------
  #declare fGradYTurbulence = RRand(0.01, 0.09, rColor);
  #declare fGradYOmega      = RRand(0.35, 0.55, rColor);
  #declare fGradYLambda     = RRand(3, 4, rColor);
  #declare fGradScale       = 2*fPlanetRadius;
  #declare fJitter          = RRand(0.05,0.10,rColor);
  #declare P_SurfaceClimateGradient = pigment { gradient y pigment_map { //step 1/5=0.2; transition step/4=0.05
     #local P_Surface_Moderate  = pigment { mModerate() }
        [0.00 P_Surface_Moderate scale 1/fGradScale ] [0.15-fJitter P_Surface_Moderate scale 1/fGradScale ] //moderate
     #local P_Surface_Mediterran  = pigment { mMediterran() }
        [0.15+fJitter P_Surface_Mediterran  scale 1/fGradScale ] [0.35-fJitter P_Surface_Mediterran scale 1/fGradScale ] //mediterranean
     #local P_Surface_Arid  = pigment { mArid() }
        [0.35+fJitter P_Surface_Arid scale 1/fGradScale ] [0.65-fJitter P_Surface_Arid scale 1/fGradScale ] //equatorial
     #local P_Surface_Mediterran  = pigment { mMediterran() }
        [0.65+fJitter P_Surface_Mediterran scale 1/fGradScale ] [0.85-fJitter P_Surface_Mediterran scale 1/fGradScale ] //mediterranean
     #local P_Surface_Moderate  = pigment { mModerate() }
        [0.85+fJitter P_Surface_Moderate scale 1/fGradScale ] [1.00 P_Surface_Moderate scale 1/fGradScale ] //moderate
  } turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda scale fGradScale phase 0.5 }
  
  // Ocean pigment
  // ---------------------------------------------------------------------------
  #declare ocean_base_color = rgb <0.063, 0.149, 0.322>*1.0;
  #declare fSteps      = RRand(2, 10, rOcean);
  #declare fJitter     = RRand(1/fSteps/4,1/fSteps/3,rOcean);
  #declare fTurbulence = RRand(1.00, 2.00, rOcean);
  #declare fOmega      = RRand(0.30, 0.60, rOcean);
  #declare fLambda     = RRand(3, 4, rOcean);
  #declare fScale      = RRand(3, 7, rOcean);
  #declare fColorDev   = RRand(0.7,0.9,rOcean);
  #declare iPattern    = IRand(4, 18, rOcean); //6-bumps
  #declare P_OceanTexture = pigment { //bumps
     GetPattern(iPattern)  
     color_map { 
     #local I=0; #while(I<1)
        [min(1,I) ocean_base_color*(1-I*fColorDev) ]
     #local I=I+1/fSteps; #end
  } turbulence fTurbulence omega fOmega lambda fLambda scale fScale*fPlanetRadius }
  
  // Planet texture
  // ---------------------------------------------------------------------------
  #declare fSurfaceTurbulence = RRand(0.30, 0.90, rStructure); // complexity of continents
  #declare fSurfaceOmega = RRand(0.30, 0.45, rStructure); // increses disconnected continents
  #declare fSurfaceLambda = RRand(3.0, 4.5, rStructure); // increses coastline roughness
  #declare fSurfacePhase = RRand(0.0, 0.4, rStructure); // different ocean shape
  #declare fSurfacePercent = RRand(0.4, 0.8, rStructure); // approximate portion of land versus ocean
  #declare fSurfaceScale = 0.5*fPlanetRadius;
  #declare iSurfacePattern = IRand(4,18,rStructure); //1-5
  #declare fSurfaceRotation = RRand(0, 360, rStructure);
  #declare fRotateX = RRand(0,360,rStructure);
  #declare fRotateY = RRand(0,360,rStructure);
  #declare fRotateZ = RRand(0,360,rStructure);
  #declare T_PlanetSurface = texture { pigment { //1-bozo; 2-bumps; 3-dents; 4-spotted; 5-wrinkles
     GetPattern(iSurfacePattern)
     pigment_map {
        [0.00 P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land ini
        [fSurfacePercent P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land end
        [fSurfacePercent P_OceanTexture scale 1/fSurfaceScale ] //ocean ini
        [1.00 P_OceanTexture scale 1/fSurfaceScale ] //ocean end
     }
  turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
  rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }
  
  #declare T_TestContinents = texture { pigment {
     GetPattern(iSurfacePattern)
     pigment_map {
        [0.00 P_SurfaceBase scale 1/fSurfaceScale ] //land ini
        [fSurfacePercent P_SurfaceBase scale 1/fSurfaceScale ] //land end
        [fSurfacePercent P_OceanBase scale 1/fSurfaceScale ] //ocean ini
        [1.00 P_OceanBase scale 1/fSurfaceScale ] //ocean end
     }
  turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
  rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }
  
  #declare shallow_coastline = 0;
  #declare fOceanDarkness = RRand(0.3, 1.0, rOcean);
  #declare T_OceanDepth = texture { pigment {
     GetPattern(iSurfacePattern)
     pigment_map {
        [0.00 color rgbft<0,0,0,0,1> ] //land ini
        [fSurfacePercent color rgbft<0,0,0,0,1> scale 1/fSurfaceScale ] //land end
        #if (shallow_coastline)
           [fSurfacePercent rgb ocean_base_color+<0,1.5,0> filter 0 transmit 0.5 scale 1/fSurfaceScale ] //coastline
           [fSurfacePercent+0.01 rgb ocean_base_color filter 0 transmit 0 scale 1/fSurfaceScale ] //coastline
        #end
        [1.00 color rgb ocean_base_color*0.3 filter 0 transmit 0 scale 1/fSurfaceScale ] //deep ocean
     }
  turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
  rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }
  
  // Arctic Pattern
  // ---------------------------------------------------------------------------
  #macro mMicroStructure_Arctic()
     #local fTurbulence = RRand(4.0, 7.0, rColor);
     #local fPhase = RRand(0.20, 1.0, rColor);
     #local fLambda = RRand(5.0,7.0,rColor); // controls coastline
     #local fOmega = RRand(0.50,0.60,rColor); // controls islands
     #local fScale = RRand(0.01, 0.1, rColor);
     #local fSteps = RRand(20, 40, rColor);
     #local iPattern = IRand(4, 18, rColor);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           #local iColor = color rgb <0.95, 0.95, 1.00>;
           #local cColor = VariateColor(iColor, fColorDev, bMonoColor, rColor);
           [I cColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
  #end //macro
  
  #macro mArctic()
     #local fSteps           = RRand(3, 5, rColor);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
     #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
     #local fGradXOmega      = RRand(0.45, 0.55, rColor);
     #local fGradXLambda     = RRand(3, 5, rColor);
     #local fGradScale       = fPlanetRadius;
     gradient x pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Arctic = pigment { mMicroStructure_Arctic() };
           [I+fJitter P_MicroStructure_Arctic ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Arctic ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
  #end
  
  // Arctic texture
  // ---------------------------------------------------------------------------
  #declare fGradYTurbulence = RRand(0.01, 0.10, rIce);
  #declare fGradYOmega      = RRand(0.35, 0.45, rIce);
  #declare fGradYLambda     = RRand(4, 6, rIce);
  #declare fArcticExtension = RRand(0.02 , 0.03, rIce);
  #declare fGradScale       = 2.1*fPlanetRadius;
  #declare T_ArcticTexture  = texture { pigment { gradient y pigment_map {
     #local P_Surface_Arctic  = pigment { mArctic() }
     [0.00 P_Surface_Arctic scale 1/fGradScale]                [fArcticExtension P_Surface_Arctic scale 1/fGradScale] //arctic
     [fArcticExtension   P_BaseTrasparent scale 1/fGradScale ] [1-fArcticExtension P_BaseTrasparent scale 1/fGradScale ] //transparent
     #local P_Surface_Arctic  = pigment { mArctic() }
     [1-fArcticExtension P_Surface_Arctic scale 1/fGradScale]  [1.00 P_Surface_Arctic scale 1/fGradScale] //arctic
  } turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda scale fGradScale phase 0.5 }
  finish { surface_finish } }
 
  // Final Surface Texture Macro
  #macro mPlanetSurface()
    texture { T_PlanetSurface }
    texture { T_OceanDepth }
    texture { T_ArcticTexture }
  #end // planet_surface texture
  
  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    finish { surface_finish }
    hollow on
    no_reflection
  }

#end //terran planet macro


// ---------------------------------------------------------------------------------------

//formerly planet_surface_type 21
#macro TerranPlanet8(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aSeedNum)

  #local iSeedNum = dimension_size(aSeedNum,1);
  #declare rPlanet = seed(aSeedNum[0]);
  #if (iSeedNum>=1) #declare rStructure = seed(aSeedNum[0]); // terrain shape
  #else #declare rStructure = rPlanet; #end
  #if (iSeedNum>=2) #declare rTexture   = seed(aSeedNum[1]);
  #else #declare rTexture   = rPlanet;  #end // texture seed
  #if (iSeedNum>=3) #declare rColor     = seed(aSeedNum[2]);
  #else #declare rColor     = rPlanet;  #end // color seed
  #if (iSeedNum>=4) #declare rOcean     = seed(aSeedNum[3]);
  #else #declare rOcean     = rPlanet; #end // ocean texture seed

  #declare DRAW_ICE = 0; #declare rIce = seed(0);
  #if (iSeedNum>=5)
    #if (aSeedNum[4]>0)
      #declare rIce       = seed(aSeedNum[4]);
      #declare DRAW_ICE   = 1;
    #end
  #end // arctic ice texture seed

  #declare NUM_RIVERS = 0;
  #if (iSeedNum>=6)
    #if (aSeedNum[5]>0)
      #declare rRiver     = seed(aSeedNum[5]);
      #declare NUM_RIVERS = IRand(5,20,rRiver);
    #end
  #end // river seed

  #declare NUM_LIGHTMAPS = 0; // light seed
  #if (iSeedNum>=7)
    #if (aSeedNum[6]>0)
      #declare rLight        = seed(aSeedNum[6]);
      #declare NUM_LIGHTMAPS = IRand(3,10,rLight);
    #end
  #end

  InitColors()

  #if (aBaseColors[0].red=0 & aBaseColors[0].green=0 & aBaseColors[0].blue=0)
    #local iColNum = 0;
  #else
    #local iColNum = dimension_size(aBaseColors,1);
  #end

  #if (iColNum>=1) //soil
    #declare Soil  = VariateColor(aBaseColors[0], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Soil = cSand[RRand(0,dimension_size(cSand,1),rColor)];
  #end
  #if (iColNum>=2) //forrest
    #declare Forrest  = VariateColor(aBaseColors[1], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Forrest = cGreen[RRand(0,dimension_size(cGreen,1),rColor)];
  #end
  #if (iColNum>=3) //fields
    #declare Field  = VariateColor(aBaseColors[2], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Field = cStone[RRand(0,dimension_size(cStone,1),rColor)];
  #end
  #if (iColNum>=4) //desert
    #declare Desert  = VariateColor(aBaseColors[3], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Desert = cSand[RRand(0,dimension_size(cSand,1),rColor)];
  #end
  #if (iColNum>=5) //Jungle
    #declare Jungle  = VariateColor(aBaseColors[4], fColorDev, bMonoColor, rPlanet);
  #else
    #declare Jungle = cGreen[RRand(0,dimension_size(cGreen,1),rColor)];
  #end

   //Stone/Erath/Fields
   #declare cStone = array [30];
   #declare cStone[0]  = color rgb <0.188, 0.196, 0.163>;
   #declare cStone[1]  = color rgb <0.257, 0.241, 0.065>;
   #declare cStone[2]  = color rgb <0.154, 0.153, 0.029>;
   #declare cStone[3]  = color rgb <0.234, 0.233, 0.109>;
   #declare cStone[4]  = color rgb <0.194, 0.139, 0.055>;
   #declare cStone[5]  = color rgb <0.275, 0.184, 0.012>;
   #declare cStone[6]  = color rgb <0.316, 0.265, 0.092>;
   #declare cStone[7]  = color rgb <0.212, 0.173, 0.018>;
   #declare cStone[8]  = color rgb <0.108, 0.116, 0.031>;
   #declare cStone[9]  = color rgb <0.200, 0.190, 0.043>;
   #declare cStone[10] = color rgb <0.380, 0.310, 0.122>;
   #declare cStone[11] = color rgb <0.349, 0.357, 0.212>;
   #declare cStone[12] = color rgb <0.322, 0.235, 0.090>;
   #declare cStone[13] = color rgb <0.279, 0.178, 0.054>;
   #declare cStone[14] = color rgb <0.255, 0.235, 0.071>;
   #declare cStone[15] = color rgb <0.255, 0.200, 0.055>;
   #declare cStone[16] = color rgb <0.200, 0.184, 0.078>;
   #declare cStone[17] = color rgb <0.373, 0.341, 0.275>;
   #declare cStone[18] = color rgb <0.333, 0.310, 0.169>;
   #declare cStone[19] = color rgb <0.318, 0.329, 0.224>;
   #declare cStone[20] = color rgb <0.282, 0.302, 0.212>;
   #declare cStone[21] = color rgb <0.259, 0.224, 0.071>;
   #declare cStone[22] = color rgb <0.161, 0.165, 0.143>;
   #declare cStone[23] = color rgb <0.420, 0.402, 0.160>;
   #declare cStone[24] = color rgb <0.165, 0.141, 0.016>;
   //Sand
   #declare cSand = array [20];
   #declare cSand[0]  = color rgb <0.569, 0.375, 0.239>;
   #declare cSand[1]  = color rgb <0.494, 0.249, 0.178>;
   #declare cSand[2]  = color rgb <0.479, 0.278, 0.054>;
   #declare cSand[3]  = color rgb <0.465, 0.265, 0.140>;
   #declare cSand[4]  = color rgb <0.455, 0.306, 0.124>;
   #declare cSand[5]  = color rgb <0.450, 0.200, 0.100>;
   #declare cSand[6]  = color rgb <0.308, 0.167, 0.080>;
   #declare cSand[7]  = color rgb <0.388, 0.235, 0.063>;
   #declare cSand[8]  = color rgb <0.280, 0.175, 0.039>;
   #declare cSand[9]  = color rgb <0.461, 0.329, 0.139>;
   #declare cSand[10] = color rgb <0.322, 0.204, 0.110>;
   #declare cSand[11] = color rgb <0.369, 0.218, 0.092>;
   #declare cSand[12] = color rgb <0.206, 0.090, 0.008>;
   #declare cSand[13] = color rgb <0.249, 0.193, 0.084>;
   #declare cSand[14] = color rgb <0.241, 0.182, 0.053>;
   #declare cSand[15] = color rgb <0.190, 0.108, 0.002>;
   #declare cSand[16] = color rgb <0.104, 0.033, 0.004>;

   #declare cStone = array [30];
   #declare cStone[0]  = color rgb <0.788, 0.696, 0.663>;
   #declare cStone[1]  = color rgb <0.757, 0.741, 0.565>;
   #declare cStone[2]  = color rgb <0.754, 0.653, 0.629>;
   #declare cStone[3]  = color rgb <0.734, 0.733, 0.609>;
   #declare cStone[4]  = color rgb <0.694, 0.639, 0.455>;
   #declare cStone[5]  = color rgb <0.675, 0.584, 0.412>;
   #declare cStone[6]  = color rgb <0.616, 0.565, 0.392>;
   #declare cStone[7]  = color rgb <0.612, 0.573, 0.518>;
   #declare cStone[8]  = color rgb <0.608, 0.616, 0.431>;
   #declare cStone[9]  = color rgb <0.600, 0.490, 0.443>;
   #declare cStone[10] = color rgb <0.580, 0.510, 0.322>;
   #declare cStone[11] = color rgb <0.549, 0.557, 0.412>;
   #declare cStone[12] = color rgb <0.522, 0.435, 0.290>;
   #declare cStone[13] = color rgb <0.479, 0.378, 0.254>;
   #declare cStone[14] = color rgb <0.455, 0.435, 0.271>;
   #declare cStone[15] = color rgb <0.455, 0.400, 0.255>;
   #declare cStone[16] = color rgb <0.400, 0.384, 0.278>;
   #declare cStone[17] = color rgb <0.373, 0.341, 0.275>;
   #declare cStone[18] = color rgb <0.333, 0.310, 0.169>;
   #declare cStone[19] = color rgb <0.318, 0.329, 0.224>;
   #declare cStone[20] = color rgb <0.282, 0.302, 0.212>;
   #declare cStone[21] = color rgb <0.259, 0.224, 0.071>;
   #declare cStone[22] = color rgb <0.161, 0.165, 0.143>;
   #declare cStone[23] = color rgb <0.420, 0.402, 0.360>;
   #declare cStone[24] = color rgb <0.165, 0.141, 0.016>;
   //Sand
   #declare cSand = array [20];
   #declare cSand[0]  = color rgb <0.969, 0.875, 0.839>;
   #declare cSand[1]  = color rgb <0.894, 0.749, 0.678>;
   #declare cSand[2]  = color rgb <0.879, 0.778, 0.454>;
   #declare cSand[3]  = color rgb <0.865, 0.765, 0.740>;
   #declare cSand[4]  = color rgb <0.855, 0.706, 0.624>;
   #declare cSand[5]  = color rgb <0.850, 0.600, 0.400>;
   #declare cSand[6]  = color rgb <0.808, 0.667, 0.580>;
   #declare cSand[7]  = color rgb <0.788, 0.635, 0.463>;
   #declare cSand[8]  = color rgb <0.780, 0.675, 0.639>;
   #declare cSand[9]  = color rgb <0.761, 0.629, 0.539>;
   #declare cSand[10] = color rgb <0.722, 0.604, 0.510>;
   #declare cSand[11] = color rgb <0.669, 0.518, 0.392>;
   #declare cSand[12] = color rgb <0.596, 0.490, 0.408>;
   #declare cSand[13] = color rgb <0.549, 0.443, 0.384>;
   #declare cSand[14] = color rgb <0.541, 0.412, 0.353>;
   #declare cSand[15] = color rgb <0.490, 0.408, 0.302>;
   #declare cSand[16] = color rgb <0.404, 0.333, 0.294>;

// Color Definitions
// ---------------------------------------------------------------------------

#declare SURFACE_COLOR_SET = IRand(1,4,rPlanet);

#if (SURFACE_COLOR_SET=1)
   //Soil
   #declare cSoil = array [10];
   #declare cSoil[0] = color rgb <0.934, 0.933, 0.609>; //brown light fields
   #declare cSoil[1] = color rgb <0.580, 0.510, 0.322>;
   #declare cSoil[2] = color rgb <0.612, 0.573, 0.518>;
   #declare cSoil[3] = color rgb <0.659, 0.324, 0.071>;
   #declare cSoil[4] = color rgb <0.675, 0.484, 0.412>;
   #declare cSoil[5] = color rgb <0.694, 0.639, 0.455>;
   #declare cSoil[6] = color rgb <0.455, 0.400, 0.255>;
   #declare cSoil[7] = color rgb <0.522, 0.435, 0.290>;
   #declare cSoil[8] = color rgb <0.865, 0.741, 0.316>;
   #declare cSoil[9] = color rgb <0.533, 0.310, 0.169>;
   // Forrest
   #declare cForrest = array [10];
   #declare cForrest[0] = color rgb <0.212, 0.341, 0.024>;
   #declare cForrest[1] = color rgb <0.127, 0.251, 0.000>;
   #declare cForrest[2] = color rgb <0.475, 0.565, 0.290>;
   #declare cForrest[3] = color rgb <0.388, 0.573, 0.259>;
   #declare cForrest[4] = color rgb <0.600, 0.678, 0.400>;
   #declare cForrest[5] = color rgb <0.153, 0.329, 0.000>;
   #declare cForrest[6] = color rgb <0.369, 0.541, 0.208>;
   #declare cForrest[7] = color rgb <0.408, 0.627, 0.341>;
   #declare cForrest[8] = color rgb <0.263, 0.482, 0.196>;
   #declare cForrest[9] = color rgb <0.188, 0.286, 0.031>;
   // Fields
   #declare cFields = array [10];
   #declare cFields[0] = color rgb <0.757, 0.741, 0.565>;
   #declare cFields[1] = color rgb <0.616, 0.565, 0.392>;
   #declare cFields[2] = color rgb <0.608, 0.616, 0.431>;
   #declare cFields[3] = color rgb <0.549, 0.557, 0.412>;
   #declare cFields[4] = color rgb <0.455, 0.435, 0.271>;
   #declare cFields[5] = color rgb <0.400, 0.384, 0.278>;
   #declare cFields[6] = color rgb <0.600, 0.490, 0.443>;
   #declare cFields[7] = color rgb <0.261, 0.165, 0.043>;
   #declare cFields[8] = color rgb <0.282, 0.302, 0.212>;
   #declare cFields[9] = color rgb <0.318, 0.229, 0.124>;
   // Desert
   #declare cDesert = array [10];
   #declare cDesert[0] = color rgb <0.961, 0.929, 0.839>;
   #declare cDesert[1] = color rgb <0.541, 0.412, 0.353>;
   #declare cDesert[2] = color rgb <0.855, 0.706, 0.624>;
   #declare cDesert[3] = color rgb <0.596, 0.490, 0.408>;
   #declare cDesert[4] = color rgb <0.404, 0.333, 0.294>;
   #declare cDesert[5] = color rgb <0.490, 0.408, 0.302>;
   #declare cDesert[6] = color rgb <0.894, 0.749, 0.678>;
   #declare cDesert[7] = color rgb <0.780, 0.675, 0.639>;
   #declare cDesert[8] = color rgb <0.969, 0.918, 0.792>;
   #declare cDesert[9] = color rgb <0.822, 0.604, 0.410>;
   // Jungle
   #declare cJungle = array [10];
   #declare cJungle[0] = color rgb <0.827, 0.976, 0.643>;
   #declare cJungle[1] = color rgb <0.702, 0.808, 0.490>;
   #declare cJungle[2] = color rgb <0.643, 0.788, 0.424>;
   #declare cJungle[3] = color rgb <0.592, 0.741, 0.400>;
   #declare cJungle[4] = color rgb <0.502, 0.702, 0.329>;
   #declare cJungle[5] = color rgb <0.404, 0.588, 0.212>;
   #declare cJungle[6] = color rgb <0.388, 0.498, 0.204>;
   #declare cJungle[7] = color rgb <0.329, 0.514, 0.208>;
   #declare cJungle[8] = color rgb <0.263, 0.455, 0.145>;
   #declare cJungle[9] = color rgb <0.298, 0.710, 0.220>;
#end //SURFACE_COLOR_SET=1

#if (SURFACE_COLOR_SET=2)
   //Soil
   #declare cSoil = array [10];
   #declare cSoil[0] = color rgb <0.934, 0.933, 0.609>; //brown light fields
   #declare cSoil[1] = color rgb <0.580, 0.510, 0.322>;
   #declare cSoil[2] = color rgb <0.612, 0.573, 0.518>;
   #declare cSoil[3] = color rgb <0.659, 0.324, 0.071>;
   #declare cSoil[4] = color rgb <0.675, 0.484, 0.412>;
   #declare cSoil[5] = color rgb <0.694, 0.639, 0.455>;
   #declare cSoil[6] = color rgb <0.455, 0.400, 0.255>;
   #declare cSoil[7] = color rgb <0.522, 0.435, 0.290>;
   #declare cSoil[8] = color rgb <0.865, 0.741, 0.316>;
   #declare cSoil[9] = color rgb <0.533, 0.310, 0.169>;
   // Forrest
   #declare cForrest = array [10];
   #declare cForrest[0] = color rgb <0.212, 0.341, 0.024>;
   #declare cForrest[1] = color rgb <0.127, 0.251, 0.000>;
   #declare cForrest[2] = color rgb <0.475, 0.565, 0.290>;
   #declare cForrest[3] = color rgb <0.388, 0.573, 0.259>;
   #declare cForrest[4] = color rgb <0.600, 0.678, 0.400>;
   #declare cForrest[5] = color rgb <0.153, 0.329, 0.000>;
   #declare cForrest[6] = color rgb <0.369, 0.541, 0.208>;
   #declare cForrest[7] = color rgb <0.408, 0.627, 0.341>;
   #declare cForrest[8] = color rgb <0.263, 0.482, 0.196>;
   #declare cForrest[9] = color rgb <0.188, 0.286, 0.031>;
   // Fields
   #declare cFields = array [10];
   #declare cFields[0] = color rgb <0.757, 0.741, 0.565>;
   #declare cFields[1] = color rgb <0.616, 0.565, 0.392>;
   #declare cFields[2] = color rgb <0.608, 0.616, 0.431>;
   #declare cFields[3] = color rgb <0.549, 0.557, 0.412>;
   #declare cFields[4] = color rgb <0.455, 0.435, 0.271>;
   #declare cFields[5] = color rgb <0.400, 0.384, 0.278>;
   #declare cFields[6] = color rgb <0.600, 0.490, 0.443>;
   #declare cFields[7] = color rgb <0.261, 0.165, 0.043>;
   #declare cFields[8] = color rgb <0.282, 0.302, 0.212>;
   #declare cFields[9] = color rgb <0.318, 0.229, 0.124>;
   // Desert
   #declare cDesert = array [10];
   #declare cDesert[0] = color rgb <0.961, 0.929, 0.839>;
   #declare cDesert[1] = color rgb <0.541, 0.412, 0.353>;
   #declare cDesert[2] = color rgb <0.855, 0.706, 0.624>;
   #declare cDesert[3] = color rgb <0.596, 0.490, 0.408>;
   #declare cDesert[4] = color rgb <0.404, 0.333, 0.294>;
   #declare cDesert[5] = color rgb <0.490, 0.408, 0.302>;
   #declare cDesert[6] = color rgb <0.894, 0.749, 0.678>;
   #declare cDesert[7] = color rgb <0.780, 0.675, 0.639>;
   #declare cDesert[8] = color rgb <0.969, 0.918, 0.792>;
   #declare cDesert[9] = color rgb <0.822, 0.604, 0.410>;
   // Jungle
   #declare cJungle = array [10];
   #declare cJungle[0] = color rgb <0.827, 0.976, 0.643>;
   #declare cJungle[1] = color rgb <0.702, 0.808, 0.490>;
   #declare cJungle[2] = color rgb <0.643, 0.788, 0.424>;
   #declare cJungle[3] = color rgb <0.592, 0.741, 0.400>;
   #declare cJungle[4] = color rgb <0.502, 0.702, 0.329>;
   #declare cJungle[5] = color rgb <0.404, 0.588, 0.212>;
   #declare cJungle[6] = color rgb <0.388, 0.498, 0.204>;
   #declare cJungle[7] = color rgb <0.329, 0.514, 0.208>;
   #declare cJungle[8] = color rgb <0.263, 0.455, 0.145>;
   #declare cJungle[9] = color rgb <0.298, 0.710, 0.220>;
   //Soil

   //#declare cSoil = array [10];
   #declare cBase = cSoil[IRand(0,9,rColor)];
   #local c=0; #while (c<10)
      #declare cBaseNew = VariateColor(cBase, fColorDev, bMonoColor,rColor);
      #declare cBaseR = cBaseNew.red;     
      #declare cBaseG = cBaseR - RRand(0.050,0.100,rColor);
      #declare cBaseB = cBaseG - RRand(0.100,0.200,rColor);
      #declare cSoil[c] = color rgb <cBaseR, cBaseG, cBaseB>;
   #local c=c+1; #end
   // Forest
   //#declare cForrest = array [10];
   #declare cBase = cForrest[IRand(0,9,rColor)];
   #local c=0; #while (c<10)
      #declare cBaseNew = VariateColor(cBase, fColorDev, bMonoColor,rColor);
      #declare cBaseG = cBaseNew.green;     
      #declare cBaseR = cBaseG - RRand(0.050,0.150,rColor);
      #declare cBaseB = cBaseG - RRand(0.100,0.200,rColor);
      #declare cForrest[c] = color rgb <cBaseR, cBaseG, cBaseB>;
   #local c=c+1; #end
   // Fields
   //#declare cFields = array [10];
   #declare cBase = cFields[IRand(0,9,rColor)];
   #local c=0; #while (c<10)
      #declare cBaseNew = VariateColor(cBase, fColorDev, bMonoColor,rColor);
      #declare cBaseR = cBaseNew.red;     
      #declare cBaseG = cBaseR - RRand(0.050,0.100,rColor);
      #declare cBaseB = cBaseG - RRand(0.050,0.150,rColor);
      #declare cFields[c] = color rgb <cBaseR, cBaseG, cBaseB>;
   #local c=c+1; #end
   // Desert
   //#declare cDesert = array [10];
   #declare cBase = cDesert[IRand(0,9,rColor)];
   #local c=0; #while (c<10)
      #declare cBaseNew = VariateColor(cBase, fColorDev, bMonoColor,rColor);
      #declare cBaseR = cBaseNew.red;     
      #declare cBaseG = cBaseR - RRand(0.050,0.150,rColor);
      #declare cBaseB = cBaseG - RRand(0.100,0.150,rColor);
      #declare cDesert[c] = color rgb <cBaseR, cBaseG, cBaseB>;
   #local c=c+1; #end
   // Jungle
   //#declare cJungle = array [10];
   #declare cBase = cJungle[IRand(0,9,rColor)];
   #local c=0; #while (c<10)
      #declare cBaseNew = VariateColor(cBase, fColorDev, bMonoColor,rColor);
      #declare cBaseG = cBaseNew.green;     
      #declare cBaseR = cBaseG - RRand(0.100,0.200,rColor);
      #declare cBaseB = cBaseG - RRand(0.150,0.300,rColor);
      #declare cJungle[c] = color rgb <cBaseR, cBaseG, cBaseB>;
   #local c=c+1; #end
#end //SURFACE_COLOR_SET=2

#if (SURFACE_COLOR_SET=3)
   #declare rIntensity = RRand(0.9,1.1,rColor);
   //Soil
   #declare cSoil = array [10];
   #declare cBase = cSand[IRand(0,16,rColor)]*rIntensity;
   #local c=0; #while (c<10)
      #declare cSoil[c] = VariateColor(cBase, fColorDev, bMonoColor,rColor);
   #local c=c+1; #end
   
   // Forest
   #declare cForrest = array [10];
   #declare cBase = cGreen[IRand(0,28,rColor)]*rIntensity;
   #local c=0; #while (c<10)
      #declare cForrest[c] = VariateColor(cBase, fColorDev, bMonoColor,rColor);
   #local c=c+1; #end

   // Fields
   #declare cFields = array [10];
   #declare cBase = cStone[IRand(0,24,rColor)]*rIntensity;
   #local c=0; #while (c<10)
      #declare cFields[c] = VariateColor(cBase, fColorDev, bMonoColor,rColor);
   #local c=c+1; #end

   // Desert
   #declare cDesert = array [10];
   #declare cBase = cSand[IRand(0,16,rColor)]*rIntensity;
   #local c=0; #while (c<10)
      #declare cDesert[c] = VariateColor(cBase, fColorDev, bMonoColor,rColor);
   #local c=c+1; #end

   // Jungle
   #declare cJungle = array [10];
   #declare cBase = cGreen[IRand(0,28,rColor)]*rIntensity;
   #local c=0; #while (c<10)
      #declare cJungle[c] = VariateColor(cBase, fColorDev, bMonoColor,rColor);
   #local c=c+1; #end

#end //SURFACE_COLOR_SET=3

#if (SURFACE_COLOR_SET>=4)
   #declare local_color_deviation = RRand(0,20,rColor);
   //Soil
   #declare cSoil = array [10];
   #declare cBase = VariateColor(Soil, fColorDev, bMonoColor,rColor);
   #local c=0; #while (c<10)
      #declare cSoil[c] = VariateColor(cBase, local_color_deviation, bMonoColor,rColor);
   #local c=c+1; #end

   // Forrest
   #declare cForrest = array [10];
   #declare cBase = VariateColor(Forrest, fColorDev, bMonoColor,rColor);
   #local c=0; #while (c<10)
      #declare cForrest[c] = VariateColor(cBase, local_color_deviation, bMonoColor,rColor);
   #local c=c+1; #end

   // Fields
   #declare cFields = array [10];
   #declare cBase = VariateColor(Field, fColorDev, bMonoColor,rColor);
   #local c=0; #while (c<10)
      #declare cFields[c] = VariateColor(cBase, local_color_deviation, bMonoColor,rColor);
   #local c=c+1; #end

   // Desert
   #declare cDesert = array [10];
   #declare cBase = VariateColor(cBase, fColorDev, bMonoColor,rColor);
   #local c=0; #while (c<10)
      #declare cDesert[c] = VariateColor(cBase, local_color_deviation, bMonoColor,rColor);
   #local c=c+1; #end

   // Jungle
   #declare cJungle = array [10];
   #declare cBase = VariateColor(Jungle, fColorDev, bMonoColor,rColor);
   #local c=0; #while (c<10)
      #declare cJungle[c] = VariateColor(cBase, local_color_deviation, bMonoColor,rColor);
   #local c=c+1; #end

#end //SURFACE_COLOR_SET=4

// ---------------------------------------------------------------------------
// Surface Pigments and Textures
// ---------------------------------------------------------------------------
#declare SURFACE_REVISION = IRand(1,2,rPlanet);
#declare MAX_LANDSCAPE_ITERATION = IRand(10,40,rPlanet);
#declare MAX_LANDSCAPE_ZONES = IRand(10,20,rPlanet);
#declare MAX_CLIMATE_ZONES = IRand(10,20,rPlanet);

#if (SURFACE_REVISION=1)

// Base pigments
// ---------------------------------------------------------------------------
#declare P_SurfaceBase    = pigment { Soil filter 0 }
#declare P_OceanBase      = pigment { Soil filter 1 }
#declare P_ArcticBase     = pigment { color rgb <1,1,1> filter 0 }
#declare P_BaseTrasparent = pigment { color rgb <1,1,1> filter 1 } //transparent

// Landscape Zones pigment macro
// ---------------------------------------------------------------------------
#macro mMicroStructure_Arid()
   #local fTurbulence = RRand(4.0, 7.0, rColor);
   #local fPhase = RRand(0.20, 0.9, rColor);
   #local fLambda = RRand(5.0,7.0,rColor); // controls coastline
   #local fOmega = RRand(0.50,0.60,rColor); // controls islands
   #local fScale = RRand(0.001, 0.01, rColor);
   #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rColor);
   #local iPattern = IRand(5, 16, rColor);
   GetPattern(iPattern) 
   turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
   color_map {
      #local I=0; #while(I<1)
         #local iZone  = IRand(1,3,rColor);
         #local iColor = IRand(0,9,rColor);
         #switch(iZone)
            #case (1) #declare cColor = cDesert[iColor];  #break
            #case (2) #declare cColor = cForrest[iColor]; #break
            #case (3) #declare cColor = cJungle[iColor];  #break
         #end
         #local cPigmentColor = VariateColor(cColor, fColorDev, bMonoColor, rColor);
         [I cPigmentColor ]
      #local I=I+1/fSteps; #end
   } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
#end //macro

#macro mMicroStructure_Mediterran()
   #local fTurbulence = RRand(4.0, 7.0, rColor);
   #local fPhase = RRand(0.20, 0.9, rColor);
   #local fLambda = RRand(4.0,10.0,rColor); // controls coastline
   #local fOmega = RRand(0.50,0.70,rColor); // controls islands
   #local fScale = RRand(0.001, 0.01, rColor);
   #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rColor);
   #local iPattern = IRand(5, 16, rColor);
   GetPattern(iPattern) 
   turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
   color_map {
      #local I=0; #while(I<1)
         #local iZone  = IRand(1,3,rColor);
         #local iColor = IRand(0,9,rColor);
         #switch(iZone)
            #case (1) #declare cColor = cForrest[iColor]; #break
            #case (2) #declare cColor = cSoil[iColor];    #break
            #case (3) #declare cColor = cFields[iColor];  #break
         #end
         #local cPigmentColor = VariateColor(cColor, fColorDev, bMonoColor, rColor);
         [I cPigmentColor ]
      #local I=I+1/fSteps; #end
   } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
#end //macro

#macro mMicroStructure_Moderate()
   #local fTurbulence = RRand(4.0, 7.0, rColor);
   #local fPhase = RRand(0.20, 0.9, rColor);
   #local fLambda = RRand(4.0,10.0,rColor); // controls coastline
   #local fOmega = RRand(0.50,0.70,rColor); // controls islands
   #local fScale = RRand(0.001, 0.01, rColor);
   #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rColor);
   #local iPattern = IRand(5, 16, rColor);
   GetPattern(iPattern) 
   turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
   color_map {
      #local I=0; #while(I<1)
         #local iZone  = IRand(1,3,rColor);
         #local iColor = IRand(0,9,rColor);
         #switch(iZone)
            #case (1) #declare cColor = cForrest[iColor]; #break
            #case (2) #declare cColor = cSoil[iColor];    #break
            #case (3) #declare cColor = cFields[iColor];  #break
         #end
         #local cPigmentColor = VariateColor(cColor, fColorDev, bMonoColor, rColor);
         [I cPigmentColor ]
      #local I=I+1/fSteps; #end
   } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
#end //macro

// Landscape Zones gradient (longitudonal)
// ---------------------------------------------------------------------------
#macro mArid()
   #local fSteps           = RRand(MAX_LANDSCAPE_ZONES/2, MAX_LANDSCAPE_ZONES, rColor);
   #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
   #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
   #local fGradXOmega      = RRand(0.50, 0.60, rColor);
   #local fGradXLambda     = RRand(3, 5, rColor);
   #local fGradScale       = fPlanetRadius;
   gradient x pigment_map {
      #local I=0; #while(I<1)
         #local P_MicroStructure_Arid = pigment { mMicroStructure_Arid() };
         [I+fJitter P_MicroStructure_Arid ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Arid ]
      #local I=I+1/fSteps; #end
   } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
#end
//#declare P_Surface_Arid  = pigment { mArid() }

#macro mMediterran()
   #local fSteps           = RRand(MAX_LANDSCAPE_ZONES/2, MAX_LANDSCAPE_ZONES, rColor);
   #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
   #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
   #local fGradXOmega      = RRand(0.50, 0.60, rColor);
   #local fGradXLambda     = RRand(3, 5, rColor);
   #local fGradScale       = fPlanetRadius;
   gradient x pigment_map {
      #local I=0; #while(I<1)
         #local P_MicroStructure_Mediterran = pigment { mMicroStructure_Mediterran() };
         [I+fJitter P_MicroStructure_Mediterran ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Mediterran ]
      #local I=I+1/fSteps; #end
   } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
#end
//#declare P_Surface_Mediterran  = pigment { mMediterran() }

#macro mModerate()
   #local fSteps           = RRand(MAX_LANDSCAPE_ZONES/2, MAX_LANDSCAPE_ZONES, rColor);
   #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
   #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
   #local fGradXOmega      = RRand(0.50, 0.60, rColor);
   #local fGradXLambda     = RRand(3, 5, rColor);
   #local fGradScale       = fPlanetRadius;
   gradient x pigment_map {
      #local I=0; #while(I<1)
         #local P_MicroStructure_Moderate = pigment { mMicroStructure_Moderate() };
         [I+fJitter P_MicroStructure_Moderate ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Moderate ]
      #local I=I+1/fSteps; #end
   } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
#end
//#declare P_Surface_Moderate  = pigment { mModerate() }

// Climate Zones gradient (latitudonal)
// ---------------------------------------------------------------------------
#declare fClimateZones    = RRand(MAX_CLIMATE_ZONES/2, MAX_CLIMATE_ZONES, rColor);
#declare fGradYTurbulence = RRand(0.01, 0.09, rColor);
#declare fGradYOmega      = RRand(0.35, 0.55, rColor);
#declare fGradYLambda     = RRand(3, 4, rColor);
#declare fGradScale       = 2*fPlanetRadius;
#declare fJitter          = RRand(0.05,0.10,rColor);
#declare P_SurfaceClimateGradient = pigment { gradient y pigment_map { //step 1/5=0.2; transition step/4=0.05
   #local I=0; #while(I<1)
      #local iZone  = IRand(1,3,rColor);
      #switch(iZone)
         #case (1) #declare P_Surface = pigment { mModerate() };   #break
         #case (2) #declare P_Surface = pigment { mMediterran() }; #break
         #case (3) #declare P_Surface = pigment { mArid() };       #break
      #end
      [I+fJitter P_Surface scale 1/fGradScale ] [min(1,I+1/fClimateZones-fJitter) P_Surface scale 1/fGradScale ]
   #local I=I+1/fClimateZones; #end
} turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda scale fGradScale phase 0.5 }

// Ocean pigment
// ---------------------------------------------------------------------------
#declare ocean_base_color = rgb <0.063, 0.149, 0.322>*RRand(0.5,1.0,rOcean);
#declare fSteps      = RRand(10, 20, rOcean);
#declare fJitter     = RRand(1/fSteps/4,1/fSteps/3,rOcean);
#declare fTurbulence = RRand(1.00, 2.00, rOcean);
#declare fOmega      = RRand(0.30, 0.60, rOcean);
#declare fLambda     = RRand(3, 4, rOcean);
#declare fScale      = RRand(0.1, 5, rOcean);
#declare fColorDev   = RRand(0.7,0.9,rOcean);
#declare iPattern    = IRand(5, 17, rOcean); //6-bumps
#declare P_OceanTexture = pigment { //bumps
   GetPattern(iPattern)  
   color_map { 
   #local I=0; #while(I<1)
      #local cColor = ocean_base_color*(1-I*fColorDev);
      [min(1,I) color cColor ]
   #local I=I+1/fSteps; #end
} turbulence fTurbulence omega fOmega lambda fLambda scale fScale*fPlanetRadius }

// Planet texture
// ---------------------------------------------------------------------------
#declare fSurfaceTurbulence = RRand(0.30, 0.90, rStructure); // complexity of continents
#declare fSurfaceOmega = RRand(0.30, 0.45, rStructure); // increses disconnected continents
#declare fSurfaceLambda = RRand(3.0, 4.5, rStructure); // increses coastline roughness
#declare fSurfacePhase = RRand(0.0, 0.4, rStructure); // different ocean shape
#declare fSurfacePercent = RRand(0.4, 0.8, rStructure); // approximate portion of land versus ocean
#declare fSurfaceScale = 0.5*fPlanetRadius;
#declare iSurfacePattern = IRand(4,18,rStructure); //1-5
#declare fSurfaceRotation = RRand(0, 360, rStructure);
#declare fRotateX = RRand(0,360,rStructure);
#declare fRotateY = RRand(0,360,rStructure);
#declare fRotateZ = RRand(0,360,rStructure);
#declare T_PlanetSurface = texture { pigment { //1-bozo; 2-bumps; 3-dents; 4-spotted; 5-wrinkles
   GetPattern(iSurfacePattern)
   pigment_map {
      [0.00 P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land ini
      [fSurfacePercent P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land end
      [fSurfacePercent P_OceanTexture scale 1/fSurfaceScale ] //ocean ini
      [1.00 P_OceanTexture scale 1/fSurfaceScale ] //ocean end
   }
turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }

#declare T_TestContinents = texture { pigment {
   GetPattern(iSurfacePattern)
   pigment_map {
      [0.00 P_SurfaceBase scale 1/fSurfaceScale ] //land ini
      [fSurfacePercent P_SurfaceBase scale 1/fSurfaceScale ] //land end
      [fSurfacePercent P_OceanBase scale 1/fSurfaceScale ] //ocean ini
      [1.00 P_OceanBase scale 1/fSurfaceScale ] //ocean end
   }
turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }

#declare shallow_coastline = 0;
#declare fOceanDarkness = RRand(0.3, 1.0, rOcean);
#declare T_OceanDepth = texture { pigment {
   GetPattern(iSurfacePattern)
   pigment_map {
      [0.00 color rgbft<0,0,0,0,1> ] //land ini
      [fSurfacePercent color rgbft<0,0,0,0,1> scale 1/fSurfaceScale ] //land end
      #if (shallow_coastline)
         [fSurfacePercent rgb ocean_base_color+<0,1.5,0> filter 0 transmit 0.5 scale 1/fSurfaceScale ] //coastline
         [fSurfacePercent+0.01 rgb ocean_base_color filter 0 transmit 0 scale 1/fSurfaceScale ] //coastline
      #end
      [1.00 color rgb ocean_base_color*RRand(0.3,0.9,rOcean) filter 0 transmit 0 scale 1/fSurfaceScale ] //deep ocean
   }
turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }

// Arctic Pattern
// ---------------------------------------------------------------------------
#macro mMicroStructure_Arctic()
   #local fTurbulence = RRand(4.0, 7.0, rIce);
   #local fPhase = RRand(0.20, 1.0, rIce);
   #local fLambda = RRand(5.0,7.0,rIce); // controls coastline
   #local fOmega = RRand(0.50,0.60,rIce); // controls islands
   #local fScale = RRand(0.01, 0.1, rIce);
   #local fSteps = RRand(20, 40, rIce);
   #local iPattern = IRand(4, 18, rIce);
   GetPattern(iPattern) 
   turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
   color_map {
      #local I=0; #while(I<1)
         #local iColor = color rgb <0.95, 0.95, 1.00>;
         #local cColor = VariateColor(iColor, fColorDev, bMonoColor, rIce);
         [I cColor ]
      #local I=I+1/fSteps; #end
   } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
#end //macro

#macro mArctic()
   #local fSteps           = RRand(3, 5, rIce);
   #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rIce);
   #local fGradXTurbulence = RRand(0.10, 1.00, rIce);
   #local fGradXOmega      = RRand(0.45, 0.55, rIce);
   #local fGradXLambda     = RRand(3, 5, rIce);
   #local fGradScale       = fPlanetRadius;
   gradient x pigment_map {
      #local I=0; #while(I<1)
         #local P_MicroStructure_Arctic = pigment { mMicroStructure_Arctic() };
         [I+fJitter P_MicroStructure_Arctic ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Arctic ]
      #local I=I+1/fSteps; #end
   } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
#end

// Arctic texture
// ---------------------------------------------------------------------------
#declare fGradYTurbulence = RRand(0.01, 0.10, rIce);
#declare fGradYOmega      = RRand(0.35, 0.45, rIce);
#declare fGradYLambda     = RRand(4, 6, rIce);
#declare fArcticExtension = RRand(0.02 , 0.03, rIce);
#declare fGradScale       = 2.1*fPlanetRadius;
#declare T_ArcticTexture  = texture { pigment { gradient y pigment_map {
   #local P_Surface_Arctic  = pigment { mArctic() }
   [0.00 P_Surface_Arctic scale 1/fGradScale]                [fArcticExtension P_Surface_Arctic scale 1/fGradScale] //arctic
   [fArcticExtension   P_BaseTrasparent scale 1/fGradScale ] [1-fArcticExtension P_BaseTrasparent scale 1/fGradScale ] //transparent
   #local P_Surface_Arctic  = pigment { mArctic() }
   [1-fArcticExtension P_Surface_Arctic scale 1/fGradScale]  [1.00 P_Surface_Arctic scale 1/fGradScale] //arctic
} turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda scale fGradScale phase 0.5 }
finish { surface_finish } }

#end //SURFACE_REVISION=1

#if (SURFACE_REVISION=2)

// Base pigments
// ---------------------------------------------------------------------------
#declare P_SurfaceBase    = pigment { Soil filter 0 }
#declare P_OceanBase      = pigment { Soil filter 1 }
#declare P_ArcticBase     = pigment { color rgb <1,1,1> filter 0 }
#declare P_BaseTrasparent = pigment { color rgb <1,1,1> filter 1 } //transparent

// Landscape Zones pigment macro
// ---------------------------------------------------------------------------
#macro mMicroStructure_Arid()
   #local fTurbulence = RRand(4.0, 7.0, rColor);
   #local fPhase = RRand(0.20, 0.9, rColor);
   #local fLambda = RRand(5.0,7.0,rColor); // controls coastline
   #local fOmega = RRand(0.50,0.60,rColor); // controls islands
   #local fScale = RRand(0.001, 0.01, rColor);
   #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rColor);
   #local iPattern = IRand(5, 17, rColor);
   GetPattern(iPattern) 
   turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
   color_map {
      #local iZone  = IRand(1,3,rColor);
      #local iColor = IRand(0,9,rColor);
      #switch(iZone)
         #case (1) #declare cColor = cDesert[iColor];  #break
         #case (2) #declare cColor = cForrest[iColor]; #break
         #case (3) #declare cColor = cJungle[iColor];  #break
      #end
      #local I=0; #while(I<1)
         #local cPigmentColor = VariateColor(cColor, fColorDev, bMonoColor, rColor);
         [I cPigmentColor ]
      #local I=I+1/fSteps; #end
   } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
#end //macro

#macro mMicroStructure_Mediterran()
   #local fTurbulence = RRand(4.0, 7.0, rColor);
   #local fPhase = RRand(0.20, 0.9, rColor);
   #local fLambda = RRand(4.0,10.0,rColor); // controls coastline
   #local fOmega = RRand(0.50,0.70,rColor); // controls islands
   #local fScale = RRand(0.001, 0.01, rColor);
   #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rColor);
   #local iPattern = IRand(5, 17, rColor);
   GetPattern(iPattern) 
   turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
   color_map {
      #local iZone  = IRand(1,3,rColor);
      #local iColor = IRand(0,9,rColor);
      #switch(iZone)
         #case (1) #declare cColor = cForrest[iColor]; #break
         #case (2) #declare cColor = cSoil[iColor];    #break
         #case (3) #declare cColor = cFields[iColor];  #break
      #end
      #local I=0; #while(I<1)
         #local cPigmentColor = VariateColor(cColor, fColorDev, bMonoColor, rColor);
         [I cPigmentColor ]
      #local I=I+1/fSteps; #end
   } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
#end //macro

#macro mMicroStructure_Moderate()
   #local fTurbulence = RRand(4.0, 7.0, rColor);
   #local fPhase = RRand(0.20, 0.9, rColor);
   #local fLambda = RRand(4.0,10.0,rColor); // controls coastline
   #local fOmega = RRand(0.50,0.70,rColor); // controls islands
   #local fScale = RRand(0.001, 0.01, rColor);
   #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rColor);
   #local iPattern = IRand(5, 17, rColor);
   GetPattern(iPattern) 
   turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
   color_map {
      #local iZone  = IRand(1,3,rColor);
      #local iColor = IRand(0,9,rColor);
      #switch(iZone)
         #case (1) #declare cColor = cForrest[iColor]; #break
         #case (2) #declare cColor = cSoil[iColor];    #break
         #case (3) #declare cColor = cFields[iColor];  #break
      #end
      #local I=0; #while(I<1)
         #local cPigmentColor = VariateColor(cColor, fColorDev, bMonoColor, rColor);
         [I cPigmentColor ]
      #local I=I+1/fSteps; #end
   } scale fScale*fPlanetRadius rotate <RRand(0,360,rColor),RRand(0,360,rColor),RRand(0,360,rColor)> //}
#end //macro

// Landscape Zones gradient (longitudonal)
// ---------------------------------------------------------------------------
#macro mArid()
   #local fSteps           = RRand(MAX_LANDSCAPE_ZONES/2, MAX_LANDSCAPE_ZONES, rColor);
   #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
   #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
   #local fGradXOmega      = RRand(0.50, 0.60, rColor);
   #local fGradXLambda     = RRand(3, 5, rColor);
   #local fGradScale       = fPlanetRadius;
   gradient x pigment_map {
      #local I=0; #while(I<1)
         #local P_MicroStructure_Arid = pigment { mMicroStructure_Arid() };
         [I+fJitter P_MicroStructure_Arid ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Arid ]
      #local I=I+1/fSteps; #end
   } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
#end
//#declare P_Surface_Arid  = pigment { mArid() }

#macro mMediterran()
   #local fSteps           = RRand(MAX_LANDSCAPE_ZONES/2, MAX_LANDSCAPE_ZONES, rColor);
   #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
   #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
   #local fGradXOmega      = RRand(0.50, 0.60, rColor);
   #local fGradXLambda     = RRand(3, 5, rColor);
   #local fGradScale       = fPlanetRadius;
   gradient x pigment_map {
      #local I=0; #while(I<1)
         #local P_MicroStructure_Mediterran = pigment { mMicroStructure_Mediterran() };
         [I+fJitter P_MicroStructure_Mediterran ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Mediterran ]
      #local I=I+1/fSteps; #end
   } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
#end
//#declare P_Surface_Mediterran  = pigment { mMediterran() }

#macro mModerate()
   #local fSteps           = RRand(MAX_LANDSCAPE_ZONES/2, MAX_LANDSCAPE_ZONES, rColor);
   #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rColor);
   #local fGradXTurbulence = RRand(0.10, 1.00, rColor);
   #local fGradXOmega      = RRand(0.50, 0.60, rColor);
   #local fGradXLambda     = RRand(3, 5, rColor);
   #local fGradScale       = fPlanetRadius;
   gradient x pigment_map {
      #local I=0; #while(I<1)
         #local P_MicroStructure_Moderate = pigment { mMicroStructure_Moderate() };
         [I+fJitter P_MicroStructure_Moderate ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Moderate ]
      #local I=I+1/fSteps; #end
   } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
#end
//#declare P_Surface_Moderate  = pigment { mModerate() }

// Climate Zones gradient (latitudonal)
// ---------------------------------------------------------------------------
#declare fClimateZones    = RRand(MAX_CLIMATE_ZONES/2, MAX_CLIMATE_ZONES, rColor);
#declare fGradYTurbulence = RRand(0.01, 0.09, rColor);
#declare fGradYOmega      = RRand(0.35, 0.55, rColor);
#declare fGradYLambda     = RRand(3, 4, rColor);
#declare fGradScale       = 2*fPlanetRadius;
#declare fJitter          = RRand(0.05,0.10,rColor);
#declare P_SurfaceClimateGradient = pigment { gradient y pigment_map { //step 1/5=0.2; transition step/4=0.05
   #local I=0; #while(I<1)
      #local iZone  = IRand(1,3,rColor);
      #switch(iZone)
         #case (1) #declare P_Surface = pigment { mModerate() };   #break
         #case (2) #declare P_Surface = pigment { mMediterran() }; #break
         #case (3) #declare P_Surface = pigment { mArid() };       #break
      #end
      [I+fJitter P_Surface scale 1/fGradScale ] [min(1,I+1/fClimateZones-fJitter) P_Surface scale 1/fGradScale ]
   #local I=I+1/fClimateZones; #end
} turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda scale fGradScale phase 0.5 }

// Planet texture
// ---------------------------------------------------------------------------
#declare fSurfaceTurbulence = RRand(0.30, 0.90, rStructure); // complexity of continents
#declare fSurfaceOmega = RRand(0.30, 0.45, rStructure); // increses disconnected continents
#declare fSurfaceLambda = RRand(3.5, 6.5, rStructure); // increses coastline roughness
#declare fSurfacePhase = RRand(0.0, 0.4, rStructure); // different ocean shape
#declare fSurfacePercent = RRand(0.4, 0.8, rStructure); // approximate portion of land versus ocean
#declare fSurfaceScale = 0.5*fPlanetRadius;
#declare iSurfacePattern = IRand(4,18,rStructure); //1-5
#declare fSurfaceRotation = RRand(0, 360, rStructure);
#declare fRotateX = RRand(0,360,rStructure);
#declare fRotateY = RRand(0,360,rStructure);
#declare fRotateZ = RRand(0,360,rStructure);
#declare T_PlanetSurface = texture { pigment { //1-bozo; 2-bumps; 3-dents; 4-spotted; 5-wrinkles
   GetPattern(iSurfacePattern)
   pigment_map {
      [0.00 P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land ini
      [fSurfacePercent P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land end
      [fSurfacePercent transmit 1 ] //ocean ini
      [1.00 transmit 1 ] //ocean end
   }
turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }

#declare T_TestContinents = texture { pigment {
   GetPattern(iSurfacePattern)
   pigment_map {
      [0.00 P_SurfaceBase scale 1/fSurfaceScale ] //land ini
      [fSurfacePercent P_SurfaceBase scale 1/fSurfaceScale ] //land end
      [fSurfacePercent color rgb <0,0,0> ] //ocean ini
      [1.00 color rgb <0,0,0> ] //ocean end
   }
turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }

// Ocean texture
// ---------------------------------------------------------------------------
#declare ocean_base_color = rgb <0.063, 0.149, 0.322>*RRand(0.5,1.0,rOcean);

#declare fSteps      = RRand(3, 10, rOcean);
#declare fJitter     = RRand(1/fSteps/4,1/fSteps/3,rOcean);
#declare fTurbulence = RRand(1, 5, rOcean);
#declare fOmega      = RRand(0.30, 0.60, rOcean);
#declare fLambda     = RRand(3, 4, rOcean);
#declare fScale      = RRand(10, 50, rOcean);
#declare fColorDev   = RRand(0.1,4,rOcean);
#declare iPattern    = IRand(5, 17, rOcean); //6-bumps
#declare P_OceanTexture = pigment { //bumps
   GetPattern(iPattern)  
   color_map { 
   #local I=0; #while(I<1)
      #local cColor = surface_color_chromo(ocean_base_color,fColorDev,rOcean)*(1-I);
      [min(1,I) color cColor ]
   #local I=I+1/fSteps; #end
} turbulence fTurbulence omega fOmega lambda fLambda scale fScale*fPlanetRadius }

#declare T_OceanSurface = texture { pigment { GetPattern(iSurfacePattern)
   pigment_map {
      [0.00 transmit 1 ] //land ini
      [fSurfacePercent transmit 1 ] //land end
      [fSurfacePercent P_OceanTexture scale 1/fSurfaceScale ] //ocean ini
      [1.00 P_OceanTexture scale 1/fSurfaceScale ] //ocean end
   }
turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }

#declare fOceanDarkness = RRand(0.8, 1.0, rOcean);
#declare fSteps      = RRand(3, 10, rOcean);
#declare fJitter     = RRand(1/fSteps/4,1/fSteps/3,rOcean);
#declare fTurbulence = RRand(1, 5, rOcean);
#declare fOmega      = RRand(0.30, 0.60, rOcean);
#declare fLambda     = RRand(3, 4, rOcean);
#declare fScale      = RRand(10, 50, rOcean);
#declare iPattern    = IRand(5, 17, rOcean); //6-bumps
#declare P_OceanDarken = pigment { GetPattern(iPattern)  
   color_map { 
   #local I=0; #while(I<1)
      #local cColor = ocean_base_color*(1-I)*fOceanDarkness;
      [min(1,I) color cColor transmit RRand(0.5,1,rOcean)]
   #local I=I+1/fSteps; #end
} turbulence fTurbulence omega fOmega lambda fLambda scale fScale*fPlanetRadius }

#declare shallow_coastline = IRand(0,1,rPlanet);

#declare T_OceanDepth = texture { pigment {
   GetPattern(iSurfacePattern)
   pigment_map {
      [0.00 transmit 1 ] //land ini
      [fSurfacePercent transmit 1 ] //land end
      #if (shallow_coastline)
         [fSurfacePercent rgb ocean_base_color+<0,1.5,0.5> filter 0 transmit 0.5 scale 1/fSurfaceScale ] //coastline
         [fSurfacePercent+0.01 P_OceanDarken scale 1/fSurfaceScale ] //coastline
      #end
      [1.00 P_OceanDarken scale 1/fSurfaceScale ] //deep ocean
   }
turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }

// Arctic Pattern
// ---------------------------------------------------------------------------
#macro mMicroStructure_Arctic()
   #local fTurbulence = RRand(4.0, 7.0, rIce);
   #local fPhase      = RRand(0.20, 1.0, rIce);
   #local fLambda     = RRand(5.0,7.0,rIce); // controls coastline
   #local fOmega      = RRand(0.50,0.60,rIce); // controls islands
   #local fScale      = RRand(0.01, 0.1, rIce);
   #local fSteps      = RRand(20, 40, rIce);
   #local iPattern    = IRand(4, 18, rIce);
   #local fColorDev   = RRand(30,90,rIce);
   GetPattern(iPattern) 
   turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
   color_map {
      #local I=0; #while(I<1)
         #local vColor = color rgb <0.95, 0.95, 1.00>;
         #local cColor = surface_color_mono(vColor, fColorDev, rIce);
         [I cColor ]
      #local I=I+1/fSteps; #end
   } scale fScale*fPlanetRadius rotate <RRand(0,360,rIce),RRand(0,360,rIce),RRand(0,360,rIce)> //}
#end //macro

#macro mArctic()
   #local fSteps           = RRand(3, 5, rIce);
   #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rIce);
   #local fGradXTurbulence = RRand(0.10, 1.00, rIce);
   #local fGradXOmega      = RRand(0.45, 0.55, rIce);
   #local fGradXLambda     = RRand(3, 5, rIce);
   #local fGradScale       = fPlanetRadius;
   gradient x pigment_map {
      #local I=0; #while(I<1)
         #local P_MicroStructure_Arctic = pigment { mMicroStructure_Arctic() };
         [I+fJitter P_MicroStructure_Arctic ] [min(1,I+1/fSteps-fJitter) P_MicroStructure_Arctic ]
      #local I=I+1/fSteps; #end
   } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
#end

// Arctic texture
#declare fGradYTurbulence = RRand(0.01, 0.10, rIce);
#declare fGradYOmega      = RRand(0.35, 0.45, rIce);
#declare fGradYLambda     = RRand(4, 6, rIce);
#declare fArcticExtension = RRand(0.02 , 0.03, rIce);
#declare fGradScale       = 2.1*fPlanetRadius;
#declare T_ArcticTexture  = texture { pigment { gradient y pigment_map {
   #local P_Surface_Arctic  = pigment { mArctic() }
   [0.00 P_Surface_Arctic scale 1/fGradScale]                [fArcticExtension P_Surface_Arctic scale 1/fGradScale] //arctic
   [fArcticExtension   P_BaseTrasparent scale 1/fGradScale ] [1-fArcticExtension P_BaseTrasparent scale 1/fGradScale ] //transparent
   #local P_Surface_Arctic  = pigment { mArctic() }
   [1-fArcticExtension P_Surface_Arctic scale 1/fGradScale]  [1.00 P_Surface_Arctic scale 1/fGradScale] //arctic
} turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda scale fGradScale phase 0.5 }
finish { surface_finish } }

// River texture
// ---------------------------------------------------------------------------
#macro mRiver(iSteps, fRiverRadius)
   #declare oRiver = sphere { 0, fRiverRadius } 
   #declare fAngularDistance = 360/((fPlanetRadius*2*pi)/(fRiverRadius/2));
   object { union {
      #local fAngleX = 0;
      #local fAngleY = 0;
      #local vDirectionUV = vnormalize(<RRand(-1,1,rRiver),RRand(-1,1,rRiver)>); //initial direction
	   #local fDirectionChangeMax = 1;
	   #local i=0; #while (i<iSteps/(fRiverRadius/50)) //river length
	      #if ( (render_quality=1) | ((render_quality=0) & (mod(i,2)=0)) ) //render samples only
	      //#else //render full
   	      #if (mod(i,10)=0) //change in river direction
               #local vDirectionUV = vnormalize(<vDirectionUV.u+RRand(0,fDirectionChangeMax,rRiver),vDirectionUV.v+RRand(0,fDirectionChangeMax,rRiver)>); //curvature
            #end
   	      #if (mod(i,50)=0) //change in river direction
               #local vDirectionUV = vnormalize(<vDirectionUV.u+RRand(-fDirectionChangeMax,fDirectionChangeMax,rRiver),vDirectionUV.v+RRand(-fDirectionChangeMax,fDirectionChangeMax,rRiver)>); //curvature
            #end
         #end //render samples
	      #local fJitter = RRand(0.5,1.0,rRiver); //irregularity
	      #local fAngleX = fAngleX+RRand(0.9,1.5,rRiver)*fAngularDistance*vDirectionUV.x*fJitter; //advancement
	      #local fAngleY = fAngleY+RRand(0.9,1.5,rRiver)*fAngularDistance*vDirectionUV.y*fJitter;
         object { oRiver scale RRand(0.1,1.5,rRiver) translate <0,0,fPlanetRadius> rotate <fAngleX, fAngleY, 0> }
      #local i=i+1; #end
   }
   color rgb <0,0,0> transmit 1 // outside object = surface
   ocean_base_color transmit 0 // inside object = river
   } 
   #local fRotateX = RRand(10,90,rRiver);
   #local fRotateY = RRand(0,360,rRiver);
   #local fRotateZ = RRand(0,360,rRiver);
   rotate <fRotateX, fRotateY, fRotateZ> //geographical position
#end //macro

#macro T_River()
   #local I=0; #while(I<NUM_RIVERS)
      #local iRiverLength = IRand(200,400,rRiver);
      #local fRiverWidth = RRand(10,40, rRiver); 
      #local P_River = pigment { mRiver(iRiverLength, fRiverWidth) };
      texture { pigment { P_River } finish { surface_finish } }
   #local I=I+1; #end
#end //macro

// Lights texture
// ---------------------------------------------------------------------------
#ifndef (LIGHT_BASE_COLOR) #declare cLightsBase = color rgb <1,1,0>; #else #declare cLightsBase = LIGHT_BASE_COLOR; #end

#macro mLightBase()
   #local fIntensity = RRand(10,30,rLight);
   #local fDensity = RRand(0.5,0.9,rLight);
   [0.0 transmit 1 ] // unlit area
   [fDensity cLightsBase*fIntensity ] // controls light density; 0.1 =high, 0.9=low
#end

#macro mLightmap(fExtension)
   #local fScale = RRand(20,40,rLight);
   #local iPattern = IRand(1, 20, rLight);
   [0.0 GetPattern2(iPattern) pigment_map { mLightBase() } scale fScale turbulence 0]  // controls spread
   [fExtension rgb 0 transmit 1 ] // controls max lights extension; 0=no lights; 1=full lights
#end

#macro mLight()
   #local fPercent = RRand(0.5,0.6,rLight);
   #local fScale = RRand(0.01, 0.2, rLight);
   #local fExtension = RRand(0.01,0.3,rLight);
   #local iPattern = IRand(6, 12, rLight);
   #local fTurbulence = 0; //RRand(0.0, 7.0, rLight);
   #local fPhase = 0; //RRand(0.20, 0.90, rLight);
   #local fLambda = 0; //RRand(0.0,1.0,rLight); // controls coastline
   #local fOmega = 0; //RRand(0.00,0.30,rLight); // controls islands
   GetPattern2(iPattern)
      pigment_map {
         [0.00 bozo pigment_map {mLightmap(fExtension)} scale 1/fSurfaceScale ] //lights ini
         [fPercent bozo pigment_map {mLightmap(fExtension/3)} scale 1/fSurfaceScale] //lights end
         [fPercent transmit 1 ] //ocean ini
         [1.00 transmit 1 ] //ocean end
      }
   turbulence fTurbulence omega fOmega lambda fLambda phase fPhase scale fScale*fPlanetRadius
   #local fRotateX = RRand(0,90,rLight);
   #local fRotateY = RRand(0,360,rLight);
   #local fRotateZ = RRand(0,360,rLight);
   rotate <fRotateX, fRotateY, fRotateZ> 
#end

#declare NUM_LIGHTMAPS = IRand(0,5,rPlanet);
#macro T_Lights() // non-transparent, not limited to continents
   #local I=0; #while(I<NUM_LIGHTMAPS)
      texture { pigment { mLight() } finish { surface_finish } }
   #local I=I+1; #end
#end //macro

#macro T_SurfaceLights() // transparent, limited to continents
   #local I=0; #while(I<NUM_LIGHTMAPS)
      texture { pigment {
      GetPattern(iSurfacePattern)
      #local P_SurfaceLights = pigment { mLight() };
      pigment_map {
         [0.00 P_SurfaceLights scale 1/fSurfaceScale ] //land ini
         [fSurfacePercent P_SurfaceLights scale 1/fSurfaceScale ] //land end
         [fSurfacePercent transmit 1 ] //ocean ini
         [1.00 transmit 1 ] //ocean end
      }
      turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
      rotate <fRotateX, fRotateY, fRotateZ> } finish { surface_finish } }
   #local I=I+1; #end
#end

#end //SURFACE_REVISION=2

// Final Surface Texture Macro
// ---------------------------------------------------------------------------

  // Final Surface Texture Macro
  #macro mPlanetSurface()
    texture { pigment { P_OceanTexture } finish { surface_finish } }
    texture { T_PlanetSurface }
    texture { T_OceanDepth }
    //T_SurfaceLights()
    texture { T_ArcticTexture }
  #end // planet_surface texture
  
  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    finish { surface_finish }
    hollow on
    no_reflection
  }

#end //planet

// ---------------------------------------------------------------------------
// Terran Planet Selector for legacyt support, testing, and planet randomization
// ---------------------------------------------------------------------------

#macro TerranPlanetSelector(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet)
  #declare iType = IRand(1,9,rPlanet);
  #switch (iType)
    #case (1) TerranPlanet1(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet) #break    
    #case (2) TerranPlanet2(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet) #break    
    #case (3) TerranPlanet3(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet) #break    
    #case (4) TerranPlanet4(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet) #break    
    #case (5) TerranPlanet5(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet) #break    
    #case (6) TerranPlanet6(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet) #break    
    #case (7) TerranPlanet7(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet) #break    
    #case (8) TerranPlanet8(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet) #break    
    #case (9) TerranPlanet(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, rPlanet) #break    
  #end
#end


//EOF
