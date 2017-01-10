
#include "triangulum/system/InputSystem.h"

using namespace entityx;

namespace triangulum {
namespace system {

InputSystem::InputSystem()
{
}

void InputSystem::update(EntityManager& entities,
                         EventManager& events,
                         TimeDelta dt)
{
   std::cout << "Updated!\n";
}

} // namespace system
} // namespace triangulum
