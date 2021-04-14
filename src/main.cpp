#include "zca.h"
#include <iostream>

using namespace std;


void testRootCA() {
    zlimbo::ca::CAManager caMgr;

    

    caMgr.genRsaPriKey("test/ca/priKey.pem", 2048u);
    caMgr.genSelfSignCert("test/ca/priKey.pem", "test/ca/selfSignCert.pem", 3060u, "CN", "SH", "ECNU", "CA");
    
    caMgr.genRsaPriKey("test/dase/priKey.pem", 2048u);
    caMgr.genCertReq("test/dase/priKey.pem", "test/dase/certReq.pem", "CN", "SH", "ECNU", "DASE");
    
    caMgr.signCert("test/ca/priKey.pem", "test/ca/selfSignCert.pem", "test/dase/certReq.csr", "test/dase/signCert.pem", 365u);
}

int main() {

    testRootCA();

    return 0;
}