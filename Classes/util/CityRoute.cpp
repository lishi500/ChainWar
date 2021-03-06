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
	set<CityWrapper*> openSet;
	set<City*> openSetCity;
    // priority_queue<CityWrapper*, vector<CityWrapper*>, cmp>* openQueue;
	set<CityWrapper* > closeSet;

	insertToSet(fromCityWrapper, NULL, &openSet, &openSetCity);
    while (!openSet.empty()) {
        CityWrapper* front = getNextOptimalCity(&openSet, &openSetCity);
        if (front->city == toCityWrapper->city) {
            return reconstructPath(front);
        }
        vector<CityWrapper*> openCity = convertToCityWrapperList(front->city->connectedCity);
        batchInsertToSet(openCity, front, &openSet, &openSetCity);
   }

	return vector<City*>();
}

void CityRoute::connectCityList(City* fromCity, vector<City*> toCityList) {
    std::vector<City*>::iterator cityIt;
    for(cityIt = toCityList.begin(); cityIt != toCityList.end(); cityIt++) {
		if ((*cityIt)->connectedCity.size() > 6) {
			CCLOG("city name --- - :  %s \n", (*cityIt)->cityName);
		}
        connectCity(fromCity, *cityIt);
    }
}

void CityRoute::connectCity(City* fromCity, City* toCity) {
    if(!(std::find(fromCity->connectedCity.begin(), fromCity->connectedCity.end(), toCity) != fromCity->connectedCity.end())) {
        fromCity->connectedCity.push_back(toCity);
    }
    if(!(std::find(toCity->connectedCity.begin(), toCity->connectedCity.end(), fromCity) != toCity->connectedCity.end())) {
        toCity->connectedCity.push_back(fromCity);
    }
}



CityRoute::CityWrapper* CityRoute::getNextOptimalCity(set<CityWrapper*> *openSet, set<City*> *openSetCity) {
    CityWrapper* nextCity = NULL;
    float smallestF = std::numeric_limits<float>::max();

    std::set<CityWrapper*>::iterator it;
    for (it = openSet->begin(); it != openSet->end(); ++it)
    {
        float nextf = (*it)->f;
        if (nextf < smallestF) {
            smallestF = nextf;
            nextCity = *it;
        }
    }
    if (nextCity != NULL) {
        openSet->erase(nextCity);
		openSetCity->erase(nextCity->city);
    }

    return nextCity;
}

void CityRoute::batchInsertToSet(vector<CityRoute::CityWrapper*> cityWrapperList, CityRoute::CityWrapper* prevCity, set<CityWrapper*> *openSet, set<City*> *openSetCity) {
	vector<CityRoute::CityWrapper*>::iterator p;
    for(p = cityWrapperList.begin(); p != cityWrapperList.end(); p++) {
		insertToSet((*p), prevCity, openSet, openSetCity);
    }
}

void CityRoute::insertToSet(CityRoute::CityWrapper* cityWrapper, CityRoute::CityWrapper* prevCity, set<CityWrapper*> *openSet, set<City*> *openSetCity) {
	if (!(openSetCity->find(cityWrapper->city) != openSetCity->end())) {
		cityWrapper->prev = prevCity;
		cityWrapper->f = fDistance(fromCityWrapper, cityWrapper, toCityWrapper);
		openSet->insert(cityWrapper);
		openSetCity->insert(cityWrapper->city);
	}
	
}

vector<City*> CityRoute::reconstructPath(CityRoute::CityWrapper* cityWrapper) {
    vector<City*> citys;

	while (cityWrapper->prev != NULL) {
        citys.push_back(cityWrapper->city);
        cityWrapper = cityWrapper->prev;
    } 
    
    return citys;
}
/* city <--> cityWrapper converter */
CityRoute::CityWrapper* CityRoute::convertToCityWrapper(City* city) {
    CityWrapper* cityWrapper = new CityWrapper();
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
float CityRoute::totalDistanceToCityGroup(City* fromCity, vector<City*> cityGroup) {
	float totalDistance = 0;
	for (int i = 0; i < cityGroup.size(); i++) {
		totalDistance += realDistanceBetweenCity(fromCity, cityGroup.at(i));
	}

	return totalDistance;
}

float CityRoute::realDistanceBetweenCity(City* fromCity, City* toCity) {
	vector<City*> route = findShortestRoute(fromCity, toCity);
	float totalDistance = 0;
	if (route.size() > 1) {
		City* prev = route.at(0);
		for (int i = 1; i < route.size(); i++) {
			City* next = route.at(i);
			totalDistance += manhattanDistance(prev, next);
			prev = next;
		}
	}
	else {
		return 0;
	}
	return totalDistance;
}

float CityRoute::manhattanDistance(City* a, City* b) {
     return sqrt(pow((a->pos.x - b->pos.x), 2) + pow((a->pos.y - b->pos.y), 2));
}

float CityRoute::hDistance(CityWrapper* from, CityWrapper* to) {
    return manhattanDistance(from->city, to->city);
}

float CityRoute::gDistance(CityWrapper* source, CityWrapper* current) {
    float distance = 0;

	while (current->prev != NULL) {
        distance += manhattanDistance(current->city, current->prev->city);
        current = current->prev;
	} 
    
    return distance;
};

float CityRoute::fDistance(CityWrapper* source, CityWrapper* current, CityWrapper* to) {
    return gDistance(source, current) + hDistance(current, to);
}

