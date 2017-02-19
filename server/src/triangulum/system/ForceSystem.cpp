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

    float force = 0.1;
    float rotForce = 40;

    float r = body.get_rotation() * M_PI / 180.0;

    if (input.thrust)
    {
      body.apply_force(b2Vec2(cos(r) * force, sin(r) * force));
    }

    if (input.reverse)
    {
      float tr = r + M_PI;
      body.apply_force(b2Vec2(cos(tr) * force * 0.2, sin(tr) * force));
    }

    if (input.strafe_left)
    {
      float tr = r - M_PI_2;
      body.apply_force(b2Vec2(cos(tr) * force * 0.2, sin(tr) * force));
    }

    if (input.strafe_right)
    {
      float tr = r + M_PI_2;
      body.apply_force(b2Vec2(cos(tr) * force * 0.2, sin(tr) * force));
    }

    if (input.turn_left)
    {
      body.apply_torque(-rotForce);
    }

    if (input.turn_right)
    {
      body.apply_torque(rotForce);
    }
  });
}

}  // namespace system
}  // namespace triangulum
