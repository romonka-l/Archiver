#ifndef ARCHALGS_H
#define ARCHALGS_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <QDir>
using namespace std;
class Archs{
private:
    string toStdDir(string path);
public:
    void archLZ78(string fileName, string relativePath);
    void archDir(vector<string> files, string dirName, QDir currentDirPath);
    void recover(string fileName);
};

#endif //ARCHALGS_H
