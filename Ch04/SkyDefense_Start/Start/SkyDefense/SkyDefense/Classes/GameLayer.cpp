/*

Background music:
Blipotron by Kevin MacLeod (incompetech.com)

*/



#include "GameLayer.h"

using namespace cocos2d;


GameLayer::~GameLayer () {
    
    
    CC_SAFE_RELEASE(_growBomb);
    CC_SAFE_RELEASE(_rotateSprite);
    CC_SAFE_RELEASE(_shockwaveSequence);
    CC_SAFE_RELEASE(_swingHealth);
    CC_SAFE_RELEASE(_groundHit);
    CC_SAFE_RELEASE(_explosion);
    
    _clouds.clear();
    _meteorPool.clear();
    _healthPool.clear();
    _fallingObjects.clear();
    
}

GameLayer::GameLayer () :  _meteorPool(50), _healthPool(20),  _fallingObjects(40), _clouds(4)
{}


Scene * GameLayer::scene()
{
   auto scene = Scene::create();
    
    auto layer = GameLayer::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //get screen size
	_screenSize = Director::getInstance()->getWinSize();
	
    _running = false;
    
    //create game screen elements
    this->createGameScreen();
    
    //create object pools
    this->createPools();
    this->createActions();
    
	//listen for touches
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //create main loop
    this->scheduleUpdate();
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
    return true;
}


void GameLayer::update (float dt) {
    
    
    if (!_running) return;
    
    int count;
    int i;
    
    //update timers
    _meteorTimer += dt;
    if (_meteorTimer > _meteorInterval) {
        _meteorTimer = 0;
        this->resetMeteor();
    }
    
    _healthTimer += dt;
    if (_healthTimer > _healthInterval) {
        _healthTimer = 0;
        this->resetHealth();
    }
    
    _difficultyTimer += dt;
    if (_difficultyTimer > _difficultyInterval) {
        _difficultyTimer = 0;
        this->increaseDifficulty();
    }
    
}

bool GameLayer::onTouchBegan(Touch * touch, Event * event){
    
       return true;
}

void GameLayer::fallingObjectDone (Node * pSender) {
    
    
    _fallingObjects.erase(_fallingObjects.find( (Sprite *)pSender));
    pSender->stopAllActions();
    pSender->setRotation(0);
    
    if (pSender->getTag() == kSpriteMeteor) {
        changeEnergy(-15);
        pSender->runAction( _groundHit->clone() );
        //play explosion sound
        SimpleAudioEngine::getInstance()->playEffect("boom.wav");
    } else {
        pSender->setVisible(false);

        if (_energy == 100) {
            
            _score += 25;
            _scoreDisplay->setString(String::createWithFormat("%i", _score)->getCString());
            
        } else {
            changeEnergy(10);
        }
        //play health bonus sound
        SimpleAudioEngine::getInstance()->playEffect("health.wav");
    }
}

void GameLayer::animationDone (Node * pSender) {
    pSender->setVisible(false);
}


void GameLayer::shockwaveDone() {
    _shockWave->setVisible(false);
}


void GameLayer::resetMeteor(void) {
    
}


void GameLayer::resetHealth(void) {
    
    if (_fallingObjects.size() > 30) return;
    
    auto health = _healthPool.at(_healthPoolIndex);
	_healthPoolIndex++;
	if (_healthPoolIndex == _healthPool.size()) _healthPoolIndex = 0;
	
    
	int health_x = rand() % (int) (_screenSize.width * 0.8f) + _screenSize.width * 0.1f;
    int health_target_x = rand() % (int) (_screenSize.width * 0.8f) + _screenSize.width * 0.1f;
    
    health->stopAllActions();
    health->setPosition(Vec2(health_x, _screenSize.height + health->getBoundingBox().size.height * 0.5));
	
    //create action
    auto  sequence = Sequence::create(
           MoveTo::create(_healthSpeed, Vec2(health_target_x, _screenSize.height * 0.15f)),
                                    CallFunc::create(std::bind(&GameLayer::fallingObjectDone, this, health) ),
           nullptr);
    
    health->setVisible ( true );
    health->runAction( _swingHealth->clone());
    health->runAction(sequence);
    _fallingObjects.pushBack(health);
}

void GameLayer::changeEnergy(float value) {
    _energy += value;
    if (_energy <= 0) {
        _energy = 0;
        this->stopGame();
        SimpleAudioEngine::getInstance()->playEffect("fire_truck.wav");
        //show GameOver
        _gameOverMessage->setVisible(true);
    }
    
    if (_energy > 100) _energy = 100;
    
    _energyDisplay->setString(String::createWithFormat("%i%% ", (int)_energy)->getCString());
}

void GameLayer::resetGame(void) {

}

void GameLayer::increaseDifficulty () {

    _meteorInterval -= 0.15f;
    if (_meteorInterval < 0.25f) _meteorInterval = 0.25f;
    _meteorSpeed -= 1;
    if (_meteorSpeed < 4) _meteorSpeed = 4;
    
    _healthSpeed -= 1;
    if (_healthSpeed < 8) _healthSpeed = 8;
    
}


void GameLayer::stopGame() {


}

void GameLayer::createGameScreen() {

    //add bg
    auto bg = Sprite::create("bg.png");
    bg->setPosition(Vec2(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(bg);
    
}

void GameLayer::createPools() {
    
}


void GameLayer::createActions() {
    
}
