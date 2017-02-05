#ifndef _WORLD_SYSTEM_H
#define _WORLD_SYSTEM_H

#include "entityx/System.h"
#include "entityx/Event.h"

#include "Box2D/Common/b2Math.h"

#include "triangulum/EntityFactory.h"
#include "triangulum/SystemEvents.h"

class b2Vec;

namespace triangulum {
namespace system {

class WorldSystem : public entityx::System<WorldSystem>, public entityx::Receiver<CreateWorldEvent>
{
public:
  WorldSystem(EntityFactory &entity_factory, entityx::EntityManager& entities, entityx::EventManager& eventManager);

  void update(entityx::EntityManager &entities,
              entityx::EventManager &events,
              entityx::TimeDelta dt);

  void configure(entityx::EventManager &event_manager);

  void receive(const CreateWorldEvent &createWorld);


private:
  void createNewWorld(int sizeX, int sizeY);

  EntityFactory m_entity_factory;
  entityx::EntityManager& m_entity_manager;
  entityx::EventManager& m_eventManager;

};

}  // namespace system
}  // namespace triangulum

#endif
