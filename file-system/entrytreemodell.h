#ifndef ENTRYTREEMODELL_H
#define ENTRYTREEMODELL_H

#include <QAbstractItemModel>
#include <entry.h>

/**
 * @brief The EntryTreeModell class which represents a tree modell of an entry
 */

class EntryTreeModell : public QAbstractItemModel
{
    Q_OBJECT

public:
    /**
     * @brief EntryTreeModell Constructor
     * @param entries
     * @param parent
     */
    explicit EntryTreeModell(QList <Entry>* entries, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    /**
     * @brief m_entries
     */
    QList <Entry>* m_entries;

};

#endif // ENTRYTREEMODELL_H
