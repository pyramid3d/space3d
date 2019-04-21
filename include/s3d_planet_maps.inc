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
// File       : planet_maps.inc
// Description: Planet maps definition include file 
// Version    : 0.45
// Date       : 2009-08-03
// Author     : Pyramid
// Internet   : http://space3d.no.sapo.pt/
// Scale      : 1 POV Unit = 1km
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// User Settings
// ---------------------------------------------------------------------------

#ifndef (render_quality)
// 0=fast-low quality maps; 1=full-high quality maps
  #declare render_quality = 1;
#end

// ---------------------------------------------------------------------------
// Surface Maps
// ---------------------------------------------------------------------------

// Planet maps taken from http://visibleearth.nasa.gov (source=nasa)
// adapted with brightness+50 ;green +10; blue +50;

// Earth maps
//#declare EARTH_MAP_NORMAL = "maps/land_ocean_ice_2048_adapt.jpg";
#declare EARTH_MAP_CLOUD = "maps/land_ocean_ice_cloud_2048_adapt.jpg";
//#declare EARTH_MAP_CLOUD = "maps/land_ocean_ice_cloud_2048.jpg";
#declare EARTH_MAP_CLOUD_HIGH = "maps/land_ocean_ice_cloud_8192_adapt.tga";
// Moon maps from http://planets.shacknet.nu/
#declare MOON_MAP_LOW = "maps/moonmap1k.jpg";
#declare MOON_MAP_HIGH = "maps/moonmap4k.jpg";
#declare MOON_BUMP_MAP = "maps/moonbump4k.jpg";

// Mercury maps
// map source http://www.jht.cjb.net
#declare MERCURY_MAP_LOW = "maps/mercurymap.jpg";
// map source http://www.solarviews.com
#declare MERCURY_MAP_HIGH = "maps/mercurycyl2_artistic_adapt.jpg";

// Venus maps
// map source http://www.jht.cjb.net
#declare VENUS_MAP_LOW = "maps/venusmap.jpg";
//map source http://laps.fsl.noaa.gov/albers/sos/sos.html
#declare VENUS_MAP_HIGH = "maps/venus4_rgb_cyl_www.jpg";

// Mars maps
// map source http://www.jht.cjb.net
#declare MARS_MAP_LOW = "maps/marsmap1k.jpg";
//map source www.space-graphics.com
#declare MARS_MAP_HIGH = "maps/m46_color_8k.jpg";

// Jupiter maps
// map source http://www.jht.cjb.net
#declare JUPITER_MAP_LOW = "maps/jupitermap.jpg";
//map source http://www.mmedia.is/%7Ebjj/
#declare JUPITER_MAP_HIGH = "maps/jupiter_vgr2.jpg";

// Saturn maps
// map source http://www.jht.cjb.net
#declare SATURN_MAP_LOW = "maps/saturnmap.jpg";
//map source http://www.mmedia.is/%7Ebjj/
#declare SATURN_MAP_HIGH = "maps/saturn.jpg";

// Uranus maps
// map source http://www.jht.cjb.net
#declare URANUS_MAP_LOW = "maps/uranusmap.jpg";
#declare URANUS_MAP_HIGH = "maps/uranusmap.jpg";

// Neptune maps
// map source http://www.jht.cjb.net
#declare NEPTUNE_MAP_LOW = "maps/neptunemap.jpg";
//map source http://www.mmedia.is/%7Ebjj/
#declare NEPTUNE_MAP_HIGH = "maps/neptune.jpg";

// Pluto maps
// map source http://www.jht.cjb.net
#declare PLUTO_MAP_LOW = "maps/plutomap1k.jpg";
// map source http://www.jht.cjb.net
#declare PLUTO_MAP_HIGH = "maps/plutomap2k.jpg";

#if (render_quality = 1) // high = best
  #declare EARTH_MAP = EARTH_MAP_CLOUD_HIGH;
  #declare MOON_MAP = MOON_MAP_HIGH;
  #declare MERCURY_MAP = MERCURY_MAP_HIGH;
  #declare VENUS_MAP = VENUS_MAP_HIGH;
  #declare MARS_MAP = MARS_MAP_HIGH;
  #declare JUPITER_MAP = JUPITER_MAP_HIGH;
  #declare SATURN_MAP = SATURN_MAP_HIGH;
  #declare URANUS_MAP = URANUS_MAP_HIGH;
  #declare NEPTUNE_MAP = NEPTUNE_MAP_HIGH;
  #declare PLUTO_MAP = PLUTO_MAP_HIGH;
#else // low = test
  #declare EARTH_MAP_TYPE = USER_MAP_TYPE_JPEG;
  #declare EARTH_MAP = EARTH_MAP_CLOUD;
  #declare MOON_MAP = MOON_MAP_LOW;
  #declare MERCURY_MAP = MERCURY_MAP_LOW;
  #declare VENUS_MAP = VENUS_MAP_LOW;
  #declare MARS_MAP = MARS_MAP_LOW;
  #declare JUPITER_MAP = JUPITER_MAP_LOW;
  #declare SATURN_MAP = SATURN_MAP_LOW;
  #declare URANUS_MAP = URANUS_MAP_LOW;
  #declare NEPTUNE_MAP = NEPTUNE_MAP_LOW;
  #declare PLUTO_MAP = PLUTO_MAP_LOW;
#end
