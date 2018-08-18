#ifndef  _MAP_GENERATOR_H_
#define  _MAP_GENERATOR_H_
#include <vector>
#include <math.h>
#include "cocos2d.h"
#include "entity/Team.h"

USING_NS_CC;

class MapGenertor {
public:
	MapGenertor(float numberOfCity, float expandFacotr)
	{
		this->numberOfCity = numberOfCity;
		this->expandFactor = expandFacotr;
		generateRandomCity();
	}

	void generateRandomCity();
	void connectNearByCity(float minConnect, float maxConnect);
	void eliminateExtraCity();

	Team myteam;
	//vector<City> cityList;
	float numberOfCity;
	float expandFactor;
};

#endif
