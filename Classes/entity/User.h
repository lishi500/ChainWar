#ifndef  _USER_H_
#define  _USER_H_
#include "cocos2d.h"
#include <vector>
#include "entity/Team.h"

USING_NS_CC;

class User : public cocos2d::Node {
private:
	float userId;
	vector<Team> selectedTeam;
	float totalInvested;
	float amount;
	float collectDropRate;
	Team myteam;

public:
	CREATE_FUNC(User);

};

#endif