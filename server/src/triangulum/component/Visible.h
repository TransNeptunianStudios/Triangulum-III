#ifndef _VISIBLE_H
#define _VISIBLE_H

#include "entityx/Entity.h"

namespace triangulum{
namespace component {
  
struct Visible : public entityx::Component<Visible>
{
  Visible(const std::string& sprite);

  std::string sprite;
  std::string color;
};

}  // namespace component
}  // namespace triangulum

#endif
