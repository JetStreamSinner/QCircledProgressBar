//
// Created by alex on 23.06.2020.
//

#ifndef CIRCLEDPROGRESSBAR_CIRCLEDPROGRESSBAR_H
#define CIRCLEDPROGRESSBAR_CIRCLEDPROGRESSBAR_H

#include <QWidget>
#include <QPaintEvent>


class CircledProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit CircledProgressBar(QWidget * parent = nullptr);

    void paintEvent(QPaintEvent * event) override ;
private:
};


#endif //CIRCLEDPROGRESSBAR_CIRCLEDPROGRESSBAR_H
