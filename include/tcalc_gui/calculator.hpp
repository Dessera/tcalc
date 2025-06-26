/**
 * @file calculator.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Calculator widget.
 * @version 0.1.0
 * @date 2025-06-26
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qlabel.h>
#include <qlineedit.h>
#include <qwidget.h>
#include <tcalc/eval.hpp>

#include "tcalc_gui/keyboard.hpp"

namespace tcalc_gui {

/**
 * @brief Calculator widget.
 *
 */
class Calculator : public QWidget
{
  Q_OBJECT

private:
  QLineEdit* _line_edit;
  QLabel* _label;
  Keyboard* _keyboard;

  tcalc::Evaluator _evaluator;

public:
  /**
   * @brief Construct a new Calculator object.
   *
   * @param parent Parent widget.
   */
  explicit Calculator(QWidget* parent = nullptr);

  ~Calculator() override = default;

private:
  /**
   * @brief Insert a key to the input text.
   *
   * @param key Key to insert.
   */
  void _update_input_text(const QString& key);

  /**
   * @brief Move the input cursor.
   *
   * @param offset Offset to move.
   */
  void _move_input_cursor(int offset);

  /**
   * @brief Evaluate the input text.
   *
   */
  void _evaluate();

private slots: // NOLINT
  /**
   * @brief Handle key clicked event.
   *
   * @param key Key clicked.
   */
  void _on_key_clicked(const QString& key);
};

}
