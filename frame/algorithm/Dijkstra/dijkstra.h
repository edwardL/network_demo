#pragma once

#include <string>
#include <iostream>
using namespace std;

///https://blog.csdn.net/qq_35644234/article/details/60870719

/* 输入
6 8
1 3 10
1 5 30
1 6 100
2 3 5
3 4 50
4 6 10
5 6 60
5 4 20
*/

//记录起点到每个顶点的最短路径信息
struct Dis {
	string path;
	int value;
	bool visit;
	Dis() {
		visit = false;
		value = 0;
		path = "";
	}
};


//图类
class Graph {
private:
	int vexnum;	//图的顶点个数
	int edge;	//图的边数
	int **arc;  //邻接矩阵
	Dis *dis;	//最短路径信息数组

public:
	Graph(int vexnum, int edge);
	~Graph();

	// 判断输入的边的信息是否合法
	bool check_edge_value(int start, int end, int weight);
	// 创建图
	void createGraph();

	//求最短路径
	void Dijkstra(int begin);

	void print();
	
	void print_path(int begin);
};