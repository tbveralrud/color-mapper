#pragma once

#include <functional>
#include <array>
#include <vector>

using Color = int;  // 0x00rrggbb
using Strategy = std::function<Color(Color)>;

template <int TColorsPerChannel>
class ColorMapper {
public:
    ColorMapper(Strategy strategy) {
        for (int z=0; z<TColorsPerChannel; ++z) {
            for (int y=0; y<TColorsPerChannel; ++y) {
                for (int x=0; x<TColorsPerChannel; ++x) {
                    auto i = z * TColorsPerChannel * TColorsPerChannel + y * TColorsPerChannel + x;
                    auto r = (0x100 * z / TColorsPerChannel);
                    auto g = (0x100 * y / TColorsPerChannel);
                    auto b = (0x100 * x / TColorsPerChannel);
                    color_map_[i] = strategy((r << 16) + (g << 8) + b);
                }
            }
        }
    }
    Color operator()(Color in) {
        auto r = ((in >> 16) & 0xFF) * TColorsPerChannel / 0x100;
        auto g = ((in >> 8) & 0xFF) * TColorsPerChannel / 0x100;
        auto b = (in & 0xFF) * TColorsPerChannel / 0x100;
        auto i = r * TColorsPerChannel * TColorsPerChannel + g * TColorsPerChannel + b;
        return color_map_[i];
    }
private:
    std::array<Color, TColorsPerChannel*TColorsPerChannel*TColorsPerChannel> color_map_;
};


class ManhattanDistance {
public:
    template <typename TIterator>
    ManhattanDistance(TIterator begin, TIterator end)
    :  colors_(begin, end)
    {

    }

    Color operator()(Color in) {
        Color out = 0;
        auto distance = std::numeric_limits<int>::max();
        auto r = (in >> 16) & 0xFF;
        auto g = (in >> 8) & 0xFF;
        auto b = in & 0xFF;
        for (auto color : colors_) {
            auto cr = (color >> 16) & 0xFF;
            auto cg = (color >> 8) & 0xFF;
            auto cb = color & 0xFF;
            auto d = std::abs(r-cr) + std::abs(g-cg) + std::abs(b-cb);
            if (d < distance) {
                distance = d;
                out = color;
            }
        }
        return out;
    }
private:
    std::vector<Color> colors_;
};