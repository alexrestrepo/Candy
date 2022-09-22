// prefs.h

void LoadPrefs( void );
void SavePrefs( void );

void GeneratePrefsFile( void );
int UniqueSystem( void );

unsigned char *FindPrefsLine( unsigned char *prefsText, int prefsLength, int searchCode, int dataQuantity );

@class NSString;

struct Preference
{
	NSString*   keyName;
    void *      valuePtr;
    int         valueLength;
};
