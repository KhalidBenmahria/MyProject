#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

#include <festplatteerstellendialog.h>

#include <partition.h>
#include <disk.h>

#include <QDebug>
#include <QDialog>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    /**
     * @brief createDiskTriggered it is a slot. It will first check if there is already a disk, because only one disk can be created.
     * if there is no other disk, the new disk will be created with the values enterd by the user and the gui will be updated depending on these new values. Otherwise warning dialog will be seen
     * @param diskSize
     */
    void createDiskTriggered();
    /**
     * @brief deleteDiskTriggered. This slot will be called when the user delets a disk .It checks if there is a disk to delete. If there is no one a warning Messege box will be seen. Otherwise the disk will be deleted and if it has a partition, they will be first deleted and than the disk
    */

    void deleteDiskTriggered();
    /**
     * @brief MainWindow::createPartitionTriggered Slot will be called when the user creats a partition. It checks if there is a disk and if the number of the partitions is 2.
     * in this case, a warning message box will be seen. Otherwise a new partition will be creates with the values enters by the user
     */

    void createPartitionTriggered();
    /**
     * @brief sample1Triggered This slot generete testing samples
     */

    void sample1Triggered();
    /**
     * @brief writeCDtriggered. This slot will be called when the user writes a cd from a partition. It checks if there is disk or a partition. If there is no disk or no partition the warning message box will be displyed. Otherwise the WriteCdDialog will be displayed
     */

    void writeCDtriggered();
    /**
     * @brief readCDtriggered. This slot will be called when the user reads a cd. The user can select a cd on his compuer and copy it to the disk
     */

    void readCDtriggered();
    /**
     * @brief generateDisk this method generets the disk gui. At beginn the column of the table will be generted and than the m_disk will be initialized. At the end the gui will be updates with the new information
     * @param diskSize
     */
    void generateDisk(int diskSize);

    /**
     * @brief generatePartition. This method checks if the added partition the first or the decond in the disk. Depending on which partition is this, a new partition gui will be created.
     * Than The Columns (number of blocks) of this Partition will be generated with the given partitionSize and blockSize. At the end the partition will be added to the disk and the disk will be updated
     * @param name
     * @param partitionSize
     * @param blockSize
     * @param type
     * @param status
     */

    void generatePartition(QString name, int partitionSize, int blockSize, int type, bool status);

    /**
     * @brief removePartitionTriggered. This slot will be calles when the user removes a partition. It checks if there is already a disk or a partition. If there is no disk or no partition to delete the warning messagebox will be displayed. Than the Partition will be deleted from the disk. At the end the gui will be updated
     */

    void removePartitionTriggered();

    /**
     * @brief on_showDetailsButton_partition1_clicked. This slot will be calles when the user clickes the show details button of the first partition
     */

    void on_showDetailsButton_partition1_clicked();
    /**
     * @brief on_showDetailsPartition2Button_clicked. This slot will be calles when the user clickes the show details button of the second partition
     */

    void on_showDetailsPartition2Button_clicked();

    void defragPartition1();
    void defragPartition2();

public:
    /**
     * @brief updateGUI checks if a disk exists or partition. if yes, it gets the information from the instance and makes the gui depending on the information. Otherwise it will display the default values.
     */
    void updateGUI();

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupTable(QTableWidget* table);
    /**
     * @brief generateColums. This method sets the number of the columns and rows of the table.
     * @param table
     * @param blockNumber
     */
    void generateColums(QTableWidget* table, int blockNumber);

private:
    Ui::MainWindow *ui;
    /**
     * @brief a table which is used to view the disk on the gui
     */

    QTableWidget* m_diskTable;
    /**
     * @briefa table which is used to view the first partition on the gui
     */
    QTableWidget* m_partition1Table;
    /**
     * @brief a table which is used to view the second partition on the gui
     */
    QTableWidget* m_partition2Table;
    /**
     * @brief m_disk
     */

    Disk* m_disk = nullptr;



};
#endif // MAINWINDOW_H
