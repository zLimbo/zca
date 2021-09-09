#ifndef __ZCLIENT_H__
#define __ZCLIENT_H__

#include "zcamgr.h"

namespace zlimbo {

namespace ca {

using std::string;

class CAClient {

public:
    static const uint BUF_SIZE = 1024;

private:

    uint clientSocketFd;

    CAManager caMgr;

public:

    void sendCertReq(const string& url, uint port, const string& inPath, const string& outPath);
    
};



} // namespace ca


} // namespace zlimbo


#endif