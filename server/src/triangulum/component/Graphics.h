#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "entityx/Entity.h"

namespace triangulum {
namespace component {

struct Graphics : public entityx::Component<Graphics>
{
  Graphics(const std::string& sprite, float width = 1.0, float height = 1.0);

  std::string sprite;
  std::string color;
  float width, height;
};

}  // namespace component
}  // namespace triangulum

#endif
