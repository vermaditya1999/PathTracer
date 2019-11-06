#include <Scene.h>
#include <camera/SimpleCamera.h>
#include <renderer/SimpleRenderer.h>
#include <geometry/Sphere.h>
#include <geometry/Rectangle.h>
#include <material/Diffused.h>
#include <material/Dielectric.h>
#include <renderer/RealisticRenderer.h>
#include "Options.h"

int main(int argc , char *argv[])
{
//    Options options(argc , argv);
//    options.parse();

    Camera *camera = new SimpleCamera(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0),
                                      30, 600, 800);
    Scene scene(camera, Color(0));

    // Rectangle *leftWall = new Rectangle(new Diffused(Color(0.75, 0.25, 0.25), Color(), 0.7, 0.2),
    //                                     vec3(-475, -485, 10),
    //                                     vec3(-475, 485, 10),
    //                                     vec3(-475, 485, -3010),
    //                                     vec3(-475, -485, -3010));
    // scene.addObject(leftWall);

    // Rectangle *rightWall = new Rectangle(new Diffused(Color(0.25, 0.25, 0.75), Color(), 0.7, 0.2),
    //                                      vec3(475, -485, -3010),
    //                                      vec3(475, 485, -3010),
    //                                      vec3(475, 485, 10),
    //                                      vec3(475, -485, 10));
    // scene.addObject(rightWall);

    // Rectangle *ceiling = new Rectangle(new Diffused(Color(0.75, 0.75, 0.75), Color(), 0.7, 0.2),
    //                                    vec3(485, 400, 10),
    //                                    vec3(485, 400, -3010),
    //                                    vec3(-485, 400, -3010),
    //                                    vec3(-485, 400, 10));
    // scene.addObject(ceiling);

    // Rectangle *floor = new Rectangle(new Diffused(Color(0.75, 0.75, 0.75), Color(), 0.7, 0.2),
    //                                  vec3(-485, -400, 10),
    //                                  vec3(-485, -400, -3010),
    //                                  vec3(485, -400, -3010),
    //                                  vec3(485, -400, 10));
    // scene.addObject(floor);

    // Rectangle *frontWall = new Rectangle(new Diffused(Color(0.75, 0.75, 0.75), Color(), 0.7, 0.2),
    //                                      vec3(-485, 485, -3000),
    //                                      vec3(485, 485, -3000),
    //                                      vec3(485, -485, -3000),
    //                                      vec3(-485, -485, -3000));
    // scene.addObject(frontWall);

    // Rectangle *backWall = new Rectangle(new Diffused(Color(0.0, 0.0, 0.0), Color(), 0.7, 0.2),
    //                                     vec3(-485, 485, 0),
    //                                     vec3(-485, -485, 0),
    //                                     vec3(485, -485, 0),
    //                                     vec3(485, 485, 0));
    // scene.addObject(backWall);

    // // Light
    // Sphere *sphere1 = new Sphere(new Diffused(Color(1), Color(1.0), 0.8, 0.1),
    //                              250, vec3(0, 550, -2600));
    // scene.addObject(sphere1);

    // Sphere *sphere2 = new Sphere(new Diffused(Color(0.5, 0.5, 0.5), Color(0), 0.8, 0.1),
    //                              125, vec3(-200, -275, -2500));
    // scene.addObject(sphere2);

    // Sphere *sphere3 = new Sphere(new Dielectric(Color(1.0, 1.0, 1.0), Color(), 1.5),
    //                              125, vec3(200, -275, -2100));
    // scene.addObject(sphere3);

    // Light *light1 = new Light(vec3(0, 350, -1750), Color(1.0, 1.0, 1.0));
    // scene.addLight(light1);

   Sphere *sphere3 = new Sphere(new Diffused(Color(1.0, 1.0, 1.0), Color(1.0), 1.0, 0),
                                200, vec3(0, 200, -2500));
   scene.addObject(sphere3);

   Sphere *sphere4 = new Sphere(new Diffused(Color(0.5), Color(0), 1.0, 0),
                                200, vec3(0, -200, -2500));
   scene.addObject(sphere4);

   Rectangle *floor = new Rectangle(new Diffused(Color(0.1), Color(0), 1.0, 0),
                                    vec3(-800, -400, 0),
                                    vec3(-800, -400, -1e5),
                                    vec3(800, -400, -1e5),
                                    vec3(800, -400, 0));
   scene.addObject(floor);

//    SimpleRenderer renderer;
    RealisticRenderer renderer;
    renderer.render(scene);
}