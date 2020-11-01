#pragma once
#include "cocos2d.h"

#include "Element.h"

class Hero : public HeroElement
{
private:
	virtual void perform(){};

public:
	bool init()
    {
	    bool bRet = false;
        do
        {
            CC_BREAK_IF(!HeroElement::init());
            this->setAnchorPoint(ccp(0.5, 0));

            //this->schedule(schedule_selector(Hero::neicun),0.5f);
            bRet = true;
        } while (0);

        return bRet;
    };

	void setAI(float dt) { perform(); };
	void setID(CCString *character, CCString *role, CCString *group){};
};

namespace AIGenerator
{
    #include "AI/__AI__.hpp"

    // int max_value = meta::reflect<int>().data<2048>(hash("max_int"));

    #define __begin__ if(0) {}
    #define is_begin(varStr) if (strcmp(varStr, name) == 0)
    #define is(varStr) else if (strcmp(varStr, name) == 0)
    #define is_or(varStr, varName) else if ((strcmp(varStr, varName) == 0) || (strcmp(name, varName) == 0))
    #define is_or2(varStr, varName, varName2) else if ((strcmp(varStr, varName) == 0) || (strcmp(name, varName) == 0) || (strcmp(name, varName2) == 0))
    #define is_or3(varStr, varName, varName2, varName3) else if ((strcmp(varStr, varName) == 0) || (strcmp(name, varName) == 0) || (strcmp(name, varName2) == 0) || (strcmp(name, varName3) == 0))
    #define is_and(varStr, varName) else if ((strcmp(varStr, varName) == 0) && (strcmp(role->getCString(), name) == 0))
    // Tags
    #define clone_tag "Clone"

    static Hero *create(CCString *character, CCString *role, CCString *group) 
	{ 
		Hero *pRet;
        // Init AI
        // ninjaEnums id = hero->_id;
        const char *name = character->getCString();
        // string fn_name = "AI_";
        // fn_name += name;
        // std::hash<std::string_view> hash{};
        // meta::func func = meta::resolve<Hero>().func(hash(fn_name));
        // if (func)
        // {
        // }
        // else
        // {
        // }

        __begin__
        is("Sakura") 				        pRet = new AI_Sakura();
        is("Pain") 						    pRet = new AI_Pain();
        is("MaskRaidon") 				    pRet = new AI_Mask();
        is("MaskFudon") 				    pRet = new AI_Mask();
        is("MaskKadon") 				    pRet = new AI_Mask();
        is("Slug") 						    pRet = new AI_Slug();
        is("Centipede") 				    pRet = new AI_Centipede();
        is("Nagato") 					    pRet = new AI_Nagato();
        is("Asuma") 					    pRet = new AI_Asuma();
        is("DevaPath") 					    pRet = new AI_DevaPath();
        is("AsuraPath") 				    pRet = new AI_AsuraPath();
        is("AnimalPath") 				    pRet = new AI_AnimalPath();
        is("Sai") 						    pRet = new AI_Sai();
        is("Tenten") 					    pRet = new AI_Tenten();
        is("Suigetsu") 					    pRet = new AI_Suigetsu();
        is("Konan") 					    pRet = new AI_Konan();
        is("Jiraiya") 					    pRet = new AI_Jiraiya();
        is("Shikamaru") 				    pRet = new AI_Shikamaru();
        is("Sasuke") 					    pRet = new AI_Sasuke();
        is("ImmortalSasuke") 			    pRet = new AI_ImmortalSasuke();
        is("Deidara") 					    pRet = new AI_Deidara();
        is("Minato") 					    pRet = new AI_Minato();
        is("DogWall") 					    pRet = new AI_DogWall();
        is("Kakashi") 					    pRet = new AI_Kakashi();
        is("Tobi") 						    pRet = new AI_Tobi();
        is("Hinata") 					    pRet = new AI_Hinata();
        is("Neji") 						    pRet = new AI_Neji();
        is("Choji") 					    pRet = new AI_Choji();
        is("Itachi") 					    pRet = new AI_Itachi();
        is("Orochimaru") 				    pRet = new AI_Orochimaru();
        is_and("Naruto", clone_tag) 		pRet = new AI_NarutoClone();
        is("Naruto") 					    pRet = new AI_Naruto();
        is("Kurama") 					    pRet = new AI_Kurama();
        is_and("SageNaruto", clone_tag) 	pRet = new AI_SageNarutoClone();
        is_and("RikudoNaruto", clone_tag)	pRet = new AI_RikudoNarutoClone();
        is("SageNaruto") 				    pRet = new AI_SageNaruto();
        is("RikudoNaruto") 				    pRet = new AI_RikudoNaruto();
        is("Gaara") 					    pRet = new AI_Gaara();
        is("Tobirama") 					    pRet = new AI_Tobirama();
        is("Akamaru") 					    pRet = new AI_Akamaru();
        is("Karasu") 					    pRet = new AI_Karasu();
        is("Saso") 						    pRet = new AI_Saso();
        is("Parents") 					    pRet = new AI_Parents();
        is("Sanshouuo") 				    pRet = new AI_Sanshouuo();
        is("Kankuro") 					    pRet = new AI_Kankuro();
        is("Chiyo") 					    pRet = new AI_Chiyo();
        is("Kiba") 						    pRet = new AI_Kiba();
        is("SageJiraiya") 				    pRet = new AI_SageJiraiya();
        is("Karin") 					    pRet = new AI_Karin();
        is("Lee") 						    pRet = new AI_Lee();
        is("RockLee") 					    pRet = new AI_RockLee();
        is("Tsunade") 					    pRet = new AI_Tsunade();
        is("Jugo") 						    pRet = new AI_Jugo();
        is("Kisame") 					    pRet = new AI_Kisame();
        is("Ino") 						    pRet = new AI_Ino();
        is("Hidan") 					    pRet = new AI_Hidan();
        is("Shino") 					    pRet = new AI_Shino();
        is("Hiruzen") 					    pRet = new AI_Hiruzen();
        is("Kakuzu") 					    pRet = new AI_Kakuzu();
        is_or("Roshi", "Han") 			    pRet = new AI_Guardian();

        if (pRet && pRet->init())
        {
            pRet->HeroElement::setID(character, role, group);
            pRet->autorelease();
            return pRet;
        }
        else
        {
            CCLOG("Set AI %s not found", name);
            delete pRet;
            pRet = NULL;
            return NULL;
        }
	};
}