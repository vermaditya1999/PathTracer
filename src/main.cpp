#include <Scene.h>
#include <camera/SimpleCamera.h>
#include <geometry/Sphere.h>
#include <geometry/Rectangle.h>
#include <material/Diffused.h>
#include <material/Dielectric.h>
#include <renderer/RealisticRenderer.h>
#include <material/Glossy.h>
#include "Options.h"

int main(int argc , char *argv[])
{
    Camera *camera = new SimpleCamera(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0),
                                      30, 600, 800);
    Scene scene(camera, Color(0));

    int scene_id = 0;
    switch (scene_id) {
        case 0: {
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

            int radius = 125;
            Sphere *sphere1 = new Sphere(new Glossy(Color(1.0), Color(0), 0.2, 0.7, 0.1, 32),
                                         radius, vec3(-225, DY - 1.5 * radius, -2100));
            scene.addObject(sphere1);

            Sphere *sphere2 = new Sphere(new Dielectric(Color(1.0), Color(), 1.5),
                                         radius, vec3(225, -DY + radius, -1700));
            scene.addObject(sphere2);

            Sphere *sphere3 = new Sphere(new Diffused(Color(0.27, 0.54, 0.46), Color(0), 0.2, 0.1),
                                         radius, vec3(-150, -DY + radius, -1500));
            scene.addObject(sphere3);

            // Light
            Sphere *light1 = new Sphere(new Diffused(Color(1.0), Color(10.0), 1.0, 0.0),
                                        2 * radius, vec3(0, DY + 1.5 * radius, -1600));
            scene.addObject(light1);
        }
            break;
        case 1: {
            Sphere *sphere3 = new Sphere(new Diffused(Color(1.0, 1.0, 1.0), Color(1.0), 1.0, 0),
                                         100, vec3(0, -100, -2000));
            scene.addObject(sphere3);

            Sphere *sphere4 = new Sphere(new Diffused(Color(0.5), Color(0), 1.0, 0),
                                         100, vec3(0, -300, -2000));
            scene.addObject(sphere4);

            Rectangle *floor = new Rectangle(new Diffused(Color(0.1), Color(0), 1.0, 0),
                                             vec3(-485, -400, 1000),
                                             vec3(-485, -400, -1e5),
                                             vec3(485, -400, -1e5),
                                             vec3(485, -400, 1000));
            scene.addObject(floor);
        }
            break;
    }

    RealisticRenderer renderer;
    renderer.render(scene);
}
