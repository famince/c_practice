#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <stdint.h>
#include <inttypes.h>
#include <cstring>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
//typedef unsigned long uint32_t;
//typedef unsigned long long uint64_t;



#define GUESS_OUI_FILE "./wanwoo_guess.oui"

#define VENDOR_NAME_LEN 32
#define MAX_GUESS_PORT 39

#define PORT_SEARCH_FULL 0
#define PORT_SEARCH_PART 1

#define PORT_PARTS_MATCH_FOR_IDENTIFY 5

#define WRITE_ONCE(a, b) (a = b)

struct list_head {
    struct list_head *next, *prev;
};

struct list_head guess_vendor_list;

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

static inline void __list_add(struct list_head *new_node, struct list_head *prev, struct list_head *next)
{       
    next->prev = new_node;
    new_node->next = next;
    new_node->prev = prev;
    WRITE_ONCE(prev->next, new_node);
}

static inline void list_add_tail(struct list_head *new_node, struct list_head *head)
{
    __list_add(new_node, head->prev, head);
}

struct guess_vendor_entry
{
    struct list_head list;
    char identify_vendor[VENDOR_NAME_LEN];
    char mac_vendor[VENDOR_NAME_LEN];
    uint16_t port_search_type;
    uint16_t port_list[MAX_GUESS_PORT];
    uint32_t identify_code;
    uint32_t as_type;
    char guess_vendor[VENDOR_NAME_LEN];
    char guess_type[VENDOR_NAME_LEN];
    uint32_t status_code;
};

static int parse_guess_line(char *line)
{
    //printf("enter %s...\n", __FUNCTION__);
    struct guess_vendor_entry *entry;
    char port_list[256];

    if (line == NULL)
    {
        printf("out %s... null\n", __FUNCTION__);
        return -1;
    }

    if (line[0] == '#')
    {
        return -1;
    }

    if (strlen(line) < 8)
    {
        printf("out %s... 8\n", __FUNCTION__);
        return -1;
    }

    entry = (struct guess_vendor_entry *)malloc(sizeof(*entry));
    if (entry == NULL)
    {
        printf("%s: can't malloc memory for guest vendor list", __FUNCTION__);
        return -1;
    }
    memset((void *)entry, 0, sizeof(*entry));
    memset((void *)&port_list, 0, sizeof(port_list));

    if (sscanf(line, "\"%31[^\"]\" \"%31[^\"]\" [%255[^]]] %u %u \"%31[^\"]\" \"%31[^\"]\" %u%*[^ \t#\r\n]",
               entry->identify_vendor, entry->mac_vendor, port_list, &entry->identify_code, &entry->as_type,
               entry->guess_vendor, entry->guess_type, &entry->status_code) == 8)
    {
        entry->port_search_type = PORT_SEARCH_FULL;
    }
    else if (sscanf(line, "\"%31[^\"]\" \"%31[^\"]\" {%255[^}]} %u %u \"%31[^\"]\" \"%31[^\"]\" %u%*[^ \t#\r\n]",
                entry->identify_vendor, entry->mac_vendor, port_list, &entry->identify_code, &entry->as_type,
                entry->guess_vendor, entry->guess_type, &entry->status_code) == 8)
    {
        entry->port_search_type = PORT_SEARCH_PART;
    }
    else
    {
        printf("%s: can't parse [%s] for guess", __FUNCTION__, line);
        free(entry);
        return -1;
    }

    char *p;
    char *strtok_data;
    int i = 0;

    p = strtok_r(port_list, ",", &strtok_data);
    while (p)
    {
        entry->port_list[i] = atoi(p);
        p = strtok_r(NULL, ",", &strtok_data);
        i++;
        if (i >= MAX_GUESS_PORT)
        {
            break;
        }
    }
    list_add_tail(&(entry->list), &guess_vendor_list);

    //printf("out %s...\n", __FUNCTION__);
    return 0;
}

void init_guess_vendor_table(void)
{
    FILE *fp = fopen(GUESS_OUI_FILE, "r");
    char buf[256];
    if (fp == NULL)
    {    
        printf("%s: Can't open %s for guess vendor table",
                 __FUNCTION__, GUESS_OUI_FILE);
        return;
    }    
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {    
        parse_guess_line(buf);
    }    
    fclose(fp);
}

int main()
{
    INIT_LIST_HEAD(&guess_vendor_list);
    init_guess_vendor_table();
}
