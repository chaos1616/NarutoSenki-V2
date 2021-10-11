#pragma once
#include "Defines.h"
#include "MyUtils/CMD5Checksum.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../../external/sqlite3/src/sqlite3.h"
#else
#include "sqlite3.h"
#endif

class CMD5Checksum;

class KTools : public CCObject
{
public:
	static bool readXMLToArray(const char *filePath, CCArray *&array);
	static void prepareFileOGG(const char *listName, bool unload = false);

	static void initTableInDB();
	static void initColumeInDB();

	static sqlite3 *prepareTableInDB();

	static bool saveToSQLite(const char *table = "GameRecord", const char *column = nullptr, const char *value = nullptr, bool isBuy = false);
	static std::string readFromSQLite(const char *table = "GameRecord", const char *column = nullptr, const char *value = nullptr);

	static void encode(std::string &str, int randomKey);
	static void decode(std::string &str);

	static std::string getKeycode(std::string path);

	static std::string readSQLite(const char *table, const char *column, const char *value, const char *targetColumn);
	static void saveSQLite(const char *table, const char *relatedColumn, const char *value, const char *targetColumn, char *targetValue, bool isPlus);

	static int readWinNumFromSQL(const char *heroName);
	static int readCoinFromSQL();
	static const char *readRecordTimeFromSQL(const char *heroName);

	static std::string encodeData(std::string data);
};

class CCTips : public CCSprite
{
public:
	bool init(const char *tips);

	static CCTips *create(const char *tips);

protected:
	void onDestroy();
};
