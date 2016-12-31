#ifndef GF256_H
#define GF256_H

#include "ED.h"
#include <string>
#include <vector>
#include <windows.h>

using namespace std;


class GF256
{
private:
    vector<string> fileList;
    string strxor(const string &a, const string &b);
public:
    GF256();
    //get flie list from directory path
    bool getFileList(string dirPath);
    //steg the message to files
    bool steg(string plainText, char stopSign = '`');
    //recover the message if possible
    string recover(char stopSign = '`');
};

#endif // GF256_H
