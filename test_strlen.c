#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

#define list_for_each(pos, head) for (pos = (head)->next; pos != (head); pos = pos->next)

struct list_head {
    struct list_head *next, *prev;
};

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

typedef struct COUNTERFEI_ASSETS
{
    char m_mac[18];
    int m_as_type;
    char m_brand[64];
    char m_name[64];
    char m_model[64];
    struct list_head tcp_port_list;
    struct list_head udp_port_list;
}COUNTERFEI_ASSETS;

static inline uint32_t list_count(struct list_head *head)
{
    uint32_t count = 0;
    struct list_head *pos;
    list_for_each(pos, head) {
        count++;
    }
    return count;
}

int main(void)
{
    ios::sync_with_stdio(false);
    char s[100] = "  ";
    cout << sizeof(s) << endl;
    cout << s << "has" << strlen(s) << "character(s)." << endl; 
    //printf("%s has %d character(s).",s,strlen(s));
    //putchar();

    COUNTERFEI_ASSETS info;
    memset(&info, 0x00, sizeof(COUNTERFEI_ASSETS));
    INIT_LIST_HEAD(&info.tcp_port_list);
    INIT_LIST_HEAD(&info.udp_port_list);

    if (list_count(&(info.tcp_port_list)) <= 0)
    {
        cout << "tcp_port_list is null" << endl;
    }
    else
    {
        cout << list_count(&info.tcp_port_list) << endl;
    }
    return 0;
}
