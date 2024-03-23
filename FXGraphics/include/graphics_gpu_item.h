#ifndef _GRAPHICS_GPU_ITEM_H_
#define _GRAPHICS_GPU_ITEM_H_

#include <map>

#include "basic_macro.h"
#include "graphics_instance.h"

namespace FX {

    enum class GPUItemType : unsigned int {
        kVBO = 0x8892,
        kEBO = 0x8893,
        kSSBO = 0x90D2,
        kDIBO = 0x8F3F
    };

    class GraphicsWindow;
    class ItemInfo;

    class GraphicsGPUItem {
    protected:
        friend class GraphicsWindow;

        explicit GraphicsGPUItem(GPUItemType type);
        virtual ~GraphicsGPUItem(void);

        DELETE_COPY_AND_MOVE_CONSTRUCT(GraphicsGPUItem);

        virtual ItemInfo* create(void) const = 0;

        ItemInfo* getOrCreate(void);

        void clearItem(GraphicsWindow* pWindow);

    protected:
        const GPUItemType m_type = GPUItemType(0);
        std::map<GraphicsWindow*, ItemInfo*> m_itemList;
    };


    class ItemInfo {
    protected:
        friend class GraphicsGPUItem;
        friend class GraphicsWindow;

        explicit ItemInfo(GPUItemType type);
        virtual ~ItemInfo(void) = default;

        DELETE_COPY_AND_MOVE_CONSTRUCT(ItemInfo);

    public:
        const GPUItemType m_type = GPUItemType(0);
        unsigned int m_handle = 0;
    };

} // namespace FX

#endif // _GRAPHICS_GPU_ITEM_H_
