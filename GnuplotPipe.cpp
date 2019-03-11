#include "GnuplotPipe.h"
#include <cstdio>
#include <cmath>

GnuplotPipe::GnuplotPipe()
{
    this->ss << "set grid front\n" 
                "set mouse\n" 
                "set datafile separator \",\"\n"
                "set xlabel 'number of rows'\n";
}

int GnuplotPipe::plot(const Params& params, const std::vector<Column>& cols)
{
    if (params.outputFileName != "") {
        this->ss << "set out '" << params.outputFileName << "'\n";
    }

    if (this->availableFileType.count(params.outputFileType) != 1) {
        std::fprintf(stderr, "invalid file type.");
        return -1;
    }

    if (cols.size() > 0) {
        this->ss << "set xrange [0:" << cols[0].vals.size() << "]\n";
    }

    if (params.singleFlag) {
        return plotSingle(params, cols);
    } else {
        return plotMulti(params, cols);
    }   
}

int GnuplotPipe::plotSingle(const Params& params, const std::vector<Column>& cols)
{
    this->ss << "set term " << params.outputFileType << "\n";

    std::string type;
    if (params.pointFlag) {
        type = "p";
    } else {
        type = "l";
    }

    for (std::size_t i = 0; i < cols.size(); ++i) {
        if (i == 0) {
            this->ss << "plot '-' u 0:1 w " << type << " t '" << cols[i].header << "'";
        } else {  
            this->ss << ", '-' u 0:1 w " << type << " t '" << cols[i].header << "'";
        }

        if (i == (cols.size() - 1)) {
            this->ss << "\n";
        }
    }

    for (const Column& col : cols) {
        for (double v : col.vals) {
            ss << v << std::endl;
        }
        ss << "e\n";
    }

    FILE* gp = popen("gnuplot -persist", "w");
    if (nullptr == gp) {
        return -1;
    }

    std::fprintf(gp, "%s", this->ss.str().c_str());

    std::fflush(gp);
    pclose(gp);

    return 0;
}

int GnuplotPipe::plotMulti(const Params& params, const std::vector<Column>& cols)
{
//     if (params.outputFileType == "pdf") {
//         this->ss << "set term pdf size ";
//     } else if (params.outputFileType == "svg") {
//         this->ss << "set term svg size ";
//     } else if (params.outputFileType == "png") {
//         this->ss << "set term svg size ";
//     } else {
//         this->ss << "set term qt size ";
//     }
    this->ss << "set term "
             << params.outputFileType
             << " size "
             << 640 * params.numOfCols
             << "," 
             << 480 * std::ceil(((double)(cols.size()) / params.numOfCols))
             << "\n";

    this->ss << "set multiplot layout " 
             << std::ceil((double)(cols.size()) / params.numOfCols)
             << ", "
             << params.numOfCols
             << "\n";

    std::string type;
    if (params.pointFlag) {
        type = "p";
    } else {
        type = "l";
    }
       
    for (const Column& col : cols) {
        this->ss << "set title '" << col.header << "'\n"
                 << "plot '-' u 0:1 w " << type << " t ''\n";

        for (double v : col.vals) {
            this->ss << v << std::endl;
        }

        this->ss << "e\n";
    }

    this->ss << "unset multiplot\n";

    FILE* gp = popen("gnuplot -persist", "w");
    if (nullptr == gp) {
        return -1;
    }

    std::fprintf(gp, "%s", this->ss.str().c_str());

    std::fflush(gp);
    pclose(gp);

    return 0;
}
