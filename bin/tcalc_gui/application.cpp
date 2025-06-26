#include "tcalc_gui/application.hpp"

namespace tcalc_gui {

Application::Application(int argc, char** argv)
  : QApplication{ argc, argv }
{
  _calc.show();
}

}
