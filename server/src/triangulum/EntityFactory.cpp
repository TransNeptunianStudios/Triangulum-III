#include "triangulum/EntityFactory.h"
#include <memory>
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Box2D/Collision/Shapes/b2EdgeShape.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"

#include "Box2D/Common/b2Math.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"

#include "triangulum/component/Bullet.h"
#include "triangulum/component/ClientInfo.h"
#include "triangulum/component/DynamicBody.h"
#include "triangulum/component/Graphics.h"
#include "triangulum/component/Input.h"
#include "triangulum/component/Score.h"
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
  // This whole thing MUST be put into dynamicBody some way? :S
  b2BodyDef body_def;

  body_def.type = b2_dynamicBody;

  float x =
  36;  // + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 20));

  float y =
  5;  // + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 20));

  body_def.position.Set(x, y);

  body_def.angle = 0.0;

  body_def.angularDamping = 0.5f;
  body_def.linearDamping = 0.5f;

  //shape definition
  b2PolygonShape polygonShape;
  polygonShape.SetAsBox(0.5, 0.5);  //a 1x1 m rectangle

  //fixture definition
  b2FixtureDef myFixtureDef;
  myFixtureDef.shape = &polygonShape;
  myFixtureDef.density = 0.5;  //pretty solid
  myFixtureDef.restitution = 0.1f;

  auto body(create_body_ptr(&body_def));

  body->CreateFixture(&myFixtureDef);

  body->SetUserData(&entity);  // to retrive entity from body in collisions

  // Assign all components to entity
  entity.assign<ClientInfo>(name, connection);
  entity.assign<DynamicBody>(std::move(body));
  entity.assign<Input>();
  entity.assign<Graphics>("player");
  entity.assign<Weapon>();
  entity.assign<Score>();
}

void EntityFactory::create_bullet(Entity entity,
                                  Entity::Id owner_id,
                                  const b2Vec2& position,
                                  const b2Vec2& velocity,
                                  float angle)
{
  float bullet_speed = 15.0f + velocity.Length();

  // Create the Box2D body
  b2BodyDef body_def;

  body_def.type = b2_dynamicBody;

  float r = angle * M_PI / 180.0;

  body_def.position.Set(position.x + cos(r), position.y + sin(r));

  body_def.angle = angle;

  body_def.linearVelocity.Set(cos(r) * bullet_speed, sin(r) * bullet_speed);

  body_def.fixedRotation = true;

  // what.... is this? Makes it doesnt collide with other bullets?
  body_def.bullet = true;

  auto body(create_body_ptr(&body_def));

  //shape definition
  b2PolygonShape polygonShape;

  polygonShape.SetAsBox(0.1, 0.1);

  //fixture definition
  b2FixtureDef fixture_def;

  fixture_def.shape = &polygonShape;

  fixture_def.density = 1;  // Solid

  body->CreateFixture(&fixture_def);

  body->SetUserData(&entity);  // to retrive entity from body in collisions

  entity.assign<Bullet>(owner_id, 5.0, 10.0);
  entity.assign<DynamicBody>(std::move(body));
  entity.assign<Graphics>("basic_green_bullet", 0.2, 0.2);
}

void EntityFactory::create_simple_asteroid(Entity entity,
                                           const b2Vec2& position,
                                           float diameter,
                                           float angle)
{
  // Create the Box2D body
  b2BodyDef body_def;

  body_def.type = b2_dynamicBody;

  body_def.position.Set(position.x, position.y);

  body_def.angle = angle;

  auto body(create_body_ptr(&body_def));

  //shape definition
  b2CircleShape circleShape;
  circleShape.m_p.Set(0, 0);            //position, relative to body position
  circleShape.m_radius = diameter / 2;  //radius

  //fixture definition
  b2FixtureDef fixture_def;

  fixture_def.shape = &circleShape;

  fixture_def.density = 1;  // Solid

  body->CreateFixture(&fixture_def);

  body->SetUserData(&entity);  // to retrive entity from body in collisions

  entity.assign<DynamicBody>(std::move(body));
  entity.assign<Graphics>("asteroid", diameter, diameter);

  std::cout << "Created asteroid" << std::endl;
}

void EntityFactory::create_border(Entity entity,
                                  const b2Vec2& from,
                                  const b2Vec2& to)
{
  // Create the Box2D body
  b2BodyDef body_def;

  body_def.type = b2_staticBody;
  body_def.position.Set(0, 0);

  auto body(create_body_ptr(&body_def));

  //shape definition
  b2EdgeShape shape;
  shape.Set(from, to);

  //fixture definition
  b2FixtureDef fixture_def;
  fixture_def.shape = &shape;
  fixture_def.density = 1;  // Solid

  body->CreateFixture(&fixture_def);

  body->SetUserData(&entity);  // to retrive entity from body in collisions

  entity.assign<DynamicBody>(std::move(body));

  std::cout << "Created border" << std::endl;
}

DynamicBody::BodyPtr EntityFactory::create_body_ptr(const b2BodyDef* def)
{
  DynamicBody::BodyPtr body(m_world.CreateBody(def), [](b2Body* b) {
    auto world = b->GetWorld();
    world->DestroyBody(b);
  });

  return body;
}
}  // namespace triangulum
