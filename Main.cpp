#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <getopt.h>

#include "CsvParser.h"
#include "GnuplotPipe.h"
#include "Params.h"

static constexpr struct option longopts[] = {
    { "point",  no_argument,       nullptr, 'p' },
    { "num",    required_argument, nullptr, 'n' },
    { "single", no_argument,       nullptr, 's' },
    { "output", required_argument, nullptr, 'o' },
    { 0,        0,                 0,        0  },
};

static void usage()
{ 
    std::printf(
        "Usage: csvplot [OPTIONS] csvfile\n"
        " -p, --point           Plot with points\n"
        " -n, --num=N           Set number of graphs in a row\n"
        " -s, --single          Plot all rows in a graph\n"
        " -o, --output=FILENAME Specify output filename and save graph\n"
        " -t, --type=FILETYPE   Specify output file type\n"
    );
}

static int parseCommandLine(int argc, char* argv[], Params& params)
{
    int opt = 0, longIndex = 0; 
    while ((opt = getopt_long(argc, argv, "pn:so:t:", longopts, &longIndex)) != -1) {
        switch (opt) {
        case 'p': { params.pointFlag  = true;              break; }
        case 'n': { params.numOfCols  = std::stoi(optarg); break; }
        case 's': { params.singleFlag = true;              break; }
        case 'o': { params.outputFileName = optarg;        break; }
        case 't': { params.outputFileType = optarg;        break; }
        default:  { 
            std::fprintf(stderr, "Invalid option '%c'\n", opt);
            return -1;
        }
        }
    }    

    if (optind < argc) {
        params.csvFilePath = argv[optind];
    } else {
        ::usage();
        return -1;
    }

    return 0;
}

int main(int argc, char* argv[])
{
    Params params;
    if (::parseCommandLine(argc, argv, params) != 0) {
        return -1;
    }
    
    CsvParser parser;
    if (parser.parse(params.csvFilePath) != 0) {
        std::cerr << "parsing csv failed" << std::endl;
        return -1;
    }

    GnuplotPipe gp;
    if (gp.plot(params, parser.getCols()) != 0) {
        std::cerr << "plot failed." << std::endl;
        return -1;
    }

    return 0;
}
