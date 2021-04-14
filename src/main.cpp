#include "zca.h"
#include <iostream>

using namespace std;


void testRootCA() {
    zlimbo::ca::CAManager caMgr;

    string priKeyPath = "test/priKey.pem";
    string signCertPath = "test/signCert.pem";
    unsigned int length = 3096;

    caMgr.genRsaPriKey(priKeyPath, length);
    caMgr.genSelfSignCert(priKeyPath, signCertPath, 3060u, "CN", "SH", "ECNU", "DASE");
    caMgr.pem2crt(signCertPath, "test/signCert.der");

    cout << "info: " << endl;
    caMgr.printPemInfo(signCertPath);
}

int main() {

    testRootCA();

    return 0;
}