#pragma once
#include <vector>
#include <math.h>
#include "../entity/City.h"
#include "cocos2d.h"
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

	vector<City> cityList;
	float numberOfCity;
	float expandFactor;
};