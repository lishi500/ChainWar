#include "TeamGenerator.h"
#include <iomanip>

using namespace std;

void TeamGenerator::generateTeam(int numberOfTeam) {
    for (int i = 0; i < numberOfTeam; i++) {
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
    queue<City*> currentQueue;

    getInitialCity(&cityList, &openQueue, &openSet);
    while (!openQueue.empty()) {
        City* next = popFromQueueSet(&openQueue, &openSet);
        if (&(next->team)) {
            continue;
        }
		batchAddToQueueSet(next->connectedCity, &openQueue, &openSet);
		

    }
}

void spreadCity(City* city, queue<City*> *queue, set<City*> *set) {
    
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