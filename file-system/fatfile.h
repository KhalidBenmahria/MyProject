#ifndef FATFILE_H
#define FATFILE_H
#include <file.h>

/**
 * @brief This class represents a fat file
 */
class FatFile: public File
{
public:
    /**
     * @brief FatFile Constructor
     * @param name
     * @param typ
     * @param size
     * @param status
     * @param creator
     */
    FatFile(QString name, QString typ, int size, bool status, QString creator): File(name, typ, size, status, creator){}

    // Setter and Getter
    int startIndex() const;
    void setStartIndex(int startIndex);

private:
    /**
     * @brief start index of the file
     */
    int m_startIndex;
};

#endif // FATFILE_H
