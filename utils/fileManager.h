#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

class FileManager
{
private:
    void prettyPrintLevel();
    bool highScoreSaved = false;
public:
    FileManager();
    vector<vector<int>> loadedLevel;
    bool saveHighScore(float score);
    bool loadLevel();
    void reset();
};

#endif