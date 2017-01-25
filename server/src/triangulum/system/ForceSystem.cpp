#include "triangulum/system/ForceSystem.h"
#include "Box2D/Dynamics/b2Body.h"

#include "triangulum/component/DynamicBody.h"
#include "triangulum/component/Input.h"

#include <math.h>

# define PI          3.141592653589793238462643383279502884L /* pi */

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
    float r = body.get_rotation() * PI / 180.0;
    
    if (input.thrust)
    {
      float tr = r - PI/2;
      body.apply_force( b2Vec2(cos(tr) * speed, sin(tr) * speed) );
    }
    if (input.strafe_right)
    {
      body.apply_force( b2Vec2(cos(r) * speed, sin(r) * speed) );
    }
    if (input.reverse)
    {
      float tr = r + PI/2;
      body.apply_force( b2Vec2(cos(tr) * speed, sin(tr) * speed) );
    }
    if (input.strafe_left)
    {
      float tr = r + PI;
      body.apply_force( b2Vec2(cos(tr) * speed, sin(tr) * speed) );
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
