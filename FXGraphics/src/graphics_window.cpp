#include "graphics_window.h"

#include "basic_log.h"

namespace FX {

    namespace {

        void windowKeyboardCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
        {
            GraphicsEventProcessor::processKeyboard(pWindow, key, scancode, action, mods);
        }

        void windowCursorMoveCallback(GLFWwindow* pWindow, double x, double y)
        {
            GraphicsEventProcessor::processCursorMove(pWindow, static_cast<float>(x), static_cast<float>(y));
        }

        void windowMouseButtonCallback(GLFWwindow* pWindow, int button, int action, int mods)
        {
            GraphicsEventProcessor::processMouseButton(pWindow, button, action, mods);
        }

    }  // namespace

    GraphicsWindow::GraphicsWindow(unsigned short width, unsigned short height, const std::string& title, bool isMultiSample)
        : m_windowSize({ width, height }), m_bufferSize({ width, height }), m_title(title), m_isMultiSample(isMultiSample),
          m_creationTime(std::chrono::steady_clock::now())
    {
        // init glfw
        isMultiSample ? glfwWindowHint(GLFW_SAMPLES, 4) : glfwWindowHint(GLFW_SAMPLES, 0);

        m_pWindowHandle = glfwCreateWindow(width, height, title.c_str(), 0, 0);
        if (m_pWindowHandle == nullptr)
        {
            BasicLog::out(BasicLog::kError, "CANNOT CREATE WINDOW [", title, "]!");
        }

        glfwMakeContextCurrent(m_pWindowHandle);
        s_pCurrentWindow = this;
        s_windowMap.insert({ m_pWindowHandle, this });

        glfwSwapInterval(1);

        // init glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            BasicLog::out(BasicLog::kError, "CANNOT INIT OPENGL!");
        }

        isMultiSample ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);

        glfwSetKeyCallback(m_pWindowHandle, windowKeyboardCallback);
        glfwSetCursorPosCallback(m_pWindowHandle, windowCursorMoveCallback);
        glfwSetMouseButtonCallback(m_pWindowHandle, windowMouseButtonCallback);
    }

    GraphicsWindow::~GraphicsWindow()
    {
        if (!m_bufferList.empty() || !m_recycledBufferList.empty())
        {
            auto pOriginalWindow = s_pCurrentWindow;

            if (pOriginalWindow != this)
            {
                glfwMakeContextCurrent(m_pWindowHandle);
            }

            releaseBuffer(m_bufferList);
            releaseBuffer(m_recycledBufferList);

            if (pOriginalWindow != this)
            {
                glfwMakeContextCurrent(pOriginalWindow == nullptr ? 0 : pOriginalWindow->m_pWindowHandle);
            }
        }

        s_windowMap.erase(m_pWindowHandle);
        glfwDestroyWindow(m_pWindowHandle);

        if (s_pCurrentWindow == this)
        {
            auto pCurrent = glfwGetCurrentContext();
            if (pCurrent != nullptr)
            {
                auto itr = s_windowMap.find(pCurrent);
                s_pCurrentWindow = itr != s_windowMap.end() ? (*itr).second : nullptr;
            }
            else
            {
                s_pCurrentWindow = nullptr;
                glfwMakeContextCurrent(0);
            }
        }
    }

    void GraphicsWindow::use()
    {
        if (s_pCurrentWindow != this)
        {
            glfwMakeContextCurrent(m_pWindowHandle);
            if (m_isMultiSample != s_pCurrentWindow->m_isMultiSample)
            {
                m_isMultiSample ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);
            }
            glViewport(0, 0, m_bufferSize.x, m_bufferSize.y);
            s_pCurrentWindow = this;
        }
    }

    void GraphicsWindow::frame()
    {
        if (s_pCurrentWindow == this)
        {
            releaseBuffer(m_recycledBufferList);
        }
        else
        {
            BasicLog::out(BasicLog::kWarn, "Frame a window that is not currently used.");
        }

        glfwSwapBuffers(m_pWindowHandle);
        glfwPollEvents();
    }

    bool GraphicsWindow::shouldClose() const
    {
        return glfwWindowShouldClose(m_pWindowHandle);
    }

    void GraphicsWindow::addBuffer(GraphicsBufferObject& buffer)
    {
        m_bufferList.insert(&buffer);
    }

    void GraphicsWindow::removeBuffer(GraphicsBufferObject& buffer)
    {
        m_bufferList.erase(&buffer);
    }

    void GraphicsWindow::addRecycledBuffer(BufferInfo buffer)
    {
        m_recycledBufferList.insert(buffer);
    }

    void GraphicsWindow::releaseBuffer(std::set<GraphicsWindow::BufferInfo>& bufferList) const
    {
        for (auto&& bufferInfo : bufferList)
        {
            switch (bufferInfo.type)
            {
                case GraphicsBufferObject::Type::kProgram:
                    glDeleteProgram(bufferInfo.handle);
                    break;
                case GraphicsBufferObject::Type::kShader:
                    glDeleteShader(bufferInfo.handle);
                    break;
                case GraphicsBufferObject::Type::kVertexArray:
                    glDeleteVertexArrays(1, &bufferInfo.handle);
                    break;
                case GraphicsBufferObject::Type::kBuffer:
                    glDeleteBuffers(1, &bufferInfo.handle);
                    break;
                case GraphicsBufferObject::Type::kTexture:
                    glDeleteTextures(1, &bufferInfo.handle);
                    break;
                default:
                    BasicLog::out(BasicLog::kWarn, "Cannot release a buffer of undefined buffer type.");
                    break;
            }
        }

        bufferList.clear();
    }

    void GraphicsWindow::releaseBuffer(std::set<GraphicsBufferObject*>& bufferList) const
    {
        for (auto&& pBuffer : bufferList)
        {
            if (pBuffer == nullptr)
            {
                continue;
            }

            auto buffer = pBuffer->getOrCreate();
            switch (pBuffer->m_type)
            {
                case GraphicsBufferObject::Type::kProgram:
                    glDeleteProgram(buffer.handle);
                    break;
                case GraphicsBufferObject::Type::kShader:
                    glDeleteShader(buffer.handle);
                    break;
                case GraphicsBufferObject::Type::kVertexArray:
                    glDeleteVertexArrays(1, &buffer.handle);
                    break;
                case GraphicsBufferObject::Type::kBuffer:
                    glDeleteBuffers(1, &buffer.handle);
                    break;
                case GraphicsBufferObject::Type::kTexture:
                    glDeleteTextures(1, &buffer.handle);
                    break;
                default:
                    BasicLog::out(BasicLog::kWarn, "Cannot release a buffer of undefined buffer type.");
                    break;
            }

            pBuffer->notifyRemove();
        }

        bufferList.clear();
    }

    GraphicsWindow* GraphicsWindow::s_pCurrentWindow = nullptr;
    GraphicsWindow::WindowMap GraphicsWindow::s_windowMap = GraphicsWindow::WindowMap();

    void GraphicsEventProcessor::processKeyboard(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
    {

    }

    void GraphicsEventProcessor::processCursorMove(GLFWwindow* pWindow, float x, float y)
    {

    }

    void GraphicsEventProcessor::processMouseButton(GLFWwindow* pWindow, int button, int action, int mods)
    {

    }

} // namespace FX
