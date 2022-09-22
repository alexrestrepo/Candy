// music.h


void EnableMusic( MBoolean on );
void PauseMusic( void );
void ResumeMusic( void );
void FastMusic( void );
void SlowMusic( void );
void ChooseMusic( short which );
void InitMusic( void );


extern MBoolean musicOn;
extern int      musicSelection;

namespace FMOD { class System; }

extern MBoolean         soundOn;
extern FMOD::System    *g_fmod;
