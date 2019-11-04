#include <Scene.h>
#include <SimpleCamera.h>
#include <SimpleRenderer.h>
#include <Sphere.h>
#include <Rectangle.h>
#include <Diffused.h>
#include <Dielectric.h>
#include "Options.h"

int main(int argc , char *argv[])
{
//    Options options(argc , argv);
//    options.parse();

    Camera *camera = new SimpleCamera(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0),
                                      30, 600, 800);
    Scene scene(camera, Color(0));

    Rectangle *leftWall = new Rectangle(new Diffused(Color(0.75, 0.25, 0.25), 0.7, 0.2),
                                        vec3(-475, -485, 10),
                                        vec3(-475, 485, 10),
                                        vec3(-475, 485, -3010),
                                        vec3(-475, -485, -3010));
    scene.addObject(leftWall);

    Rectangle *rightWall = new Rectangle(new Diffused(Color(0.25, 0.25, 0.75), 0.7, 0.2),
                                         vec3(475, -485, -3010),
                                         vec3(475, 485, -3010),
                                         vec3(475, 485, 10),
                                         vec3(475, -485, 10));
    scene.addObject(rightWall);

    Rectangle *ceiling = new Rectangle(new Diffused(Color(0.75, 0.75, 0.75), 0.7, 0.2),
                                       vec3(485, 400, 10),
                                       vec3(485, 400, -3010),
                                       vec3(-485, 400, -3010),
                                       vec3(-485, 400, 10));
    scene.addObject(ceiling);

    Rectangle *floor = new Rectangle(new Diffused(Color(0.75, 0.75, 0.75), 0.7, 0.2),
                                     vec3(-485, -400, 10),
                                     vec3(-485, -400, -3010),
                                     vec3(485, -400, -3010),
                                     vec3(485, -400, 10));
    scene.addObject(floor);

    Rectangle *frontWall = new Rectangle(new Diffused(Color(0.75, 0.75, 0.75), 0.7, 0.2),
                                         vec3(-485, 485, -3000),
                                         vec3(485, 485, -3000),
                                         vec3(485, -485, -3000),
                                         vec3(-485, -485, -3000));
    scene.addObject(frontWall);

    Rectangle *backWall = new Rectangle(new Diffused(Color(0.0, 0.0, 0.0), 0.7, 0.2),
                                        vec3(-485, 485, 0),
                                        vec3(-485, -485, 0),
                                        vec3(485, -485, 0),
                                        vec3(485, 485, 0));
    scene.addObject(backWall);

    Sphere *sphere1 = new Sphere(new Dielectric(Color(1.0, 1.0, 1.0), 1.5),
                                 125, vec3(-170, -250, -2300));
    scene.addObject(sphere1);

    Sphere *sphere2 = new Sphere(new Dielectric(Color(1.0, 1.0, 1.0), 1.5),
                                 125, vec3(170, -275, -1950));
    scene.addObject(sphere2);

    Sphere *sphere3 = new Sphere(new Dielectric(Color(1.0, 1.0, 1.0), 1.01),
                                 125, vec3(0, -275, -1600));
    scene.addObject(sphere3);

    Light *light1 = new Light(vec3(0, 350, -1750), Color(1.0, 1.0, 1.0));
    scene.addLight(light1);

    SimpleRenderer renderer;
    renderer.render(scene);
}