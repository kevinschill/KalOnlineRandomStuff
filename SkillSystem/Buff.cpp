#include "Header.h"
#include "Buff.h"

int Health =		50;
int Intelligence =  50;
int Strength =		50;
int Agility =		50;
int Critical =		23;
int Speed =			120;
int Defense =		190;
int Refine =		190;

#define ID_Speed			12
#define ID_Refine			36
#define ID_Defense			37
#define ID_Strength			46
#define ID_Health			47
#define ID_Agility			48
#define ID_Intelligence		49
#define ID_Critical			50

void CBuff::BuffServer()
{
	GameServer::IOCriticalSection::Enter((std::intptr_t*)0x4e2078);
	GameServer::IOCriticalSection::Enter((std::intptr_t*)0x4e2098);
	GameServer::Link::MoveTo((std::intptr_t*)0x4e200c, static_cast<int>( 0x4e2004 ));
	GameServer::IOCriticalSection::Leave((std::intptr_t*)0x4e2098);

	std::intptr_t* Playerp = 0;
	for (std::uint32_t i = *(std::uint32_t*)0x4e2004; i != 0x4e2004; i = *(std::uint32_t* )i)
	{
		Playerp = (std::intptr_t* )(i - 428);
		if (Playerp)
		{
			GameServer::Char::CancelBuff(Playerp, ID_Refine);
			GameServer::Char::CancelBuff(Playerp, ID_Defense);
			GameServer::Char::CancelBuff(Playerp, ID_Strength);
			GameServer::Char::CancelBuff(Playerp, ID_Health);
			GameServer::Char::CancelBuff(Playerp, ID_Agility);
			GameServer::Char::CancelBuff(Playerp, ID_Intelligence);
			GameServer::Char::CancelBuff(Playerp, ID_Critical);
			GameServer::Char::CancelBuff(Playerp, ID_Speed);

			GameServer::Player::AddBuff(Playerp, GameServer::Char::CreateBuff(ID_Refine, 2000, Refine, 0));
			GameServer::Player::AddBuff(Playerp, GameServer::Char::CreateBuff(ID_Defense, 1000, Defense, 0));
			GameServer::Player::AddBuff(Playerp, GameServer::Char::CreateBuff(ID_Strength, 1000, Strength, 0));
			GameServer::Player::AddBuff(Playerp, GameServer::Char::CreateBuff(ID_Health, 1000, Health, 0));
			GameServer::Player::AddBuff(Playerp, GameServer::Char::CreateBuff(ID_Agility, 1000, Agility, 0));
			GameServer::Player::AddBuff(Playerp, GameServer::Char::CreateBuff(ID_Intelligence, 1000, Intelligence, 0));
			GameServer::Player::AddBuff(Playerp, GameServer::Char::CreateBuff(ID_Critical, 1000, Critical, 0));
			GameServer::Player::AddBuff(Playerp, GameServer::Char::CreateBuff(ID_Speed, 3600, Speed, 0));
		}
	}
	GameServer::IOCriticalSection::Leave((std::intptr_t*)0x4e2078);
}