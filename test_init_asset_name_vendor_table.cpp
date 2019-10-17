#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <cstring>
#include <stdlib.h>
using namespace std;

#define HUAWEI_ASSET_INFO_FILE    "wanwoo_huawei_asset_info.oui"
#define HIKVISION_ASSET_INFO_FILE "wanwoo_hikvision_asset_info.oui"
#define KEDACOM_ASSET_INFO_FILE   "wanwoo_kedacom_asset_info.oui"
#define UNIVIEW_ASSET_INFO_FILE   "wanwoo_uniview_asset_info.oui"
#define DAHUA_ASSET_INFO_FILE     "wanwoo_DAHUA_asset_info.oui"

#define WRITE_ONCE(a, b) (a = b)

struct list_head {
    struct list_head *next, *prev;
};

struct list_head asset_name_vendor_list;

struct asset_name_vendor_entry
{
    struct list_head list;
    char name[64];        // 资产名字
    uint32_t as_type;     // 资产类型
    char vendor[64];      // 厂商
};

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next =  list;
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

static int parse_asset_name_type_line(char *line, const char *vendor)
{
    struct asset_name_vendor_entry *entry;
    
    if (line == NULL || line[0] == '#' || strlen(line) < 2)
    {
        return -1;
    }
    
    entry = (struct asset_name_vendor_entry *)malloc(sizeof(*entry));
    if (entry == NULL)
    {
        printf("%s: can't malloc memory for asset_name_vendor_entry !", __FUNCTION__);
        return -1;
    }
    
    memset((void *)entry, 0, sizeof(*entry));
    
    strcpy(entry->vendor, vendor);
    int sscanf_ret = sscanf(line, "\"%63[^\"]\" %u%*[^ \t\r\n]", entry->name, &entry->as_type);
    printf("sscanf_ret = %d\n", sscanf_ret);
    if ( 2 != sscanf_ret)
    {
        printf("%s: parse failed name: [%s], type: [%u] !\n", __FUNCTION__, entry->name, entry->as_type);
        free(entry);
        return -1;
    }

    list_add_tail(&(entry->list), &asset_name_vendor_list);
    printf("%s: get asset_name=\"%s\",as_type=%d, asset_vendor=\"%s\"", __FUNCTION__, entry->name, entry->as_type, entry->vendor);
    
    return 0;
}

void init_asset_name_table(void)
{
    std::map<const char*, const char*> mapVendor;
    mapVendor["HIKVISION"] = HIKVISION_ASSET_INFO_FILE;
    mapVendor["HUAWEI"]    = HUAWEI_ASSET_INFO_FILE;
    mapVendor["KEDACOM"]   = KEDACOM_ASSET_INFO_FILE;
    mapVendor["UNIVIEW"]   = UNIVIEW_ASSET_INFO_FILE;
    mapVendor["DAHUA"]     = DAHUA_ASSET_INFO_FILE;

    std::map<const char*, const char*>::iterator iter;
    for(iter = mapVendor.begin(); iter != mapVendor.end(); iter++)
    {
        FILE *fp = fopen(iter->second, "r");
        char buf[256];
        if (fp == NULL)
        {
            printf("%s: Can't open %s for asset name vendor table",
                    __FUNCTION__, iter->second);
            continue;
        }

        printf("%s: open %s for asset name vendor table success !\n", __FUNCTION__, iter->second);

        while (fgets(buf, sizeof(buf), fp) != NULL)
        {
            parse_asset_name_type_line(buf, iter->first);
        }

        fclose(fp);
    }
}

int main()
{
    INIT_LIST_HEAD(&asset_name_vendor_list);

    init_asset_name_table();
}
