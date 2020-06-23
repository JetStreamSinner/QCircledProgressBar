//
// Created by alex on 23.06.2020.
//

#ifndef CIRCLEDPROGRESSBAR_CIRCLEDPROGRESSBAR_H
#define CIRCLEDPROGRESSBAR_CIRCLEDPROGRESSBAR_H

#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>


class CircledProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit CircledProgressBar(QWidget * parent = nullptr);

    void paintEvent(QPaintEvent * event) override;
    void resizeEvent(QResizeEvent * event) override;

    void setMin(int min);
    void setMax(int max);
    void setRange(int min, int max);

    void setValue(int value);
    int value() const;


private slots:
    void updateProgress();

private:

    QRect _innerRect;
    double outerCircleRadius;
    double innerCircleRadius;

    void updateDrawPlaceholders();
    void updateRange();

    void renderOuterBar(QPainter * painter);
    void renderInnerBar(QPainter * painter);

    int _value{};

    int _range{};
    int _rangeMin{};
    int _rangeMax{};

    const int fullCircleDegrees = 16 * 360;
    const int startCountdownAngle = 16 * 90;

    QBrush _pieBrush;
};


#endif //CIRCLEDPROGRESSBAR_CIRCLEDPROGRESSBAR_H
