```
#====================================
# @file: trunk/CHANGES.md
# @version : 0.55.02
# @version : 2019-05-25
# @created : 2009-08-03
# @author  : pyramid
# @brief   : Space3D for POV-Ray version history
# @internet: https://github.com/pyramid3d/space3d
# @internet: https://openteq.wordpress.com/portfolio/space3d/
#====================================
# ex file: space3d_version_history.txt
# description: space3d development and version history
# ex internet: http://space3d.no.sapo.pt/
#====================================
```


-----------------------------------------------------------
# Change History
-----------------------------------------------------------

2019-05-25 | v0.55.02 |
- s3d_starfield.ini:
  simple adjustment of intensity when size > 1
  set optimum nebula distance at 4e4 to avoid artifacts
  with stars (at default distance 2e4)

2019-05-24 | v0.55.01 |
- s3d_starfield.ini:
  adjusted box emission to accept param between 0 (random)
  and 10 (max).
  changed box depth to fsize parameter (2e4). box must be
  moved to the background to avoid star artifacts.
  changed default nebula position to origin <0,0,0,>. use
  object { nebula translate <..> } to set depth.
  with this changes the new mCloudNebula08 will produce
  different results from the previous one.

2019-05-20 | v0.55.00 |
- s3d_starfield.ini: changed sphere to box in mCloudNebula08 to
  remove overlap artifacts with stars
  /* Legacy implementation has artifacts with the star tirangles
   * which, when present, prevent the nebula density to be drawn
   * inside the triangles, and therefore makes those visible
   * as artifacts
   */

2019-05-18 | v0.54 |
- s3d_math.inc: added FxRnd and Fx macros for random and id function selection
- moved command line scripts to "sh" directory

2019-05-08 | v0.53 |
- s3d_scene.ini: improved WaterMark macro to customize font
- dir: added fonts directory

2019-04-20 | v0.52 |
- github: first time published sources on github

-----------------------------------------------------------

=======
# @file: trunk/CHANGES.md
# @version : 0.51
# @version : 2019-04-20
# @created : 2009-08-03
# @author  : pyramid
# @brief   : Space3D for POV-Ray version history
# @internet: https://openteq.wordpress.com/portfolio/space3d/
# ex file: space3d_version_history.txt
# description: space3d development and version history
# ex internet: http://space3d.no.sapo.pt/

```


---------------------------------------------------------------------------------------
 To Do List
---------------------------------------------------------------------------------------
 01 - better nebula backgrounds
 02 - documentation: objects and uses
 03 - ateroid texture map is not satisfactory
 - tiled web backround as per the cicada principle:
    http://designfestival.com/the-cicada-principle-and-why-it-matters-to-web-designers/


// ---------------------------------------------------------------------------------------
// Change History
// ---------------------------------------------------------------------------------------
>>>>>>> added last space3d complete version
// 2016-09-19 | v0.51 | added: WaterMark macro to s3d_scene.ini 
// 2012-07-02 | v0.50 | bugfix in s3d_planet.inc Unexpected '.' in DensityCurve 
// 2012-04-19 | v0.49 | added: added Star macro with color parameter 
// 2011-11-21 | v0.48 | bugfix: local vs. global variables in Camera() and CameraRotate()
//                      scences: included SHOW_LABELS global flag for test scenes
//                      scenees: improved lightning in test scenes
// 2011-04-11 | v0.47 | bugfix: made planet rings hollow objects
//                      converted UranusRings() to macro
//                      simplified TitleText(), included TitleTextAdjust()
//                      added simple and quick Starfield() macro
//                      texturing bugfixes (non-hollow planets, declared surface finishes)
//                      error handling for free camera if position and lookat point are
//                      equal
//                      StarNebula and Cloud Nebula pigments now take arguments
//                      new QuickNebula() macro included
//                      added CameraRotation() macro
//                      fixed declaration of standard variables for standalone pov scenes
//                      now some nebula accept on color (array[1]{cColor})
//                      adjust starcluster star size according to image width
// 2011-04-04 | v0.46 | bugfix: removed obsolete variable from StarCluster
//                      fixed space3d_gallery renders
//                      replaced CAMERA = x statements to CameraX macros
//                      converted asteroid objects to macros
//                      converted cloud objects to macros
//                      consolidated old clouds to new objects
//                      changed Sun(vSunLocation, fIntensity) to take intensity parameter
//                      corrected atmosphere transparency issue
//                      position & look_at validity check for Camera1
//                      corrected pattern bug in cloud nebula 2
//                      limited max background nebula size to avoid blank renders
//                      swapped type 2-background and type 3-ring nebula in NebulaSelect
//                      included s3d_test for macro andobject testing
//                      moved all TerranPlanetN objects to s3d_planet_terran
//                      adapted all planet macros to use generic color randomizers
//                      added QuickPlanet macro
//                      fixed trantor planet to have the same shape for cities and lights
//                      removed planet_legacy.inc from distribution
//                      included generic space3d.inc that loads all other includes
//                      added preset 16:9 screen ratio formats
// 2009-12-18 | v0.45 | planet bugfixes
//                      new ColorHSL(Hue, Saturation, Lightness) macro
// 2009-08-03 | v0.44 | joined asteroid, planet, starfield includes into one package
//                      converted objects to macros
//                      separated light & camera, and object macros into separate
//                      inc files
<<<<<<< HEAD
-----------------------------------------------------------

-----------------------------------------------------------
# To Do List
-----------------------------------------------------------
 01 - better nebula backgrounds
 02 - documentation: objects and uses
 03 - ateroid texture map is not satisfactory
 - tiled web backround as per the cicada principle:
    http://designfestival.com/the-cicada-principle-and-why-it-matters-to-web-designers/
=======
// ---------------------------------------------------------------------------------------

>>>>>>> added last space3d complete version
