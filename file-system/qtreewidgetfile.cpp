#include "qtreewidgetfile.h"

QTreeWidgetFile::QTreeWidgetFile(File* file): m_file(file)
{

}

File *QTreeWidgetFile::file() const
{
    return m_file;
}

void QTreeWidgetFile::setFile(File *newFile)
{
    m_file = newFile;
}
