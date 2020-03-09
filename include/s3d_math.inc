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
// @file    : s3d_math.inc
// @brief   : mathematical functions
// @version : 2019-05-17
// @created : 2009-08-03
// @author  : pyramid
// @internet: https://openteq.wordpress.com/portfolio/space3d/
// @scale   : 1 POV unit = 1 km
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
// MACROS
//   IRand(Min,Max,Stream) // random integer
//   VRand(stream)  // random vector
//   FxRnd(a, rng1) // random function
//   FxRnd(a, fx)   // selected function
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

#macro FxRnd(a, rng1)
    //#local r1 = a/a;
    #local fx = IRand(1,2,rng1);
    #if(fx=1) #local r1 = sin(a); #end
    #if(fx=2) #local r1 = cos(a); #end
    #if(fx=3) #local r1 = tan(a); #end
    //#if(fx=4) #local r1 = asin(a); #end //domin error
    //#if(fx=5) #local r1 = acos(a); #end
    #if(fx=4) #local r1 = atan(a); #end
    #if(fx=5) #local r1 = sinh(a); #end
    #if(fx=6) #local r1 = cosh(a); #end
    #if(fx=7) #local r1 = tanh(a); #end
    //#if(fx=10) #local r1 = asinh(a); #end
    //#if(fx=11) #local r1 = acosh(a); #end
    #if(fx=8) #local r1 = atanh(a); #end
    #if(fx=9) #local r1 = exp(a); #end
    //#if(fx=9) #local r1 = log(abs(a)); #end
    //#if(fx=15) #local r1 = ln(abs(a)); #end
    #if(fx=10) #local r1 = a*a; #end // power^2
    #if(fx=11) #local r1 = sqrt(abs(a)); #end
    #if(fx=12) #local r1 = abs(a); #end
    #if(fx=13) #local r1 = ceil(a); #end
    #if(fx=14) #local r1 = floor(a); #end
    r1
#end

#macro Fx(a, fx)
    #if(fx=1) #local r1 = sin(a); #end
    #if(fx=2) #local r1 = cos(a); #end
    #if(fx=3) #local r1 = tan(a); #end
    #if(fx=4) #local r1 = atan(a); #end
    #if(fx=5) #local r1 = sinh(a); #end
    #if(fx=6) #local r1 = cosh(a); #end
    #if(fx=7) #local r1 = tanh(a); #end
    #if(fx=8) #local r1 = atanh(a); #end
    #if(fx=9) #local r1 = exp(a); #end
    #if(fx=10) #local r1 = a*a; #end // power^2
    #if(fx=11) #local r1 = sqrt(abs(a)); #end
    #if(fx=12) #local r1 = abs(a); #end
    #if(fx=13) #local r1 = ceil(a); #end
    #if(fx=14) #local r1 = floor(a); #end
    r1
#end

//EOF
