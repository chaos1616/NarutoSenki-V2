#include "KTools.h"
#include "Defines.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../../../cocos2dx/platform/android/jni/JniHelper.h"
#endif

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#endif

void KTools::prepareFileMD5()
{
}

void KTools::prepareFileSHA()
{
}

int KTools::checkMD5(std::string findPath /* ="" */)
{
	return 1;
}

std::string KTools::getKeycode(std::string path)
{
	std::string strKey = CMD5Checksum::GetMD5(path);
	std::string strKeyCode = CCString::createWithFormat("%s,%s", strKey.substr(16, 5).c_str(), strKey.substr(6, 5).c_str())->getCString();
	return strKeyCode;
}

bool KTools::checkData()
{
	return true;
}

void KTools::updateData()
{
}

bool KTools::readXMLToArray(const char *filePath, CCArray *&array)
{
	unsigned long nSize;
	auto data = (const char *)CCFileUtils::sharedFileUtils()->getFileData(filePath, "r", &nSize);
	if (data == nullptr)
	{
		CCMessageBox(CCString::createWithFormat("Data %s is null", filePath)->getCString(), "Read XML Error");
		return false;
	}
	tinyxml2::XMLDocument doc;
	auto err = doc.Parse(data, nSize);
	if (err)
	{
		CCMessageBox(CCString::createWithFormat("XML Error: %s", tinyxml2::XMLDocument::ErrorIDToName(err))->getCString(), "Parse XML Error");
		return false;
	}

	auto rootEle = doc.RootElement();
	auto actionEle = rootEle->FirstChildElement();

	while (actionEle)
	{
		const char *actionName = actionEle->FirstAttribute()->Value();
		//CCLog("[%s]",actionName);

		auto actionNodeEle = actionEle->FirstChildElement();
		auto actionArray = CCArray::create();
		auto actionData = CCArray::create();
		auto actionFrame = CCArray::create();
		while (actionNodeEle)
		{
			// CCLog("+[%s]",actionNodeEle->Name());
			if (strcmp(actionNodeEle->Name(), "frame"))
			{
				auto dataEle = actionNodeEle->FirstChildElement();

				while (dataEle)
				{
					const char *nodeKey = dataEle->FirstAttribute()->Value();
					CCString *nodeValue = CCString::create(dataEle->GetText());

					// CCLog("%s:%s",nodeKey,nodeValue->getCString());
					auto dataDic = CCDictionary::create();
					dataDic->setObject(nodeValue, nodeKey);

					actionData->addObject(dataDic);
					dataEle = dataEle->NextSiblingElement();
				}
			}
			else
			{
				auto frameEle = actionNodeEle->FirstChildElement();

				while (frameEle)
				{
					const char *nodeKey;
					if (strcmp(frameEle->Name(), "frameName"))
					{
						nodeKey = frameEle->FirstAttribute()->Value();
					}
					else
					{
						nodeKey = frameEle->Name();
					}

					CCString *nodeValue = CCString::create(frameEle->GetText());

					// CCLog("%s:%s",nodeKey,nodeValue->getCString());
					auto frameDic = CCDictionary::create();
					frameDic->setObject(nodeValue, nodeKey);
					actionFrame->addObject(frameDic);

					frameEle = frameEle->NextSiblingElement();
				}
			}
			actionNodeEle = actionNodeEle->NextSiblingElement();
		}
		actionArray->addObject(actionData);
		actionArray->addObject(actionFrame);

		array->addObject(actionArray);
		actionEle = actionEle->NextSiblingElement();
	}

	delete data;

	return true;
}

int isExisted(void *para, int n_column, char **column_value, char **column_name)
{
	bool *isExisted_ = (bool *)para;
	*isExisted_ = (**column_value) != '0';
	return 0;
}

void KTools::encode(std::string &str, int radomKey)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		int ch = str[i];
		ch += radomKey;
		str[i] = ch;
	}
	str += radomKey;
}

void KTools::decode(std::string &str)
{
	size_t num = str.length() - 1;
	int key = str[num];
	str = str.substr(0, num);

	for (size_t i = 0; i < str.length(); i++)
	{
		int ch = str[i];
		ch -= key;
		str[i] = ch;
	}
}

void KTools::initTableInDB()
{
	sqlite3 *pDB = nullptr;
	char *errorMsg = nullptr;
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "sql.db";
	int result = sqlite3_open(path.c_str(), &pDB);
	if (result != SQLITE_OK)
	{
		CCLOG("open sql file Failed!");
		return;
	}

	CCString *sql = CCString::create("drop table IF EXISTS Achievement");

	sqlite3_exec(pDB, sql->getCString(), nullptr, nullptr, &errorMsg);

	sql = CCString::create("create table if not exists CharRecord (name char(20)  primary key ,column1 char(10),column2 char(10),column3 char(10))");
	sqlite3_exec(pDB, sql->getCString(), nullptr, nullptr, &errorMsg);

	sql = CCString::create("select * from  GameRecord");

	sqlite3_exec(pDB, sql->getCString(), nullptr, nullptr, &errorMsg);

	if (errorMsg != nullptr)
	{
		errorMsg = nullptr;
		sql = CCString::create("create table if not exists GameRecord (id char(10) primary key,coin char(20),version char(20))");
		sqlite3_exec(pDB, sql->getCString(), nullptr, nullptr, &errorMsg);

		std::string str = "n>";
		CCString *coin = CCString::create(str);

		sql = CCString::createWithFormat("insert into GameRecord values(1,'%s','1')", coin->getCString());
		int result = sqlite3_exec(pDB, sql->getCString(), nullptr, nullptr, &errorMsg);

		if (errorMsg != nullptr)
		{
			CCLOG("exec sql %s failed with mgs: %s", sql->getCString(), errorMsg);
			sqlite3_close(pDB);
			return;
		}

		KTools::updateData();
	}

	bool isExisted_;

	sql = CCString::create("select count(*) from  CharRecord");
	sqlite3_exec(pDB, sql->getCString(), isExisted, &isExisted_, &errorMsg);

	if (!isExisted_)
	{
		for (int i = 0; i < kHeroNum; i++)
		{
			std::string name = kHeroList[i];

			int key = rand() % 50 + 40;
			encode(name, key);
			CCString *nameDB = CCString::create(name);

			std::string column1 = "0";
			key = rand() % 60 + 40;
			encode(column1, key);
			CCString *column1DB = CCString::create(column1);

			std::string column2 = "0";
			key = rand() % 60 + 40;
			encode(column2, key);
			CCString *column2DB = CCString::create(column2);

			std::string column3 = "";
			key = rand() % 60 + 40;
			encode(column3, key);
			CCString *column3DB = CCString::create(column3);

			CCString *sql = CCString::createWithFormat("insert into  CharRecord values('%s','%s','%s','%s')", nameDB->getCString(), column1DB->getCString(), column2DB->getCString(), column3DB->getCString());
			sqlite3_exec(pDB, sql->getCString(), nullptr, nullptr, &errorMsg);

			if (errorMsg != nullptr)
			{
				CCLOG("exec sql %s failed with mgs: %s", sql->getCString(), errorMsg);
				sqlite3_close(pDB);
				return;
			}
		}

		KTools::updateData();
	}

	sqlite3_close(pDB);
}

void KTools::initColumeInDB()
{
	sqlite3 *pDB = nullptr;
	char *errorMsg = nullptr;
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "sql.db";
	int result = sqlite3_open(path.c_str(), &pDB);
	if (result != SQLITE_OK)
	{
		CCLOG("open sql file Failed!");
		return;
	}

	char **result2;
	int row = 0;
	int column = 0;

	CCString *sql = CCString::create("select coin from GameRecord");
	sqlite3_get_table(pDB, sql->getCString(), &result2, &row, &column, nullptr);
	std::string str2 = result2[1];
	decode(str2);

	std::string str3 = "uuuuu<";
	decode(str3);
	if (to_int(str2.c_str()) > to_int(str3.c_str()))
	{
		CCString *coin = CCString::create("uuuuu<");
		sql = CCString::createWithFormat("update GameRecord set coin='%s'", coin->getCString());
		sqlite3_exec(pDB, sql->getCString(), nullptr, nullptr, &errorMsg);
		KTools::updateData();
	}
}

void KTools::prepareFileOGG(const char *listName, bool unload /* =false */)
{
	if (!CCUserDefault::sharedUserDefault()->getBoolForKey("isPreload"))
	{
		return;
	}

	//MD5

	std::string md5Path = "Audio/list.xml";

	bool isExisted = CCFileUtils::sharedFileUtils()->isFileExist(md5Path);

	if (!isExisted)
	{
		return;
	}

	unsigned long nSize;
	const char *pXmlBuffer = (const char *)CCFileUtils::sharedFileUtils()->getFileData(md5Path.c_str(), "r", &nSize);
	tinyxml2::XMLDocument doc;
	doc.Parse(pXmlBuffer);

	auto rootEle = doc.RootElement();
	auto fileEle = rootEle->FirstChildElement();

	while (fileEle)
	{
		auto pathSrc = fileEle->FirstAttribute()->Value();
		auto soundPath = fileEle->GetText();
		if (is_same(pathSrc, listName))
		{
			if (!unload)
			{
				SimpleAudioEngine::sharedEngine()->preloadEffect(soundPath);
			}
			else if (unload)
			{
				SimpleAudioEngine::sharedEngine()->unloadEffect(soundPath);
			}
		}

		fileEle = fileEle->NextSiblingElement();
	}
}

sqlite3 *KTools::prepareTableInDB()
{
	sqlite3 *pDB = nullptr;
	char *errorMsg = nullptr;

	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "sql.db";
	int result = sqlite3_open(path.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		CCLOG("open sql file Failed!");
		return nullptr;
	}

	return pDB;
}

bool KTools::saveToSQLite(const char *table /* ="GameRecord"*/, const char *column /* =nullptr */, const char *value /* =nullptr */, bool isBuy /*= false */)
{
	sqlite3 *pDB = prepareTableInDB();
	char *errorMsg = nullptr;
	if (pDB != nullptr)
	{
		int key = rand() % 60 + 40;
		std::string str = value;

		encode(str, key);
		CCString *coin = CCString::create(str);
		CCString *sql = CCString::createWithFormat("update %s set %s='%s'", table, column, coin->getCString());
		sqlite3_exec(pDB, sql->getCString(), nullptr, nullptr, &errorMsg);

		if (errorMsg != nullptr)
		{
			sqlite3_close(pDB);
			return false;
		}

		KTools::updateData();

		return true;
	}

	return false;
	sqlite3_close(pDB);
}

CCString *KTools::readFromSQLite(const char *table /* ="GameRecord" */, const char *column /* =nullptr */, const char *value /* =nullptr */)
{
	sqlite3 *pDB = prepareTableInDB();

	if (pDB != nullptr)
	{
		char **result;
		CCString *sql = CCString::createWithFormat("select %s from  GameRecord", "coin");
		int row = 0;
		int column = 0;

		sqlite3_get_table(pDB, sql->getCString(), &result, &row, &column, nullptr);

		std::string str = result[1];
		decode(str);
		CCString *coin = CCString::createWithFormat("%s", str.c_str());
		sqlite3_free_table(result);
		sqlite3_close(pDB);
		return coin;
	}
	sqlite3_close(pDB);
	return 0;
}

CCString *KTools::readSQLite(const char *table, const char *column, const char *value, const char *targetColumn)
{
	sqlite3 *pDB = prepareTableInDB();

	if (pDB != nullptr)
	{
		char **result;

		CCString *sql = CCString::createWithFormat(("select %s,%s from  %s "), column, targetColumn, table);
		int row = 0;
		int column = 0;

		sqlite3_get_table(pDB, sql->getCString(), &result, &row, &column, nullptr);

		std::string target;
		for (int i = 0; i <= row * 2; i++)
		{
			std::string str = result[i];

			decode(str);
			if (is_same(str.c_str(), value))
			{
				target = result[i + 1];
				decode(target);
				break;
			}
		}

		CCString *targetValue = CCString::create("");

		if (is_same(targetColumn, "column3") ||
			is_same(targetColumn, "column4"))
		{
			targetValue = CCString::createWithFormat("%s", target.c_str());
		}
		else
		{
			targetValue = to_ccstring(to_int(target.c_str()));
		}
		sqlite3_free_table(result);
		sqlite3_close(pDB);
		return targetValue;
	}
	sqlite3_close(pDB);
	return 0;
}

void KTools::saveSQLite(const char *table, const char *relatedColumn, const char *value, const char *targetColumn, char *targetValue, bool isPlus)
{
	char *errorMsg = nullptr;
	sqlite3 *pDB = prepareTableInDB();

	if (pDB != nullptr)
	{
		char **result;

		CCString *sql = CCString::createWithFormat(("select %s,%s from  %s "), relatedColumn, targetColumn, table);
		int row = 0;
		int column = 0;

		sqlite3_get_table(pDB, sql->getCString(), &result, &row, &column, nullptr);

		std::string target;
		std::string columnValue;
		for (int i = 0; i <= row * 2; i++)
		{
			std::string str = result[i];
			decode(str);
			if (is_same(str.c_str(), value))
			{
				columnValue = result[i];
				target = result[i + 1];
				decode(target);
				break;
			}
		}

		std::string saveValue;
		if (isPlus)
		{
			saveValue = std::string(targetValue) + target;
			sql = CCString::createWithFormat(("update %s set %s='%s' where %s='%s'"), table, targetColumn, saveValue.c_str(), relatedColumn, columnValue.c_str());
		}
		else
		{
			saveValue = std::string(targetValue);
		}
		int key = rand() % 50 + 40;
		encode(saveValue, key);
		sql = CCString::createWithFormat(("update %s set %s='%s' where %s='%s'"), table, targetColumn, saveValue.c_str(), relatedColumn, columnValue.c_str());
		sqlite3_exec(pDB, sql->getCString(), nullptr, nullptr, nullptr);

		if (isPlus)
		{
			char **result2;
			sql = CCString::create("select coin from GameRecord");
			sqlite3_get_table(pDB, sql->getCString(), &result2, &row, &column, nullptr);
			std::string str2 = result2[1];
			decode(str2);

			std::string str3 = "uuuuu<";
			decode(str3);

			if (to_int(str2.c_str()) > to_int(str3.c_str()))
			{
				CCString *coin = CCString::create("uuuuu<");
				sql = CCString::createWithFormat("update GameRecord set coin='%s'", coin->getCString());
				sqlite3_exec(pDB, sql->getCString(), nullptr, nullptr, &errorMsg);
			}
		}

		sqlite3_free_table(result);

		KTools::updateData();

		sqlite3_close(pDB);
		return;
	}
	sqlite3_close(pDB);
}

std::string KTools::encodeData(std::string data)
{
	//SHA1 *sha1;
	//unsigned char *digest;
	std::string dataMD5 = CMD5Checksum::GetMD5OfString(data);

	//sha1=new SHA1;
	////sha1->addBytes( "goldlion" ,strlen( "goldlion" ));//
	//std::string result=(char*) digest;
	//delete sha1;
	//free(digest);
	return dataMD5;
}

bool CCTips::init(const char *tips)
{
	RETURN_FALSE_IF(!CCSprite::init());

	setAnchorPoint(ccp(0.5, 0.5));
	auto strings = CCDictionary::createWithContentsOfFile("Element/strings.xml");
	const char *reply = ((CCString *)strings->objectForKey(tips))->m_sString.c_str();

	CCLabelTTF *tipLabel = CCLabelTTF::create(reply, FONT_TYPE, 12);
	addChild(tipLabel, 5000);
	setPosition(ccp(winSize.width / 2, 50));
	auto call = CCCallFunc::create(this, callfunc_selector(CCTips::onDestroy));

	auto mv = CCMoveBy::create(0.2f, ccp(0, 12));
	auto fadeOut = CCFadeOut::create(0.2f);
	auto delay = CCDelayTime::create(2.0f);
	auto sp = CCSpawn::create(fadeOut, mv, nullptr);

	auto seqArray = CCArray::create();
	seqArray->addObject(sp);
	seqArray->addObject(delay);
	seqArray->addObject(call);

	auto seq = CCSequence::create(seqArray);
	runAction(seq);

	return true;
}

void CCTips::onDestroy()
{
	removeAllChildren();
	removeFromParentAndCleanup(true);
}

CCTips *CCTips::create(const char *tips)
{
	CCTips *ab = new CCTips();
	if (ab && ab->init(tips))
	{
		ab->autorelease();
		return ab;
	}
	else
	{
		delete ab;
		return nullptr;
	}
}
