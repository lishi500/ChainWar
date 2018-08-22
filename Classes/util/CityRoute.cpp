#include "CityRoute.h"


vector<City*> CityRoute::convertToCityList(vector<CityRoute::CityWraper*> cityWrapperList) {
    vector<City*> citys;
    for (size_t i = 0; i < cityWrapperList.size(); i++) {
        citys.push_back(cityWrapperList[i]->current);
    }
    return citys;
}

vector<CityRoute::CityWraper*> CityRoute::convertToCityWraperList(vector<City*> cityList){

}