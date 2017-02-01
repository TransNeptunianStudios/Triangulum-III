#ifndef _SCORE_H
#define _SCORE_H

#include "entityx/Entity.h"

namespace triangulum {
namespace component {

 // Pretty pointless component, move into something bigger? Clientinfo? 
struct Score : public entityx::Component<Score>
{
  Score();

  float score;
};

}  // namespace component
}  // namespace triangulum

#endif
