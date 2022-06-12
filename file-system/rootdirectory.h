#ifndef ROOTDIRECTORY_H
#define ROOTDIRECTORY_H

#include <directory.h>
/**
 * @brief This class represents a root directory
 */

class RootDirectory : public Directory
{
public:

    RootDirectory(QString name);
    /**
     * @brief addDirectory. This method checks if the name already exists in the m_entrylist. In this case the dir will not be added.
     * Otherwise the dir will be added the m_entryList
     *
     * @param dir
     */

    void addDirectory(Directory* dir);
    /**
     * @brief deleteDirectory. At the beginning this method gets the name of the given dir. It iterates through the entries of m_entryList and compares the names of the entries whith name of the given dir. If the match, the entry will be deleted
     * @param dir
     */
    void deleteDirectory(Directory* dir);
    /**
     * @brief getDirectory. This method iterates through the entries in the root directory. It compares the given folderName with the name of the entrie. if they match, the method checks whether it is a directory.. In this case the directory is returned
     * @param folderName
     * @return
     */
    Directory* getDirectory(QString path);



};

#endif // ROOTDIRECTORY_H
