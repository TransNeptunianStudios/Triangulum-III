#ifndef _CONTROL_SYSTEM_H
#define _CONTROL_SYSTEM_H

#include "entityx/System.h"

namespace triangulum {
namespace system {

class ControlSystem : public entityx::System<ControlSystem>
{
public:
  ControlSystem();

  void update(entityx::EntityManager& entities, entityx::EventManager& events,
              entityx::TimeDelta dt);
};

}  // namespace system
}  // namespace triangulum

#endif
