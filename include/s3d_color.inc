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
// @file    : s3d_color.inc
// @brief   : Color macros
// @version : 2019-05-30
// @created : 2011-03-30
// @author  : pyramid
// @internet: https://openteq.wordpress.com/portfolio/space3d/
// @scale   : 1 POV unit = 1 km
// ---------------------------------------------------------------------------
// MACROS
//  InitColors()   
//    - required to init color presets
//  ColorHSL()     
//    - get colors by hue, saturation, and lightness
//  RandomColor(iColor, rColor, fColorDev)
//    - get random color in hue 0: random,  1-9: reddish to violet, 10-14:mono blueish to whitish
//    - fColorDev [0..1]
//  VariateColor()
//    - variate a base color by given amount, and mono or polychromity
//  GetPattern()
//    - get a random pattern
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// Global Settings
// ---------------------------------------------------------------------------
#version 3.6;

// ---------------------------------------------------------------------------
// Include Files
// ---------------------------------------------------------------------------
#include "rand.inc" // random number generation macros

// ---------------------------------------------------------------------------
// Color Definitions
// ---------------------------------------------------------------------------
#ifndef (cAtmosphereColor) #declare cAtmosphereColor = rgb <0.6, 0.8, 1.0>; #end

#macro InitColors()

  //tmp only
   //#declare cSoil = array [10];
   //#declare cForrest = array [10];
   //#declare cFields = array [10];
   //#declare cDesert = array [10];
   //#declare cJungle = array [10];
  //tmp
  
  // Greens - sorted by green color component
  #declare cGreen = array [56];
  #declare cGreen[0]  = rgb <0.788, 0.987, 0.663>;
  #declare cGreen[1]  = rgb <0.827, 0.976, 0.643>;
  #declare cGreen[2]  = rgb <0.427, 0.976, 0.343>;
  #declare cGreen[3]  = rgb <0.641, 0.840, 0.516>; //green forest
  #declare cGreen[4]  = rgb <0.441, 0.840, 0.416>; //green forest
  #declare cGreen[5]  = rgb <0.702, 0.808, 0.490>;
  #declare cGreen[6]  = rgb <0.402, 0.808, 0.290>;
  #declare cGreen[7]  = rgb <0.643, 0.788, 0.424>;
  #declare cGreen[8]  = rgb <0.589, 0.788, 0.464>; //green grass
  #declare cGreen[9]  = rgb <0.572, 0.771, 0.447>; //green fade
  #declare cGreen[10] = rgb <0.592, 0.741, 0.400>;
  #declare cGreen[11] = rgb <0.298, 0.710, 0.220>;
  #declare cGreen[12] = rgb <0.502, 0.702, 0.329>;
  #declare cGreen[13] = rgb <0.288, 0.687, 0.263>;
  #declare cGreen[14] = rgb <0.600, 0.678, 0.400>;
  #declare cGreen[15] = rgb <0.549, 0.635, 0.388>;
  #declare cGreen[16] = rgb <0.408, 0.627, 0.341>;
  #declare cGreen[17] = rgb <0.420, 0.588, 0.224>;
  #declare cGreen[18] = rgb <0.404, 0.588, 0.212>;
  #declare cGreen[19] = rgb <0.289, 0.588, 0.164>; //green grass
  #declare cGreen[20] = rgb <0.243, 0.588, 0.024>;
  #declare cGreen[21] = rgb <0.451, 0.573, 0.353>;
  #declare cGreen[22] = rgb <0.388, 0.573, 0.259>;
  #declare cGreen[23] = rgb <0.475, 0.565, 0.290>;
  #declare cGreen[24] = rgb <0.369, 0.541, 0.208>;
  #declare cGreen[25] = rgb <0.192, 0.541, 0.000>;
  #declare cGreen[26] = rgb <0.000, 0.540, 0.000>; //very green
  #declare cGreen[27] = rgb <0.329, 0.514, 0.208>;
  #declare cGreen[28] = rgb <0.388, 0.498, 0.204>;
  #declare cGreen[29] = rgb <0.304, 0.488, 0.112>;
  #declare cGreen[30] = rgb <0.263, 0.482, 0.196>;
  #declare cGreen[31] = rgb <0.200, 0.478, 0.000>;
  #declare cGreen[32] = rgb <0.075, 0.465, 0.090>;
  #declare cGreen[33] = rgb <0.263, 0.455, 0.145>;
  #declare cGreen[34] = rgb <0.249, 0.435, 0.088>;
  #declare cGreen[35] = rgb <0.120, 0.400, 0.000>;
  #declare cGreen[36] = rgb <0.318, 0.391, 0.173>;
  #declare cGreen[37] = rgb <0.118, 0.391, 0.073>;
  #declare cGreen[38] = rgb <0.318, 0.341, 0.173>;
  #declare cGreen[39] = rgb <0.212, 0.341, 0.024>;
  #declare cGreen[40] = rgb <0.153, 0.329, 0.100>;
  #declare cGreen[41] = rgb <0.153, 0.329, 0.000>;
  #declare cGreen[42] = rgb <0.2627, 0.3098, 0.1451>;
  #declare cGreen[43] = rgb <0.102, 0.302, 0.029>;
  #declare cGreen[44] = rgb <0.100, 0.300, 0.000>;
  #declare cGreen[45] = rgb <0.188, 0.286, 0.031>;
  #declare cGreen[46] = rgb <0.127, 0.251, 0.000>;
  #declare cGreen[47] = rgb <0.160, 0.250, 0.000>;
  #declare cGreen[48] = rgb <0.150, 0.220, 0.000>;
  #declare cGreen[49] = rgb <0.100, 0.210, 0.000>;
  #declare cGreen[50] = rgb <0.150, 0.200, 0.000>;
  #declare cGreen[51] = rgb <0.100, 0.200, 0.000>;
  #declare cGreen[52] = rgb <0.090, 0.200, 0.000>;
  #declare cGreen[53] = rgb <0.080, 0.190, 0.000>;
  #declare cGreen[54] = rgb <0.140, 0.160, 0.000>;
  #declare cGreen[55] = rgb <0.120, 0.050, 0.000>;

  //Stone - greyish to dark brownish tones
  #declare cStone = array [53];
  #declare cStone[0]  = rgb <0.934, 0.933, 0.609>; //brown light fields
  #declare cStone[1]  = rgb <0.879, 0.878, 0.754>; //grey stone
  #declare cStone[2]  = rgb <0.865, 0.741, 0.316>;
  #declare cStone[3]  = rgb <0.788, 0.996, 0.663>; //brown light stone
  #declare cStone[4]  = rgb <0.757, 0.741, 0.565>;
  #declare cStone[5]  = rgb <0.754, 0.953, 0.629>; //brown stone
  #declare cStone[6]  = rgb <0.734, 0.933, 0.609>; //brown light fields
  #declare cStone[7]  = rgb <0.7020, 0.6588, 0.4824>;  
  #declare cStone[8]  = rgb <0.694, 0.639, 0.455>;
  #declare cStone[9]  = rgb <0.675, 0.584, 0.412>;
  #declare cStone[10] = rgb <0.675, 0.484, 0.412>;
  #declare cStone[11] = rgb <0.659, 0.324, 0.071>;
  #declare cStone[12] = rgb <0.616, 0.565, 0.392>;
  #declare cStone[13] = rgb <0.612, 0.573, 0.518>;
  #declare cStone[14] = rgb <0.608, 0.616, 0.431>;
  #declare cStone[15] = rgb <0.600, 0.490, 0.443>;
  #declare cStone[16] = rgb <0.580, 0.510, 0.322>;
  #declare cStone[17] = rgb <0.549, 0.557, 0.412>;
  #declare cStone[18] = rgb <0.533, 0.310, 0.169>;
  #declare cStone[19] = rgb <0.522, 0.435, 0.290>;
  #declare cStone[20] = rgb <0.4824, 0.5098, 0.2510>;
  #declare cStone[21] = rgb <0.455, 0.435, 0.271>;
  #declare cStone[22] = rgb <0.455, 0.400, 0.255>;
  #declare cStone[23] = rgb <0.434, 0.533, 0.109>;
  #declare cStone[24] = rgb <0.420, 0.402, 0.160>;
  #declare cStone[25] = rgb <0.400, 0.384, 0.278>;
  #declare cStone[26] = rgb <0.380, 0.310, 0.122>;
  #declare cStone[27] = rgb <0.373, 0.341, 0.275>;
  #declare cStone[28] = rgb <0.349, 0.357, 0.212>;
  #declare cStone[29] = rgb <0.333, 0.310, 0.169>;
  #declare cStone[30] = rgb <0.322, 0.235, 0.090>;
  #declare cStone[31] = rgb <0.318, 0.329, 0.224>;
  #declare cStone[32] = rgb <0.318, 0.229, 0.124>;
  #declare cStone[33] = rgb <0.316, 0.265, 0.092>;
  #declare cStone[34] = rgb <0.282, 0.302, 0.212>;
  #declare cStone[35] = rgb <0.279, 0.178, 0.054>;
  #declare cStone[36] = rgb <0.275, 0.184, 0.012>;
  #declare cStone[37] = rgb <0.261, 0.165, 0.043>;
  #declare cStone[38] = rgb <0.259, 0.224, 0.071>;
  #declare cStone[39] = rgb <0.257, 0.241, 0.065>;
  #declare cStone[40] = rgb <0.255, 0.235, 0.071>;
  #declare cStone[41] = rgb <0.255, 0.200, 0.055>;
  #declare cStone[42] = rgb <0.2392, 0.1686, 0.0902>;
  #declare cStone[43] = rgb <0.234, 0.233, 0.109>;
  #declare cStone[44] = rgb <0.212, 0.173, 0.018>;
  #declare cStone[45] = rgb <0.200, 0.190, 0.043>;
  #declare cStone[46] = rgb <0.200, 0.184, 0.078>;
  #declare cStone[47] = rgb <0.194, 0.139, 0.055>;
  #declare cStone[48] = rgb <0.188, 0.196, 0.163>;
  #declare cStone[49] = rgb <0.165, 0.141, 0.016>;
  #declare cStone[50] = rgb <0.161, 0.165, 0.043>;
  #declare cStone[51] = rgb <0.154, 0.153, 0.029>;
  #declare cStone[52] = rgb <0.108, 0.116, 0.031>;

  //Sand - light brownish to yellowish tones
  #declare cSand = array [38];
  #declare cSand[0]  = rgb <0.969, 0.918, 0.792>;
  #declare cSand[1]  = rgb <0.969, 0.875, 0.839>;
  #declare cSand[2]  = rgb <0.961, 0.929, 0.839>;
  #declare cSand[3]  = rgb <0.894, 0.749, 0.678>;
  #declare cSand[4]  = rgb <0.865, 0.764, 0.740>; //brown sand
  #declare cSand[5]  = rgb <0.855, 0.706, 0.624>;
  #declare cSand[6]  = rgb <0.850, 0.600, 0.600>;
  #declare cSand[7]  = rgb <0.822, 0.604, 0.410>;
  #declare cSand[8]  = rgb <0.808, 0.667, 0.580>;
  #declare cSand[9]  = rgb <0.788, 0.635, 0.463>;
  #declare cSand[10] = rgb <0.780, 0.675, 0.639>;
  #declare cSand[11] = rgb <0.722, 0.604, 0.510>;
  #declare cSand[12] = rgb <0.7020, 0.6588, 0.1224>;
  #declare cSand[13] = rgb <0.596, 0.490, 0.408>;
  #declare cSand[14] = rgb <0.569, 0.375, 0.239>;
  #declare cSand[15] = rgb <0.580, 0.475, 0.439>;
  #declare cSand[16] = rgb <0.549, 0.443, 0.384>;
  #declare cSand[17] = rgb <0.541, 0.412, 0.353>;
  #declare cSand[18] = rgb <0.494, 0.249, 0.178>;
  #declare cSand[19] = rgb <0.490, 0.408, 0.302>;
  #declare cSand[20] = rgb <0.479, 0.278, 0.054>;
  #declare cSand[21] = rgb <0.465, 0.265, 0.140>;
  #declare cSand[22] = rgb <0.461, 0.329, 0.139>;
  #declare cSand[23] = rgb <0.455, 0.306, 0.124>;
  #declare cSand[24] = rgb <0.450, 0.278, 0.199>;
  #declare cSand[25] = rgb <0.420, 0.362, 0.310>;
  #declare cSand[26] = rgb <0.404, 0.303, 0.194>;
  #declare cSand[27] = rgb <0.388, 0.235, 0.063>;
  #declare cSand[28] = rgb <0.373, 0.291, 0.235>;
  #declare cSand[29] = rgb <0.369, 0.218, 0.092>;
  #declare cSand[30] = rgb <0.322, 0.204, 0.110>;
  #declare cSand[31] = rgb <0.308, 0.167, 0.080>;
  #declare cSand[32] = rgb <0.280, 0.175, 0.039>;
  #declare cSand[33] = rgb <0.249, 0.193, 0.084>;
  #declare cSand[34] = rgb <0.241, 0.182, 0.053>;
  #declare cSand[35] = rgb <0.206, 0.090, 0.008>;
  #declare cSand[36] = rgb <0.190, 0.108, 0.002>;
  #declare cSand[37] = rgb <0.104, 0.033, 0.004>;
  
  //Mediterran - obsolete, legacy only
  #declare cMediterran = array [2];
  #declare cMediterran[0] = rgb <0.420, 0.402, 0.360>;
  #declare cMediterran[1] = rgb <0.373, 0.341, 0.275>;

  //Ocean - sort by blue component
  #declare cOcean = array [15];
  #declare cOcean[0]  = rgb <0.202, 0.259, 0.922>;
  #declare cOcean[1]  = rgb <0.063, 0.800, 0.822>;
  #declare cOcean[2]  = rgb <0.063, 0.600, 0.822>;
  #declare cOcean[3]  = rgb <0.063, 0.400, 0.822>;
  #declare cOcean[4]  = rgb <0.149, 0.435, 0.698>;
  #declare cOcean[5]  = rgb <0.013, 0.200, 0.622>;
  #declare cOcean[6]  = rgb <0.000, 0.000, 0.622>;
  #declare cOcean[7]  = rgb <0.210, 0.250, 0.600>; // flat ocean
  #declare cOcean[8]  = rgb <0.180, 0.220, 0.480>;
  #declare cOcean[9]  = rgb <0.170, 0.210, 0.470>; // deep ocean 
  #declare cOcean[10] = rgb <0.013, 0.100, 0.422>;
  #declare cOcean[11] = rgb <0.000, 0.000, 0.422>;
  #declare cOcean[12] = rgb <0.125, 0.192, 0.290>;
  #declare cOcean[13] = rgb <0.013, 0.100, 0.222>;
  #declare cOcean[14] = rgb <0.000, 0.000, 0.222>;

  //Test colors
/*
  #declare cTest = array [7];
  #declare cTest[0] = color rgb <1.00, 0.000, 0.000>; //red
  #declare cTest[1] = color rgb <0.000, 1.000, 0.000>; //green
  #declare cTest[2] = color rgb <0.000, 0.000, 1.000>; //blue
  #declare cTest[3] = color rgb <1.000, 1.000, 1.000>; //white
  #declare cTest[4] = color rgb <1.000, 1.000, 0.000>; //yellow
  #declare cTest[5] = color rgb <1.000, 0.000, 1.000>; //magenta
  #declare cTest[6] = color rgb <0.000, 1.000, 1.000>; //cyan
*/
#end

#macro GeneratePlanetColorSet(aBaseColors)
  InitColors()

  #if (aBaseColors[0].red=0 & aBaseColors[0].green=0 & aBaseColors[0].blue=0)
    #local iColNum = 0;
  #else
    #local iColNum = dimension_size(aBaseColors,1);
  #end

  #declare iMinIntensity = 37; //min(dimension_size(cGreen,1),dimension_size(cStone,1),dimension_size(cSand,1)); 
  #declare iRelativeIntensity = IRand(0, iMinIntensity-1,rColor); 

  #declare iMinIntensity = 37; //min(dimension_size(cGreen,1),dimension_size(cStone,1),dimension_size(cSand,1)); 
  #declare iRelativeIntensity = IRand(0, iMinIntensity-1,rColor); 
  #declare cSoil = array [10]; #local c=0; #while (c<10)
    #if (iColNum>=1) //Soil
      #declare cBase  = VariateColor(aBaseColors[0], fColorDev, bMonoColor, rColor);
    #else
      #declare cBase = cStone[iRelativeIntensity]; //*fIntensity;
    #end
    #declare cSoil[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end

  #declare cForrest = array [10]; #local c=0; #while (c<10)
    #if (iColNum>=2) //Forrest
      #declare cBase  = VariateColor(aBaseColors[1], fColorDev, bMonoColor, rColor);
    #else
      #declare cBase = cGreen[iRelativeIntensity]; //*fIntensity;
    #end
    #declare cForrest[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end

  #declare cHill = array [10]; #local c=0; #while (c<10)
    #if (iColNum>=3) //Hills
      #declare cBase  = VariateColor(aBaseColors[2], fColorDev, bMonoColor, rColor);
    #else
      #declare cBase = cStone[iRelativeIntensity]; //*fIntensity;
    #end
    #declare cHill[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end

  #declare cDesert = array [10]; #local c=0; #while (c<10)
    #if (iColNum>=4) //Desert
      #declare cBase  = VariateColor(aBaseColors[3], fColorDev, bMonoColor, rColor);
    #else
      #declare cBase = cSand[iRelativeIntensity]; //*fIntensity;
    #end
    #declare cDesert[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end

  #declare cJungle = array [10]; #local c=0; #while (c<10)
    #if (iColNum>=5) //Jungle
      #declare cBase  = VariateColor(aBaseColors[4], fColorDev, bMonoColor, rColor);
    #else
      #declare cBase = cGreen[iRelativeIntensity]; //*fIntensity;
    #end
    #declare cJungle[c] = VariateColor(cBase,fColorDev,bMonoColor,rColor);
  #local c=c+1; #end

  #if (iColNum>=6) //Ocean
    #declare Ocean  = VariateColor(aBaseColors[5], fColorDev, bMonoColor, rOcean);
  #else
    #local cColor = cOcean[IRand(0,dimension_size(cOcean,1)-1,rOcean)];
    #declare Ocean  = VariateColor(cColor, fColorDev, bMonoColor, rOcean);
  #end

#end

// ---------------------------------------------------------------------------
// Macros
// ---------------------------------------------------------------------------

#macro ColorHSL(h, s, l) //Hue, Saturation, Lightness
//h range 0-360
//  with: 0-red; 21-brown; 30-orange; 59-yellow; 120-green; 179-cyan; 240-blue; 300-magenta;
//s,l range 0-100
//source: http://en.wikipedia.org/wiki/HSL_and_HSV

	#local s = s/100;
	#local l = l/100;
  #local hue = h/360;
	#if (s = 0) //undefined rgb for s=0
		#local r = l;
		#local g = l;
		#local b = l;
	#else
		#if (l <= 0.5)
			#local q = l * (s + 1);
		#else
			#local q = l + s - (l * s);
		#end
		#local p = (l * 2) - q;
		#local r = Hue2Rgb(p, q, hue + 1/3);
		#local g = Hue2Rgb(p, q, hue);
		#local b = Hue2Rgb(p, q, hue - 1/3);
	#end
	rgb <r, g, b>;

#end //macro

#macro Hue2Rgb(m1,m2,hue)

  #if (hue<0) 
    #local hue = hue+1;
  #else
    #if (hue>1) #local hue = hue-1; #end
  #end
  #if (6*hue<1)
    #local value = m1 + ((m2 - m1) * hue * 6); 
  #else
    #if (2 * hue < 1)
    	#local value = m2;
    #else
      #if (3 * hue < 2)
		    #local value = m1 + ((m2 - m1) * (2/3 - hue) * 6);
      #else
		    #local value = m1;
      #end  
    #end
  #end
  value

#end //macro


#macro RandomColor(iColor, rColor, fColorDev)
  #switch (iColor)
    #case (0) color rgb <RRand(0.3,0.7,rColor), RRand(0.3,0.7,rColor), RRand(0.3,0.7,rColor)>; #break //random
    #case (1) color rgb <RRand(0.8,1.0,rColor), RRand(0.3,0.5,rColor), RRand(0.3,0.5,rColor)>; #break //light redish
    #case (2) color rgb <RRand(0.6,0.8,rColor), RRand(0.2,0.3,rColor), RRand(0.2,0.3,rColor)>; #break //redish
    #case (3) color rgb <RRand(0.8,1.0,rColor), RRand(0.5,0.7,rColor), RRand(0.1,0.2,rColor)>; #break //orange
    #case (4) color rgb <RRand(0.6,0.8,rColor), RRand(0.3,0.4,rColor), RRand(0.0,0.1,rColor)>; #break //orange
    #case (5) color rgb <RRand(0.7,0.8,rColor), RRand(0.7,0.8,rColor), RRand(0.0,0.1,rColor)>; #break //yellowish-whitish
    #case (6) color rgb <RRand(0.8,1.0,rColor), RRand(0.8,1.0,rColor), RRand(0.0,0.1,rColor)>; #break //yellowish
    #case (7) color rgb <RRand(0.5,0.9,rColor), RRand(0.5,0.9,rColor), RRand(0.0,0.1,rColor)>; #break //yellow-greenish
    #case (8) color rgb <RRand(0.4,0.6,rColor), RRand(0.4,0.6,rColor), RRand(0.8,1.0,rColor)>; #break //light blueish
    #case (9) color rgb <RRand(0.6,1.0,rColor), RRand(0.1,0.3,rColor), RRand(0.6,1.0,rColor)>; #break //violet
    #case (10) VariateColor_mono(<0.2, 0.2, 1.0>, fColorDev, rColor); #break //dark blue
    #case (11) VariateColor_mono(<0.4, 0.4, 1.0>, fColorDev, rColor); #break //blueish
    #case (12) VariateColor_mono(<0.6, 0.6, 1.0>, fColorDev, rColor); #break //blueish
    #case (13) VariateColor_mono(<0.8, 0.8, 1.0>, fColorDev, rColor); #break //blueish
    #case (14) VariateColor_mono(<0.9, 0.9, 1.0>, fColorDev, rColor); #break //whiteish
  #end
#end

// Randomize Color
// ---------------------------------------------------------------------------
#macro VariateColor(cBaseColor, fColDev, bMonoColor, rColor)
  #if (bMonoColor)
    #local detail_intensity = RRand(1-fColDev/255, 1+fColDev/255, rColor);
    #declare col_dev = RRand(-fColDev/255,fColDev/255,rColor);
    #declare r = cBaseColor.red*detail_intensity+col_dev;
    #declare g = cBaseColor.green*detail_intensity+col_dev;
    #declare b = cBaseColor.blue*detail_intensity+col_dev;
  #else
    #local detail_intensity = RRand(1-fColDev/255, 1+fColDev/255, rColor);
    #declare base_color_component = IRand(1,3,rColor);
    #declare r = cBaseColor.red;
    #declare g = cBaseColor.green;
    #declare b = cBaseColor.blue;
    #if (base_color_component=1)
       #declare r = cBaseColor.red*detail_intensity+RRand(-fColDev/255,fColDev/255,rColor);
    #end
    #if (base_color_component=2)
       #declare g = cBaseColor.green*detail_intensity+RRand(-fColDev/255,fColDev/255,rColor);
    #end
    #if (base_color_component=3)
       #declare b = cBaseColor.blue*detail_intensity+RRand(-fColDev/255,fColDev/255,rColor);
    #end
  #end
  color rgb <r, g, b>
#end //macro

// ---------------------------------------------------------------------------

#macro GetPattern(pattern_method)
  #switch(pattern_method)
    //spotty
    #case (1)  bozo       scale 1   #break
    #case (2)  bumps      scale 1   #break
    #case (3)  cells      scale 1   #break
    #case (4)  dents      scale 1   #break
    #case (5)  spotted    scale 1   #break
    #case (6)  quilted    scale 3   #break
  
    //stringy
    #case (7)  agate      scale 10  #break
    #case (8)  granite    scale 10  #break
    #case (9)  crackle    scale 5   #break
    #case (10) marble     scale 2   #break
    #case (11) spiral1 5  scale 30  #break
    #case (12) onion      scale 2   #break
  
    //other
    #case (13) leopard    scale 0.3 #break
    #case (14) waves      scale 0.1 #break
    #case (15) wrinkles   scale 1   #break
    #case (16) ripples    scale 0.5 #break
    #case (17) gradient y scale 3   #break 
    #case (18) gradient x scale 3   #break
    #case (19) gradient z scale 2   #break
    #case (20) radial     scale 10  #break
  #end //switch
#end //macro

// ---------------------------------------------------------------------------
// Old Macros for legacy compatibility
// ---------------------------------------------------------------------------

#macro VariateColor_mono(base_color_tone, color_deviation, rSeed)
   #local base_color_dev = RRand(-color_deviation/255,color_deviation/255,rSeed);
   #local dummy = RRand(0,1,rSeed); //required to have the same result when using chromo
   #local r = base_color_tone.red+base_color_dev;
   #local g = base_color_tone.green+base_color_dev;
   #local b = base_color_tone.blue+base_color_dev;
   color rgb <r, g, b>
#end

#macro VariateColor_chromo(base_color_tone, color_deviation, rSeed)
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
#end // surface_color_mono macro

// Randomize Color - OLD
// ---------------------------------------------------------------------------
#macro surface_color_mono(base_color_tone, color_deviation, rSeed)
   #local base_color_dev = RRand(-color_deviation/255,color_deviation/255,rSeed);
   #local dummy = RRand(0,1,rSeed); //required to have the same result when using chromo
   #local r = base_color_tone.red+base_color_dev;
   #local g = base_color_tone.green+base_color_dev;
   #local b = base_color_tone.blue+base_color_dev;
   color rgb <r, g, b>
#end // surface_color_mono macro

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
#end // surface_color_mono macro

#macro surface_color_random(base_color_tone, color_deviation, rSeed)
   // color deviation settings
   #declare detail_intensity = RRand(0.9, 1.1, rColor); //0.5-1.1
   //#declare base_color_dev = color_deviation/100;
   #if (surface_mono_color)
      #declare base_color_dev = RRand(-color_deviation/255,color_deviation/255,rSeed);
      #local dummy = RRand(0,1,rSeed); //required to have the same result when using chromo
      #declare r = base_color_tone.red+base_color_dev;
      #declare g = base_color_tone.green+base_color_dev;
      #declare b = base_color_tone.blue+base_color_dev;
   #else
      #declare base_color_component = IRand(1,3,rSeed);
      #declare r = base_color_tone.red;
      #declare g = base_color_tone.green;
      #declare b = base_color_tone.blue;
      #if (base_color_component=1)
         #declare r = base_color_tone.red*detail_intensity+RRand(-color_deviation/255,color_deviation/255,rSeed);
      #end
      #if (base_color_component=2)
         #declare g = base_color_tone.green*detail_intensity+RRand(-color_deviation/255,color_deviation/255,rSeed);
      #end
      #if (base_color_component=3)
         #declare b = base_color_tone.blue*detail_intensity+RRand(-color_deviation/255,color_deviation/255,rSeed);
      #end
   #end
   color rgb <r, g, b>
#end // surface_color_random macro

// Get Pattern from Range
// ---------------------------------------------------------------------------
#macro GetPattern_OLD(pattern_method)
   #switch(pattern_method)
      #case (1)  gradient y scale 3   #break //doesn't produce nice microstructures
      #case (2)  gradient x scale 3   #break //doesn't produce nice microstructures
      #case (3)  gradient z scale 2   #break //doesn't produce nice microstructures
      #case (4)  cells      scale 1   #break //doesn't produce nice microstructures
      #case (5)  agate      scale 10  #break

      #case (6)  bozo       scale 1   #break
      #case (7)  bumps      scale 1   #break
      #case (8)  crackle    scale 5   #break
      #case (9)  dents      scale 1   #break
      #case (10) ripples    scale 2   #break
      #case (11) spotted    scale 1   #break
      #case (12) waves      scale 0.5 #break
      #case (13) wrinkles   scale 1   #break
      #case (14) granite    scale 10  #break
      #case (15) quilted    scale 3   #break

      #case (16) leopard    scale 0.3 #break //doesn't produce nice microstructures
      #case (17) marble     scale 1 #break
      #case (18) spiral1 5  scale 30  #break
      #case (19) onion      scale 2   #break //doesn't produce nice microstructures
      #case (20) radial     scale 10  #break //doesn't produce nice microstructures
   #end //switch
#end //macro

//EOF
