require 'utils.utils'

-- Hook for GameLayer
hook = {}

local display = require 'framework.display'
local ui = require 'framework.ui'

hook.onSelectedCallback = function(name)
    print('Invoke callback : onSelectedCallback [ %s ]', name)
end

hook.onGameStartCallback = function() print('Invoke callback : onGameStart') end
hook.onGameStartedCallback =
    function() print('Invoke callback : onGameStarted') end
hook.onGameEndedCallback = function() print('Invoke callback : onGameEnded') end
hook.onInitTileMapCallback =
    function() print('Invoke callback : onInitTileMap') end
hook.onInitEffectsCallback =
    function() print('Invoke callback : onInitEffects') end
hook.onInitHerosCallback = function() print('Invoke callback : onInitHeros') end

function hook:onSelect(name)
    if hook.onSelectedCallback then hook.onSelectedCallback(name) end
end

function hook.onGameStart(this)
    hook.onSelectedCallback = nil
    if hook.onGameStartCallback then hook.onGameStartCallback() end
end

function hook:onGameStarted()
    if hook.onGameStartedCallback then hook.onGameStartedCallback() end
end

function hook:onGameEnded()
    if hook.onGameEndedCallback then hook.onGameEndedCallback() end

    hook.onGameStartCallback = nil
    hook.onGameStartedCallback = nil
    hook.onGameEndedCallback = nil
    hook.onInitTileMapCallback = nil
    hook.onInitEffectsCallback = nil
    hook.onInitHerosCallback = nil
end

function hook:onInitTileMap() end

function hook:onInitEffects() end

function hook:onInitHeros() end

-- SelectButton
function SelectButton:init()
    log('%s init ...', type(SelectButton))

    -- handling touch events
    local function onTouchBegan(x, y)
        log('on touch: %s', self._isCanBuy)
        return true
    end

    local function onTouch(eventType, x, y)
        if eventType == "began" then return onTouchBegan(x, y) end
    end

    self:setTouchEnabled(true)
    self:registerScriptTouchHandler(onTouch)
end

-- for key, value in pairs(_G) do
--     print(key,value)
-- end

function hook.registerInitHandlerOnly(target, handler)
    target:registerScriptHandler(function (event)
        handler(target)
        target:unregisterScriptHandler()
    end)
end
