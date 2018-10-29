#ifndef _A_STAR_H
#define _A_STAR_H

#include<iostream>
using namespace std;
#include<list>

#define MAX_MMAP_SIZEX 400
#define MAX_MMAP_SIZEY 400

typedef struct _point
{
	int x;
	int y;
	_point()
	{
		x = 0;
		y = 0;
	}
	_point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
}point;

// 节点
typedef struct _Node
{
	point pt;
	int f,g,h;
	struct _Node *parentNode; //父节点
}Node;

class AStar
{
public:
	AStar();
	~AStar();
public:
	static const int SPEND_H = 10;
	static const int SPEND_G_FAR = 14;
	static const int SPEND_G_NEAR = 10;

	void Init(unsigned char pMapData[MAX_MMAP_SIZEX][MAX_MMAP_SIZEY], int nWidth , int nHeight);
	void SetMapWidth(int nWidth);
	void SetMapHeight(int nHeight);

public:
	void SetStartNode(int x, int y);
	void SetEndNode(int x, int y);

	bool IsTarget(int x , int y) const
	{
		if(x == m_ptTarget.x && y == m_ptTarget.y)
			return true;
		return false;
	}
	bool Search(list<point>& path);
	bool AddChildToOpenList(Node* parent);// 添加到开放列表
	bool AddNodeByPoint(Node *parent, int _x, int _y); //通过坐标添加到开放列表
	bool IsClosed(int x , int y); // 坐标点是否在封闭列表中
	bool IsInOpenList(int x, int y); // 坐标点是否在开放列表中
	bool IsBlock(int x , int y); //坐标点是否是阻挡点
	void SetH(Node* node); // 设定H 的耗费
	void SetG(Node* node); // 设定G 的耗费
	void SetF(Node* node); // 设定F 的耗费

	Node* FindMinFNode(); // 得到最优的节点
	bool isPath(list<point> *path, int i, int j);

protected:
	int GetManhadDistance(int nx, int ny, int nTx, int nTy);
	int GetGVal(int nx1, int ny1, int nx2, int ny2);
	void ClearOpenCloseMap();

protected:
	list<Node*> listOpen;	//开放列表
	list<Node*> listClose;  //封闭列表

	point m_ptStart;
	point m_ptTarget;

	char** m_mapOpen;
	char** m_mapClose;

	Node* pcurrNode;

	/// map data
	unsigned char** m_vecPathNodes;
	int m_nWidth;
	int m_nHeight;
};




#endif