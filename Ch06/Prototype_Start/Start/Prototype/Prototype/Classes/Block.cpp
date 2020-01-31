
#define TILE_H_SIZE 6
#define TILE_W_SIZE 8

#include "Block.h"

Block::~Block () {

}

Block::Block () {
    
    //get screen size
	_screenSize = Director::getInstance()->getWinSize();
    _tileWidth = _screenSize.width / TILE_W_SIZE;
    _tileHeight = _screenSize.height / TILE_H_SIZE;
    
    this->setVisible(false);
}

Block * Block::create () {
    
    auto block = new Block();
	if (block && block->initWithFile("blank.png")) {
		block->autorelease();
		return block;
	}
	CC_SAFE_DELETE(block);
	return nullptr;
}


void Block::setupBlock (int width, int height, int type) {
    
}

