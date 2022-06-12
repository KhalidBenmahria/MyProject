#ifndef PARTITIONDETAISDIALOG_H
#define PARTITIONDETAISDIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

#include <QTreeWidgetItem>
#include <file.h>
#include <partition.h>
#include "fatpartition.h"
#include "disk.h"
#include "entrytreemodell.h"
#include "creatfiledialog.h"
#include "createfolderdialog.h"
#include "QMessageBox"

namespace Ui {

class PartitionDetaisDialog;
}
/**
 * @brief The PartitionDetaisDialog class represents a dialog which will be seen when the show details button is clicked
 */


class PartitionDetaisDialog : public QDialog
{
    Q_OBJECT



public:
    /**
     * @brief PartitionDetaisDialog Constructor
     * @param parent
     * @param partition
     */
    explicit PartitionDetaisDialog(QWidget *parent = nullptr, Partition* partition = nullptr);
    // Destructor
    ~PartitionDetaisDialog();

    // Setter and Getter

    const QStandardItemModel &model() const;
    void setModel(const QStandardItemModel &newModel);

private slots:

    /**
     * @brief addFillButtonClicked When the user the butten add File clicks, this slot will dispaly a CreatFileDialog
     * it checks whether the number of the file blocks  is larger than the free blocks of the partition. In the Case a warnung message box will be displayed
     * Than it checks whether the user enter the name, creator. If not a warning message box will be displayed.
     * A file is created depending on which partition type the user has selected.
     */
    void addFillButtonClicked();
    /**
     * @brief on_addFolderButton_clicked When the user the butten add folder clicks, this slot will dispaly a CreatFolderDialog
     * It checks if the user has enterd a folder name. In this case the dialog gets the name an creats a directory and adds this directory to the partition. Otherwise
     * a warning message box will be displayed
     */


    void on_addFolderButton_clicked();
    /**
     * @brief on_deleteButton_clicked When the user the butten delete clicks, this slot will dispaly a deleteDialog
     * This method gets the path of the entry from the dialog. It checks whether is the entry a file or directory using the compare methode
     * When the name of the entry ends with /, the entry is a directory, otherwise the entry is a file
     * At the end the entry will be deleted
     */

    void on_deleteButton_clicked();

private:
    Ui::PartitionDetaisDialog *ui;
    /**
     * @brief this method displays all the entries in the partition using the treeView
     * @param rootDirectory
     */
    void generateTreeView(Directory* rootDirectory);
    /**
     * @brief m_partition
     */
    Partition* m_partition;
    /**
     * @brief m_model
     */
    QStandardItemModel m_model;

};

#endif // PARTITIONDETAISDIALOG_H
