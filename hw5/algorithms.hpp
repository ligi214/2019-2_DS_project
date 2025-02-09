#ifndef algorithms_hpp
#define algorithms_hpp

#include "ds.hpp"

#define	INF	INT_MAX

void dfs(Adj_Node** adj_list, int v_num, int e_num);
void bfs(Adj_Node** adj_list, int v_num, int e_num, int s);
void prim(Adj_Node** adj_list, int v_nun, int e_num);
void dijkstra(int** length, int v_num, int e_num, int s);

#endif
