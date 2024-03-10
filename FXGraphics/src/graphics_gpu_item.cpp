#include "graphics_gpu_item.h"

#include "basic_log.h"
#include "graphics_window.h"

namespace FX {

    GraphicsGPUItem::GraphicsGPUItem(GPUItemType type) : m_type(type)
    {
    }

    GraphicsGPUItem::~GraphicsGPUItem()
    {
        for (auto&& pair : m_itemList)
        {
            pair.first->addToDelete(pair.second);
            pair.first->removeItem(this);
        }
    }

    ItemInfo* GraphicsGPUItem::getOrCreate()
    {
        auto pWindow = GraphicsWindow::currentWindow();
        if (pWindow == nullptr)
        {
            BasicLog::out(BasicLog::kWarn, "No window is used, cannot get the gpu item.");
            return nullptr;
        }

        auto itr = m_itemList.find(pWindow);
        if (itr != m_itemList.end())
        {
            return itr->second;
        }
        else
        {
            auto pNewItem = create();
            if (pNewItem == nullptr)
            {
                BasicLog::out(BasicLog::kError, "NULL POINTER!");
                return nullptr;
            }

            pWindow->addItem(this);
            auto res = m_itemList.insert({ pWindow, pNewItem });
            return res.first->second;
        }
    }

    void GraphicsGPUItem::clearItem(GraphicsWindow* pWindow)
    {
        if (pWindow == nullptr)
        {
            BasicLog::out(BasicLog::kError, "NULL POINTER!");
            return;
        }

        auto itr = m_itemList.find(pWindow);
        if (itr != m_itemList.end())
        {
            m_itemList.erase(itr);
        }
        else
        {
            BasicLog::out(BasicLog::kWarn, "Incorrect record between gpu item and window.");
        }
    }

    ItemInfo::ItemInfo(GPUItemType type) : m_type(type)
    {
    }

} // namespace FX
