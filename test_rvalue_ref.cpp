// 练习右值引用

#include <iostream>
using namespace std;
int glo=10;
void process(int && a){
    glo+=a;
}

void process(int &a){
    glo-=a;
}

int get_return(){
    int b=3;
    return b;
}

int main() {
    int a = 6;
    process(8);
    cout<<glo<<endl;
    process(a);
    cout<<glo<<endl;
    int && k = 	get_return();
    cout<<k<<endl;
    return 0;
}
