#include <iostream>
#include "graphics_window.h"
#include "graphics_scene.h"

int main(void)
{
    FX::GraphicsWindow window(800, 600);

    window.use();

    FX::GraphicsScene scene(window);

    while (!window.shouldClose())
    {
        scene.draw();

        window.frame();
    }
}