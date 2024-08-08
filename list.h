#ifndef LIST_H
#define LIST_H

#define LinkedList(T)          \
    struct {                   \
        struct Node {          \
            T data;            \
            struct Node *next; \
        } *head;               \
        size_t len;            \
        struct Node *_curr;    \
        struct Node *_node;    \
    }

#define LL_head(self) ((self)->head)
#define LL_len(self) ((self)->len)
#define _ll_curr(self) ((self)->_curr)
#define _ll_node(self) ((self)->_node)

#define LL_new() {NULL, 0, NULL, NULL}

#define LL_push_back(self, value)                                   \
    do {                                                            \
        if (LL_head(self) != NULL) {                                \
            _ll_curr(self) = LL_head(self);                         \
            while (_ll_curr(self)->next != NULL) {                  \
                _ll_curr(self) = _ll_curr(self)->next;              \
            }                                                       \
            _ll_curr(self)->next = malloc(sizeof(*_ll_curr(self))); \
            _ll_curr(self)->next->data = value;                     \
            _ll_curr(self)->next->next = NULL;                      \
        } else {                                                    \
            LL_head(self) = malloc(sizeof(*_ll_curr(self)));        \
            LL_head(self)->data = value;                            \
            LL_head(self)->next = NULL;                             \
        }                                                           \
        LL_len(self)++;                                             \
    } while (0)

#define LL_push_front(self, value)                            \
    do {                                                      \
        if (LL_head(self) != NULL) {                          \
            _ll_curr(self) = malloc(sizeof(*_ll_curr(self))); \
            _ll_curr(self)->data = value;                     \
            _ll_curr(self)->next = LL_head(self);             \
            LL_head(self) = _ll_curr(self);                   \
        } else {                                              \
            LL_head(self) = malloc(sizeof(*_ll_curr(self)));  \
            LL_head(self)->data = value;                      \
            LL_head(self)->next = NULL;                       \
        }                                                     \
        LL_len(self)++;                                       \
    } while (0)

#define LL_foreach(self, func)                     \
    do {                                           \
        _ll_curr(self) = LL_head(self);            \
        while (_ll_curr(self)) {                   \
            func(&_ll_curr(self)->data);           \
            _ll_curr(self) = _ll_curr(self)->next; \
        }                                          \
    } while (0)

#define LL_reverse(self)                           \
    do {                                           \
        _ll_curr(self) = LL_head(self);            \
        LL_head(self) = NULL;                      \
        while (_ll_curr(self)) {                   \
            _ll_node(self) = _ll_curr(self);       \
            _ll_curr(self) = _ll_node(self)->next; \
            _ll_node(self)->next = LL_head(self);  \
            LL_head(self) = _ll_node(self);        \
        }                                          \
    } while (0)

#define LL_clear(self)                             \
    do {                                           \
        _ll_curr(self) = LL_head(self);            \
        while (_ll_curr(self)) {                   \
            void *curr = _ll_curr(self);           \
            _ll_curr(self) = _ll_curr(self)->next; \
            free(curr);                            \
        }                                          \
        LL_len(self) = 0;                          \
    } while (0)

#endif
