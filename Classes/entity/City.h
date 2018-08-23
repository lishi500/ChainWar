#ifndef _CITY_H_
#define _CITY_H_

#include "cocos2d.h"
#include <vector>
#include <string> 

// #include "entity/Invest.h"
#include "entity/Team.h"
#include "entity/User.h"

using namespace std;
USING_NS_CC;

class City : public cocos2d::Node {
private: 

public:
	CREATE_FUNC(City);

	string cityName;
	cocos2d::Vec2 pos;
	bool isCapital;

	float resourcePool;
	vector<City*> connectedCity;
	// vector<Invest> investList;
	Team team;

	string toString();

};
#endif // !_CITY_H_

