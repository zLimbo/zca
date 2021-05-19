#include "zcamgr.h"
#include "zserver.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


void testRootCA() {
    zlimbo::ca::CAManager caMgr;

    // ca及其证书
    // caMgr.genRsaPriKey("./demoCA/private/cakey.pem", 2048u);
    caMgr.genSm2PriKey("./demoCA/private/cakey.pem");
    caMgr.genSelfSignCert("./demoCA/private/cakey.pem", "./demoCA/cacert.pem", 3060u, "CN", "SH", "ECNU", "CA");
    
    // 相关机构构建证书申请
    // caMgr.genRsaPriKey("./demoReq/priKey.pem", 2048u);
    caMgr.genSm2PriKey("./demoReq/priKey.pem");
    caMgr.genCertReq("./demoReq/priKey.pem", "./demoReq/certReq.pem", "CN", "SH", "ECNU", "DASE22");
    
    // ca签署证书
    caMgr.signCert("./demoReq/certReq.pem", "./demoReq/signCert.pem", 365u);


    // 证书验证
    cout << "ca verify: " << endl;
    caMgr.verify("./demoCA/cacert.pem", "./demoReq/signCert.pem");
}

int main() {

    // testCAServer();

    testRootCA();


    // uint serial;
    // ifstream fin("./demoCA/serial");
    // if (fin.fail()) {
    //     cout << "error" << endl;
    // }
    // fin >> serial;
    // cout << "serial: " << serial << endl;

    // string s = "12345";
    // const char* data = s.data();
    // const char *cs = s.c_str();
    // printf("%s\nlen=%d\n%d\n", data, strlen(data), int(data[5]));
    // printf("%s\nlen=%d\n%d\n", cs, strlen(cs), int(cs[5]));


    return 0;
}