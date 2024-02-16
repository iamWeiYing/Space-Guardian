#pragma once
#include "GameManager/Singleton.h"
#include "Sfx.h"
#include <map>
#include <string>

class SoundManager : public CSingleton<SoundManager>
{
private:
	std::shared_ptr<Sfx> sfx;
	std::map<std::string, std::shared_ptr<Sfx>> sfxs;
public:
	void Init();
	void PauseSound();
	void PauseSfx();
	void PlaySound(std::string key);
};

