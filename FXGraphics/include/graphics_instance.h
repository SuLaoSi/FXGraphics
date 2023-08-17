#ifndef _GRAPHICS_INSTANCE_H_
#define _GRAPHICS_INSTANCE_H_

namespace FX {

    class GraphicsInstance {
    private:
        GraphicsInstance(void);
        ~GraphicsInstance(void);

        static GraphicsInstance s_instance;
    };

} // namespace FX

#endif // _GRAPHICS_INSTANCE_H_
