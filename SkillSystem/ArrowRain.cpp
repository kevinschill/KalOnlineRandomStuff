#include "Header.h"
#include "SkillSystem.h"

/*
TO-DO:
fix Sleep to correct timings.
add Damage Calculation
fix mana calculation
*/

void CArcher::ArrowRainThrd(CPlayer* p,int* Coordinates)
{
	std::unique_ptr<CSkill> tSkill(new CSkill(p->pObject));
	
	int Grade = tSkill->getGrade(SKILL_ARROWRAIN);
	
	if(!Grade) return;

	int nMana = ((((p->getLevel() * 2) + 50) * Grade) / 10) + ((p->getLevel() * 2) + 50);
	if(p->getStats(CurrentMP,false) < nMana) return;
	
	int nDmg = 500;
	

	bool first = true;

	for(int i = 0; i < 8; i++)
	{
		for (auto vList = p->GetAroundList(6, p->pObject); vList.size(); vList.pop_front())
		{	
			auto pMonster = vList.front();
			if(!pMonster->pObject || !p->pObject) continue;

			if(!tSkill->isInArea(pMonster->pObject,Coordinates[0],Coordinates[1],90)) continue;

			if(!p->canAttack(pMonster->pObject)) continue;

			if(first)
			{
				GameServer::MonsterMagic::Create(9000,p->getMap(),(int)Coordinates,1,(int)p->pObject,500,6000);                           
				first = false;
			}
			GameServer::Player::WriteInSight(p->pObject, 0x3f, "bddbbwwb",SKILL_ARROWRAIN, p->getID(), pMonster->getID(), 1, 1, p->Damage(pMonster->pObject,nDmg), 0, true);	
						
			if(p->TargetDeath)
				GameServer::ObjectReleases((void *)pMonster->pObject, LONG(pMonster->pObject) + 0x160);
		}
		if(first)
		{
			GameServer::Player::WriteInSight(p->pObject, 0x3f, "bddbbwwb", SKILL_ARROWRAIN, p->getID(), p->getID(), 1, 0, 0, 0, false);
			first=false;
		}
		Sleep(1500);
	}
	p->ConsumeMana(nMana);
	GameServer::Player::WriteInSight(p->pObject, 0x3d, "db", p->getID(),0);
}