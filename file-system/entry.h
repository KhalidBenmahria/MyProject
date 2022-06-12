#ifndef ENTRY_H
#define ENTRY_H

#include <QString>
#include <QTreeWidgetItem>
/**
 * @brief This class represents an entry
 */
class Entry
{
public:
    /**
     * @brief Entry default Constructor
     */
    Entry();
    /**
     * @brief Entry Constructor
     * @param name
     * @param directoryFlag
     */

    Entry(QString name, bool directoryFlag);

    // Setter and Getter

    const QString &name() const;
    void setName(const QString &newName);

    bool isDirectory() const;
    void setDirectoryFlag(bool newEntryFlag);



protected:
    /**
     * @brief name of the entry
     */
    QString m_name;
    /**
     * @brief flag which shows whether the entry is a folder or a file
     */
    bool m_directoryFlag;
    /**
     * @brief m_item
     */
    QTreeWidgetItem* m_item;
};

#endif // ENTRY_H
