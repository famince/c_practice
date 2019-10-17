#include<stdio.h>
typedef struct _test 
{ 
    char i; 
    int j; 
    char k; 
}Test; 

struct rb_node {
    unsigned long  __rb_parent_color;
    struct rb_node *rb_right;
    struct rb_node *rb_left;
};  

struct rb_root {                                                                                                                                             struct rb_node *rb_node;
};

typedef struct asset {
    //struct hlist_node asset_node;
    uint32_t device_ip;
    uint16_t reported;
    uint16_t info_index;
    uint8_t cur_discovery_state;
    uint32_t group_id;
    long discovery_timestamp;

    volatile long last_refresh_timestamp;
    struct rb_root *discovery_root;
    struct rb_node discovery_node;
    uint32_t discovery_times;
}asset;

#ifndef container_of
#define container_of(ptr, type, member)    __extension__ ({        \
        const typeof(((type *)0)->member) *_ptr = (ptr); \
        __attribute__((unused)) type *_target_ptr = (type *)(ptr);  \
        (type *)(((uintptr_t)_ptr) - offsetof(type, member)); \
        })
#endif
#define    rb_entry(ptr, type, member) container_of(ptr, type, member)

int main() 
{ 
    Test *p = 0; 
    printf("%p \n", &(p->i)); 
    printf("%p \n", &(p->j)); 
    printf("%p \n", &(p->k)); 

    entry = 
    info = rb_entry(entry, struct asset, discovery_node);
} 
