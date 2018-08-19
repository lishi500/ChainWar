#include "MapGenerator.h"
#include <iostream>

USING_NS_CC;
using namespace std;

void MapGenertor::generateRandomCity()
{
	CCLOG("generate start ! %s", this->numberOfCity);
	srand((unsigned)time(0));

	for (int i = 0; i < this->numberOfCity; i++) {
		string name;
		name.append("city ");
		name.append(to_string(i));

		City* c = generateCity(name);
		
		cityList.push_back(c);
	}

	CCLOG("generate start !!!!!!! %d", cityList.size());

	std::vector<City*>::iterator cityIterator;
	for (cityIterator = cityList.begin(); cityIterator != cityList.end(); cityIterator++) {
		string aa = (*cityIterator)->toString();
		CCLOG("city pos:  %f,%f\n", (*cityIterator)->pos.x, (*cityIterator)->pos.y);


	}
}

void MapGenertor::eliminateExtraCity()
{
}

void MapGenertor::connectNearByCity(float minConnect, float maxConnect)
{
}


cocos2d::Vec2 MapGenertor::randomLocation()
{
	int posX = rand() % _MAP_WIDTH;
	int posY = rand() % _MAP_HEIGHT;
	CCLOG("city pos:  %d,%d\n", posX, posY);
	return cocos2d::Vec2(posX, posY);
}

City* MapGenertor::generateCity(string name)
{
	City * c = NULL;
	c = City::create();
	c->cityName = name;
	cocos2d::Vec2 point = randomLocation();
	c->pos = point;
	c->isCapital = false;
	currentCity = c;

	bool validPoint = false;

	while ((cityList.size() != 0) && !validPoint) {
		point = randomLocation();
		City* nearstCity = findNearestCity(c);
		double distance = this->distance(nearstCity, c);
		if (distance <= _MAX_DISTANCE || distance >= _MIN_DISTANCE) {
			validPoint = true;
		}
	}
	

	return c;
}

City * MapGenertor::findNearestCity(City * current)
{
	std::vector<City*>::iterator cityIterator;
	City * nearestCity = cityList.front();
	double currentNerstDistance = this->distance(nearestCity, current);
	for (cityIterator = cityList.begin(); cityIterator != cityList.end(); cityIterator++) {
		double distance = this->distance((*cityIterator), current);
		if (distance < currentNerstDistance) {
			currentNerstDistance = distance;
			nearestCity = (*cityIterator);
		}
	}
	return nearestCity;
}

bool MapGenertor::cityDistanceSort(City * a, City * b)
{
	return distance(a, currentCity) > distance(b, currentCity);
}

double MapGenertor::distance(City * a, City * b)
{
	return sqrt(pow((a->pos.x - b->pos.x), 2) + pow((a->pos.y - b->pos.y), 2));
}





