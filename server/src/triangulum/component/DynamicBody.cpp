#include "triangulum/component/DynamicBody.h"

namespace triangulum {
namespace component {

DynamicBody::DynamicBody(BodyPtr body_)
   : body(std::move(body_))
{
}

} // namespace component
} // namespace triangulum
