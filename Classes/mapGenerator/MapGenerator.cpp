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
		CCLOG("city name --- - :  %s \n", &cityList[i]->cityName);
		currentCity = cityList[i];
		int numberOfConnectCity = rand() % 2 + 2;
		vector<City*> nearCity = findNearestKCity(cityList[i], numberOfConnectCity);
		currentCity->connectedCity = nearCity;
		cityRoute.connectCityList(currentCity, &nearCity);
		
		CCLOG("nearst city name --- - :  %s \n", &cityListCopy[1]->cityName);
	}

	std::vector<City*>::iterator cityIterator;
	for (cityIterator = cityList.begin(); cityIterator != cityList.end(); cityIterator++) {
		string aa = (*cityIterator)->toString();
		CCLOG("city pos:  %f,%f, connected city %d\n", (*cityIterator)->pos.x, (*cityIterator)->pos.y, (*cityIterator)->connectedCity.size());
	}
}

void MapGenertor::clusterCity() { // arrange team
	City* initialCity = getInitialCity();


}

City* MapGenertor::getInitialCity() { // left bottom city
	City* fakeCornerCity;
	fakeCornerCity->pos = cocos2d::Vec2(0,0);
	
	return findNearestCity(fakeCornerCity);
}

vector<City*> MapGenertor::findNearestKCity(City* current, int k) {
	vector<City*> cityListCopy(cityList.size());
	copy(cityList.begin(), cityList.end(), cityListCopy.begin());

	for (int i = 0; i < k; i++) {
		//CCLOG("city name --- - :  %s \n", &cityList[i]->cityName);
		vector<City*> cityListTemp(cityList.size() - i);
		copy(cityListCopy.begin() + i, cityListCopy.end(), cityListTemp.begin());

		currentCity = cityList[i];
		int index = findNearestCityIndex(current, cityListTemp);
		iter_swap(cityListCopy.begin() + i, cityListCopy.begin() + i + index);

	}

	vector<City*> topK(k);
	copy(cityListCopy.begin() + 1, cityListCopy.begin() + k, topK.begin());
	return topK;
}

cocos2d::Vec2 MapGenertor::randomLocation()
{
	int posX = rand() % _MAP_WIDTH;
	int posY = rand() % _MAP_HEIGHT;
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
	City * nearestCity = cityList.front();
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

bool MapGenertor::cityDistanceSort(City * a, City * b)
{
	return distance(a, currentCity) > distance(b, currentCity);
}

double MapGenertor::distance(City * a, City * b)
{
	return sqrt(pow((a->pos.x - b->pos.x), 2) + pow((a->pos.y - b->pos.y), 2));
}





