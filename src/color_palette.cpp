#include "color_palette.h"

#define ESC "\033"
#define COL(c) (ESC "[" c "m")
#define COLRESET (ESC "[0m")


std::string color_palette::punct = COL("1;33");
std::string color_palette::element = COL("34;1");
const std::string color_palette::text = COL("37;1");
std::string color_palette::attribute = COL("34;1");
std::string color_palette::attribute_value = COL("1;30");
