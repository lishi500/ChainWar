#pragma once
#include "cocos2d.h"
#include <vector>
#include "Team.h"


class User : public cocos2d::Node {
private:
	float userId;
	vector<Team> selectedTeam;
	float totalInvested;
	float amount;
	float collectDropRate;
	Team team;
public:
	User(float userId);

};

