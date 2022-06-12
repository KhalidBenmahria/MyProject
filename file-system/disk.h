#ifndef DISK_H
#define DISK_H
#include "partition.h"
#include "QTableWidget"
#include "fatpartition.h"
#include "inodepartition.h"

#include "QList"

/**
 * @brief This class represents a disk
 */
class Disk
{
public:
    /**
     * @brief Disk Constructor
     * @param size
     * @param diskTable
     */
    Disk(int size, QTableWidget* diskTable);


    // Setter and Getter
    int size() const;
    int unallocatedSpace() const;
    void setSize(int size);

    /**
     * @brief addPartition This method creats either an inode partition or a fat partition depending on the type. type = 0 -->Fat Partition, type = 1 --> inode Partition
     *  This method calculates the number of Blocks for this partition. At the end the startblock and the endblock of the partition in the disk will be calculated
     * @param name
     * @param partitionSize
     * @param blockSize
     * @param type
     * @param status
     * @param table
     */

    void addPartition(QString name, int partitionSize, int blockSize, int type, bool status, QTableWidget* table);
    /**
     * @brief this method removes a partition from the disk
     */
    void removePartition();


    // Destructor
    ~Disk();


    // maximum number of partitions that the user can create
    int maxNumberPartitions = 2;

    //Partition partition1;
    //Partition partition2;

    Partition* partitions[2];


    int numPartitions() const;
    void setNumPartitions(int newNumPartitions);


private:

    /**
     * @brief size of the disk
     */
    int m_size;
    /**
     * @brief number of partitions that the disk has
     */
    int m_numPartitions;
    /**
     * @brief unallocated space of the disk
     */
    int m_unallocatedSpace;
    /**
     * @brief the start block of the first partition
     */

    int startBlockPartition1;
    /**
     * @brief the end block of the first partition
     */
    int endBlockPartition1;
    /**
     * @brief the start block of the second partition
     */

    int startBlockPartition2;
    /**
     * @brief the end block of the partition
     */
    int endBlockPartition2;
    /**
     * @brief m_table
     */

    QTableWidget* m_table;
    /**
     * @brief this method fills the blocks int the partition table view whith index, text and color
     * @param index
     * @param text
     * @param color
     */
    void fillBlock(int index, QString text, QBrush color);
    /**
     * @brief fills the disk table view with MBR and the partitions
     */
    void fillDisk();


};

#endif // DISK_H
