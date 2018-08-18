#ifndef  _TEAM_H_
#define  _TEAM_H_
#include "cocos2d.h"
#include <string> 

using namespace std;

class Team : public cocos2d::Node {
private:
	string name;
	float totalMember;
	float totalInvest; // initial invest
	float amount; // current total invest 

public:
	Team::Team() {};
	Team::Team(string name)
	{
		this->name = name;
	};

};

#endif