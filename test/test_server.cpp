#include "zserver.h"

using namespace std;

int main() {

    zlimbo::ca::CAServer caServer("127.0.0.1", 8888);
    caServer.start();

    return 0;
}