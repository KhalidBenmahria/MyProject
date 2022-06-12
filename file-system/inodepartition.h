#ifndef INODEPARTITION_H
#define INODEPARTITION_H
#include <inodefile.h>
#include <partition.h>
/**
 * @brief This class represents a inode partition
 */

class InodePartition: public Partition
{
public:
    /**
     * @brief InodePartition Cunstructor
     * @param name
     * @param size
     * @param status
     * @param blockSize
     * @param table
     */
    InodePartition(QString name, int size, bool status, int blockSize, QTableWidget* table):
    Partition(name, size, status, blockSize, table, partitionType::Inode)
    {

    }

    InodeFile *fileList() const;
    //void setFileList(InodeFile *fileList);
    /**
     * @brief adds an inode file to the inode partition
     * @param path
     * @param f
     */

    void addFile(QString path, File* f);
    /**
     * @brief delets an inode file from the partition
     * @param filePath
     */
    void deleteFile(QString filePath);
    /**
     * @brief delets a directory from the partition
     * @param path
     */

    void deleteDirectory(QString path);
    /**
     * @brief this method helps with defragmentation, which moves a file to the front
     * @param fp
     */

    void moveFileToFront(Entry* fp);

};

#endif // INODEPARTITION_H
