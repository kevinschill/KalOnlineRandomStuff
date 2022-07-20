#include "Header.h"
#include "CPlayer.h"


std::map<int*,unsigned long long> mMute;
void __fastcall Hooks::Player::hkProcessMsg(int* Player,void* _edx, char* Message)
{
	UNREFERENCED_PARAMETER(_edx);

	bool forward = true;

	for (std::map<int*,unsigned long long>::iterator b = mMute.begin(); b != mMute.end();) 
	{ 
		if( b->first == Player) 
		{
			unsigned long long t = GetTickCount64() - b->second;
			if(t >= 60000)//1800000)
			{
				b = mMute.erase( b );
			}
			else
			{
				std::stringstream s;
				unsigned long long TimeLeft = 60000 - t;
				s << "Mute Time Left: [ " << TimeLeft / 1000 << " ] Seconds.!";
				if(Player)
					GameServer::Player::Write(Player,60,"ss","Mute System",s.str().c_str());

				forward = false;
				++b;
			}
		}
		else
			++b;
	}	

	if(forward)
		GameServer::Player::ProcessMsg(Player,Message);
}