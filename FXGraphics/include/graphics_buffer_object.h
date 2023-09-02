#ifndef _GRAPHICS_BUFFER_OBJECT_H_
#define _GRAPHICS_BUFFER_OBJECT_H_

#include <map>

#include "basic_macro.h"
#include "graphics_instance.h"

namespace FX {

    class GraphicsWindow;

    class GraphicsBufferObject {
    public:
        friend class GraphicsWindow;

        enum class Type : unsigned int {
            kNone = 0,
            kProgram,
            kShader,
            kVertexArray,
            kBuffer,
            kTexture,
        };

        void setDirty(bool isDirty = true);

    protected:
        explicit GraphicsBufferObject(Type type);
        virtual ~GraphicsBufferObject(void);

        DELETE_COPY_AND_MOVE_CONSTRUCT(GraphicsBufferObject);

        struct BufferInfo {
            unsigned int handle = 0;
            bool isDirty = false;
        };

        virtual unsigned int create(void) const = 0;    // Override with opengl api to create and return with the handle.

        BufferInfo getOrCreate(void);

        void setReady(void);    // Notify this buffer is ready for only current window.

    private:
        void notifyRemove(void);

    private:
        std::map<GraphicsWindow*, BufferInfo> m_bufferList;
        Type m_type = Type::kNone;
    };

} // namespace FX

#endif // _GRAPHICS_BUFFER_OBJECT_H_
