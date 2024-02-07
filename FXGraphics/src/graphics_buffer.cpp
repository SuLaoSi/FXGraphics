#include "graphics_buffer.h"

#include "basic_log.h"
#include "graphics_window.h"

namespace FX {

    GraphicsBuffer::GraphicsBuffer(GPUItemType type, StorageHint hint) : GraphicsGPUItem(type), m_hint(hint)
    {
    }

    void GraphicsBuffer::bind()
    {
        auto pItem = static_cast<BufferInfo*>(getOrCreate());
        pItem->bind();
    }

    void GraphicsBuffer::unbind()
    {
        auto pItem = static_cast<BufferInfo*>(getOrCreate());
        pItem->unbind();
    }

    BufferInfo::BufferInfo(GPUItemType type, StorageHint hint) : ItemInfo(type), m_hint(hint)
    {
    }

    void BufferInfo::bind()
    {
        glBindBuffer((GLenum)m_type, m_handle);
    }

    void BufferInfo::unbind()
    {
        glBindBuffer((GLenum)m_type, 0);
    }

    void BufferInfo::setData(unsigned int size, const void* pData) const
    {
        glBufferData((GLenum)m_type, size, pData, (GLenum)m_hint);
    }

    void BufferInfo::setData(unsigned int start, unsigned int size, const void* pData) const
    {
        glBufferSubData((GLenum)m_type, start, size, pData);
    }

    void* BufferInfo::mapBuffer() const
    {
        return glMapBuffer((GLenum)m_type, GL_WRITE_ONLY);
    }

    void* BufferInfo::mapBuffer(unsigned int start, unsigned int size) const
    {
        return glMapBufferRange((GLenum)m_type, start, size, GL_WRITE_ONLY);
    }

    void BufferInfo::unMapBuffer() const
    {
        glUnmapBuffer((GLenum)m_type);
    }

} // namespace FX
