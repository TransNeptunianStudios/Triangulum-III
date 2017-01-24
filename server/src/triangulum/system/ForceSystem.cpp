#include "triangulum/system/ForceSystem.h"
#include "Box2D/Dynamics/b2Body.h"

#include "triangulum/component/DynamicBody.h"
#include "triangulum/component/Input.h"

using namespace entityx;

namespace triangulum {
namespace system {

using namespace component;

ForceSystem::ForceSystem()
{
}

void ForceSystem::update(EntityManager& entities,
                         EventManager& events,
                         TimeDelta dt)
{
  // from Inputs
  entities.each<DynamicBody, Input>(
  [](Entity entity, DynamicBody& body, Input& input) {

    float speed = 100.0;

    if (input.thrust)
    {
      body.apply_force(b2Vec2(0.0, -speed));
    }
    if (input.reverse)
    {
      body.apply_force(b2Vec2(0.0, speed));
    }
    if (input.strafe_left)
    {
      body.apply_force(b2Vec2(-speed, 0.0));
    }
    if (input.strafe_right)
    {
      body.apply_force(b2Vec2(speed, 0.0));
    }
    if (input.turn_left)
    {
      body.apply_torque(-speed);
    }
    if (input.turn_right)
    {
      body.apply_torque(speed);
    }
  });
}

}  // namespace system
}  // namespace triangulum
