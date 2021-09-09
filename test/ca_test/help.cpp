#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


const string file_name("decode_cert.c");

int main() {

    ifstream fin(file_name, ifstream::in);

    string s;
    vector<string> lines;
    while (getline(fin, s)) {
        if (s != "") {
            lines.push_back(s);
        }
    }

    cout << lines.size() << endl;

    fin.close();

    ofstream fout(file_name, ofstream::out);
    for (string& s: lines) {
        fout << s << endl;
    }
    fout.flush();
    fout.close();

    return 0;
}