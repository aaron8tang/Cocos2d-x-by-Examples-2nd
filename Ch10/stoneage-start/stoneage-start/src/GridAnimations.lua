local constants = require ("constants")

local GridAnimations = class("GridAnimations")

function GridAnimations.create ( )
    local ga = GridAnimations.new ()
    return ga
end

function GridAnimations:setGameLayer (value)
    self.gameLayer = value
end

function GridAnimations:ctor()
    self.animatedGems = 0
    self.animatedMatchedGems = 0
    self.gameLayer = nil
    self.animatedCollapsedGems = 0
end


function GridAnimations:animateIntro ()
    self.gameLayer.enabled = false 
    self.animatedGems = 0
    for i = 1, constants.GRID_SIZE_X do 
        self:dropColumn ( i )
    end
end

function GridAnimations:dropColumn (col)

    local function onAnimatedColumn (sender)
        self.animatedGems = self.animatedGems + 1
        if (self.animatedGems == constants.GEMS_TOTAL) then
            self.gameLayer.enabled = true
            self.gameLayer:startTimer()
        end
    end

    local delay = 0
    if (col > 1) then delay = math.random() * 1.5 end
     
    local gem = nil 
    for i = 1, constants.GRID_SIZE_Y do
        gem = self.gameLayer.gridGemsColumnMap[col][i]
        gem:setVisible(true)
        local finalY = gem:getPositionY()
        gem:setPositionY(finalY + 800)
        local moveTo = cc.MoveTo:create(2, cc.p(gem:getPositionX(), finalY  ))
        local move_ease_out = cc.EaseBounceOut:create( moveTo )
        local delayAction = cc.DelayTime:create(delay)
        local callback = cc.CallFunc:create(onAnimatedColumn)
        local seq1 = cc.Sequence:create(delayAction, move_ease_out, callback)
        gem:runAction(seq1)
    end
end

function GridAnimations:animateSelected (gem)
end

function GridAnimations:resetSelectedGem ()
    local gem = self.gameLayer.selectedGem
    local gemPosition = self.gameLayer.selectedGemPosition
    local moveTo = cc.MoveTo:create(0.25, gemPosition)
    local move_elastic_out = cc.EaseElasticOut:create( moveTo )
    gem:runAction(move_elastic_out)
end

function GridAnimations:swapGems (gemOrigin, gemTarget, onComplete)
    
end

function GridAnimations:animateMatches (matches, onComplete)

end


function GridAnimations:animateCollapse ( onComplete )

end

function GridAnimations:dropGemTo (gem, y, delay, onComplete)
   
end

function GridAnimations:collectDiamonds(diamonds)
    
end


return GridAnimations