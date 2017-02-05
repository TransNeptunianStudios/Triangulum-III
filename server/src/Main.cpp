
#include "triangulum/Game.h"

int main(int argc, char* argv[])
{
  triangulum::Game g;

  std::cout << "Triangulum III server (v. " <<  g.m_version << ") started" << std::endl;

  g.init();

  g.run();

  return 0;
}
