#include "midisetup.h"
#include "mainwindow.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    qDebug() << argv[0] << "arguments:" << argc;

    MainWindow w;
    MidiSetup s;
  
    if (argc > 1) {
      w.show();
    } else {
      s.show();
    }

    return a.exec();
}
