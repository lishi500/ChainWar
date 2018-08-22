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
    struct CityWraper {
        City* current;
        City* pre;
        City* next;
        float f;
        float g;
        float h;
    };

	vector<City*> findShortestRoute(City* fromCity, City* toCity);
    vector<CityWraper*> convertToCityWraperList(vector<City*> cityList);
    vector<City*> convertToCityList(vector<CityWraper*> cityWrapperList);
    float hDistance(CityWraper* from, CityWraper* to);
    float gDistance(CityWraper* source, CityWraper* to);
    float fDistance(CityWraper* source, CityWraper* to);
    
};

#endif