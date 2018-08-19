#ifndef  _MAP_GENERATOR_H_
#define  _MAP_GENERATOR_H_
#include <vector>
#include <math.h>
#include "cocos2d.h"
#include "entity/City.h"
#include "entity/Team.h"

#define _MAP_HEIGHT 50
#define _MAP_WIDTH 40
#define _MAX_DISTANCE 5
#define _MIN_DISTANCE 3

USING_NS_CC;

class MapGenertor {
public:
	MapGenertor(float numberOfCity, float expandFacotr)
	{
		this->numberOfCity = numberOfCity;
		this->expandFactor = expandFacotr;
		generateRandomCity();
		eliminateExtraCity();
		connectNearByCity(2,6);
	}

	void generateRandomCity();
	void connectNearByCity(float minConnect, float maxConnect);
	void eliminateExtraCity();


	


	vector<City*> cityList;
	City* currentCity;
	std::vector<Team*> teamlist;
	float numberOfCity;
	float expandFactor;
private:
	cocos2d::Vec2 randomLocation();
	City* generateCity(string name);
	City* findNearestCity(City* current);
	bool cityDistanceSort(City* a, City* b);
	double distance(City* a, City*);

};

#endif
