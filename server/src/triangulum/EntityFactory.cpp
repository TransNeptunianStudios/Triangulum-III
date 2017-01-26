#include "triangulum/EntityFactory.h"
#include <memory>
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"

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

  float x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 200));
  float y = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 200));

  body_def.position.Set(x, y);
  body_def.angle = 0;

  //shape definition
  b2PolygonShape polygonShape;
  polygonShape.SetAsBox(0.5, 1);  //a 1x2 rectangle

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
                                  const b2Vec2& position,
                                  float angle)
{
  // Create the Box2D body
  b2BodyDef body_def;

  body_def.type = b2_dynamicBody;

  body_def.position.Set(position.x, position.y);

  body_def.angle = angle;

  body_def.linearVelocity.Set(0.0f, -100.0f);

  body_def.fixedRotation = true;

  //shape definition
  b2PolygonShape polygonShape;

  polygonShape.SetAsBox(0.1, 0.1);

  //fixture definition
  b2FixtureDef fixture_def;

  fixture_def.shape = &polygonShape;

  fixture_def.density = 1;  // Solid

  DynamicBody::BodyPtr body(m_world.CreateBody(&body_def), [](b2Body* b) {
    auto world = b->GetWorld();
    world->DestroyBody(b);
  });

  body->CreateFixture(&fixture_def);

  entity.assign<DynamicBody>(std::move(body));
  entity.assign<Visible>("basic_green_bullet");
  entity.assign<Weapon>();
}

}  // namespace triangulum
