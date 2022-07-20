#include "Header.h"
#include "ConfigParser.h"
#include "WorldEvent.h"

std::vector<SWorldEventCounter> vWorldEventCounter;
std::vector <SWorldEvent> vWorldEvent;

void CWorldEvent::LoadConfig()
{
	GameServer::MainServer::WriteBlack(" ------------------ Loading World Event Config ------------------ ");
	std::ifstream spawnitem;
	spawnitem.open("WorldEvent.txt");
	std::string line;
	std::vector<int> vec;

	if(spawnitem.is_open())
	{

		while(std::getline(spawnitem,line,']'))
		{
			std::unique_ptr<ConfigParse> Cfg(new ConfigParse(line));
			SWorldEvent tWorldEvent;
			SWorldEventCounter tWorldEventCounter;

			Cfg->Extract("TargetIndex",")",true);
			tWorldEvent.TargetIndex = Cfg->getInt();
			tWorldEventCounter.Index = tWorldEvent.TargetIndex;

			Cfg->Extract("TargetAmount",")",true);
			tWorldEvent.TargetAmount = Cfg->getInt();

			vWorldEventCounter.push_back(tWorldEventCounter);

			Cfg->Extract("BossIndex",")",true);
			tWorldEvent.BossIndex = Cfg->getInt();

			Cfg->Extract("BossAmount",")",true);
			tWorldEvent.BossAmount = Cfg->getInt();

			Cfg->Extract("X",")",true);
			tWorldEvent.CoordX = Cfg->getInt();

			Cfg->Extract("Y",")",true);
			tWorldEvent.CoordY = Cfg->getInt();

			Cfg->Extract("Map",")",true);
			tWorldEvent.Map = Cfg->getInt();

			std::stringstream sMob;
			sMob << "Target[" << tWorldEvent.TargetIndex << "] Amount[" << tWorldEvent.TargetAmount << "] Boss[" << tWorldEvent.BossIndex << "] Amount[" << tWorldEvent.BossAmount << "] Coordinates[" << tWorldEvent.CoordX << " : " << tWorldEvent.CoordY << " : " << tWorldEvent.Map << "]";
			GameServer::MainServer::WriteRed((char*)sMob.str().c_str());
			vWorldEvent.push_back(tWorldEvent);
		}
	}
	spawnitem.close();
	GameServer::MainServer::WriteBlack(" ------------------ Finished Loading World Event Config ------------------ ");
}