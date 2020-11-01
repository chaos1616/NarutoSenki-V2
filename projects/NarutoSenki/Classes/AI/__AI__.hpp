#pragma once
#include "Defines.h"

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

class IAI
{
    AI_API abstract(setClone);
};

// Utilities
#define find_Hero(searchRange, masterRange) this->findEnemy("Hero", searchRange, masterRange)
#define find_Flog(searchRange, masterRange) this->findEnemy("Flog", searchRange, masterRange)
#define find_Tower(searchRange, masterRange) this->findEnemy("Tower", searchRange, masterRange)
#define not_find_Hero(searchRange, masterRange) !this->findEnemy("Hero", searchRange, masterRange)
#define not_find_Flog(searchRange, masterRange) !this->findEnemy("Flog", searchRange, masterRange)
#define not_find_Tower(searchRange, masterRange) !this->findEnemy("Tower", searchRange, masterRange)
