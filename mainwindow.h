#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "api/deezer.h"

#include "pages/mainpage.h"
#include "pages/searchpage.h"

#include <QMainWindow>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_searchLineEdit_textChanged(const QString &arg1);

    void on_clearSearchButton_clicked();

    void on_searchLineEdit_editingFinished();

    void on_searchButton_clicked();

private:
    QSystemTrayIcon *trayIcon;
    Ui::MainWindow *ui;

    MainPage *mainPage;
    SearchPage *searchPage;
    api::Deezer* deezerApiInstance;
};
#endif // MAINWINDOW_H
