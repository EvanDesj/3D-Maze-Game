#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <unordered_map>
using namespace std;

class FileManager
{
private:
    void prettyPrintLevel();
    bool highScoreSaved = false;
    unordered_map<string, float> levelScores;
public:
    FileManager();
    vector<vector<int>> loadedLevel;
    bool getHighScores();
    bool saveHighScore(string level, float score);
    bool loadLevel();
    void reset();
};

#endif