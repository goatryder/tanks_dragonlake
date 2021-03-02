#pragma once

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

// Brick, full block has 16, four of each
constexpr auto BRICK_0 =				"X:\\DragonLake\\Tanki\\Content\\brick\\brick_frag_0.png";
constexpr auto BRICK_1 =				"X:\\DragonLake\\Tanki\\Content\\brick\\brick_frag_1.png";
constexpr auto BRICK_2 =				"X:\\DragonLake\\Tanki\\Content\\brick\\brick_frag_2.png";
constexpr auto BRICK_3 =				"X:\\DragonLake\\Tanki\\Content\\brick\\brick_frag_3.png";

// Bullet
constexpr auto BULLET_UP =				"X:\\DragonLake\\Tanki\\Content\\bullet\\bullet_u.png";
constexpr auto BULLET_DOWN =			"X:\\DragonLake\\Tanki\\Content\\bullet\\bullet_d.png";
constexpr auto BULLET_RIGHT =			"X:\\DragonLake\\Tanki\\Content\\bullet\\bullet_r.png";
constexpr auto BULLET_LEFT =			"X:\\DragonLake\\Tanki\\Content\\bullet\\bullet_l.png";


// Game Consts

#define WINDOW_W						640
#define WINDOW_H						480

#define GAME_AREA_W						208 * 2
#define GAME_AREA_H						208 * 2
#define GAME_CHUNK_W					16 * 2
#define GAME_CHUNK_H					16 * 2

#define GAME_LOGIC_TICK					1000 / 30