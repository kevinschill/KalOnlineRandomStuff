#ifndef PLAYER_H
#define PLAYER_H

#define Strength 1
#define Health 2
#define Intelligence 3
#define Agility 4
#define Wisdom 5
#define OTP 6
#define Evasion 7
#define MinPhyDmg 8
#define MaxPhyDmg 9
#define MinMagicDmg 10
#define MaxMagicDmg 11
#define MinDef 12
#define MaxDef 13
#define Absorb 14
#define CurrentHP 15
#define CurrentMP 16

#define X 1
#define Y 2
#define Z 3
#define ALL 4


#define Property_Statpoints 24
#define Property_HealthPoints 7
#define Property_ManaPoints 8

class CPlayer
{
	public:
		int* pObject;
		CPlayer::CPlayer(){}
		CPlayer::CPlayer(int* Player)
		{
			this->pObject = Player;
		}
		CPlayer::~CPlayer()
		{
			
		}
		
		int getAdmin();
		int getLevel();
		int getID();
		int getPID();
		int getUID();
		BYTE getClass();
		WORD getStatPoints();
		WORD getSkillPoints();
		char* getName();
		int getType();

		unsigned short getStats(BYTE bType,bool Bonus);
		void SetStats(BYTE bType,unsigned short Amount,bool Bonus);

		int getMap();
		int getCoordinate(BYTE bType);
		int* getCoordinates();

		void UpdateProperty(BYTE bID,BYTE bType,int Amount);

		void IncreaseOTP(int Amount);
		void IncreaseEvasion(int Amount);

		bool canAttack(int* Target);
		std::list<CPlayer*> GetAroundList(int Range,int* Target);
		void ConsumeMana(int Amount);
		int Damage(int* Target,int Damage);

		bool TargetDeath;
};

#endif