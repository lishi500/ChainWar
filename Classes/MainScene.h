#ifndef __MAIN_SCENE_H_
#define __MAIN_SCENE_H_

#include "cocos2d.h"

class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    void renderCity();
    void renderConnection();


    vector<City*> cityList;

};


#endif