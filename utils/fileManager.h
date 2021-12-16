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
    bool highScoreSaved = false;
public:
    FileManager();
    vector<vector<int>> loadedLevel;
    unordered_map<int, float> getHighScores();
    bool saveHighScore(int level, float score);
    bool loadLevel();
    void reset();
};

void prettyPrintLevel(vector<vector<int>>);
#endif