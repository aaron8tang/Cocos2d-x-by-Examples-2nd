--[[
Background music: Life of Reilly by
Kevin MacLeod - kevin@incompetech.com
http://incompetech.com/
--]]

local constants = require ("constants")
local GridController = require ("GridController")
local GridAnimations = require ("GridAnimations")
local ObjectPools = require ("ObjectPools")
local Gem = require ("Gem")

local GameScene = class("GameScene",function()
    return cc.Scene:create()
end)

function GameScene.create()
    local scene = GameScene.new()
    return scene
end

function GameScene:ctor()
    self.visibleSize = cc.Director:getInstance():getVisibleSize()
    self.middle = {x = self.visibleSize.width * 0.5, y = self.visibleSize.height * 0.5}
    self.origin = cc.Director:getInstance():getVisibleOrigin()
    self.schedulerID = nil
    self.grid = {}
    self.gridController = nil
    self.gridAnimations = nil
    self.objectPools = nil
    self.gridGemsColumnMap = {}
    self.allGems = {}
    self.gemsContainer = cc.Node:create()
    self.selectedGem = nil
    self.targetGem = nil
    self.selectedIndex = {x = 0, y = 0}
    self.targetIndex = {x = 0, y = 0}
    self.selectedGemPosition = {x = 0, y = 0}
    self.combos = 0
    self.addingCombos = false
    self.scoreLabel = nil
    self.diamondScoreLabel = nil
    self.diamondScore = 0
    self.gemsScore = 0
    self.running = true
    self:addTouchEvents()
    self:init()
    self:buildGrid()
end

function GameScene:addTouchEvents()

end

function GameScene:init ()
    
end


function GameScene:buildGrid ()
    
end

function GameScene:getVerticalUnique (col, row)

end

function GameScene:getVerticalHorizontalUnique (col, row)
end

function GameScene:swapGemsToNewPosition ()
    
end

function GameScene:collapseGrid ()
    
end

function GameScene:dropSelectedGem ()
    self.selectedGem:setLocalZOrder(constants.Z_GRID)
    self.gridAnimations:resetSelectedGem()
end

function GameScene:getNewGem ()
    return math.random(1, #constants.TYPES)
end

function GameScene:addToScore ()
    for i = 1, #self.gridController.matchArray do
        local position = self.gridController.matchArray[i]
        local gem = self.gridGemsColumnMap[position.x][position.y]
        if (gem.type == constants.TYPE_GEM_WHITE) then
            --got a diamond
        end
    end
end

function GameScene:showMatchParticle (matches)
    
    for i = 1, #matches do
        local gem = self.gridGemsColumnMap[matches[i].x][matches[i].y]
        local particle = self.objectPools:getMatchParticle()
        particle:setPosition(gem:getPositionX() + self.gemsContainer:getPositionX(), gem:getPositionY()  + self.gemsContainer:getPositionY())       
    end
    
end

function GameScene:setDiamondScore (value)
    self.diamondScore = self.diamondScore  + value
    self.diamondScoreLabel:setString("" .. self.diamondScore) 
end

function GameScene:setGemsScore (value)
    self.gemsScore = self.gemsScore  + value
    self.scoreLabel:setString("" .. self.gemsScore)
end

function GameScene:playFX(name)
    local fx = cc.FileUtils:getInstance():fullPathForFilename(name) 
    cc.SimpleAudioEngine:getInstance():playEffect(fx)
end

function GameScene:startTimer()

    local timeBarBg = cc.Sprite:create("timeBarBg.png")
    timeBarBg:setPosition(self.middle.x, 40)
    self:addChild(timeBarBg)

    local timeBar = cc.Sprite:create("timeBar.png")
    timeBar:setAnchorPoint(cc.p(0,0.5))
    timeBar:setPosition(self.middle.x - 290, 40)
    self:addChild(timeBar)
    
    local function tick()
        local scaleNow = timeBar:getScaleX()
        local speed = 0.007
        if (scaleNow - speed > 0) then
            timeBar:setScaleX(scaleNow - speed)
        else
            --GameOver!!!
            timeBar:setScaleX(0)
            cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self.schedulerID)
            cc.SimpleAudioEngine:getInstance():stopMusic()
            self.running = false            
            -- show game over
            local gameOver = cc.Sprite:create("gameOver.png")
            gameOver:setPosition(self.middle.x, self.middle.y)
            self:addChild(gameOver)
        end 
    end
  
    self.schedulerID = cc.Director:getInstance():getScheduler():scheduleScriptFunc(tick, 1, false)
end

return GameScene
