
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
, m_player_info_queue(10)
, m_input_queue(10)
, m_output_queue(100)
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
   web::WebServer server(m_player_info_queue,
                         m_input_queue,
                         m_output_queue);

   std::thread server_thread(&web::WebServer::run, &server);

   while (1)
   {
      m_system_manager.update_all(10.0); // TODO: Fix time step
   }
}

void Game::createSystems()
{
   using namespace system;

   m_system_manager.add<ConnectionSystem>(m_player_info_queue);
   m_system_manager.add<InputSystem>(m_input_queue);
   m_system_manager.configure();
}

} // namespace triangulum
