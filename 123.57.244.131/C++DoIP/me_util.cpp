
#include "me_util.h"
#include <stdio.h>

Me_Util* Me_Util::m_instance = NULL;
Me_Util* Me_Util::instance()
{
    if (m_instance == NULL) {
        m_instance = new Me_Util();
    }
    return m_instance;
}

Me_Util::Me_Util()
{

}

Me_Util::~Me_Util()
{
    delete m_instance;
}


void Me_Util::me_list_init(me_list_t *list)
{
    list->prev = list;
    list->next = list;
}

void Me_Util::me_list_insert(me_list_t *list, me_list_t *elm)
{
    elm->prev = list;
    elm->next = list->next;
    list->next = elm;
    elm->next->prev = elm;
}

void Me_Util::me_list_remove(me_list_t *elm)
{
    elm->prev->next = elm->next;
    elm->next->prev = elm->prev;
    elm->next = NULL;
    elm->prev = NULL;
}

uint8_t Me_Util::me_list_length(const me_list_t *list)
{
    me_list_t *e = NULL;
    int count;

    count = 0;
    e = list->next;
    while (e != list) {
        e = e->next;
        count++;
    }

    return count;
}

int Me_Util::me_list_empty(const me_list_t *list)
{
    return list->next == list;
}

void Me_Util::me_list_insert_list(me_list_t *list, me_list_t *other)
{
    if (me_list_empty(other)) {
        return;
    }

    other->next->prev = list;
    other->prev->next = list->next;
    list->next->prev = other->prev;
    list->next = other->next;
}
