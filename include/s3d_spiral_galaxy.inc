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
// @file    : s3d_spiral_galaxy.inc
// @brief   : a spiral galaxy for starfields
// @version : 2019-05-25
// @created : 2008-07-01
// @author  : pyramid
// @internet: https://openteq.wordpress.com/portfolio/space3d/
// @scale   : 1 POV unit = 1 km
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
//TITLE: Space Is Minimalist
//NAME: Tekno Frannansa
//COUNTRY: USA
//EMAIL: tek@evilsuperbrain.com
//WEBPAGE: http://evilsuperbrain.com
//TOPIC: Minimalism
//COPYRIGHT: I SUBMIT TO THE STANDARD RAYTRACING COMPETITION COPYRIGHT.
//JPGFILE: evrythng.jpg
//ZIPFILE: evrythng.zip
// ---------------------------------------------------------------------------------------
//RENDERER USED: 
//        POV-Ray 3.6.1
//        
//TOOLS USED: 
//        povray editor
//        Irfanview (to resize & convert to jpg)
//
//RENDER TIME: 
//        7h 55m 48s at 7800x5200
//
//HARDWARE USED: 
//        Athlon XP 3200+ 2.22GHz 1GB RAM
//
//
//IMAGE DESCRIPTION: 
//
//Space is minimalist. It is mostly nothing yet it's defined and given meaning by
//the tiniest of specks.
//
//The arrangement of this image is inspired by deep-field images from Hubble, with
//a little artistic license :)
//
//Note - IRTC file size rules mean I've had to compress this image quite severely,
//so there's a few subtle artefacts. A better quality version is available here:
//http://evilsuperbrain.com/gallery/finished/index.php?image=evrythng
//
//
//DESCRIPTION OF HOW THIS IMAGE WAS CREATED: 
//
//I spent a long time working on the emmissive & absorbing media that describes
//the galaxy, based on photo reference of milky-way-like galaxies (mostly NGC
//1232). Then I put that into a macro with a lot of parameters to vary things
//like colour, pattern, noise, etc.
//
//The main galaxy was positioned and has parameters chosen by hand, in fact the
//macro was developed for this one galaxy so all the others in the scene are
//variations from this source. A second galaxy was placed by hand in the
//foreground, and then 8000 others were randomly generated throughout the scene.
//All 8000 are visible in the final image, though some are just specks!
//
//In the extreme distance I've used a sky_sphere with some bright dots on it to
//fake even more distant galaxies. I created this by rendering a small section of
//the scene with full detail galaxies at that distance, so when I created the
//fake ones I could make sure they look the same. In the full resolution
//7800x5200 version you can just about see that it's a trick, but in this version
//you really can't tell.
//
//The hi-res version was rendered for a poster at zazzle.com, then I sampled the
//image down in Irfanview using it's highest quality resampling.
//
//I've provided full source so you can play around with it for yourself. Enjoy!
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
// Macros from original scene
// ---------------------------------------------------------------------------------------
 
#default { pigment { rgb 1 transmit 1 } finish { ambient 1 diffuse 0 } }

#macro ColPhase( col, Phase )	//0 = 1 = col
	#local Phase = Phase*2*pi;
	#local cut = cos(2*pi/3);
	#local c0 = max(0,cos(Phase) - cut)/(1-cut);
	#local c1 = max(0,cos(Phase-2*pi/3) - cut)/(1-cut);
	#local c2 = max(0,cos(Phase-4*pi/3) - cut)/(1-cut);
	<vdot(col,<c0,c1,c2>),vdot(col,<c2,c0,c1>),vdot(col,<c1,c2,c0>)>
#end

//spiral galaxy
// Uage: object { SpiralGalaxy(6, 0, 2, .5, .5, 0) rotate <40,-30,0> translate <2,0,5*2/.7> }
// Optimum parameters arms:0-10; Rand:vector 0-100; spiralness:0-2; glowiness:0-1; turb:0-0.7; colShift:0-1;
#macro SpiralGalaxy(arms, Rand, spiralness, glowiness, turb, colShift)
	sphere { 0, 1 hollow on
		//#local cheap = off;  //damn useful to see if it's a bug in the pattern or in the media
      //#if (cheap)
   	//	scale <1,1,.001> //a disc
   	//	pigment {
      //#else
   		scale <1.2,1.2,.3>
   		texture { pigment { rgbt 1 } }
   		interior { media { emission 3.5 //5
   		   absorption 0 //absorprtion will be just a disc through the middle and beyond the edges.
   			density {
      //#end
   				//brightness (apart from outer edge)
   				pigment_pattern {
   					function { min(1,max(0,((1-z*z/(.01+.03*1/((x*x+y*y)*50+1))))*4)) } //fried egg shape
   					scale 13 warp { turbulence .5 lambda 3 } scale 1/13
   					pigment_map {
   						[0 rgb 0 transmit 1 ]
   						[1 //brighter & denser center
   							pigment_pattern { spherical cubic_wave } poly_wave 5.5-glowiness*5
   							pigment_map {
   								[0 average
   									pigment_map {
   										//spiral arms
   										[spiralness pigment_pattern { pigment_pattern { spiral1 arms scale 1.8/arms } cubic_wave } poly_wave 5 colour_map { [0 rgb .1 transmit 1 ][1 rgb 1 transmit 1 ] }
   											translate Rand
   											scale 7
   											warp { turbulence turb lambda 3 }
   											scale 1/7
   											translate -Rand
   										]
   										//cloudiness
   										[.7 granite scale .1 translate Rand]
   										//stars
   										[100 pigment_pattern { crackle form <1,0,0> pigment_map { [.1 spotted scale .1 turbulence 1 poly_wave 1][1 rgb 0 transmit 1 ] } cubic_wave } poly_wave 8 scale .05 translate Rand]
   									}
   								]
   								[1 rgb .008 transmit 1 ]
   							}
   						]
   					}
   				}
					//colour (with black at edge) 
      //#if (cheap)
		//			pigment_map {
      //#else
					density_map {
      //#end
						[0 rgb 0 transmit 1 ]
						[1
							average
      //#if (cheap)
		//					pigment_map {
      //#else
							density_map {
      //#end
								[1 pigment_pattern { spherical cubic_wave } poly_wave 4-colShift*2.5  colour_map { [0 rgb 0 transmit 1 ][1 rgb 50*x*(6-colShift*0) transmit 1 ] }]
								[1 pigment_pattern { spherical cubic_wave } poly_wave 1.3  colour_map { [0 rgb 0 transmit 1 ][1 rgb 50*y*3.5 transmit 1 ] }]
								[1 pigment_pattern { spherical cubic_wave } poly_wave .2+colShift*.8 colour_map { [0 rgb 0 transmit 1 ][1 rgb 50*z*2.4 transmit 1 ] }]
								[4-4*colShift pigment_pattern { spherical cubic_wave } poly_wave .5 colour_map { [0 rgb 0 transmit 1 ][1 rgb 50*1 transmit 1 ] }]
							}
						]
					}
				}
      //#if (!cheap)
			}
			media { absorption 0 //5 
				density {
					pigment_pattern { planar scale .12 poly_wave 2 rotate x*90 }
					density_map {
						[0 rgb 0 transmit 1 ]
						[1 spherical scale 1.2 poly_wave .2]
					}
					translate Rand
					scale 13/<2,2,.6>
					warp { turbulence 2 lambda 3 }
					scale <2,2,.6>/13
					translate -Rand
				}
			}
		}
      //#end
	no_shadow no_reflection }
#end //macro

#macro vRand(s) (<rand(s),rand(s),rand(s)>*2-1) #end

// ---------------------------------------------------------------------------------------
// Original scene elements are commented
// ---------------------------------------------------------------------------------------
/* 
//build the scene around the camera, I don't usually do this but it's appropriate for this type of scene
camera { right x up y*image_height/image_width direction	z*2 location 0
	//aperture .01 focal_point <2.2,-.4,5*2/.7>*.9 blur_samples 20
}

global_settings {
	assumed_gamma 2.2	//this seriously alters the falloff on the stars
	max_trace_level 20
}

//background { rgb .2 }
	
object { SpiralGalaxy(6, 0, 2, .5, .5, 0) rotate <40,-30,0> translate <2,0,5*2/.7> }

#local rsParam = seed(10);
#local rsLoc = seed(17); //17 - damn nice but there's a bit of a line, 23 - similar problem but less up close, 7 - mid sized ones
#local loop = 0;
#while ( loop < 8000 )
	object {
		SpiralGalaxy(int(rand(rsParam)*4)+2,vRand(rsParam)*100,rand(rsParam)*2,rand(rsParam),rand(rsParam)*.7,rand(rsParam))
		#local rot = vRand(rsLoc);
		rotate -rot*<abs(rot.x),1,1>*<90,360,360>
		#local FrustPos = (vRand(rsLoc)*.5+z*.5001);
		//random position within a frustum, evenly distributed through the space, haha.
		//so basically (z*xy1) gets the shape, then scale it all by 1/sqrt(z) to adjust the probability
		#local FrustPos = FrustPos*<FrustPos.z,FrustPos.z*image_height/image_width,2>*pow(FrustPos.z,-.5);
		translate FrustPos*1000
		//rotate -x*90 translate <0,-20,50>
	}
	#local loop = loop + 1;
#end

//sit the camera ion the edge of one
object {
	SpiralGalaxy(3, 0, 2, 0, .2, .8)//(2, -10, 1, 1, .5, .7)
	//scale .7
	rotate 180*y
	rotate 60*z
	rotate <30,0,-10> translate <-1,-.6,3>
	//scale .6 //this makes it a bit less dense & smaller while keeping it in the same 2D place on screen.
}

//do this sharp, for the poster, meaning maybe put even more real ones in!
//really distant ones
sky_sphere {
	pigment {
		pigment_pattern { crackle form <1,0,0> pigment_map { [0 crackle solid sine_wave frequency 100][.16 rgb 0] } }
		cubic_wave//poly_wave 2
		pigment_map {
			[0 rgb 0]
			[1 crackle solid pigment_map { [.2 rgb (x*2+y)*2][.6 rgb 2][1 rgb (z*2+y)*2] }]
		}
	}
	scale .00135
}

union {
	text {
		ttf "tahomabd.ttf" "EVERYTHING" .001,0 //kartika
		//position 3D within the scene
		scale .1
		translate <.19,-.25,0>
	}

	disc { 0, -z, .06, .04 }
	box { -.5, .5 scale <.02, .2, .001> translate -y*(.05+.2/2) rotate 45*z }

	//scale 1024/image_width
	translate <2.1,-.4,5*2/.7>
	pigment { rgb <1,.2,.3> }
	//scale towards the camera to make sure it draws "on top" of everything
	scale .9//.01
}
*/

//EOF
