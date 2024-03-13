#include <bits/stdc++.h>
#include "Tourism.h"

using namespace std;

bool isRunning = true;

int main() {
	Tourism tourism;
	while (isRunning) {
		cout << "==========图与景区管理系统==========" << endl;
		cout << "1.创建景区景点图" << endl;
		cout << "2.查询景点信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;
		int keyc;
		cout << "请输入操作编号(0~5):";
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