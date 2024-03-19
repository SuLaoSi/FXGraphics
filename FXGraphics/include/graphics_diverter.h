#ifndef _GRAPHICS_DIVERTER_H_
#define _GRAPHICS_DIVERTER_H_

#include <set>

#include "graphics_entity.h"

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
            return add(pEntity);
        }

        template<class T>
        bool removeEntity(GraphicsEntity<T>* pEntity)
        {
            return remove(pEntity);
        }

    protected:

#define FUNCTION_DEFINITION(TYPE, TARGET)              \
        bool add(GraphicsEntity<TYPE>* pEntity)        \
        {                                              \
            return (TARGET.insert(pEntity)).second;    \
        }                                              \
        bool remove(GraphicsEntity<TYPE>* pEntity)     \
        {                                              \
            return TARGET.erase(pEntity) > 0;          \
        }

        FUNCTION_DEFINITION(Vertex, m_entityVList)
        FUNCTION_DEFINITION(VertexIndex, m_entityVIList)
        FUNCTION_DEFINITION(VertexNormal, m_entityVNList)
        FUNCTION_DEFINITION(VertexNormalIndex, m_entityVNIList)

#undef FUNCTION_DEFINITION

    protected:
        GraphicsScene* m_pScene = nullptr;

        std::set<GraphicsEntity<Vertex>*> m_entityVList;
        std::set<GraphicsEntity<VertexIndex>*> m_entityVIList;
        std::set<GraphicsEntity<VertexNormal>*> m_entityVNList;
        std::set<GraphicsEntity<VertexNormalIndex>*> m_entityVNIList;
    };

} // namespace FX

#endif // _GRAPHICS_DIVERTER_H_
