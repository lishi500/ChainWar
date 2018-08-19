#ifndef  _TEAM_H_
#define  _TEAM_H_
#include "cocos2d.h"
#include <string> 

using namespace std;
USING_NS_CC;

class Team : public cocos2d::Node {
private:
public:

	CREATE_FUNC(Team);

	string teamName;
	float totalMember;
	float amount; // current total invest 

	void setTeamName(string name);
	string getTeamName();

};

#endif