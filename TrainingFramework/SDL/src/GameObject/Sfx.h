#pragma once
#include "SDL_mixer.h"
#include <string>
class Sfx
{
public:
	Sfx(std::string pathMusic);
	~Sfx();
	bool Init();
	void PlaySfx();
	void StopSfx();
	void LoadSfx(std::string pathMusic);
	void Free();
	void Volume(int volume);
	static inline bool isPlaying = true;
private:
	std::string m_PathMusic;
	Mix_Chunk* m_Chunk = NULL;

};
