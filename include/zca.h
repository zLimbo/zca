#ifndef __ZCA_H__
#define __ZCA_H__

#include <vector>
#include <string>

namespace zlimbo {

namespace ca {

using std::string;
using std::vector;
using std::to_string;

using uint = unsigned int;

const static string OPENSSL = "openssl";
const static string OPENSSL_GENRSA = "openssl genrsa";
const static string OPENSSL_CA = "openssl ca";
const static string OPENSSL_REQ = "openssl req";
const static string OPENSSL_X509 = "openssl x509";

class CAManager {

private:

    void execCmd(string cmd);
    
public:

    string genSubj(string subjC, string subjST, string subjO, string subjCN);

    void genRsaPriKey(string outPath, uint __throw_length_error);

    void genCertReq(string priKeyPath, string outPath, 
            string subjC, string subjST, string subjO, string subjCN);

    void genSelfSignCert(string priKeyPath, string outPath, uint days, 
            string subjC, string subjST, string subjO, string subjCN);
    
    void signCert(string inPath, string outPath, uint days);

    void pem2crt(string inPath, string outPath);

    void printPemInfo(string inPath);

}; // class ZCA


} // ca

} // namespace zlimbo 

#endif