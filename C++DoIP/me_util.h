
#ifndef ME_UTIL__
#define ME_UTIL__

#include <stdint.h>

/* GCC visibility */
#if defined(__GNUC__) && __GNUC__ >= 4
#define ME_EXPORT __attribute__ ((visibility("default")))
#else
#define ME_EXPORT
#endif

#define ARRAY_LENGTH(a) (sizeof (a) / sizeof (a)[0])

#ifdef __GNUC__
#define  me_container_of(ptr, sample, member)                \
    (__typeof__(sample))((char *)(ptr)    -            \
         ((char *)&(sample)->member - (char *)(sample)))
#else
#define  me_container_of(ptr, sample, member)                \
    (void *)((char *)(ptr)    -                        \
         ((char *)&(sample)->member - (char *)(sample)))
#endif

#define me_list_for_each(pos, head, member)                \
    for (pos = 0, pos =  me_container_of((head)->next, pos, member);    \
         &pos->member != (head);                    \
         pos =  me_container_of(pos->member.next, pos, member))

#define me_list_for_each_safe(pos, tmp, head, member)            \
    for (pos = 0, tmp = 0,                         \
         pos =  me_container_of((head)->next, pos, member),        \
         tmp =  me_container_of((pos)->member.next, tmp, member);    \
         &pos->member != (head);                    \
         pos = tmp,                            \
         tmp =  me_container_of(pos->member.next, tmp, member))

#define me_list_for_each_reverse(pos, head, member)            \
    for (pos = 0, pos =  me_container_of((head)->prev, pos, member);    \
         &pos->member != (head);                    \
         pos =  me_container_of(pos->member.prev, pos, member))

#define me_list_for_each_reverse_safe(pos, tmp, head, member)        \
    for (pos = 0, tmp = 0,                         \
         pos =  me_container_of((head)->prev, pos, member),    \
         tmp =  me_container_of((pos)->member.prev, tmp, member);    \
         &pos->member != (head);                    \
         pos = tmp,                            \
         tmp =  me_container_of(pos->member.prev, tmp, member))

namespace nutshell {

    class Me_Util;
}

struct me_list {

    struct me_list *prev;
    struct me_list *next;
};
typedef struct me_list me_list_t;
typedef int (*compare)(void *, void *);

class Me_Util
{
private:
    /* data */
    static Me_Util* m_instance;
public:
    Me_Util();
    virtual ~Me_Util();

    Me_Util(const Me_Util& other);
    Me_Util& operator=(const Me_Util& other);

    void me_list_init(me_list_t *list);
    void me_list_insert(me_list_t *list, me_list_t *elm);
    void me_list_remove(me_list_t *elm);
    uint8_t me_list_length(const me_list_t *list);
    int me_list_empty(const me_list_t *list);
    void me_list_insert_list(me_list_t *list, me_list_t *other);

    static Me_Util* instance();

};


#endif // ME_THREAD__
/* EOF */