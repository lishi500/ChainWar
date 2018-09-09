#ifndef __MAP_READER_H_
#define __MAP_READER_H_

#include <vector>
#include <math.h>
#include <fstream>
#include "cocos2d.h"
#include "entity/City.h"
#include "entity/Team.h"
#include "mapGenerator/json.hpp"


USING_NS_CC;
using namespace std;

class MapReader {
public:
    vector<City*> cityMap;

	void readMap();

};

#endif