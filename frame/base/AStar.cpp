#include "AStar.h"

AStar::AStar(void)
{
	pcurrNode = NULL;

	m_vecPathNodes = NULL;
	m_nWidth = 0;
	m_nHeight = 0;
}

AStar::~AStar(void)
{
}

void AStar::Init(unsigned char pMapData[MAX_MMAP_SIZEX][MAX_MMAP_SIZEY], int nWidth, int nHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_vecPathNodes = new unsigned char*[m_nWidth];
	for(unsigned short i = 0; i < m_nWidth; i++)
	{
		m_vecPathNodes[i] = new unsigned char[m_nHeight];
	}

	for(unsigned short i = 0; i < m_nWidth; i++)
		for(unsigned short j = 0; i < m_nHeight; j++)
		{
			m_vecPathNodes[i][j] = pMapData[i][j];
		}

	m_mapOpen = new char*[m_nWidth];
	m_mapClose = new char*[m_nHeight];
	for(int i = 0; i < m_nWidth; i++)
	{
		m_mapOpen[i] = new char[m_nHeight];
		m_mapClose[i] = new char[m_nHeight];
	}
}

void AStar::ClearOpenCloseMap()
{
	for(int w = 0; w < m_nWidth; w++)
	{
		memset(m_mapOpen[w],0,m_nHeight);
		memset(m_mapClose[w],0,m_nHeight);
	}
}

//曼哈顿距离
int AStar::GetManhadDistance(int nx, int ny, int nTx, int nTy)
{
	return ::abs(nTx - nx) * SPEND_H + ::abs(nTy - ny) * SPEND_H;
}

void AStar::SetStartNode(int x, int y)
{
	m_ptStart.x = x;
	m_ptStart.y = y;
}

void AStar::SetEndNode(int x, int y)
{
	m_ptTarget.x = x;
	m_ptTarget.y = y;
}

//添加到开放列表
bool AStar::AddChildToOpenList(Node *parentNode)
{
	// 添加当前坐标的周围坐标（共8 个方向）
	for(int i = -1; i <= 1; i++)
		for(int j = -1; j <= 1; j++)
		{
			int nx = parentNode->pt.x + i;
			int ny = parentNode->pt.y + j;
			bool bFind = AddNodeByPoint(parentNode,nx,ny);
			if(bFind)
				return true;
		}
		return false;
}

bool AStar::AddNodeByPoint(Node *parent, int _x, int _y)
{
	if(_x < 0 || _y < 0 || _x >= m_nWidth || _y >= m_nHeight)
		return false;
	if(_x == parent->pt.x && _y == parent->pt.y)
		return false;
	if(IsBlock(_x,_y))
		return false;
	if(!IsClosed(_x,_y) && !IsInOpenList(_x,_y))
	{
		Node* sNode = new Node();
		// 设定坐标值
		sNode->pt.x = _x;
		sNode->pt.y = _y;
		sNode->parentNode = parent;
		SetG(sNode);
		SetH(sNode);
		SetF(sNode);

		bool bInsert = false;
		for(list<Node*>::iterator openIterator = listOpen.begin(); openIterator != listOpen.end(); openIterator++)
		{
			Node *pNode = *openIterator;
			if(pNode->f > sNode->f)
			{
				listOpen.insert(openIterator,sNode);
				bInsert = true;
				break;
			}
		}
		if(!bInsert)
		{
			listOpen.push_back(sNode);
		}
		m_mapOpen[_x][_y] = 1;
		if(IsTarget(sNode->pt.x, sNode->pt.y))
		{
			return true;
		}
	}
	return false;
}

//是否存在于封闭列表
bool AStar::IsClosed(int x, int y)
{
	return m_mapClose[x][y] == 1 ? true : false;
}


// 是否存在于开放列表中
bool AStar::IsInOpenList(int x, int y)
{
	return m_mapOpen[x][y] == 1 ? true : false;
}

// 是否是阻挡坐标
bool AStar::IsBlock(int x, int y)
{
	int nn = m_vecPathNodes[x][y];
	return nn == 1 ? true : false;
}

// 计算从某点到终点的耗费
void AStar::SetH(Node *node)
{
	node->h = GetManhadDistance(node->pt.x,node->pt.y,m_ptTarget.x,m_ptTarget.y);
}

//计算从起点到B点(某点)的耗费
int	AStar::GetGVal(int nx1, int ny1, int nx2, int ny2)
{
	if(nx1 == nx2 && ny1 == ny2)
		return 0;

	int nXdis = 0;
	int nYdis = 0;

	nXdis =::abs(nx2 - nx1);
	nYdis =::abs(ny2 - ny1);

	if(nXdis > 0 && nYdis > 0)
		return SPEND_G_FAR;
	else
		return SPEND_G_NEAR;
}

void AStar::SetG(Node *node)
{
	node->g = node->parentNode->g + GetGVal(node->pt.x, node->pt.y, node->parentNode->pt.x, node->parentNode->pt.y);
    if(node->pt.x != node->parentNode->pt.x && node->pt.y != node->parentNode->pt.y)
    	node->g = node->parentNode->g + SPEND_G_FAR;
    else
    	node->g = node->parentNode->g + SPEND_G_NEAR;
}

//计算总体耗费 F = G + H
void AStar::SetF(Node *node)
{
    node->f = node->g + node->h;
}

// 从开放列表中得到最优值 
Node* AStar::FindMinFNode()
{
	if(listOpen.size() == 0)
		return NULL;

	Node* pNode = listOpen.front();
	listOpen.pop_front();

	m_mapOpen[pNode->pt.x][pNode->pt.y] = 0;

	return pNode;
}

bool AStar::Search(list<point>& path)
{
	ClearOpenCloseMap();

	Node* currentNode = new Node; // 当前节点
	currentNode->parentNode = NULL;
	currentNode->pt.x = m_ptStart.x;
	currentNode->pt.y = m_ptStart.y;
	currentNode->g = 0;
	SetH(currentNode);
	SetF(currentNode);

	m_mapOpen[currentNode->pt.x][currentNode->pt.y] = 1;
	listOpen.push_front(currentNode); //添加起始点到开放列表

	bool bFind = false;

	do
	{
		currentNode = FindMinFNode(); // 从开放列表中得到最优节点
		listClose.push_front(currentNode); // 添加到关闭列表
		m_mapClose[currentNode->pt.x][currentNode->pt.y] = 1;

		if(IsTarget(currentNode->pt.x, currentNode->pt.y))
		{
			bFind = true;
			break;
		}
		bFind = AddChildToOpenList(currentNode); // 遍历当期节点周围的节点
		if(listOpen.size() == 0 || bFind)
			break; // 如果目标节点已经存在于开放列表或开放列表是空则退出

	}while(true);

    if(!bFind)
    {
    	printf("寻路 from (%d, %d) to (%d, %d) 失败\n", m_ptStart.x, m_ptStart.y, m_ptTarget.x, m_ptTarget.y);
    	return false;
    }

	/// 找到了
	do
	{
		path.push_back(currentNode->pt); // 从终点开始
		if(currentNode->pt.x == m_ptStart.x && currentNode->pt.y == m_ptStart.y)
			break;
		currentNode = currentNode->parentNode;

	}while(true);

	/// delete node
	for(list<Node*>::iterator it = listOpen.begin(); it != listOpen.end(); it++)
	{
		Node* node = *it;
		delete node;
	}
	listOpen.clear();

	for(list<Node*>::iterator it = listClose.begin(); it != listClose.end(); it++)
	{
		Node* node = *it;
		delete node;
	}
	listClose.clear();

	return true;

}