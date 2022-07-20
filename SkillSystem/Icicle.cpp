#include "Header.h"
#include "SkillSystem.h"

/*
TO-DO:
fix Sleep to correct timings.
add Damage Calculation
fix mana calculation
*/
void CMage::IceCircleThrd(CPlayer* p)
{

	std::unique_ptr<CSkill> tSkill(new CSkill(p->pObject));

	int Grade = tSkill->getGrade(SKILL_ICECIRCLE);

	if(!Grade) return;
	
	int nMana = ((((p->getLevel() * 2) + 50) * Grade) / 10) + ((p->getLevel() * 2) + 50);
	
	if(p->getStats(CurrentMP,false) < nMana) return;

	bool finish = false;

	int nDmg = 500 * Grade;
	for(int i = 0; i < 5; i++)
	{

		for (auto vList = p->GetAroundList(3, p->pObject); vList.size(); vList.pop_front())
		{

			auto pMonster = vList.front();

			if(!pMonster->pObject ||  !p->pObject) continue;
		
			if(!p->canAttack(pMonster->pObject)) continue;

			GameServer::Player::WriteInSight(p->pObject, 0x3f, "bddbbwwb", SKILL_ICECIRCLE,  p->getID(), pMonster->getID(), 1, 1, p->Damage(pMonster->pObject,nDmg), 0, true);
			finish = true;
			
			if(p->TargetDeath)
				GameServer::ObjectReleases((void *)pMonster->pObject, LONG(pMonster->pObject) + 0x160);
		}
		if(!finish)
		{
			finish = true;
			GameServer::Player::WriteInSight(p->pObject, 0x3f, "bddbbwwb", SKILL_ICECIRCLE,  p->getID(), p->getID(), 1, 0, 0, 0, false);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1300));
	}
	p->ConsumeMana(nMana);

	GameServer::Player::WriteInSight(p->pObject, 0x3f, "bddbbwwb", 4,  p->getID(), p->getID(), 1, 0, 0, 0, false);

}