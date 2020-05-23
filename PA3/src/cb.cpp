#include <iostream>
#include <fstream>
#include <algorithm>
#include "cb.h"
using namespace std;

Graph::Graph() {
	_directed = false;
	_numOfVertice = 0;
	_totalWeight = 0;
}

void
Graph::read(string input_file) {
	ifstream fin(input_file);

	// Read in graph parameters
	string line;
	fin >> line;
	if (line == "u") { _directed = false; }
	else { _directed = true; }
	fin >> _numOfVertice;
	init();
	
	// Construct adjacent matrix
	int edge; fin >> edge;
	for (int i=0;i<edge;i++) {
		int vertex_1, vertex_2, weight;
		fin >> vertex_1 >> vertex_2 >> weight;
		insertEdge(vertex_1, vertex_2, weight);
	}
}

void
Graph::init() {
	// Initialize all private lists and matrices
	vector<int> tmp;
	list<int> initList;
	for (int i=0;i<_numOfVertice;i++) { 
		_allAdj.push_back(initList);
		_allNode.push_back(new Node(i));	// Construct all nodes
		
		tmp.push_back(INT32_MIN);
	}
	// for (int i=0;i<_numOfVertice;i++) { init.push_back(INT32_MIN); }
	for (int i=0;i<_numOfVertice;i++) { _weight.push_back(tmp); }
}

void
Graph::insertEdge(int i, int j, int w) {
	if (_directed) {
		_allEdge.push_back(new Edge(i, j, w));
		// _allAdj[i].push_back(j);
		// _weight[i][j] = w; 
	}
	else {
		_allEdge.push_back(new Edge(i, j, w));
	}
}

void
Graph::cycleBreak() {
	if (_directed) {
		directMST();
		addUpEdge();
	}
	else { undirectMST(); }
}

void
Graph::directMST() {
	makeAllSet();
	sortEdges();

	for (int i=_allEdge.size()-1;i>=0;i--) {
		Edge* currEdge = _allEdge[i];
		int u = currEdge->_begin, v = currEdge->_end;

		if (findSet(u) != findSet(v)) {
			unionSet(u, v);
			Node* node = _allNode[u];
			node->_adj.push_back(v);
		}
		else {
			_restEdge.push_back(currEdge);
		}
	}
}

void
Graph::addUpEdge() {
	for (int i=0;i<_restEdge.size();i++) {
		Edge* currEdge = _restEdge[i];
		int u = currEdge->_begin, v = currEdge->_end;
		
		if (currEdge->_weight < 0) { 
			pushCycleEdge(currEdge);
			continue; 
		}

		initDfs();
		// If its ok to add the edge
		if (dfsCheck(u, v)) { _allNode[u]->_adj.push_back(v); }
		// If it causes a cycle
		else { pushCycleEdge(currEdge); }
	}
}

void
Graph::initDfs() {
	for (int i=0;i<_numOfVertice;i++) {	_allNode[i]->_color = 0; }
}

// Return true if its ok to add the edge, return false if it causes a cycle
bool
Graph::dfsCheck(int u, int v) {
	_allNode[u]->_color = 1;
	if (!dfs(v)) { return false; }
	else { return true; }
}

bool
Graph::dfs(int u) {
	Node* node = _allNode[u];
	
	node->_color = 1;

	list<int>::iterator it=node->_adj.begin();
	for (;it!=node->_adj.end();it++) {
		Node* successor = _allNode[*it];
		// If successor is white
		if (successor->_color == 0) {
			// If a cycle is detected -> return false to restart dfs
			if (!dfs(successor->_index)) { return false; }
		}
		// If successor is gray -> cycle detected
		else if (successor->_color == 1) { return false; }
	}

	node->_color = 2;

	return true;
}

void
Graph::undirectMST() {
	makeAllSet();
	sortEdges();
	
	while (!_allEdge.empty()) {
		Edge* currEdge = _allEdge.back();
		int u = currEdge->_begin, v = currEdge->_end;
		_allEdge.pop_back();

		if (findSet(u) != findSet(v)) { unionSet(u, v); }

		else { pushCycleEdge(currEdge); }
	}
}

void
Graph::makeAllSet() {
	for (int i=0;i<_numOfVertice;i++) {
		_set.push_back(-1);
	}
}

bool compare(Edge* a, Edge* b) { return a->getWeight() < b->getWeight(); }

void
Graph::sortEdges() {
	sort(_allEdge.begin(), _allEdge.end(), compare);
}

// Returns representative of the set
int
Graph::findSet(int u) {
	int root = u;
	while (_set[root] >= 0) { root = _set[root]; }
	while (u != root) { 
		int p = _set[u];
		_set[u] = root;
		u = p;
	}
	return root;
}

void
Graph::unionSet(int u, int v) {
	int root1 = findSet(u), root2 = findSet(v);
	if (_set[root1] < _set[root2]) {
		_set[root1] += _set[root2];
		_set[root2] = root1;
	}
	else {
		_set[root2] += _set[root1];
		_set[root1] = root2;
	}
}

void
Graph::pushCycleEdge(Edge* edge) {
	vector<int> tmp{ edge->_begin, edge->_end, edge->_weight };
	_cycleEdge.push_back(tmp);
	_totalWeight += edge->_weight;
}

void
Graph::print(string output_file) {
	ofstream fout(output_file);
	fout << _totalWeight << endl;
	for (int i=0;i<_cycleEdge.size();i++) {
		for (int j=0;j<3;j++) {
			fout << _cycleEdge[i][j] << " ";
		}
		fout << "\n";
	}
}