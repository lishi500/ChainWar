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


USING_NS_CC;


class TeamGenerator {
public:
	TeamGenerator(int numberOfTeam)
	{
		generateTeam(numberOfTeam);
	}

    vector<Team*> teamList;

    void generateTeam(int numberOfTeam);
    void autoClusterCity(vector<City*> cityList);
    void getInitialCity(vector<City*> *cityList, queue<City*> *queue, set<City*> *set);

	void batchAddToQueueSet(vector<City*> citys, queue<City*> *queue, set<City*> *set);
    void addToQueueSet(City* city, queue<City*> *queue, set<City*> *set);
    City* popFromQueueSet(queue<City*> *queue, set<City*> *set);
};

#endif