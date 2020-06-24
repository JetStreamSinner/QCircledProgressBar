//
// Created by alex on 23.06.2020.
//

#include <QPainter>
#include <cmath>

#include "CircledProgressBar.h"

CircledProgressBar::CircledProgressBar(QWidget * parent) : QWidget(parent), _pieBrush(Qt::green)
{

}


void CircledProgressBar::resizeEvent(QResizeEvent * event)
{
    updateDrawPlaceholders();
}

void CircledProgressBar::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    renderOuterBar(&painter);
    renderInnerBar(&painter);
}

void CircledProgressBar::renderInnerBar(QPainter * painter)
{
    painter->save();
    QBrush alphaZeroBrush(QColor(0, 0, 0, 0));
    painter->setBrush(alphaZeroBrush);

    QFont font;
    font.setPixelSize(_innerCircleRadius / 2);
    painter->setFont(font);

    painter->drawEllipse(_innerRect);
    QString valueAsString = QString::number(static_cast<double>(_value) / _range * 100, 'g', 3);
    QString formattedString = valueAsString + "%";
    painter->drawText(_innerRect, Qt::AlignCenter, formattedString);
    painter->restore();
}

void CircledProgressBar::renderOuterBar(QPainter * painter)
{
    painter->save();

    QRegion innerCircle(_innerRect, QRegion::Ellipse);
    QRegion outerCircle(rect(), QRegion::Ellipse);
    QRegion drawingRegion = outerCircle - innerCircle;
    painter->setClipRegion(drawingRegion);

    const auto widgetRect = rect();
    auto outerRect = QRect(widgetRect.x() + 3, widgetRect.y() + 3,
            widgetRect.width() - 5, widgetRect.height() - 5);

    painter->setBrush(_pieBrush);

    int normalizedMax = _rangeMax - _rangeMin;
    int normalizedValue = _value - _rangeMin;

    double angleCoefficient = static_cast<double>(normalizedValue) / (normalizedMax ? normalizedMax : 1);

    int spanAngle = floor(-angleCoefficient * fullCircleDegrees);
    painter->drawPie(outerRect, startCountdownAngle, spanAngle);

    painter->setBrush(QBrush());
    painter->drawEllipse(outerRect);

    painter->restore();
}

void CircledProgressBar::setValue(int value)
{
    if (value < _rangeMin)
        value = _rangeMin;
    else if (value > _rangeMax)
        value = _rangeMax;
    else
        _value = value;
    emit valueChanged(_value);
}

int CircledProgressBar::value() const
{
    return _value;
}

void CircledProgressBar::setMin(int min)
{
    _rangeMin = min > _rangeMax ? _rangeMax : min;
    updateRange();
}

void CircledProgressBar::setMax(int max)
{
    _rangeMax = max < _rangeMin ? _rangeMin : max;
    updateRange();
}

void CircledProgressBar::setRange(int min, int max)
{
    setMin(min);
    setMax(max);
}

void CircledProgressBar::updateRange()
{
    _range = _rangeMax - _rangeMin;
    if (!_range)
        _range = 0;
}

void CircledProgressBar::updateDrawPlaceholders()
{
    const auto widgetWidth = width();
    const auto widgetHeight = height();

    const auto middleX = width() / 2;
    const auto middleY = height() / 2;

    _outerCircleRadius = sqrt(widgetWidth * widgetWidth + widgetHeight * widgetHeight) / 2;
    _innerCircleRadius = _outerCircleRadius / 2;

    _innerRect.setX(middleX - _innerCircleRadius);
    _innerRect.setY(middleY - _innerCircleRadius);
    _innerRect.setWidth(_outerCircleRadius);
    _innerRect.setHeight(_outerCircleRadius);
}