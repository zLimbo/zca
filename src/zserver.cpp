#include "zserver.h"
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
#include <iostream>


namespace zlimbo {

namespace ca {

using std::cout;
using std::endl;


CAServer::CAServer(const string& url, uint port, uint queueNum): 
        url(url), port(port), queueNum(queueNum) {
    
}


void CAServer::bindAndListen() {
    serverSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(url.c_str());
    serverAddr.sin_port = htons(port);
    bind(serverSocketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocketFd, queueNum);
    isOpen = true;
    cout << "CA server listen on " << url << ":" << port << endl;
}


void CAServer::loopHandleConnect() {
    int clientSocketFd;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    char buffer[BUF_SIZE] = {0};
    FILE *fp = nullptr;
    int num = 0;
    while (true) {
        cout << "In listening, wait for a connection..." << endl;
        clientSocketFd = accept(serverSocketFd, (struct sockaddr*)&clientAddr, &clientAddrSize);
        cout << "connect start, client " << clientAddr.sin_addr.s_addr << ":" << clientAddr.sin_port << endl;
        string serial = caMgr.readSerialFromFile();
        cout << "serial: " << serial << endl;

        string reqPath = caMgr.getCaDir() + "/req/" + serial + ".pem";
        if ( (fp = fopen(reqPath.data(), "wb")) == nullptr) {
            cout << "open file " + reqPath + " failed!" << endl;
            exit(-1);
        }
        if ( (num = read(clientSocketFd, buffer, BUF_SIZE)) > 0) {
            fwrite(buffer, 1, num, fp);
        }
        fclose(fp);

        caMgr.signCert(reqPath, CAManager::DEFUALT_DAYS);
        
        string certPath = caMgr.getCaDir() + "/newcerts/" + serial + ".pem";
        if ( (fp = fopen(certPath.data(), "rb")) == nullptr) {
            cout << "open file " + certPath + " failed!" << endl;
            exit(-1);
        }
        while ( (num = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
            write(clientSocketFd, buffer, num);
        }
        
        shutdown(clientSocketFd, SHUT_WR);
        fclose(fp);

        cout << "connect close..." << endl;
        close(clientSocketFd);
    }
}


void CAServer::start() {
    bindAndListen();
    loopHandleConnect();
}



} // namespace ca


} // namespace zlimbo