#ifndef SETTING_H
#define SETTING_H

#include <cstdint>
#include <string>

struct Params {
    Params()  
      : csvFilePath(), 
        outputFileName(),
        outputFileType("qt"),
        numOfCols(1),
        pointFlag(false),
        singleFlag(false) {
    }

    std::string csvFilePath;
    std::string outputFileName;
    std::string outputFileType;
    int  numOfCols;
    bool pointFlag;
    bool singleFlag;
};

#endif
