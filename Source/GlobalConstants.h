#pragma once

#include <string>

std::string GetResourcePath(const char* RelativePath);

constexpr auto EXE_NAME = "tanks_dragonlake.exe";  // used in hack to get root path


// Resource Location consts

// BG
constexpr auto BG_IMAGE_PATH =			"resources\\BG.png";

// Tank yellow
constexpr auto TANK_DOWN_0 =			"resources\\tank0\\tank0_down_0.png";
constexpr auto TANK_DOWN_1 =			"resources\\tank0\\tank0_down_1.png";
constexpr auto TANK_UP_0 =				"resources\\tank0\\tank0_up_0.png";
constexpr auto TANK_UP_1 =				"resources\\tank0\\tank0_up_1.png";
constexpr auto TANK_LEFT_0 =			"resources\\tank0\\tank0_left_0.png";
constexpr auto TANK_LEFT_1 =			"resources\\tank0\\tank0_left_1.png";
constexpr auto TANK_RIGHT_0 =			"resources\\tank0\\tank0_right_0.png";
constexpr auto TANK_RIGHT_1 =			"resources\\tank0\\tank0_right_1.png";

// Brick, full block has 16, four of each side
constexpr auto BRICK_0 =				"resources\\brick\\brick_frag_0.png";
constexpr auto BRICK_1 =				"resources\\brick\\brick_frag_1.png";
constexpr auto BRICK_BASE =				"resources\\brick\\brick_base.png";

// Bullet
constexpr auto BULLET_UP =				"resources\\bullet\\bullet_u.png";
constexpr auto BULLET_DOWN =			"resources\\bullet\\bullet_d.png";
constexpr auto BULLET_RIGHT =			"resources\\bullet\\bullet_r.png";
constexpr auto BULLET_LEFT =			"resources\\bullet\\bullet_l.png";

// Tank Base Enemy
constexpr auto TANK_EB_DOWN_0 =			"resources\\tank_enemy_base\\tank_e_b_down_0.png";
constexpr auto TANK_EB_DOWN_1 =			"resources\\tank_enemy_base\\tank_e_b_down_1.png";
constexpr auto TANK_EB_UP_0 =			"resources\\tank_enemy_base\\tank_e_b_up_0.png";
constexpr auto TANK_EB_UP_1 =			"resources\\tank_enemy_base\\tank_e_b_up_1.png";
constexpr auto TANK_EB_LEFT_0 =			"resources\\tank_enemy_base\\tank_e_b_left_0.png";
constexpr auto TANK_EB_LEFT_1 =			"resources\\tank_enemy_base\\tank_e_b_left_1.png";
constexpr auto TANK_EB_RIGHT_0 =		"resources\\tank_enemy_base\\tank_e_b_right_0.png";
constexpr auto TANK_EB_RIGHT_1 =		"resources\\tank_enemy_base\\tank_e_b_right_1.png";

// Base
constexpr auto PHOENIX_PNG =			"resources\\phoenix.png";

// Boom
constexpr auto BOOM_SMALL_0 =			"resources\\boom\\boom_small_0.png";
constexpr auto BOOM_SMALL_1 =			"resources\\boom\\boom_small_1.png";
constexpr auto BOOM_SMALL_2 =			"resources\\boom\\boom_small_2.png";
constexpr auto BOOM_BIG_0 =				"resources\\boom\\boom_big_0.png";
constexpr auto BOOM_BIG_1 =				"resources\\boom\\boom_big_1.png";

// Flashy
constexpr auto FLASHY_0 =				"resources\\flashy_0.png";
constexpr auto FLASHY_1 =				"resources\\flashy_1.png";

// Boost
constexpr auto BOOST_HP =				"resources\\tank_hp_boost.png";

// UI
constexpr auto WON_UI =					"resources\\UI\\GameOverWon.png";
constexpr auto LOOSE_UI =				"resources\\UI\\GameOverLoose.png";
constexpr auto TANK_ICO_UI =			"resources\\UI\\ui_enemy.png";
constexpr auto UI_NUM_0 =				"resources\\Num\\0.png";
constexpr auto UI_NUM_1 =				"resources\\Num\\1.png";
constexpr auto UI_NUM_2 =				"resources\\Num\\2.png";
constexpr auto UI_NUM_3 =				"resources\\Num\\3.png";
constexpr auto UI_NUM_4 =				"resources\\Num\\4.png";
constexpr auto UI_NUM_5 =				"resources\\Num\\5.png";
constexpr auto UI_NUM_6 =				"resources\\Num\\6.png";
constexpr auto UI_NUM_7 =				"resources\\Num\\7.png";
constexpr auto UI_NUM_8 =				"resources\\Num\\8.png";
constexpr auto UI_NUM_9 =				"resources\\Num\\9.png";


// Game Sizes conts

#define WINDOW_W						640
#define WINDOW_H						480

#define GAME_AREA_OFFSET_W				64
#define GAME_AREA_OFFSET_H				32

#define GAME_AREA_W						208 * 2  // orig game 2x scaled 
#define GAME_AREA_H						208 * 2

#define GAME_AREA_W0					GAME_AREA_OFFSET_W
#define GAME_AREA_W1					GAME_AREA_OFFSET_W + GAME_AREA_W

#define GAME_AREA_H0					GAME_AREA_OFFSET_H
#define GAME_AREA_H1					GAME_AREA_OFFSET_H + GAME_AREA_H

#define GAME_AREA_MID_W					GAME_AREA_W / 2 + GAME_AREA_OFFSET_W				
#define GAME_AREA_MID_H					GAME_AREA_H / 2 + GAME_AREA_OFFSET_H				

#define GAME_CHUNK_W					16 * 2  // orig game 2x scaled
#define GAME_CHUNK_H					16 * 2  // orig game 2x scaled

#define TANK_W							13 * 2  // orig game 2x scaled
#define TANK_H							13 * 2  // orig game 2x scaled


// Game Logic consts

#define GAME_LOGIC_TICK					1000 / 60  // in ms, update time 2 ms is minimal, 33 or 16 fit best
#define GAME_SPEED_MIN					(1000 / (GAME_LOGIC_TICK))  // one pixel in one game tick


// Game Paramters consts
// Note: if GAME_LOGIC_TICK * Speed < 1000 speed will be equal zero, 
// if GAME_LOGIC_TICK == 33, 31 is min speed value

#define TANK_SPEED_SLOW					GAME_SPEED_MIN * 2 // pixels in one sec
#define TANK_SPEED_SLOW_ANIM_TIME		100 // Time in ms to SpriteFlipFlop swap sprites
#define TANK_HEALTH_BASIC				1

#define BULLET_SPEED_SLOW				GAME_SPEED_MIN * 7 // pixels in one sesc
#define BULLET_DAMAGE_LOW				1

#define BRICK_BASE_HEALTH				1

#define TANK_SPAWN_NUM_DEFAULT			20
#define TANK_SPAWN_RATE_DEFAULT			1200 // time in ms

#define PLAYER_TANK_RESPAWN_NUM			5

#define ENEMY_TANK_SLOW_FIRE_RATE		600 // in ms

#define ENEMY_TANK_CHANGE_DIRECTION_RATE	800 // in ms

#define BOOM_SMALL_ANIM_TIME			50
#define BOOM_BIG_ANIM_TIME				80

const int FLASHY_ARRAY_DEFAULT[] = { 4, 11, 18 };
const int FLASHY_ARRAY_DEFAULT_SIZE = sizeof FLASHY_ARRAY_DEFAULT / sizeof *FLASHY_ARRAY_DEFAULT;

#define FLASHY_ANIM_TIME				100

#define RESPAWN_PROTECTION_TIME			1000  // zero val will disable spawn protection effect

#define HP_BOOSTER_VAL					1

#define RESTART_TIME					3000

// ui elements

#define GAME_OVER_PLATE_W				200	
#define GAME_OVER_PLATE_H				225

#define TANK_UI_FIRST_W					496
#define TANK_UI_FIRST_H					60
#define TANK_UI_OFFSET_W				16
#define TANK_UI_OFFSET_H				16
#define TANK_UI_MAX						20
#define TANK_UI_HORIZONTAL_MAX			2

#define PLAYER_RESPAWN_NUM_W			514
#define PLAYER_RESPAWN_NUM_H			274
#define UI_NUM_DIGIT_OFFSET				16


