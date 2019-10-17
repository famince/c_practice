/* sscanf example */
#include <stdio.h>

int main ()
{
    char mac[32]  = {0};
    char ip[32]  = {0};
    char gw[32]  = {0};
    char mask[32]  = {0};
    char ver[32]  = {0};

    char sentence []="MAC=10B11C4:C215CAAB DHCP=OFF IP=172.10.10.97 GW=172.10.10.1 NM=255.255.255.0 MDNS:PORT=12";

    int result = sscanf(sentence, "MAC=%s DHCP=OFF IP=%s GW=%s NM=%s %*s VER:%s", mac, ip, gw, mask, ver);
     
    printf("%d: mac= [%s] ip = [%s] gw = [%s] mask = [%s] ver = [%s]\n", result, mac, ip, gw, mask, ver);

    return 0;
}
