#ifndef _GRAPHICS_DIVERTER_H_
#define _GRAPHICS_DIVERTER_H_

#include <set>

#include "graphics_entity.h"
#include "graphics_entity_group.h"

namespace FX {

    class GraphicsScene;

    class GraphicsDiverter {
    protected:
        friend class GraphicsScene;

        GraphicsDiverter(GraphicsScene* pScene) : m_pScene(pScene) {}
        virtual ~GraphicsDiverter(void) = default;

    public:
        template<class T>
        bool addEntity(GraphicsEntity<T>* pEntity)
        {
            static_assert(false, "Please implement add function of specific type!");
            return false;
        }

        template<class T>
        bool removeEntity(GraphicsEntity<T>* pEntity)
        {
            static_assert(false, "Please implement remove function of specific type!");
            return false;
        }

#define FUNCTION_DEFINITION(TYPE, TARGET)                \
        bool addEntity(GraphicsEntity<TYPE>* pEntity)    \
        {                                                \
            return TARGET->addEntity(pEntity);           \
        }                                                \
        bool removeEntity(GraphicsEntity<TYPE>* pEntity) \
        {                                                \
            return TARGET->addEntity(pEntity);           \
        }

        FUNCTION_DEFINITION(Vertex, m_pEntityVGroup)
        FUNCTION_DEFINITION(VertexIndex, m_pEntityVIGroup)
        FUNCTION_DEFINITION(VertexNormal, m_pEntityVNGroup)
        FUNCTION_DEFINITION(VertexNormalIndex, m_pEntityVNIGroup)

#undef FUNCTION_DEFINITION

    protected:
        GraphicsScene* m_pScene = nullptr;

        GraphicsEntityGroup<Vertex>* m_pEntityVGroup = nullptr;
        GraphicsEntityGroup<VertexIndex>* m_pEntityVIGroup = nullptr;
        GraphicsEntityGroup<VertexNormal>* m_pEntityVNGroup = nullptr;
        GraphicsEntityGroup<VertexNormalIndex>* m_pEntityVNIGroup = nullptr;
    };

} // namespace FX

#endif // _GRAPHICS_DIVERTER_H_
