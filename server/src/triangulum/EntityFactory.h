#ifndef _ENTITY_FACTORY_H
#define _ENTITY_FACTORY_H

#include "entityx/Entity.h"

class b2World;

namespace triangulum {

namespace network {
class IConnection;
}  // namesapce network

class EntityFactory
{
public:
  EntityFactory(b2World& world);

  ~EntityFactory();

  void create_player(entityx::Entity entity, const std::string& name,
                     const std::weak_ptr<network::IConnection>& connection);

private:
  b2World& m_world;
};

}  // namespace triangulum

#endif
