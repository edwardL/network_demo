#pragma once

#include <string>
#include <iostream>
using namespace std;

///https://blog.csdn.net/qq_35644234/article/details/60870719

/* ����
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

//��¼��㵽ÿ����������·����Ϣ
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


//ͼ��
class Graph {
private:
	int vexnum;	//ͼ�Ķ������
	int edge;	//ͼ�ı���
	int **arc;  //�ڽӾ���
	Dis *dis;	//���·����Ϣ����

public:
	Graph(int vexnum, int edge);
	~Graph();

	// �ж�����ıߵ���Ϣ�Ƿ�Ϸ�
	bool check_edge_value(int start, int end, int weight);
	// ����ͼ
	void createGraph();

	//�����·��
	void Dijkstra(int begin);

	void print();
	
	void print_path(int begin);
};