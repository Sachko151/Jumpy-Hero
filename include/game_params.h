#ifndef __GAME_PARAMS_H__
#define __GAME_PARAMS_H__
#define WIDTH 600
#define HEIGHT 600
#define TITLE "Jumpy-Hero"
#define OBSTACLE_AMOUNT 2
#define JUMP_POWER 10
#define SAVE_FILE_FILENAME "high_score.ssf"
#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif
#endif