#ifndef PARTITION_H
#define PARTITION_H
#include "block.h"

#include "QTableWidget"
#include "file.h"
#include "rootdirectory.h"
#include "QTreeWidget"


/**
 * @brief This abstract class represents partition
 */

class Partition
{
public:
    /**
     * @brief The partitionType for the two types of the partition (Inode and Fat)
     */

    enum partitionType { Inode = 0, Fat = 1};
    /**
     * @brief Partition Constructor
     * @param name
     * @param size
     * @param status
     * @param blockSize
     * @param table
     * @param type
     */

    Partition(QString name, int size, bool status, int blockSize, QTableWidget* table, partitionType type);

    // settter and getter
    int numBlocks() const;
    int size() const;

    void setNumBlocks(int numBlocks);

    QTableWidget *table() const;
    void setTable(QTableWidget *newTable);
    const QList<File> &fileList() const;
    void setFileList(const QList<File> &newFileList);

    virtual void addFile(QString path, File* f) = 0;
    virtual void deleteFile(QString filePath) = 0;
    void addDirectory(QString name);
    virtual void deleteDirectory(QString path) = 0;

    /**
     * @brief calulateFragmentation This method calculats the fragmentation. It checks firs if the number of free Blocks = 0. If this is the cas, the fragmentation is 100
     * Otherwise it calculates the fragmenation using the formel (freemax/ free) * 100
     */
    void calulateFragmentation();
    /**
     * @brief defrag. This method goes through the entries in the root directory. If the entry is a directory, the files inside it will be moved to the front and if the entry is a file, it will also moved to the front. AT the end the fragmentation will be calculated
     */
    void defrag();

    /**
     * @brief moveFileToFront this method is precisely defined in the subclasses depending on the type of partition
     * @param ep
     */
    virtual void moveFileToFront(Entry* ep) = 0;

    /**
     * @brief m_fileList
     */
    QList <File> m_fileList;


    // Setter and Getter
    const QString &getName() const;
    void setName(const QString &newName);
    int blockSize() const;
    void setBlockSize(int newBlockSize);
    Directory* getDirectory(QString path);
    File* getFile(QString filePath);

    int freeBlocks() const;
    void setFreeBlocks(int newFreeBlocks);

    RootDirectory *rootDirectory() const;
    void setRootDirectory(RootDirectory *newRootDirectory);

    QTreeWidget *treeWidget() const;
    void setTreeWidget(QTreeWidget *newTreeWidget);

    partitionType type() const;
    int fragmentation() const;


    /**
     * @brief typeString returns the type of the partition as a QString
     * @return
     */
    QString typeString();

    /**
     * @brief addDirectory adds a directory to m_rootDirectory
     * @param f
     */

    void addDirectory(Directory* f);

    /**
     * @brief getFirstFreeBlock
     * @return the index of the first free block in the partition
     */

    int getFirstFreeBlock();
    /**
     * @brief getLastFreeBlock
     * @return the index of the last free block in the partition
     */
    int getLastFreeBlock();



protected:
    /**
     * @brief this method makes the tabel gui
     */

    void fillTable();
    /**
     * @brief getBlock
     * @param index
     * @return Block* at the index
     */
    Block* getBlock(int index);
    /**
     * @brief represents  the root directory of the partition
     */
    RootDirectory* m_rootDirectory;
    /**
     * @brief m_name
     */
    QString m_name;
    /**
     * @brief size of the partition
     */
    int m_size;
    /**
     * @brief status of the partition
     */
    bool m_status;
    /**
     * @brief the block size of the partition
     */
    int m_blockSize;
    /**
     * @brief m_blockList
     */
    Block* m_blockList;
    /**
     * @brief number of the partitions block
     */
    int m_numBlocks;
    /**
     * @brief the number of the free blocks of the partition
     */
    int m_freeBlocks;
    /**
     * @brief m_table
     */
    QTableWidget* m_table;
    /**
     * @brief m_treeWidget
     */
    QTreeWidget* m_treeWidget;
    /**
     * @brief the type of the partition
     */
    partitionType m_type;
    /**
     * @brief m_fragmentation
     */
    int m_fragmentation;

};

#endif // PARTITION_H
