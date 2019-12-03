#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "ds.hpp"
using namespace std;

BFS_Node_Queue::BFS_Node_Queue(){
	this->queue = new BFS_Node*[100];
	this->start = 0;
	this->end = 99;
	this->node_num = 0;
	this->size = 100;
}

BFS_Node_Queue::BFS_Node_Queue(int size){
	this->queue = new BFS_Node*[size];
	this->start = 0;
	this->end = size-1;
	this->node_num=0;
	this->size = size;
}

void BFS_Node_Queue::enqueue(BFS_Node* v){
	if(node_num == size){
		cout << "queue is full" << endl;
		return;
	}
	this->end = (this->end+1)%(this->size);
	this->queue[end] = v;
	this->node_num++;
}

bool BFS_Node_Queue::isEmpty() { return (this->node_num==0); }

BFS_Node* BFS_Node_Queue::dequeue(){
	if(isEmpty()){
		cout << "Queue is empty" << endl;
		return NULL;
	}
	BFS_Node* temp = queue[this->start];
	this->start = (this->start+1)%(this->size);
	this->node_num--;
	return temp;
}
