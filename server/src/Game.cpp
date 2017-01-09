#include "Game.h"

Game::Game()
: m_eventManager()
, m_entityManager(m_eventManager)
, m_systemManager(m_entityManager, m_eventManager)
{
}

Game::~Game()
{
}
