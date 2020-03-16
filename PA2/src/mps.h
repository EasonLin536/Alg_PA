#ifndef _MPS_H
#define _MPS_H

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class chordMap;

class chordMap 
{
    public:
        chordMap() {};
        void read(string);                  // Read in .in file
        void findMPS();                     // Recurrsively call MPS to find maximum planar subset
        void print(string);                 // Print MPS to .out file
    private:
        // Private functions
        void insert(int, int);              // Push chord into _chordPair
        int MPS(int, int);                  // Find the MPS at [i][j]
        void trace(int, int);               // Trace back to find the chords that leads to MPS

        // Private data member
        int _num = 0;
        vector<int> _chordPair;
        vector<vector<int>> _MIS;
        vector<vector<int>> _trace;
        vector<int> _outList;
};

#endif