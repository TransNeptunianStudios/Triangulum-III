#ifndef _INPUT_SYSTEM_H
#define _INPUT_SYSTEM_H

#include "entityx/System.h"

namespace triangulum {
namespace system {

class InputSystem : public entityx::System<InputSystem>
{
public:
  InputSystem();

  void update(entityx::EntityManager& entities, entityx::EventManager& events,
              entityx::TimeDelta dt);
};

}  // namespace system
}  // namespace triangulum

#endif
