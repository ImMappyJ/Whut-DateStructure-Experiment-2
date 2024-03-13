#pragma once
#include "Graph.h"
#include <bits/stdc++.h>

using namespace std;

class Tourism {
private:
	CGraph graph;
public:
	void GetSpotInfo();
	void CreateGraph();
	void TravelPath();
	void FindShortPath();
	void DesignPath();
};