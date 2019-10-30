#include <Scene.h>
#include <SimpleCamera.h>
#include <Renderer.h>
#include "Options.h"

int main(int argc , char *argv[])
{
    Options options(argc , argv);
    options.parse();

    Camera *camera = new SimpleCamera(vec3(0), vec3(0, 0, -1), vec3(0, 1, 0), 10, 500, 500);
    Scene scene(camera);

//    Renderer renderer;
//    renderer.render(scene);
}