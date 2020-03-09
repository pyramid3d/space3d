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
// @file    : s3d_planet_trantor.inc
// @brief   : Random planet surface generation
// @version : 2019-05-25
// @created : 2011-04-06
// @author  : pyramid
// @internet: https://openteq.wordpress.com/portfolio/space3d/
// @scale   : 1 POV unit = 1 km
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//  MACROS
//    TrantorPlanet(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aSeedNum)
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
#include "include/s3d_math.inc"
#include "include/s3d_color.inc"

// ---------------------------------------------------------------------------
// Trantor Planet
// ---------------------------------------------------------------------------

//formerly planet_surface_type 23
#macro TrantorPlanet(fPlanetRadius, aBaseColors, fColorDev, bMonoColor, aSeedNum)

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
      #declare NUM_RIVERS = IRand(2,10,rRiver);
    #end
  #end // river seed

  #declare NUM_LIGHTMAPS = 0; // light seed
  #if (iSeedNum>=7)
    #if (aSeedNum[6]>0)
      #declare iSeedNumLight = aSeedNum[6];
      #declare rLight        = seed(aSeedNum[6]);
      #declare NUM_LIGHTMAPS = IRand(30,35,rLight); // old range=30,50
    #end
  #else // this seed is also used for the city and highway structures
    #declare iSeedNumLight = aSeedNum[0];
    #declare rLight        = rStructure;
    #declare NUM_LIGHTMAPS = IRand(30,35,rLight)-NUM_RIVERS-DRAW_ICE; //max=38
  #end

  // Internal parameters
  //#declare SURFACE_COLOR_SET = IRand(1,6,rPlanet);
  //#declare NUM_RIVERS = IRand(2,10,rPlanet);
  //#declare NUM_LIGHTMAPS = IRand(30,50,rPlanet);
  #declare SURFACE_REVISION = IRand(1,2,rPlanet);
  #declare MAX_LANDSCAPE_ITERATION = IRand(10,20,rPlanet);
  #declare MAX_LANDSCAPE_ZONES = IRand(4,20,rPlanet);
  #declare MAX_CLIMATE_ZONES = IRand(8,20,rPlanet);
  #declare LANDSCAPE_ZONES = IRand(6,20,rPlanet);
  #declare SHALLOW_COASTLINE = IRand(0,1,rPlanet);
  #declare ICE_SHAPE_NUMBER = IRand(0,1,rPlanet);
  #ifndef (OCEAN_PERCENTAGE) #declare OCEAN_PERCENTAGE = 0.2; #end
  #ifndef (LIGHT_BASE_COLOR) #declare LIGHT_BASE_COLOR = color rgb <1.0,1.0,0.9>; #end

  // ---------------------------------------------------------------------------
  // Surface Color
  // ---------------------------------------------------------------------------

  GeneratePlanetColorSet(aBaseColors)


// Color Set
// ---------------------------------------------------------------------------
/*
#if (SURFACE_COLOR_SET<=5)
   #declare aBaseColors = array [142];
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
   #declare aBaseColors[130] = color rgb <0.969, 0.875, 0.839>;
   #declare aBaseColors[131] = color rgb <0.894, 0.749, 0.678>;
   #declare aBaseColors[132] = color rgb <0.879, 0.778, 0.454>;
   #declare aBaseColors[133] = color rgb <0.865, 0.765, 0.740>;
   #declare aBaseColors[134] = color rgb <0.855, 0.706, 0.624>;
   #declare aBaseColors[135] = color rgb <0.850, 0.600, 0.400>;
   #declare aBaseColors[136] = color rgb <0.808, 0.667, 0.580>;
   #declare aBaseColors[137] = color rgb <0.788, 0.635, 0.463>;
   #declare aBaseColors[138] = color rgb <0.780, 0.675, 0.639>;
   #declare aBaseColors[139] = color rgb <0.761, 0.629, 0.539>;
   #declare aBaseColors[140] = color rgb <0.722, 0.604, 0.510>;
   #declare aBaseColors[141] = color rgb <0.669, 0.518, 0.392>;
   #declare iBaseColorsMax = dimension_size(aBaseColors,1)-1;
#end

// Color Set
// ---------------------------------------------------------------------------
#if (SURFACE_COLOR_SET=6)
   #declare aBaseColors = array [255];
   #declare aBaseColors[0]  = <0.3137, 0.3725, 0.2275>;
   #declare aBaseColors[1]  = <0.3098, 0.3922, 0.2118>;
   #declare aBaseColors[2]  = <0.3137, 0.3843, 0.1725>;
   #declare aBaseColors[3]  = <0.3333, 0.4196, 0.1608>;
   #declare aBaseColors[4]  = <0.3686, 0.4196, 0.1686>;
   #declare aBaseColors[5]  = <0.3373, 0.3882, 0.2118>;
   #declare aBaseColors[6]  = <0.3412, 0.4118, 0.2078>;
   #declare aBaseColors[7]  = <0.3608, 0.4039, 0.2>;
   #declare aBaseColors[8]  = <0.349, 0.3804, 0.2431>;
   #declare aBaseColors[9]  = <0.3647, 0.3922, 0.2196>;
   #declare aBaseColors[10]  = <0.349, 0.4196, 0.1882>;
   #declare aBaseColors[11]  = <0.3647, 0.451, 0.1922>;
   #declare aBaseColors[12]  = <0.3725, 0.4431, 0.2196>;
   #declare aBaseColors[13]  = <0.3922, 0.4118, 0.2118>;
   #declare aBaseColors[14]  = <0.3922, 0.4353, 0.2353>;
   #declare aBaseColors[15]  = <0.3922, 0.4471, 0.1961>;
   #declare aBaseColors[16]  = <0.4, 0.4392, 0.2157>;
   #declare aBaseColors[17]  = <0.4235, 0.4549, 0.2039>;
   #declare aBaseColors[18]  = <0.4078, 0.4784, 0.1961>;
   #declare aBaseColors[19]  = <0.4118, 0.4745, 0.2196>;
   #declare aBaseColors[20]  = <0.451, 0.4627, 0.2431>;
   #declare aBaseColors[21]  = <0.451, 0.4745, 0.2039>;
   #declare aBaseColors[22]  = <0.3569, 0.3804, 0.2863>;
   #declare aBaseColors[23]  = <0.3765, 0.4353, 0.2549>;
   #declare aBaseColors[24]  = <0.4039, 0.4235, 0.251>;
   #declare aBaseColors[25]  = <0.3961, 0.4745, 0.2549>;
   #declare aBaseColors[26]  = <0.4353, 0.4549, 0.2588>;
   #declare aBaseColors[27]  = <0.4235, 0.4431, 0.2902>;
   #declare aBaseColors[28]  = <0.4275, 0.4706, 0.2588>;
   #declare aBaseColors[29]  = <0.4118, 0.4392, 0.3176>;
   #declare aBaseColors[30]  = <0.4667, 0.4039, 0.302>;
   #declare aBaseColors[31]  = <0.4627, 0.4314, 0.2863>;
   #declare aBaseColors[32]  = <0.4392, 0.4314, 0.3412>;
   #declare aBaseColors[33]  = <0.4588, 0.4353, 0.3176>;
   #declare aBaseColors[34]  = <0.498, 0.4118, 0.3137>;
   #declare aBaseColors[35]  = <0.4667, 0.4588, 0.2627>;
   #declare aBaseColors[36]  = <0.4431, 0.451, 0.2824>;
   #declare aBaseColors[37]  = <0.4784, 0.4471, 0.2627>;
   #declare aBaseColors[38]  = <0.4902, 0.4941, 0.2745>;
   #declare aBaseColors[39]  = <0.4745, 0.4941, 0.2941>;
   #declare aBaseColors[40]  = <0.498, 0.4902, 0.298>;
   #declare aBaseColors[41]  = <0.4667, 0.4824, 0.3294>;
   #declare aBaseColors[42]  = <0.4667, 0.4863, 0.3569>;
   #declare aBaseColors[43]  = <0.4784, 0.4863, 0.3137>;
   #declare aBaseColors[44]  = <0.4941, 0.4745, 0.3294>;
   #declare aBaseColors[45]  = <0.4902, 0.4784, 0.3569>;
   #declare aBaseColors[46]  = <0.4745, 0.4824, 0.3843>;
   #declare aBaseColors[47]  = <0.4863, 0.4941, 0.4824>;
   #declare aBaseColors[48]  = <0.4667, 0.5216, 0.2118>;
   #declare aBaseColors[49]  = <0.4471, 0.5059, 0.2235>;
   #declare aBaseColors[50]  = <0.4784, 0.502, 0.2275>;
   #declare aBaseColors[51]  = <0.4784, 0.5333, 0.2471>;
   #declare aBaseColors[52]  = <0.4275, 0.5059, 0.2824>;
   #declare aBaseColors[53]  = <0.4353, 0.5059, 0.3255>;
   #declare aBaseColors[54]  = <0.4471, 0.5098, 0.251>;
   #declare aBaseColors[55]  = <0.4549, 0.5373, 0.3098>;
   #declare aBaseColors[56]  = <0.4784, 0.5059, 0.2549>;
   #declare aBaseColors[57]  = <0.4745, 0.5137, 0.2902>;
   #declare aBaseColors[58]  = <0.498, 0.5216, 0.3412>;
   #declare aBaseColors[59]  = <0.4863, 0.5686, 0.3255>;
   #declare aBaseColors[60]  = <0.498, 0.5216, 0.3882>;
   #declare aBaseColors[61]  = <0.5098, 0.4196, 0.302>;
   #declare aBaseColors[62]  = <0.5216, 0.4863, 0.302>;
   #declare aBaseColors[63]  = <0.5255, 0.4706, 0.3451>;
   #declare aBaseColors[64]  = <0.5137, 0.4824, 0.3922>;
   #declare aBaseColors[65]  = <0.5843, 0.498, 0.3961>;
   #declare aBaseColors[66]  = <0.6118, 0.498, 0.4039>;
   #declare aBaseColors[67]  = <0.5137, 0.5333, 0.2314>;
   #declare aBaseColors[68]  = <0.5059, 0.5294, 0.2549>;
   #declare aBaseColors[69]  = <0.5216, 0.5216, 0.251>;
   #declare aBaseColors[70]  = <0.5255, 0.5294, 0.2824>;
   #declare aBaseColors[71]  = <0.5255, 0.5255, 0.3059>;
   #declare aBaseColors[72]  = <0.5059, 0.5608, 0.2745>;
   #declare aBaseColors[73]  = <0.5255, 0.5608, 0.3059>;
   #declare aBaseColors[74]  = <0.5569, 0.5529, 0.2824>;
   #declare aBaseColors[75]  = <0.5569, 0.5529, 0.3059>;
   #declare aBaseColors[76]  = <0.5098, 0.5255, 0.3255>;
   #declare aBaseColors[77]  = <0.5294, 0.5216, 0.3255>;
   #declare aBaseColors[78]  = <0.5059, 0.5176, 0.3647>;
   #declare aBaseColors[79]  = <0.5176, 0.5176, 0.3451>;
   #declare aBaseColors[80]  = <0.5569, 0.5176, 0.3294>;
   #declare aBaseColors[81]  = <0.5412, 0.5137, 0.3451>;
   #declare aBaseColors[82]  = <0.5333, 0.5137, 0.3686>;
   #declare aBaseColors[83]  = <0.5569, 0.502, 0.3451>;
   #declare aBaseColors[84]  = <0.549, 0.5529, 0.3294>;
   #declare aBaseColors[85]  = <0.5333, 0.5529, 0.349>;
   #declare aBaseColors[86]  = <0.5451, 0.549, 0.3725>;
   #declare aBaseColors[87]  = <0.5608, 0.549, 0.3529>;
   #declare aBaseColors[88]  = <0.5412, 0.5647, 0.2627>;
   #declare aBaseColors[89]  = <0.5412, 0.5647, 0.2863>;
   #declare aBaseColors[90]  = <0.5294, 0.5686, 0.3412>;
   #declare aBaseColors[91]  = <0.5608, 0.5882, 0.3333>;
   #declare aBaseColors[92]  = <0.5882, 0.5451, 0.3451>;
   #declare aBaseColors[93]  = <0.6039, 0.5569, 0.3216>;
   #declare aBaseColors[94]  = <0.5725, 0.5922, 0.2863>;
   #declare aBaseColors[95]  = <0.5882, 0.5843, 0.3137>;
   #declare aBaseColors[96]  = <0.5804, 0.5843, 0.3333>;
   #declare aBaseColors[97]  = <0.5882, 0.5843, 0.3608>;
   #declare aBaseColors[98]  = <0.6039, 0.5843, 0.3412>;
   #declare aBaseColors[99]  = <0.6118, 0.6235, 0.3137>;
   #declare aBaseColors[100]  = <0.6196, 0.6235, 0.3451>;
   #declare aBaseColors[101]  = <0.6118, 0.6196, 0.3647>;
   #declare aBaseColors[102]  = <0.5255, 0.5137, 0.3922>;
   #declare aBaseColors[103]  = <0.5098, 0.5137, 0.4157>;
   #declare aBaseColors[104]  = <0.5255, 0.549, 0.4235>;
   #declare aBaseColors[105]  = <0.5608, 0.5098, 0.3843>;
   #declare aBaseColors[106]  = <0.5412, 0.549, 0.3961>;
   #declare aBaseColors[107]  = <0.5608, 0.5451, 0.4235>;
   #declare aBaseColors[108]  = <0.5451, 0.5412, 0.4392>;
   #declare aBaseColors[109]  = <0.5725, 0.5451, 0.3765>;
   #declare aBaseColors[110]  = <0.5647, 0.5451, 0.4>;
   #declare aBaseColors[111]  = <0.5882, 0.5412, 0.4>;
   #declare aBaseColors[112]  = <0.5804, 0.5412, 0.4235>;
   #declare aBaseColors[113]  = <0.6, 0.5412, 0.3843>;
   #declare aBaseColors[114]  = <0.6078, 0.5373, 0.4039>;
   #declare aBaseColors[115]  = <0.6, 0.5373, 0.4275>;
   #declare aBaseColors[116]  = <0.5725, 0.5333, 0.4431>;
   #declare aBaseColors[117]  = <0.5922, 0.5608, 0.4941>;
   #declare aBaseColors[118]  = <0.5882, 0.5804, 0.3843>;
   #declare aBaseColors[119]  = <0.5804, 0.5804, 0.4039>;
   #declare aBaseColors[120]  = <0.5725, 0.5804, 0.4275>;
   #declare aBaseColors[121]  = <0.6039, 0.5725, 0.4039>;
   #declare aBaseColors[122]  = <0.6157, 0.5765, 0.3765>;
   #declare aBaseColors[123]  = <0.5961, 0.5765, 0.4314>;
   #declare aBaseColors[124]  = <0.6157, 0.5686, 0.4275>;
   #declare aBaseColors[125]  = <0.6039, 0.6157, 0.3882>;
   #declare aBaseColors[126]  = <0.6039, 0.6078, 0.4314>;
   #declare aBaseColors[127]  = <0.6235, 0.6157, 0.4157>;
   #declare aBaseColors[128]  = <0.5647, 0.5843, 0.4588>;
   #declare aBaseColors[129]  = <0.5882, 0.5765, 0.4549>;
   #declare aBaseColors[130]  = <0.6118, 0.5725, 0.451>;
   #declare aBaseColors[131]  = <0.6078, 0.5647, 0.4706>;
   #declare aBaseColors[132]  = <0.6039, 0.6157, 0.4627>;
   #declare aBaseColors[133]  = <0.6235, 0.6078, 0.4824>;
   #declare aBaseColors[134]  = <0.6392, 0.6118, 0.3412>;
   #declare aBaseColors[135]  = <0.6353, 0.5333, 0.3882>;
   #declare aBaseColors[136]  = <0.6392, 0.5451, 0.4235>;
   #declare aBaseColors[137]  = <0.6706, 0.5412, 0.4>;
   #declare aBaseColors[138]  = <0.6588, 0.5373, 0.4314>;
   #declare aBaseColors[139]  = <0.6275, 0.5451, 0.4627>;
   #declare aBaseColors[140]  = <0.6275, 0.5608, 0.451>;
   #declare aBaseColors[141]  = <0.6627, 0.5529, 0.4784>;
   #declare aBaseColors[142]  = <0.6275, 0.5686, 0.4078>;
   #declare aBaseColors[143]  = <0.6353, 0.5647, 0.4314>;
   #declare aBaseColors[144]  = <0.6353, 0.6196, 0.3961>;
   #declare aBaseColors[145]  = <0.651, 0.6196, 0.3765>;
   #declare aBaseColors[146]  = <0.6549, 0.6118, 0.3961>;
   #declare aBaseColors[147]  = <0.651, 0.5961, 0.4353>;
   #declare aBaseColors[148]  = <0.651, 0.6118, 0.4196>;
   #declare aBaseColors[149]  = <0.6392, 0.6078, 0.4392>;
   #declare aBaseColors[150]  = <0.6275, 0.6039, 0.4549>;
   #declare aBaseColors[151]  = <0.6471, 0.5961, 0.4549>;
   #declare aBaseColors[152]  = <0.6392, 0.6, 0.4784>;
   #declare aBaseColors[153]  = <0.6745, 0.5922, 0.4627>;
   #declare aBaseColors[154]  = <0.6824, 0.5922, 0.4863>;
   #declare aBaseColors[155]  = <0.6627, 0.5961, 0.4863>;
   #declare aBaseColors[156]  = <0.702, 0.5765, 0.4549>;
   #declare aBaseColors[157]  = <0.698, 0.5843, 0.4941>;
   #declare aBaseColors[158]  = <0.698, 0.6078, 0.4549>;
   #declare aBaseColors[159]  = <0.7412, 0.6157, 0.4941>;
   #declare aBaseColors[160]  = <0.6588, 0.6627, 0.3529>;
   #declare aBaseColors[161]  = <0.6824, 0.651, 0.3804>;
   #declare aBaseColors[162]  = <0.6627, 0.6627, 0.3843>;
   #declare aBaseColors[163]  = <0.6784, 0.6588, 0.4118>;
   #declare aBaseColors[164]  = <0.6392, 0.6588, 0.4745>;
   #declare aBaseColors[165]  = <0.6627, 0.6392, 0.4902>;
   #declare aBaseColors[166]  = <0.6824, 0.6392, 0.4706>;
   #declare aBaseColors[167]  = <0.6863, 0.6392, 0.4941>;
   #declare aBaseColors[168]  = <0.6784, 0.6627, 0.4392>;
   #declare aBaseColors[169]  = <0.702, 0.651, 0.4078>;
   #declare aBaseColors[170]  = <0.6902, 0.651, 0.451>;
   #declare aBaseColors[171]  = <0.7059, 0.6314, 0.4941>;
   #declare aBaseColors[172]  = <0.7216, 0.6549, 0.4627>;
   #declare aBaseColors[173]  = <0.7294, 0.6275, 0.498>;
   #declare aBaseColors[174]  = <0.702, 0.7098, 0.4235>;
   #declare aBaseColors[175]  = <0.7333, 0.702, 0.4275>;
   #declare aBaseColors[176]  = <0.702, 0.7059, 0.4471>;
   #declare aBaseColors[177]  = <0.7137, 0.698, 0.4706>;
   #declare aBaseColors[178]  = <0.7098, 0.702, 0.498>;
   #declare aBaseColors[179]  = <0.7216, 0.6941, 0.4431>;
   #declare aBaseColors[180]  = <0.7412, 0.6902, 0.4471>;
   #declare aBaseColors[181]  = <0.7333, 0.6941, 0.498>;
   #declare aBaseColors[182]  = <0.7412, 0.6902, 0.4745>;
   #declare aBaseColors[183]  = <0.6196, 0.6, 0.502>;
   #declare aBaseColors[184]  = <0.6235, 0.6118, 0.5412>;
   #declare aBaseColors[185]  = <0.6627, 0.5961, 0.5059>;
   #declare aBaseColors[186]  = <0.6588, 0.6078, 0.5451>;
   #declare aBaseColors[187]  = <0.7176, 0.6235, 0.5176>;
   #declare aBaseColors[188]  = <0.7294, 0.6157, 0.5294>;
   #declare aBaseColors[189]  = <0.6549, 0.6392, 0.5137>;
   #declare aBaseColors[190]  = <0.6431, 0.651, 0.502>;
   #declare aBaseColors[191]  = <0.6784, 0.6353, 0.5176>;
   #declare aBaseColors[192]  = <0.6588, 0.6392, 0.5412>;
   #declare aBaseColors[193]  = <0.6784, 0.6863, 0.5176>;
   #declare aBaseColors[194]  = <0.6824, 0.6784, 0.549>;
   #declare aBaseColors[195]  = <0.698, 0.6314, 0.5176>;
   #declare aBaseColors[196]  = <0.6902, 0.6314, 0.5412>;
   #declare aBaseColors[197]  = <0.7137, 0.6275, 0.5451>;
   #declare aBaseColors[198]  = <0.7098, 0.6784, 0.5059>;
   #declare aBaseColors[199]  = <0.7059, 0.6824, 0.5294>;
   #declare aBaseColors[200]  = <0.7137, 0.6745, 0.5529>;
   #declare aBaseColors[201]  = <0.749, 0.6549, 0.549>;
   #declare aBaseColors[202]  = <0.7294, 0.6706, 0.5059>;
   #declare aBaseColors[203]  = <0.7216, 0.6745, 0.5294>;
   #declare aBaseColors[204]  = <0.749, 0.6667, 0.5059>;
   #declare aBaseColors[205]  = <0.7412, 0.6627, 0.5255>;
   #declare aBaseColors[206]  = <0.7333, 0.6627, 0.549>;
   #declare aBaseColors[207]  = <0.702, 0.6706, 0.5765>;
   #declare aBaseColors[208]  = <0.7412, 0.6549, 0.5725>;
   #declare aBaseColors[209]  = <0.7255, 0.6667, 0.5804>;
   #declare aBaseColors[210]  = <0.7098, 0.7176, 0.549>;
   #declare aBaseColors[211]  = <0.7333, 0.7098, 0.5569>;
   #declare aBaseColors[212]  = <0.7412, 0.7098, 0.5373>;
   #declare aBaseColors[213]  = <0.749, 0.7333, 0.5137>;
   #declare aBaseColors[214]  = <0.7137, 0.7137, 0.5843>;
   #declare aBaseColors[215]  = <0.7451, 0.702, 0.5804>;
   #declare aBaseColors[216]  = <0.7373, 0.7059, 0.6157>;
   #declare aBaseColors[217]  = <0.7451, 0.7451, 0.5765>;
   #declare aBaseColors[218]  = <0.7333, 0.749, 0.6118>;
   #declare aBaseColors[219]  = <0.7608, 0.6549, 0.5255>;
   #declare aBaseColors[220]  = <0.7804, 0.651, 0.5294>;
   #declare aBaseColors[221]  = <0.7804, 0.6588, 0.5569>;
   #declare aBaseColors[222]  = <0.7922, 0.6863, 0.5569>;
   #declare aBaseColors[223]  = <0.7569, 0.6471, 0.5686>;
   #declare aBaseColors[224]  = <0.8, 0.6863, 0.6078>;
   #declare aBaseColors[225]  = <0.7608, 0.6941, 0.5059>;
   #declare aBaseColors[226]  = <0.7569, 0.698, 0.5333>;
   #declare aBaseColors[227]  = <0.7529, 0.702, 0.5569>;
   #declare aBaseColors[228]  = <0.7765, 0.698, 0.5569>;
   #declare aBaseColors[229]  = <0.7765, 0.7255, 0.5255>;
   #declare aBaseColors[230]  = <0.7647, 0.6941, 0.5804>;
   #declare aBaseColors[231]  = <0.7569, 0.698, 0.6118>;
   #declare aBaseColors[232]  = <0.7765, 0.6902, 0.6039>;
   #declare aBaseColors[233]  = <0.7686, 0.7412, 0.5843>;
   #declare aBaseColors[234]  = <0.7608, 0.749, 0.6235>;
   #declare aBaseColors[235]  = <0.7804, 0.7373, 0.6157>;
   #declare aBaseColors[236]  = <0.7843, 0.6902, 0.5804>;
   #declare aBaseColors[237]  = <0.7843, 0.7333, 0.5882>;
   #declare aBaseColors[238]  = <0.7961, 0.7373, 0.5647>;
   #declare aBaseColors[239]  = <0.8039, 0.7255, 0.5843>;
   #declare aBaseColors[240]  = <0.8, 0.7255, 0.6118>;
   #declare aBaseColors[241]  = <0.7725, 0.7412, 0.651>;
   #declare aBaseColors[242]  = <0.7922, 0.7294, 0.6392>;
   #declare aBaseColors[243]  = <0.8275, 0.7765, 0.6235>;
   #declare aBaseColors[244]  = <0.8431, 0.7569, 0.6157>;
   #declare aBaseColors[245]  = <0.7922, 0.7804, 0.6471>;
   #declare aBaseColors[246]  = <0.8039, 0.7725, 0.6745>;
   #declare aBaseColors[247]  = <0.8, 0.7882, 0.6275>;
   #declare aBaseColors[248]  = <0.8157, 0.7725, 0.6471>;
   #declare aBaseColors[249]  = <0.8314, 0.7608, 0.6431>;
   #declare aBaseColors[250]  = <0.8275, 0.7608, 0.6706>;
   #declare aBaseColors[251]  = <0.8431, 0.8039, 0.6784>;
   #declare aBaseColors[252]  = <0.8549, 0.7804, 0.6627>;
   #declare aBaseColors[253]  = <0.8392, 0.8078, 0.7216>;
   #declare aBaseColors[254]  = <0.8549, 0.7882, 0.702>;
   #declare iBaseColorsMax = dimension_size(aBaseColors,1)-1;
#end
*/

// Color Set
// ---------------------------------------------------------------------------
/*
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
  
  #if (SURFACE_REVISION=1)

  // Landscape Zones pigment macro
  // ---------------------------------------------------------------------------
  #macro mMicroStructure_Arid()
     #local fTurbulence = RRand(1.0, 3.0, rTexture);
     #local fPhase = RRand(0.2, 0.9, rTexture);
     #local fLambda = RRand(2.0,5.0,rTexture); // controls coastline
     #local fOmega = RRand(0.30,0.65,rTexture); // controls islands
     #local fScale = RRand(0.001, 0.01, rTexture);
     #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rTexture);
     #local iPattern = IRand(5, 15, rTexture);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           //#if (SURFACE_COLOR_SET>=5)
           //   #local iColor = IRand(0,iBaseColorsMax,rColor);
           //   #declare cColor = aBaseColors[iColor]; #break
           //#else
              #local iZone  = IRand(1,3,rColor);
              //#local iColor = IRand(0,iBaseColorsMax,rColor);
              #local iColor = IRand(0,9,rColor);
              #switch(iZone)
                 #case (1) #declare cColor = cDesert[iColor];  #break
                 #case (2) #declare cColor = cSoil[iColor]; #break
                 #case (3) #declare cColor = cHill[iColor];  #break
              #end
           //#end
           #local cPigmentColor = VariateColor(cColor, fColorDev, bMonoColor, rColor);
           [I cPigmentColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius rotate <RRand(0,360,rTexture),RRand(0,360,rTexture),RRand(0,360,rTexture)> //}
  #end //macro

  #macro mMicroStructure_Mediterran()
     #local fTurbulence = RRand(1.0, 3.0, rTexture);
     #local fPhase = RRand(0.2, 0.9, rTexture);
     #local fLambda = RRand(2.0,5.0,rTexture); // controls coastline
     #local fOmega = RRand(0.30,0.65,rTexture); // controls islands
     #local fScale = RRand(0.001, 0.01, rTexture);
     #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rTexture);
     #local iPattern = IRand(5, 15, rTexture);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           //#if (SURFACE_COLOR_SET>=5)
           //   #local iColor = IRand(0,iBaseColorsMax,rColor);
           //   #declare cColor = aBaseColors[iColor]; #break
           //#else
              #local iZone  = IRand(1,3,rColor);
              //#local iColor = IRand(0,iBaseColorsMax,rColor);
              #local iColor = IRand(0,9,rColor);
              #switch(iZone)
                 #case (1) #declare cColor = cForrest[iColor]; #break
                 #case (2) #declare cColor = cHill[iColor];  #break
                 #case (3) #declare cColor = cSoil[iColor];  #break
              #end
           //#end
           #local cPigmentColor = VariateColor(cColor, fColorDev, bMonoColor,rColor);
           [I cPigmentColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius rotate <RRand(0,360,rTexture),RRand(0,360,rTexture),RRand(0,360,rTexture)> //}
  #end //macro

  #macro mMicroStructure_Moderate()
     #local fTurbulence = RRand(1.0, 3.0, rTexture);
     #local fPhase = RRand(0.2, 0.9, rTexture);
     #local fLambda = RRand(2.0,5.0,rTexture); // controls coastline
     #local fOmega = RRand(0.30,0.65,rTexture); // controls islands
     #local fScale = RRand(0.001, 0.01, rTexture);
     #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rTexture);
     #local iPattern = IRand(5, 15, rTexture);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           //#if (SURFACE_COLOR_SET>=5)
           //   #local iColor = IRand(0,iBaseColorsMax,rColor);
           //   #declare cColor = aBaseColors[iColor]; #break
           //#else
              #local iZone  = IRand(1,3,rColor);
              //#local iColor = IRand(0,iBaseColorsMax,rColor);
              #local iColor = IRand(0,9,rColor);
              #switch(iZone)
                 #case (1) #declare cColor = cForrest[iColor]; #break
                 #case (2) #declare cColor = cSoil[iColor];    #break
                 #case (3) #declare cColor = cJungle[iColor];  #break
              #end
           //#end
           #local cPigmentColor = VariateColor(cColor, fColorDev, bMonoColor,rColor);
           [I cPigmentColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius rotate <RRand(0,360,rTexture),RRand(0,360,rTexture),RRand(0,360,rTexture)> //}
  #end //macro

  // Landscape Zones gradient (longitudonal)
  // ---------------------------------------------------------------------------
  #macro mArid()
     #local fSteps           = MAX_LANDSCAPE_ZONES*2; //IRand(MAX_LANDSCAPE_ZONES/2, MAX_LANDSCAPE_ZONES, rTexture);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rTexture);
     #local fGradXTurbulence = RRand(1, 5, rTexture);
     #local fGradXOmega      = RRand(0.35, 0.65, rTexture);
     #local fGradXLambda     = RRand(2, 6, rTexture);
     #local fGradScale       = fPlanetRadius;
     //#local fRotateX         = RRand(0,360,rTexture);
     //#local fRotateY         = RRand(0,360,rTexture);
     //#local fRotateZ         = RRand(0,360,rTexture);
     radial pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Arid = pigment { mMicroStructure_Arid() };
           [min(1,I+1/fSteps-fJitter) P_MicroStructure_Arid ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
     //rotate <fRotateX, fRotateY, fRotateZ>
  #end

  #macro mMediterran()
     #local fSteps           = MAX_LANDSCAPE_ZONES*2; //IRand(MAX_LANDSCAPE_ZONES/2, MAX_LANDSCAPE_ZONES, rTexture);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rTexture);
     #local fGradXTurbulence = RRand(1, 5, rTexture);
     #local fGradXOmega      = RRand(0.35, 0.65, rTexture);
     #local fGradXLambda     = RRand(2, 6, rTexture);
     #local fGradScale       = fPlanetRadius;
     //#local fRotateX         = RRand(0,360,rTexture);
     //#local fRotateY         = RRand(0,360,rTexture);
     //#local fRotateZ         = RRand(0,360,rTexture);
     radial pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Mediterran = pigment { mMicroStructure_Mediterran() };
           [min(1,I+1/fSteps-fJitter) P_MicroStructure_Mediterran ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
     //rotate <fRotateX, fRotateY, fRotateZ>
  #end

  #macro mModerate()
     #local fSteps           = MAX_LANDSCAPE_ZONES*2; //IRand(MAX_LANDSCAPE_ZONES/2, MAX_LANDSCAPE_ZONES, rTexture);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rTexture);
     #local fGradXTurbulence = RRand(1, 5, rTexture);
     #local fGradXOmega      = RRand(0.35, 0.65, rTexture);
     #local fGradXLambda     = RRand(2, 6, rTexture);
     #local fGradScale       = fPlanetRadius;
     //#local fRotateX         = RRand(0,360,rTexture);
     //#local fRotateY         = RRand(0,360,rTexture);
     //#local fRotateZ         = RRand(0,360,rTexture);
     radial pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Moderate = pigment { mMicroStructure_Moderate() };
           [min(1,I+1/fSteps-fJitter) P_MicroStructure_Moderate ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
     //rotate <fRotateX, fRotateY, fRotateZ>
  #end

  // Climate Zones gradient (latitudonal)
  // ---------------------------------------------------------------------------
  #declare fClimateZones    = LANDSCAPE_ZONES; //RRand(MAX_CLIMATE_ZONES/2, MAX_CLIMATE_ZONES, rTexture);
  #declare fGradYTurbulence = RRand(0.3, 0.9, rTexture);
  #declare fGradYOmega      = RRand(0.15, 0.35, rTexture);
  #declare fGradYLambda     = RRand(1, 2, rTexture);
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
  #declare fSurfaceTurbulence = RRand(0.3, 0.9, rStructure); // complexity of continents
  #declare fSurfaceOmega = RRand(0.35, 0.45, rStructure); // increses disconnected continents
  #declare fSurfaceLambda = RRand(3.5, 6.5, rStructure); // increses coastline roughness
  #declare fSurfacePhase = RRand(0.0, 0.4, rStructure); // different ocean shape
  #declare fSurfacePercent = RRand((1-OCEAN_PERCENTAGE)*0.8, (1-OCEAN_PERCENTAGE), rStructure); // approximate portion of land versus ocean
  #declare fSurfaceScale = 0.5*fPlanetRadius; //0.5*fPlanetRadius;
  #declare iSurfacePattern = IRand(5,15,rStructure); //5-15
  //#declare fSurfaceRotation = RRand(0, 360, rStructure);
  #declare fRotateX = RRand(-180,180,rStructure);
  #declare fRotateY = RRand(-180,180,rStructure);
  #declare fRotateZ = RRand(-90,90,rStructure);
  #declare T_PlanetSurface = texture { pigment { GetPattern(iSurfacePattern)
     pigment_map {
        [0.00 P_SurfaceClimateGradient rotate -fRotateX*x rotate -fRotateY*y rotate -fRotateZ*z scale 1/fSurfaceScale phase -fSurfacePhase lambda -fSurfaceLambda omega -fSurfaceOmega turbulence -fSurfaceTurbulence] //land ini
        [fSurfacePercent P_SurfaceClimateGradient rotate -fRotateX*x rotate -fRotateY*y rotate -fRotateZ*z scale 1/fSurfaceScale phase -fSurfacePhase lambda -fSurfaceLambda omega -fSurfaceOmega turbulence -fSurfaceTurbulence] //land end
        //[0.00 P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land ini
        //[fSurfacePercent P_SurfaceClimateGradient scale 1/fSurfaceScale ] //land end
        [fSurfacePercent transmit 1 ] //ocean ini
        [1.00 transmit 1 ] //ocean end
     }
     turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
     rotate fRotateZ*z rotate fRotateY*y rotate fRotateX*x 
  } finish { surface_finish } }
  
  #declare T_TestContinents = texture { pigment { GetPattern(iSurfacePattern)
     pigment_map {
        [0.00 P_SurfaceBase scale 1/fSurfaceScale ] //land ini
        [fSurfacePercent P_SurfaceBase scale 1/fSurfaceScale ] //land end
        [fSurfacePercent color rgb <0,0,0> ] //ocean ini
        [1.00 color rgb <0,0,0> ] //ocean end
     }
  turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
  rotate fRotateZ*z rotate fRotateY*y rotate fRotateX*x } finish { surface_finish } }

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
  rotate fRotateZ*z rotate fRotateY*y rotate fRotateX*x } finish { surface_finish } }

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
  rotate fRotateZ*z rotate fRotateY*y rotate fRotateX*x } finish { surface_finish } }

#end //SURFACE_REVISION=1

#if (SURFACE_REVISION=2)

  // Landscape Zones pigment macro
  // ---------------------------------------------------------------------------
  #macro mMicroStructure_Arid()
     #local fTurbulence = RRand(1.0, 3.0, rTexture);
     #local fPhase = RRand(0.2, 0.9, rTexture);
     #local fLambda = RRand(2.0,5.0,rTexture); // controls coastline
     #local fOmega = RRand(0.30,0.65,rTexture); // controls islands
     #local fScale = RRand(0.001, 0.01, rTexture);
     #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rTexture);
     #local iPattern = IRand(5, 15, rTexture);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           //#if (SURFACE_COLOR_SET>=5)
           //   #local iColor = IRand(0,iBaseColorsMax,rColor);
           //   #declare cColor = aBaseColors[iColor]; #break
           //#else
              #local iZone  = IRand(1,3,rColor);
              //#local iColor = IRand(0,iBaseColorsMax,rColor);
              #local iColor = IRand(0,9,rColor);
              #switch(iZone)
                 #case (1) #declare cColor = cDesert[iColor];  #break
                 #case (2) #declare cColor = cSoil[iColor]; #break
                 #case (3) #declare cColor = cHill[iColor];  #break
              #end
           //#end
           #local cPigmentColor = VariateColor(cColor, fColorDev, bMonoColor, rColor);
           [I cPigmentColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius
     //rotate <RRand(0,360,rTexture),RRand(0,360,rTexture),RRand(0,360,rTexture)> //}
  #end //macro

  #macro mMicroStructure_Mediterran()
     #local fTurbulence = RRand(1.0, 3.0, rTexture);
     #local fPhase = RRand(0.2, 0.9, rTexture);
     #local fLambda = RRand(2.0,5.0,rTexture); // controls coastline
     #local fOmega = RRand(0.30,0.65,rTexture); // controls islands
     #local fScale = RRand(0.001, 0.01, rTexture);
     #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rTexture);
     #local iPattern = IRand(5, 15, rTexture);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           //#if (SURFACE_COLOR_SET>=5)
           //   #local iColor = IRand(0,iBaseColorsMax,rColor);
           //   #declare cColor = aBaseColors[iColor]; #break
           //#else
              #local iZone  = IRand(1,3,rColor);
              //#local iColor = IRand(0,iBaseColorsMax,rColor);
              #local iColor = IRand(0,9,rColor);
              #switch(iZone)
                 #case (1) #declare cColor = cForrest[iColor]; #break
                 #case (2) #declare cColor = cHill[iColor];    #break
                 #case (3) #declare cColor = cSoil[iColor];  #break
              #end
           //#end
           #local cPigmentColor = VariateColor(cColor, fColorDev, bMonoColor, rColor);
           [I cPigmentColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius
     //rotate <RRand(0,360,rTexture),RRand(0,360,rTexture),RRand(0,360,rTexture)> //}
  #end //macro

  #macro mMicroStructure_Moderate()
     #local fTurbulence = RRand(1.0, 3.0, rTexture);
     #local fPhase = RRand(0.2, 0.9, rTexture);
     #local fLambda = RRand(2.0,5.0,rTexture); // controls coastline
     #local fOmega = RRand(0.30,0.65,rTexture); // controls islands
     #local fScale = RRand(0.001, 0.01, rTexture);
     #local fSteps = RRand(MAX_LANDSCAPE_ITERATION/2, MAX_LANDSCAPE_ITERATION, rTexture);
     #local iPattern = IRand(5, 15, rTexture);
     GetPattern(iPattern) 
     turbulence fTurbulence phase fPhase lambda fLambda omega fOmega
     color_map {
        #local I=0; #while(I<1)
           //#if (SURFACE_COLOR_SET>=5)
           //   #local iColor = IRand(0,iBaseColorsMax,rColor);
           //   #declare cColor = aBaseColors[iColor]; #break
           //#else
              #local iZone  = IRand(1,3,rColor);
              //#local iColor = IRand(0,iBaseColorsMax,rColor);
              #local iColor = IRand(0,9,rColor);
              #switch(iZone)
                 #case (1) #declare cColor = cForrest[iColor]; #break
                 #case (2) #declare cColor = cSoil[iColor];    #break
                 #case (3) #declare cColor = cJungle[iColor];  #break
              #end
           //#end
           #local cPigmentColor = VariateColor(cColor, fColorDev, bMonoColor, rColor);
           [I cPigmentColor ]
        #local I=I+1/fSteps; #end
     } scale fScale*fPlanetRadius
     //rotate <RRand(0,360,rTexture),RRand(0,360,rTexture),RRand(0,360,rTexture)> //}
  #end //macro

  // Landscape Zones gradient (longitudonal)
  // ---------------------------------------------------------------------------
  #macro mArid()
     #local fSteps           = LANDSCAPE_ZONES; //IRand(LANDSCAPE_ZONES/2, LANDSCAPE_ZONES, rTexture);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rTexture);
     #local fGradXTurbulence = RRand(1.0, 5, rTexture);
     #local fGradXOmega      = RRand(0.35, 0.65, rTexture);
     #local fGradXLambda     = RRand(2, 6, rTexture);
     #local fGradScale       = fPlanetRadius;
     #local fRotateX         = RRand(0,360,rTexture);
     #local fRotateY         = RRand(0,360,rTexture);
     #local fRotateZ         = RRand(0,360,rTexture);
     radial pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Arid = pigment { mMicroStructure_Arid() };
           [min(1,I+1/fSteps-fJitter) P_MicroStructure_Arid ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
     rotate <fRotateX, fRotateY, fRotateZ>
  #end
  
  #macro mMediterran()
     #local fSteps           = LANDSCAPE_ZONES; //IRand(LANDSCAPE_ZONES/2, LANDSCAPE_ZONES, rTexture);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rTexture);
     #local fGradXTurbulence = RRand(1.0, 5, rTexture);
     #local fGradXOmega      = RRand(0.35, 0.65, rTexture);
     #local fGradXLambda     = RRand(2, 6, rTexture);
     #local fGradScale       = fPlanetRadius;
     #local fRotateX         = RRand(0,360,rTexture);
     #local fRotateY         = RRand(0,360,rTexture);
     #local fRotateZ         = RRand(0,360,rTexture);
     radial pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Mediterran = pigment { mMicroStructure_Mediterran() };
           [min(1,I+1/fSteps-fJitter) P_MicroStructure_Mediterran ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
     rotate <fRotateX, fRotateY, fRotateZ>
  #end

  #macro mModerate()
     #local fSteps           = LANDSCAPE_ZONES; //IRand(LANDSCAPE_ZONES/2, LANDSCAPE_ZONES, rTexture);
     #local fJitter          = RRand(1/fSteps/4,1/fSteps/3,rTexture);
     #local fGradXTurbulence = RRand(1.0, 5, rTexture);
     #local fGradXOmega      = RRand(0.35, 0.65, rTexture);
     #local fGradXLambda     = RRand(2, 6, rTexture);
     #local fGradScale       = fPlanetRadius;
     #local fRotateX         = RRand(0,360,rTexture);
     #local fRotateY         = RRand(0,360,rTexture);
     #local fRotateZ         = RRand(0,360,rTexture);
     radial pigment_map {
        #local I=0; #while(I<1)
           #local P_MicroStructure_Moderate = pigment { mMicroStructure_Moderate() };
           [min(1,I+1/fSteps-fJitter) P_MicroStructure_Moderate ]
        #local I=I+1/fSteps; #end
     } turbulence fGradXTurbulence omega fGradXOmega lambda fGradXLambda scale fGradScale //}
     rotate <fRotateX, fRotateY, fRotateZ>
  #end

  // Climate Zones gradient (latitudonal)
  // ---------------------------------------------------------------------------
  #declare fClimateZones = LANDSCAPE_ZONES;
  //RRand(MAX_CLIMATE_ZONES/2, MAX_CLIMATE_ZONES, rTexture);
  #declare fGradYTurbulence = 0; //RRand(0.1, 0.5, rTexture);
  #declare fGradYOmega      = 0; //RRand(0.35, 0.65, rTexture);
  #declare fGradYLambda     = 0; //RRand(1, 2, rTexture);
  #declare fGradScale       = 2*fPlanetRadius;
  #declare fJitter          = RRand(0.05,0.10,rTexture);
  #declare P_SurfaceClimateGradient = pigment { gradient y pigment_map {
     #local I=0; #while(I<1)
        #local iZone  = IRand(1,3,rTexture);
        #switch(iZone)
           #case (1) #declare P_Surface = pigment { mModerate() };   #break
           #case (2) #declare P_Surface = pigment { mMediterran() }; #break
           #case (3) #declare P_Surface = pigment { mArid() };       #break
        #end
        [min(1,I+1/fClimateZones-fJitter) P_Surface scale 1/fGradScale ]
     #local I=I+1/fClimateZones; #end
  } turbulence fGradYTurbulence omega fGradYOmega lambda fGradYLambda
  scale fGradScale phase 0.5 }

  // Planet texture
  // ---------------------------------------------------------------------------
  #declare T_PlanetSurface = texture { pigment { P_SurfaceClimateGradient } finish { surface_finish } }
  
  // Ocean texture
  // ---------------------------------------------------------------------------
  #declare ocean_base_color = Ocean*RRand(0.3,0.8,rOcean);
  
  #declare fSurfaceTurbulence = RRand(0.3, 0.9, rStructure); // complexity of continents
  #declare fSurfaceOmega = RRand(0.35, 0.45, rStructure); // increses disconnected continents
  #declare fSurfaceLambda = RRand(3.5, 6.5, rStructure); // increses coastline roughness
  #declare fSurfacePhase = RRand(0.0, 0.4, rStructure); // different ocean shape
  #declare fSurfacePercent = RRand((1-OCEAN_PERCENTAGE)*0.8, (1-OCEAN_PERCENTAGE), rStructure); // approximate portion of land versus ocean
  #declare fSurfaceScale = 0.5*fPlanetRadius; //0.5*fPlanetRadius;
  #declare iSurfacePattern = IRand(5,15,rStructure); //5-15
  #declare fSurfaceRotation = RRand(0, 360, rStructure);
  #declare fRotateX = RRand(-180,180,rStructure);
  #declare fRotateY = RRand(-180,180,rStructure);
  #declare fRotateZ = RRand(-90,90,rStructure);
  
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
  rotate fRotateZ*z rotate fRotateY*y rotate fRotateX*x } finish { surface_finish } }
  
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
  rotate fRotateZ*z rotate fRotateY*y rotate fRotateX*x } finish { surface_finish } }
  
  #declare T_TestContinents = texture { pigment { GetPattern(iSurfacePattern)
     pigment_map {
        [0.00 P_SurfaceBase scale 1/fSurfaceScale ] //land ini
        [fSurfacePercent P_SurfaceBase scale 1/fSurfaceScale ] //land end
        [fSurfacePercent color rgb <0,0,0> ] //ocean ini
        [1.00 color rgb <0,0,0> ] //ocean end
     }
  turbulence fSurfaceTurbulence omega fSurfaceOmega lambda fSurfaceLambda phase fSurfacePhase scale fSurfaceScale
  rotate fRotateZ*z rotate fRotateY*y rotate fRotateX*x } finish { surface_finish } }
  
  #end //SURFACE_REVISION=2

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

  // Trantor cities
  // ---------------------------------------------------------------------------
  #macro mLightBase(cLightsBase,bType,rLight)
     #if (bType=0) //surface
        #local fDensity = RRand(0.0,0.05,rLight);
        #local fIntensity = RRand(0.5,1.5,rLight);
     #else //lights
        #local fDensity = RRand(0.8,0.9,rLight);
        #local fIntensity = RRand(10,30,rLight);
     #end      
     [0.0 transmit 1 ] // unlit area
     [fDensity cLightsBase*fIntensity ] // controls light density; 0.1 =high, 0.9=low
     [1.0 cLightsBase*fIntensity ] // controls light density; 0.1 =high, 0.9=low
  #end
  
  #macro mLightmap(fExtension,cLightsBase,bType,rLight)
     #local fScale = RRand(20,40,rLight);
     #local iPattern = IRand(6, 9, rLight);
     [0.0 GetPattern(iPattern) pigment_map { mLightBase(cLightsBase,bType,rLight) } scale fScale turbulence 0]  // controls spread
     [fExtension rgb 0 transmit 1 ] // controls max lights extension; 0=no lights; 1=full lights
  #end
  
  #macro mLight(cLightsBase,bType,rLight)
     #if (bType=0) //surface
        #local fExtension = RRand(0.95,1.0,rLight); //0=no lights; 1=full lights
        #local fPercent = RRand(0.9,1.0,rLight); //strength
     #else //lights
        #local fExtension = RRand(0.35,0.65,rLight); // How many lights are really visible //0.5-0.8
        #local fPercent = RRand(0.9,0.9,rLight); //strength
     #end      
     #local fScale = RRand(0.001, 0.01, rLight);
     #local iPattern = IRand(6, 9, rLight);
     #local fTurbulence = RRand(1.0, 7.0, rLight);
     #local fPhase = 0; //RRand(0.20, 0.90, rLight);
     #local fLambda = RRand(2.0,4.0,rLight); // controls coastline //0.0,1.0
     #local fOmega = RRand(0.35,0.55,rLight); // controls islands //0.00,0.30
     GetPattern(iPattern)
        pigment_map {
           [0.00 bozo pigment_map {mLightmap(fExtension,cLightsBase,bType,rLight)} scale 1/fSurfaceScale ] //lights ini
           [fPercent bozo pigment_map {mLightmap(fExtension/3,cLightsBase,bType,rLight)} scale 1/fSurfaceScale] //lights end
           [fPercent transmit 1 ] [1.00 transmit 1 ]
        }
     turbulence fTurbulence omega fOmega lambda fLambda phase fPhase scale fScale*fPlanetRadius
  #end

  #macro mTrantorCircle(fSize,fRings,bType,rLight)
     function { max(0,x) }
        pigment_map {
           [0.0 transmit 1 ] //outside
           #local I=fRings; #while(I>0) // the different rings
              #if (bType=0) //surface
                 //#local cLightsBase = surface_color_mono(surface_base_color,surface_color_deviation,rLight);
                 #local cLightsBase = VariateColor(aBaseColors[IRand(0,dimension_size(aBaseColors,1)-1,rColor)]*0.1, fColorDev*0.1, bMonoColor, rLight);
                 #local fTransGrad = RRand(0.0,0.1,rLight); //controls the smoothness of light circle edges and the apparent distance between them
              #else //lights
                 #local cLightsBase = VariateColor(LIGHT_BASE_COLOR, fColorDev*0.1, 0, rLight);
                 #local fTransGrad = RRand(0.1,0.4,rLight); //controls the smoothness of light circle edges and the apparent distance between them
              #end      
              #local P_SurfaceLights = pigment { mLight(cLightsBase,bType,rLight) };
              #local fRadiusOuter = 1-I*fSize/fRings;
              #local fThickness   = fSize/fRings;
                 [fRadiusOuter transmit 1 ] //outside
                 [fRadiusOuter+fThickness*fTransGrad P_SurfaceLights scale fRadiusOuter/fSurfaceScale ]
                 [fRadiusOuter+fThickness*(1-fTransGrad) P_SurfaceLights scale fRadiusOuter/fSurfaceScale ]
                 [fRadiusOuter+fThickness transmit 1]
           #local I=I-1; #end
           [1.0 transmit 1] //inside         
        } scale fPlanetRadius
  #end

  #macro T_TrantorCity(fSize,fRings,rotz,roty,rotx,bType,rLight) // non-transparent, not limited to continents
        texture { pigment { mTrantorCircle(fSize,fRings,bType,rLight)
              rotate fRotateZ*z rotate fRotateY*y rotate fRotateX*x //geographical position
        } finish { surface_finish } }
  #end //macro
  
  #macro T_TrantorCities(bType) // non-transparent, not limited to continents
    #declare  rLight = seed(iSeedNumLight);
    #local I=0; #while(I<NUM_LIGHTMAPS)
      #local fRings = RRand(4,6,rLight);
      #local fSize = RRand(0.01,0.05,rLight);
      #local fJitter = RRand(-0.4,0.4,rLight);
      #local fRotateZ = 0; //RRand(-180,180,rLight);
      #local fRotateY = I*(360/NUM_LIGHTMAPS)*(1+fJitter);
      #local fRotateX = RRand(-70,70,rLight);
      T_TrantorCity(fSize,fRings,fRotateZ,fRotateY,fRotateX,bType,rLight)
    #local I=I+1; #end
  #end //macro

  // Trantor highways
  // ---------------------------------------------------------------------------
  #macro mHighway(fWidth,fLength)
     box { <-fLength, -fWidth/2, 0>  <fLength, fWidth/2, -fPlanetRadius*1.1> }
  #end
  
  #macro mHighwayLightBase(cLightsBase,bType,rLight)
     #if (bType=0) //surface
        #local fDensity = RRand(0.0,0.1,rLight);
        #local fIntensity = RRand(0.5,1.0,rLight);
     #else //lights
        #local fDensity = RRand(0.8,0.9,rLight);
        #local fIntensity = RRand(10,20,rLight);
     #end      
     [0.0 transmit 1 ] // unlit area
     [fDensity cLightsBase*fIntensity ] // controls light density; 0.1 =high, 0.9=low
  #end
  
  #macro mHighwayLightmap(fExtension,cLightsBase,bType,rLight)
     #local fScale = RRand(20,40,rLight);
     #local iPattern = IRand(6, 9, rLight);
     [0.0 GetPattern(iPattern) pigment_map { mHighwayLightBase(cLightsBase,bType,rLight) } scale fScale turbulence 0]  // controls spread
     [fExtension rgb 0 transmit 1 ] // controls max lights extension; 0=no lights; 1=full lights
  #end

  #macro mHighwayLight(cLightsBase,bType,rLight)
    #local fIntensity = RRand(10,20,rLight);
    #if (bType=0) //surface
      #local fExtension = RRand(0.9,1.0,rLight); //0.8
      #local fPercent = RRand(0.9,1.0,rLight);
    #else //lights
      #local fExtension = RRand(0.35,0.65,rLight); //density - how many lights are visible
      #local fPercent = RRand(0.9,0.9,rLight); //strength
    #end      
    #local fScale = RRand(0.001, 0.01, rLight);
    #local iPattern = IRand(6, 9, rLight);
    #local fTurbulence = RRand(0.0, 7.0, rLight);
    #local fPhase = 0; //RRand(0.20, 0.90, rLight);
    #local fLambda = RRand(0.0,1.0,rLight); // controls coastline
    #local fOmega = RRand(0.00,0.30,rLight); // controls islands
    GetPattern(iPattern)
      pigment_map {
         [0.00 bozo pigment_map {mHighwayLightmap(fExtension,cLightsBase,bType,rLight)} scale 1/fSurfaceScale ] //lights ini
         [fPercent bozo pigment_map {mHighwayLightmap(fExtension/3,cLightsBase,bType,rLight)} scale 1/fSurfaceScale] //lights end
         [fPercent transmit 1 ] [1.00 transmit 1 ]
      }
    turbulence fTurbulence omega fOmega lambda fLambda phase fPhase scale fScale*fPlanetRadius
  #end
  
  #macro mHighways(iHighways,bType,rLight)
    object { union {
      #if (bType=0) //surface
         #local cLightsBase = VariateColor(aBaseColors[IRand(0,dimension_size(aBaseColors,1)-1,rColor)]*0.1, fColorDev*0.1, bMonoColor, rLight);
      #else //lights
         #local cLightsBase = VariateColor(LIGHT_BASE_COLOR, fColorDev*0.1, 0, rLight);
      #end      
      #local P_HighwayLights = pigment { mHighwayLight(cLightsBase,bType,rLight) };
      #local i=0; #while (i<iHighways) //no of highways
         #local fWidth  = fPlanetRadius*RRand(0.001,0.01,rLight);
         #local fLength = fPlanetRadius*RRand(0.2,0.6,rLight);
         #local fRotateZ = RRand(-180,180,rLight);
         #local fRotateY = RRand(-180,180,rLight);
         #local fRotateX = RRand(-90,90,rLight);
         #local oHighway = object { mHighway(fWidth,fLength) };
         object { oHighway 
            rotate fRotateZ*z rotate fRotateY*y rotate fRotateX*x //geographical position
         }
       #local i=i+1; #end         
     } pigment { transmit 1 } pigment { P_HighwayLights }
     } 
  #end //macro

  #macro T_Highways(bType)
    #declare  rLight = seed(iSeedNumLight);
    #local I=0; #while(I<10)
      #local iHighways = 50; //500
      #local P_Highways = pigment { mHighways(iHighways,bType,rLight) };
      texture { pigment { P_Highways } finish { surface_finish } }
    #local I=I+1; #end
  #end //macro
  
  #declare bTrantorSurface = 0;
  #declare bTrantorLights  = 1;

  // ---------------------------------------------------------------------------
  // Final Surface Texture Macro
  // ---------------------------------------------------------------------------
  #declare render_mode = 1; //0-debug; 1-regular render; 2-surface; 3-lights

  // Final Surface Texture Macro
  #if (render_mode=0) // just for debugging different things separately
    #macro mPlanetSurface()
      texture { T_PlanetSurface }
      //T_TrantorCities(bTrantorSurface) //surface artifacts
      //T_Highways(bTrantorSurface)

      #declare surface_finish_prev = surface_finish;
      #declare surface_finish = finish { ambient 1.0 }
      T_TrantorCities(bTrantorLights) //surface artifacts
      T_Highways(bTrantorLights)
      #declare surface_finish = surface_finish_prev;
      finish { surface_finish }

      texture { T_OceanSurface }
      texture { T_OceanDepth }
      texture { T_ArcticTexture }
    #end // planet surface texture
  #end

  #if (render_mode=1) // this is the real normal rendering, all inclusive
    #macro mPlanetSurface()
      texture { pigment { P_OceanTexture } finish { surface_finish } }
      texture { T_PlanetSurface }
      T_TrantorCities(bTrantorSurface) //surface artifacts
      T_Highways(bTrantorSurface)

      #if (NUM_LIGHTMAPS>0)
        #declare surface_finish_prev = surface_finish;
        #declare surface_finish = finish { ambient 1.0 }
        T_TrantorCities(bTrantorLights) //lights
        T_Highways(bTrantorLights)
        #declare surface_finish = surface_finish_prev;
        finish { surface_finish }
      #end

      #if (NUM_RIVERS>0) T_River() #end
      texture { T_OceanSurface }
      texture { T_OceanDepth }
      #if (ICE_SHAPE_NUMBER>0 | frame_number=0)
        texture { T_ArcticTexture }
      #end

    #end // planet surface texture
  #end

  #if (render_mode=2) // for texturing: render the surface only, without lights
    #macro mPlanetSurface()
      texture { T_PlanetSurface }

      T_TrantorCities(bTrantorSurface) //lights
      T_Highways(bTrantorSurface)

      #if (NUM_RIVERS>0) T_River() #end
      texture { T_OceanSurface }
      texture { T_OceanDepth }
      #if (ICE_SHAPE_NUMBER>0 | frame_number=0)
        texture { T_ArcticTexture }
      #end
      finish { surface_finish }
      
    #end // planet surface texture
  #end //debug_mode

  #if (render_mode=3) // rendering the lights only, use +UA to render transparent image
    #macro mPlanetSurface()
      texture { T_PlanetSurface }

      #declare surface_finish_prev = surface_finish;
      #declare surface_finish = finish { ambient 1.0 }
      finish { surface_finish }
      T_TrantorCities(bTrantorLights) //lights
      T_Highways(bTrantorLights)
      #declare surface_finish = surface_finish_prev;

      texture { T_OceanDepth }
    #end // planet surface texture
  #end //debug_mode

  sphere {<0, 0, 0>, fPlanetRadius
    mPlanetSurface()
    //finish { surface_finish }
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

//EOF
