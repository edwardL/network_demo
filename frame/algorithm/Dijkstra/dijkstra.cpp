#include "dijkstra.h"

//����
Graph::Graph(int vexnum , int edge)
{
	// ��ʼ���������ͱ���
	this->vexnum = vexnum;
	this->edge = edge;

	// Ϊ�ڽӾ��󿪱ٿռ�͸���ʼֵ
	arc = new int*[this->vexnum];
	dis = new Dis[this->vexnum];
	for (int i = 0; i < this->vexnum; i++)
	{
		arc[i] = new int[this->vexnum];
		for (int k = 0; k < this->vexnum; k++)
		{
			/// �ڽӾ����ʼ��Ϊ�����
			arc[i][k] = INT_MAX;
		}
	}
}

Graph::~Graph()
{
	delete[] dis;
	for(int i = 0; i < this->vexnum; i++)
	{
		delete arc[i];
	}
	delete arc;
}

bool Graph::check_edge_value(int start, int end, int weight)
{
	if(start < 1 || end < 1 || start > vexnum || end > vexnum || weight < 0) {
		return false;
	}
	return true;
}

void Graph::createGraph()
{
	cout << "������ÿ���ߵ������ص㼰��Ȩ��" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while(count != this->edge)
	{
		cin >> start >> end >> weight;
		while(!this->check_edge_value(start , end, weight))
		{
			cout << "����ıߵ���Ϣ���Ϸ�,����������" << endl;
			cin >> start >> end >> weight;
		}
		// ���ڽӾ����϶�Ӧ�ĵ㸳ֵ
		arc[start -1][end -1 ] = weight;
		
		count++;
	}
}

void Graph::print()
{
	cout << "ͼ���ڽӾ���Ϊ��" << endl;
	int count_row = 0;
	int count_col = 0;
	while(count_row != this->vexnum) {
		count_col = 0;
		while(count_col != this->vexnum) {
			if(arc[count_row][count_col] == INT_MAX)
				cout << "��" << " ";
			else
				cout << arc[count_row][count_col] << " ";
			++count_col;
		}
		cout << endl;
		++count_row;
	}
}

void Graph::Dijkstra(int begin)
{
	//��ʼ��dis ����
	int i;
	for (i = 0; i < this->vexnum; i++) {
		dis[i].path = "v" + to_string((long long)begin) + "-->v" + to_string((long long)i);
		dis[i].value = arc[begin - 1][i];
	}

	//������㵽����·��Ϊ0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;
	//ʣ��this->vexnum-1������
	int count = 1;
	while(count != this->vexnum)
	{
		// temp ���ڱ��浱ǰdis ��������С���Ǹ��±�
		int temp = 0;
		int min = INT_MAX;
		for(i = 0; i < this->vexnum; i++)
		{
			if(!dis[i].visit && dis[i].value < min) {
				min = dis[i].value;
				temp = i;
			}
		}
		// ��temp ��Ӧ�Ķ�����뵽�Ѿ��ҵ������·���ļ�����
		dis[temp].visit = true;
		++count;

		for(i = 0; i < this->vexnum; i++)
		{
			if(!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i] < dis[i].value))
			{
				//����µõ��ı߿���Ӱ������δ���ʵĶ��㣬�͸����������·���ͳ���
				dis[i].value = dis[temp].value + arc[temp][i];
				dis[i].path = dis[temp].path + "-->v" + to_string((long long)(i + 1));
			}
		}
	}

}

void Graph::print_path(int begin)
{
	string str;
	str = "v" + to_string(long long(begin));
	cout << "��" << str << "Ϊ����ͼ�����·��Ϊ: " << endl;
	for(int i = 0; i != this->vexnum; i++)
	{
		if(dis[i].value != INT_MAX)
		{
			cout << dis[i].path << "=" << dis[i].value << endl;
		}
		else
			cout << dis[i].path << "�������·����" << endl;
	}
}