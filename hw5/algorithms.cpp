#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "algorithms.hpp"
using namespace std;

#define	WHITE	0
#define	GRAY	1
#define BLACK	2


int dfs_time = 0;

void dfs_visit(Adj_Node** adj_list, DFS_Node** vertices, int s){
	dfs_time++;
	vertices[s]->d_time = dfs_time;
	vertices[s]->color = GRAY;
	Adj_Node* v = adj_list[s];
	while(v){
		if(v && vertices[v->vertex]->color==WHITE){
			dfs_visit(adj_list, vertices, v->vertex);
			vertices[v->vertex]->pred = vertices[s];
		}
		v = v->next;
	}
	dfs_time++;
	vertices[s]->f_time = dfs_time;
	vertices[s]->color = BLACK;
}

void dfs_visualize(DFS_Node** vertices, int v_num){
	for(int i=0;i<v_num;i++){
		cout << "[Vertex #" << vertices[i]->vertex << "]\t";
		cout << "d_time: " << vertices[i]->d_time;
		cout << ", f_time: " << vertices[i]->f_time;
		if(vertices[i]->pred){
			cout << ", predecessor: Vertex #" << vertices[i]->pred->vertex << endl;
		}
		else{
			cout << ", predecessor: NIL"  << endl;
		}
	}
}

void dfs(Adj_Node** adj_list, int v_num, int e_num){
	DFS_Node** vertices = new DFS_Node*[v_num];
	// Initialize vertices array
	for(int i=0;i<v_num;i++){
		vertices[i] = (DFS_Node*)(malloc(sizeof(DFS_Node)));
		vertices[i]->vertex=i;
		vertices[i]->d_time=0;
		vertices[i]->f_time=0;
		vertices[i]->color=WHITE;
		vertices[i]->pred=NULL;
	}
	
	// Drive DFS operation
	for(int i=0;i<v_num;i++){
		if(vertices[i]->color==WHITE){
			dfs_visit(adj_list, vertices, i);
		}
	}
	dfs_time = 0;
	dfs_visualize(vertices, v_num);
	cout << endl;
}

void bfs_visit(Adj_Node** adj_list, BFS_Node** vertices, int v_num, int s){
	BFS_Node_Queue queue = BFS_Node_Queue(v_num*2);
	vertices[s]->d = 0;
	vertices[s]->color = GRAY;
	queue.enqueue(vertices[s]);
	while(!queue.isEmpty()){
		BFS_Node* u = queue.dequeue();
		vertices[u->vertex]->color = BLACK;
		Adj_Node* v = adj_list[u->vertex];
		while(v){
			if(v && vertices[v->vertex]->color==WHITE){
				vertices[v->vertex]->color = GRAY;
				vertices[v->vertex]->pred = vertices[u->vertex];
				vertices[v->vertex]->d = vertices[u->vertex]->d + 1;
				queue.enqueue(vertices[v->vertex]);
			}
			v = v->next;
		}
	}
}

void bfs_visualize(BFS_Node** vertices, int v_num){
	for(int i=0;i<v_num;i++){
		cout << "[Vertex #" << vertices[i]->vertex << "]\t";
		cout << "d: " << vertices[i]->d;
		if(vertices[i]->pred){
			cout << ", predecessor: Vertex #" << vertices[i]->pred->vertex << endl;
		}
		else{
			cout << ", predecessor: NIL"  << endl;
		}
	}
}

void bfs(Adj_Node** adj_list, int v_num, int e_num){
	BFS_Node** vertices = new BFS_Node*[v_num];
	for(int i=0;i<v_num;i++){
		vertices[i] = (BFS_Node*)(malloc(sizeof(BFS_Node)));
		vertices[i]->vertex = i;
		vertices[i]->d = -1;
		vertices[i]->color = WHITE;
		vertices[i]->pred = NULL;
	}

	for(int i=0;i<v_num;i++){
		if(vertices[i]->color==WHITE){
			bfs_visit(adj_list, vertices, v_num, i);
		}
	}
	bfs_visualize(vertices, v_num);
	cout << endl;
}

void prim_visualize(MST_Node** vertices, int v_num){
	int total_key = 0;
	for(int i=0;i<v_num;i++){
		cout << "[Vertex #" << vertices[i]->vertex << "]\t";
		cout << "key: " << vertices[i]->key;
		total_key += vertices[i]->key;
		if(vertices[i]->pred){
			cout << ", predecessor: Vertex #" << vertices[i]->pred->vertex << endl;
		}
		else{
			cout << ", predecessor: NIL"  << endl;
		}
	}
	cout << "Total key : " << total_key << endl;
}

void prim(Adj_Node** adj_list, int v_num, int e_num){
	MST_Node** vertices = new MST_Node*[v_num];
	for(int i=0;i<v_num;i++){
		vertices[i] = (MST_Node*)(malloc(sizeof(MST_Node)));
		vertices[i]->vertex = i;
		vertices[i]->key = INF;
		vertices[i]->pred = NULL;
	}
	bool in_tv[v_num];
	for(int i=0;i<v_num;i++){
		in_tv[i] = false;
	}
	int selected = 0;
	vertices[selected]->key = 0;

	int i;
	for(i=0;i<v_num;i++){
		int min_vertex;
		int min_value = INF;
		for(int j=0;j<v_num;j++){
			if(vertices[j]->key < min_value && !in_tv[j]){
				min_vertex = j;
				min_value = vertices[j]->key;
			}
		}
		selected = min_vertex;
		in_tv[selected] = true;

		Adj_Node* v = adj_list[selected];
		while(v){
			if(v->weight < vertices[v->vertex]->key && !in_tv[v->vertex]){
				vertices[v->vertex]->key = v->weight;
				vertices[v->vertex]->pred = vertices[selected];
			}
			v = v->next;
		}
		if(min_value==INF){
			break;
		}
	}
	if(i<v_num) cout << "no spanning tree" << endl << endl;
	else{
		prim_visualize(vertices, v_num);
		cout << endl;
	}
}

void dijkstra_visualize(int dist[], int pred[], int v_num, int source){
	string s = "";
	for(int i=0;i<v_num;i++){
		cout << "[Vertex #" << i << "]\t";
		if(source == i){
			cout << "Source vertex, Length of the path: 0" << endl;
		}
		else if(pred[i] >= 0){
			cout << "Shortest path: ";
			int temp = i;
			while(temp!=source){
				s = "-" + to_string(temp) + s;
				temp = pred[temp];
			}
			s = to_string(source) + s;
			cout << s;
			cout << ", Length of the path: " << dist[i] << endl;
			s = "";
		}
		else{
			cout << "No path exists" << endl;
		}
	}
	cout << endl;
}

void dijkstra(int** length, int v_num, int e_num, int source){
	int dist[v_num];
	int pred[v_num];
	bool s[v_num];
	for(int i=0;i<v_num;i++){
		dist[i] = INF;
		pred[i] = -1;
		s[i] = false;
	}
	dist[source] = 0;
	int u;
	int min_value = INF;
	for(int i=0;i<v_num;i++){
		for(int j=0;j<v_num;j++){
			if(dist[j]<min_value && !s[j]){
				min_value = dist[j];
				u = j;
			}
		}
		min_value = INF;
		s[u]=true;
		for(int w=0;w<v_num;w++){
			if(!s[w] && dist[u]+length[u][w] < dist[w]){
				dist[w] = dist[u]+length[u][w];
				pred[w] = u;
			}
		}
	}
	dijkstra_visualize(dist, pred, v_num, source);
}
