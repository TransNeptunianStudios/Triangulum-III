#ifndef SCORE_SYSTEM_H
#define SCORE_SYSTEM_H

#include "entityx/System.h"
#include "triangulum/SystemEvents.h"

namespace triangulum {
namespace system {

class ScoreSystem : public entityx::System<ScoreSystem>
{
public:
  ScoreSystem();

  void update(entityx::EntityManager& entities, entityx::EventManager& events,
              entityx::TimeDelta dt);

  void configure(entityx::EventManager &event_manager);

  void receive(const ScoreEvent &scoreUpdate);

};

}  // namespace system
}  // namespace triangulum

#endif
