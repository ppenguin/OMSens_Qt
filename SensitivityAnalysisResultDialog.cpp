#include "SensitivityAnalysisResultDialog.h"

#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <TableItemDelegate.h>

SensitivityAnalysisResultDialog::SensitivityAnalysisResultDialog(QString filePath, QWidget *parent) : QDialog(parent)
{
    QStandardItemModel *csvModel = standardItemModelFromFilePath(filePath);
    initializeTableWithStandardItemModel(csvModel);
    configureLayout();
}

QStandardItemModel * SensitivityAnalysisResultDialog::standardItemModelFromFilePath(QString filePath)
{
    // Open file
    QFile file(filePath);
    file.open(QFile::ReadOnly | QFile::Text);
    // Create a thread to retrieve data from a file
    QTextStream in(&file);
    // Read first row into column names
    QString columnNamesLine = in.readLine();
    QList<QString> columnNames = columnNamesLine.split(",");
    int numberOfColumns = columnNames.length();
    // Create table from columns data
    QStandardItemModel *csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(numberOfColumns);
        csvModel->setHorizontalHeaderLabels(columnNames);
    // Read the rest of the lines. Each one will correspond to a parameter result
    while (!in.atEnd())
    {
        QString line = in.readLine();
        // Adding to the model in line with the elements
        QList<QStandardItem *> standardItemsList;
        // consider that the line separated by semicolons into columns
        QList<QString> cells = line.split(",");
        // Convert to double every number so the notation is consistent (the column sort is buggy otherwise)

        for (int i = 0; i < cells.length(); i++ ) {
            QString itemStr = cells[i];
            bool ok;
            double d;
            d = itemStr.toDouble(&ok); // ok == true, d == 12.3456
            QStandardItem *stdItem = new QStandardItem(itemStr);
            // Assign a numeric QVariant if it's numeric
            if(ok){
                // If it's a valid double
                stdItem->setData(QVariant(d),Qt::DisplayRole);
            }
            standardItemsList.append(stdItem);
        }
        csvModel->insertRow(csvModel->rowCount(), standardItemsList);
    }
    // Close file
    file.close();

    return csvModel;
}

void SensitivityAnalysisResultDialog::initializeTableWithStandardItemModel(QStandardItemModel *csvModel)
{
    mpResultsTable = new QTableView;
    mpResultsTable->setModel(csvModel);
    // Resize columns to contents
    mpResultsTable->resizeColumnsToContents();
    mpResultsTable->setSortingEnabled(true);
    // Set item delegate to format doubles in specified precision
    TableItemDelegate *decDelegate = new TableItemDelegate;
    mpResultsTable->setItemDelegate(decDelegate);
}

void SensitivityAnalysisResultDialog::configureLayout()
{
    // New layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    // Assign table view to layout
    mainLayout->addWidget(mpResultsTable);
    // Set Dialog layout
    setLayout(mainLayout);
}

