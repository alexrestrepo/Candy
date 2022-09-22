// music.c

#include <string.h>

#include "main.h"
#include "music.h"
#include "gworld.h"
#include "gameticks.h"
#include "soundfx.h"
#include "graphics.h"

#include "fmod.hpp"
#include "fmod_errors.h"

const int               k_noMusic = -1;
const int               k_songs = 14;

MBoolean                musicOn = true;
int                     musicSelection = k_noMusic;

static MBoolean         s_musicFast = false;
int                     s_musicPaused = 0;
static FMOD::Channel*   s_musicChannel = NULL;
static FMOD::Sound*     s_musicModule = NULL;

FMOD::System              *g_fmod;

void FMOD_ERRCHECK(int result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(FMOD_RESULT(result)));
        abort();
    }
}

void InitMusic( void )
{
#warning music doesn't work just yet...
    return;

    FMOD_RESULT   result = FMOD::System_Create(&g_fmod);
    FMOD_ERRCHECK(result);

    unsigned int  version;
    result = g_fmod->getVersion(&version);
    FMOD_ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        abort();
    }

    result = g_fmod->init(64, FMOD_INIT_NORMAL, 0);
    FMOD_ERRCHECK(result);
}

void EnableMusic( MBoolean on )
{
    if (s_musicChannel)
    {
        FMOD_RESULT result = s_musicChannel->setVolume(on? 0.75f: 0.0f);
        FMOD_ERRCHECK(result);
    }
}

void FastMusic( void )
{
    if (s_musicModule && !s_musicFast)
    {
        FMOD_RESULT result = s_musicModule->setMusicSpeed(1.3f);
        FMOD_ERRCHECK(result);
        
        s_musicFast = true;
    }
}

void SlowMusic( void )
{
    if (s_musicModule && s_musicFast)
    {
        FMOD_RESULT result = s_musicModule->setMusicSpeed(1.0f);
        FMOD_ERRCHECK(result);
        
        s_musicFast = false;
    }
}

void PauseMusic( void )
{
    if (s_musicChannel)
    {
        FMOD_RESULT result = s_musicChannel->setPaused(true);
        FMOD_ERRCHECK(result);
        
        s_musicPaused++;
    }
}

void ResumeMusic( void )
{
    if (s_musicChannel)
    {
        FMOD_RESULT result = s_musicChannel->setPaused(false);
        FMOD_ERRCHECK(result);
        
        s_musicPaused--;
    }
}

void ChooseMusic( short which )
{
#warning music doesn't work just yet...
    return;
    
    if (s_musicChannel != NULL)
    {
        s_musicChannel->stop();
        s_musicChannel = NULL;
    }
    
    if (s_musicModule != NULL)
    {
        s_musicModule->release();
        s_musicModule = NULL;
    }
    
    musicSelection = -1;
    
    if (which >= 0 && which <= k_songs)
    {
        FMOD_RESULT result = g_fmod->createSound(QuickResourceName("mod", which+128, ""), FMOD_DEFAULT, 0, &s_musicModule);
        FMOD_ERRCHECK(result);
        
        result = g_fmod->playSound(FMOD_CHANNEL_FREE, s_musicModule, true, &s_musicChannel);
        FMOD_ERRCHECK(result);
        
        result = s_musicChannel->setPriority(10); // prioritize music first--WAVs should never knock out a MOD
        FMOD_ERRCHECK(result);
        
        EnableMusic(musicOn);
        
        result = s_musicModule->setLoopCount(-1);
        FMOD_ERRCHECK(result);
        
        result = s_musicChannel->setPaused(false);
        FMOD_ERRCHECK(result);
        
        musicSelection = which;
        s_musicPaused  = 0;
    }
}
