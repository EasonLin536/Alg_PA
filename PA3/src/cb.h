#ifndef CB_H
#define CB_H

#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Graph;
class Node;
class Edge;

class Node {
    friend class Graph;
public:
    Node(int index): _index(index), _color(0), _parent(-1) {}
private:
    int _index;
    int _color;
    int _parent;
    list<int> _adj;
};

class Edge {
    friend class Graph;
public:
    Edge(int begin, int end, int weight): _begin(begin), _end(end), _weight(weight) {}
    int getWeight() { return _weight; }
private:
    int _begin;
    int _end;
    int _weight;
};

class Graph {
public:
    Graph();
    void read(string);
    void cycleBreak();
    void print(string);

private:
    bool _directed;
    int _numOfVertice;
    vector<list<int>> _allAdj;      // Adjacency list: _adj[i] = list of vertices tha are connected with vertex i   
    vector<vector<int>> _weight;    // Weight matrix: _weight[i][j] = weight of edge(i, j)
    // vector<int> _visited;        // _visited[i] = 0: white; = 1: gray; = 2: black
    // vector<int> _parent;         // Remember predecessor

    vector<int> _set;
    vector<Edge*> _allEdge;         // All edges from input file
    vector<Edge*> _restEdge;        // Edges left after constructing MST
    vector<Node*> _allNode;

    vector<vector<int>> _cycleEdge; // Record the edges deleted
	int _totalWeight;
    void pushCycleEdge(Edge*);

    void init();                    // Initialize adjacent list and weight matrix
    void insertEdge(int, int, int); // Insert edges with weight into _weight
    
    void directMST();
    void addUpEdge();
    void initDfs();
    bool dfsCheck(int, int);        // DFS from one node to another
    bool dfs(int);

    void undirectMST();             // Perform undirectMST to undirected graph
    void makeAllSet();
    void sortEdges();
    int findSet(int);
    void unionSet(int, int);
};

#endif