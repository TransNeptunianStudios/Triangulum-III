
#include <thread>

#include "triangulum/Game.h"
#include "triangulum/system/ConnectionSystem.h"
#include "triangulum/system/InputSystem.h"
#include "triangulum/web/WebServer.h"

namespace triangulum {

Game::Game()
: m_event_manager()
, m_entity_manager(m_event_manager)
, m_system_manager(m_entity_manager, m_event_manager)
, m_msg_manager()
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
   web::WebServer server(m_msg_manager);

   while (1)
   {
      server.process_input();

      m_system_manager.update_all(10.0); // TODO: Fix time step

      server.process_output();
   }
}

void Game::createSystems()
{
   using namespace system;

   m_system_manager.add<ConnectionSystem>(m_msg_manager);
   m_system_manager.add<InputSystem>();
   m_system_manager.configure();
}

} // namespace triangulum
