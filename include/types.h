#include <raylib.h>
#ifndef __TYPES_H__
#define __TYPES_H__
typedef struct
{
    Vector2 player_position;
    Vector2 player_size;
    Color color;
    float weight;
    float velocity_up;
    float velocity_down;
} player_t;
typedef struct
{
    Vector2 obstacle_position;
    Vector2 obstacle_size;
    Color obstacle_color;
} obstacle_t;
typedef struct
{
    char text[64];
    Vector2 text_position;
    int font_size;
    Color color;
    
} score_text_t;
#endif