#include <qgridlayout.h>
#include <qpushbutton.h>

#include "tcalc_gui/key.hpp"
#include "tcalc_gui/keyboard.hpp"

namespace tcalc_gui {

Keyboard::Keyboard(QWidget* parent)
  : QWidget{ parent }
{
  auto* layout = new QGridLayout{ this };
  setLayout(layout);

  for (const auto& keydef : KEYMAP) {
    auto* key = new Key{ keydef.first, this };
    connect(key, &Key::key_clicked, this, &Keyboard::key_clicked);

    layout->addWidget(key, keydef.second.y(), keydef.second.x());
  }
}

}
