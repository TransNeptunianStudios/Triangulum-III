#ifndef VELOCITY_H
#define VELOCITY_H

#include "entityx/Entity.h"

namespace triangulum {
namespace component {

struct Velocity : public entityx::Component<Velocity>
{
   Velocity(float vx, float vy, float vr);

   float vx, vy, vr;
};

} // namespace component
} // namespace triangulum

#endif
