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

// �ڵ�
typedef struct _Node
{
	point pt;
	int f,g,h;
	struct _Node *parentNode; //���ڵ�
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
	bool AddChildToOpenList(Node* parent);// ��ӵ������б�
	bool AddNodeByPoint(Node *parent, int _x, int _y); //ͨ��������ӵ������б�
	bool IsClosed(int x , int y); // ������Ƿ��ڷ���б���
	bool IsInOpenList(int x, int y); // ������Ƿ��ڿ����б���
	bool IsBlock(int x , int y); //������Ƿ����赲��
	void SetH(Node* node); // �趨H �ĺķ�
	void SetG(Node* node); // �趨G �ĺķ�
	void SetF(Node* node); // �趨F �ĺķ�

	Node* FindMinFNode(); // �õ����ŵĽڵ�
	bool isPath(list<point> *path, int i, int j);

protected:
	int GetManhadDistance(int nx, int ny, int nTx, int nTy);
	int GetGVal(int nx1, int ny1, int nx2, int ny2);
	void ClearOpenCloseMap();

protected:
	list<Node*> listOpen;	//�����б�
	list<Node*> listClose;  //����б�

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