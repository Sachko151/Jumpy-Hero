#ifndef __MAIN_GAME_FUNCS_H__
#define __MAIN_GAME_FUNCS_H__
#include "types.h"
void jump_physics(player_t *player);
void handle_movement(player_t *player);
void spawn_obstacles(obstacle_t *obstacles, int *score);
void draw_obstacles(obstacle_t *obstacles);
void move_obstacles(obstacle_t *obstacles);
void reset_the_game(player_t *player,obstacle_t *obstacles, int *score, int *game_started, int *high_score);
int player_has_colided(obstacle_t *obstacles, player_t *player);
void display_score(int score, score_text_t *score_text);
void display_main_menu_screen();
int should_start_game();
int should_quit_game();
int score_file_exists();
void get_high_score(int *high_score);
void save_high_score(int score, int *high_score);
void clear_obstacles(obstacle_t *obstacles);
void display_high_score(int high_score);
#endif