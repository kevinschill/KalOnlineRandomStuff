#include "Header.h"

#include "SkillSystem.h"
#include "CPlayer.h"


/*
TO-DO:
fix Sleep to correct timings.
add Damage Calculation
fix mana calculation
*/

void CMage::FlameInjetionThrd(CPlayer* p,CPlayer* t)
{
	std::unique_ptr<CSkill> tSkill(new CSkill(p->pObject));
	
	int Grade = tSkill->getGrade(SKILL_FLAMEINJECTION);
	
	if(!Grade) return;

	int nMana = ((((p->getLevel() * 2) + 50) * Grade) / 10) + ((p->getLevel() * 2) + 50);
	if(p->getStats(CurrentMP,false) < nMana) return;
	
	int nDmg = 500;
	
	bool first = true;

	for(int i = 0; i < 5; i++)
	{
		for (auto vList = p->GetAroundList(6, p->pObject); vList.size(); vList.pop_front())
		{	
			auto pMonster = vList.front();
			if(!pMonster->pObject || !p->pObject) continue;

			if(!tSkill->isInArea(pMonster->pObject,t->getCoordinate(X),t->getCoordinate(Y),90)) continue;

			if(!p->canAttack(pMonster->pObject)) continue;

			GameServer::Player::WriteInSight(p->pObject, 0x3f, "bddbbwwb",SKILL_FLAMEINJECTION, p->getID(), pMonster->getID(), 1, 1, p->Damage(pMonster->pObject,nDmg), 0, true);	
						
			if(p->TargetDeath)
				GameServer::ObjectReleases((void *)pMonster->pObject, LONG(pMonster->pObject) + 0x160);
		}
		if(first)
		{
			GameServer::Player::WriteInSight(p->pObject, 0x3f, "bddbbwwb", SKILL_FLAMEINJECTION, p->getID(), p->getID(), 1, 0, 0, 0, false);
			first=false;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	}
	p->ConsumeMana(nMana);
	GameServer::Player::WriteInSight(p->pObject, 0x3d, "db", p->getID(),0);
}