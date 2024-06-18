#ifndef VEC_H
#define VEC_H

#endif // VEC_H

#define Vec(T)            \
    struct                \
    {                     \
        T *data;          \
        unsigned int cap; \
        unsigned int len; \
    }

#define Vec_as_ptr(self) \
    ((self)->data)

#define Vec_len(self) \
    ((self)->len)

#define __capacity(self) \
    ((self)->cap)

#define Vec_new() \
    {NULL, 0, 0}

#define Vec_with_capacity(T, num) \
    {malloc(sizeof(T) * num), num, 0}

#define Vec_is_empty(self) \
    (Vec_len(self) == 0)

#define __grow(self)                                                                                \
    do                                                                                              \
    {                                                                                               \
        __capacity(self) <<= 1;                                                                     \
        if (__capacity(self) < 8)                                                                   \
        {                                                                                           \
            __capacity(self) = 8;                                                                   \
        }                                                                                           \
        Vec_as_ptr(self) = realloc(Vec_as_ptr(self), sizeof(*Vec_as_ptr(self)) * __capacity(self)); \
    } while (0)

#define Vec_push(self, item)                      \
    do                                            \
    {                                             \
        if (Vec_len(self) == __capacity(self))    \
        {                                         \
            __grow(self);                         \
        }                                         \
        Vec_as_ptr(self)[Vec_len(self)++] = item; \
    } while (0)

#define Vec_insert(self, index, item)                          \
    do                                                         \
    {                                                          \
        if (index < Vec_len(self) || index >= 0)               \
        {                                                      \
            if (Vec_len(self) == __capacity(self))             \
            {                                                  \
                __grow(self);                                  \
            }                                                  \
            for (int i = Vec_len(self) - 1; i >= index; i--)   \
            {                                                  \
                Vec_as_ptr(self)[i + 1] = Vec_as_ptr(self)[i]; \
            }                                                  \
            Vec_as_ptr(self)[index] = item;                    \
            Vec_len(self)++;                                   \
        }                                                      \
    } while (0)

#define Vec_remove(self, index)                                \
    do                                                         \
    {                                                          \
        if (index < Vec_len(self) || index >= 0)               \
        {                                                      \
            for (int i = index; i < Vec_len(self) - 1; i++)    \
            {                                                  \
                Vec_as_ptr(self)[i] = Vec_as_ptr(self)[i + 1]; \
            }                                                  \
            Vec_len(self)--;                                   \
        }                                                      \
    } while (0)

#define Vec_sort(self, comp)                                                     \
    do                                                                           \
    {                                                                            \
        qsort(Vec_as_ptr(self), Vec_len(self), sizeof(*Vec_as_ptr(self)), comp); \
    } while (0)

#define Vec_get(self, index, or) \
    (index >= 0 && index < Vec_len(self) ? Vec_as_ptr(self)[index] : (or))

#define Vec_foreach(self, func)                 \
    do                                          \
    {                                           \
        for (int i = 0; i < Vec_len(self); i++) \
        {                                       \
            func(&Vec_as_ptr(self)[i]);         \
        }                                       \
    } while (0)

#define Vec_clear(self)          \
    do                           \
    {                            \
        free(Vec_as_ptr(self));  \
        Vec_as_ptr(self) = NULL; \
        Vec_len(self) = 0;       \
        __capacity(self) = 0;    \
    } while (0)

#define Vec_first(self) \
    (&Vec_as_ptr(self)[0])

#define Vec_last(self) \
    (&Vec_as_ptr(self)[Vec_len(self) - 1])

#define __swap(a, b)            \
    do                          \
    {                           \
        a ^= b, b ^= a, a ^= b; \
    } while (0)

#define Vec_reverse(self)                                                                     \
    do                                                                                        \
    {                                                                                         \
        int half_len = Vec_len(self) / 2;                                                     \
        int i = 0;                                                                            \
        while (i < half_len)                                                                  \
        {                                                                                     \
            __swap(Vec_as_ptr(self)[i], (&Vec_as_ptr(self)[half_len + 1])[half_len - 1 - i]); \
            i++;                                                                              \
        }                                                                                     \
    } while (0)
