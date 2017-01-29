#include "triangulum/EntityFactory.h"
#include <memory>
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"

#include "triangulum/component/Bullet.h"
#include "triangulum/component/ClientInfo.h"
#include "triangulum/component/DynamicBody.h"
#include "triangulum/component/Input.h"
#include "triangulum/component/Visible.h"
#include "triangulum/component/Weapon.h"

using namespace entityx;

namespace triangulum {

using namespace component;
using namespace network;

EntityFactory::EntityFactory(b2World& world)
: m_world(world)
{
}

EntityFactory::~EntityFactory()
{
}

void EntityFactory::create_player(Entity entity,
                                  const std::string& name,
                                  const std::string& color,
                                  const std::weak_ptr<IConnection>& connection)
{
  // Create the Box2D body
  b2BodyDef body_def;

  body_def.type = b2_dynamicBody;

  float x = 2;//static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 200));

  float y = 2;//static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 200));

  body_def.position.Set(x, y);

  body_def.angle = 0.0;

  body_def.linearDamping = 0.5f;

  body_def.angularDamping = 0.5f;

  //shape definition
  b2PolygonShape polygonShape;
  polygonShape.SetAsBox(0.5, 0.5);  //a 1x1 m rectangle

  //fixture definition
  b2FixtureDef myFixtureDef;
  myFixtureDef.shape = &polygonShape;
  myFixtureDef.density = 1;  // Solid

  DynamicBody::BodyPtr body(m_world.CreateBody(&body_def), [](b2Body* b) {
    auto world = b->GetWorld();
    world->DestroyBody(b);
  });

  body->CreateFixture(&myFixtureDef);

  // Assign all components to entity
  entity.assign<ClientInfo>(name, connection);
  entity.assign<DynamicBody>(std::move(body));
  entity.assign<Input>();
  entity.assign<Visible>("player");
  entity.assign<Weapon>();
}

void EntityFactory::create_bullet(Entity entity,
                                  Entity::Id owner_id,
                                  const b2Vec2& position,
                                  const b2Vec2& velocity,
                                  float angle)
{
  float bullet_speed = 20.0f + velocity.Length();

  // Create the Box2D body
  b2BodyDef body_def;

  body_def.type = b2_dynamicBody;

  body_def.position.Set(position.x, position.y);

  body_def.angle = angle;

  float r = angle * M_PI / 180.0;

  body_def.linearVelocity.Set(cos(r) * bullet_speed, sin(r) * bullet_speed);

  body_def.fixedRotation = true;

  //body_def.bullet = true;

  DynamicBody::BodyPtr body(m_world.CreateBody(&body_def), [](b2Body* b) {
    auto world = b->GetWorld();
    world->DestroyBody(b);
  });

  //shape definition
  //b2PolygonShape polygonShape;

  //polygonShape.SetAsBox(0.1, 0.1);

  //fixture definition
  //b2FixtureDef fixture_def;

  //fixture_def.shape = &polygonShape;

  //fixture_def.density = 1;  // Solid

  //body->CreateFixture(&fixture_def);

  entity.assign<Bullet>(owner_id, 5.0, 10.0);
  entity.assign<DynamicBody>(std::move(body));
  entity.assign<Visible>("basic_green_bullet");
}

}  // namespace triangulum
