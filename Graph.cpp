#include "Graph.h"

void CGraph::DFS(int nVex, bool bVisited[], int &nIndex, PathList& pList)
{
	bVisited[nVex] = true;
	pList->vexs[nIndex++] = nVex;
	bool allVisited = true;
	for (int i = 0; i < m_nVexNum; i++) {
		if (bVisited[i] == false) allVisited = false;
	}
	//如果已经遍历完一次了
	if (allVisited) {
		//for (int i = 0; i < m_nVexNum; i++) {
		//	cout << pList->vexs[i] << " ";
		//}
		//cout << endl;
		//保存当前路径
		PathList newPath = (Path*)malloc(sizeof(Path));
		for (int i = 0; i < nIndex-1; i++) {
			newPath->vexs[i] = pList->vexs[i];
		}
		newPath->next = pList;
		pList = newPath;
	}
	//如果没有遍历完一次
	else {
		for (int i = 0; i < m_nVexNum; i++) {
			//权值不为0则为相邻顶点 还有一个前提是该邻接点未被访问
			if (m_aAdjMatrix[nVex][i] != 0 && bVisited[i] == false) {
				DFS(i, bVisited, nIndex, pList);
				nIndex--;
				bVisited[i] = false;
			}
		}
	}
}

void CGraph::Init()
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			this->m_aAdjMatrix[i][j] = 0;
		}
	}
	this->m_nVexNum = 0;
	for (int i = 0; i < SIZE; i++) {
		Vex vex = { 0,NULL,NULL};
		m_aVexs[i] = vex;
	}
}

Vex CGraph::getVex(int n)
{
	return m_aVexs[n];
}

bool CGraph::InsertVex(Vex vex)
{
	if (m_nVexNum == SIZE) {
		//顶点已满
		return false;
	}
	m_aVexs[m_nVexNum++] = vex;
	return true;
}

bool CGraph::InsertEdge(Edge edge)
{
	if (edge.vex1 < 0 || edge.vex1 >= m_nVexNum || edge.vex2 < 0 || edge.vex2 >= m_nVexNum) {
		//顶点下标越界
		return false;
	}
	m_aAdjMatrix[edge.vex1][edge.vex2] = edge.weight;
	m_aAdjMatrix[edge.vex2][edge.vex1] = edge.weight;
	return true;
}

int CGraph::FindEdge(int v)
{
	int k = 0;
	for (int i = 0; i < m_nVexNum; i++) {
		//如果两个点之间有权值则为有一条边
		if (m_aAdjMatrix[i][v] != 0) {
			cout << getVex(v).name << "到" <<getVex(i).name << "距离" << m_aAdjMatrix[i][v] << "米" << endl;
			k++;
		}
	}
	//返回点的边的条数
	return k;
}

void CGraph::DFSTraverse(int nVex, PathList& pList)
{
	int nIndex = 0;
	bool bVisited[SIZE] = { false };
	DFS(nVex, bVisited, nIndex, pList);
	cout << "0";
}

int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	//初始化最短路径
	int Distance[SIZE];
	int Pre[SIZE];
	bool isShort[SIZE] = { false };
	memset(Pre, -1, SIZE);
	for (int i = 0; i < m_nVexNum; i++) {
		Distance[i] = 0xfffffff;
	}
	Distance[nVexStart] = 0;
	isShort[nVexStart] = true;
	Pre[nVexStart] = nVexStart;
	//使用Dijkstra最短路径算法
	stack<int> nextPoints;
	//起始点入栈
	nextPoints.push(nVexStart);
	//如果栈不为空则循环搜索最短路径
	while (!nextPoints.empty()) {
		int point = nextPoints.top();
		nextPoints.pop();
		for (int i = 0; i < m_nVexNum; i++) {
			//如果该点的邻接点为i
			if (m_aAdjMatrix[point][i] != 0) {
				//startPoint到point的距离加上point到i的距离为startPoint到i的距离
				if (m_aAdjMatrix[point][i] + Distance[point] < Distance[i]) {
					Distance[i] = m_aAdjMatrix[point][i] + Distance[point];
					isShort[i] = true;
					Pre[i] = point; //i点的前驱点则为point
					nextPoints.push(i);
				}
			}
		}
	}
	int pos = 0;
	//判断末尾点未到初始点
	while (nVexEnd != nVexStart) {
		Edge edge;
		edge.vex1 = nVexEnd;
		edge.vex2 = Pre[nVexEnd];
		edge.weight = Distance[nVexEnd];
		aPath[pos++] = edge;
		nVexEnd = Pre[nVexEnd];
	}
	return pos;//返回路径数
}

int CGraph::FindMinTree(Edge aPath[])
{
	//使用PRIM构建最小生成树
	vector<int> TE;
	//stack<int> nextPoints;
	//nextPoints.push(0);
	////若栈不为空则循环生成最小生成树
	//while (!nextPoints.empty()) {
	//	int nextPoint = nextPoints.top();
	//	nextPoints.pop();
	//	int smallest = 0xfffffff;
	//	int smallest_point = -1;
	//	for (int j = 0; j < m_nVexNum; j++) {
	//		//若该点没有被包含进生成树且为邻接点
	//		if (m_aAdjMatrix[nextPoint][j] != 0 && find(TE.begin(), TE.end(), j) == TE.end()) {
	//			if (m_aAdjMatrix[nextPoint][j] < smallest) {
	//				smallest_point = j;
	//				cout << nextPoint << " " << j << ":" << m_aAdjMatrix[nextPoint][j] << endl;
	//			}
	//		}
	//	}
	//	//若为-1则代表遍历完了
	//	if (smallest_point != -1) {
	//		nextPoints.push(smallest_point);
	//		TE.push_back(smallest_point);
	//	}
	//}
	TE.push_back(0);
	int pos = 0;
	//寻找和TE集合距离最短的点
	while (TE.size() != m_nVexNum) {
		int smallest = 0xfffffff;
		int smallest_point_vex1 = -1;
		int smallest_point_vex2 = -1;
		for (int i = 0; i < TE.size(); i++) {
			int k = TE[i];//这里k是属于TE里的点
			//遍历所有点找距离最短的点
			for (int j = 0; j < m_nVexNum; j++) {
				//如果TE中不包含点j才进行运算
				if (find(TE.begin(), TE.end(), j) == TE.end()) {
					if (m_aAdjMatrix[k][j] > 0 && m_aAdjMatrix[k][j] < smallest) {
						smallest = m_aAdjMatrix[k][j];
						smallest_point_vex1 = k;
						smallest_point_vex2 = j;
					}
				}
			}
		}
		Edge edge;
		edge.vex1 = smallest_point_vex1;
		edge.vex2 = smallest_point_vex2;
		edge.weight = m_aAdjMatrix[edge.vex1][edge.vex2];
		aPath[pos++] = edge;
		TE.push_back(smallest_point_vex2);
	}
	return pos;//返回边的数量
}
