#ifndef ASTARFINDPATH_H
#define ASTARFINDPATH_H

#include "base/heap.h"
#include <vector>

namespace AStar
{
	struct Point{
		Point():x(0),y(0){}
		Point(int _x , int _y):x(_x),y(_y){}
		int x;
		int y;
	};
	typedef std::vector<Point> PointVec;
}

class AStarFindPath
{
public:
	AStarFindPath();
	~AStarFindPath();

	bool Init(const void * mem_mask, int mask_width , int mask_width);
	bool FindWay(const AStar::Point &start, const AStar::Point &end);
	void GenerateInflexPoint(AStar::PointVec *inflex_points , float range = 0.0);
	void Clear();

private:
	enum ASTAR_DIR
	{
		DIR_S = 0,
		DIR_LU,
		DIR_U,
		DIR_L,
		DIR_RESERVED,
		DIR_R,
		DIR_LD,
		DIR_D,
		DIR_RD,
		DIR_Count,
	};

	struct PointInfo
	{
		int x;
		int y;
		bool block;	// 当前点已经找到了，关闭列表标识
		int g;
		int h;
		PointInfo *parent;
		int dir;		/// 当前点与parent 的方向
	};

	// 开放列表项
	struct OpenItem
	{
		OpenItem():x(0),y(0),f(0){}
		OpenItem(int _x , int _y , int _f):x(_x),y(_y),f(_f){}
		int x;
		int y;
		int f; // 当前点的g + h
		bool operator<(const OpenItem &v)const
		{
			return f < v.f;
		}
	};

	void CalcWeight();

	int CalH(int pox_x , int pos_y);

	int m_mask_width;
	int m_mask_height;
	
	PointInfo **m_map;
	
	Heap<OpenItem> m_open_list;

};

#endif