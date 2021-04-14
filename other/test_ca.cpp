#include <iostream>
#include <vector>
#include <string>

using namespace std;

constexpr int N = 300;

int main() {

    vector<string> cmds = {
        "touch /etc/pki/CA/index.txt",
        "echo 01 > /etc/pki/CA/serial",
        "openssl genrsa -out /etc/pki/CA/private/cakey.pem 8192",
        "openssl req -new -x509 -key /etc/pki/CA/private/cakey.pem -days 7300 -out /etc/pki/CA/cacert.pem -subj /C=CN/ST=GD/O=LINZ/CN=RootCA",
        "openssl x509 -outform der -in /etc/pki/CA/cacert.pem -out /etc/pki/CA/cacert.crt",
        "openssl x509 -noout -text -in /etc/pki/CA/cacert.pem"
    };


    for (string cmd: cmds) {
        cout << "\ncmd: " << cmd << endl;

        char line[N];
        const char *sysCmd = cmd.data();
        FILE *fp = nullptr;

        if ((fp = popen(sysCmd, "r")) == NULL) {
            cout << "error" << endl;
            exit(EXIT_FAILURE);
        }
        while (fgets(line, sizeof(line) - 1, fp) != NULL) {
            cout << line;
        }
        pclose(fp);
    }


    return 0;
}