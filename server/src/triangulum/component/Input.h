#ifndef _INPUT_H
#define _INPUT_H

#include "entityx/Entity.h"

namespace triangulum{
namespace component {
  
struct Input : public entityx::Component<Input>
{
  Input();

  bool thrust;
  bool reverse;
  
  bool strafe_left;
  bool strafe_right;
  
  bool turn_left;
  bool turn_right;

  bool fire;
  bool spare;

};

}  // namespace component
}  // namespace triangulum

#endif
