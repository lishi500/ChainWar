#ifndef  _MAP_GENERATOR_H_
#define  _MAP_GENERATOR_H_
#include <vector>
#include <math.h>
#include "cocos2d.h"
#include "entity/City.h"
#include "entity/Team.h"

#define _MAP_HEIGHT 900
#define _MAP_WIDTH 1600
#define _MAX_DISTANCE 200
#define _MIN_DISTANCE 40

USING_NS_CC;

class MapGenertor {
public:
	MapGenertor(float numberOfCity, float mapWidth, float mapHeight)
	{
		this->numberOfCity = numberOfCity;
		this->mapWidth = (int)mapWidth;
		this->mapHeight = (int)mapHeight;

		//CCLOG("generate start ! total %d citys, width %d, height %d ", this->numberOfCity, this->mapWidth, this->mapHeight);

		generateRandomCity();
		connectNearByCity(4,6);
	}

	void generateRandomCity();
	void connectNearByCity(float minConnect, float maxConnect);


	vector<City*> cityList;
	std::vector<Team*> teamlist;

	float numberOfCity;
	int mapWidth;
	int mapHeight;
private:
	cocos2d::Vec2 randomLocation();
	City* generateCity(string name);
	City* findNearestCity(City* current);
	City* findNearestCity(City * current, vector<City*> list);
	int findNearestCityIndex(City* current, vector<City*> list);
	vector<City*> findNearestKCity(City* current, int k);
	double distance(City* a, City*);

	City* getInitialCity();
	void clusterCity();
};

#endif
