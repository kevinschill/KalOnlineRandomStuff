#include "SkillSystem.h"

std::map<int,DWORD64> mshinyMonster;

void CMage::LightningArrowThrd(CPlayer* p, CPlayer* t)
{
	std::unique_ptr<CSkill> tSkill(new CSkill(p->pObject));

	int Grade = tSkill->getGrade(67);

	if(!Grade) return;

	int nMana = ((((p->getLevel() * 2) + 50) * Grade) / 10) + ((p->getLevel() * 2) + 50);
	if(p->getStats(CurrentMP,false) < nMana) return;

	if(!t->pObject ||  !p->pObject) return;
		
	if(!p->canAttack(t->pObject)) return;

	
	GameServer::Player::WriteInSight(p->pObject, 0x3f, "bddbbwwb", 67,  p->getID(), t->getID(), 1, 1, 0, 0, true);

	mshinyMonster[t->getID()] = GetTickCount64();

	p->ConsumeMana(nMana);
}