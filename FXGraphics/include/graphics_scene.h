#ifndef _GRAPHICS_SCENE_H_
#define _GRAPHICS_SCENE_H_

#include "graphics_buffer_object.h"

namespace FX {

    class GraphicsWindow;

    class GraphicsScene : public GraphicsBufferObject {
    public:
        explicit GraphicsScene(const GraphicsWindow& window);
        ~GraphicsScene(void);

        void draw(void);

    protected:
        unsigned int create(void) const override;

        void beforeDraw(void);
        void afterDraw(void);

    protected:
        const GraphicsWindow* m_pWindow = { nullptr };
    };

} // namespace FX

#endif // _GRAPHICS_SCENE_H_
