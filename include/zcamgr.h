#ifndef __ZCA_H__
#define __ZCA_H__

#include <vector>
#include <string>

namespace zlimbo {

namespace ca {

using std::string;
using uint = unsigned int;

class CAManager {

public:
    static const string OPENSSL;
    static const string OPENSSL_GENRSA;
    static const string OPENSSL_CA;
    static const string OPENSSL_REQ;
    static const string OPENSSL_X509;
    static const string OPENSSL_VERIFY;
    static const string OPENSSL_ECPARAM_GENKEY_SM2;

    static const string SERIAL_FILE_NAME;

    static const uint DEFUALT_DAYS = 365U;

private:
    string caDir;
    
private:
    void execCmd(string cmd);

public:
    string genSubj(string subjC, string subjST, string subjO, string subjCN);

    void genRsaPriKey(string outPath, uint len);

    void genSm2PriKey(string outPath);

    void genCertReq(string priKeyPath, string outPath, 
            string subjC, string subjST, string subjO, string subjCN);

    void genSelfSignCert(string priKeyPath, string outPath, uint days, 
            string subjC, string subjST, string subjO, string subjCN);
    
    void signCert(string inPath, uint days);
    void signCert(string inPath, string outPath, uint days);

    void verify(string caCertPath, string certPath);

    void pem2der(string inPath, string outPath);

    void printPemInfo(string inPath);

    string readSerialFromFile();


public:
    CAManager(string caDir = "./demoCA"): caDir(caDir) {}

    string getCaDir() const { return caDir; }
    

}; // class ZCA


} // ca

} // namespace zlimbo 

#endif