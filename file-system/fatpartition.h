#ifndef FATPARTITION_H
#define FATPARTITION_H

#include <fatfile.h>
#include <partition.h>

/**
 * @brief This class represents a fatpartition
 */
class FatPartition: public Partition
{
public:
    /**
     * @brief FatPartition Constructor
     * @param name
     * @param size
     * @param status
     * @param blockSize
     * @param table
     */
    FatPartition(QString name, int size, bool status, int blockSize, QTableWidget* table);


    // Destructor

    ~FatPartition();

    /**
     * @brief addFile. This method checks at the beginning if number of the free block is smaller than the number of the number of the file blocks.
     * This means that the fill can not be added. Otherwise the number of free blocks is reduced by the number of file blocks. The file will be added to the directory.
     * The file blocks will be the blocks are distributed randomly
     * @param path
     * @param f
     */
    void addFile(QString path,  File* f);
    /**
     * @brief deleteFile. This method delets checks first if the file exists. If it exists. The number of the file blocks will be added to the
     * free blocks and than the file will be removed
     * @param filePath
     */
    void deleteFile(QString filePath);
    /**
     * @brief deleteDirectory. This methods delets first all the files in the directory than the directory. At The end the Fragmentation will be calculated
     * @param path
     */
    void deleteDirectory(QString path);
    /**
     * @brief this method prints a fat tabel
     */

    void printfFatTable();
    /**
     * @brief this method helps with defragmentation. It moves all blocks to front
     * @param ep
     */

    void moveFileToFront(Entry* ep);

private:
    /**
     * @brief fat allocation tabel
     */
    int* m_fatTable;

};

#endif // FATPARTITION_H
