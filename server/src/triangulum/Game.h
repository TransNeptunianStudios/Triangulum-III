#ifndef _GAME_H
#define _GAME_H

#include "Box2D/Dynamics/b2World.h"

#include "entityx/Entity.h"
#include "entityx/Event.h"
#include "entityx/System.h"

#include "triangulum/EntityFactory.h"
#include "triangulum/network/Server.h"

struct b2Vec2;

namespace triangulum {

class Game
{
public:
  Game();

  ~Game();

  void init();

  void run();

  const std::string m_version;

private:
  void createSystems();

  void createWorld(const b2Vec2& size);

  void process_input();

  void update(double dt);

  void process_output();

  entityx::EventManager m_event_manager;

  entityx::EntityManager m_entity_manager;

  entityx::SystemManager m_system_manager;

  b2World m_world;

  network::Server m_server;

  EntityFactory m_entity_factory;
};

}  // namespace triangulum

#endif
