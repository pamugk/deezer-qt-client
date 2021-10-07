#ifndef ICAROUSEL_H
#define ICAROUSEL_H

#include <QLayout>

class ICarousel: public QLayout
{
    Q_OBJECT

public:
    explicit ICarousel(QWidget *parent = nullptr): QLayout(parent) {}
    virtual bool prev() = 0;
    virtual bool next() = 0;
};

#endif // ICAROUSEL_H
