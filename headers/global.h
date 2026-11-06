#ifndef GLOBAL_H
#define GLOBAL_H

#include "parser.h"
#ifdef RELEASE
#include "../headers/raylib.h"
#else
#include <raylib.h>
#endif // RELEASE

// definations
#define MAX_FILEPATH_RECORDED 2

// main
extern char *AppData;
extern char *tmpEditData;
extern Deck cards;
extern Settings sett;

// menu
extern enum OPT option;
extern enum STATE mode;

extern char *filePaths[MAX_FILEPATH_RECORDED];
extern char *tmpMp3Path;
extern char *tmpLrcPath;
extern int filePathCounter;
extern Rectangle Subwindow;
extern bool enter;
extern Image tmp_tRay;
extern Image tmp_tLibtinyfiledialogs;
extern Image tmp_tColorhunt;
extern Image tmp_tJ1gggs;

// utility
extern Color Ccol;
extern Color Bocol;
extern Color Mencol;
extern Color Tcol;
extern Color Pcol;
extern Color Butcol1;
extern Color Butcol2;
extern Color Butcol3;
extern Color Butcol4;
extern Color Textcol;
extern Color ExitButcol1;
extern Color ExitButcol2;
extern Color SaveButcol;
extern Color CancelButcol;

#endif // ! GLOBAL_H