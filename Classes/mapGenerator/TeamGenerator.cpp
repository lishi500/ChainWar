#include "TeamGenerator.h"
#include "CityRoute.h"
#include <iomanip>

using namespace std;

void TeamGenerator::generateTeam() {
    for (int i = 0; i < _NUMBER_OF_TEAM; i++) {
        Team* t;
        string name;
		name.append("team ");
		name.append(to_string(i));

        int r = rand() % 255;
        int g = rand() % 255;
        int b = rand() % 255;
        int color = r<<16 || g<<8 || b;
        std::stringstream stream;
        stream << std::hex << color;

        t->teamName = name;
        t->color = stream.str();
        teamList.push_back(t);
    }
}

void TeamGenerator::autoClusterCity(vector<City*> cityList) {
    set<City*> openSet;
    set<City*> currentSet;
    queue<City*> openQueue;
    vector<City*> currentTeamCitys;
    int teamIndex = 0;
    Team* currentTeam = teamList.at(teamIndex++);


    getInitialCity(&cityList, &openQueue, &openSet);
    while (!openQueue.empty()) {
       

        City* next = popFromQueueSet(&openQueue, &openSet);
        if (&(next->team)) {
            continue;
        }

        insertConnectedCityToSet(next, &currentSet);
       
        while(!currentSet.empty() && currentTeamCitys.size() < _TEAM_SIZE) {
            City* nearst = findNearestCityToCurrentTeam(&currentSet, &currentTeamCitys);
            nearst->team = currentTeam;
            currentTeamCitys.push_back(nearst);
            insertConnectedCityToSet(nearst, &currentSet);
        }

        if (currentTeamCitys.size() >= _TEAM_SIZE) {
            currentTeam = teamList.at(teamIndex++);
            moveExtraCitysToOpenQueueSet(&currentSet, &openQueue, &openSet);
        }
    }
}

void TeamGenerator::insertConnectedCityToSet(City* city, set<City*> *set) {
     for (int i = 0; i <city->connectedCity.size(); i++) {
            if (!&(city->connectedCity.at(i)->team)) {
		        set->insert(city->connectedCity.at(i));
            }
	    }
}

void TeamGenerator::moveExtraCitysToOpenQueueSet(set<City*> *lefted, queue<City*> *queue, set<City*> *set) {
    std::set<City*>::iterator it;
    for (it = lefted->begin(); it != lefted->end(); ++it) {
       addToQueueSet(*it, queue, set);
    }
}

City* TeamGenerator::findNearestCityToCurrentTeam(set<City*> *set,  vector<City*> *teamCity) {
    CityRoute cityRoute = CityRoute();
    City* nearst;
    float shortest = numeric_limits<float>::max();

    std::set<City*>::iterator it;
    for (it = set->begin(); it != set->end(); ++it) {
       float distance = cityRoute.totalDistanceToCityGroup(*it, *teamCity);
       if (distance < shortest) {
           shortest = distance;
           nearst = *it;
       }
    }

    return nearst;

}

void TeamGenerator::getInitialCity(vector<City*> *cityList, queue<City*> *queue, set<City*> *set) {
    City *east, *west, *north, *south;
    float e = numeric_limits<float>::min();
    float w = numeric_limits<float>::max();
    float n = numeric_limits<float>::min();
    float s = numeric_limits<float>::max();

    std::vector<City*>::iterator cit;
	for (cit = cityList->begin(); cit != cityList->end(); cit++) {
        City* city = (*cit);
        if (city->pos.x > e) {
            e = city->pos.x;
            east = city;
        }

        if (city->pos.x < w) {
            w = city->pos.x;
            west = city;
        }

        if (city->pos.y > n) {
            n = city->pos.y;
            north = city;
        }

        if (city->pos.y < s) {
            s = city->pos.y;
            south = city;
        }
    }
    addToQueueSet(east, queue, set);
    addToQueueSet(west, queue, set);
    addToQueueSet(north, queue, set);
    addToQueueSet(south, queue, set);

}


void TeamGenerator::batchAddToQueueSet(vector<City*> citys, queue<City*> *queue, set<City*> *set) {
	for (int i = 0; i <citys.size(); i++) {
		addToQueueSet(citys.at(i), queue, set);
	}
}

void TeamGenerator::addToQueueSet(City* city, queue<City*> *queue, set<City*> *set) {
    const bool is_in = set->find(city) != set->end();
    if (!is_in) {
        queue->push(city);
        set->insert(city);
    }
}

City* TeamGenerator::popFromQueueSet(queue<City*> *queue, set<City*> *set) {
	City* city = queue->front();
	queue->pop();
    set->erase(city);
    return city;
}