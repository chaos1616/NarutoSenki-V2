--
-- SelectButton
--
SelectButton.Type = {
    Menu = 0,
    Unlock1 = 1,
    Unlock2 = 2,
    skill1 = 3,
    skill2 = 4,
    skill3 = 5,
    Ougis1 = 6,
    Ougis2 = 7
}

local selectBtn = SelectButton

selectBtn.Char_None = 'None'
selectBtn.Char_None2 = 'None2'

local unsupportedList = {
    -- Here are not supported or in dev characters
    'Pain', 'Orochimaru'
}

-- init values to lower case
for k, v in pairs(unsupportedList) do unsupportedList[k] = string.lower(v) end

local function is_not_support(val)
    for _, v in ipairs(unsupportedList) do
        if v == string.lower(val) then return true end
    end
    return false
end

function ns.addUnsupportCharacter(name)
    if name ~= nil then
        if table.has(name) then
            log('Add error %s already in unsupported table', name)
        else
            unsupportedList.insert(name)
        end
    end
end

function SelectButton:init()
    --
end

function setSelectButton(name, isAvailable)
    -- get current select point character name
    if name == selectBtn.Char_None2 then
        -- tools:setTip('LimitedChar')
    elseif name == selectBtn.Char_None then
        -- pass
    elseif isAvailable and not is_not_support(name) then
        log('Select %s ', name)
    else
        log(
            not isAvailable and 'Has selected character %s' or 'Not support %s ',
            name)
    end
end

function SelectButton:spriteToGrey()
    local black = display.newSprite('#Black_select.png')
    black:setAnchorPoint(CCPoint(0.5, 0.5))
    black:setPosition(CCPoint(17, 32))
    self:addChild(black)
end
