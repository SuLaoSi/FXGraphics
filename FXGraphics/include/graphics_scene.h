#ifndef _GRAPHICS_SCENE_H_
#define _GRAPHICS_SCENE_H_

#include "graphics_entity_group.h"
#include "graphics_diverter.h"

namespace FX {

    class GraphicsScene {
    public:
        GraphicsScene(void);
        virtual ~GraphicsScene(void);

    protected:
        GraphicsScene(void) = default;

    public:
        template<class T>
        bool addEntity(GraphicsEntity<T>* pEntity)
        {
            return m_pDiverter->addEntity(pEntity);
        }

        template<class T>
        bool removeEntity(GraphicsEntity<T>* pEntity)
        {
            return m_pDiverter->removeEntity(pEntity);
        }

        virtual void draw(void);

    protected:
        GraphicsDiverter* m_pDiverter = nullptr;

        GraphicsEntityGroup<Vertex> m_entityVGroup;
        GraphicsEntityGroup<VertexIndex> m_entityVIGroup;
        GraphicsEntityGroup<VertexNormal> m_entityVNGroup;
        GraphicsEntityGroup<VertexNormalIndex> m_entityVNIGroup;
    };

} // namespace FX

#endif // _GRAPHICS_SCENE_H_
