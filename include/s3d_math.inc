// ---------------------------------------------------------------------------------------
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
// Persistence of Vision Ray Tracer Scene Description Include File
// File       : s3d_camera.inc
// Description: camera definition macros
// Version    : 0.45
// Date       : 2009-08-03
// Author     : Pyramid
// Scale      : 1 POV Unit = 1km
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// MACROS
//   IRand(Min,Max,Stream)
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
// Global Settings
// ---------------------------------------------------------------------------------------
#version 3.6;

// ---------------------------------------------------------------------------------------
// Macros
// ---------------------------------------------------------------------------------------
#macro IRand(Min,Max,Stream)
   (int(rand(Stream)*(Max-Min+1)) + Min)
#end

#macro VRand(s) (<rand(s),rand(s),rand(s)>*2-1) #end

//EOF