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
int** weights = NULL;

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
	weights = new int*[v_num];
	for(int i=0;i<v_num;i++){
		directed_adj_list[i]=NULL;
		undirected_adj_list[i]=NULL;
		weights[i] = new int[v_num];
	}

	for(int i=0;i<v_num;i++){
		for(int j=0;j<v_num;j++){
			if(i!=j) weights[i][j] = INF;
			else weights[i][j] = 0;
		}
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

		weights[u][v] = w;

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
	if(edge!=e_num){
		cout << "error: edge number does not match" << endl;
		exit(1);
	}
	
	int question_num;
	while(1){
		cout << "Select question number that you want to look up the answer" << endl;
		cout << "1. Depth First Search" << endl;
		cout << "2. Breadth First Search" << endl;
		cout << "3. Minimum Spanning Tree" << endl;
		cout << "4. Single Source Shortest Path" << endl;
		cout << "5. Exit from the program (not given question)" << endl;
		cout << "Input : ";
		cin >> question_num;
		cout << endl;

		switch(question_num)
		{
			case 1:
				// Q1. DFS Algorithm
				cout << "Question #1. Depth First Search algorithm" << endl;
				dfs(undirected_adj_list, v_num, e_num);
				break;
			case 2:
				cout << "Question #2. Breadth First Search algorithm" << endl;
				bfs(undirected_adj_list, v_num, e_num);
				break;
			case 3:
				cout << "Question #3. Minimum Spanning Tree algorithm" << endl;
				prim(undirected_adj_list, v_num, e_num);
				break;
			case 4:
				// Q4. Dijkstra Algorithm (Shortest path)
				int source;
				cout << "Question #4. Single Source Shortest Path algorithm" << endl;
				cout << "Input source vertex num : ";
				cin >> source;
				cout << endl;
				if(source >= v_num){
					cout << "Given source vertex is out of range!" << endl;
				}
				else {
					dijkstra(weights, v_num, e_num, source);
				}
				break;
			case 5:
				exit(1);
			default:
				cout << "Wrong Question Number" << endl << endl;
		}
	}


	return 0;	
}
