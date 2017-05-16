
#ifndef MIDISETUP_H
#define MIDISETUP_H

#include "ui_midisetup.h"
#include <QDialog>

class MidiSetup : public QDialog
{
    Q_OBJECT

public:
    MidiSetup(QWidget *parent = 0);
    void inputNotAvailable();
    bool inputIsEnabled() const;
    bool thruIsEnabled() const;
    bool omniIsEnabled() const;
    void setInputEnabled(const bool state);
    void setThruEnabled(const bool state);
    void setOmniEnabled(const bool state);
    void clearCombos();
    void addInputPortName(const QString& name, int index);
    void addOutputPortName(const QString& output, int index);
    void setCurrentInput(int index);
    void setCurrentInput(const QString name);
    void setCurrentOutput(int index);
    void setCurrentOutput(const QString name);
    int  selectedInput();
    int  selectedOutput();
    QString selectedInputName() const;
    QString selectedOutputName() const;
    void retranslateUi();

public slots:
    void toggledInput(bool state);

private:
    Ui::MidiSetupClass ui;
};

#endif /* MIDISETUP_H */
