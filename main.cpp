#include <iostream>
#include <iomanip>
#include "ColorMapper.h"

int main()
{
    Color palette_colors[] = {
            0x444444,
            0xBBBBBB,
            0xBB2222,
            0x22BB22,
            0x2222BB,
    };

    ColorMapper<8> mapper(ManhattanDistance(std::begin(palette_colors), std::end(palette_colors)));

    Color test_colors[] = {
            0x000000,
            0xFFFFFF,
            0x448888,
            0xCC4444,
            0x99BB99,
            0x4444FF,
    };

    for (auto color_itr = std::begin(test_colors); color_itr != std::end(test_colors); ++color_itr) {
        std::cout << std::setw(6) << std::setfill('0') << std::hex <<
                *color_itr << " => " << mapper(*color_itr) << std::endl;
    }

    return 0;
}