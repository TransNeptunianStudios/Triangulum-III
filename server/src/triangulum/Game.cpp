
#include <thread>

#include "triangulum/Game.h"
#include "triangulum/system/ConnectionSystem.h"
#include "triangulum/system/InputSystem.h"

namespace triangulum {

Game::Game()
: m_event_manager()
, m_entity_manager(m_event_manager)
, m_system_manager(m_entity_manager, m_event_manager)
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
   while (1)
   {
      m_system_manager.update_all(10.0); // TODO: Fix time step
   }
}

void Game::createSystems()
{
   using namespace system;

   m_system_manager.add<ConnectionSystem>();
   m_system_manager.add<InputSystem>();
   m_system_manager.configure();
}

} // namespace triangulum
