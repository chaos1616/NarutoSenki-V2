require 'utils.utils'

-- Hook for GameLayer
hook = {}

local display = require 'framework.display'

hook.onSelectedCallback = function(name)
    print('Invoke callback : onSelectedCallback [ %s ]', name)
end

hook.onGameStartCallback =
    function() print('Invoke callback : onGameStart') end
hook.onGameStartedCallback =
    function() print('Invoke callback : onGameStarted') end
hook.onGameEndedCallback =
    function() print('Invoke callback : onGameEnded') end
hook.onInitTileMapCallback =
    function() print('Invoke callback : onInitTileMap') end
hook.onInitEffectsCallback =
    function() print('Invoke callback : onInitEffects') end
hook.onInitHerosCallback =
    function() print('Invoke callback : onInitHeros') end

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

local notSupportedList = {'Pain'}

function setSelectButton(name, isAvailable)
    -- get current select point character name
    if name == 'None2' then
        tools:setTip('LimitedChar')
    elseif name == 'None' then
        -- pass
    elseif isAvailable and not table.has(notSupportedList, name) then
        log('Select character       -> %s ', name)
    else
        log('Not support character  -> %s ', name)
    end
end

--[[    GameScene
]]
function GameScene:init()
    log('Init Game Scene ...')

    -- local ud = cc.UserDefault:sharedUserDefault()
    -- if not ud:getBoolForKey('isHavingSave') then
    --     ud:setBoolForKey('isHavingSave', true)
    --     ud:setBoolForKey('isBGM', true)
    --     ud:setBoolForKey('isVoice', true)
    --     ud:flush()
    -- end

    -- local introLayer = display.newLayer()

    -- local logoImage = display.newSprite('zakume.png', display.width / 2, display.height / 2)

    -- local fadein = cc.FadeIn:create(1.5)
    -- local fadeout = cc.FadeOut:create(1.5)
    -- local call = cc.CallFunc:create(self, GameScene.onLogo)
    -- local seq = cc.Sequence:create(fadein, fadeout, call, nil)
    -- introLayer:addChild(logoImage)
    -- logoImage:runAction(seq)
    -- self:addChild(introLayer)

    -- KTools* tool= KTools:create()
    -- tool:initTableInDB()
    -- tool:initColumeInDB()
    -- CCLayer* menuLayer=StartMenu:create()
    -- self:addChild(menuLayer)

    -- CCDirector:sharedDirector():sharedDispatcher():addDelegate(self)
end

function NetworkLayer_Init(self)
	if tools.is_c_type(self, 'NetwordLayer') then
	end

		tools.addSprites(
            'Record.plist',
            'Record2.plist',
            'UI.plist',
            'Report.plist',
            'Ougis.plist',
            'Ougis2.plist',
            'Map.plist',
            'Gears.plist'
        )

		-- KTools *tool = KTools:create()
		-- if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) then
			-- if (tool:checkMD5() == 0) then
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

		--produce groud
		local gold_left = display.newSprite('#gold_left.png', 0, 20)
		gold_left:setAnchorPoint(0, 0)
		self:addChild(gold_left, 1)

		local gold_right = display.newSprite('#gold_right.png')
		gold_right:setAnchorPoint(0, 1)
		gold_right:setPosition(width - gold_right:getContentSize().width - 20, height - 20)
		self:addChild(gold_right, 1)

		--produce the cloud
		local cloud_left = display.newSprite('#cloud.png', 0, 15)
		cloud_left:setAnchorPoint(0, 0)
		cloud_left:setFlipX(true)
		cloud_left:setFlipY(true)
		self:addChild(cloud_left, 2)

		local cmv1 = CCMoveBy:create(1, -15, 0)
		local cseq1 = CCRepeatForever:create(CCSequence:createWithTwoActions(cmv1, cmv1:reverse()))
		cloud_left:runAction(cseq1)

		local cloud_right = display.newSprite('#cloud.png')
		cloud_right:setAnchorPoint(0, 0)
		cloud_right:setPosition(width - cloud_right:getContentSize().width, 15)
		cloud_right:setFlipY(true)
		self:addChild(cloud_right, 2)

		local cmv2 = CCMoveBy:create(1, 15, 0)
		local cseq2 = CCRepeatForever:create(CCSequence:create(cmv2, cmv2:reverse(), nil))
		cloud_right:runAction(cseq2)

		local cloud_top = display.newSprite('#cloud_top.png')
		cloud_top:setAnchorPoint(0.5, 0)
		cloud_top:setPosition(width / 2, height - (cloud_top:getContentSize().height + 12))
		self:addChild(cloud_top, 1)

		--produce the menu_bar
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
		select_title:setPosition(2, height - select_title:getContentSize().height - 2)
		self:addChild(select_title, 3)

		self._selectList = CCArray:create()
		self.selectArray = CCArray:create()
		self._pageLayer1 = display.newLayer()
		self._pageLayer2 = display.newLayer()
		self._pageLayer3 = display.newLayer()

		local selectList = {
			-- Page One
			'Naruto', 'Sakura', 'Sai', 'Kakashi',
			'None', 'None', 'None',
			'Shikamaru', 'Ino', 'Choji', 'Asuma',
			'Kiba', 'Hinata', 'Shino',
			'Neji', 'Tenten', 'Lee', 'None',
			'None', 'None', 'None',
			-- Page Two
			'None', 'Tobirama', 'Hiruzen', 'Minato',
			'Jiraiya', 'Tsunade', 'Orochimaru',
			'None', 'Deidara', 'Kakuzu', 'Hidan',
			'Tobi', 'Konan', 'Pain',
			'Itachi', 'Kisame', 'None', 'None',
			'None', 'None', 'None',
			-- Page Three
			'Sasuke', 'Karin', 'Suigetsu', 'Jugo',
			'None', 'None', 'None',
			'Gaara', 'None', 'Kankuro', 'Chiyo',
			'None', 'None', 'None',
			'None', 'None', 'None', 'None',
			'None', 'None', 'None'
        }

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

			local select_btn = SelectButton:create(charName..'_select.png')
			select_btn:setDelegate2(self)
			select_btn:setCharName(CCString:create(charName))

            if Page == 0 then
				select_btn:setPosition(width / 2 - 36 + (Column - 1) * 27 + Column / 4 * 10, height - 112 - (72 * Row))
				_pageLayer1:addChild(select_btn, -Column)
			elseif Page == 1 then
				select_btn:setPosition(width / 2 - 36 + (Column - 1) * 27 + Column / 4 * 10, height - 112 - (72 * (Row - 3)))
				_pageLayer2:addChild(select_btn, -Column)
			elseif Page == 2 then
				select_btn:setPosition(width / 2 - 36 + (Column - 1) * 27 + Column / 4 * 10, height - 112 - (72 * (Row - 6)))
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

		page1_btn = CCMenuItemSprite:create(display.newSprite('#page1_off.png'), display.newSprite('#page1_on.png'), self, NetworkLayer.onPage1Btn)
		page2_btn = CCMenuItemSprite:create(display.newSprite('#page2_off.png'), display.newSprite('#page2_on.png'), self, NetworkLayer.onPage2Btn)
		page3_btn = CCMenuItemSprite:create(display.newSprite('#page3_off.png'), display.newSprite('#page3_on.png'), self, NetworkLayer.onPage3Btn)

		page_menu = CCMenu:create(page1_btn, page2_btn, page3_btn, nil)

		page_menu:alignItemsHorizontallyWithPadding(20)
		page_menu:setPosition(width / 2 + 48, 42)
		self:addChild(page_menu, 10)
		page1_btn:selected()

		selectArray:retain()
		_selectList:retain()

		local hero = (cc.String *)_selectList:objectAtIndex(0)

		local path = cc.String:createWithFormat('%s_half.png', hero:getCString()):getCString()
		_heroHalf = CCSprite:createWithSpriteFrameName(path)
		_heroHalf:setAnchorPoint(0, 0)
		_heroHalf:setPosition(10, 10)
		self:addChild(_heroHalf, 1)

		local namePath = cc.String:createWithFormat('%s_font.png', hero:getCString()):getCString()
		_heroName = CCSprite:createWithSpriteFrameName(namePath)
		_heroName:setAnchorPoint(0.5, 0)
		_heroName:setPosition(100, 20)
		self:addChild(_heroName, 5)

		local _selectImg = display.newSprite('#1p.png')
		_selectImg:setAnchorPoint(0, 0)
		local pObject = selectArray:objectAtIndex(0)
		_selectImg:setPosition(pObject:getPositionX() - 2, pObject:getPositionY() - 2)
		self:addChild(_selectImg, 500)

		_selectHero = pObject:getCharName():getCString()

		local blink = CCBlink:create(0.6, 1)
		_selectImg:runAction(CCRepeatForever:create(blink))

		if adResult == 1 then
			_teamSelector = display.newLayer()

			local _teamBg = display.newSprite('#team_bg.png')
			_teamBg:setAnchorPoint(0, 0)
			_teamBg:setPosition(0, 185)
			_teamSelector:addChild(_teamBg)

			_comSelector1 = display.newSprite('#unknow_select.png')
			_comSelector1:setAnchorPoint(0, 0)
			_comSelector1:setPosition(2, 194)
			_teamSelector:addChild(_comSelector1)

			_comLabel1 = display.newSprite('#com_label.png')
			_comLabel1:setAnchorPoint(0.5, 0.5)
			_comLabel1:setPosition(_comSelector1:getPositionX() + _comSelector1:getContentSize().width + 2 + 18, _comSelector1:getPositionY() + _comSelector1:getContentSize().height / 2))
			_teamSelector:addChild(_comLabel1)

			_comSelector2 = display.newSprite('#unknow_select.png')
			_comSelector2:setAnchorPoint(0, 0)
			_comSelector2:setPosition(_comSelector1:getPositionX() + _comSelector1:getContentSize().width + 40, _comSelector1:getPositionY())
			_teamSelector:addChild(_comSelector2)

			_comLabel2 = display.newSprite('#com_label.png')
			_comLabel2:setAnchorPoint(0.5, 0.5)
			_comLabel2:setPosition(_comSelector2:getPositionX() + _comSelector2:getContentSize().width + 2 + 18, _comSelector2:getPositionY() + _comSelector2:getContentSize().height / 2))
			_teamSelector:addChild(_comLabel2)

			self:addChild(_teamSelector, 50)
        end

		local ranking_btn = CCMenuItemSprite:create(display.newSprite('#ranking_btn.png'), nil, nil, self, menu_selector(NetworkLayer:onRankingBtn))
		local menu3 = CCMenu:create(ranking_btn, nil)
		ranking_btn:setAnchorPoint(1, 0.5)
		menu3:setPosition(width - 15, height - 34)
		self:addChild(menu3, 5)

		local start_bt = CCMenuItemSprite:create(display.newSprite('#start_btn.png'), nil, nil, self, menu_selector(NetworkLayer:onGameStart))
		local menu = CCMenu:create(start_bt, nil)
		menu:setAnchorPoint(0, 0)
		menu:setPosition(width - 40, 36)
		self:addChild(menu, 5)

		local skill_bt = CCMenuItemSprite:create(display.newSprite('#skill_btn.png'), nil, nil, self, menu_selector(NetworkLayer:onSkillMenu))
		local menu2 = CCMenu:create(skill_bt, nil)
		menu2:setAnchorPoint(0, 0)
		menu2:setPosition(width - 35, 96)
		self:addChild(menu2, 5)

		if CCUserDefault:sharedUserDefault():getBoolForKey('isBGM') == true then
			SimpleAudioEngine:sharedEngine():playBackgroundMusic(SELECT_MUSIC, true)
		end

		-- if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID then
		-- 	self:setKeypadEnabled(true)
		-- end
end

-- for key, value in pairs(_G) do
--     print(key,value)
-- end
