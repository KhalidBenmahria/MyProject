#include "entry.h"

Entry::Entry(QString name, bool directoryFlag):m_name(name), m_directoryFlag(directoryFlag) {

    m_item = new QTreeWidgetItem();
    m_item->setText(0, m_name);

}

const QString &Entry::name() const
{
    return m_name;
}

void Entry::setName(const QString &newName)
{
    m_name = newName;
}

void Entry::setDirectoryFlag(bool newdirectoryFlag)
{
    m_directoryFlag = newdirectoryFlag;
}

bool Entry::isDirectory() const{
    return m_directoryFlag;
}
