/**
 * @file application.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Tcalc GUI Application.
 * @version 0.2.0
 * @date 2025-06-26
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qapplication.h>

#include "tcalc_gui/calculator.hpp"

namespace tcalc_gui {

/**
 * @brief Tcalc GUI Application.
 *
 */
class Application : public QApplication
{
  Q_OBJECT

private:
  Calculator _calc;

public:
  /**
   * @brief Construct a new Application object.
   *
   * @param argc Number of arguments.
   * @param argv Arguments.
   */
  Application(int argc, char** argv);

  ~Application() override = default;
};

}
