-- design resoluation configuration
CONFIG_SCREEN_WIDTH = 480
CONFIG_SCREEN_HEIGHT = 320
CONFIG_SCREEN_AUTOSCALE = 'FIXED_HEIGHT'

require 'framework.init'

log = function(...) print(string.format(...)) end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(msg) .. "\n")
    print(debug.traceback())
    print("----------------------------------------")
end

-- defines
GameScene = GameScene

-- AI Module
require 'ai.provider'

require 'utils.utils'

require 'class.ICharacter'
