#ifndef _ENTITY_FACTORY_H
#define _ENTITY_FACTORY_H

#include "entityx/Entity.h"

class b2World;
struct b2Vec2;

namespace triangulum {

namespace network {
class IConnection;
}  // namesapce network

class EntityFactory
{
public:
  EntityFactory(b2World& world);

  ~EntityFactory();

  void create_player(entityx::Entity entity,
                     const std::string& name,
                     const std::string& color,
                     const std::weak_ptr<network::IConnection>& connection);

  void create_bullet(entityx::Entity entity,
                     entityx::Entity::Id owner_id,
                     const b2Vec2& position,
                     const b2Vec2& velocity,
                     float angle);

  void create_simple_asteroid(entityx::Entity entity,
		     const b2Vec2& position,
                     float size,
		     float angle);

  void create_border_block(entityx::Entity entity,
		     const b2Vec2& position,
			   float width,
			   float height);
private:
  b2World& m_world;
};

}  // namespace triangulum

#endif
