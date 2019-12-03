#ifndef ds_hpp
#define ds_hpp

struct Adj_Node{
	int vertex;
	int weight;
	Adj_Node* next;
};

struct DFS_Node{
	int vertex;
	int d_time;
	int f_time;
	int color;
	DFS_Node* pred;
};

struct BFS_Node{
	int vertex;
	int d;
	int color;
	BFS_Node* pred;
};

struct MST_Node{
	int vertex;
	int key;
	MST_Node* pred;
};

class BFS_Node_Queue{
private:
	BFS_Node** queue;
	int start;
	int end;
	int node_num;
	int size;
public:
	BFS_Node_Queue();
	BFS_Node_Queue(int size);
	void enqueue(BFS_Node* v);
	bool isEmpty();
	BFS_Node* dequeue();
};
#endif
