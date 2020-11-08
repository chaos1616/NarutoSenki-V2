#ifndef __AI_HPP__
#define __AI_HPP__
#include "Defines.h"
#include "Characters.h"

// Implementations
#include "AI_Akamaru.hpp"
#include "AI_Asuma.hpp"
#include "AI_Centipede.hpp"
#include "AI_Chiyo.hpp"
#include "AI_Choji.hpp"
#include "AI_Deidara.hpp"
#include "AI_DogWall.hpp"
#include "AI_Gaara.hpp"
#include "AI_Hidan.hpp"
#include "AI_Hinata.hpp"
#include "AI_Hiruzen.hpp"
#include "AI_ImmortalSasuke.hpp"
#include "AI_Ino.hpp"
#include "AI_Itachi.hpp"
#include "AI_Jiraiya.hpp"
#include "AI_Jugo.hpp"
#include "AI_Kakashi.hpp"
#include "AI_Kakuzu.hpp"
#include "AI_Kankuro.hpp"
#include "AI_Karasu.hpp"
#include "AI_Karin.hpp"
#include "AI_Kiba.hpp"
#include "AI_Kisame.hpp"
#include "AI_Konan.hpp"
#include "AI_Kurama.hpp"
#include "AI_Lee.hpp"
#include "AI_Mask.hpp"
#include "AI_Minato.hpp"
#include "AI_Nagato.hpp"
#include "AI_Naruto.hpp"
#include "AI_Neji.hpp"
#include "AI_Orochimaru.hpp"
// Pain
#include "AI_Pain.hpp"
#include "AI_AnimalPath.hpp"
#include "AI_AsuraPath.hpp"
#include "AI_DevaPath.hpp"

#include "AI_Parents.hpp"
#include "AI_RikudoNaruto.hpp"
#include "AI_RockLee.hpp"
#include "AI_SageJiraiya.hpp"
#include "AI_SageNaruto.hpp"
#include "AI_Sai.hpp"
#include "AI_Sakura.hpp"
#include "AI_Sanshouuo.hpp"
#include "AI_Saso.hpp"
#include "AI_Sasuke.hpp"
#include "AI_Shikamaru.hpp"
#include "AI_Shino.hpp"
#include "AI_Slug.hpp"
#include "AI_Suigetsu.hpp"
#include "AI_Tenten.hpp"
#include "AI_Tobi.hpp"
#include "AI_Tobirama.hpp"
#include "AI_Tsunade.hpp"

// Guardian
// Han, Roshi
#include "AI_Guardian.hpp"

// Clone
#include "AI_NarutoClone.hpp"
#include "AI_SageNarutoClone.hpp"
#include "AI_RikudoNarutoClone.hpp"

#define AI_API
#define abstract(varName) virtual void on_##varName() {}

//     AI_API abstract(setClone);


// Utilities
#define find_Hero(searchRange, masterRange) this->findEnemy("Hero", searchRange, masterRange)
#define find_Flog(searchRange, masterRange) this->findEnemy("Flog", searchRange, masterRange)
#define find_Tower(searchRange, masterRange) this->findEnemy("Tower", searchRange, masterRange)
#define not_find_Hero(searchRange, masterRange) !this->findEnemy("Hero", searchRange, masterRange)
#define not_find_Flog(searchRange, masterRange) !this->findEnemy("Flog", searchRange, masterRange)
#define not_find_Tower(searchRange, masterRange) !this->findEnemy("Tower", searchRange, masterRange)

#include <iostream>
#include <typeinfo>
#include <map>
// int max_value = meta::reflect<int>().data<2048>(hash("max_int"));

#define __begin__ if(0) {}
#define is_begin(varStr) if (strcmp(varStr, name) == 0)
#define is(varStr) else if (strcmp(varStr, name) == 0)
#define is_or(varStr, varName) else if ((strcmp(varStr, varName) == 0) || (strcmp(name, varName) == 0))
#define is_or2(varStr, varName, varName2) else if ((strcmp(varStr, varName) == 0) || (strcmp(name, varName) == 0) || (strcmp(name, varName2) == 0))
#define is_or3(varStr, varName, varName2, varName3) else if ((strcmp(varStr, varName) == 0) || (strcmp(name, varName) == 0) || (strcmp(name, varName2) == 0) || (strcmp(name, varName3) == 0))
#define is_tag(tag) if (strcmp(role->getCString(), tag) == 0)

class AIProvider
{
    // static const map<std::string, type> ai_providers;

public:
    static HeroElement *createAI(CCString *character, CCString *role, CCString *group)
    {
        Hero *pAI;
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
        is("Sakura") 				        pAI = new AI_Sakura();
        is("Pain") 						    pAI = new AI_Pain();
        is("MaskRaidon") 				    pAI = new AI_Mask();
        is("MaskFudon") 				    pAI = new AI_Mask();
        is("MaskKadon") 				    pAI = new AI_Mask();
        is("Slug") 						    pAI = new AI_Slug();
        is("Centipede") 				    pAI = new AI_Centipede();
        is("Nagato") 					    pAI = new AI_Nagato();
        is("Asuma") 					    pAI = new AI_Asuma();
        is("DevaPath") 					    pAI = new AI_DevaPath();
        is("AsuraPath") 				    pAI = new AI_AsuraPath();
        is("AnimalPath") 				    pAI = new AI_AnimalPath();
        is("Sai") 						    pAI = new AI_Sai();
        is("Tenten") 					    pAI = new AI_Tenten();
        is("Suigetsu") 					    pAI = new AI_Suigetsu();
        is("Konan") 					    pAI = new AI_Konan();
        is("Jiraiya") 					    pAI = new AI_Jiraiya();
        is("Shikamaru") 				    pAI = new AI_Shikamaru();
        is("Sasuke") 					    pAI = new AI_Sasuke();
        is("ImmortalSasuke") 			    pAI = new AI_ImmortalSasuke();
        is("Deidara") 					    pAI = new AI_Deidara();
        is("Minato") 					    pAI = new AI_Minato();
        is("DogWall") 					    pAI = new AI_DogWall();
        is("Kakashi") 					    pAI = new AI_Kakashi();
        is("Tobi") 						    pAI = new AI_Tobi();
        is("Hinata") 					    pAI = new AI_Hinata();
        is("Neji") 						    pAI = new AI_Neji();
        is("Choji") 					    pAI = new AI_Choji();
        is("Itachi") 					    pAI = new AI_Itachi();
        is("Orochimaru") 				    pAI = new AI_Orochimaru();
        is("Kurama") 					    pAI = new AI_Kurama();
        is("Naruto") 		                is_tag(K_TAG_CLONE) pAI = new AI_NarutoClone();         else pAI = new AI_Naruto();
        is("SageNaruto") 				    is_tag(K_TAG_CLONE) pAI = new AI_SageNarutoClone();     else pAI = new AI_SageNaruto();
        is("RikudoNaruto") 				    is_tag(K_TAG_CLONE) pAI = new AI_RikudoNarutoClone();   else pAI = new AI_RikudoNaruto();
        is("Gaara") 					    pAI = new AI_Gaara();
        is("Tobirama") 					    pAI = new AI_Tobirama();
        is("Akamaru") 					    pAI = new AI_Akamaru();
        is("Karasu") 					    pAI = new AI_Karasu();
        is("Saso") 						    pAI = new AI_Saso();
        is("Parents") 					    pAI = new AI_Parents();
        is("Sanshouuo") 				    pAI = new AI_Sanshouuo();
        is("Kankuro") 					    pAI = new AI_Kankuro();
        is("Chiyo") 					    pAI = new AI_Chiyo();
        is("Kiba") 						    pAI = new AI_Kiba();
        is("SageJiraiya") 				    pAI = new AI_SageJiraiya();
        is("Karin") 					    pAI = new AI_Karin();
        is("Lee") 						    pAI = new AI_Lee();
        is("RockLee") 					    pAI = new AI_RockLee();
        is("Tsunade") 					    pAI = new AI_Tsunade();
        is("Jugo") 						    pAI = new AI_Jugo();
        is("Kisame") 					    pAI = new AI_Kisame();
        is("Ino") 						    pAI = new AI_Ino();
        is("Hidan") 					    pAI = new AI_Hidan();
        is("Shino") 					    pAI = new AI_Shino();
        is("Hiruzen") 					    pAI = new AI_Hiruzen();
        is("Kakuzu") 					    pAI = new AI_Kakuzu();
        is_or("Roshi", "Han") 			    pAI = new AI_Guardian();

        if (!pAI)
        {
            CCLog("not found AI %s", name);
            CCAssert(0, "Not found character");
            return NULL;
        }

        if (pAI->init())
        {
            pAI->setID(character, role, group);
            pAI->autorelease();
            return pAI;
        }
        else
        {
            CCLOG("Set AI %s not found", name);
            delete pAI;
            pAI = NULL;
            return NULL;
        }
    };

    // static bool addAI(const char *name, type t)
    // {
    // }
};

#endif
