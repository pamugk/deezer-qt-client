#ifndef PLAYLISTFLOW_H
#define PLAYLISTFLOW_H

#include "../api/deezer.h"

#include "playlistcard.h"

#include <QLayoutItem>
#include <QScrollArea>

namespace Ui {
class PlaylistFlow;
}

class PlaylistFlow : public QScrollArea
{
    Q_OBJECT

public:
    explicit PlaylistFlow(api::Deezer *apiInstance, QWidget *parent = nullptr);
    ~PlaylistFlow();
    void addContents(QVector<api::Playlist>&);
    void clearAll();

signals:
    void clickedItem(int id);

private:
    int lastContentIndex;
    Ui::PlaylistFlow *ui;

    api::Deezer *apiInstance;
};

#endif // PLAYLISTFLOW_H
