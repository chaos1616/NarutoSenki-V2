--
-- CCUserDefault
--
save = {}

local u = CCUserDefault:sharedUserDefault()

-- get value methods

--[[--
    Get bool value by key, if the key doesn't exist, a default value will return.
    You can set the default value, or it is false.
]]
function save.getBool(key, default)
    if default and type(default) == 'boolean' then
        return u.getBoolForKey(key, default)
    end
    return u.getBoolForKey(key)
end

--[[--
    Get integer value by key, if the key doesn't exist, a default value will return.
    You can set the default value, or it is 0.
]]
function save.getInteger(key, default)
    if default and type(default) == 'number' then
        return u.getIntegerForKey(key, default)
    end
    return u.getIntegerForKey(key)
end

--[[--
    Get float value by key, if the key doesn't exist, a default value will return.
    You can set the default value, or it is 0.0f.
]]
function save.getFloat(key, default)
    if default and type(default) == 'number' then
        return u.getFloatForKey(key, default)
    end
    return u.getFloatForKey(key)
end

--[[--
    Get double value by key, if the key doesn't exist, a default value will return.
    You can set the default value, or it is 0.0.
]]
function save.getDouble(key, default)
    if default and type(default) == 'number' then
        return u.getDoubleForKey(key, default)
    end
    return u.getDoubleForKey(key)
end

--[[--
    Get string value by key, if the key doesn't exist, a default value will return.
    You can set the default value, or it is "".
]]
function save.getString(key, default)
    if default and type(default) == 'string' then
        return u.getStringForKey(key, default)
    end
    return u.getStringForKey(key)
end

-- set value methods

--[[--
    Set bool value by key.
]]
function save.Bool(key, bool) u.setBoolForKey(key, bool) end

--[[--
    Set integer value by key.
]]
function save.Integer(key, int) u.setIntegerForKey(key, int) end

--[[--
    Set float value by key.
]]
function save.Float(key, float) u.setFloatForKey(key, float) end

--[[--
    Set double value by key.
]]
function save.Double(key, double) u.setDoubleForKey(key, double) end

--[[--
    Set string value by key.
]]
function save.String(key, str) u.setStringForKey(key, str) end

--[[--
    Save content to xml file
]]
function save.flush() u.flush() end

function save.purgeSharedUserDefault() u.purgeSharedUserDefault() end

function save.getDataFilePath() return u.getXMLFilePath():c_str() end

function save.isDataFileExist() return u.isXMLFileExist() end
