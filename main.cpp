#include "bmp.h"
#include "ED.h"
#include "gf256.h"
#include <iostream>
#include <string>

using namespace std;
//extern bool encrypt(string path, string message);
//extern string decrypt(const char* path, const unsigned char stop_symbol);

int main(int argc, char *argv[])
{
    if(argc == 1 || argc > 3) {
        cout<<"this program is for multi-file steg\n"
            <<"no argument: show this menu\n"
            <<"with argument DIRPATH: try to recover message from the directory\n"
            <<"with arguments DIRPATH and MESSAGE(without blank): steg the MESSAGE to directory\n";
        return 0;
    }
    GF256 s;
    if(argc == 2) {
        if(!s.getFileList(argv[1])) {
            cout<<"the path is not exist, or there is no bmp files in it.\n";
            return -1;
        }
        cout<<"recover:"<<s.recover()<<endl;
    }
    if(argc == 3) {
        if(!s.getFileList(argv[1])) {
            cout<<"the path is not exist, or there is no bmp files in it.\n";
            return -1;
        }
        if(!s.steg(argv[2])) {
            cout<<"some error occurs TAT\n";
            return -1;
        }
        cout<<"steg success!\n";
    }
    return 0;
}
