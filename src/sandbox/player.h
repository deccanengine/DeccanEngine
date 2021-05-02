#pragma once
#include <corelib/Deccan.h>

void _player_begin(deccan_game_object_t this);
void _player_step(deccan_game_object_t this);
void _player_render(deccan_game_object_t this);
void _player_end(deccan_game_object_t this);

void _none_begin(deccan_game_object_t this);
void _none_begin2(deccan_game_object_t this);
void _none_step(deccan_game_object_t this);
void _none_render(deccan_game_object_t this);
void _none_end(deccan_game_object_t this);
