#ifndef CREATEPARTITIONDIALOG_H
#define CREATEPARTITIONDIALOG_H

#include <QDialog>
#include "partition.h"
namespace Ui {

class createPartitionDialog;
}
/**
 * @brief The createPartitionDialog class.this class represents a dialog that will be seen when the user adds a new partition to the disk.
 */

class createPartitionDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief createPartitionDialog Constructor
     * @param parent
     * @param diskSize
     * @param nameTaken
     */
    explicit createPartitionDialog(QWidget *parent = nullptr, int diskSize = 0, QString nameTaken = "");
    // Destructor
    ~createPartitionDialog();

    // Setter and Getter

    int partitionSize() const;
    void setPartitionSize(int newPartitionSize);

    int blockSize() const;
    void setBlockSize(int newBlockSize);

    const QString &name() const;
    void setName(const QString &newName);

    Partition::partitionType type() const;
    void setType(Partition::partitionType newType);

private:
    /**
     * @brief m_nameTaken
     */

    QString m_nameTaken;

    const QString m_possiblePartitionNames[4] = {"C:","D:","E:","F:"};
    /**
     * @brief m_numPossibleNames
     */

    const int m_numPossibleNames = 4;
    /**
     * @brief user interface
     */
    Ui::createPartitionDialog *ui;
    /**
     * @brief Size of the partition
     */
    int m_partitionSize;
    /**
     * @brief size of block
     */
    int m_blockSize;
    /**
     * @brief type of the partition
     */
    Partition::partitionType m_type;
    /**
     * @brief name of the partition
     */
    QString m_name;


public slots:
    /**
     * @brief this slot sets the member variable m_Partition depending on the input of the user
     */
    void partitionSizeSlot();
    /**
     * @brief this slot sets the member variable m_size depending on the input of the user
     */
    void blockSizeSlot();
    /**
     * @brief  this slot sets the member variable m_type depending on the input of the user
     */
    void partitionTypSlot();
    /**
     * @brief  this slot sets the member variable m_name depending on the input of the user
     */
    void partitionNameSlot();

};

#endif // CREATEPARTITIONDIALOG_H
