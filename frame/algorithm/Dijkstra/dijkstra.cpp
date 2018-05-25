#include "dijkstra.h"

//构造
Graph::Graph(int vexnum , int edge)
{
	// 初始化顶点数和边数
	this->vexnum = vexnum;
	this->edge = edge;

	// 为邻接矩阵开辟空间和赋初始值
	arc = new int*[this->vexnum];
	dis = new Dis[this->vexnum];
	for (int i = 0; i < this->vexnum; i++)
	{
		arc[i] = new int[this->vexnum];
		for (int k = 0; k < this->vexnum; k++)
		{
			/// 邻接矩阵初始化为无穷大
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
	cout << "请输入每条边的起点和重点及其权重" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while(count != this->edge)
	{
		cin >> start >> end >> weight;
		while(!this->check_edge_value(start , end, weight))
		{
			cout << "输入的边的信息不合法,请重新输入" << endl;
			cin >> start >> end >> weight;
		}
		// 对邻接矩阵上对应的点赋值
		arc[start -1][end -1 ] = weight;
		
		count++;
	}
}

void Graph::print()
{
	cout << "图的邻接矩阵为：" << endl;
	int count_row = 0;
	int count_col = 0;
	while(count_row != this->vexnum) {
		count_col = 0;
		while(count_col != this->vexnum) {
			if(arc[count_row][count_col] == INT_MAX)
				cout << "∞" << " ";
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
	//初始化dis 数组
	int i;
	for (i = 0; i < this->vexnum; i++) {
		dis[i].path = "v" + to_string((long long)begin) + "-->v" + to_string((long long)i);
		dis[i].value = arc[begin - 1][i];
	}

	//设置起点到起点的路径为0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;
	//剩余this->vexnum-1个顶点
	int count = 1;
	while(count != this->vexnum)
	{
		// temp 用于保存当前dis 数据中最小的那个下标
		int temp = 0;
		int min = INT_MAX;
		for(i = 0; i < this->vexnum; i++)
		{
			if(!dis[i].visit && dis[i].value < min) {
				min = dis[i].value;
				temp = i;
			}
		}
		// 把temp 对应的顶点加入到已经找到的最短路径的集合中
		dis[temp].visit = true;
		++count;

		for(i = 0; i < this->vexnum; i++)
		{
			if(!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i] < dis[i].value))
			{
				//如果新得到的边可以影响其他未访问的顶点，就更新它的最短路径和长度
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
	cout << "以" << str << "为起点的图的最短路径为: " << endl;
	for(int i = 0; i != this->vexnum; i++)
	{
		if(dis[i].value != INT_MAX)
		{
			cout << dis[i].path << "=" << dis[i].value << endl;
		}
		else
			cout << dis[i].path << "是无最短路径的" << endl;
	}
}