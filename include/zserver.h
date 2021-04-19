#ifndef __ZSERVER_H__
#define __ZSERVER_H__

#include "zcamgr.h"
#include <unistd.h>

namespace zlimbo {

namespace ca {

using std::string;

class CAServer {

public:
    static const uint BUF_SIZE = 1024;

private:

    string url;
    uint port;
    uint queueNum;
    uint serverSocketFd;
    bool isOpen = false;

    CAManager caMgr;


private:

    void bindAndListen();

    void loopHandleConnect();

public:

    CAServer(const string& url, uint port, uint queueNum = 20);
    ~CAServer() { if (isOpen) close(serverSocketFd); }
    void start();
    
};



} // namespace ca


} // namespace zlimbo


#endif