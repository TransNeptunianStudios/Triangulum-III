#include "triangulum/component/DynamicBody.h"

namespace triangulum {
namespace component {

DynamicBody::DynamicBody(BodyPtr body_)
   : body(std::move(body_))
{
}

  void DynamicBody::ApplyForce(b2Vec2 force)
  {
    this->body->ApplyForceToCenter(force, true);
  }

  void DynamicBody::ApplyTorque(float torque)
  {
    this->body->ApplyTorque( torque, true);
  }

} // namespace component
} // namespace triangulum
