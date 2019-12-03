#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include "algorithms.hpp"
#include "ds.hpp"
using namespace std;

Adj_Node** directed_adj_list = NULL;
Adj_Node** undirected_adj_list = NULL;

int main(){
	int x;
	ifstream inFile("./input.txt");
	if(!inFile){
		cerr << "Unable to open the input file";
		exit(1);
	}
	int v_num, e_num;
	inFile >> v_num;
	inFile >> e_num;

	directed_adj_list = new Adj_Node* [v_num];
	undirected_adj_list = new Adj_Node* [v_num];
	for(int i=0;i<v_num;i++){
		directed_adj_list[i]=NULL;
		undirected_adj_list[i]=NULL;
	}

	int w, u, v;
	string line;
	getline(inFile, line);
	int edge = 0;

	while(getline(inFile, line, ',')){
		w = stoi(line);
		getline(inFile, line, ',');
		u = stoi(line);
		getline(inFile, line, '\n');
		v = stoi(line);

		Adj_Node* new_node = new Adj_Node;
		new_node->vertex = v;
		new_node->weight = w;
		new_node->next = directed_adj_list[u];
		directed_adj_list[u] = new_node;

		Adj_Node* new_node_1 = new Adj_Node;
		new_node_1->vertex = v;
		new_node_1->weight = w;
		new_node_1->next = undirected_adj_list[u];
		undirected_adj_list[u] = new_node_1;

		Adj_Node* new_node_2 = new Adj_Node;
		new_node_2->vertex = u;
		new_node_2->weight = w;
		new_node_2->next = undirected_adj_list[v];
		undirected_adj_list[v] = new_node_2;

		edge++;
	}
	if(edge!=e_num) cout << "error: edge number does not match" << endl;

	// 1. Input adjacency list is directed
	cout << "======================================" << endl;
	cout << " First case : Given graph is directed " << endl;
	cout << "======================================" << endl;
	// Q1. DFS Algorithm
	dfs(directed_adj_list, v_num, e_num);
	// Q2. BFS Algorithm
	bfs(directed_adj_list, v_num, e_num);

	// 2. Input adjacency list is undirected
	cout << endl << endl << "=======================================" << endl;
	cout << "Second case : Given graph is undirected" << endl;
	cout << "=======================================" << endl;
	dfs(undirected_adj_list, v_num, e_num);
	bfs(undirected_adj_list, v_num, e_num);
	prim(undirected_adj_list, v_num, e_num);

	return 0;	
}
