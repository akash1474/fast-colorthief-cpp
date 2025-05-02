#pragma once
#include <vector>
#include "constants.hpp"

enum Color {RED, GREEN, BLUE};

int get_color_index(int r, int g, int b);
std::vector<color_t> get_palette_cpp(uint8_t* data, int width, int height, int color_count, int quality);
