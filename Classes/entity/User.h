#ifndef  _USER_H_
#define  _USER_H_
#include "cocos2d.h"
#include <vector>
#include "entity/Team.h"


class User : public cocos2d::Node {
private:
	float userId;
	//vector<Team> selectedTeam;
	float totalInvested;
	float amount;
	float collectDropRate;
	Team myteam;

public:
	User::User()
	{
		this->userId = 5;
	};
};

#endif