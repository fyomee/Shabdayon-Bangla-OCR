
#include "point.h"
#include <vector>

#pragma once

using namespace std;

class ConnCompProperties
{
private:
	vector<vector<point>> Components;

public:
	ConnCompProperties(vector<vector<point>> cc);
	vector<int> getRegion(int compNumber);
	vector<vector<int>> getAllRegion();
	int getMinVal(vector<int> a);
	int getMaxVal(vector<int> a);
};
