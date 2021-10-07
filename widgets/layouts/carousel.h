#ifndef CAROUSEL_H
#define CAROUSEL_H

#include "icarousel.h"

#include <QStyle>
#include <QVector>
#include <QWidget>

template<typename T>
class CarouselLayout: public ICarousel
{
private:
    QList<QLayoutItem*> items;
    int hSpacing;
    int leftmostItem;
    int visibleItemsCount;

    void doLayout(const QRect &rect)
    {
        int left, top, right, bottom;
        getContentsMargins(&left, &top, &right, &bottom);
        QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
        int x = effectiveRect.x();
        const int y = effectiveRect.y();
        int lineHeight = 0;

        int i;
        for (i = 0; i < leftmostItem; i++)
        {
            items[i]->widget()->hide();
        }

        for (i = i; i < items.size(); i++)
        {
            const auto item = items[i];
            const QWidget *wid = items[i]->widget();

            int spaceX = horizontalSpacing();
            if (spaceX == -1)
                spaceX = wid->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);

            int nextX = x + item->sizeHint().width() + spaceX;
            if (nextX - spaceX > effectiveRect.right() && lineHeight > 0)
            {
                break;
            }

            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

            x = nextX;
            lineHeight = qMax(lineHeight, item->sizeHint().height());
        }

        visibleItemsCount = i - leftmostItem;
        for (i = i; i < items.size(); i++)
        {
            items[i]->widget()->hide();
        }
    }

    int smartSpacing(QStyle::PixelMetric pm) const
    {
        QObject *parent = this->parent();
        if (parent == nullptr)
        {
            return -1;
        } else if (parent->isWidgetType())
        {
            QWidget *pw = static_cast<QWidget *>(parent);
            return pw->style()->pixelMetric(pm, nullptr, pw);
        } else
        {
            return static_cast<QLayout *>(parent)->spacing();
        }
    }

protected:
    virtual QWidget* instantiateItem(T &obj) = 0;

public:
    explicit CarouselLayout(QWidget *parent = nullptr, int margin = -1, int hSpacing = -1):
        ICarousel(parent), hSpacing(hSpacing), leftmostItem(0)
    {
        setContentsMargins(margin, margin, margin, margin);
    }

    ~CarouselLayout()
    {
        while (items.count() > 0)
            delete takeAt(0);
    }

    void addData(QVector<T> &data)
    {
        for (T obj: data)
        {
            addWidget(instantiateItem(obj));
        }
    }

    void addItem(QLayoutItem *item) override
    {
        items.append(item);
    }

    int count() const override
    {
        return items.count();
    }

    Qt::Orientations expandingDirections() const override
    {
        return Qt::Horizontal;
    }

    bool hasHeightForWidth() const override
    {
        return true;
    }

    int heightForWidth(int width) const override
    {
        int lineHeight = 0;
        int takenWidth = 0;
        for (int i = leftmostItem; i < items.size(); i++)
        {

            const auto item = items[i];
            const QWidget *wid = items[i]->widget();

            int spaceX = horizontalSpacing();
            if (spaceX == -1)
                spaceX = wid->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);

            int nextX = takenWidth + item->sizeHint().width() + spaceX;
            if (nextX - spaceX > width && lineHeight > 0)
            {
                break;
            }

            takenWidth = nextX;
            lineHeight = qMax(lineHeight, item->sizeHint().height());
        }

        return lineHeight;
    }

    int horizontalSpacing() const
    {
        return hSpacing < 0 ?
                    smartSpacing(QStyle::PM_LayoutHorizontalSpacing) :
                    hSpacing;
    }

    bool isEmpty() const override
    {
        return items.count() == 0;
    }

    QLayoutItem *itemAt(int index) const override
    {
        return index >= 0 && index < items.size() ?
                    items.at(index) :
                    nullptr;
    }

    QSize minimumSize() const override
    {
        const QMargins margins = contentsMargins();
        return items[leftmostItem]->minimumSize() + QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
    }

    void setGeometry(const QRect &rect) override
    {
        QLayout::setGeometry(rect);
        doLayout(rect);
    }

    QSize sizeHint() const override
    {
        return minimumSize();
    }

    QLayoutItem *takeAt(int index) override
    {
        return index >= 0 && index < items.size() ?
                    items.takeAt(index) :
                    nullptr;
    }

    bool prev() override
    {
        leftmostItem = qMax(leftmostItem - visibleItemsCount, 0);
        return leftmostItem == 0;
    }

    bool next() override
    {
        leftmostItem = qMin(leftmostItem + visibleItemsCount, items.size() - 1);
        return leftmostItem + visibleItemsCount < items.size();
    }
};

#endif // CAROUSEL_H
