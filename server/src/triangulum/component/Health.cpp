#include "triangulum/component/Health.h"

namespace triangulum {
namespace component {

Health::Health()
: health(100.0)
{
}

Health::Health(float health_)
: health(health_)
{
}

}  // namespace component
}  // namespace triangulum
