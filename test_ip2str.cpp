#include<stdlib.h>
#include<stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<iostream>
#include<string.h>
using namespace std;


//typedef unsigned long uint32_t;

#define IPBUF_LEN 16

void ip2str(uint32_t ip, char *ipstr_tmpbuf)
{
    struct in_addr in; 
    in.s_addr = htonl(ip);
    snprintf(ipstr_tmpbuf, IPBUF_LEN, "%s", inet_ntoa(in));

    printf("%s\n", ipstr_tmpbuf);
}

int str2ip(char *ipstr)
{
    struct in_addr dstIp;
    //uint32_t ip;
   int ip;

    if ( 0 == inet_aton(ipstr, &dstIp))
    {
        printf("inet_aton error! ");
        return -1;
    }

    ip = ntohl(dstIp.s_addr);
    return ip;
}

int main()
{
    uint32_t key;
    printf("input integer number:\n");
    printf("1: unit ip to ipstr\n");
    printf("2: ipstr to ip\n");

    scanf("%d", &key);

    int ip;
    char ipstr[IPBUF_LEN]= {0};
    char ipstr_tmpbuf[IPBUF_LEN] = {0};

    switch(key) {
        case 1:
            cout<<"请输入ip地址：";
            cin >> ip;

            ip2str(ip, ipstr_tmpbuf);

            break;
        case 2:
            cout<<"请输入ip地址：";
            cin >> ipstr;

            cout << "您输入的ip地址是："<< ipstr << endl;

            ip = str2ip(ipstr);

            printf("%u\n", ip);
            break;
    }
    return 0; 
}
