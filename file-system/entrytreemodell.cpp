#include "entrytreemodell.h"

EntryTreeModell::EntryTreeModell(QList <Entry>* entries, QObject *parent)
    :QAbstractItemModel(parent),m_entries(entries)
{
}

QVariant EntryTreeModell::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch (section) {
            case 0: return "Name";
            case 1: return "Type";
            }
        }else{
            return QString::number(section + 1);
        }


    }
     return QVariant();

}

QModelIndex EntryTreeModell::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QModelIndex EntryTreeModell::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int EntryTreeModell::rowCount(const QModelIndex &parent) const
{
    return m_entries->length();
}

int EntryTreeModell::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant EntryTreeModell::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole){
        const Entry& entry = m_entries->at(index.row());
        if(index.column() == 0){
            return entry.name();
        }else if(index.column() == 1){
            if(entry.isDirectory() == true){
                return "Folder";
            }else{
                return "File";
            }

        }
    }

    // FIXME: Implement me!
    return QVariant();
}
