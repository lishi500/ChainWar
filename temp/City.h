#pragma once
#include "cocos2d.h"
#include <vector>
#include "entity/Invest.h"
#include "entity/Team.h"
#include <string> 

using namespace std;

class City : public cocos2d::Node {
private: 
	string name;
	cocos2d::Vec2 pos;
	bool isCapital;

public:
	City();
	City(string name, cocos2d::Vec2 pos, bool isCapital);

	
	float resourcePool;
	vector<City> connectedCity;
	vector<Invest> investList;
	Team team;
};

