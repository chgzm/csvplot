#ifndef GNUPLOTPIPE_H
#define GNUPLOTPIPE_H

#include <sstream>
#include <vector>
#include <unordered_set>

#include "Column.h"
#include "Params.h"

class GnuplotPipe {
public:
    GnuplotPipe();

    int plot(const Params& params, const std::vector<Column>& cols);
private: 
    int plotSingle(const Params& params, const std::vector<Column>& cols);
    int plotMulti (const Params& params, const std::vector<Column>& cols);

    const std::unordered_set<std::string> availableFileType = {"png", "svg"};

    std::stringstream ss;
};

#endif
