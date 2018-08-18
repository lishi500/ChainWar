#pragma once
#include "cocos2d.h"
#include <vector>
#include "entity/User.h"
//#include "entity/City.h"
#include "entity/Team.h"


class Invest : public cocos2d::Node {
private:
	User *user;
	float amountInvested;
	float amount;
	float collectRate;
	float collectDropRate;
	Team team;
public:
	Invest::Invest() {
	};
	Invest::Invest(User *user)
	{
		this->user = user;
	};



	float resourcePool;
	//vector<City> connectedCity;
	vector<Invest> investList;
};
