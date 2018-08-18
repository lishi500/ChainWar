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
	City::City() {
	};
	City::City(string name, cocos2d::Vec2 pos, bool isCapital)
	{
		this->name = name;
		this->pos = pos;
		this->isCapital = isCapital;
	};


	
	float resourcePool;
	vector<City> connectedCity;
	vector<Invest> investList;
	Team team;
};

