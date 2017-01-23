#ifndef _FORCE_SYSTEM_H
#define _FORCE_SYSTEM_H

#include "entityx/System.h"

namespace triangulum {
namespace system {

class ForceSystem : public entityx::System<ForceSystem>
{
public:
  ForceSystem();

  void update(entityx::EntityManager& entities, entityx::EventManager& events,
              entityx::TimeDelta dt);
};

}  // namespace system
}  // namespace triangulum

#endif
