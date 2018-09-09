#include "MapGenerator.h"
#include "util/CityRoute.h"
#include <iostream>
#include <algorithm>


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
	
}


void MapGenertor::connectNearByCity(float minConnect, float maxConnect)
{
	vector<City*> cityListCopy(cityList.size());
	copy(cityList.begin(), cityList.end(), cityListCopy.begin());
	CityRoute cityRoute = CityRoute();

	for (size_t i = 0; i < cityList.size(); i++) {
		int numberOfConnectCity = rand() % 2 + 2;
		vector<City*> nearCity = findNearestKCity(cityList[i], numberOfConnectCity);
		cityRoute.connectCityList(cityList[i], nearCity);
	}

	std::vector<City*>::iterator cityIterator;
	/*for (cityIterator = cityList.begin(); cityIterator != cityList.end(); cityIterator++) {
		string aa = (*cityIterator)->toString();
		CCLOG("city pos:  %f,%f, connected city %d\n", (*cityIterator)->pos.x, (*cityIterator)->pos.y, (*cityIterator)->connectedCity.size());
	}*/
}

void MapGenertor::clusterCity() { // arrange team
	City* initialCity = getInitialCity();
}

City* MapGenertor::getInitialCity() { // left bottom city
	City* fakeCornerCity;
	fakeCornerCity->pos = cocos2d::Vec2(0,0);
	
	return this->findNearestCity(fakeCornerCity);
}

vector<City*> MapGenertor::findNearestKCity(City* current, int k) {
	vector<City*> topK;
	vector<City*> cityListCopy(cityList.size());
	copy(cityList.begin(), cityList.end(), cityListCopy.begin());
	cityListCopy.erase(std::remove(cityListCopy.begin(), cityListCopy.end(), current), cityListCopy.end());

	for (int i = 0; i < k; i++) {
		City* nearestCity = findNearestCity(current, cityListCopy);
		topK.push_back(nearestCity);
		cityListCopy.erase(std::remove(cityListCopy.begin(), cityListCopy.end(), nearestCity), cityListCopy.end());
	}

	return topK;
}

cocos2d::Vec2 MapGenertor::randomLocation()
{
	/*int posX = (rand() % (mapWidth - 200)) + 100;
	int posY = (rand() % (mapHeight - 150)) + 75;*/
	int posX = rand() % (this->mapWidth - 400) + 200;
	int posY = rand() % (this->mapHeight - 300) + 150;
	return cocos2d::Vec2(posX, posY);
}

City* MapGenertor::generateCity(string name)
{
	City * c = NULL;
	c = City::create();
	c->cityName = name;
	cocos2d::Vec2 point = randomLocation();
	if (cityList.size() == 0) {
		point = cocos2d::Vec2(mapWidth / 2, mapHeight / 2);
	}
	c->pos = point;
	c->isCapital = false;

	bool validPoint = false;

	while ((cityList.size() != 0) && !validPoint) {
		point = randomLocation();
		c->pos = point;
		City* nearstCity = findNearestCity(c);
		double distance = this->distance(nearstCity, c);
		if (distance <= _MAX_DISTANCE && distance >= _MIN_DISTANCE) {
			validPoint = true;
		}
	}
	

	return c;
}

City * MapGenertor::findNearestCity(City * current)
{
	return findNearestCity(current, cityList);
}

int MapGenertor::findNearestCityIndex(City * current, vector<City*> list)
{
	vector<City*>::iterator cityIterator;
	City * nearestCity = cityList.front();
	double currentNerstDistance = this->distance(nearestCity, current);
	int index = 0;
	for (cityIterator = list.begin(); cityIterator != list.end(); cityIterator++) {
		double distance = this->distance((*cityIterator), current);
		if (distance < currentNerstDistance) {
			currentNerstDistance = distance;
			nearestCity = (*cityIterator);
			index = std::distance(list.begin(), cityIterator);
		}
	}
	return index;
}


City * MapGenertor::findNearestCity(City * current, vector<City*> list) {
	 
	std::vector<City*>::iterator cityIterator;
	City * nearestCity = list.front();
	double currentNerstDistance = this->distance(nearestCity, current);
	for (cityIterator = list.begin(); cityIterator != list.end(); cityIterator++) {
		double distance = this->distance((*cityIterator), current);
		if (distance < currentNerstDistance) {
			currentNerstDistance = distance;
			nearestCity = (*cityIterator);
		}
	}
	return nearestCity;

}

double MapGenertor::distance(City * a, City * b)
{
	return sqrt(pow((a->pos.x - b->pos.x), 2) + pow((a->pos.y - b->pos.y), 2));
}





