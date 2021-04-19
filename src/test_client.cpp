#include "zclient.h"

using namespace std;

int main() {

    zlimbo::ca::CAClient caClient;
    zlimbo::ca::CAManager caMgr;
    
    // 相关机构构建证书申请
    caMgr.genRsaPriKey("./demoReq/priKey.pem", 2048u);
    for (int i = 115; i < 124; ++i) {
        caMgr.genCertReq("./demoReq/priKey.pem", 
                "./demoReq/certReq.pem", "CN", "SH", "ECNU", "DASE" + to_string(i));
                caClient.sendCertReq("127.0.0.1", 8888, "./demoReq/certReq.pem", "./demoReq/cert.pem");
    }

    
    
    return 0;
}