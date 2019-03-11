#include "CsvParser.h"

#include <iostream>
#include <fstream>

int CsvParser::parse(const std::string& csvFilePath)
{
    std::ifstream ifs(csvFilePath.c_str());
    if (!ifs) {
        std::fprintf(stderr, "failed to open file.");
        return -1;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        std::size_t current = 0, prev = 0, colIndex = 0;
        while (true) {
            current = line.find(",", prev);
            if (this->cols.size() <= colIndex) {
                Column col;
                col.header = line.substr(prev, current - prev);
                cols.push_back(std::move(col));
            } else {
                cols[colIndex].vals.push_back(std::stof(line.substr(prev, current - prev)));
            }

            if (current == std::string::npos) {
                break;
            }

            prev = current + 1;
            ++colIndex;
        }
    }

    return 0;
}
