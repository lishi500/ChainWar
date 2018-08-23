#include "CityRoute.h"

struct cmp
{
    bool operator()(CityRoute::CityWrapper* a, CityRoute::CityWrapper* b) {
        return a->f < b->f;
    }
};


vector<City*> CityRoute::findShortestRoute(City* fromCity, City* toCity) {
    fromCityWrapper = convertToCityWrapper(fromCity);
    toCityWrapper = convertToCityWrapper(toCity);

    priority_queue<CityWrapper*, vector<CityWrapper*>, cmp>* openQueue;
    vector<CityWrapper* > closeSet;

    vector<CityWrapper*> initialOpenCity = convertToCityWrapperList(fromCity->connectedCity);
    insertToQueue(fromCityWrapper, fromCityWrapper, openQueue);
    while (!openQueue->empty()) {
        CityWrapper* front = openQueue.pop();
        if (front == toCityWrapper) {
            return reconstructPath(front);
        }
    }

	return vector<City*>();
}

void CityRoute::batchInsertToQueue(vector<CityRoute::CityWrapper*> cityWrapperList, CityRoute::CityWrapper* prevCity, priority_queue* queue) {
    for(vector<CityRoute::CityWrapper*>::iterator p = cityWrapperList.begin(); p! = cityWrapperList.end(); p++) {
        insertToQueue((*p), prevCity, queue);
    }
}

void CityRoute::insertToQueue(CityRoute::CityWrapper* cityWrapper, CityRoute::CityWrapper* prevCity, priority_queue* queue) {
    for(vector<CityRoute::CityWrapper*>::iterator p = queue.begin(); p! = queue.end(); p++) {
        if (cityWrapper == (*p)) {
            return;
        }
    }
    cityWrapper->prev = prevCity;
    cityWrapper->f = fDistance(fromCityWrapper, cityWrapper, toCityWrapper);
    queue.push(cityWrapper);
}
vector<City*> CityRoute::reconstructPath(CityRoute::CityWrapper* cityWrapper) {
    vector<City*> citys;

    do {
        citys.push_back(cityWrapper->city);
        cityWrapper = cityWrapper->prev;
    } while(cityWrapper->prev != NULL);
    
    return citys;
}
/* city <--> cityWrapper converter */
CityRoute::CityWrapper* CityRoute::convertToCityWrapper(City* city) {
    CityWrapper* cityWrapper;
    cityWrapper->city = city;
    cityWrapper->prev = NULL;
    cityWrapper->next = NULL;

    return cityWrapper;
}

City* CityRoute::converToCity(CityWrapper* cityWrapper) {
    return cityWrapper->city;
}


vector<City*> CityRoute::convertToCityList(vector<CityRoute::CityWrapper*> cityWrapperList) {
    vector<City*> citys;
    for (size_t i = 0; i < cityWrapperList.size(); i++) {
        citys.push_back(converToCity(cityWrapperList[i]));
    }
    return citys;
}

vector<CityRoute::CityWrapper*> CityRoute::convertToCityWrapperList(vector<City*> cityList) {
	vector<CityRoute::CityWrapper*> cityWrappers;
	for (size_t i = 0; i < cityList.size(); i++) {
		cityWrappers.push_back(convertToCityWrapper(cityList[i]));
	}
	return cityWrappers;
}
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
        distance += realDistance(current->city, current->prev->city);
        current = current->prev;
	} while (current->prev != NULL);
    
    return distance;
};

float CityRoute::fDistance(CityWrapper* source, CityWrapper* current, CityWrapper* to) {
    return gDistance(source, current) + hDistance(current, to);
}

