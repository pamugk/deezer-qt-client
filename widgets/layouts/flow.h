#ifndef FLOW_H
#define FLOW_H

#include <QLayout>
#include <QStyle>
#include <QVector>
#include <QWidget>

template<typename T>
class Flow: public QLayout
{
private:
    QList<QLayoutItem*> items;
    int hSpacing;
    int vSpacing;

    int doLayout(const QRect &rect, bool updateGeometry) const
    {
        int left, top, right, bottom;
        getContentsMargins(&left, &top, &right, &bottom);
        QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
        int x = effectiveRect.x();
        int y = effectiveRect.y();
        int lineHeight = 0;

        for (QLayoutItem *item: qAsConst(items))
        {
            const QWidget *wid = item->widget();

            int spaceX = horizontalSpacing();
            if (spaceX == -1)
                spaceX = wid->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);

            int spaceY = verticalSpacing();
            if (spaceY == -1)
                spaceY = wid->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);

            int nextX = x + item->sizeHint().width() + spaceX;
            if (nextX - spaceX > effectiveRect.right() && lineHeight > 0)
            {
                x = effectiveRect.x();
                y = y + lineHeight + spaceY;
                nextX = x + item->sizeHint().width() + spaceX;
                lineHeight = 0;
            }

            if (updateGeometry)
            {
                item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));
            }

            x = nextX;
            lineHeight = qMax(lineHeight, item->sizeHint().height());
        }
        return y + lineHeight - rect.y() + bottom;
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
    virtual QWidget* instantiateItem(T &item) = 0;

public:
    Flow(QWidget *parent = nullptr, int margin = -1, int hSpacing = -1, int vSpacing = -1):
        QLayout(parent), hSpacing(hSpacing), vSpacing(vSpacing)
    {
        setContentsMargins(margin, margin, margin, margin);
    }

    ~Flow()
    {
        clearAll();
    }

    void addItem(QLayoutItem *item) override
    {
        items.append(item);
    }

    void addContents(QVector<T> &data)
    {
        for (T obj: data)
        {
            addWidget(instantiateItem(obj));
        }
    }

    void clearAll()
    {
        while (items.count() > 0)
            delete takeAt(0);
    }

    int count() const override
    {
        return items.count();
    }

    Qt::Orientations expandingDirections() const override
    {
        return {};
    }

    bool hasHeightForWidth() const override
    {
        return true;
    }

    int heightForWidth(int width) const override
    {
        return doLayout(QRect(0, 0, width, 0), false);
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
        QSize size;
        for (const QLayoutItem *item : qAsConst(items))
            size = size.expandedTo(item->minimumSize());

        const QMargins margins = contentsMargins();
        size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
        return size;
    }

    void setGeometry(const QRect &rect) override
    {
        QLayout::setGeometry(rect);
        doLayout(rect, true);
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

    int verticalSpacing() const
    {
        return vSpacing < 0 ?
                    smartSpacing(QStyle::PM_LayoutHorizontalSpacing) :
                    vSpacing;
    }
};

#endif // FLOW_H
