#ifndef _DYNAMIC_BODY_H
#define _DYNAMIC_BODY_H

#include "entityx/Entity.h"

class b2Body;

namespace triangulum {
namespace component {

struct DynamicBody : public entityx::Component<DynamicBody>
{
   using BodyPtr = std::unique_ptr<b2Body, std::function<void(b2Body*)>>;

   DynamicBody(BodyPtr body_);

   BodyPtr body;
};

} // namespace component
} // namespace triangulum

#endif
