#pragma once
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
	Team(string name);
};
