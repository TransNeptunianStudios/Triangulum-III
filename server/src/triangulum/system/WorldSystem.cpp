#include "triangulum/system/WorldSystem.h"
#include "triangulum/EntityFactory.h"

using namespace entityx;

namespace triangulum {
namespace system {


  WorldSystem::WorldSystem(EntityFactory &entity_factory, entityx::EntityManager& entities, entityx::EventManager& eventManager)
: m_entity_factory(entity_factory)
, m_entity_manager(entities)
, m_eventManager(eventManager)
{
  createNewWorld(50, 50); // where should this come from? 
}

void WorldSystem::createNewWorld(int sizeX, int sizeY)
{
  std::cout << "CREATES NEW WORLD!" << std::endl;

  // creates border walls  
  m_entity_factory.create_border(m_entity_manager.create(), b2Vec2(0, 0), b2Vec2(sizeX, 0));
  m_entity_factory.create_border(m_entity_manager.create(), b2Vec2(sizeX, 0), b2Vec2(sizeX, sizeY));
  m_entity_factory.create_border(m_entity_manager.create(), b2Vec2(sizeX, sizeY), b2Vec2(0, sizeY));
  m_entity_factory.create_border(m_entity_manager.create(), b2Vec2(0, sizeY), b2Vec2(0, 0));
  
  // creates asteroids
  for(int i = 0; i < 30; ++i)  {
    // should check for overlaps as well...
    auto entity = m_entity_manager.create();

    float x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / sizeX));
    float y = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / sizeY));
    float r = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 360));
    float s = 0.5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));

    m_entity_factory.create_simple_asteroid(entity, b2Vec2(x, y), s, r);
  }
}

void WorldSystem::update(entityx::EntityManager& entities,
                          entityx::EventManager& events,
                          entityx::TimeDelta dt)
{
}

void WorldSystem::configure(entityx::EventManager &event_manager)
{
  event_manager.subscribe<CreateWorldEvent>(*this);
}

void WorldSystem::receive(const CreateWorldEvent &createWorld)
{
  createNewWorld(createWorld.sizeX, createWorld.sizeY);
}


}  // namespace system
}  // namespace triangulum
