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

--[[
    GameScene
]]
function GameScene:init()
    log('Init Game Scene ...')
    --[[
bool bRet = false;
do
{
    CC_BREAK_IF(!CCScene::init());

    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("isHavingSave"))
    {

        CCUserDefault::sharedUserDefault()->setBoolForKey("isHavingSave", true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("isBGM", true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("isVoice", true);

        CCUserDefault::sharedUserDefault()->flush();
    }

    introLayer = CCLayer::create();

    CCSprite *zakume = CCSprite::create("zakume.png");
    zakume->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    CCActionInterval *fadein = CCFadeIn::create(1.5f);
    CCActionInterval *fadeout = CCFadeOut::create(1.5f);
    CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(GameScene::onLogo));
    CCAction *seq = CCSequence::create(fadein, fadeout, call, NULL);
    introLayer->addChild(zakume);
    zakume->runAction(seq);
    this->addChild(introLayer);

    /*KTools* tool= KTools::create();
    tool->initTableInDB();


    tool->initColumeInDB();


    CCLayer* menuLayer=StartMenu::create();
    this->addChild(menuLayer);*/

    // CCDirector::sharedDirector()->sharedDispatcher()->addDelegate(this);

    bRet = true;
} while (0);

return bRet;
]] --
end
