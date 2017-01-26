#ifndef _DYNAMIC_BODY_H
#define _DYNAMIC_BODY_H

#include "Box2D/Dynamics/b2Body.h"
#include "entityx/Entity.h"

class b2Body;
class b2Vec;

namespace triangulum {
namespace component {

struct DynamicBody : public entityx::Component<DynamicBody>
{
  using BodyPtr = std::unique_ptr<b2Body, std::function<void(b2Body*)>>;

  DynamicBody(BodyPtr body_);

  void apply_force(b2Vec2 force);  // Force applied to center

  void apply_torque(float torque);

  const b2Vec2& get_position() const;

  const b2Vec2& get_linear_velocity() const;

  float get_rotation() const;

  BodyPtr body;
};

}  // namespace component
}  // namespace triangulum

#endif
