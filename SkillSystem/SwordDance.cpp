#include "Header.h"
#include "SkillSystem.h"

/*
TO-DO:
fix Sleep to correct timings.
add Damage Calculation
fix mana calculation
*/
void CKnight::SwordDanceThrd(CPlayer* p, CPlayer* t)
{
	std::unique_ptr<CSkill> tSkill(new CSkill(p->pObject));

	int Grade = tSkill->getGrade(43);

	if(!Grade) return;
	
	int nMana = ((((p->getLevel() * 2) + 50) * Grade) / 10) + ((p->getLevel() * 2) + 50);
	
	if(p->getStats(CurrentMP,false) < nMana) return;

	int nDmg = 500;

	if(!t->pObject) return;

	for(int i = 0; i < 5; i++)
	{			
		GameServer::Player::WriteInSight(p->pObject, 0x3f, "bddbbwwb", 43, p->getID(), t->getID(), 1, 1, p->Damage(t->pObject,nDmg), 0, true);                
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	GameServer::Player::WriteInSight(p->pObject, 0x3f, "bddbbwwb", 43, p->getID(), t->getID(), 1, 0, 0, 0, false); 
	
	if(p->TargetDeath)					
		GameServer::ObjectReleases((void *)t->pObject, LONG(t->pObject) + 0x160);
}