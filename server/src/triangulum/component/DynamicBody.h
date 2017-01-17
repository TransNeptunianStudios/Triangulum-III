#ifndef _DYNAMIC_BODY_H
#define _DYNAMIC_BODY_H

#include "entityx/Entity.h"

class b2Body;

namespace triangulum {
namespace component {

struct DynamicBody : public entityx::Component<DynamicBody>
{
   DynamicBody(b2Body* body_);

   b2Body* body;
};

} // namespace component
} // namespace triangulum

#endif
