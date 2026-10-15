#ifndef PARSER_H
#define PARSER_H

#define FILE_SIGNATURE "[gameliboke]"
#define ZERO "=0="
#define TMPF "tmp.liboke"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @breif a struct that holds the settings values from liboke
 *
 * @var master_sound Floating volume value of all kind of music that running
 *
 * @var background_sound Floating volume of background music(at the start up)
 *
 * @var background_color hexdecial value for color of the theme
 *
 * @var default_config where the default config(liboke) is
 */
typedef struct Settings
{
    float master_sound;
    float background_sound;
    unsigned int background_color;
    char *default_config;
} Settings;

/**
 * @brief a struct that holds one value of card from liboke
 *
 * @var name title of the card
 *
 * @var length the music lenght of the music track in secconds
 *
 * @var score the last played score of the game for that card
 *
 * @var musicPath the directory of the intrumental music
 *
 * @var lrcPath the directory of the LRC
 *
 * @var songPath (optional) the directory of the vocal + intrumental music
 */
typedef struct
{
    char *name;
    float length;
    float score;
    char *musicPath;
    char *lrcPath;
    char *songPath;
} MusicTrack;

/**
 * @brief Deck a bunch of card
 *
 * @var card a array of cards
 *
 * @var count the number of cards
 */
typedef struct Deck
{
    MusicTrack *card;
    int count;
} Deck;

/**
 * @brief a enum the holds the type of editable parameter we have in settings
 *
 *  @var SETTING_MASTER_SOUND or master_sound
 *
 * @var SETTING_BACKGROUND_SOUND or background_sound
 *
 * @var SETTING_BACKGROUND_COLOR or background_color
 *
 * @var SETTING_DEFAULT_CONFIG or default_config
 */
typedef enum SettingType
{
    SETTING_MASTER_SOUND = 0,
    SETTING_BACKGROUND_SOUND,
    SETTING_BACKGROUND_COLOR,
    SETTING_DEFAULT_CONFIG,
} SettingType;

/**
 * @brief a enum the holds the type of editable parameter we have in a single card/MusicTrack
 *
 * @var CARD_TITLE or name
 *
 * @var CARD_LENGTH or length
 *
 * @var CARD_SCORE or score
 *
 * @var CARD_VOCAL_PATH or musicPath
 *
 * @var CARD_MP3_PATH or lrcPath
 *
 * @var CARD_LRC_PATH or songPath
 */
typedef enum Cardtype
{
    CARD_TITLE = 0,
    CARD_LENGTH,
    CARD_SCORE,
    CARD_VOCAL_PATH,
    CARD_MP3_PATH,
    CARD_LRC_PATH,
} Cardtype;

/**
 * @brief Read a File (as text) from a file stream
 *
 * @var f file stream to read
 *
 * @var spacing wether it should return a string that has spacings/ /n / /0 in it
 *
 *  @returns Returns the null terminated string buffer from the file stream
 */
char *ReadFileStream(FILE *f, int spacing);

/**
 * @brief Free a signle card
 *
 * @var card the MusicTrack to free
 *
 */
void freeCard(MusicTrack card);

/**
 * @brief Free every card in a deck
 *
 * @var deck the deck to free
 *
 */
void freeDeck(Deck deck);

/**
 * @brief Free a all variable in settings
 *
 * @var sets sets of settings to free
 *
 */
void freeSettings(Settings sets);

/**
 * @brief Free every deck and settings values
 *
 * @var deck the deck to free
 *
 * @var sets sets of setting to free
 *
 */
void freeLiboke(Deck deck, Settings sets);

/**
 * @brief checks if the .liboke file is valid
 *
 * @var dir directory of the liboke file
 *
 * @returns Return 0 if valid, if not return 1
 */
int ValidateOke(char *dir);

/**
 * @brief Reads the liboke file and fill the value
 *
 * @var dir directory of the liboke file
 *
 * @var cards Deck of cards to fill
 *
 * @var sets sets of setting to fill
 *
 * @returns Returns 1 if anything goes wrong
 *
 */
int ReadOKEData(char *dir, Deck *cards, Settings *sets);
int SetSettingDataEx(char *Indir, char *Outdir, SettingType type, char *val);
int SetCardDataEx(char *Indir, char *Outdir, Cardtype type, int cardIndex, char *val);
int AddNewCardEx(char *Indir, char *Outdir, MusicTrack NewCard);
int RemoveCardEx(char *Indir, char *Outdir, int cardIndex);
int SetSettingData(char *dir, SettingType type, char *val);
int SetCardData(char *dir, Cardtype type, int cardIndex, char *val);
int AddNewCard(char *dir, MusicTrack NewCard);
int RemoveCard(char *dir, int cardIndex);

#endif // !PARSER_H