#ifndef  _INVEST_H_
#define  _INVEST_H_
#include "cocos2d.h"
#include <vector>
#include<iostream>
#include<queue>

#include "entity/City.h"

using namespace std;

USING_NS_CC;



class CityRoute {
public:
    struct CityWrapper {
        City* city;
        CityWrapper* prev;
        CityWrapper* next;
        float f;
        float g;
        float h;
    };

	vector<City*> findShortestRoute(City* fromCity, City* toCity);
    CityWrapper* convertToCityWrapper(City* city);
    City* converToCity(CityWrapper* cityWrapper);
    vector<CityRoute::CityWrapper*> convertToCityWrapperList(vector<City*> cityList);
    vector<City*> convertToCityList(vector<CityWrapper*> cityWrapperList);

	float realDistance(City* a, City* b);
    float hDistance(CityWrapper* from, CityWrapper* to);
    float gDistance(CityWrapper* source, CityWrapper* to);
    float fDistance(CityWrapper* source, CityWrapper* current, CityWrapper* to);
    
};

#endif