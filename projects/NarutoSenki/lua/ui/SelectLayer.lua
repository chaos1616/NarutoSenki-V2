--
-- SelectLayer
--
ns.enableCustomSelect = false

local selectLayer = SelectLayer

selectLayer.pageNum = 3

local comLabel1
local comLabel2

local pageLayers = {}
local pageButtons = {}

function SelectLayer:init()
    log('Initial SelectLayer...')

    tools.addSprites('Record.plist', 'Record2.plist', 'UI.plist',
                     'Report.plist', 'Ougis.plist', 'Ougis2.plist', 'Map.plist',
                     'Gears.plist')

    -- if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) then
    -- if (KTools:checkMD5() == 0) then
    -- 	SimpleAudioEngine:sharedEngine():stopBackgroundMusic()
    -- 	CCDirector:sharedDirector():end()
    -- 	return false
    -- end
    -- end

    local width, height = display.width, display.height

    local bg_src
    if ns.enableCustomSelect then
        bg_src = 'red_bg.png'
    else
        bg_src = 'blue_bg.png'
    end
    local bgSprite = display.newSprite(bg_src, 0, 0)
    bgSprite:setAnchorPoint(0, 0)
    bgSprite:fullScreen()
    self:addChild(bgSprite, -5)

    -- produce groud
    local gold_left = display.newSprite('#gold_left.png', 0, 20)
    gold_left:setAnchorPoint(0, 0)
    self:addChild(gold_left, 1)

    local gold_right = display.newSprite('#gold_right.png')
    gold_right:setAnchorPoint(0, 1)
    gold_right:setPosition(width - gold_right:getContentSize().width - 20,
                           height - 20)
    self:addChild(gold_right, 1)

    -- produce the cloud
    local cloud_left = display.newSprite('#cloud.png', 0, 15)
    cloud_left:setAnchorPoint(0, 0)
    cloud_left:setFlipX(true)
    cloud_left:setFlipY(true)
    self:addChild(cloud_left, 2)

    local cmv1 = CCMoveBy:create(1, CCPoint(-15, 0))
    local cseq1 = CCRepeatForever:create(
                      transition.sequence({cmv1, cmv1:reverse()}))
    cloud_left:runAction(cseq1)

    local cloud_right = display.newSprite('#cloud.png')
    cloud_right:setAnchorPoint(0, 0)
    cloud_right:setPosition(width - cloud_right:getContentSize().width, 15)
    cloud_right:setFlipY(true)
    self:addChild(cloud_right, 2)

    local cmv2 = CCMoveBy:create(1, CCPoint(15, 0))
    local cseq2 = CCRepeatForever:create(
                      transition.sequence({cmv2, cmv2:reverse()}))
    cloud_right:runAction(cseq2)

    local cloud_top = display.newSprite('#cloud_top.png')
    cloud_top:setAnchorPoint(0.5, 0)
    cloud_top:setPosition(width / 2,
                          height - (cloud_top:getContentSize().height + 12))
    self:addChild(cloud_top, 1)

    -- produce the menu_bar
    local menu_bar_b = display.newSprite('menu_bar2.png')
    menu_bar_b:setAnchorPoint(0, 0)
    menu_bar_b:fullScreen()
    self:addChild(menu_bar_b, 2)

    local menu_bar_t = display.newSprite('menu_bar3.png')
    menu_bar_t:setAnchorPoint(0, 0)
    menu_bar_t:setPosition(0, height - menu_bar_t:getContentSize().height)
    menu_bar_t:fullScreen()
    self:addChild(menu_bar_t, 2)

    local select_title = display.newSprite('#hcmode_title.png')
    select_title:setAnchorPoint(0, 0)
    select_title:setPosition(2,
                             height - select_title:getContentSize().height - 2)
    self:addChild(select_title, 3)

    local selectNameList = CCArray:create()
    local selectButtons = CCArray:create()
    for i = 1, self.pageNum do
        -- initial page list
        local index = i
        local pageLayer = display.newLayer()
        local page_btn = ui.newImageMenuItem(
                             {
                image = '#page' .. tostring(i) .. '_off.png',
                imageSelected = '#page' .. tostring(i) .. '_on.png',
                listener = function()
                    return SelectLayer:onPageButtonClick(index)
                end
            })

        self:addChild(pageLayer, 5)
        if i == 1 then
            pageLayer:show()
            page_btn:selected()
        else
            pageLayer:hide()
            pageLayer:setPositionY(2000)
        end

        table.insert(pageLayers, pageLayer)
        table.insert(pageButtons, page_btn)
    end

    local charactersList = ns.CharactersLayout
    local pageNum = #pageLayers

    for i = 1, #charactersList do
        local charName = charactersList[i]

        selectNameList:addObject(CCString:create(charName))

        local idx = i - 1
        local Column = idx % 7
        local Row = toint(idx / 7)
        local Page = toint(idx / 21)
        -- log(
        --     ' -> load character %s\t[ Column: %d Row: %d Page: %d ] [ pos: %f, %f ]',
        --     charName, Column, Row, Page,
        --     width / 2 - 36 + (Column - 1) * 27 + Column / 4 * 10,
        --     height - 112 - (72 * (Row - 3 * Page)))

        local select_btn = SelectButton:create(charName .. '_select.png')
        select_btn:setSelectLayer(self)
        select_btn:setCharName(CCString:create(charName))
        --           -- LAYOUT --
        -- --- LEFT ---        --- RIGHT ---
        -- 1, 2, 3, 4, padding 5, 6, 7
        local groupPadding = toint(Column / 4) * 10
        select_btn:setPosition(
            width / 2 - 36 + (Column - 1) * 27 + groupPadding,
            height - 112 - (72 * (Row - 3 * Page)))

        if Page + 1 > pageNum then
            log('Select page index out of range')
            break
        end
        pageLayers[Page + 1]:addChild(select_btn, -Column)

        selectButtons:addObject(select_btn)
        hook.registerInitHandlerOnly(select_btn)
    end

    local page_menu = ui.newMenu(pageButtons)
    page_menu:alignItemsHorizontallyWithPadding(20)
    page_menu:setPosition(width / 2 + 48, 42)
    self:addChild(page_menu, 10)

    selectButtons:retain()
    selectNameList:retain()
    self:setSelectButtons(selectButtons)
    self:setSelectList(selectNameList)

    local hero = tolua.cast(selectNameList:objectAtIndex(0), 'CCString') -- CCString*
    if hero.getCString ~= nil then
        local heroHalfImage = display.newSprite(
                                  '#' .. hero:getCString() .. '_half.png', 10,
                                  10)
        heroHalfImage:setAnchorPoint(0, 0)
        self:addChild(heroHalfImage, 1)

        local heroName = display.newSprite(
                             '#' .. hero:getCString() .. '_font.png', 100, 20)
        heroName:setAnchorPoint(0.5, 0)
        self:addChild(heroName, 5)

        self:setHeroName(heroName)
        self:setHeroHalf(heroHalfImage)
    end

    local selectBtn = tolua.cast(selectButtons:objectAtIndex(0), 'SelectButton')
    local selectImg = display.newSprite('#1p.png', selectBtn:getPositionX() - 2,
                                        selectBtn:getPositionY() - 2)
    selectImg:setAnchorPoint(0, 0)
    self:addChild(selectImg, 500)
    self:setSelectImg(selectImg)

    local selectHero = selectBtn:getCharName():getCString()
    self:setSelectHero(selectHero)

    local blink = CCBlink:create(0.6, 1)
    selectImg:runAction(CCRepeatForever:create(blink))

    if ns.enableCustomSelect then
        local teamSelector = display.newLayer()

        local teamBg = display.newSprite('#team_bg.png', 0, 185)
        teamBg:setAnchorPoint(0, 0)
        teamSelector:addChild(teamBg)

        local comSelector1 = display.newSprite('#unknow_select.png', 2, 194)
        comSelector1:setAnchorPoint(0, 0)
        teamSelector:addChild(comSelector1)

        comLabel1 = display.newSprite('#com_label.png')
        -- comLabel1:setAnchorPoint(0.5, 0.5) -- default is {0.5, 0.5}
        comLabel1:setPosition(comSelector1:getPositionX() +
                                  comSelector1:getContentSize().width + 2 + 18,
                              comSelector1:getPositionY() +
                                  comSelector1:getContentSize().height / 2)
        teamSelector:addChild(comLabel1)

        local comSelector2 = display.newSprite('#unknow_select.png')
        comSelector2:setAnchorPoint(0, 0)
        comSelector2:setPosition(comSelector1:getPositionX() +
                                     comSelector1:getContentSize().width + 40,
                                 comSelector1:getPositionY())
        teamSelector:addChild(comSelector2)

        comLabel2 = display.newSprite('#com_label.png')
        -- comLabel2:setAnchorPoint(0.5, 0.5)
        comLabel2:setPosition(comSelector2:getPositionX() +
                                  comSelector2:getContentSize().width + 2 + 18,
                              comSelector2:getPositionY() +
                                  comSelector2:getContentSize().height / 2)
        teamSelector:addChild(comLabel2)

        self:addChild(teamSelector, 50)

        self:setComSelector1(comSelector1)
        self:setComLabel1(comLabel1)
        self:setComSelector2(comSelector2)
        self:setComLabel2(comLabel2)
    end

    local ranking_btn = ui.newImageMenuItem(
                            {
            image = '#ranking_btn.png',
            listener = handler(self, SelectLayer.onRankingBtn)
        })
    ranking_btn:setAnchorPoint(1, 0.5)
    local menu3 = ui.newMenu({ranking_btn})
    menu3:setPosition(width - 15, height - 34)
    self:addChild(menu3, 5)

    local start_btn = ui.newImageMenuItem(
                          {
            image = '#start_btn.png',
            -- call c++ layer function
            listener = function() self:onGameStart() end
        })
    local menu = ui.newMenu({start_btn})
    menu:setAnchorPoint(0, 0)
    menu:setPosition(width - 40, 36)
    self:addChild(menu, 5)

    local skill_btn = ui.newImageMenuItem(
                          {
            image = '#skill_btn.png',
            listener = handler(self, SelectLayer.onSkillMenu)
        })
    local menu2 = ui.newMenu({skill_btn})
    menu2:setAnchorPoint(0, 0)
    menu2:setPosition(width - 35, 96)
    self:addChild(menu2, 5)

    if save.isBGM() then audio.playMusic(ns.music.SELECT_MUSIC, true) end

    -- if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID then
    self:setKeypadEnabled(true)
    -- end
end

function SelectLayer:onQuestBtn()
    -- not support
    self:setTip('ComingSoon')
end

function SelectLayer:onRankingBtn()
    -- not support
    self:setTip('ComingSoon')
end

function SelectLayer:onSkillMenu()
    local scene = CCScene:create()
    local skillLayer = SkillLayer:create()
    skillLayer:setDelegate(self)
    skillLayer:initInterface()
    scene:addChild(skillLayer)

    director.pushScene(scene)
end

function SelectLayer:onPageButtonClick(index)
    audio.playSound(ns.menu.SELECT_SOUND)

    for i, pageBtn in pairs(pageButtons) do
        if i == index then
            pageBtn:selected()
        else
            pageBtn:unselected()
        end
    end
    for i, pageLayer in pairs(pageLayers) do
        if i == index then
            pageLayer:show()
            pageLayer:setPositionY(0)
        else
            pageLayer:hide()
            pageLayer:setPositionY(10000)
        end
    end
end

function SelectLayer:keyBackClicked() log('keyback selectlayer') end

function backToStartMenu()
    audio.playSound('Audio/Menu/cancel.ogg')
    local menuScene = CCScene:create()
    local menuLayer = StartMenu:create()

    hook.registerInitHandlerOnly(menuLayer, StartMenu.init)
    menuScene:addChild(menuLayer)
    director.replaceSceneWithFade(menuScene, 1.5)
end
