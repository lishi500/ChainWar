#include "CityRoute.h"

struct cmp
{
    bool operator()(CityWrapper* a, CityWrapper* b) {
        return a->f < b->f;
    }
};


vector<City*> CityRoute::findShortestRoute(City* fromCity, City* toCity) {
    CityWrapper* fromCityWrapper = convertToCityWrapper(fromCity);
    CityWrapper* toCityWrapper = convertToCityWrapper(toCity);

    priority_queue<CityWrapper*, vector<CityWrapper*>,cmp > openQueue;
    vector<CityWrapper* > closeSet;
}


/* city <--> cityWrapper converter */
CityWrapper* convertToCityWrapper(City* city) {
    CityWrapper* cityWrapper;
    cityWrapper.city = city;
    cityWrapper.prev = NULL;
    cityWrapper.next = NULL;

    return cityWrapper;
}

City* converToCity(CityWrapper* cityWrapper) {
    return cityWrapper.city;
}

vector<City*> CityRoute::convertToCityList(vector<CityRoute::CityWrapper*> cityWrapperList) {
    vector<City*> citys;
    for (size_t i = 0; i < cityWrapperList.size(); i++) {
        citys.push_back(converToCity(cityWrapperList[i]));
    }
    return citys;
}

vector<CityRoute::CityWrapper*> CityRoute::convertToCityWrapperList(vector<City*> cityList){
    vector<CityRoute::CityWrapper> cityWrappers;
    for(size_t i = 0; i < cityList.size(); i++) {
        cityWrappers.push_back(convertToCityWrapper(cityList[i]));
    }
    return cityWrappers;

/* distance functions */

float CityRoute::realDistance(City* a, City* b) {
     return sqrt(pow((a->pos.x - b->pos.x), 2) + pow((a->pos.y - b->pos.y), 2));
}
float CityRoute::hDistance(CityWrapper* from, CityWrapper* to) {
    return realDistance(from->city, to->city);
}
float CityRoute::gDistance(CityWrapper* source, CityWrapper* current) {
    float distance = 0;

    do {    
        distance += realDistance(current.city, current.prev.city);
        current = current.prev;
    } while (current.prev != NULL) 
    
    return distance;
};
float CityRoute::fDistance(CityWrapper* source, CityWrapper* current, CityWrapper* to) {
    return gDistance(source, current) + hDistance(current, to);
}

