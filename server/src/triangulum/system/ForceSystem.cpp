#include "triangulum/system/ForceSystem.h"

#include <math.h>

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

    float speed = 7.5;
    float rotSpeed = 50;

    float r = body.get_rotation() * M_PI / 180.0;

    if (input.thrust)
    {
      body.apply_force(b2Vec2(cos(r) * speed, sin(r) * speed));
    }

    if (input.reverse)
    {
      float tr = r + M_PI;
      body.apply_force(b2Vec2(cos(tr) * speed, sin(tr) * speed));
    }

    if (input.strafe_left)
    {
      float tr = r - M_PI_2;
      body.apply_force(b2Vec2(cos(tr) * speed, sin(tr) * speed));
    }

    if (input.strafe_right)
    {
      float tr = r + M_PI_2;
      body.apply_force(b2Vec2(cos(tr) * speed, sin(tr) * speed));
    }

    if (input.turn_left)
    {
      body.apply_torque(-rotSpeed);
    }

    if (input.turn_right)
    {
      body.apply_torque(rotSpeed);
    }
  });
}

}  // namespace system
}  // namespace triangulum
