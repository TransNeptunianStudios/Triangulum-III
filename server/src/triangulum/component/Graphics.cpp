#include "triangulum/component/Graphics.h"

namespace triangulum {
namespace component {

  Graphics::Graphics(const std::string& sprite, float width, float height)
: sprite(sprite)
, color("#FFFFFF")
, width(width)
, height(height)
{
}

}  // namespace component
}  // namespace triangulum
