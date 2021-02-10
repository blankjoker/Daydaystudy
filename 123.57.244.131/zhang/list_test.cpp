
#define  ne_doip_container_of(ptr, sample, member)                \
    (__typeof__(pos))((char *)((head)->next) - ((char *)&(pos)->member - (char *)(pos)))

#define  ne_doip_container_of(ptr, sample, member)                \
    (__typeof__(pos))((char *)(pos->member.next) - ((char *)&(pos)->member - (char *)(pos)))


#define ne_doip_list_for_each(pos, head, member)                \
    for (pos = 0, pos =  (__typeof__(pos))((char *)((head)->next) - ((char *)&(pos)->member - (char *)(pos)));
         &pos->member != (head);                    \
         pos =   (__typeof__(pos))((char *)(pos->member.next) - ((char *)&(pos)->member - (char *)(pos)))