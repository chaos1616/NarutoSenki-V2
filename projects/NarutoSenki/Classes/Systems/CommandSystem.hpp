#pragma
#include "CharacterBase.h"
#include "Enums/Enums.hpp"

namespace Command
{
	mk_const(addHP);
	mk_const(setInvincible);
	mk_const(setGainCKR);
	mk_const(reInvincible);
	mk_const(setInvisible);
	mk_const(reInvisible);
	mk_const(setTransport2);
	mk_const(setTransport);
	mk_const(reTransport);
	mk_const(setDead);
	mk_const(findTarget);
	mk_const(setRevive);
	mk_const(setTrade);
	mk_const(addExtern);
	mk_const(pauseJump);
	mk_const(setCounter);
} // namespace Command

using CommandHandler = std::function<void(CharacterBase *)>;

class CommandSystem
{
private:
	static std::map<const char *, CommandHandler> cmds;

public:
	static inline void on(const char *cmd, CommandHandler handler)
	{
		cmds.insert(std::make_pair(cmd, handler));
	}

	static inline bool invoke(const char *cmd, CharacterBase *c)
	{
		auto it_find = cmds.find(cmd);
		if (it_find != cmds.end())
		{
			auto handler = it_find->second;
			handler(c);
		}
		else
		{
			CCLOGERROR("Not found command handler %s", cmd);
		}
		return true;
	}

	static inline void remove(const char *cmd)
	{
		cmds.erase(cmd);
	}

	static inline void reset()
	{
		cmds.clear();
		init();
	}

	static void init()
	{
		on(Command::addHP, [](CharacterBase *c) {});
		on(Command::setInvincible, [](CharacterBase *c) {});
		on(Command::setGainCKR, [](CharacterBase *c) {});
		on(Command::reInvincible, [](CharacterBase *c) {});
		on(Command::setInvisible, [](CharacterBase *c) {});
		on(Command::reInvisible, [](CharacterBase *c) {});
		on(Command::setTransport2, [](CharacterBase *c) {});
		on(Command::setTransport, [](CharacterBase *c) {});
		on(Command::reTransport, [](CharacterBase *c) {});
		on(Command::setDead, [](CharacterBase *c) {});
		on(Command::findTarget, [](CharacterBase *c) {});
		on(Command::setRevive, [](CharacterBase *c) {});
		on(Command::setTrade, [](CharacterBase *c) {});
		on(Command::addExtern, [](CharacterBase *c) {});
		on(Command::pauseJump, [](CharacterBase *c) {});
		on(Command::setCounter, [](CharacterBase *c) {});
	}
};

// declear static member
std::map<const char *, CommandHandler> CommandSystem::cmds;
