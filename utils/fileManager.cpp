#include "fileManager.h"

FileManager::FileManager()
{
    return;
}

bool FileManager::saveHighScore(float score)
{
    if (highScoreSaved)
    {
        return false;
    }
    highScoreSaved = true;
    string name = "";
    cout << "Type your name to save highscore, enter N to cancel: ";
    getline(cin, name);
    if (name == "N" || name == "n")
    {
        cout<<"High score not saved";
        return false;
    }
    ofstream MyFile("save.txt", std::ios_base::app);
    if (MyFile.fail())
    {
        return false;
    }
    MyFile << name << "|" << score << endl;
    MyFile.close();
    return true;
}

bool FileManager::loadLevel()
{
    string myText;
    ifstream MyReadFile("board.txt");
    if (MyReadFile.fail())
    {
        return false;
    }
    while (getline(MyReadFile, myText))
    {
        loadedLevel.clear();
        vector<int> localVector = {};
        for (size_t i = 0; i < myText.length(); i++)
        {
            char character = myText[i];
            if (character != '{' && character != ',' && character != '}')
            {
                localVector.push_back(character - '0');
            }
            if (character == '}')
            {
                if (localVector.size())
                {
                    loadedLevel.push_back(localVector);
                }
                localVector = {};
            }
        }
    }
    // prettyPrintLevel();
    return true;
}

void FileManager::reset()
{
    highScoreSaved = false;
    loadedLevel = {{}};
}

void FileManager::prettyPrintLevel()
{
    for (size_t i = 0; i < loadedLevel.size(); i++)
    {
        cout << "{";
        for (size_t j = 0; j < loadedLevel[i].size(); j++)
        {
            if (j == loadedLevel[i].size() - 1)
            {
                cout << loadedLevel[i][j];
            }
            else
            {
                cout << loadedLevel[i][j] << ",";
            }
        }
        if (i == loadedLevel.size() - 1)
        {
            cout << "}";
        }
        else
        {
            cout << "},";
        }
    }
}