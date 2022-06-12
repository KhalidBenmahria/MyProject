#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>
#include "partition.h"

namespace Ui {

class deleteDialog;
}
/**
 * @brief this class represents a dialog which will be seen when the user delets a file or a dialog
 */

class deleteDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief deleteDialog Constructor
     * @param parent
     * @param partition
     */
    explicit deleteDialog(QWidget *parent = nullptr, Partition* partition = nullptr);
    // Destructor
    ~deleteDialog();

    // Getter
    const QString &path() const;

private:
    /**
     * @brief ui
     */
    Ui::deleteDialog *ui;
    /**
     * @brief m_partition
     */
    Partition* m_partition;
    /**
     * @brief m_path
     */
    QString m_path;

private slots:
    /**
     * @brief this slot sets the member variable m_path depending on the input of the user
     */
    void setPathSlot();
};

#endif // DELETEDIALOG_H
