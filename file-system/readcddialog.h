#ifndef READCDDIALOG_H
#define READCDDIALOG_H
#include <QDialog>
#include <file.h>
#include <disk.h>


namespace Ui {
class readCdDialog;
}
/**
 * @brief The readCdDialog class represents a dialog which will be seen when the user reads a cd.
 */

class readCdDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief readCdDialog Constructor
     * @param parent
     * @param disk
     */
    explicit readCdDialog(QWidget *parent = nullptr, Disk* disk = nullptr);
    // Destructor
    ~readCdDialog();

private:
    // User interface
    Ui::readCdDialog *ui;
    /**
     * @brief m_disk
     */

    Disk* m_disk;
    /**
     * @brief m_partitionType
     */
    Partition::partitionType m_partitionType;

    void stringToFile(QString fileString);
    /**
     * @brief filePath
     */

    QString filePath;
    /**
     * @brief desktopPath
     */
    QString desktopPath;

    QList<File*> m_files;
    /**
     * @brief createTable generets a table based on the files within chosen cd file.
     */

    void createTable();



private slots:
    /**
     * @brief setPartitionType gets the partition type which is already selected by the user
     */

    void setPartitionType();
    void readCD();
    void setFilePath();
    void copyFiles();
};

#endif // READCDDIALOG_H
