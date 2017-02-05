#ifndef SCORE_SYSTEM_H
#define SCORE_SYSTEM_H

#include "entityx/System.h"
#include "entityx/Event.h"
#include "triangulum/SystemEvents.h"

namespace triangulum {
namespace system {

class ScoreSystem : public entityx::System<ScoreSystem>, public entityx::Receiver<ScoreEvent>
{
public:
  ScoreSystem(entityx::EventManager& eventManager);

  void update(entityx::EntityManager& entities, entityx::EventManager& events,
              entityx::TimeDelta dt);

  void configure(entityx::EventManager &event_manager);

  void receive(const ScoreEvent &scoreUpdate);

 private:
  entityx::EventManager& m_eventManager;

};

}  // namespace system
}  // namespace triangulum

#endif
