#include <Scene.h>
#include <SimpleCamera.h>
#include <SimpleRenderer.h>
#include <Sphere.h>
#include "Options.h"

int main(int argc , char *argv[])
{
//    Options options(argc , argv);
//    options.parse();

    Camera *camera = new SimpleCamera(vec3(0, 0, 1000), vec3(0, 0, -1), vec3(0, 1, 0), 5,
                                      800, 400);
    Scene scene(camera);

    Material mat(Color(1.0, 0.0, 0.0));
    Sphere *sphere = new Sphere(mat, 100, vec3(100, -100, -100));
    scene.addObject(sphere);

    SimpleRenderer renderer;
    renderer.render(scene);
}