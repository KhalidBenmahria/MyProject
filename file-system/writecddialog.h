#ifndef WRITECDDIALOG_H
#define WRITECDDIALOG_H

#include <QDialog>
#include "QList"
#include "file.h"
#include "disk.h"
#include "qtreewidgetfile.h"

namespace Ui {

class writeCdDialog;
}
/**
 * @brief The writeCdDialog class represents a dialog which will be seen when the user writes a cd
 */
class writeCdDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief writeCdDialog Constructor
     * @param parent
     * @param disk
     */
    explicit writeCdDialog(QWidget *parent = nullptr, Disk* disk = nullptr);
    //Destructor
    ~writeCdDialog();

private:
    /**
     * @brief user interface which represents the write dialog
     */
    Ui::writeCdDialog *ui;
    /**
     * @brief generateDirectory. This method creats at first a QTreeWidgetItem from the given entry, which should be a directory.
     * It iterates through the entries of the directory and makes QTreeWidgetFile from each entry. These QTreeWidgetFiles will be at the end to the QTreeWidgetItem.
     * @param ep
     * @return
     */

    QTreeWidgetItem* generateDirectory(Entry* ep);



    /**
     * @brief maximum size of the data which can the user write.
     */
    const int m_maxSize = 25;
    /**
     * @brief the left size of the maximum size, after the user has written a cd.This means when the user writes a 10 GB file. The left size is 15 GB. This variable will be used to check if the maximum size has been reached or not
     *
     */
    int m_sizeLeft;
    /**
     * @brief m_files
     */
    QList<File*> m_files;
    /**
     * @brief m_disk
     */
    Disk* m_disk;
    /**
     * @brief m_partition
     */
    Partition* m_partition;
    /**
     * @brief The path of the current user's desktop folder
     */
    QString desktopPath;
    /**
     * @brief m_tree
     */
    QTreeWidget* m_tree;
    QList<File> getSelectedFiles();


private slots:
    /**
     * @brief handleItemChanged. It is a slot.This slot checks if the selected status changes. If the files is selectes the left size musst be smaller by the size of the date. When the same file which was selected and to the m_files added, is now not selected, the size of it which is from the left size substracted, musst be now added to the left size
     * This file musst be also removed from the file
     * @param item
     * @param column
     */

    void handleItemChanged(QTreeWidgetItem* item, int column);
    /**
     * @brief generateTree. This slot displays the files the partition has on the gui. At first this method checks which partition has the user selected
     * and gets the name of this partition and sets this partition as the top item in the tree. Than it iterates through the entries of the partition and checks if the entray is a folder or a file. Depending on this, the entry will be added to the tree
     */
    void generateTree();
    /**
     * @brief writeCd. This method checks at first if the maximus size has been reached. In this case a message box will be displayes.
     * It also checks if the user has enterd a name or not. In this case a warning message box will be displayed. At the end the selectes file will be written.
     */

    void writeCd();

};

#endif // WRITECDDIALOG_H
