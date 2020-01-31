﻿#ifndef __GAMESPRITE_H__
#define __GAMESPRITE_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameSprite : public Sprite {
public:

	CC_SYNTHESIZE(Vec2, _nextPosition, NextPosition);
	
	CC_SYNTHESIZE(Vec2, _vector, Vector);
    
    CC_SYNTHESIZE(Touch*, _touch, Touch);
	
	GameSprite();
	
	virtual ~GameSprite();
    
    static GameSprite* gameSpriteWithFile(const char* pszFileName);
    	
	virtual void setPosition(const Vec2& pos) override;
    
    float radius();
    
};

#endif // __GAMESPRITE_H__		