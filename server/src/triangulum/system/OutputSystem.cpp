#include "triangulum/system/OutputSystem.h"

#include "triangulum/component/ClientInfo.h"
#include "triangulum/component/DynamicBody.h"
#include "triangulum/network/ConnectionManager.h"

using namespace entityx;

namespace triangulum {
  namespace system {

    using namespace component;
    using namespace network;

    OutputSystem::OutputSystem() {}

    void OutputSystem::update(EntityManager& entities, EventManager& events,
			      TimeDelta dt)
    {
      entities.each<ClientInfo>([](Entity entity, ClientInfo& bodyClient) {
	  // take everything with a dynamic body and put it in a list.
	});
    }

  }  // namespace system
}  // namespace triangulum
