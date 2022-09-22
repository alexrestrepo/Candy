///
///  SDLU.h
///


#ifndef __SDLU__
#define __SDLU__


#include "MTypes.h"

void         SDLU_Init();
SDL_Rect*    SDLU_MRectToSDLRect( const MRect* in, SDL_Rect* out );
MRect*       SDLU_SDLRectToMRect( const SDL_Rect* in, MRect* out );
int          SDLU_BlitSurface( SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect );
void         SDLU_GetPixel( SDL_Surface* surface, int x, int y, SDL_Color* pixel );
void         SDLU_ChangeSurfaceDepth( SDL_Surface** surface, int depth );
SDL_Surface* SDLU_InitSurface( SDL_Rect* rect, int depth );
void         SDLU_BlitFrontSurface( SDL_Surface* source, SDL_Rect* sourceSDLRect, SDL_Rect* destSDLRect );
void         SDLU_SetBrightness( float b );
void         SDLU_AcquireSurface( SDL_Surface* surface );
SDL_Surface* SDLU_GetCurrentSurface();
void         SDLU_ReleaseSurface( SDL_Surface* surface );
void         SDLU_GetMouse( MPoint* pt );
int          SDLU_Button();
void         SDLU_Yield();
void         SDLU_PumpEvents();
void         SDLU_StartWatchingTyping();
void         SDLU_StopWatchingTyping();
MBoolean     SDLU_CheckASCIITyping(char* ascii);
MBoolean     SDLU_CheckSDLTyping(SDL_Keycode* sdlKey);
int          SDLU_BlitSurfaceHQ( SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect );
MBoolean     SDLU_IsForeground();
void         SDLU_Present();


#endif
