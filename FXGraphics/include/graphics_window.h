#ifndef _GRAPHICS_WINDOW_H_
#define _GRAPHICS_WINDOW_H_

#include <string>
#include <map>
#include <chrono>
#include "glad.h"
#include "glfw3.h"

#include "basic_vector.h"
#include "basic_macro.h"
#include "graphics_instance.h"

namespace FX {

    class GraphicsWindow {
    public:
        friend class GraphicsEventProcessor;

        GraphicsWindow(unsigned short width, unsigned short height, const std::string& title = "FXGraphics", bool isMultiSample = true);
        virtual ~GraphicsWindow(void);

        DELETE_COPY_AND_MOVE_CONSTRUCT(GraphicsWindow);

    public:
        void use(void);
        void frame(void);
        bool shouldClose(void) const;

    protected:
        virtual void init(void);
        virtual void uninit(void);

    protected:
        GLFWwindow* m_pWindowHandle = { nullptr };
        vec2us m_windowSize = { 1280, 720 };
        vec2us m_bufferSize = { 1280, 720 };
        std::string m_title;
        const std::chrono::steady_clock::time_point m_creationTime;
        bool m_isMultiSample = true;

        static GraphicsWindow* s_pCurrentWindow;
        using WindowMap = std::map<const GLFWwindow*, GraphicsWindow*>;
        static WindowMap s_windowMap;
    };


    class GraphicsEventProcessor {
    private:
        GraphicsEventProcessor(void) = default;
        ~GraphicsEventProcessor(void) = default;

    public:
        static void processKeyboard(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
        static void processCursorMove(GLFWwindow* pWindow, float x, float y);
        static void processMouseButton(GLFWwindow* pWindow, int button, int action, int mods);
    };

} // namespace FX

#endif // _GRAPHICS_WINDOW_H_
