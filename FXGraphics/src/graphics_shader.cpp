#include "graphics_shader.h"

#include <fstream>
#include <sstream>
#include "glad.h"

#include "basic_log.h"
#include "graphics_scene.h"

namespace FX {

    GraphicsShader::GraphicsShader(Type shaderType)
        : GraphicsBufferObject(GraphicsBufferObject::Type::kShader), m_type(shaderType)
    {
    }

    GraphicsShader::GraphicsShader(const std::string& filePath, Type shaderType)
        : GraphicsBufferObject(GraphicsBufferObject::Type::kShader), m_type(shaderType)
    {
        std::ifstream in(filePath.c_str(), std::ios::in);

        if (in.is_open())
        {
            std::stringstream ss;
            ss << in.rdbuf();
            m_shaderSource.assign(ss.str());
        }
        else
        {
            BasicLog::out(BasicLog::kWarn, "Cannot open file \n\t\t", filePath.c_str(), "\n\t\tas shader.");
        }
    }

    GraphicsShader::~GraphicsShader()
    {
        for (auto pScene : m_sceneList)
        {
            if (pScene == nullptr)
            {
                continue;
            }

            pScene->removeShader(*this);
        }
    }

    void GraphicsShader::setSource(const std::string& shaderSource)
    {
        m_shaderSource = shaderSource;
        setDirty();
    }

    unsigned int GraphicsShader::create() const
    {
        auto handle = glCreateShader(static_cast<unsigned int>(m_type));

        if (handle == 0)
        {
            BasicLog::out(BasicLog::kWarn, "Failed to create opengl shader.");
        }

        return handle;
    }

    void GraphicsShader::addScene(GraphicsScene& scene)
    {
        m_sceneList.insert(&scene);
    }

    void GraphicsShader::removeScene(GraphicsScene& scene)
    {
        m_sceneList.erase(&scene);
    }

    void GraphicsShader::update(unsigned int handle) const
    {
        auto source = m_shaderSource.c_str();
        glShaderSource(handle, 1, &source, 0);
        glCompileShader(handle);

        int success = 0;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
        if (success == 0)
        {
            BasicLog::out(BasicLog::kWarn, "Failed to compile shader.");
        }
    }

} // namespace FX
