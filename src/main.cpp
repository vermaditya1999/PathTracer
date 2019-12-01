#include <Scene.h>
#include <camera/SimpleCamera.h>
#include <geometry/Sphere.h>
#include <geometry/Rectangle.h>
#include <material/Diffused.h>
#include <material/Dielectric.h>
#include <renderer/RealisticRenderer.h>
#include <material/Glossy.h>
#include "Options.h"
#include <chrono>
#include <material/SpecularDiffused.h>

int main(int argc , char *argv[])
{
    debug("Running in Debug mode ...", 1);
    Camera *camera = new SimpleCamera(vec3(0, 0, -100), vec3(0, 0, -1), vec3(0, 1, 0),
                                      30, 600, 800 , 15000 , 0.002);
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

            Rectangle *floor = new Rectangle(new Diffused(Color(0.75), Color(0), 9.0, 1),
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

            Sphere *sphere2 = new Sphere(new Dielectric(Color(1.0), Color(), 1.5),
                                         radius, vec3(250, -DY + radius, -1700));
            scene.addObject(sphere2);

            Sphere *sphere3 = new Sphere(new Glossy(Color(1.0 ,0.843, 0), Color(0), 0.2, 0.7, 0.1, 10),
                                         radius, vec3(-200, -DY + radius, -2000));
            scene.addObject(sphere3);

            // Light
            Sphere *light1 = new Sphere(new Diffused(Color(1.0), Color(10.0), 1.0, 0.0),
                                        1e5, vec3(0, DY + 1e5 - 0.2, -2000));
            scene.addObject(light1);
        }
            break;
        case 1: {
//            // Light
//            scene.addObject(new Sphere(new Diffused(Color(1.0, 1.0, 1.0), Color(10.0), 1.0, 0),
//                                       100, vec3(0, -100, -2000)));
//
//            // Diffused ball
//            scene.addObject(new Sphere(new Diffused(Color(0.5), Color(0), 1.0, 0),
//                                       100, vec3(0, -300, -2000)));
//
//            // Floor
//            scene.addObject(new Rectangle(new SpecularDiffused(Color(0.1), Color(0), 0.8),
//                                          vec3(-1e5, -400, 0),
//                                          vec3(-1e5, -400, -1e5),
//                                          vec3(1e5, -400, -1e5),
//                                          vec3(1e5, -400, 0)));

            scene.addObject(new Sphere(new Diffused(Color(1.0, 1.0, 1.0), Color(15.0), 1.0, 0),
                                       100, vec3(0, 200 , -2000)));

            // DOF Scene
            // Diffused ball
            scene.addObject(new Sphere(new Diffused(Color(0.5), Color(0), 1.0, 0),
                                       100, vec3(0, 0, -2000)));
            scene.addObject(new Sphere(new Diffused(Color(0.023 , 0.84 , 0.627), Color(0), 1.0, 0),
                                       100, vec3(500, 0, -1500)));
            scene.addObject(new Sphere(new Diffused(Color(0.9 , 0.3 , 0.5), Color(0), 1.0, 0),
                                       100, vec3(-500, 0, -1500)));

            scene.addObject(new Sphere(new Diffused(Color(1 , 0.42 , 0.42), Color(0), 1.0, 0),
                                       80, vec3(300, 0, -1700)));
            scene.addObject(new Sphere(new Diffused(Color(0.03 , 0.376 , 0.372), Color(0), 1.0, 0),
                                       80, vec3(-300, 0, -1700)));
            // Floor
            scene.addObject(new Rectangle(new Diffused(Color(0.1), Color(0), 1.0, 0),
                                          vec3(-1e5, -100, 0),
                                          vec3(-1e5, -100, -1e5),
                                          vec3(1e5, -100, -1e5),
                                          vec3(1e5, -100, 0)));
        }
            break;
        case 2: {
            int dx = 1e8, dy = 1e8;

            // Light
            scene.addObject(new Rectangle(new Diffused(Color(1.0), Color(10.0), 1.0, 0),
                            vec3(dx, dy, 1e8),
                            vec3(dx, dy, -1e8),
                            vec3(-dx, dy, -1e8),
                            vec3(-dx, dy, 1e8)));

            dx = 400, dy = 400;
            scene.addObject(new Rectangle(new Diffused(Color(1.0, 0.5, 0.7), Color(0.0), 1.0, 0),
                          vec3(dx, dy, -1750),
                          vec3(dx, -dy, -1750),
                          vec3(-dx, -dy, -1750),
                          vec3(-dx, dy, -1750)));
        }
    }

    RealisticRenderer renderer;

    auto start = std::chrono::high_resolution_clock::now();
    renderer.render(scene);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    fprintf(stdout, "Time elapsed: %lds\n", duration);
}
