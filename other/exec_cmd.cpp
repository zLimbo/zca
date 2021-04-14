#include<cstdlib>
#include<string>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 300;

void Test(void){
    char line[N];
    FILE *fp;
    string cmd = "echo 01 > /etc/pki/CA/serial";
    //引号内是你的linux指令
    // 系统调用
    const char *sysCommand = cmd.data();
    if ((fp = popen(sysCommand, "r")) == NULL) {
        cout << "error" << endl;
        return;
    }
    while (fgets(line, sizeof(line)-1, fp) != NULL){
        cout << line ;
    }
    pclose(fp);
}

int main(){
    Test();

    return 0;
}