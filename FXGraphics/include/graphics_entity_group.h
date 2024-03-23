#ifndef _GRAPHICS_ENTITY_GROUP_H_
#define _GRAPHICS_ENTITY_GROUP_H_

#include <vector>

#include "graphics_entity.h"
#include "graphics_buffer.h"

namespace FX {

    class GraphicsScene;

    template<class T>
    class GraphicsEntityGroup {
    protected:
        friend class GraphicsScene;

        GraphicsEntityGroup(GraphicsScene* pScene) : m_pScene(pScene) {}
        virtual GraphicsEntityGroup(void) = default;

        struct EntityList {
            std::vector<GraphicsEntity<T>*> entityList;
            unsigned int byteSize = 0;
        };

    public:
        bool addEntity(GraphicsEntity<T>* pEntity)
        {
            if (pEntity->groupPos(m_pScene).valid())
            {
                return false;
            }

            if (pEntity->byteSize() == 0)
            {
                // TODO
            }

            auto first = availableList(pEntity->byteSize());
            m_entityGroup[first].entityList.push_back(pEntity);
            auto second = static_cast<unsigned int>(m_entityGroup[first].entityList.size() - 1);


        }

        bool removeEntity(GraphicsEntity<T>* pEntity)
        {

        }

        virtual void ensure(void)
        {

        }

    protected:
        unsigned int availableList(unsigned int size)
        {
            if (m_entityGroup.empty() || m_entityGroup.back().byteSize + size > 1e7)
            {
                m_entityGroup.emplace_back(EntityList());
            }
            return static_cast<unsigned int>(m_entityGroup.size() - 1);
        }

    protected:
        GraphicsScene* m_pScene = nullptr;
        std::vector<EntityList> m_entityGroup;
    };


} // namespace FX

#endif // _GRAPHICS_ENTITY_GROUP_H_
