#include "Tourism.h"

void Tourism::GetSpotInfo() {
	//for (int i = 0; i < graph.m_nVexNum; i++) {
	//	Vex vex = graph.getVex(i);
	//	cout << "���:" << vex.num << "\t" << "����:" << vex.name << "\t" << "���:" << vex.desc << endl;
	//}
	//for (int i = 0; i < graph.m_nVexNum; i++) {
	//	graph.FindEdge(i);
	//}
	int k_in;
	cout << "����������Ҫ��ѯ�ľ�����:";
	cin >> k_in;
	Vex vex = graph.getVex(k_in);
	cout << "����:" << vex.name << "\t" << "���:" << vex.desc << endl;
	cout << "====================================" << endl;
	graph.FindEdge(k_in);
}

void Tourism::CreateGraph()
{
	graph.Init();//��ʼ��

	FILE* invex = fopen("Vex.txt", "r+");
	int vex_num;
	fscanf_s(invex, "%d", &vex_num);
	cout << "���ڶ���" << vex_num << "������" << endl;
	FILE* inedge = fopen("Edge.txt", "r+");
	//���ö���
	for (int i = 0; i < vex_num; i++) {
		int id;
		fscanf_s(invex, "%d", &id);
		char name[20];
		fscanf_s(invex, "%s", name, 20);
		char desc[1024];
		fscanf_s(invex, "%s", desc, 1024);
		Vex vex;
		vex.num = id;
		strcpy(vex.name, name);
		strcpy(vex.desc, desc);
		cout << "���� " << vex.num << vex.name << " -" << vex.desc << endl;
		graph.InsertVex(vex);
	}
	//���ñ�
	while (!feof(inedge)) {
		int vex1, vex2, weight;
		fscanf_s(inedge, "%d %d %d", &vex1, &vex2, &weight);
		Edge edge = { vex1,vex2,weight };
		cout << "���� " << "<v" << vex1 << ",v" << vex2 << ">:" << weight << endl;
		graph.InsertEdge(edge);
	}
	fclose(invex);
	fclose(inedge);
}

void Tourism::TravelPath()
{
	int k_in;
	cout << "����������Ҫ��ѯ�ľ�����:";
	cin >> k_in;
	PathList pList = (PathList)malloc(sizeof(Path));
	pList->next = NULL;
	graph.DFSTraverse(k_in, pList);
	pList = pList->next;//�������һ��·�����Ǵ���·����
	while (pList != NULL) {
		for (int i = 0; i < graph.m_nVexNum; i++) {
			if (i == 0) {
				cout << graph.getVex(pList->vexs[i]).name;
			}
			else {
				cout << "->" << graph.getVex(pList->vexs[i]).name;
			}
		}
		cout << endl;
		pList = pList->next;
	}
	cout << endl;
}

void Tourism::FindShortPath()
{
	int start, end;
	cout << "��������ʼ����:";
	cin >> start;
	cout << "�������յ㾰��:";
	cin >> end;
	Edge edges[SIZE * (SIZE - 1) / 2];
	int number = graph.FindShortPath(start, end, edges);
	int totalLength = edges[0].weight;
	for (int i = number-1; i >= 0; i--) {
		//�������һ����
		if (i == number-1) {
			cout << graph.getVex(edges[i].vex2).name << "->" << graph.getVex(edges[i].vex1).name;
		}
		else {
			cout << "->" << graph.getVex(edges[i].vex1).name;
		}
	}
	cout << endl;
	cout << "��·��:" << totalLength << "��" << endl;
}

void Tourism::DesignPath()
{
	Edge aPath[SIZE * (SIZE - 1) / 2];
	int number = graph.FindMinTree(aPath);
	int totalWeight = 0;
	for (int i = number - 1; i >= 0; i--) {
		cout << graph.getVex(aPath[i].vex1).name << "->" << graph.getVex(aPath[i].vex2).name << "\t" << aPath[i].weight << endl;
		totalWeight += aPath[i].weight;
	}
	cout << "�����賤��" << totalWeight << "��" << endl;
}
