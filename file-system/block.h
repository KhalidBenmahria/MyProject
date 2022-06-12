#ifndef BLOCK_H
#define BLOCK_H
#include <QString>
#include <QTableWidgetItem>

/**
 * @brief  Class represents a block. Every block has a status, data (id of the file or f for free) and position representing by index
 */

class Block
{


public:
    /**
     * @brief The blockStatus enum
     */
    enum blockStatus{Free = 0, Occupied = 1, Defect = 2};
    /**
     * @brief Block Constructor
     * @param index
     * @param status
     * @param data
     */

    Block(int index, blockStatus status, QString data);
    // Destructor

    ~Block();


    // Setter and Getter

    Block *nextBlock() const;   
    void setNextBlock(Block *nextBlock);    
    Block *prevBlock() const;
    void setPrevBlock(Block *prevBlock);
    int index() const;
    void setIndex(int index);    

    QString data() const;
    void setData(const QString &data);
    QTableWidgetItem *item() const;
    void setItem(QTableWidgetItem *newItem);
    blockStatus status() const;
    void setStatus(blockStatus newStatus);

    /**
     * @brief writes index in the current block (which represents by a column in the gui). This method makes the block Occupied and red
     * @param data
     */
    void writeBlock(QString data);
    /**
     * @brief makes the block free and makes it green
     */
    void freeBlock();

protected:

    Block* m_nextBlock;
    Block* m_prevBlock;
    int m_index;
    /**
     * @brief m_status can be Free, Occupied or defect
     */
    blockStatus m_status;
    /**
     * @brief m_data can be the id or just f which mwans free
     */
    QString m_data;
    QTableWidgetItem* m_item;
};

#endif // BLOCK_H
