#include "graphics_instance.h"

#include "glfw3.h"

#include "basic_platform.h"
#include "basic_log.h"

namespace FX {

    GraphicsInstance::GraphicsInstance()
    {
        if (glfwInit() == false)
        {
            BasicLog::out(BasicLog::kError, "CANNOT INIT GLFW!");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef FX_APPLE
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    GraphicsInstance::~GraphicsInstance()
    {
        glfwTerminate();
    }

    GraphicsInstance GraphicsInstance::s_instance = GraphicsInstance();

} // namespace FX
