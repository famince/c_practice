#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <cstring>
using namespace std;

#define HIKVISION_ASSET_NAME_INFO "/usr/local/VA_IoTSec/conf/hikvision_asset_name_info.conf"
#define HUAWEI_ASSET_NAME_INFO    "/usr/local/VA_IoTSec/conf/huawei_asset_name_info.conf"
#define KEDACOM_ASSET_NAME_INFO   "/usr/local/VA_IoTSec/conf/kedacom_asset_name_info.conf"
#define UNIVIEW_ASSET_NAME_INFO   "/usr/local/VA_IoTSec/conf/uniview_asset_name_info.conf"
#define DAHUA_ASSET_NAME_INFO     "/home/alex/practice/dahua.txt"


struct asset_info {
    uint32_t device_ip;              /* ipv4 */
    uint8_t mac_addr[6];             /* mac */
    uint8_t identify_status;         /* 识别完成状态 */
    uint8_t switch_and_num;          /* 如果是snmp从交换机获取的，这个标识这个资产是从那个交换机snmp配置获取到的 */
    uint8_t access_status;           /* 接入状态 */
    uint8_t as_type;                 /* 设备类型 */
    uint8_t cur_identify_state;         
    uint8_t online_status;           /* 在线状态 */
    uint16_t as_type_changed;
    uint16_t onetime_idy_stat;
    uint32_t group_id;
    char name[64];
    char vendor[64];      /* 厂商 */
};

void Trim( string& inout_s )
{
    // Remove leading and trailing whitespace
    static const char whitespace[] = " \n\t\v\r\f";
    inout_s.erase( 0, inout_s.find_first_not_of(whitespace) );
    inout_s.erase( inout_s.find_last_not_of(whitespace) + 1U );
}

//const void supplement_vendor_info(const string& vendor_name, const string& file_name, const string& asset_name, asset_info *info)
const void set_vendor_info(const char *vendor_name, const char *file_name, asset_info *info)
{
    vector<string> asset_names;

    ifstream infile(file_name);
    if(! infile){
        cerr << "open error!" << endl;
        return;
    }

    string line;
    while (getline(infile, line)){
	Trim(line);
	asset_names.push_back(line);
    }

    //for (string & line : asset_names)
    //    cout << line << endl;

    vector<string>::iterator result = find(asset_names.begin(), asset_names.end(), info->name);
    if ( result != asset_names.end() ){
	strcpy(info->vendor, vendor_name);
        cout << info->name << " vendor is " << vendor_name << endl;
    }
}

int main()
{
    //string file_names[] = {
    //    HIKVISION_ASSET_NAME_INFO,
    //    HUAWEI_ASSET_NAME_INFO,
    //    KEDACOM_ASSET_NAME_INFO,
    //    UNIVIEW_ASSET_NAME_INFO,
    //    DAHUA_ASSET_NAME_INFO
    //};

    //for(auto &file_name : file_names)
    //{
    //    read_into_array(file_name, vendor_name);
    //}

    map<const char*, const char*> mapVendor;  
    mapVendor["HIKVISION"] = HIKVISION_ASSET_NAME_INFO;
    mapVendor["HUAWEI"]    = HUAWEI_ASSET_NAME_INFO;
    mapVendor["KEDACOM"]   = KEDACOM_ASSET_NAME_INFO;
    mapVendor["UNIVIEW"]   = UNIVIEW_ASSET_NAME_INFO;
    mapVendor["DAHUA"]     = DAHUA_ASSET_NAME_INFO;

    asset_info info;
    memset(&info, 0, sizeof(info));
    strncpy(info.name, "DH-IPC-HDBW5233R变焦系列", sizeof(info.name));

    map<const char*, const char*>::iterator iter; 
    for(iter = mapVendor.begin(); iter != mapVendor.end(); iter++)
    {
        set_vendor_info(iter->first, iter->second, &info);
    }
}
