#include "Header.h"
#include "SkillSystem.h"

void CMage::MagicIntensification(CPlayer* p)
{
	printf("Level: %d new %d\n",p->pObject[15],p->pObject[15] + 10);
	p->pObject[15] += 10;
}