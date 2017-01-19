#include "triangulum/Game.h"
#include "Box2D/Common/b2Math.h"
#include "triangulum/system/ConnectionSystem.h"
#include "triangulum/system/InputSystem.h"
#include "triangulum/system/OutputSystem.h"
#include "triangulum/system/SimulationSystem.h"

namespace triangulum {

Game::Game()
: m_event_manager()
, m_entity_manager(m_event_manager)
, m_system_manager(m_entity_manager, m_event_manager)
, m_world(b2Vec2(0.0f, 0.0f))
, m_server()
, m_entity_factory(m_world)
{
}

Game::~Game() {}

void Game::init() { createSystems(); }

void Game::run()
{
  while (1)
  {
    m_server.process_input();

    m_system_manager.update_all(10.0);  // TODO: Fix time step
  }
}

void Game::createSystems()
{
  using namespace system;

  m_system_manager.add<ConnectionSystem>(m_server.get_connection_mgr(),
                                         m_entity_factory);
  m_system_manager.add<InputSystem>();
  m_system_manager.add<SimulationSystem>(m_world);
  m_system_manager.add<OutputSystem>();
  m_system_manager.configure();
}

}  // namespace triangulum
