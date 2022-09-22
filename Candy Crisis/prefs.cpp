// prefs.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Cocoa/Cocoa.h>

#include "main.h"
#include "prefs.h"
#include "music.h"
#include "soundfx.h"
#include "hiscore.h"
#include "keyselect.h"

Preference prefList[] =
{
    { @"MusicOn",        &musicOn,     sizeof(MBoolean  ) },
    { @"SoundOn",        &soundOn,     sizeof(MBoolean  ) },
    { @"KeyBindings",    playerKeys,   sizeof(playerKeys) },
    { @"HighScores",     scores,       sizeof(scores    ) },
    { @"BestCombo",      &best,        sizeof(best      ) }
};


void LoadPrefs()
{
    for (Preference& pref: prefList)
    {
        NSData* data = [[NSUserDefaults standardUserDefaults] dataForKey:pref.keyName];
        if ([data length] == pref.valueLength)
        {
            memcpy(pref.valuePtr, [data bytes], pref.valueLength);
        }
    }
}


void SavePrefs()
{
    for (Preference& pref: prefList)
    {
        [[NSUserDefaults standardUserDefaults]
            setObject:[NSData dataWithBytes:pref.valuePtr length:pref.valueLength]
               forKey:pref.keyName];
    }
    
    [[NSUserDefaults standardUserDefaults] synchronize];
}
