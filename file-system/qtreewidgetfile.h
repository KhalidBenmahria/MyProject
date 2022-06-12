#ifndef QTREEWIDGETFILE_H
#define QTREEWIDGETFILE_H
#include <QTreeWidgetItem>
#include <file.h>
/**
 * @brief The QTreeWidgetFile class will be used to display the entries of the partition in the writeCdDialog
 */

class QTreeWidgetFile : public QTreeWidgetItem
{
public:
    /**
     * @brief QTreeWidgetFile Constructor
     * @param file
     */
    QTreeWidgetFile(File* file);

    // Setter and Getter
    File *file() const;
    void setFile(File *newFile);

private:
    /**
     * @brief m_file
     */
    File* m_file;
};

#endif // QTREEWIDGETFILE_H
