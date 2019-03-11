#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <vector>
#include <string>
#include "Column.h"

class CsvParser {
public:
    int parse(const std::string& csvFilePath);

    inline const std::vector<Column> getCols() const
    {
        return this->cols;
    }
private:
    std::vector<Column> cols;
};

#endif
