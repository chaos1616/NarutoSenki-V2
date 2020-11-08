require 'utils.utils'

local selectLayer = SelectLayer

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

    local bg_src = 'blue_bg.png'
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

    local cmv1 = CCMoveBy:create(1, -15, 0)
    local cseq1 = CCRepeatForever:create(
                      CCSequence:createWithTwoActions(cmv1, cmv1:reverse()))
    cloud_left:runAction(cseq1)

    local cloud_right = display.newSprite('#cloud.png')
    cloud_right:setAnchorPoint(0, 0)
    cloud_right:setPosition(width - cloud_right:getContentSize().width, 15)
    cloud_right:setFlipY(true)
    self:addChild(cloud_right, 2)

    local cmv2 = CCMoveBy:create(1, 15, 0)
    local cseq2 =
        CCRepeatForever:create(CCSequence:create(cmv2, cmv2:reverse()))
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

    local _selectList = CCArray:create()
    local selectArray = CCArray:create()
    local _pageLayer1 = display.newLayer()
    local _pageLayer2 = display.newLayer()
    local _pageLayer3 = display.newLayer()

    local selectList = ns.CharactersLayout

    local num = #selectList
    local Column = 0
    local Row = 0
    local Page = 0

    for i = 1, num do
        local charName = selectList[i]

        _selectList:addObject(CCString:create(charName))

        Column = i % 7
        Row = i / 7
        Page = toint(i / 21)

        local select_btn = SelectButton:create(charName .. '_select.png')
        select_btn:setDelegate2(self)
        select_btn:setCharName(CCString:create(charName))

        if Page == 0 then
            select_btn:setPosition(
                width / 2 - 36 + (Column - 1) * 27 + Column / 4 * 10,
                height - 112 - (72 * Row))
            _pageLayer1:addChild(select_btn, -Column)
        elseif Page == 1 then
            select_btn:setPosition(
                width / 2 - 36 + (Column - 1) * 27 + Column / 4 * 10,
                height - 112 - (72 * (Row - 3)))
            _pageLayer2:addChild(select_btn, -Column)
        elseif Page == 2 then
            select_btn:setPosition(
                width / 2 - 36 + (Column - 1) * 27 + Column / 4 * 10,
                height - 112 - (72 * (Row - 6)))
            _pageLayer3:addChild(select_btn, -Column)
            -- elseif Page == 3 then
            -- 	select_btn:setPosition(width / 2 - 36 + (Column - 1) * 27 + Column / 4 * 10, height - 112 - (72 * (Row - 9)))
            -- 	_pageLayer4:addChild(select_btn, -Column)
        end

        selectArray:addObject(select_btn)
    end

    self:addChild(_pageLayer1, 5)
    self:addChild(_pageLayer2, 5)
    self:addChild(_pageLayer3, 5)

    _pageLayer2:setVisible(false)
    _pageLayer3:setVisible(false)
    _pageLayer2:setPositionY(2000)
    _pageLayer3:setPositionY(2000)

    local page1_btn = ui.newImageMenuItem(
                          {
            image = '#page1_off.png',
            imagePressed = '#page1_on.png',
            listener = SelectLayer.onPage1Btn
        })
    local page2_btn = ui.newImageMenuItem(
                          {
            image = '#page2_off.png',
            imagePressed = '#page2_on.png',
            listener = SelectLayer.onPage2Btn
        })
    local page3_btn = ui.newImageMenuItem(
                          {
            image = '#page3_off.png',
            imagePressed = '#page3_on.png',
            listener = SelectLayer.onPage3Btn
        })

    local page_menu = ui.newMenu({page1_btn, page2_btn, page3_btn})

    page_menu:alignItemsHorizontallyWithPadding(20)
    page_menu:setPosition(width / 2 + 48, 42)
    self:addChild(page_menu, 10)
    page1_btn:selected()

    selectArray:retain()
    _selectList:retain()

    local hero = _selectList:objectAtIndex(0) -- CCString*
    if hero.getCString ~= nil then
        local _heroHalf = display.newSprite(
                              '#' .. hero:getCString() .. '_half.png', 10, 10)
        _heroHalf:setAnchorPoint(0, 0)
        self:addChild(_heroHalf, 1)

        local _heroName = display.newSprite(
                              '#' .. hero:getCString() .. '_font.png', 100, 20)
        _heroName:setAnchorPoint(0.5, 0)
        self:addChild(self._heroName, 5)
    end

    local _selectBtn = self.selectArray:objectAtIndex(0)
    local _selectImg = display.newSprite('#1p.png',
                                         _selectBtn:getPositionX() - 2,
                                         _selectBtn:getPositionY() - 2)
    _selectImg:setAnchorPoint(0, 0)
    self:addChild(_selectImg, 500)

    local _selectHero = _selectBtn:getCharName():getCString()

    local blink = CCBlink:create(0.6, 1)
    _selectImg:runAction(CCRepeatForever:create(blink))

    -- if adResult == 1 then
    -- 	_teamSelector = display.newLayer()

    -- 	local _teamBg = display.newSprite('#team_bg.png', 0, 185)
    -- 	_teamBg:setAnchorPoint(0, 0)
    -- 	_teamSelector:addChild(_teamBg)

    -- 	_comSelector1 = display.newSprite('#unknow_select.png', 2, 194)
    -- 	_comSelector1:setAnchorPoint(0, 0)
    -- 	_teamSelector:addChild(_comSelector1)

    -- 	_comLabel1 = display.newSprite('#com_label.png')
    -- 	-- _comLabel1:setAnchorPoint(0.5, 0.5) -- default is {0.5, 0.5}
    -- 	_comLabel1:setPosition(
    -- 		_comSelector1:getPositionX() + _comSelector1:getContentSize().width + 2 + 18,
    -- 		_comSelector1:getPositionY() + _comSelector1:getContentSize().height / 2)
    -- 	_teamSelector:addChild(_comLabel1)

    -- 	_comSelector2 = display.newSprite('#unknow_select.png')
    -- 	_comSelector2:setAnchorPoint(0, 0)
    -- 	_comSelector2:setPosition(
    -- 		_comSelector1:getPositionX() + _comSelector1:getContentSize().width + 40,
    -- 		_comSelector1:getPositionY())
    -- 	_teamSelector:addChild(_comSelector2)

    -- 	_comLabel2 = display.newSprite('#com_label.png')
    -- 	_comLabel2:setAnchorPoint(0.5, 0.5)
    -- 	_comLabel2:setPosition(
    -- 		_comSelector2:getPositionX() + _comSelector2:getContentSize().width + 2 + 18,
    -- 		_comSelector2:getPositionY() + _comSelector2:getContentSize().height / 2)
    -- 	_teamSelector:addChild(_comLabel2)

    -- 	self:addChild(_teamSelector, 50)
    -- end

    local ranking_btn = ui.newImageMenuItem(
                            {
            image = '#ranking_btn.png',
            listener = SelectLayer.onRankingBtn
        })
    ranking_btn:setAnchorPoint(1, 0.5)
    local menu3 = ui.newMenu({ranking_btn})
    menu3:setPosition(width - 15, height - 34)
    self:addChild(menu3, 5)

    local start_bt = ui.newImageMenuItem(
                         {
            image = '#start_btn.png',
            listener = SelectLayer.onGameStart
        })
    local menu = ui.newMenu({start_bt})
    menu:setAnchorPoint(0, 0)
    menu:setPosition(width - 40, 36)
    self:addChild(menu, 5)

    local skill_bt = ui.newImageMenuItem(
                         {
            image = '#skill_btn.png',
            listener = SelectLayer.onSkillMenu
        })
    local menu2 = ui.newMenu({skill_bt})
    menu2:setAnchorPoint(0, 0)
    menu2:setPosition(width - 35, 96)
    self:addChild(menu2, 5)

    if save.getBool('isBGM') then
        audio.playMusic(ns.music.SELECT_MUSIC, true)
    end

    -- if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID then
    -- 	self:setKeypadEnabled(true)
    -- end

    -- tools:addSprites('Record.plist',
    --                  'Record2.plist',
    --                  'UI.plist',
    --                  'Report.plist',
    --                  'Ougis.plist',
    --                  'Ougis2.plist',
    --                  'Map.plist',
    --                  'Gears.plist'
    -- )
end
