#ifndef INODEFILE_H
#define INODEFILE_H
#include <file.h>

/**
 * @brief The class represents an inode file
 */
class InodeFile: public File
{
public:
    /**
     * @brief InodeFile Constructor
     * @param name
     * @param typ
     * @param size
     * @param status
     * @param creator
     */
    InodeFile(QString name, QString typ, int size, bool status, QString creator): File(name, typ, size, status, creator)
    {

    }
    /**
     * @brief length
     * @return the length of m_inodeTable
     */

    int length();
    /**
     * @brief itemAt
     * @param index
     * @return the value which is stored in the Tabel at the index
     */
    int itemAt(int index);
    /**
     * @brief sets an item at the index in the tabel
     * @param index
     * @param item
     */
    void setItemAt(int index, int item);
    /**
     * @brief pushs an index to the tabel
     * @param index
     */
    void addIndex(int index);

private:
    /**
     * @brief m_inodeTable
     */
    QList<int> m_inodeTable;
};

#endif // INODEFILE_H
