#include "zca.h"
#include <iostream>

namespace zlimbo {

namespace ca {

using std::cout;
using std::endl;


void CAManager::execCmd(string cmd) {
    cout << "\n>>> cmd: " << cmd << endl;

    char line[1024];
    const char *sysCmd = cmd.data();
    FILE *fp = nullptr;

    if ((fp = popen(sysCmd, "r")) == nullptr) {
        cout << "error" << endl;
        exit(EXIT_FAILURE);
    }
    while (fgets(line, sizeof(line) - 1, fp) != nullptr) {
        cout << line;
    }
    pclose(fp);
}


inline string CAManager::genSubj(string subjC, string subjST, string subjO, string subjCN) {
    string subj = "/C=" + subjC + "/ST=" + subjST + "/O=" + subjO + "/CN=" + subjCN; 
    return subj;
}


void CAManager::genRsaPriKey(string outPath, uint length) {
    // e.g.: openssl genrsa -out /etc/pki/tls/private/subcakey.pem 2048
    string cmd = OPENSSL_GENRSA + " -out " + outPath + " " + to_string(length);
    execCmd(cmd);
}


void CAManager::genCertReq(string priKeyPath, string outPath, 
        string subjC, string subjST, string subjO, string subjCN) {
    // e.g.: openssl req -new -key /etc/pki/tls/private/subcakey.pem -out /etc/pki/tls/subca.csr -subj /C=CN/ST=GD/O=LINZ/CN=SubCA
    string subj = genSubj(subjC, subjST, subjO, subjCN);
    string cmd = OPENSSL_REQ + " -new -key " + priKeyPath + " -out " + outPath + " -subj " + subj;
    execCmd(cmd);
}


void CAManager::genSelfSignCert(string priKeyPath, string outPath, uint days, 
            string subjC, string subjST, string subjO, string subjCN) {
    // e.g.: openssl req -new -x509 -key /etc/pki/CA/private/cakey.pem -days 7300 -out /etc/pki/CA/cacert.pem -subj /C=CN/ST=GD/O=LINZ/CN=RootCA
    string subj = genSubj(subjC, subjST, subjO, subjCN);
    string cmd = OPENSSL_REQ + " -new -x509 -key " + priKeyPath + " -out " + outPath + " -days " + to_string(days) + " -subj " + subj;
    execCmd(cmd);
}


void CAManager::signCert(string caPriKeyPath, string certPath, string inPath, string outPath, uint days) {
    // e.g.: openssl ca -in subca.centos9.top.csr -out subca.centos9.top.crt -days 3650
    string cmd = OPENSSL_CA + " -in " + inPath + " -out " + outPath + " -days " + to_string(days);
    // string cmd = OPENSSL_CA + " -key " + caPriKeyPath + " -cert " + certPath + " -in " + inPath + " -out " + outPath + " -days " + to_string(days);
    execCmd(cmd);
}


void CAManager::pem2crt(string inPath, string outPath) {
    // e.g.: openssl x509 -outform der -in /etc/pki/CA/cacert.pem -out /etc/pki/CA/cacert.crt
    string cmd = OPENSSL_X509 + " -outform der -in " + inPath + " -out " + outPath; 
    execCmd(cmd);
}


void CAManager::printPemInfo(string inPath) {
    // e.g.: openssl x509 -noout -text -in /etc/pki/CA/cacert.pem
    string cmd = OPENSSL_X509 + " -noout -text -in " + inPath;
    execCmd(cmd);
}



} // namespace ca


} // namespace zlimbo