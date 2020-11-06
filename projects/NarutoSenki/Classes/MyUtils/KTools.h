#pragma once
#include "support/tinyxml2/tinyxml2.h"
#include "cocos2d.h"
#include "platform/CCFileUtils.h"
#include "MyUtils/CMD5Checksum.h"
#include "sqlite3.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class CMD5Checksum;
class KTools : public CCObject
{
public:
	static void prepareFileMD5();
	static void prepareFileSHA();

	static bool readXMLToArray(const char *filePath, CCArray *&array);
	static void prepareFileOGG(const char *listName, bool unload = false);

	static void initTableInDB();
	static void initColumeInDB();

	static sqlite3 *prepareTableInDB();

	static bool checkData();
	static void updateData();
	static bool saveToSQLite(const char *table = "GameRecord", const char *column = NULL, const char *value = NULL, bool isBuy = false);
	static CCString *readFromSQLite(const char *table = "GameRecord", const char *column = NULL, const char *value = NULL);

	static void encode(std::string &str, int randomKey);
	static void decode(std::string &str);
	static int checkMD5(std::string findPath = "");

	static void dfsFolder(std::string folderPath, int depth = 0, int type = 0);

	static bool checkPackage();

	static std::string getKeycode(std::string path);

	static CCString *readSQLite(const char *table, const char *column, const char *value, const char *targetColumn);
	static void saveSQLite(const char *table, const char *relatedColumn, const char *value, const char *targetColumn, char *targetValue, bool isPlus);

	static std::string encodeData(std::string data);
};

class CCTips : public CCSprite
{
public:
	virtual bool init(const char *tips);
	static CCTips *create(const char *tips);

protected:
	void onDestroy();
};
