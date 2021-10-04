#pragma once

// Shinobi
#include "Shinobi/Asuma.hpp"
#include "Shinobi/Chiyo.hpp"
#include "Shinobi/Choji.hpp"
#include "Shinobi/Deidara.hpp"
#include "Shinobi/Gaara.hpp"
#include "Shinobi/Hidan.hpp"
#include "Shinobi/Hinata.hpp"
#include "Shinobi/Hiruzen.hpp"
#include "Shinobi/Ino.hpp"
#include "Shinobi/Itachi.hpp"
#include "Shinobi/Jiraiya.hpp"
#include "Shinobi/Jugo.hpp"
#include "Shinobi/Kakashi.hpp"
#include "Shinobi/Kakuzu.hpp"
#include "Shinobi/Kankuro.hpp"
#include "Shinobi/Karin.hpp"
#include "Shinobi/Kiba.hpp"
#include "Shinobi/Kisame.hpp"
#include "Shinobi/Konan.hpp"
#include "Shinobi/Lee.hpp"
#include "Shinobi/Minato.hpp"
#include "Shinobi/Nagato.hpp"
#include "Shinobi/Naruto.hpp"
#include "Shinobi/Neji.hpp"
#include "Shinobi/Orochimaru.hpp"
// Pain
#include "Shinobi/Pain.hpp"
#include "Shinobi/AnimalPath.hpp"
#include "Shinobi/AsuraPath.hpp"
#include "Shinobi/DevaPath.hpp"

#include "Shinobi/Sai.hpp"
#include "Shinobi/Sakura.hpp"
#include "Shinobi/Sasuke.hpp"
#include "Shinobi/Shikamaru.hpp"
#include "Shinobi/Shino.hpp"
#include "Shinobi/Suigetsu.hpp"
#include "Shinobi/Tenten.hpp"
#include "Shinobi/Tobi.hpp"
#include "Shinobi/Tobirama.hpp"
#include "Shinobi/Tsunade.hpp"

// Bunshin
#include "Shinobi/Bunshin/NarutoClone.hpp"
#include "Shinobi/Bunshin/SageNarutoClone.hpp"
#include "Shinobi/Bunshin/RikudoNarutoClone.hpp"

// Guardian
// Han, Roshi
#include "Guardian/Guardian.hpp"

// Jutsu

// Kuchiyose
#include "Kuchiyose/Akamaru.hpp"
#include "Kuchiyose/Centipede.hpp"
#include "Kuchiyose/DogWall.hpp"
#include "Kuchiyose/Karasu.hpp"
#include "Kuchiyose/Kurama.hpp"
#include "Kuchiyose/Mask.hpp"
#include "Kuchiyose/Parents.hpp"
#include "Kuchiyose/Sanshouuo.hpp"
#include "Kuchiyose/Saso.hpp"
#include "Kuchiyose/Slug.hpp"

#define __begin__ if(0) {}
#define is(var) else if (is_same(var, name))
#define is_or(var1, var2) else if (is_same(var1, name) || is_same(var2, name))
#define is_tag(tag) if (is_same(role->getCString(), tag))

// TODO: Impl a default AI logic
class DefaultAI : public Hero
{
	void perform()
	{
	}
};

class Provider
{
public:
	static Hero *create(CCString *character, CCString *role, CCString *group)
	{
		Hero *ptr;
		const char *name = character->getCString();

		__begin__
		is("Sakura") 						ptr = new Sakura();
		is("Pain") 							ptr = new Pain();
		is("MaskRaiton") 					ptr = new Mask();
		is("MaskFuton") 					ptr = new Mask();
		is("MaskKaton") 					ptr = new Mask();
		is("Slug") 							ptr = new Slug();
		is("Centipede") 					ptr = new Centipede();
		is("Nagato") 						ptr = new Nagato();
		is("Asuma") 						ptr = new Asuma();
		is("DevaPath") 						ptr = new DevaPath();
		is("AsuraPath") 					ptr = new AsuraPath();
		is("AnimalPath") 					ptr = new AnimalPath();
		is("Sai") 							ptr = new Sai();
		is("Tenten") 						ptr = new Tenten();
		is("Suigetsu") 						ptr = new Suigetsu();
		is("Konan") 						ptr = new Konan();
		is_or("Jiraiya", "SageJiraiya") 	ptr = new Jiraiya();
		is("Shikamaru") 					ptr = new Shikamaru();
		is_or("Sasuke", "ImmortalSasuke") 	ptr = new Sasuke();
		is("Deidara") 						ptr = new Deidara();
		is("Minato") 						ptr = new Minato();
		is("DogWall") 						ptr = new DogWall();
		is("Kakashi") 						ptr = new Kakashi();
		is("Tobi") 							ptr = new Tobi();
		is("Hinata") 						ptr = new Hinata();
		is("Neji") 							ptr = new Neji();
		is("Choji") 						ptr = new Choji();
		is("Itachi") 						ptr = new Itachi();
		is("Orochimaru") 					ptr = new Orochimaru();
		is("Kurama") 						ptr = new Kurama();
		is("Naruto") 						is_tag(kRoleClone) ptr = new NarutoClone();			else ptr = new Naruto();
		is("SageNaruto") 					is_tag(kRoleClone) ptr = new SageNarutoClone();		else ptr = new Naruto();
		is("RikudoNaruto") 					is_tag(kRoleClone) ptr = new RikudoNarutoClone();	else ptr = new Naruto();
		is("Gaara") 						ptr = new Gaara();
		is("Tobirama") 						ptr = new Tobirama();
		is("Akamaru") 						ptr = new Akamaru();
		is("Karasu") 						ptr = new Karasu();
		is("Saso") 							ptr = new Saso();
		is("Parents") 						ptr = new Parents();
		is("Sanshouuo") 					ptr = new Sanshouuo();
		is("Kankuro") 						ptr = new Kankuro();
		is("Chiyo") 						ptr = new Chiyo();
		is("Kiba") 							ptr = new Kiba();
		is("Karin") 						ptr = new Karin();
		is_or("Lee", "RockLee") 			ptr = new Lee();
		is("Tsunade") 						ptr = new Tsunade();
		is("Jugo") 							ptr = new Jugo();
		is("Kisame") 						ptr = new Kisame();
		is("Ino") 							ptr = new Ino();
		is("Hidan") 						ptr = new Hidan();
		is("Shino") 						ptr = new Shino();
		is("Hiruzen") 						ptr = new Hiruzen();
		is("Kakuzu") 						ptr = new Kakuzu();
		is_or("Roshi", "Han")				ptr = new Guardian();
		else								ptr = new DefaultAI();

		if (!ptr)
		{
			CCLOG("Not found character [ %s ]", name);
			return nullptr;
		}

		if (ptr->init())
		{
			ptr->setID(character, role, group);
			ptr->autorelease();
		}
		else
		{
			CCLOG("Set character %s not found", name);
			delete ptr;
			ptr = nullptr;
		}
		return ptr;
	}
};

#undef __begin__
#undef is
#undef is_or
#undef is_tag
