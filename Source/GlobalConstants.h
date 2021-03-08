#pragma once

// Resource Location consts

// BG
constexpr auto BG_IMAGE_PATH =			"E:\\DragonLake\\tanks_dragonlake\\Content\\BG.png";

// Tank yellow
constexpr auto TANK_DOWN_0 =			"E:\\DragonLake\\tanks_dragonlake\\Content\\tank0\\tank0_down_0.png";
constexpr auto TANK_DOWN_1 =			"E:\\DragonLake\\tanks_dragonlake\\Content\\tank0\\tank0_down_1.png";
constexpr auto TANK_UP_0 =				"E:\\DragonLake\\tanks_dragonlake\\Content\\tank0\\tank0_up_0.png";
constexpr auto TANK_UP_1 =				"E:\\DragonLake\\tanks_dragonlake\\Content\\tank0\\tank0_up_1.png";
constexpr auto TANK_LEFT_0 =			"E:\\DragonLake\\tanks_dragonlake\\Content\\tank0\\tank0_left_0.png";
constexpr auto TANK_LEFT_1 =			"E:\\DragonLake\\tanks_dragonlake\\Content\\tank0\\tank0_left_1.png";
constexpr auto TANK_RIGHT_0 =			"E:\\DragonLake\\tanks_dragonlake\\Content\\tank0\\tank0_right_0.png";
constexpr auto TANK_RIGHT_1 =			"E:\\DragonLake\\tanks_dragonlake\\Content\\tank0\\tank0_right_1.png";

// Brick, full block has 16, four of each side
constexpr auto BRICK_0 =				"E:\\DragonLake\\tanks_dragonlake\\Content\\brick\\brick_frag_0.png";
constexpr auto BRICK_1 =				"E:\\DragonLake\\tanks_dragonlake\\Content\\brick\\brick_frag_1.png";
constexpr auto BRICK_0C =				"E:\\DragonLake\\tanks_dragonlake\\Content\\brick\\brick_frag_0c.png";
constexpr auto BRICK_1C =				"E:\\DragonLake\\tanks_dragonlake\\Content\\brick\\brick_frag_1c.png";

constexpr auto BRICK_BASE =				"E:\\DragonLake\\tanks_dragonlake\\Content\\brick\\brick_base.png";

// Bullet
constexpr auto BULLET_UP =				"E:\\DragonLake\\tanks_dragonlake\\Content\\bullet\\bullet_u.png";
constexpr auto BULLET_DOWN =			"E:\\DragonLake\\tanks_dragonlake\\Content\\bullet\\bullet_d.png";
constexpr auto BULLET_RIGHT =			"E:\\DragonLake\\tanks_dragonlake\\Content\\bullet\\bullet_r.png";
constexpr auto BULLET_LEFT =			"E:\\DragonLake\\tanks_dragonlake\\Content\\bullet\\bullet_l.png";

// Tank Base Enemy
constexpr auto TANK_EB_DOWN_0 =			"E:\\DragonLake\\tanks_dragonlake\\Content\\tank_enemy_base\\tank_e_b_down_0.png";
constexpr auto TANK_EB_DOWN_1 =			"E:\\DragonLake\\tanks_dragonlake\\Content\\tank_enemy_base\\tank_e_b_down_1.png";
constexpr auto TANK_EB_UP_0 =			"E:\\DragonLake\\tanks_dragonlake\\Content\\tank_enemy_base\\tank_e_b_up_0.png";
constexpr auto TANK_EB_UP_1 =			"E:\\DragonLake\\tanks_dragonlake\\Content\\tank_enemy_base\\tank_e_b_up_1.png";
constexpr auto TANK_EB_LEFT_0 =			"E:\\DragonLake\\tanks_dragonlake\\Content\\tank_enemy_base\\tank_e_b_left_0.png";
constexpr auto TANK_EB_LEFT_1 =			"E:\\DragonLake\\tanks_dragonlake\\Content\\tank_enemy_base\\tank_e_b_left_1.png";
constexpr auto TANK_EB_RIGHT_0 =		"E:\\DragonLake\\tanks_dragonlake\\Content\\tank_enemy_base\\tank_e_b_right_0.png";
constexpr auto TANK_EB_RIGHT_1 =		"E:\\DragonLake\\tanks_dragonlake\\Content\\tank_enemy_base\\tank_e_b_right_1.png";

// Base
constexpr auto PHOENIX_PNG =			"E:\\DragonLake\\tanks_dragonlake\\Content\\phoenix.png";

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


// Game Logic consts

#define GAME_LOGIC_TICK					1000 / 25  // in ms, update time 2 ms is minimal, 33 or 16 fit best
#define GAME_SPEED_MIN					(1000 / (GAME_LOGIC_TICK))  // one pixel in one game tick


// Game Paramters consts
// Note: if GAME_LOGIC_TICK * Speed < 1000 speed will be equal zero, 
// if GAME_LOGIC_TICK == 33, 31 is min speed value

#define TANK_SPEED_SLOW					GAME_SPEED_MIN * 5 // pixels in one sec
#define TANK_SPEED_SLOW_ANIM_TIME		160 // Time in ms to SpriteFlipFlop swap sprites
#define TANK_HEALTH_BASIC				1

#define BULLET_SPEED_SLOW				GAME_SPEED_MIN * 12 // pixels in one sesc
#define BULLET_DAMAGE_LOW				1

#define BRICK_BASE_HEALTH				1

#define TANK_SPAWN_NUM_DEFAULT			3
#define TANK_SPAWN_RATE_DEFAULT			1000 // time in ms