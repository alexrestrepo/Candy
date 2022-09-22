// soundfx.c

#include <SDL2_mixer/SDL_mixer.h>

#include "main.h"
#include "soundfx.h"
#include "music.h"

MBoolean            soundOn = true;
static Mix_Chunk    *s_sound[kNumSounds];

typedef enum
{
    SDLMIX_OK = 0
} SDLMIX_Status;

void SDL_ERRCHECK(int result)
{
    if (result < SDLMIX_OK) {
        printf("SDL_Mixer error! (%d) %s\n", result, Mix_GetError());
        abort();
    }
}

void InitSound( void )
{
    int result = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    SDL_ERRCHECK(result);

    for (int index=0; index<kNumSounds; index++)
    {
        const char *filename = QuickResourceName("snd", index + 128, ".wav");
        Mix_Chunk *wav = Mix_LoadWAV(filename);
        if (wav) {
            // NOTE: release on quit?
            s_sound[index] = wav;

        } else {
            printf("Unable to load wav file %s\n", filename);
            abort();
        }
    }
}


void PlayMono( short which )
{
    PlayStereoFrequency(2, which, 0);
}

void PlayStereo( short player, short which )
{
    PlayStereoFrequency(player, which, 0);
}

void PlayStereoFrequency( short player, short which, short freq )
{
    struct SpeakerMix
    {
        uint8_t left, right;
    };

    SpeakerMix speakerMixForPlayer[] =
    {
        { 255,  0 },
        { 0,    255 },
        { 255,  255 },
    };

    const SpeakerMix& mix = speakerMixForPlayer[player];

    if (soundOn) {        
        int result = Mix_SetPanning(MIX_CHANNEL_POST, mix.left, mix.right);
        SDL_ERRCHECK(result);

        result = Mix_PlayChannel(-1, s_sound[which], 0);
        SDL_ERRCHECK(result);
    }
}

void UpdateSound()
{
    // noop
}

void CleanupAudio()
{
    for (int index=0; index<kNumSounds; index++) {
        Mix_FreeChunk(s_sound[index]);
    }
    Mix_CloseAudio();
}
