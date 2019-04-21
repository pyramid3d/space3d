// ---------------------------------------------------------------------------
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
// Persistence of Vision Ray Tracer Scene Description File
// File       : simple_scene.pov
// Description: Space3D scene
// Version    : 0.47
// Date       : 2011-04-07
// Author     : Pyramid
// Scale      : 1 POV Unit = 1km
// ---------------------------------------------------------------------------

#include "space3d.inc"

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
