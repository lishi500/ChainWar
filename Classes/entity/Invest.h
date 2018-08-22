#ifndef  _INVEST_H_
#define  _INVEST_H_
#include "cocos2d.h"
#include <vector>

USING_NS_CC;

//class City;


class Invest : public cocos2d::Node {
private:
	int userId;
	float amountInvested;
	float amount;
	float collectRate;
	float collectDropRate;

public:
	//City * city;

	CREATE_FUNC(Invest);
};

#endif