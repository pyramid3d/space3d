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
// File       : space3d.inc
// Description: Main Space3d include
// Version    : 0.47
// Date       : 2011-04-06
// Author     : Pyramid
// Scale      : 1 POV Unit = 1km
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
// Include Files
// ---------------------------------------------------------------------------------------
#include "rand.inc" // random number generation macros
#include "math.inc" // math function macros
#include "include/s3d_math.inc"
#include "include/s3d_color.inc" //random color macros
#include "include/s3d_scene.inc" //camera and sun light
#include "include/s3d_star.inc"
#include "include/s3d_planet.inc" //planets and atmospheres
#include "include/s3d_starfield.inc" //background stars and nebulas
#include "include/s3d_spiral_galaxy.inc"
#include "include/s3d_planet_maps.inc" // predefined solar planet maps
#include "include/s3d_asteroid.inc" // asteroids and crater textures
#include "include/s3d_planet_clouds.inc" // planet weather
#include "include/s3d_virtual_rings.inc"
#include "include/s3d_saturn_rings.inc"
#include "include/s3d_uranus_rings.inc"

//EOF