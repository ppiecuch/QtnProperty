#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget * parent = 0, Qt::WindowFlags flags = 0 );
    virtual ~MainWindow();

protected Q_SLOTS:

protected:

private:
};

#endif // MAINWINDOW_H
