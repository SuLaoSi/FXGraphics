#include "graphics_scene.h"

#include "basic_log.h"
#include "graphics_window.h"

namespace FX {

    GraphicsScene::GraphicsScene(const GraphicsWindow& window)
        : GraphicsBufferObject(GraphicsBufferObject::Type::kProgram), m_pWindow(&window)
    {
    }

    GraphicsScene::~GraphicsScene() {}

    void GraphicsScene::draw()
    {
        if (GraphicsWindow::s_pCurrentWindow != m_pWindow)
        {
            BasicLog::out(BasicLog::kWarn, "Trying to draw a GraphicsScene, but its window is not used, discard.");
            return;
        }

        beforeDraw();

        // TO DO

        afterDraw();
    }

    unsigned int GraphicsScene::create() const
    {
        auto handle = glCreateProgram();

        if (handle == 0)
        {
            BasicLog::out(BasicLog::kWarn, "Failed to create opengl program.");
        }

        return handle;
    }

    void GraphicsScene::beforeDraw()
    {
        auto program = getOrCreate();
        if (program.isDirty == true)
        {
            // TO DO

            setReady();
        }

        glUseProgram(program.handle);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
    }

    void GraphicsScene::afterDraw()
    {
        glUseProgram(0);
    }

} // namespace FX
