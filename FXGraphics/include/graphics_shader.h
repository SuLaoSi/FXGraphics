#ifndef _GRAPHICS_SHADER_H_
#define _GRAPHICS_SHADER_H_

#include <string>
#include <set>

#include "graphics_buffer_object.h"

namespace FX {

    class GraphicsScene;

    class GraphicsShader : public GraphicsBufferObject {
    public:
        friend class GraphicsScene;

        enum class Type : unsigned int {
            kVertex = 0x8B31,
            kFragment = 0x8B30,
            kGeometry = 0x8DD9,
            kCompute = 0x91B9
        };

        explicit GraphicsShader(Type shaderType);
        GraphicsShader(const std::string& filePath, Type shaderType);
        virtual ~GraphicsShader(void);

        void setSource(const std::string& shaderSource);

    protected:
        unsigned int create(void) const override;

    private:
        void addScene(GraphicsScene& scene);
        void removeScene(GraphicsScene& scene);
        void update(unsigned int handle) const;

    protected:
        std::string m_shaderSource;
        std::set<GraphicsScene*> m_sceneList;
        Type m_type = Type(0);
    };

} // namespace FX

#endif // _GRAPHICS_SHADER_H_
