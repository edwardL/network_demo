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

//�����پ���
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

//��ӵ������б�
bool AStar::AddChildToOpenList(Node *parentNode)
{
	// ��ӵ�ǰ�������Χ���꣨��8 ������
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
		// �趨����ֵ
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

//�Ƿ�����ڷ���б�
bool AStar::IsClosed(int x, int y)
{
	return m_mapClose[x][y] == 1 ? true : false;
}


// �Ƿ�����ڿ����б���
bool AStar::IsInOpenList(int x, int y)
{
	return m_mapOpen[x][y] == 1 ? true : false;
}

// �Ƿ����赲����
bool AStar::IsBlock(int x, int y)
{
	int nn = m_vecPathNodes[x][y];
	return nn == 1 ? true : false;
}

// �����ĳ�㵽�յ�ĺķ�
void AStar::SetH(Node *node)
{
	node->h = GetManhadDistance(node->pt.x,node->pt.y,m_ptTarget.x,m_ptTarget.y);
}

//�������㵽B��(ĳ��)�ĺķ�
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

//��������ķ� F = G + H
void AStar::SetF(Node *node)
{
    node->f = node->g + node->h;
}

// �ӿ����б��еõ�����ֵ 
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

	Node* currentNode = new Node; // ��ǰ�ڵ�
	currentNode->parentNode = NULL;
	currentNode->pt.x = m_ptStart.x;
	currentNode->pt.y = m_ptStart.y;
	currentNode->g = 0;
	SetH(currentNode);
	SetF(currentNode);

	m_mapOpen[currentNode->pt.x][currentNode->pt.y] = 1;
	listOpen.push_front(currentNode); //�����ʼ�㵽�����б�

	bool bFind = false;

	do
	{
		currentNode = FindMinFNode(); // �ӿ����б��еõ����Žڵ�
		listClose.push_front(currentNode); // ��ӵ��ر��б�
		m_mapClose[currentNode->pt.x][currentNode->pt.y] = 1;

		if(IsTarget(currentNode->pt.x, currentNode->pt.y))
		{
			bFind = true;
			break;
		}
		bFind = AddChildToOpenList(currentNode); // �������ڽڵ���Χ�Ľڵ�
		if(listOpen.size() == 0 || bFind)
			break; // ���Ŀ��ڵ��Ѿ������ڿ����б�򿪷��б��ǿ����˳�

	}while(true);

    if(!bFind)
    {
    	printf("Ѱ· from (%d, %d) to (%d, %d) ʧ��\n", m_ptStart.x, m_ptStart.y, m_ptTarget.x, m_ptTarget.y);
    	return false;
    }

	/// �ҵ���
	do
	{
		path.push_back(currentNode->pt); // ���յ㿪ʼ
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