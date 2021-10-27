#pragma once
#include "cocos2d.h"

using namespace cocos2d;

inline CCSequence *newSequence(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2)
{
	return CCSequence::createWithTwoActions(pAction1, pAction2);
}
inline CCSequence *newSequence(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2, CCFiniteTimeAction *pAction3)
{
	return CCSequence::create(pAction1, pAction2, pAction3, nullptr);
}
inline CCSequence *newSequence(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2, CCFiniteTimeAction *pAction3, CCFiniteTimeAction *pAction4)
{
	return CCSequence::create(pAction1, pAction2, pAction3, pAction4, nullptr);
}
inline CCSequence *newSequence(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2, CCFiniteTimeAction *pAction3, CCFiniteTimeAction *pAction4, CCFiniteTimeAction *pAction5)
{
	return CCSequence::create(pAction1, pAction2, pAction3, pAction4, pAction5, nullptr);
}
inline CCSequence *newSequence(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2, CCFiniteTimeAction *pAction3, CCFiniteTimeAction *pAction4, CCFiniteTimeAction *pAction5, CCFiniteTimeAction *pAction6)
{
	return CCSequence::create(pAction1, pAction2, pAction3, pAction4, pAction5, pAction6, nullptr);
}
