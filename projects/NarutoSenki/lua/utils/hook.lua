--
-- Hook for GameLayer
--
hook = {}

function hook.registerInitHandlerOnly(target)
    if not target.init then
        log('Not found function target:init()')
        return
    end

    target:registerScriptHandler(function(event)
        target:init()
        target:unregisterScriptHandler()
    end)
end
