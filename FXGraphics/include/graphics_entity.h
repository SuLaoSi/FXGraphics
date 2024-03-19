#ifndef _GRAPHICS_ENTITY_H_
#define _GRAPHICS_ENTITY_H_

namespace FX {

    class Vertex;
    class VertexIndex;
    class VertexNormal;
    class VertexNormalIndex;

    template<class T>
    class GraphicsEntity {

    };

    class PolygonEdge : public GraphicsEntity<Vertex> {

    };

    class PolygonFace : public GraphicsEntity<VertexNormalIndex> {

    };

} // namespace FX

#endif // _GRAPHICS_ENTITY_H_
