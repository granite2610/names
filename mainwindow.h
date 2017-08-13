/*
 * Controls the main window of the names program.
 * Sends and receives data to various widgets on screen.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSettings>

#include "nameshuffler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void computeSlot();
    void changeHistory();

private:
    Ui::MainWindow *ui;
    QString input;
    const QString name = "Name";
    QSettings* settings;
};

#endif // MAINWINDOW_H
