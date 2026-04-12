#pragma once
#include "Common.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class RecordManager
{
private:
    std::vector<int> Allrecords;
    std::vector<int> TopThree;

public:
    RecordManager();
    ~RecordManager();

    bool ifFileEmpty;
    int lastGoat;
    int getLastGoat() const;

    const std::vector<int> &getAllRecords() const { return Allrecords; }
    void loadRecord();
    void saveRecord(const int &score);
    void sortRecord();
};