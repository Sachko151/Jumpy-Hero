#include <stdio.h>
#include <raylib.h>
#define WIDTH 600
#define HEIGHT 600
#define TITLE "Jumpy-Hero"
#define OBSTACLE_AMOUNT 2
#define JUMP_POWER 10
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

void jump_physics(player_t *player);
void handle_movement(player_t *player);
void spawn_obstacles(obstacle_t *obstacles, int *score);
void draw_obstacles(obstacle_t *obstacles);
void move_obstacles(obstacle_t *obstacles);
void reset_the_game(int *score, int *game_started);
int player_has_colided(obstacle_t *obstacles, player_t *player);
void display_score(int score, score_text_t *score_text);
void display_main_menu_screen();
int should_start_game();
int should_quit_game();
int main(int argc, char **argv){
    int score = -1;
    int game_started = 0;
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(60);
    Rectangle terrain = {.x=0,.y=550,.height=50,.width=600};
    player_t player = {.player_position.x = 0, .player_position.y=500,.player_size.x=50,
    .player_size.y=50,.color = RED, .weight = 10, .velocity_up=0.0f,.velocity_down=0.0f};
    obstacle_t obsatcles[2];
    score_text_t score_text = {.text_position.x = 0,.text_position.y=0,.font_size=20,.color=RED, .text="asdsa"};
        while (!WindowShouldClose())
        {
            if(should_start_game()) game_started = 1;
                 if(game_started){
                    move_obstacles(obsatcles);
                    jump_physics(&player);
                    handle_movement(&player);
                    spawn_obstacles(obsatcles, &score);
                    if(player_has_colided(obsatcles, &player)) reset_the_game(&score, &game_started);
            } else{
                if(should_quit_game()){
                break;
            }
            }
            

            BeginDrawing();
            {
                if(!game_started){
                    display_main_menu_screen();
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
void jump_physics(player_t *player){
    if(player->player_position.y < HEIGHT - player->player_size.y -50 && !IsKeyDown(KEY_SPACE)){
        player->player_position.y += JUMP_POWER;
    }
}
void handle_movement(player_t *player){
    if(IsKeyDown(KEY_A) && player->player_position.x > 0) player->player_position.x -= 10;
    if(IsKeyDown(KEY_D) && player->player_position.x < WIDTH-player->player_size.x) player->player_position.x += 10;
    if(IsKeyDown(KEY_SPACE) && player->player_position.y > 0){
        player->player_position.y -= JUMP_POWER;
        //  player->player_position.y -= 100;
    }
}
void spawn_obstacles(obstacle_t *obstacles, int *score){
    if(obstacles[0].obstacle_position.x < -obstacles[0].obstacle_size.x){
        int x_pos = GetRandomValue(WIDTH-100,WIDTH+100);
        int height = GetRandomValue(HEIGHT / 4, (HEIGHT / 2) - 50);
        //TOP PILLAR
        obstacles[0].obstacle_position.x = x_pos;
        obstacles[0].obstacle_position.y = 0;
        obstacles[0].obstacle_size.x = 50;
        obstacles[0].obstacle_size.y = height;
        obstacles[0].obstacle_color = RED;
        //BOTTOM PILLAR
        height = GetRandomValue(HEIGHT / 4, (HEIGHT / 2) - 50);
        obstacles[1].obstacle_position.x = x_pos;
        obstacles[1].obstacle_position.y = 550 - height;
        obstacles[1].obstacle_size.x = 50;
        obstacles[1].obstacle_size.y = height;
        obstacles[1].obstacle_color = RED;
        *score = *score + 1;

    }
}
void move_obstacles(obstacle_t *obstacles){
    for (char i = 0; i < OBSTACLE_AMOUNT; i++)
    {
        obstacles[i].obstacle_position.x -= 10;
    }
    
}
void draw_obstacles(obstacle_t *obstacles){
    for (char i = 0; i < OBSTACLE_AMOUNT; i++)
    {
        DrawRectangleV(obstacles[i].obstacle_position, obstacles[i].obstacle_size, obstacles[i].obstacle_color);
    }
}
int player_has_colided(obstacle_t *obstacles, player_t *player){
    Rectangle top_obstacle = {.height=obstacles[0].obstacle_size.y, .width=obstacles[0].obstacle_size.x, 
    .x=obstacles[0].obstacle_position.x, .y=obstacles[0].obstacle_position.y};
    Rectangle bottom_obstacle = {.height=obstacles[1].obstacle_size.y, .width=obstacles[1].obstacle_size.x, 
    .x=obstacles[1].obstacle_position.x, .y=obstacles[1].obstacle_position.y};
    Rectangle player_box = {.height=player->player_size.y, .width=player->player_size.x, 
    .x=player->player_position.x, .y=player->player_position.y};
    if(CheckCollisionRecs(player_box, top_obstacle) || CheckCollisionRecs(player_box, bottom_obstacle)){
        return 1;
    }
    return 0;
}
void reset_the_game(int *score, int *game_started){
    *score = 0;
    *game_started = 0;
    // display_main_menu_screen();
    // printf("HIT!\n");

}
void display_score(int score, score_text_t *score_text){
    sprintf(score_text->text, "Current score:%d", score);
    DrawText(score_text->text, score_text->text_position.x, score_text->text_position.y, 
    score_text->font_size, score_text->color);
}
void display_main_menu_screen(){
    ClearBackground(WHITE);
    DrawRectangle(200,200,200,100,GRAY);
    DrawText("Play", 275,240,20,RED);
    DrawRectangle(200,350,200,100,GRAY);
    DrawText("Exit", 275,390,20,RED);
}
int should_start_game(){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (GetMouseX() > 200 && GetMouseX() < 400) &&
        (GetMouseY() > 200 && GetMouseY() < 300)){
        return 1;
    }
    return 0;
}
int should_quit_game(){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (GetMouseX() > 200 && GetMouseX() < 400) && 
        (GetMouseY() > 350 && GetMouseY() < 450)){
        return 1;
    }
    return 0;
}