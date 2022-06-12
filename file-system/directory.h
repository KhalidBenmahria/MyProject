#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "file.h"
#include "entry.h"
#include <QList>

/**
 * @brief This class represents a directory
 */

class Directory: public Entry
{
public:
    /**
     * @brief Directory Constructor
     * @param name
     */
    Directory(QString name);


    // Setter and Getter
    const QList<Entry *> &getEntryList() const;    
    void setEntryList(const QList<Entry *> &newEntryList);

    /**
     * @brief add only a file to the directory
     * @param entry
     */
    void addFile(File* entry);
    /**
     * @brief removes a file from the directory
     * @param entry
     */
    void removeFile(File* entry);
    /**
     * @brief gets a specific file from the direcory using the filename
     * @param filename
     * @return File*
     */
    File* getFile(QString filename);

protected:
    /**
     * @brief m_entryList
     */
    QList <Entry*> m_entryList;

};

#endif // DIRECTORY_H
