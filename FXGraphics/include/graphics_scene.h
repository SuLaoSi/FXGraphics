#ifndef _GRAPHICS_SCENE_H_
#define _GRAPHICS_SCENE_H_

#include <set>

#include "graphics_buffer_object.h"

namespace FX {

    class GraphicsWindow;
    class GraphicsShader;

    class GraphicsScene : public GraphicsBufferObject {
    public:
        explicit GraphicsScene(const GraphicsWindow& window);
        ~GraphicsScene(void);

        void draw(void);

        void addShader(GraphicsShader& shader);
        void removeShader(GraphicsShader& shader);

    protected:
        unsigned int create(void) const override;

        void beforeDraw(void);
        void afterDraw(void);

    protected:
        const GraphicsWindow* m_pWindow = { nullptr };
        std::set<GraphicsShader*> m_shaderList;
    };

} // namespace FX

#endif // _GRAPHICS_SCENE_H_
