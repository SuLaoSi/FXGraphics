#ifndef _GRAPHICS_ENTITY_H_
#define _GRAPHICS_ENTITY_H_

#include <map>
#include <vector>

namespace FX {

    using EntityType = unsigned char;

    constexpr EntityType VertexTypeID = 0;
    constexpr EntityType VertexIndexTypeID = 1;
    constexpr EntityType VertexNormalTypeID = 2;
    constexpr EntityType VertexNormalIndexTypeID = 3;

    using DirtyType = unsigned int;

    constexpr DirtyType DataDirty = 1 << 0;
    constexpr DirtyType ColorDirty = 1 << 1;
    constexpr DirtyType MatrixDirty = 1 << 2;

    using EntityData = std::vector<float>;

    struct GroupPos {
        int first = -1;
        int second = -1;

        bool valid(void) const
        {
            return first >= 0 && second >= 0;
        }
    };

    class GraphicsScene;

    class GraphicsEntity {
    protected:
        GraphicsEntity(void) = default;
        virtual ~GraphicsEntity(void) = default;

        virtual EntityType type(void) const = 0;

        virtual void generate(void) = 0;

        const EntityData& data(void) const
        {
            return m_data;
        }

        unsigned int byteSize(void) const
        {
            return static_cast<unsigned int>(m_data.size());
        }

        GroupPos groupPos(const GraphicsScene* pScene)
        {
            return m_posMap[pScene];
        }

        void setGroupPos(const GraphicsScene* pScene, GroupPos pos)
        {
            m_posMap[pScene] = pos;
        }

    protected:
        std::map<const GraphicsScene*, GroupPos> m_posMap;
        EntityData m_data;
        DirtyType m_status = 0;
    };

    class PolygonEdge : public GraphicsEntity {
    public:
        PolygonEdge(void) = default;
        ~PolygonEdge(void) = default;

        EntityType type(void) const override
        {
            return VertexTypeID;
        }
    };

    class PolygonFace : public GraphicsEntity {
    public:
        PolygonFace(void) = default;
        ~PolygonFace(void) = default;

        EntityType type(void) const override
        {
            return VertexNormalIndexTypeID;
        }
    };

} // namespace FX

#endif // _GRAPHICS_ENTITY_H_
