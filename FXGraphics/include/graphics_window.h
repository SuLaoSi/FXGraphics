#ifndef _GRAPHICS_WINDOW_H_
#define _GRAPHICS_WINDOW_H_

#include <string>
#include <map>
#include <set>
#include <chrono>
#include "glad.h"
#include "glfw3.h"

#include "basic_vector.h"
#include "basic_macro.h"
#include "graphics_instance.h"
#include "graphics_buffer_object.h"

namespace FX {

    class GraphicsScene;

    class GraphicsWindow {
    public:
        friend class GraphicsEventProcessor;
        friend class GraphicsBufferObject;
        friend class GraphicsScene;

        GraphicsWindow(unsigned short width, unsigned short height, const std::string& title = "FXGraphics", bool isMultiSample = true);
        virtual ~GraphicsWindow(void);

        DELETE_COPY_CONSTRUCT(GraphicsWindow);

    public:
        void use(void);
        void frame(void);
        bool shouldClose(void) const;

    private:
        struct BufferInfo {
            GraphicsBufferObject::Type type = GraphicsBufferObject::Type::kNone;
            unsigned int handle = 0;
            bool operator<(const BufferInfo& other) const
            {
                return this->type != other.type ? this->type < other.type : this->handle < other.handle;
            }
        };

        void addBuffer(GraphicsBufferObject& buffer);
        void removeBuffer(GraphicsBufferObject& buffer);
        void addRecycledBuffer(BufferInfo buffer);
        void releaseBuffer(std::set<GraphicsWindow::BufferInfo>& bufferList) const;
        void releaseBuffer(std::set<GraphicsBufferObject*>& bufferList) const;

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

    private:
        std::set<GraphicsBufferObject*> m_bufferList;
        std::set<BufferInfo> m_recycledBufferList;
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
