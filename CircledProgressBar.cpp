//
// Created by alex on 23.06.2020.
//

#include <QPainter>
#include "CircledProgressBar.h"

CircledProgressBar::CircledProgressBar(QWidget * parent)
{

}

void CircledProgressBar::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);

    // Widget rect
    const auto x = 0;
    const auto y = 0;
    const auto width = this->width();
    const auto height = this->height();

    painter.drawEllipse(x, y, width, height);
}