#ifndef COLOR_H
#define COLOR_H

class Color {
 public:
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) :
    r(r), g(g), b(b), alpha(alpha) {}
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t alpha;
};

namespace Palette{
const Color background{0x1E, 0x1E, 0x1E, 0xFF};
const Color food{0xFF, 0xCC, 0x00, 0xFF};
const Color snake_body{0, 166, 96, 0xFF};
const Color snake_head_alive{0x00, 0x7A, 0xCC, 0xFF};
const Color snake_head_dead{0xFF, 0x00, 0x00, 0xFF};
const Color snake_tail{0xFF, 0, 0xFF, 0xFF};
const Color white{0xFF, 0xFF, 0xFF, 0xFF};
}
#endif