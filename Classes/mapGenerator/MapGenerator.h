#ifndef  _MAP_GENERATOR_H_
#define  _MAP_GENERATOR_H_
#include <vector>
#include <math.h>
#include "cocos2d.h"
#include "entity/City.h"
#include "entity/Team.h"

#define _MAP_HEIGHT 20
#define _MAP_WIDTH 15
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
		connectNearByCity(2,6);
	}

	void generateRandomCity();
	void connectNearByCity(float minConnect, float maxConnect);


	vector<City*> cityList;
	City* currentCity;
	std::vector<Team*> teamlist;
	float numberOfCity;
	float expandFactor;
private:
	cocos2d::Vec2 randomLocation();
	City* generateCity(string name);
	City* findNearestCity(City* current);
	City* findNearestCity(City * current, vector<City*> list);
	int findNearestCityIndex(City* current, vector<City*> list);
	vector<City*> findNearestKCity(City* current, int k);
	bool cityDistanceSort(City* a, City* b);
	double distance(City* a, City*);

};

#endif
