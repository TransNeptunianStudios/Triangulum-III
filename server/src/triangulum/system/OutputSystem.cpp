#include "triangulum/system/OutputSystem.h"

#include "triangulum/component/ClientInfo.h"
#include "triangulum/component/DynamicBody.h"
#include "triangulum/component/Visible.h"
#include "triangulum/network/ConnectionManager.h"

using namespace entityx;

namespace triangulum {
  namespace system {

    using namespace component;
    using namespace network;

    OutputSystem::OutputSystem() {
    }

    void OutputSystem::update(EntityManager& entities, EventManager& events,
			      TimeDelta dt)
    {
      nlohmann::json resp_msg;
      resp_msg["type"] = "update";
      
      entities.each<Visible, DynamicBody>([](Entity entity, Visible& visible, DynamicBody& body) {	  
	 	
	  /*      resp_msg[]["color"] = visible.color;
		  resp_msg[]["sprite"] = visible.sprite;		 
		  resp_msg[]["x"] = body.get_position().x;
		  resp_msg[]["y"] = body.get_position().y;
		  resp_msg[]["vx"] = 0;
		  resp_msg[]["vy"] = 0;	*/
	});
      
      entities.each<ClientInfo>([](Entity entity, ClientInfo& clientinfo) {
	  // send to all clients
	  //clientinfo.connection->send_msg(resp_msg);
	});
    }
  }  // namespace system
}  // namespace triangulum
