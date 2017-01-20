#include "triangulum/Game.h"
#include <chrono>
#include "Box2D/Common/b2Math.h"
#include "triangulum/system/ConnectionSystem.h"
#include "triangulum/system/InputSystem.h"
#include "triangulum/system/OutputSystem.h"
#include "triangulum/system/SimulationSystem.h"

namespace triangulum {

using namespace system;

Game::Game()
: m_event_manager()
, m_entity_manager(m_event_manager)
, m_system_manager(m_entity_manager, m_event_manager)
, m_world(b2Vec2(0.0f, 0.0f))
, m_server()
, m_entity_factory(m_world)
{
}

Game::~Game()
{
}

void Game::init()
{
  createSystems();
}

void Game::run()
{
  using clock = std::chrono::high_resolution_clock;

  std::chrono::nanoseconds time_step_ns(std::chrono::milliseconds(16));

  std::chrono::duration<double> time_step_s(time_step_ns);

  std::chrono::nanoseconds lag(0);

  auto current_time = clock::now();

  while (1)
  {
    auto delta_time = clock::now() - current_time;

    current_time = clock::now();

    lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

    process_input();

    while (lag >= time_step_ns)
    {
      lag -= time_step_ns;

      update(time_step_s.count());
    }

    process_output();
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

void Game::process_input()
{
  m_server.process_input();

  m_system_manager.update<ConnectionSystem>(0.0);

  m_system_manager.update<InputSystem>(0.0);
}

void Game::update(double dt)
{
  m_system_manager.update<SimulationSystem>(dt);
}

void Game::process_output()
{
  m_system_manager.update<OutputSystem>(0.0);
}

}  // namespace triangulum
