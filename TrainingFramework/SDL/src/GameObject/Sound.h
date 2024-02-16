#pragma once
#include "SDL_mixer.h"
#include <string>
class Sound
{
public:
	Sound(std::string pathMusic);
	~Sound();
	bool Init();
	void PlaySound();
	void PauseSound();
	void ResumeSound();
	void StopSound();
	void LoadSound(std::string pathMusic);
	void Free();
	void Volume(int volume);
	static inline bool isPlaying = true;
private:
	std::string m_PathMusic;
	Mix_Music* m_Music = NULL;
	
};
