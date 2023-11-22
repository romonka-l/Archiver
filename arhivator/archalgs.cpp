#include "archalgs.h"

using namespace std;
    string Archs::toStdDir(string path){
        for(int i = 0; i < path.length(); i++){
            if(path[i] == '/'){
                path.replace(i, 1, "\\\\");
            }
        }
        return path;
    }

    void Archs::archLZ78(string fileName, string relativePath){
        fileName = toStdDir(fileName);
        fstream fsrc;
        string ext = fileName.substr(fileName.find_last_of('.'), fileName.length() - fileName.find_last_of('.'));
        if(ext.compare(".txt") == 0){
            fsrc.open(fileName, ios_base::in);
        } else {
            fsrc.open(fileName, ios_base::binary | ios_base::in);
        }
        map<string, unsigned short> dictionary = {{"", 0}};
        fileName.replace(fileName.find_last_of('.'),fileName.length() - fileName.find_last_of('.'), ".zxc");
        fstream fdest(fileName, ios_base::binary | ios_base::out);
        int fileSize = 0;
        fdest.write((char*)&fileSize, sizeof(fileSize));
        for(char i = 0; i < relativePath.length(); i++){
           fdest.write((char*)&(relativePath[i]), sizeof(relativePath[i]));
        }
        string buffer = "";
        char tempChar = 0;
        while(true){
            fsrc.get(tempChar);
            if(fsrc.eof()) break;

            if(dictionary.find(buffer + tempChar) != dictionary.end()){
                buffer += tempChar;
            } else {
                unsigned short pos = dictionary.find(buffer)->second;
                fdest.write((char*)&pos, sizeof(pos));
                fdest.write((char*)&(tempChar), sizeof(tempChar));
                fileSize++;
                dictionary[buffer + tempChar] = (unsigned short)(dictionary.size());
                buffer.clear();
                if(dictionary.size() > 65534){
                    dictionary.clear();
                    dictionary.insert({"", 0});
                }
            }
         }
         if(buffer.length() != 0){
             char last = buffer.back();
             buffer.pop_back();
             unsigned short pos = 0;
             if(dictionary.find(buffer) != dictionary.end()){
                pos = dictionary.find(buffer)->second;
             }
             fdest.write((char*)&pos, sizeof(pos));
             fdest.write((char*)&last, sizeof(last));
             fileSize++;
         }
         fdest.seekp(ios::beg);
         fdest.write((char*)&fileSize, sizeof(fileSize));
         fdest.close();
         fsrc.close();
    }

    void Archs::archDir(vector<string> files, string dirName, QDir currentDirPath){
        fstream fdest(toStdDir(dirName) + ".zxc", ios_base::binary | ios_base::out);

        for(int i = 0; i < files.size(); i++){
            string ext = toStdDir(files[i]).substr(toStdDir(files[i]).find_last_of('.'), toStdDir(files[i]).length() - toStdDir(files[i]).find_last_of('.'));
            fstream fsrc;
            if(ext.compare(".txt") == 0){
                fsrc.open(toStdDir(files[i]), ios_base::in);
            } else {
                fsrc.open(toStdDir(files[i]), ios_base::binary | ios_base::in);
            }
            map<string, unsigned short> dictionary = {{"", 0}};
            string buffer = "";

            unsigned int fileSize = 0;
            fdest.write((char*)&fileSize, sizeof(fileSize));

            string relativePath = currentDirPath.relativeFilePath(QString::fromStdString(files[i])).toStdString();
            for(char i = 0; i < relativePath.length(); i++){
                fdest.write((char*)&(relativePath[i]), sizeof(relativePath[i]));
            }
            char tempChar = 0;
            while(true){
                fsrc.get(tempChar);
                if(fsrc.eof()) break;
                if(dictionary.find(buffer + tempChar) != dictionary.end()){
                    buffer += tempChar;
                } else {
                    unsigned short pos = dictionary.find(buffer)->second;
                    fdest.write((char*)&pos, sizeof(pos));
                    fdest.write((char*)&tempChar, sizeof(tempChar));
                    fileSize++;
                    dictionary[buffer + tempChar] = (unsigned short)(dictionary.size());
                    buffer.clear();
                    if(dictionary.size() > 65534){
                        dictionary.clear();
                        dictionary.insert({"", 0});
                    }
                }
             }
             if(buffer.length() != 0){
                 char last = buffer.back();
                 buffer.pop_back();
                 unsigned short pos = 0;
                 if(dictionary.find(buffer) != dictionary.end()){
                    pos = dictionary.find(buffer)->second;
                 }
                 fdest.write((char*)&pos, sizeof(pos));
                 fdest.write((char*)&last, sizeof(last));
                 fileSize++;
             }
             fsrc.close();
             fdest.seekp(-(fileSize * 3 + relativePath.size() + 4), ios::cur);
             fdest.write((char*)&fileSize, sizeof(fileSize));
             fdest.seekp(0, ios::end);
        }
        fdest.close();
    }
    void Archs::recover(string filePath){
        QDir currentDir(QString::fromStdString(filePath.substr(0, filePath.find_last_of('/'))));
        filePath = toStdDir(filePath);
        fstream fsrc(filePath, ios_base::binary | ios_base::in);
        while(true){
            unsigned int fileSize = 0;
            fsrc.read((char*)&fileSize, sizeof(fileSize));
            if(fsrc.eof()){
                break;
            }
            string relativeFileName = "";
            while(true){
                char temp = 0;
                fsrc.get(temp);
                if(temp == 0){
                    break;
                }
                relativeFileName.push_back(temp);
            }
            fsrc.seekp(-1, ios::cur);
            vector<string> dictionary = {""};
            if(relativeFileName.find_last_of('/') != -1){
                currentDir.mkpath(QString::fromStdString(relativeFileName.substr(0, relativeFileName.find_last_of('/'))));
            }
            fstream fdest;
            string ext = relativeFileName.substr(relativeFileName.find_last_of('.'), relativeFileName.length() - relativeFileName.find_last_of('.'));
            if(ext.compare(".txt") == 0){
                fdest.open(toStdDir(currentDir.absolutePath().toStdString() + "\\\\" + relativeFileName), ios_base::out);
            } else {
                fdest.open(toStdDir(currentDir.absolutePath().toStdString() + "\\\\" + relativeFileName), ios_base::binary | ios_base::out);
            }
            for(unsigned int i = 0; i < fileSize; i++){
                unsigned short tempPos = 0;
                fsrc.read((char*)&tempPos, sizeof(tempPos));
                char tempChar = 0;
                fsrc.read((char*)&tempChar, sizeof(tempChar));
                string word = dictionary[tempPos] + tempChar;
                fdest << word;
                dictionary.push_back(word);

                if(dictionary.size() > 65534){
                    dictionary.clear();
                    dictionary.push_back("");
                }
            }
            dictionary.clear();
            fdest.close();
        }
        fsrc.close();
    }
