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
                                        vec3(-400, -400, 0),
                                        vec3(-400, 400, 0),
                                        vec3(-400, 400, -2500),
                                        vec3(-400, -400, -2500));
    scene.addObject(leftWall);

    Rectangle *rightWall = new Rectangle(Material(Color(0.25, 0.25, 0.75), 0.2, 0.7, 0.1, 16),
                                         vec3(400, -400, -2500),
                                         vec3(400, 400, -2500),
                                         vec3(400, 400, 0),
                                         vec3(400, -400, 0));
    scene.addObject(rightWall);

    Rectangle *ceiling = new Rectangle(Material(Color(0.75, 0.75, 0.75), 0.2, 0.7, 0.1, 16),
                                       vec3(400, 400, 0),
                                       vec3(400, 400, -2500),
                                       vec3(-400, 400, -2500),
                                       vec3(-400, 400, 0));
    scene.addObject(ceiling);

    Rectangle *floor = new Rectangle(Material(Color(0.75, 0.75, 0.75), 0.2, 0.7, 0.1, 16),
                                     vec3(-400, -400, 0),
                                     vec3(-400, -400, -2500),
                                     vec3(400, -400, -2500),
                                     vec3(400, -400, 0));
    scene.addObject(floor);

    Rectangle *frontWall = new Rectangle(Material(Color(0.75, 0.75, 0.75), 0.2, 0.7, 0.1, 16),
                                         vec3(-400, 400, -2500),
                                         vec3(400, 400, -2500),
                                         vec3(400, -400, -2500),
                                         vec3(-400, -400, -2500));
    scene.addObject(frontWall);

    Rectangle *backWall = new Rectangle(Material(Color(0.75, 0.75, 0.75), 0.2, 0.7, 0.1, 16),
                                        vec3(-400, 400, 0),
                                        vec3(-400, -400, 0),
                                        vec3(400, -400, 0),
                                        vec3(400, 400, 0));
    scene.addObject(backWall);

    Light *light1 = new Light(vec3(0, 375, -1250), Color(1.0, 1.0, 1.0));
    scene.addLight(light1);

    Sphere *sphere1 = new Sphere(Material(Color(0.1, 0.4, 0.4), 0.2, 0.4, 0.4, 32),
                                 125, vec3(-150, -275, -2000));
    scene.addObject(sphere1);

    SimpleRenderer renderer;
    renderer.render(scene);
}