#ifndef _DYNAMIC_BODY_H
#define _DYNAMIC_BODY_H

#include "Box2D/Dynamics/b2Body.h"
#include "entityx/Entity.h"

class b2Body;

namespace triangulum {
namespace component {

struct DynamicBody : public entityx::Component<DynamicBody>
{
   using BodyPtr = std::unique_ptr<b2Body, std::function<void(b2Body*)>>;

   DynamicBody(BodyPtr body_);

   void ApplyForce(b2Vec2 force); // Force applied to center

   void ApplyTorque(float torque);

   BodyPtr body;
};

} // namespace component
} // namespace triangulum

#endif
