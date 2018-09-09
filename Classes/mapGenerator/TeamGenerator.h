#ifndef  _TEAM_GENERATOR_H_
#define  _TEAM_GENERATOR_H_
#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include "cocos2d.h"
#include "entity/City.h"
#include "entity/Team.h"


#define _NUMBER_OF_TEAM 8
#define _TEAM_SIZE 10

USING_NS_CC;


class TeamGenerator {
public:
	TeamGenerator()
	{
		generateTeam();
	}

    vector<Team*> teamList;

    void generateTeam();
    void autoClusterCity(vector<City*> *cityList);
    void getInitialCity(vector<City*> *cityList, queue<City*> *queue, set<City*> *set);

    void moveExtraCitysToOpenQueueSet(set<City*> *lefted, queue<City*> *queue, set<City*> *set);
    City* findNearestCityToCurrentTeam(set<City*> *set,  vector<City*> *teamCity);
    void insertConnectedCityToSet(City* city, queue<City*> *queue, set<City*> *set);

	void batchAddToQueueSet(vector<City*> citys, queue<City*> *queue, set<City*> *set);
    void addToQueueSet(City* city, queue<City*> *queue, set<City*> *set);
    City* popFromQueueSet(queue<City*> *queue, set<City*> *set);

	void printTeam(vector<City*> *cityList);
	vector<City*> getCitysByTeam(Team* team, vector<City*> *cityList);
};

#endif