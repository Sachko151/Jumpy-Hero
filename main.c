#include <stdio.h>
#include "include/main_game_functions.h"
#include "include/game_params.h"
int main(int argc, char **argv){
    int score = -1;
    int game_started = 0;
    int high_score_ssf = 0;
    int high_score_current = 0;
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(60);
    Rectangle terrain = {.x=0,.y=550,.height=50,.width=600};
    player_t player = {.player_position.x = 0, .player_position.y=500,.player_size.x=50,
    .player_size.y=50,.color = RED, .weight = 10, .velocity_up=0.0f,.velocity_down=0.0f};
    obstacle_t obsatcles[2];
    score_text_t score_text = {.text_position.x = 0,.text_position.y=0,.font_size=20,.color=RED, .text="asdsa"};
        get_high_score(&high_score_ssf);
        high_score_current = high_score_ssf;
        while (!WindowShouldClose())
        {
            if(should_start_game()) game_started = 1;
                 if(game_started){
                    move_obstacles(obsatcles);
                    jump_physics(&player);
                    handle_movement(&player);
                    spawn_obstacles(obsatcles, &score);
                    if(player_has_colided(obsatcles, &player)) reset_the_game(&player,obsatcles,&score, &game_started, &high_score_current);
            } else{
                if(should_quit_game()){
                    save_high_score(high_score_current, &high_score_ssf);
                    break;
                }
            }
            BeginDrawing();
            {
                if(!game_started){
                    display_main_menu_screen(high_score_current);
                } else {
                    ClearBackground(WHITE);
                    DrawRectangleRec(terrain, GREEN);
                    DrawRectangleV(player.player_position, player.player_size, player.color);
                    draw_obstacles(obsatcles);
                    display_score(score, &score_text);
                }
            }
            EndDrawing();
        }
        
    CloseWindow();
    return 0;
}