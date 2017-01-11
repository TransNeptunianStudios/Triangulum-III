
#include "triangulum/system/InputSystem.h"

using namespace entityx;

namespace triangulum {
namespace system {

InputSystem::InputSystem(moodycamel::ReaderWriterQueue<int>& input_queue)
: m_input_queue(input_queue)
{
}

void InputSystem::update(EntityManager& entities,
                         EventManager& events,
                         TimeDelta dt)
{
}

} // namespace system
} // namespace triangulum
