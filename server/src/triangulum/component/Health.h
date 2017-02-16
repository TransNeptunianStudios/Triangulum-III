#ifndef _HEALTH_H
#define _HEALTH_H

#include "entityx/Entity.h"

namespace triangulum {
namespace component {

// Pretty pointless component, move into something bigger? Clientinfo?
struct Health : public entityx::Component<Health>
{
  Health();

  Health(float health_);

  float health;
};

}  // namespace component
}  // namespace triangulum

#endif
