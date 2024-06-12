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

#define Vec_new() \
    {NULL, 0, 0}

#define Vec_grow(self)                                                               \
    do                                                                               \
    {                                                                                \
        (self)->cap <<= 1;                                                           \
        if ((self)->cap < 8)                                                         \
        {                                                                            \
            (self)->cap = 8;                                                         \
        }                                                                            \
        (self)->data = realloc((self)->data, sizeof(*((self)->data)) * (self)->cap); \
    } while (0)

#define Vec_push(self, item)                \
    do                                      \
    {                                       \
        if ((self)->len == (self)->cap)     \
        {                                   \
            Vec_grow(self);                 \
        }                                   \
        (self)->data[(self)->len++] = item; \
    } while (0)

#define Vec_insert(self, index, item)                      \
    do                                                     \
    {                                                      \
        if (index < (self)->len || index >= 0)             \
        {                                                  \
            if ((self)->len == (self)->cap)                \
            {                                              \
                Vec_grow(self);                            \
            }                                              \
            for (int i = (self)->len - 1; i >= index; i--) \
            {                                              \
                (self)->data[i + 1] = (self)->data[i];     \
            }                                              \
            (self)->data[index] = item;                    \
            (self)->len++;                                 \
        }                                                  \
    } while (0)

#define Vec_remove(self, index)                           \
    do                                                    \
    {                                                     \
        if (index < (self)->len || index >= 0)            \
        {                                                 \
            for (int i = index; i < (self)->len - 1; i++) \
            {                                             \
                (self)->data[i] = (self)->data[i + 1];    \
            }                                             \
            (self)->len--;                                \
        }                                                 \
    } while (0)

#define Vec_sort(self, comp)                                             \
    do                                                                   \
    {                                                                    \
        qsort((self)->data, (self)->len, sizeof(*((self)->data)), comp); \
    } while (0);

#define Vec_get(self, index, or) \
    index >= 0 && index < (self)->len ? (self)->data[index] : (or)

#define Vec_foreach(self, func)               \
    do                                        \
    {                                         \
        for (int i = 0; i < (self)->len; i++) \
        {                                     \
            func(&(self)->data[i]);           \
        }                                     \
    } while (0)

#define Vec_drop(self)       \
    do                       \
    {                        \
        free((self)->data);  \
        (self)->data = NULL; \
        (self)->len = 0;     \
        (self)->cap = 0;     \
    } while (0)
