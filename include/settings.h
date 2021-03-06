#ifndef _SETTINGS_H
#define _SETTINGS_H

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define FPS 60

#define PLAYER_POS_X (SCREEN_WIDTH / 2)
#define PLAYER_POS_Y (SCREEN_HEIGHT / 2)

#define PLAYER_SPEED 2

#define PI 3.14159265358979323846
#define FOV (PI / 3.0)
#define NUM_RAYS 300
#define MAX_DEPTH 800
#define DELTA_ANGLE (FOV / NUM_RAYS)

#define MAP_SCALE 5
#define MAP_POS_X 0
#define MAP_POS_Y (SCREEN_HEIGHT - SCREEN_HEIGHT / MAP_SCALE)

#endif
