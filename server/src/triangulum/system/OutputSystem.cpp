#include "triangulum/system/OutputSystem.h"

#include "triangulum/component/ClientInfo.h"
#include "triangulum/component/DynamicBody.h"
#include "triangulum/network/ConnectionManager.h"

using namespace entityx;

namespace triangulum {
namespace system {

using namespace component;
using namespace network;

OutputSystem::OutputSystem()
{
}

void OutputSystem::update(EntityManager& entities,
                         EventManager& events,
                         TimeDelta dt)
{
   entities.each<DynamicBody>([](
     Entity entity,
     DynamicBody& body) {
				
       /*if (auto connection = client_info.connection.lock())
      {
         Json msg;

         if (connection->get_msg("control", msg) ) //&& msg["input_mask"].is_integer())
         {
         }      
	 }*/
   });
}

} // namespace system
} // namespace triangulum
