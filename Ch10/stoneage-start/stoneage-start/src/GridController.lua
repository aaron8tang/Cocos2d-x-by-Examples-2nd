local constants = require ("constants")
local GridController = class("GridController")

function GridController:ctor()
    self.enabled = true
    self.touchDown = false
    self.gameLayer = nil
    self.matchArray = {}
end

function GridController.create (  )
    local gc = GridController.new ()
    return gc
end

function GridController:setGameLayer (value) 
    self.gameLayer = value
end

function GridController:checkGridMatches ()
    
end

function GridController:checkTypeMatch (c, r)
    
end

function GridController:addMatches (matches)
end

function GridController:find (np, array)
end

function GridController:findGemAtPosition (position)
    
end

function GridController:selectStartGem (touchedGem)
    
end

function GridController:selectTargetGem (touchedGem)
end

function GridController:onTouchDown (touch)
end

function GridController:onTouchUp (touch)
end

function GridController:onTouchMove (touch)
end

function GridController:isValidTarget (px, py, touch)

end

return GridController