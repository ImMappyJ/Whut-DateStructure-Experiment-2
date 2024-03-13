#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <bits/stdc++.h>
#define SIZE 20

using namespace std;

typedef struct Path {
	int vexs[20]; //保存一条路径
	Path* next = NULL; //保存另一条路径
} *PathList;

struct Vex {
	int num;
	char name[20];
	char desc[1024];
};

struct Edge {
	int vex1;
	int vex2;
	int weight;
};

class CGraph {
private:
	int m_aAdjMatrix[SIZE][SIZE];
	Vex m_aVexs[SIZE];
	void DFS(int nVex, bool bVisited[], int &nIndex, PathList& pList);
public:
	int m_nVexNum;
	void Init();
	Vex getVex(int n);
	bool InsertVex(Vex vex);
	bool InsertEdge(Edge edge);
	int FindEdge(int v);
	void DFSTraverse(int nVex, PathList &pList);
	int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);
	int FindMinTree(Edge aPath[]);
};
