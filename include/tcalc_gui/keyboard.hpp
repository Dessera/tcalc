/**
 * @file keyboard.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Tcalc GUI keyboard.
 * @version 0.1.0
 * @date 2025-06-26
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qlist.h>
#include <qwidget.h>

namespace tcalc_gui {

/**
 * @brief Tcalc GUI keyboard.
 *
 */
class Keyboard : public QWidget
{
  Q_OBJECT

public:
  inline static const QList<QPair<QString, QPoint>> KEYMAP = {
    { "B", { 0, 0 } },    { "F", { 1, 0 } },    { "log", { 2, 0 } },
    { "exp", { 3, 0 } },  { "sqrt", { 4, 0 } }, { "pow", { 5, 0 } },
    { "sin", { 0, 1 } },  { "cos", { 1, 1 } },  { "tan", { 2, 1 } },
    { "asin", { 3, 1 } }, { "acos", { 4, 1 } }, { "atan", { 5, 1 } },
    { "1", { 0, 2 } },    { "2", { 1, 2 } },    { "3", { 2, 2 } },
    { "+", { 3, 2 } },    { "C", { 4, 2 } },    { "DEL", { 5, 2 } },
    { "4", { 0, 3 } },    { "5", { 1, 3 } },    { "6", { 2, 3 } },
    { "-", { 3, 3 } },    { "(", { 4, 3 } },    { ")", { 5, 3 } },
    { "7", { 0, 4 } },    { "8", { 1, 4 } },    { "9", { 2, 4 } },
    { "*", { 3, 4 } },    { "pi", { 4, 4 } },   { "e", { 5, 4 } },
    { ".", { 0, 5 } },    { "0", { 1, 5 } },    { "=", { 2, 5 } },
    { "/", { 3, 5 } },    { "ans", { 4, 5 } }
  }; /**< Keyboard keymap. */

  /**
   * @brief Construct a new Keyboard object.
   *
   * @param parent Parent widget.
   */
  explicit Keyboard(QWidget* parent = nullptr);

  ~Keyboard() override = default;

signals:
  /**
   * @brief Emitted when a key is clicked.
   *
   * @param key Key name.
   */
  void key_clicked(const QString& key);
};

}
