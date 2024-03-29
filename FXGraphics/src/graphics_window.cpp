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
        init();
    }

    void GraphicsWindow::init()
    {
        // init glfw
        m_isMultiSample ? glfwWindowHint(GLFW_SAMPLES, 4) : glfwWindowHint(GLFW_SAMPLES, 0);

        m_pWindowHandle = glfwCreateWindow(m_windowSize.x, m_windowSize.y, m_title.c_str(), 0, 0);
        if (m_pWindowHandle == nullptr)
        {
            BasicLog::out(BasicLog::kError, "CANNOT CREATE WINDOW [", m_title, "]!");
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

        m_isMultiSample ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);

        glfwSetKeyCallback(m_pWindowHandle, windowKeyboardCallback);
        glfwSetCursorPosCallback(m_pWindowHandle, windowCursorMoveCallback);
        glfwSetMouseButtonCallback(m_pWindowHandle, windowMouseButtonCallback);
    }

    GraphicsWindow::~GraphicsWindow()
    {
        uninit();
    }

    void GraphicsWindow::uninit()
    {
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
            m_isMultiSample ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);
            s_pCurrentWindow = this;
        }
    }

    void GraphicsWindow::frame()
    {
        if (s_pCurrentWindow != this)
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

    GraphicsWindow* GraphicsWindow::s_pCurrentWindow = nullptr;
    GraphicsWindow::WindowMap GraphicsWindow::s_windowMap;

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
