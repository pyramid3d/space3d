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
// @file    : s3d_scene.inc
// @brief   : camera and scene definition macros
// @version : 2019-05-08
// @created : 2011-11-21
// @author  : pyramid
// @internet: https://openteq.wordpress.com/portfolio/space3d/
// @scale   : 1 POV unit = 1 km
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
// MACROS
//    Sun(vSunLocation, fIntensity)
//      - creates a ligh source
//    Camera(vCameraPosition, vLookAtPoint, fCameraViewAngle)
//      - a freely defined camera
//    Camera1(fPlanetRadius)
//      - predefined camera positions for objects centered at the <0,0,0> origin                                
//    CameraTexture()
//      - a spherical texture unwrap camera for planet surfaces and cloud maps
//    TitleText(sTitle, Ftitleheight, vTitleRotation, rgbColor)
//      - writes a text on the image, with vTitleRotation being a fine adjustment 
//    WaterMark(sTitle, fTitleHeight, rgbColor)
//      - writes a watermark in the lower left corner of the image 
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
// Global Settings
// ---------------------------------------------------------------------------------------

global_settings {
   assumed_gamma 1.5 //1.0, 1.5-linux, 2.2-windows
   max_trace_level 256 //10
}

#ifndef(create_logfile)
  #declare create_logfile = false;
#end
#ifndef(show_debug)
  #declare show_debug = false;
#end
#ifndef(render_quality)
  #declare render_quality = 1;
#end

// ---------------------------------------------------------------------------------------
// Include Files
// ---------------------------------------------------------------------------------------
#include "rand.inc" // random number generation macros
#include "math.inc" // math function macros

// ---------------------------------------------------------------------------------------
// Macros
// ---------------------------------------------------------------------------------------


// usage examples:
//#include "space3d.inc"
//WaterMark("2019 pedrabella Space3D", 3.0, color rgb <0.3, 0.3, 0.3>)
// optional
//#declare vCamPos = <0, 0, 0>;
//#declare vCamRot = <0, 0, 0>;
//#declare fCamAng = 50;
#macro WaterMark(sTitle, fTitleHeight, rgbColor)
  #ifndef (vCamPos)
      #declare vCamPos = <0, 0, -10>;
  #end
  #ifndef (vCamRot)
      #declare vCamRot = <0, 0, 0>;
  #end
  #ifndef (fCamAng)
      #declare fCamAng = 50;
  #end
  //#ifndef (TitleFont)
    //#declare TitleFont = "arial.ttf"; // "megan___.ttf"; "AndromedaTV.ttf"; "arial.ttf";
    //#declare TitleFont = "harabara.ttf";
    //#declare TitleFont = "zektonfree.ttf";
    #declare TitleFont = "font/zerothrees.ttf";
  //#end

  //#declare vCamRot = <0,0,0>;
  //#declare TitleFont = "arial.ttf"; // "megan___.ttf"; "AndromedaTV.ttf"; "arial.ttf";
  #declare TitleTexture = texture { pigment { color rgbColor transmit 0.7 } finish { ambient 0.8 diffuse 0.5 } }
  #declare TitleWidth = Text_Width(TitleFont, sTitle, fTitleHeight,0);
  #declare textScale = radians(0.5*fCamAng)/radians(25)*0.1*fTitleHeight/24;
  #declare moveH = TitleWidth * 0.03 * textScale;
  #declare moveV = fTitleHeight * 0.001 * radians(fCamAng/2)/radians(50/2);
  #declare cornerH = radians(fCamAng/2); //0.450;
  #declare cornerV = radians(fCamAng/2); //0.440;
  text { ttf TitleFont, sTitle, 0.02, 0 // depth, spacing
    scale textScale texture { TitleTexture }
    translate vCamPos + <-cornerH-moveH*1, -(cornerV*image_height/image_width)-moveV*1, 1>
    translate -vCamPos rotate vCamRot translate vCamPos no_shadow
  }
#end

#macro TitleText(sTitle, fTitleHeight, rgbColor)
  #ifndef (vCamPos)
      #declare vCamPos = <0, 0, -10>;
  #end
  #ifndef (vCamRot)
      #declare vCamRot = <0, 0, 0>;
  #end
  #ifndef (fCamAng)
      #declare fCamAng = 50;
  #end
  //#declare vTitleRotation = <0,0,0>;
  #declare TitleFont = "arial.ttf"; // "megan___.ttf"; "AndromedaTV.ttf"; "arial.ttf";
  #declare TitleTexture = texture { pigment { color rgbColor } finish { ambient 0.8 diffuse 0.5 } }
  #declare TitleWidth = Text_Width(TitleFont, sTitle, fTitleHeight,0);
  #declare textScale = radians(0.5*fCamAng)/radians(25)*0.1*fTitleHeight/24;
  #declare moveH = TitleWidth * 0.0001 * textScale;
  #declare moveV = fTitleHeight * 0.003 * radians(fCamAng/2)/radians(50/2);
  #declare cornerH = radians(fCamAng/2); //0.450;
  #declare cornerV = radians(fCamAng/2); //0.440;
  text { ttf TitleFont, sTitle, 0.02, 0 // depth, spacing
    scale textScale texture { TitleTexture }
    translate vCamPos + <-cornerH+moveH, (cornerV*image_height/image_width)-moveV, 1>
    translate -vCamPos rotate vCamRot translate vCamPos no_shadow
  }
#end

//-----------------------------------
// Legacy Text Macros
//-----------------------------------

#macro TitleTextAdjust(Title, Ftitleheight, CameraPosition, CameraAngle, TitleRotation, rgbColor)
   #declare TitleFont = "arial.ttf"; // "megan___.ttf"; "AndromedaTV.ttf"; "arial.ttf";
   #declare TitleTexture = texture { pigment { color rgbColor } finish { ambient 0.8 diffuse 0.5 } }
   #declare TitleWidth = Text_Width(TitleFont,Title,Ftitleheight,0);
   #declare textScale = radians(CameraAngle/2)/radians(50/2)*0.1*Ftitleheight/24;
   #declare moveH = TitleWidth * 0.0001 * textScale;
   #declare moveV = Ftitleheight * 0.003 * radians(CameraAngle/2)/radians(50/2);
   #declare cornerH = radians(CameraAngle/2); //0.450;
   #declare cornerV = radians(CameraAngle/2); //0.440;
   text { ttf TitleFont, Title, 0.02, 0 // depth, spacing
      scale textScale texture { TitleTexture }
      translate CameraPosition + <-cornerH+moveH, (cornerV*image_height/image_width)-moveV, 1>
      translate -CameraPosition rotate TitleRotation translate CameraPosition no_shadow
   }
#end

#macro DrawTitle(sTitle, fTitleHeight, vTitleRotation, rgbColor)
   #declare TitleFont = "arial.ttf"; // "megan___.ttf"; "AndromedaTV.ttf"; "arial.ttf";
   #declare TitleTexture = texture { pigment { color rgbColor } finish { ambient 0.8 diffuse 0.5 } }
   #declare TitleWidth = Text_Width(TitleFont, sTitle, fTitleHeight,0);
   #declare textScale = radians(fCamAng/2)/radians(50/2)*0.1*fTitleHeight/24;
   #declare moveH = TitleWidth * 0.0001 * textScale;
   #declare moveV = fTitleHeight * 0.003 * radians(fCamAng/2)/radians(50/2);
   #declare cornerH = radians(fCamAng/2); //0.450;
   #declare cornerV = radians(fCamAng/2); //0.440;
   text { ttf TitleFont, sTitle, 0.02, 0 // depth, spacing
      scale textScale texture { TitleTexture }
      translate vCamPos + <-cornerH+moveH, (cornerV*image_height/image_width)-moveV, 1>
      translate -vCamPos rotate vTitleRotation translate vCamPos no_shadow
   }
#end


// ---------------------------------------------------------------------------------------
// Lights
// ---------------------------------------------------------------------------------------

#macro Sun(vSunLocation, fIntensity)
  #declare vSunPosition = vSunLocation;
  #declare sun = light_source { vSunLocation color rgb fIntensity } 
  light_source { sun }
#end

// ---------------------------------------------------------------------------------------
// Camera
// ---------------------------------------------------------------------------------------

// define diffuse finish for scenes
#declare surface_finish = finish { ambient 0.0 diffuse 1.0 }
//#declare surface_finish = finish { ambient 0.0 diffuse 1.0 specular 0.0 phong 0.0 }

#macro CameraRotation(vCameraPosition, vLookAt, fCamAngle, vRotation) // free camera
  #declare vCamPos = vCameraPosition;
  #if (vCamPos.x=vLookAt.x & vCamPos.y=vLookAt.y & vCamPos.z=vLookAt.z)
    #declare vLookAt = vCamPos + <0,0,1>;
  #end
  #declare vCameraDirection = vLookAt;
  #declare fCamAng = fCamAngle;
  // some calculations required for DrawTitle
  #declare fCameraRotX = -degrees(asin((vLookAt.y-vCamPos.y)/(vLookAt.z-vCamPos.z))); // asin(vec_y/-vec_z)
  #declare fCameraRotY = degrees(asin((vLookAt.x-vCamPos.x)/(vLookAt.z-vCamPos.z)));    // asin(vec_x/-vec_z)
  camera { location vCamPos right <image_width,0,0> up <0,image_height,0> look_at vLookAt angle fCamAngle rotate vRotation }    
#end

// simple camera, just your position, looking at origin
#macro CameraPos(vCameraPosition)
  CameraRotation(vCameraPosition, <0,0,0>, 50, <0,0,0>)
#end

#macro Camera(vCameraPosition, vLookAt, fCamAngle)
  CameraRotation(vCameraPosition, vLookAt, fCamAngle, <0,0,0>)
#end

#macro Camera1(fPlanetRadius) // normal full center camera
  #if (fPlanetRadius=0) #declare fPlanetRadius=1; #end // position & look_at must be different
  #declare vCamPos = <0, 0, -fPlanetRadius*4>;
  #declare vCamDir = <0, 0, 0>;
  #declare fCamAng = 50;
  camera { location vCamPos right <image_width,0,0> up <0,image_height,0> look_at vCamDir angle fCamAng }    
#end

#macro Camera2(fPlanetRadius) // quarter camera
  #declare vCamPos = <0, 0, -fPlanetRadius*4>;
  #declare vCamDir = <fPlanetRadius*0.6, fPlanetRadius*0.6, 0>;
  #declare fCamAng = 20;
  camera { location vCamPos right <image_width,0,0> up <0,image_height,0> look_at vCamDir angle fCamAng }    
#end

#macro Camera3(fPlanetRadius) // closeup camera
  #declare vCamPos = <0, 0, -fPlanetRadius*4>;
  #declare vCamDir = <fPlanetRadius*0.8, fPlanetRadius*0.5, 0>;
  #declare fCamAng = 10;
  camera { location vCamPos right <image_width,0,0> up <0,image_height,0> look_at vCamDir angle fCamAng }    
#end

#macro Camera4(fPlanetRadius) // up camera
  #declare vCamPos = <0, 0, -fPlanetRadius*4>;
  #declare vCamDir = <fPlanetRadius*0.1, fPlanetRadius*0.8, 0>;
  #declare fCamAng = 10;
  camera { location vCamPos right <image_width,0,0> up <0,image_height,0> look_at vCamDir angle fCamAng }    
#end

#macro Camera5(fPlanetRadius) // right closeup camera
  #declare vCamPos = <fPlanetRadius, 0, -fPlanetRadius*4>;
  #declare vCamDir = <fPlanetRadius, 0, 0>;
  #declare fCamAng = 5;
  camera { location vCamPos right <image_width,0,0> up <0,image_height,0> look_at vCamDir angle fCamAng }    
#end

#macro Camera6() // unwrap camera
  camera {
    spherical
    angle 360
  }    
	// define only ambient finish for textures
	#declare surface_finish = finish { ambient 1.0 diffuse 0.0 specular 0.0 phong 0.0 }
#end

#macro Camera7(fPlanetRadius) // movie camera closeup
  #declare vCamPos = <fPlanetRadius*0.3, -fPlanetRadius*0.9, -fPlanetRadius*2>;
  #declare vCamDir = <fPlanetRadius*0.3, -fPlanetRadius*0.9, 0>;
  #declare fCamAng = 35;
  camera { location vCamPos right <image_width,0,0> up <0,image_height,0> look_at vCamDir angle fCamAng }    
#end

#macro Camera8(fPlanetRadius) // full planet full screen 4:3 ratio
  #declare vCamPos = <0, 0, -fPlanetRadius*3.2>;
  #declare vCamDir = <0, 0, 0>;
  #declare fCamAng = 50;
  camera { location vCamPos right <image_width,0,0> up <0,image_height,0> look_at vCamDir angle fCamAng }    
#end

#macro Camera9(fPlanetRadius) // full planet full screen 1:1 ratio
  #declare vCamPos = <0, 0, -fPlanetRadius*2.38>;
  #declare vCamDir = <0, 0, 0>;
  #declare fCamAng = 50;
  camera { location vCamPos right <image_width,0,0> up <0,image_height,0> look_at vCamDir angle fCamAng }    
#end

#macro CameraTexture() // texture unwrap camera
  camera { spherical angle 360 }    
	// define only ambient finish for textures
  #declare vCamPos = <0, 0, -2>;
  #declare fCamAng = 360;
	#declare surface_finish = finish { ambient 1.0 diffuse 0.0 specular 0.0 phong 0.0 }
#end

/*
#ifdef (CAMERA)
  #if (CAMERA = 1) // normal full camera
    #declare vCamPos = <0, 0, -planet_radius*4>;
    #declare vCamDir = <0, 0, 0>;
    #declare fCamAng = 50;
    camera { location vCamPos right <image_width,0,0> up <0,image_height,0> look_at vCamDir angle fCamAng }    
  #end

  #if (CAMERA = 2) // quarter camera
    #declare cam_pos = <0, 0, -planet_radius*4>;
    #declare cam_dir = <planet_radius*0.6, planet_radius*0.6, 0>;
    #declare cam_ang = 20;
    camera { location cam_pos right <image_width,0,0> up <0,image_height,0> look_at cam_dir angle 20 }    
  #end
  
  #if (CAMERA = 3) // closeup camera
    #declare cam_pos = <0, 0, -planet_radius*4>;
    #declare cam_dir = <planet_radius*0.8, planet_radius*0.5, 0>;
    #declare cam_ang = 10;
    camera { location cam_pos right <image_width,0,0> up <0,image_height,0> look_at cam_dir angle 10 }    
  #end
  
  #if (CAMERA = 4) // up camera
    #declare cam_pos = <0, 0, -planet_radius*4>;
    #declare cam_dir = <planet_radius*0.1, planet_radius*0.8, 0>;
    #declare cam_ang = 10;
    camera { location cam_pos right <image_width,0,0> up <0,image_height,0> look_at cam_dir angle 10 }    
  #end
  
  #if (CAMERA = 5) // right closeup camera
    #declare cam_pos = <planet_radius, 0, -planet_radius*4>;
    #declare cam_dir = <planet_radius, 0, 0>;
    #declare cam_ang = 5;
    camera { location cam_pos right <image_width,0,0> up <0,image_height,0> look_at cam_dir angle cam_ang }    
  #end
  
  #if (CAMERA = 6)
  // unwrap camera
   camera {
  	 spherical
     angle 360
   }    
  #end
  
  #if (CAMERA = 6)
  	// define only ambient finish
  	#declare surface_finish = finish { ambient 1.0 diffuse 0.0 specular 0.0 phong 0.0 }
  #else
  	// define diffuse finish
  	#declare surface_finish = finish { ambient 0.0 diffuse 1.0 specular 0.0 phong 0.0 }
  #end
  
  #if (CAMERA = 7) // movie camera closeup
    #declare cam_pos = <planet_radius*0.3, -planet_radius*0.9, -planet_radius*2>;
    #declare cam_dir = <planet_radius*0.3, -planet_radius*0.9, 0>;
    #declare cam_ang = 35;
    camera { location cam_pos right <image_width,0,0> up <0,image_height,0> look_at cam_dir angle cam_ang }    
  #end
  
  #if (CAMERA = 8) // full planet full screen 4:3 ratio
    #declare cam_pos = <0,0,-planet_radius*3.2>;
    #declare cam_dir = <0, 0, 0>;
    #declare cam_ang = 50;
    camera { location cam_pos right <image_width,0,0> up <0,image_height,0> look_at cam_dir angle cam_ang }    
  #end
  
  #if (CAMERA = 9) // full planet full screen 1:1 ratio
    camera {
       location <0,0,-planet_radius*2.38>     // position & direction of view
       right <image_width,0,0> up <0,image_height,0>
       angle 50
    }
  #end
  
  #else
  	// define diffuse finish
  	#declare surface_finish = finish { ambient 0.0 diffuse 1.0 }
#end //def CAMERA
*/

//EOF
