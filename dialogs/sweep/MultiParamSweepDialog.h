#ifndef MULTIPARAMSWEEPDIALOG_H
#define MULTIPARAMSWEEPDIALOG_H


#include <QDialog>
#include <QDoubleSpinBox>
#include <QFrame>
#include <QGridLayout>
#include <QTableWidget>
#include <QDialogButtonBox>
#include <QJsonObject>
#include <QString>
#include "OMSens/tabs/SimulationTab.h"
#include "OMSens/tabs/VariablesTab.h"
#include "OMSens/tabs/ParametersExtendedTab.h"
#include "OMSens/tabs/HelpTab.h"
#include "OMSens/DualLists.h"
#include "OMSens/model.h"

class MultiParamSweepDialog : public QDialog
{
    Q_OBJECT
public:
    MultiParamSweepDialog(Model model, QWidget *pParent = 0);

    // Getters
    QJsonObject getRunSpecifications() const;
    QString getDestFolderPath() const;

private:
    void initializeDialogWithData(QList<QString> variables, QList<QString> parameters, QString modelName, QString modelFilePath, double percentage, double startTime, double stopTime);
    // GUI members
    QTabWidget            *mpTabWidget;
    SimulationTab         *mpSimulationSettingsTab;
    VariablesTab          *mpVariablesTab;
    ParametersExtendedTab *mpParametersTab;
    HelpTab               *mpHelpTab;
    QDialogButtonBox    *mpButtonBox;
    // Dialog "return" members
    QJsonObject mRunSpecifications;
    QString     mpDestFolderPath;

    // Auxs:
    void initializeWindowSettings();

private slots:
    void runMultiParamSweep();
};

#endif // MULTIPARAMSWEEPDIALOG_H