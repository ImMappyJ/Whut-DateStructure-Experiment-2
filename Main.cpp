#include <bits/stdc++.h>
#include "Tourism.h"

using namespace std;

bool isRunning = true;

int main() {
	Tourism tourism;
	while (isRunning) {
		cout << "==========ͼ�뾰������ϵͳ==========" << endl;
		cout << "1.������������ͼ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.���ξ��㵼��" << endl;
		cout << "4.�������·��" << endl;
		cout << "5.�����·�滮" << endl;
		cout << "0.�˳�" << endl;
		int keyc;
		cout << "������������(0~5):";
		cin >> keyc;
		switch (keyc) {
		case 0:
			return 0;
		case 1:
			tourism.CreateGraph();
			break;
		case 2:
			tourism.GetSpotInfo();
			break;
		case 3:
			tourism.TravelPath();
			break;
		case 4:
			tourism.FindShortPath();
			break;
		case 5:
			tourism.DesignPath();
			break;
		default:
			break;
		}
	}
}