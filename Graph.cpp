#include "Graph.h"

void CGraph::DFS(int nVex, bool bVisited[], int &nIndex, PathList& pList)
{
	bVisited[nVex] = true;
	pList->vexs[nIndex++] = nVex;
	bool allVisited = true;
	for (int i = 0; i < m_nVexNum; i++) {
		if (bVisited[i] == false) allVisited = false;
	}
	//����Ѿ�������һ����
	if (allVisited) {
		//for (int i = 0; i < m_nVexNum; i++) {
		//	cout << pList->vexs[i] << " ";
		//}
		//cout << endl;
		//���浱ǰ·��
		PathList newPath = (Path*)malloc(sizeof(Path));
		for (int i = 0; i < nIndex-1; i++) {
			newPath->vexs[i] = pList->vexs[i];
		}
		newPath->next = pList;
		pList = newPath;
	}
	//���û�б�����һ��
	else {
		for (int i = 0; i < m_nVexNum; i++) {
			//Ȩֵ��Ϊ0��Ϊ���ڶ��� ����һ��ǰ���Ǹ��ڽӵ�δ������
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
		//��������
		return false;
	}
	m_aVexs[m_nVexNum++] = vex;
	return true;
}

bool CGraph::InsertEdge(Edge edge)
{
	if (edge.vex1 < 0 || edge.vex1 >= m_nVexNum || edge.vex2 < 0 || edge.vex2 >= m_nVexNum) {
		//�����±�Խ��
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
		//���������֮����Ȩֵ��Ϊ��һ����
		if (m_aAdjMatrix[i][v] != 0) {
			cout << getVex(v).name << "��" <<getVex(i).name << "����" << m_aAdjMatrix[i][v] << "��" << endl;
			k++;
		}
	}
	//���ص�ıߵ�����
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
	//��ʼ�����·��
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
	//ʹ��Dijkstra���·���㷨
	stack<int> nextPoints;
	//��ʼ����ջ
	nextPoints.push(nVexStart);
	//���ջ��Ϊ����ѭ���������·��
	while (!nextPoints.empty()) {
		int point = nextPoints.top();
		nextPoints.pop();
		for (int i = 0; i < m_nVexNum; i++) {
			//����õ���ڽӵ�Ϊi
			if (m_aAdjMatrix[point][i] != 0) {
				//startPoint��point�ľ������point��i�ľ���ΪstartPoint��i�ľ���
				if (m_aAdjMatrix[point][i] + Distance[point] < Distance[i]) {
					Distance[i] = m_aAdjMatrix[point][i] + Distance[point];
					isShort[i] = true;
					Pre[i] = point; //i���ǰ������Ϊpoint
					nextPoints.push(i);
				}
			}
		}
	}
	int pos = 0;
	//�ж�ĩβ��δ����ʼ��
	while (nVexEnd != nVexStart) {
		Edge edge;
		edge.vex1 = nVexEnd;
		edge.vex2 = Pre[nVexEnd];
		edge.weight = Distance[nVexEnd];
		aPath[pos++] = edge;
		nVexEnd = Pre[nVexEnd];
	}
	return pos;//����·����
}

int CGraph::FindMinTree(Edge aPath[])
{
	//ʹ��PRIM������С������
	vector<int> TE;
	//stack<int> nextPoints;
	//nextPoints.push(0);
	////��ջ��Ϊ����ѭ��������С������
	//while (!nextPoints.empty()) {
	//	int nextPoint = nextPoints.top();
	//	nextPoints.pop();
	//	int smallest = 0xfffffff;
	//	int smallest_point = -1;
	//	for (int j = 0; j < m_nVexNum; j++) {
	//		//���õ�û�б���������������Ϊ�ڽӵ�
	//		if (m_aAdjMatrix[nextPoint][j] != 0 && find(TE.begin(), TE.end(), j) == TE.end()) {
	//			if (m_aAdjMatrix[nextPoint][j] < smallest) {
	//				smallest_point = j;
	//				cout << nextPoint << " " << j << ":" << m_aAdjMatrix[nextPoint][j] << endl;
	//			}
	//		}
	//	}
	//	//��Ϊ-1������������
	//	if (smallest_point != -1) {
	//		nextPoints.push(smallest_point);
	//		TE.push_back(smallest_point);
	//	}
	//}
	TE.push_back(0);
	int pos = 0;
	//Ѱ�Һ�TE���Ͼ�����̵ĵ�
	while (TE.size() != m_nVexNum) {
		int smallest = 0xfffffff;
		int smallest_point_vex1 = -1;
		int smallest_point_vex2 = -1;
		for (int i = 0; i < TE.size(); i++) {
			int k = TE[i];//����k������TE��ĵ�
			//�������е��Ҿ�����̵ĵ�
			for (int j = 0; j < m_nVexNum; j++) {
				//���TE�в�������j�Ž�������
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
	return pos;//���رߵ�����
}
