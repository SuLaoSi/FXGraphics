#include <iostream>
#include "graphics_window.h"

int main(void)
{
    FX::GraphicsWindow window(800, 600);

    window.use();

    gladLoadGL();

    while (!window.shouldClose())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        window.frame();
    }
}