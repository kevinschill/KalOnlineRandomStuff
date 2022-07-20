#include "Header.h"

#include "SkillSystem.h"
#include "CPlayer.h"

/*
TO-DO:
add Damage Calculation
fix mana calculation
*/
void CKnight::SpinSplash(CPlayer* p)
{
	std::unique_ptr<CSkill> tSkill(new CSkill(p->pObject));

	int Grade = tSkill->getGrade(SKILL_SPINSPLASH);

	if(!Grade) return;

	int nMana = ((((p->getLevel() * 2) + 50) * Grade) / 10) + ((p->getLevel() * 2) + 50);
	if(p->getStats(CurrentMP,false) < nMana) return;


	int nDmg = 500 * Grade;

	for (auto vList = p->GetAroundList(4, p->pObject); vList.size(); vList.pop_front())
	{
		auto pMonster = vList.front();
		if(!pMonster->pObject ||  !p->pObject) continue;
		
		if(!p->canAttack(pMonster->pObject)) continue;

		GameServer::Player::WriteInSight(p->pObject, 0x3f, "bddbbwwb", SKILL_SPINSPLASH,  p->getID(), pMonster->getID(), 1, 1, p->Damage(pMonster->pObject,nDmg), 0, true);		                               
	}
	p->ConsumeMana(nMana);
}