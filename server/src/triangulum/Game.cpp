
#include "triangulum/Game.h"
#include "triangulum/system/InputSystem.h"

namespace triangulum {

Game::Game()
: m_eventManager()
, m_entityManager(m_eventManager)
, m_systemManager(m_entityManager, m_eventManager)
, m_webServer()
{
}

Game::~Game()
{
}

void Game::init()
{
   createSystems();

   m_webServer.init();
}

void Game::run()
{
   while (1)
   {
      m_webServer.process();
      m_systemManager.update_all(10.0); // TODO: Fix time step
   }
}

void Game::createSystems()
{
   using namespace system;

   m_systemManager.add<InputSystem>();
   m_systemManager.configure();
}

} // namespace triangulum
