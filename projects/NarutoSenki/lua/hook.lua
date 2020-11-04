-- Hook for GameLayer
hook = {}
SelectButton = SelectButton or {}

hook.onSelectedCallback = function(name)
    print('Invoke callback -> onSelectedCallback [ %s ]', name)
end

hook.onGameStartCallback =
    function() print('Invoke callback -> onGameStart') end
hook.onGameStartedCallback =
    function() print('Invoke callback -> onGameStarted') end
hook.onGameEndedCallback =
    function() print('Invoke callback -> onGameEnded') end
hook.onInitTileMapCallback =
    function() print('Invoke callback -> onInitTileMap') end
hook.onInitEffectsCallback =
    function() print('Invoke callback -> onInitEffects') end
hook.onInitHerosCallback =
    function() print('Invoke callback -> onInitHeros') end

function hook:onSelect(name)
    if not hook.onSelectedCallback then hook.onSelectedCallback(name) end
end

function hook:onGameStart()
    hook.onSelectedCallback = nil

    if not hook.onGameStartCallback then hook.onGameStartCallback() end
end

function hook:onGameStarted()
    if not hook.onGameStartedCallback then hook.onGameStartedCallback() end
end

function hook:onGameEnded()
    if not hook.onGameEndedCallback then hook.onGameEndedCallback() end

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

--[[
    SelcetButton
]]
function SelectButton:onselect(name)
    if name then
        -- print selected character name
        print(string.format('\nSelect -> [ %s ]\n', name))
    end
end
