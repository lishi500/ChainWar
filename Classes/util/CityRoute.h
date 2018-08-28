#ifndef  _INVEST_H_
#define  _INVEST_H_
#include "cocos2d.h"
#include <vector>
#include<iostream>
#include<queue>

#include "entity/City.h"



USING_NS_CC;
using namespace std;


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

    CityRoute::CityWrapper* fromCityWrapper;
    CityRoute::CityWrapper* toCityWrapper;


	vector<City*> findShortestRoute(City* fromCity, City* toCity);

    CityWrapper* convertToCityWrapper(City* city);
    City* converToCity(CityWrapper* cityWrapper);
    vector<CityRoute::CityWrapper*> convertToCityWrapperList(vector<City*> cityList);
    vector<City*> convertToCityList(vector<CityWrapper*> cityWrapperList);
    vector<City*> reconstructPath(CityRoute::CityWrapper* cityWrapper);
    CityRoute::CityWrapper* getNextOptimalCity( set<CityWrapper*> &openSet);

    void batchInsertToSet(vector<CityRoute::CityWrapper*> cityWrapperList, CityRoute::CityWrapper* prevCity, set<CityWrapper*> &openSet);
    void insertToSet(CityRoute::CityWrapper* cityWrapper, CityRoute::CityWrapper* prevCity, set<CityWrapper*> &openSet);

	float realDistance(City* a, City* b);
    float hDistance(CityWrapper* from, CityWrapper* to);
    float gDistance(CityWrapper* source, CityWrapper* to);
    float fDistance(CityWrapper* source, CityWrapper* current, CityWrapper* to);
    
};

#endif