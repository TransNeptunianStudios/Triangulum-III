#include "triangulum/component/Input.h"

namespace triangulum {
  namespace component {

    Input::Input()
      : thrust(false)
      , reverse(false)
      , strafe_left(false)
      , strafe_right(false)
      , turn_left(false)
      , turn_right(false)
      , fire(false)
      , spare(false)
    {
    }

  }  // namespace component
}  // namespace triangulum
