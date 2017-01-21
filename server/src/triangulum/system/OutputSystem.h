#ifndef OUTPUT_SYSTEM_H
#define OUTPUT_SYSTEM_H

#include "entityx/System.h"

namespace triangulum {

  namespace network {
    class IConnection;
    class IConnectionManager;
  }

  namespace system {
  
    class OutputSystem : public entityx::System<OutputSystem>
    {
    public:
      OutputSystem();

      void update(entityx::EntityManager& entities, entityx::EventManager& events,
		  entityx::TimeDelta dt);
    };

  }  // namespace system
}  // namespace triangulum

#endif
