#include "GameLayer.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;
using namespace CocosDenshion;

GameLayer::~GameLayer() {
    
}

Scene* GameLayer::scene()
{
    auto scene = Scene::create();
    
    GameLayer *layer = GameLayer::create();

    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
    //get screen size
    _screenSize = Director::getInstance()->getWinSize();
    
    createGameScreen();
    
    resetGame();
    
    //listen for touches
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //create main loop
    this->scheduleUpdate();
    
    return true;
}

void GameLayer::resetGame () {
    
    _speedIncreaseInterval = 15;
	_speedIncreaseTimer = 0;
    
    _running = true;
}


void GameLayer::update(float dt) {

}

bool GameLayer::onTouchBegan(Touch* touch, Event* event) {
    
    return true;
}

void GameLayer::onTouchEnded(Touch* touch, Event* event) {
    
}

void GameLayer::createGameScreen () {
    
    
}