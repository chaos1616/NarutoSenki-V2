-- design resoluation configuration
CONFIG_SCREEN_WIDTH = 480
CONFIG_SCREEN_HEIGHT = 320
CONFIG_SCREEN_AUTOSCALE = 'FIXED_HEIGHT'

require 'framework.init'

-- if DEBUG == 0 then
log = function(...) print(string.format(...)) end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(msg) .. "\n")
    print(debug.traceback())
    print("----------------------------------------")
end

-- defines
require 'hook'

-- AI Module
require 'ai.provider'

require 'ui.init'

require 'utils.utils'
require 'utils.save'

-- require 'class.ICharacter'
require 'class.basic'
