
#include "triangulum/Game.h"

int main(int argc, char* argv[])
{
  triangulum::Game g;

  g.init();

  std::cout << "Triangulum III server started" << std::endl;

  g.run();

  return 0;
}
