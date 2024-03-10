#ifndef _GRAPHICS_BUFFER_H_
#define _GRAPHICS_BUFFER_H_

#include "graphics_gpu_item.h"

namespace FX {

    enum class StorageHint : unsigned int {
        kStatic = 0x88E4,
        kDynamic = 0x88E8,
        kStream = 0x88E0,
    };

    class GraphicsBuffer : public GraphicsGPUItem {
    public:
        GraphicsBuffer(GPUItemType type, StorageHint hint = StorageHint::kStatic);

        void bind(void);
        void unbind(void);

    protected:
        const StorageHint m_hint = StorageHint::kStatic;
    };


    class BufferInfo : public ItemInfo {
    protected:
        friend class GraphicsBuffer;

        BufferInfo(GPUItemType type, StorageHint hint = StorageHint::kStatic);

        void bind(void);
        void unbind(void);
        void setData(unsigned int size, const void* pData) const;
        void setData(unsigned int start, unsigned int size, const void* pData) const;
        void* mapBuffer(void) const;
        void* mapBuffer(unsigned int start, unsigned int size) const;
        void unMapBuffer(void) const;

    protected:
        const StorageHint m_hint = StorageHint::kStatic;
    };

} // namespace FX

#endif // _GRAPHICS_BUFFER_H_
