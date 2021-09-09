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
    void execCmd(const string& cmd);

public:
    string genSubj(const string& subjC, const string& subjST, const string& subjO, const string& subjCN);

    void genRsaPriKey(const string& outPath, uint len);

    void genSm2PriKey(const string& outPath);

    void genCertReq(const string& priKeyPath, const string& outPath, 
            const string& subjC, const string& subjST, const string& subjO, const string& subjCN);

    void genSelfSignCert(const string& priKeyPath, const string& outPath, uint days, 
            const string& subjC, const string& subjST, const string& subjO, const string& subjCN);
    
    void signCert(const string& inPath, uint days);
    void signCert(const string& inPath, const string& outPath, uint days);

    void verify(const string& caCertPath, const string& certPath);

    void pem2der(const string& inPath, const string& outPath);

    void printPemInfo(const string& inPath);

    string readSerialFromFile();


public:
    CAManager(const string& caDir = "./demoCA"): caDir(caDir) {}

    string getCaDir() const { return caDir; }
    

}; // class ZCA


} // ca

} // namespace zlimbo 

#endif