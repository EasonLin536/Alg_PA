#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "mps.h"
using namespace std;

void
chordMap::read(string input_file) {
    ifstream fin(input_file);
    string line;
    while(getline(fin, line)) {
        if (line == "0") { break; }
        if (_num == 0) { 
            _num = stoi(line); 
            for (int i=0;i<_num;i++) { _chordPair.push_back(0); }
            continue; 
        }

        stringstream ss(line);
        int i, j;
        ss >> i >> j;
        insert(i, j);
    }
}

void
chordMap::insert(int i, int j) {
    _chordPair[i] = j;
    _chordPair[j] = i;
}

void
chordMap::print(string output_file) {
    ofstream fout(output_file);
    fout << _outList.size() << endl;
    sort(_outList.begin(), _outList.end());
    for (int i=0;i<_outList.size();i++) {
        fout << "[" << _outList[i] << ", " << _chordPair[_outList[i]] << "]" << endl;
    }
}

void 
chordMap::findMPS() {
    // initialize _MIS
    for (int i=0;i<_num;i++) {
        vector<int> tmp;
        for (int j=0;j<_num;j++) {
            tmp.push_back(0);
        }
        _MIS.push_back(tmp);
        _trace.push_back(tmp);
    }

    MPS(0, _num-1);
    trace(0, _num-1);
}

int 
chordMap::MPS(int i, int j) {
    // If reaches end or calculated, return
    if (i >= j) { return 0; }
    if (_MIS[i][j] != 0) { return _MIS[i][j]; }

    int k = _chordPair[j];
    // case 1
    if (k > j || k < i) {
        _MIS[i][j] = MPS(i, j-1);
        _trace[i][j] = 1;
    }
    // case 2
    else if (i < k && k < j) {
        if (MPS(i, k-1)+1+MPS(k+1, j-1) > MPS(i, j-1)) {
            _MIS[i][j] = _MIS[i][k-1] + 1 + _MIS[k+1][j-1];
            _trace[i][j] = 2;
        }
        else {
            _MIS[i][j] = _MIS[i][j-1];
            _trace[i][j] = 1;
        }
    }
    // case 3
    else if (k == i) {
        _MIS[i][j] = MPS(i+1, j-1) + 1;
        _trace[i][j] = 3;
    }

    return _MIS[i][j];
}

void
chordMap::trace(int i, int j) {
    if (_trace[i][j] == 0) { return; }
    
    int k = _chordPair[j];
    if (_trace[i][j] == 1) {
        if (k == j-1) {
            _outList.push_back(k);
            trace(i, j-2);
        }
        else {            
            trace(i, j-1);
        }
    }
    else if (_trace[i][j] == 2) {
        trace(k+1, j-1);
        _outList.push_back(k);
        trace(i, k-1);
    }
    else if (_trace[i][j] == 3) {
        trace(i+1, j-1);
        _outList.push_back(i);
    }
}