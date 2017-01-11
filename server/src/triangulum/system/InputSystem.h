#ifndef _INPUT_SYSTEM_H
#define _INPUT_SYSTEM_H

#include "entityx/System.h"

#include "moodycamel/readerwriterqueue.h"

namespace triangulum {
namespace system {

class InputSystem : public entityx::System<InputSystem>
{
public:
   InputSystem(moodycamel::ReaderWriterQueue<int>& input_queue);

   void update(entityx::EntityManager &entities,
               entityx::EventManager &events,
               entityx::TimeDelta dt);
private:
   moodycamel::ReaderWriterQueue<int>& m_input_queue;
};

} // namespace system
} // namespace triangulum

#endif
