#include <algorithm>
#include <qboxlayout.h>
#include <qlineedit.h>

#include "tcalc_gui/calculator.hpp"
#include "tcalc_gui/keyboard.hpp"

namespace tcalc_gui {

Calculator::Calculator(QWidget* parent)
  : QWidget{ parent }
  , _line_edit{ new QLineEdit{ this } }
  , _label{ new QLabel{ this } }
  , _keyboard{ new Keyboard{ this } }
{
  auto* layout = new QVBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(_line_edit);
  layout->addWidget(_label);
  layout->addWidget(_keyboard);

  connect(
    _keyboard, &Keyboard::key_clicked, this, &Calculator::_on_key_clicked);
}

void
Calculator::_update_input_text(const QString& key)
{
  auto text = _line_edit->text();
  auto cursor = _line_edit->cursorPosition();

  text.insert(cursor, key);
  _line_edit->setText(text);

  cursor += static_cast<int>(key.size());
  _line_edit->setCursorPosition(cursor);
}

void
Calculator::_move_input_cursor(int offset)
{
  const auto& text = _line_edit->text();
  auto cursor = _line_edit->cursorPosition();

  cursor += offset;
  cursor = std::max(cursor, 0);
  cursor = std::min(cursor, static_cast<int>(text.size()));

  _line_edit->setCursorPosition(cursor);
}

void
Calculator::_evaluate()
{
  auto text_bytes = _line_edit->text().toLocal8Bit();
  auto* text_ptr = text_bytes.data();

  auto res = _evaluator.eval(text_ptr);
  if (res.has_value()) {
    _label->setText(QString::number(res.value()));
    _line_edit->clear();
  } else {
    _label->setText(QString::fromStdString(res.error().msg()));
  }
}

void
Calculator::_on_key_clicked(const QString& key)
{
  const auto& text = _line_edit->text();

  if (key == "C") {
    _line_edit->clear();
  } else if (key == "DEL") {
    _line_edit->backspace();
  } else if (key == "<") {
    _move_input_cursor(-1);
  } else if (key == ">") {
    _move_input_cursor(1);
  } else if (key == "=") {
    _evaluate();
  } else {
    _update_input_text(key);
  }
}

}
