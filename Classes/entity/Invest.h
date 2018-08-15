#pragma once
#include "cocos2d.h"
#include <vector>
#include "User.h"


class Invest : public cocos2d::Node {
private:
	User user;
	float amountInvested;
	float amount;
	float collectRate;
	float collectDropRate;
	Team team;
public:
	Invest(User user);


	float resourcePool;
	vector<City> connectedCity;
	vector<Invest> investList;
};
