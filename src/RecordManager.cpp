#include "RecordManager.h"
#include <vector>
#include <algorithm>

RecordManager::RecordManager() { this->Allrecords.clear(); }
RecordManager::~RecordManager() {}

void RecordManager::loadRecord()
{
    this->Allrecords.clear();
    std::ifstream ifs("Tetris_score.txt", std::ios::in);

    if (!ifs.is_open())
    {
        this->ifFileEmpty = true;
        return;
    }
    int score = 0;
    while (ifs >> score)
    {
        this->Allrecords.push_back(score);
    }

    ifs.close();

    this->ifFileEmpty = this->Allrecords.empty();

    this->sortRecord();
}

void RecordManager::saveRecord(const int &score)
{
    this->lastGoat = this->getLastGoat();
    std::ofstream ofs("Tetris_score.txt", std::ios::app);

    if (ofs.is_open())
    {
        ofs << score << std::endl;
        ofs.close();
    }

    this->Allrecords.push_back(score);

    this->sortRecord();

    this->ifFileEmpty = false;
}

void RecordManager::sortRecord()
{
    if (this->Allrecords.empty())
    {
        return;
    }

    std::sort(Allrecords.begin(), Allrecords.end(), [](int a, int b)
              { return a > b; });
}

int RecordManager::getLastGoat() const
{
    if (Allrecords.empty())
    {
        return 0;
    }
    return this->Allrecords[0];
}