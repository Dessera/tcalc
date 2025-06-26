#include "tcalc_gui/application.hpp"

int
main(int argc, char** argv)
{
  using tcalc_gui::Application;

  auto app = Application{ argc, argv };
  return Application::exec();
}
