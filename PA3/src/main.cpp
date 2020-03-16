#include <iostream>
#include "cb.h"

using namespace std;

void errorHandle() {
    cerr << "Invalid input!" << endl;
    cerr << "./cb <input file name> <output file name>" << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) { errorHandle(); }

    string input_file = argv[1];
    string output_file = argv[2];

    Graph graph;
    graph.read(input_file);
    graph.cycleBreak();
    graph.print(output_file);
}