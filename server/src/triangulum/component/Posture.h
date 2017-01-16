#ifndef POSTURE_H
#define POSTURE_H

#include "entityx/Entity.h"

namespace triangulum {
namespace component {

struct Posture : public entityx::Component<Posture>
{
   Posture(float x, float y, float r);

   float x, y, r;
};

} // namespace component
} // namespace triangulum

#endif
