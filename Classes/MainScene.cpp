#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "mapGenerator/MapGenerator.h"


USING_NS_CC;

Scene* MainScene::createScene() {
    return MainScene::create();
}

bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    MapGenertor mapGenertor = MapGenertor(10, 4);
	mapGenertor.generateRandomCity();
    this->cityList = MapGenertor.cityList;

    renderCity();
}

void MainScene::renderCity() {
    std::vector<City*>::iterator cityIt;
    for (cityIt = cityList.begin; cityList != cityList.end; cityIt++) {
        
    }
}


void MainScene::renderConnection() {

}