//
// Created by alex on 23.06.2020.
//

#include <QPainter>
#include <QDebug>
#include <cmath>
#include <QTimer>

#include "CircledProgressBar.h"

CircledProgressBar::CircledProgressBar(QWidget * parent) : QWidget(parent), _pieBrush(Qt::green)
{
    setFixedSize(400, 400);

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgress()));
    timer->start(500);
}

void CircledProgressBar::updateProgress()
{
    qDebug() << "Updated";
    setValue(value() + 1);
    update();
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
    painter->setBrush(Qt::red);
    const auto widgetWidth = width();
    const auto widgetHeight = height();

    const auto middleX = width() / 2;
    const auto middleY = height() / 2;

    const double outerCircleRadius = sqrt(widgetWidth * widgetWidth + widgetHeight * widgetHeight) / 2;
    const double innerCircleRadius = outerCircleRadius / 2;

    const int innerRectX = middleX - innerCircleRadius;
    const int innerRectY = middleY - innerCircleRadius;
    const int innerRectWidth = outerCircleRadius;
    const int innerRectHeight = outerCircleRadius;

    QFont font;
    font.setPixelSize(innerCircleRadius / 2);
    painter->setFont(font);

    painter->drawEllipse(innerRectX, innerRectY, innerRectWidth, innerRectHeight);

    QString formattedString = QString("%0%").arg(static_cast<double>(_value) / _range * 100);
    painter->drawText(innerRectX, innerRectY, innerRectWidth, innerRectHeight, Qt::AlignCenter, formattedString);
    painter->restore();
}

void CircledProgressBar::renderOuterBar(QPainter * painter)
{
    const auto widgetRect = rect();
    painter->setBrush(_pieBrush);

    int normalizedMax = _rangeMax - _rangeMin;
    int normalizedValue = _value - _rangeMin;

    double angleCoefficient = static_cast<double>(normalizedValue) / (normalizedMax ? normalizedMax : 1);

    int spanAngle = floor(-angleCoefficient * fullCircleDegrees);
    painter->drawPie(widgetRect, startCountdownAngle, spanAngle);

    painter->setBrush(QBrush());
    painter->drawEllipse(widgetRect);
}

void CircledProgressBar::setValue(int value)
{
    if (value < _rangeMin)
        value = _rangeMin;
    else if (value > _rangeMax)
        value = _rangeMax;
    else
        _value = value;
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