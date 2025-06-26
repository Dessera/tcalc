#include "tcalc_gui/key.hpp"

namespace tcalc_gui {

Key::Key(const QString& text, QWidget* parent)
  : QPushButton{ text, parent }
{
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  connect(this, &QPushButton::clicked, this, &Key::_on_button_clicked);
}

void
Key::_on_button_clicked()
{
  const auto& text = this->text();
  emit key_clicked(text);
}

}
