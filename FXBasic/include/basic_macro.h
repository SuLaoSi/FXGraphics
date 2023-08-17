#ifndef _BASIC_MACRO_H_
#define _BASIC_MACRO_H_

namespace FX {

#define DELETE_COPY_CONSTRUCT(Class)                \
    Class(const Class&) = delete;                   \
    Class& operator=(const Class&) = delete

#define DELETE_MOVE_CONSTRUCT(Class)                \
    Class(Class&&) = delete;                        \
    Class& operator=(Class&&) = delete

#define DELETE_COPY_AND_MOVE_CONSTRUCT(Class)       \
    DELETE_COPY_CONSTRUCT(Class);                   \
    DELETE_MOVE_CONSTRUCT(Class)

} // namespace FX

#endif // _BASIC_MACRO_H_
