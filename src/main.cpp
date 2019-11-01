#include <Scene.h>
#include <SimpleCamera.h>
#include <SimpleRenderer.h>
#include <Sphere.h>
#include "Options.h"

int main(int argc , char *argv[])
{
//    Options options(argc , argv);
//    options.parse();

    Camera *camera = new SimpleCamera(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0),
                                      30, 600, 800);
    Scene scene(camera);

    Material mat1(Color(1.0, 0.4, 0.8), 0.2, 0.4, 0.4, 32);
    Sphere *sphere1 = new Sphere(mat1, 100, vec3(300, 0, -2000));
    scene.addObject(sphere1);

    Material mat2(Color(0.3, 0.8, 0.2), 0.2, 0.4, 0.4, 32);
    Sphere *sphere2 = new Sphere(mat2, 100, vec3(-300, 0, -2000));
    scene.addObject(sphere2);

    Material mat3(Color(0.5, 0.2, 0.8), 0.2, 0.4, 0.4, 32);
    Sphere *sphere3 = new Sphere(mat3, 100, vec3(0, 0, -2000));
    scene.addObject(sphere3);

    Light *light1 = new Light(vec3(500, 500, -1000), Color(1.0, 1.0, 1.0));
    scene.addLight(light1);

    SimpleRenderer renderer;
    renderer.render(scene);
}