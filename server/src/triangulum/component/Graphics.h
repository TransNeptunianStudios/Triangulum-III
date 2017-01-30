#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "entityx/Entity.h"

namespace triangulum {
namespace component {

struct Graphics : public entityx::Component<Graphics>
{
  Graphics(const std::string& sprite);

  std::string sprite;
  std::string color;
};

}  // namespace component
}  // namespace triangulum

#endif
