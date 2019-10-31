#include <Scene.h>
#include <SimpleCamera.h>
#include <SimpleRenderer.h>
#include <Sphere.h>
#include "Options.h"

int main(int argc , char *argv[])
{
//    Options options(argc , argv);
//    options.parse();

    Camera *camera = new SimpleCamera(vec3(0, 0, 100), vec3(0, 0, -1), vec3(0, 1, 0),
                                      100, 1080, 1920);
    Scene scene(camera);

    Material mat1(Color(1.0, 0.4, 0.8), 0.2, 0.4, 0.4, 32);
    Sphere *sphere1 = new Sphere(mat1, 800, vec3(0, 0, -1000));
    scene.addObject(sphere1);

    Light *light1 = new Light(vec3(400, 200, 200), Color(1.0, 1.0, 1.0));
    scene.addLight(light1);

    SimpleRenderer renderer;
    renderer.render(scene);
}