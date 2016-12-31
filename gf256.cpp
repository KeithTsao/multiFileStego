#include "gf256.h"

GF256::GF256()
{

}

bool GF256::getFileList(string dirPath) {
    WIN32_FIND_DATA findData;
    HANDLE hFindFile;
    string p;

    fileList.clear();
    dirPath.append("\\");
    hFindFile = ::FindFirstFile(p.assign(dirPath).append("*.bmp").c_str(), &findData);
    if(hFindFile == INVALID_HANDLE_VALUE) {
        return false;
    }

    do
    {
        if(findData.cFileName[0] == '.') {
            continue;
        }
        if(!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            fileList.push_back(p.assign(dirPath).append(findData.cFileName));
        }
    }while(::FindNextFile(hFindFile, &findData));
    if(fileList.empty()) return false;
    return true;
}

bool GF256::steg(string plainText, char stopSign) {
    if(fileList.empty()) return false;

    string mat[9];
    int count = 0;

    for(unsigned i = 0; i < 9; ++i) {
        mat[i].push_back('0'+i);
    }//首标识符

    for(string::iterator i = plainText.begin(); i < plainText.end(); ++i) {
        mat[count % 4].push_back(*i);
        ++count;
    }//主存储单元

    for(; count % 4 != 0; ++count) {
        mat[count % 4].append(" ");
    }//长度对齐

    for(unsigned i = 0; i < mat[0].size(); ++i) {
        mat[4].push_back( mat[0].at(i) ^ mat[1].at(i) ^ 0x80);//4: 0 xor 1
        mat[5].push_back( mat[1].at(i) ^ mat[2].at(i) ^ 0x80);//5: 1 xor 2
        mat[6].push_back( mat[2].at(i) ^ mat[3].at(i) ^ 0x80);//6: 2 xor 3
        mat[7].push_back( mat[3].at(i) ^ mat[0].at(i) ^ 0x80);//7: 3 xor 0
        mat[8].push_back( mat[4].at(i) ^ mat[6].at(i) ^ 0x80);//8: 0 xor 1 xor 2 xor 3
    }//辅助单元,最后的异或是为了防止出现0

    for(unsigned i = 0; i < 9; ++i) {
        mat[i].push_back(stopSign);
    }//停止符

    for(unsigned i = 0; i < 9; ++i) {
        if(!encrypt(fileList[i % fileList.size()], mat[i])) {
            return false;
        }
    }
    return true;
}

string GF256::recover(char stopSign) {
    string ans("");

    if(fileList.empty()) return ans;

    string mat[9];
    string temp;
    char head;
    for(unsigned i = 0; i < 9; ++i) mat[i].clear();
    for(unsigned i = 0; i < fileList.size(); ++i) {
        temp = decrypt(fileList[i].c_str(), stopSign);
        head = temp.at(0);
        if(head >= '0' && head <='8') {
            mat[head - '0'].assign(temp);
        }
    }

    bool solved = false;
    int trans[3][3] = {{0,1,4},{3,2,6},{7,5,8}};
    for(unsigned int i = 0; i < 9; ++i) {
        solved = true;
        for(int j = 0; j < 4; ++j) solved = solved && !mat[j].empty();
        if(solved) break;

        vector<int> empt;
        vector<int> hath;
        for(int j = 0; j < 3; ++j) {
            empt.clear(), hath.clear();
            for(int k = 0; k < 3; ++k) {
                if(mat[trans[j][k]].empty()) {
                    empt.push_back(trans[j][k]);
                }
                else {
                    hath.push_back(trans[j][k]);
                }
            }
            if(empt.size() == 1) {
                mat[empt[0]] = strxor(mat[hath[0]], mat[hath[1]]);
            }//行

            empt.clear(), hath.clear();
            for(int k = 0; k < 3; ++k) {
                if(mat[trans[k][j]].empty()) {
                    empt.push_back(trans[k][j]);
                }
                else {
                    hath.push_back(trans[k][j]);
                }
            }
            if(empt.size() == 1) {
                mat[empt[0]] = strxor(mat[hath[0]], mat[hath[1]]);
            }//列
        }
    }
    if(!solved) return ans;

    for(unsigned i = 1; i < mat[0].size(); ++i) {
        for(int j = 0; j < 4; ++j) {
            ans.push_back(mat[j].at(i));
        }
    }
    return ans;
}

string GF256::strxor(const string &a, const string &b) {
    string ans("");
    if(a.size() != b.size()) return ans;

    for( unsigned i = 0; i < a.size(); ++i) {
        ans.push_back(a.at(i) ^ b.at(i) ^ 0x80);
    }
    return ans;
}
