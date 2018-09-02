#ifndef __MAP_READER_H_
#define __MAP_READER_H_

#include <json/value.h>
#include <fstream>
#include "entity/City.h"

using namespace std;

class MapReader {
public:
    vector<City*> cityMap;
    void readerMap();
    

}

#endif