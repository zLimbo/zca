#include "zca.h"
#include <iostream>

using namespace std;


void testRootCA() {
    zlimbo::ca::CAManager caMgr;

    caMgr.genRsaPriKey("./demoCA/private/cakey.pem", 2048u);
    caMgr.genSelfSignCert("./demoCA/private/cakey.pem", "./demoCA/cacert.pem", 3060u, "CN", "SH", "ECNU", "CA");
    
    caMgr.genRsaPriKey("./demoReq/priKey.pem", 2048u);
    caMgr.genCertReq("./demoReq/priKey.pem", "./demoReq/certReq.pem", "CN", "SH", "ECNU", "DASE4");
    
    caMgr.signCert("./demoReq/certReq.pem", "./demoReq/signCert.pem", 365u);
}

int main() {

    testRootCA();

    return 0;
}