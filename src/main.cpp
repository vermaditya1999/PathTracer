#include <Scene.h>
#include <camera/SimpleCamera.h>
#include <geometry/Sphere.h>
#include <geometry/Rectangle.h>
#include <material/Diffused.h>
#include <material/Dielectric.h>
#include <renderer/RealisticRenderer.h>
#include "Options.h"

int main(int argc , char *argv[])
{
    Camera *camera = new SimpleCamera(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0),
                                      30, 600, 800);
    Scene scene(camera, Color(0));

    int DX = 475, DY = 300;
    Rectangle *leftWall = new Rectangle(new Diffused(Color(0.75, 0.25, 0.25), Color(), 0.7, 0.2),
                                        vec3(-DX, -DY, 0),
                                        vec3(-DX, DY, 0),
                                        vec3(-DX, DY, -2600),
                                        vec3(-DX, -DY, -2600));
    scene.addObject(leftWall);

    Rectangle *rightWall = new Rectangle(new Diffused(Color(0.25, 0.25, 0.75), Color(), 0.7, 0.2),
                                         vec3(DX, -DY, -2600),
                                         vec3(DX, DY, -2600),
                                         vec3(DX, DY, 0),
                                         vec3(DX, -DY, 0));
    scene.addObject(rightWall);

    Rectangle *ceiling = new Rectangle(new Diffused(Color(0.75, 0.75, 0.75), Color(), 0.7, 0.2),
                                       vec3(DX, DY, 0),
                                       vec3(DX, DY, -2600),
                                       vec3(-DX, DY, -2600),
                                       vec3(-DX, DY, 0));
    scene.addObject(ceiling);

    Rectangle *floor = new Rectangle(new Diffused(Color(0.75, 0.75, 0.75), Color(), 0.7, 0.2),
                                     vec3(-DX, -DY, 0),
                                     vec3(-DX, -DY, -2600),
                                     vec3(DX, -DY, -2600),
                                     vec3(DX, -DY, 0));
    scene.addObject(floor);

    Rectangle *frontWall = new Rectangle(new Diffused(Color(0.75, 0.75, 0.75), Color(), 0.7, 0.2),
                                         vec3(-DX, DY, -2600),
                                         vec3(DX, DY, -2600),
                                         vec3(DX, -DY, -2600),
                                         vec3(-DX, -DY, -2600));
    scene.addObject(frontWall);

    Rectangle *backWall = new Rectangle(new Diffused(Color(0.0, 0.0, 0.0), Color(), 0.7, 0.2),
                                        vec3(-DX, DY, 0),
                                        vec3(-DX, -DY, 0),
                                        vec3(DX, -DY, 0),
                                        vec3(DX, DY, 0));
    scene.addObject(backWall);

    // Light
    Sphere* light1 = new Sphere(new Diffused(Color(1.0), Color(12.0), 1.0, 0.0),
                                            1e5, vec3(0, 1e5 + DY - 0.1, -1500));
    scene.addObject(light1);

    int radius = 125;
    Sphere *sphere2 = new Sphere(new Diffused(Color(0.5), Color(0), 0.8, 0.1),
                                 125, vec3(-250, -DY + radius, -2200));
    scene.addObject(sphere2);

    Sphere *sphere3 = new Sphere(new Dielectric(Color(1.0, 1.0, 1.0), Color(), 1.5),
                                 125, vec3(250, -DY + radius, -1700));
    scene.addObject(sphere3);

    RealisticRenderer renderer;
    renderer.render(scene);
}