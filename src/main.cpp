#include <Scene.h>
#include <SimpleCamera.h>
#include <SimpleRenderer.h>
#include <Sphere.h>
#include <Rectangle.h>
#include "Options.h"

int main(int argc , char *argv[])
{
//    Options options(argc , argv);
//    options.parse();

    Camera *camera = new SimpleCamera(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0),
                                      30, 600, 800);
    Scene scene(camera);

    Rectangle *leftWall = new Rectangle(Material(Color(0.75, 0.25, 0.25), 0.2, 0.7, 0.1, 16),
                                        vec3(-400, -410, 10),
                                        vec3(-400, 410, 10),
                                        vec3(-400, 410, -2510),
                                        vec3(-400, -410, -2510));
    scene.addObject(leftWall);

    Rectangle *rightWall = new Rectangle(Material(Color(0.25, 0.25, 0.75), 0.2, 0.7, 0.1, 16),
                                         vec3(400, -410, -2510),
                                         vec3(400, 410, -2510),
                                         vec3(400, 410, 10),
                                         vec3(400, -410, 10));
    scene.addObject(rightWall);

    Rectangle *ceiling = new Rectangle(Material(Color(0.75, 0.75, 0.75), 0.2, 0.7, 0.1, 16),
                                       vec3(410, 400, 10),
                                       vec3(410, 400, -2510),
                                       vec3(-410, 400, -2510),
                                       vec3(-410, 400, 10));
    scene.addObject(ceiling);

    Rectangle *floor = new Rectangle(Material(Color(0.75, 0.75, 0.75), 0.2, 0.7, 0.1, 16),
                                     vec3(-410, -400, 10),
                                     vec3(-410, -400, -2510),
                                     vec3(410, -400, -2510),
                                     vec3(410, -400, 10));
    scene.addObject(floor);

    Rectangle *frontWall = new Rectangle(Material(Color(0.75, 0.75, 0.75), 0.2, 0.7, 0.1, 16),
                                         vec3(-410, 410, -2500),
                                         vec3(410, 410, -2500),
                                         vec3(410, -410, -2500),
                                         vec3(-410, -410, -2500));
    scene.addObject(frontWall);

    Rectangle *backWall = new Rectangle(Material(Color(0.75, 0.75, 0.75), 0.2, 0.7, 0.1, 16),
                                        vec3(-410, 410, 0),
                                        vec3(-410, -410, 0),
                                        vec3(410, -410, 0),
                                        vec3(410, 410, 0));
    scene.addObject(backWall);

    Light *light1 = new Light(vec3(0, 100, -1250), Color(1.0, 1.0, 1.0));
    scene.addLight(light1);

    Sphere *sphere1 = new Sphere(Material(Color(1.0, 1.0, 1.0), 0.1, 0.3, 0.6, 64, true),
                                 125, vec3(-170, -275, -2000));
    scene.addObject(sphere1);

    Sphere *sphere2 = new Sphere(Material(Color(1.0, 1.0, 1.0), 0.1, 0.3, 0.6, 64, true),
                                 125, vec3(170, -275, -1750));
    scene.addObject(sphere2);

    SimpleRenderer renderer;
    renderer.render(scene);
}