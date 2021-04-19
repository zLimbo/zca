#include "zclient.h"
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
#include <iostream>

namespace zlimbo {

namespace ca {

using std::cout;
using std::endl;


void CAClient::sendCertReq(string url, uint port, string inPath, string outPath) {
    char buffer[BUF_SIZE] = {0};
    int num = 0;
    FILE *fp = nullptr;

    clientSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(url.data());
    serverAddr.sin_port = htons(port);
    connect(clientSocketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    if ( (fp = fopen(inPath.data(), "rb")) == nullptr) {
        cout << "open file " + inPath + " failed!" << endl;
        exit(-1);
    }
    cout << "send req " << inPath << " ..." << endl; 
    while ( (num = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
        write(clientSocketFd, buffer, num);
    }
    fclose(fp);

    
    if ( (fp = fopen(outPath.data(), "wb")) == nullptr) {
        cout << "open file " + outPath + " failed!" << endl;
        exit(-1);
    }
    cout << "receive cert " << outPath << " ..." << endl;
    while ( (num = read(clientSocketFd, buffer, BUF_SIZE)) > 0) {
        fwrite(buffer, 1, BUF_SIZE, fp);
    }
    fclose(fp);
    close(clientSocketFd);
}
    

} // namespace ca


} // namespace zlimbo