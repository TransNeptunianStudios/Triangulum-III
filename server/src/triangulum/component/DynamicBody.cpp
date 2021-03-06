#include "triangulum/component/DynamicBody.h"

namespace triangulum {
namespace component {

DynamicBody::DynamicBody(BodyPtr body_, entityx::Entity::Id id_)
: body(std::move(body_))
, id(id_)
{
  body->SetUserData(&id);
}

void DynamicBody::apply_force(b2Vec2 force)
{
  body->ApplyForceToCenter(force, true);
}

void DynamicBody::apply_torque(float torque)
{
  body->ApplyTorque(torque, true);
}

const b2Vec2& DynamicBody::get_position() const
{
  return body->GetPosition();
}

const b2Vec2&DynamicBody::get_linear_velocity() const
{
  return body->GetLinearVelocity();
}

float DynamicBody::get_rotation() const
{
  return body->GetAngle();
}

}  // namespace component
}  // namespace triangulum
