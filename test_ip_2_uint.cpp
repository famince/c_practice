#include<iostream>
#include<string.h>
#include<cstdlib>
using namespace std;
 
union IP 
{
	unsigned char char_ip[4];
	unsigned int uint_ip; 
};

unsigned int IptoUint(char * ip,int size)
{
	unsigned int t[4]; 
	int dot_ind[3]={0};//存储.位置
	int j=0;
	for(int i=0;i<size;i++)
	{
		if(ip[i]=='.')
		{
			dot_ind[j++]=i;
		}
	}
	char *p=(char *)malloc(3);
	p=strncpy (p,ip,dot_ind[0]);
	t[0]=atoi(p);
	p=strncpy (p,ip+dot_ind[0]+1,dot_ind[1]-dot_ind[0]-1);
	t[1]=atoi(p);
	p=strncpy (p,ip+dot_ind[1]+1,dot_ind[2]-dot_ind[1]-1);
	t[2]=atoi(p);
	p=strncpy (p,ip+dot_ind[2]+1,size-dot_ind[2]-1);
	t[3]=atoi(p);
	unsigned int ip_uint=t[0]*256*256*256+t[1]*256*256+t[2]*256+t[3];
	return ip_uint;
}
 
char* UinttoIp(const unsigned int a)
{
	IP ip;
	ip.uint_ip=a;
	char * pp=new char[20];
	memset(pp,0,20);
 
	for(int i=3;i>=0;i--)//由机器的大小端决定，此处是小端，即高位存在高地址，地位存在低地址
	{
 
		char tmp[4]="";
		//itoa(ip.char_ip[i],tmp,10);
                sprintf(tmp,"%d",ip.char_ip[i]);
		strcat(pp,tmp);
		if(i>0)
		{
			char *dot=".";
			strcat(pp,dot);
		}
	}
	return pp;
}

int main()
{
	char s[20]="172.18.2.243";
	cout<<"请输入ip地址：";
	cin>>s;
	cout<<"您输入的ip地址是："<<s<<endl;
	unsigned int b=IptoUint(s,strlen(s));
	cout<<"转换成uint字符是："<<b<<endl;
	
	cout<<"uint再转换为ip地址是："<<UinttoIp(b)<<endl;  
    return 0; 
}
