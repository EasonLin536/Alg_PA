#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "mps.h"
#include "../lib/tm_usage.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Invalid input!" << endl;
        return 0;
    }

    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    string input_file = argv[1];
    string output_file = argv[2];

    tmusg.periodStart();

    chordMap myMap;
    myMap.read(input_file);
    myMap.findMPS();
    myMap.print(output_file);

    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000000.0 << "s" << endl;
}