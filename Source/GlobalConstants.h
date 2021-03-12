#pragma once

// Resource Location consts

// BG
constexpr auto BG_IMAGE_PATH =			"X:\\DragonLake\\Tanki\\Content\\BG.png";

// Tank yellow
constexpr auto TANK_DOWN_0 =			"X:\\DragonLake\\Tanki\\Content\\tank0\\tank0_down_0.png";
constexpr auto TANK_DOWN_1 =			"X:\\DragonLake\\Tanki\\Content\\tank0\\tank0_down_1.png";
constexpr auto TANK_UP_0 =				"X:\\DragonLake\\Tanki\\Content\\tank0\\tank0_up_0.png";
constexpr auto TANK_UP_1 =				"X:\\DragonLake\\Tanki\\Content\\tank0\\tank0_up_1.png";
constexpr auto TANK_LEFT_0 =			"X:\\DragonLake\\Tanki\\Content\\tank0\\tank0_left_0.png";
constexpr auto TANK_LEFT_1 =			"X:\\DragonLake\\Tanki\\Content\\tank0\\tank0_left_1.png";
constexpr auto TANK_RIGHT_0 =			"X:\\DragonLake\\Tanki\\Content\\tank0\\tank0_right_0.png";
constexpr auto TANK_RIGHT_1 =			"X:\\DragonLake\\Tanki\\Content\\tank0\\tank0_right_1.png";

// Brick, full block has 16, four of each side
constexpr auto BRICK_0 =				"X:\\DragonLake\\Tanki\\Content\\brick\\brick_frag_0.png";
constexpr auto BRICK_1 =				"X:\\DragonLake\\Tanki\\Content\\brick\\brick_frag_1.png";
constexpr auto BRICK_BASE =				"X:\\DragonLake\\Tanki\\Content\\brick\\brick_base.png";

// Bullet
constexpr auto BULLET_UP =				"X:\\DragonLake\\Tanki\\Content\\bullet\\bullet_u.png";
constexpr auto BULLET_DOWN =			"X:\\DragonLake\\Tanki\\Content\\bullet\\bullet_d.png";
constexpr auto BULLET_RIGHT =			"X:\\DragonLake\\Tanki\\Content\\bullet\\bullet_r.png";
constexpr auto BULLET_LEFT =			"X:\\DragonLake\\Tanki\\Content\\bullet\\bullet_l.png";

// Tank Base Enemy
constexpr auto TANK_EB_DOWN_0 =			"X:\\DragonLake\\Tanki\\Content\\tank_enemy_base\\tank_e_b_down_0.png";
constexpr auto TANK_EB_DOWN_1 =			"X:\\DragonLake\\Tanki\\Content\\tank_enemy_base\\tank_e_b_down_1.png";
constexpr auto TANK_EB_UP_0 =			"X:\\DragonLake\\Tanki\\Content\\tank_enemy_base\\tank_e_b_up_0.png";
constexpr auto TANK_EB_UP_1 =			"X:\\DragonLake\\Tanki\\Content\\tank_enemy_base\\tank_e_b_up_1.png";
constexpr auto TANK_EB_LEFT_0 =			"X:\\DragonLake\\Tanki\\Content\\tank_enemy_base\\tank_e_b_left_0.png";
constexpr auto TANK_EB_LEFT_1 =			"X:\\DragonLake\\Tanki\\Content\\tank_enemy_base\\tank_e_b_left_1.png";
constexpr auto TANK_EB_RIGHT_0 =		"X:\\DragonLake\\Tanki\\Content\\tank_enemy_base\\tank_e_b_right_0.png";
constexpr auto TANK_EB_RIGHT_1 =		"X:\\DragonLake\\Tanki\\Content\\tank_enemy_base\\tank_e_b_right_1.png";

// Base
constexpr auto PHOENIX_PNG =			"X:\\DragonLake\\Tanki\\Content\\phoenix.png";

// Boom
constexpr auto BOOM_SMALL_0 =			"X:\\DragonLake\\Tanki\\Content\\boom\\boom_small_0.png";
constexpr auto BOOM_SMALL_1 =			"X:\\DragonLake\\Tanki\\Content\\boom\\boom_small_1.png";
constexpr auto BOOM_SMALL_2 =			"X:\\DragonLake\\Tanki\\Content\\boom\\boom_small_2.png";
constexpr auto BOOM_BIG_0 =				"X:\\DragonLake\\Tanki\\Content\\boom\\boom_big_0.png";
constexpr auto BOOM_BIG_1 =				"X:\\DragonLake\\Tanki\\Content\\boom\\boom_big_1.png";

// Flashy
constexpr auto FLASHY_0 =				"X:\\DragonLake\\Tanki\\Content\\flashy_0.png";
constexpr auto FLASHY_1 =				"X:\\DragonLake\\Tanki\\Content\\flashy_1.png";

// Boost
constexpr auto BOOST_HP =				"X:\\DragonLake\\Tanki\\Content\\tank_hp_boost.png";

// UI
constexpr auto GAME_OVER =				"X:\\DragonLake\\Tanki\\Content\\UI\\GameOver.png";
constexpr auto WON =					"X:\\DragonLake\\Tanki\\Content\\UI\\Won.png";
constexpr auto LOOSE =					"X:\\DragonLake\\Tanki\\Content\\UI\\Loose.png";
constexpr auto UI_NUM_0 =				"X:\\DragonLake\\Tanki\\Content\\Num\\0.png";
constexpr auto UI_NUM_1 =				"X:\\DragonLake\\Tanki\\Content\\Num\\1.png";
constexpr auto UI_NUM_2 =				"X:\\DragonLake\\Tanki\\Content\\Num\\2.png";
constexpr auto UI_NUM_3 =				"X:\\DragonLake\\Tanki\\Content\\Num\\3.png";
constexpr auto UI_NUM_4 =				"X:\\DragonLake\\Tanki\\Content\\Num\\4.png";
constexpr auto UI_NUM_5 =				"X:\\DragonLake\\Tanki\\Content\\Num\\5.png";


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
#define TANK_SPAWN_RATE_DEFAULT			1000 // time in ms

#define PLAYER_TANK_RESPAWN_NUM			5

#define ENEMY_TANK_SLOW_FIRE_RATE		1000 // in ms

#define ENEMY_TANK_CHANGE_DIRECTION_RATE	600 // in ms

#define BOOM_SMALL_ANIM_TIME			50
#define BOOM_BIG_ANIM_TIME				80

const int FLASHY_ARRAY_DEFAULT[] = { 4, 11, 18 };
const int FLASHY_ARRAY_DEFAULT_SIZE = sizeof FLASHY_ARRAY_DEFAULT / sizeof *FLASHY_ARRAY_DEFAULT;

#define FLASHY_ANIM_TIME				100

#define RESPAWN_PROTECTION_TIME			1000  // zero val will disable spawn protection effect

#define HP_BOOSTER_VAL					1

#define RESTART_TIME					3000