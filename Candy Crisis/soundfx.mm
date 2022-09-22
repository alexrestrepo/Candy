// soundfx.c

#include <AVFoundation/AVFoundation.h>

#include "main.h"
#include "soundfx.h"
#include "music.h"

MBoolean            soundOn = true;

#define MAX_PLAYERS 4

static AVAudioEngine    *engine;
static AVAudioPlayerNode *audioPlayers[MAX_PLAYERS];
static AVAudioEnvironmentNode *panNodes[MAX_PLAYERS];
static AVAudioUnitVarispeed *rateNodes[MAX_PLAYERS];
static AVAudioFile      *sounds[kNumSounds];
static int CurrentPlayer = 0;

typedef enum
{
    SDLMIX_OK = 0
} SDLMIX_Status;

AVAudioPlayerNode *nextPlayer(float panValue, float rate) {
    AVAudioPlayerNode *player = audioPlayers[CurrentPlayer];
    [player stop]; // just in case?

    AVAudioEnvironmentNode *panNode = panNodes[CurrentPlayer];
    panNode.pan = panValue;

    AVAudioUnitVarispeed *rateNode = rateNodes[CurrentPlayer];
    rateNode.rate = rate;

    CurrentPlayer = (CurrentPlayer + 1) % MAX_PLAYERS;
    return player;
}

void InitSound( void )
{
    engine = [[AVAudioEngine alloc] init];

    for (int i = 0; i < MAX_PLAYERS; i++) {
        audioPlayers[i] = [[AVAudioPlayerNode alloc] init];
        panNodes[i] = [[AVAudioEnvironmentNode alloc] init];
        rateNodes[i] = [[AVAudioUnitVarispeed alloc] init];

        [engine attachNode:audioPlayers[i]];
        [engine attachNode:rateNodes[i]];
        [engine attachNode:panNodes[i]];

        [engine connect:audioPlayers[i] to:rateNodes[i] format:nil];
        [engine connect:rateNodes[i] to:panNodes[i] format:nil];
        [engine connect:panNodes[i] to:engine.mainMixerNode format:nil];
    }

    NSError *error = nil;
    if (![engine startAndReturnError:&error]) {
        printf("Unable to start audio engine%s\n", error.localizedDescription.UTF8String);
        abort();
    }

    for (int index=0; index<kNumSounds; index++)
    {
        const char *filename = QuickResourceName("snd", index + 128, ".wav");

        NSURL *url = [NSURL fileURLWithFileSystemRepresentation:filename isDirectory:NO relativeToURL:nil];

        error = nil;
        AVAudioFile *file = [[AVAudioFile alloc] initForReading:url error:&error];

        if (file) {
            sounds[index] = file;

        } else {
            printf("Unable to load wav file %s: %s\n", filename, error.localizedDescription.UTF8String);
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
    float speakerMixForPlayer[] = {
        -1.0,
        1.0,
        0.0
    };

    const float mix = speakerMixForPlayer[player];

    if (soundOn) {
        float rate = (16.0 + freq) / 16.0;
        AVAudioPlayerNode *audioPlayer = nextPlayer(mix, rate);
        [audioPlayer scheduleFile:sounds[which] atTime:nil completionHandler:nil];
        [audioPlayer play];
    }
}

void UpdateSound()
{
    // noop
}

void CleanupAudio()
{
    // clear files?
    [engine stop];
    engine = nil;
}
