#include "graphics_buffer_object.h"

#include "basic_log.h"
#include "graphics_window.h"

namespace FX {

    GraphicsBufferObject::GraphicsBufferObject(Type type) : m_type(type) {}

    GraphicsBufferObject::~GraphicsBufferObject()
    {
        for (auto&& itr : m_bufferList)
        {
            if (itr.first == nullptr)
            {
                continue;
            }

            itr.first->removeBuffer(*this);
            itr.first->addRecycledBuffer({ m_type, itr.second.handle });
        }
    }

    void GraphicsBufferObject::setDirty(bool isDirty)
    {
        for (auto&& itr : m_bufferList)
        {
            itr.second.isDirty = isDirty;
        }
    }

    GraphicsBufferObject::BufferInfo GraphicsBufferObject::getOrCreate()
    {
        if (GraphicsWindow::s_pCurrentWindow == nullptr)
        {
            BasicLog::out(BasicLog::kWarn, "No window is used, cannot get buffer object.");
            return GraphicsBufferObject::BufferInfo();
        }

        auto itr = m_bufferList.lower_bound(GraphicsWindow::s_pCurrentWindow);
        if (itr != m_bufferList.end() && (*itr).first == GraphicsWindow::s_pCurrentWindow)
        {
            return (*itr).second;
        }
        else
        {
            auto handle = create();
            m_bufferList.insert(itr, { GraphicsWindow::s_pCurrentWindow, { handle, true } });
            GraphicsWindow::s_pCurrentWindow->addBuffer(*this);
            return { handle, true };
        }
    }

    void GraphicsBufferObject::setReady()
    {
        if (GraphicsWindow::s_pCurrentWindow == nullptr)
        {
            BasicLog::out(BasicLog::kWarn, "No window is used, cannot set buffer as ready.");
            return;
        }

        auto itr = m_bufferList.find(GraphicsWindow::s_pCurrentWindow);
        if (itr != m_bufferList.end())
        {
            (*itr).second.isDirty = false;
        }
        else
        {
            BasicLog::out(BasicLog::kWarn, "Cannot set ready, you need to create first.");
        }
    }

    void GraphicsBufferObject::notifyRemove()
    {
        if (GraphicsWindow::s_pCurrentWindow == nullptr)
        {
            BasicLog::out(BasicLog::kWarn, "No window is used, cannot remove buffer object.");
            return;
        }

        m_bufferList.erase(GraphicsWindow::s_pCurrentWindow);
    }

} // namespace FX
