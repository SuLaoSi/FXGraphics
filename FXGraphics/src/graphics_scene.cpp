#include "graphics_scene.h"

#include "basic_log.h"
#include "graphics_window.h"
#include "graphics_shader.h"

namespace FX {

    GraphicsScene::GraphicsScene(const GraphicsWindow& window)
        : GraphicsBufferObject(GraphicsBufferObject::Type::kProgram), m_pWindow(&window)
    {
    }

    GraphicsScene::~GraphicsScene()
    {
        for (auto pShader : m_shaderList)
        {
            if (pShader == nullptr)
            {
                continue;
            }

            pShader->removeScene(*this);
        }
    }

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

    void GraphicsScene::addShader(GraphicsShader& shader)
    {
        m_shaderList.insert(&shader);
        shader.addScene(*this);
        setDirty();
    }

    void GraphicsScene::removeShader(GraphicsShader& shader)
    {
        m_shaderList.erase(&shader);
        shader.removeScene(*this);
        setDirty();
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
            for (auto pShader : m_shaderList)
            {
                auto shader = pShader->getOrCreate();
                if (shader.isDirty == true)
                {
                    pShader->update(shader.handle);
                    pShader->setReady();
                }


            }



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
