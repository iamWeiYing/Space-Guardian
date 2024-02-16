#include "Sfx.h"
#include <SDL_ttf.h>

Sfx::Sfx(std::string pathMusic)
{
    Init();
    LoadSfx(pathMusic);
}

Sfx::~Sfx()
{
    Free();
}

bool Sfx::Init()
{
    bool ret = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) //SDL_INIT_AUDIO for Init SDL audio
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        ret = false;

    }
    //Initialize SDL_mixer
      // first argument sets the Sfx frequency, and 44100 is a standard frequency that works on most systems. The second argument determines the sample format, which again here we're using the default. The third argument is the number of hardware channels, and here we're using 2 channels for stereo. The last argument is the sample size, which determines the size of the chunks we use when playing Sfx. 2048 bytes (AKA 2 kilobyes) worked fine for me, but you may have to experiment with this value to minimize lag when playing Sfxs.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        ret = false;
    }
    return ret;
}

void Sfx::PlaySfx()
{
    Mix_PlayChannel(-1, m_Chunk, 0);
}

void Sfx::LoadSfx(std::string pathMusic)
{
    //Load music
    m_Chunk = Mix_LoadWAV(pathMusic.c_str());
    if (m_Chunk == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());

    }
}

void Sfx::StopSfx()
{
    Mix_HaltChannel(-1);
}

void Sfx::Free()
{
    Mix_FreeChunk(m_Chunk);
    m_Chunk = NULL;
}

void Sfx::Volume(int volume) {
    Mix_VolumeChunk(m_Chunk, volume);
}