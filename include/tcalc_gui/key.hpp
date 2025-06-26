/**
 * @file key.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Tcalc key button.
 * @version 0.2.0
 * @date 2025-06-26
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qpushbutton.h>

namespace tcalc_gui {

/**
 * @brief Tcalc key button.
 *
 */
class Key : public QPushButton
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new Key object.
   *
   * @param text Key text.
   * @param parent Parent widget.
   */
  Key(const QString& text, QWidget* parent = nullptr);

  ~Key() override = default;

signals:
  /**
   * @brief Emitted when the key is clicked.
   *
   * @param text Key text.
   */
  void key_clicked(const QString& text);

private slots:
  /**
   * @brief Handle the button clicked event.
   *
   */
  void _on_button_clicked();
};

}
