#include "triangulum/system/ScoreSystem.h"
#include "triangulum/component/Score.h"

using namespace entityx;

namespace triangulum {
  namespace system {

    using namespace component;
  
    ScoreSystem::ScoreSystem(EventManager& eventManager)
      : m_eventManager(eventManager)
    {  
    }

    void ScoreSystem::update(EntityManager& entities,
			     EventManager& events,
			     TimeDelta dt)
    {
      // Basic score per second 
      entities.each<Score>(
			   [&dt](Entity entity, Score& score) {
			     score.score += dt;
			   });
    }

    void ScoreSystem::configure(entityx::EventManager &event_manager) {
      event_manager.subscribe<ScoreEvent>(*this);
    }

    void ScoreSystem::receive(const ScoreEvent &scoreUpdate) {
      std::cout << "New score: " + scoreUpdate.score + scoreUpdate.scoreInfo << std::endl;
    }

  }  // namespace system
}  // namespace triangulum
