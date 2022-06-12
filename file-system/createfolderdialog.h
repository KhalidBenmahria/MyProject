#ifndef CREATEFOLDERDIALOG_H
#define CREATEFOLDERDIALOG_H

#include <QDialog>
#include "partition.h"

namespace Ui {

class CreateFolderDialog;
}
/**
 * @brief this class represents a dialog which will be seen when the button add folder is clicked
 */

class CreateFolderDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief CreateFolderDialog Constructor
     * @param parent
     * @param partition
     */
    explicit CreateFolderDialog(QWidget *parent = nullptr, Partition* partition = nullptr);
    // Destructor
    ~CreateFolderDialog();

    // Getter
    const QString &path() const;
    const QString &name() const;

private:
    /**
     * @brief user interface
     */
    Ui::CreateFolderDialog *ui;
    /**
     * @brief m_partition
     */
    Partition* m_partition;
    /**
     * @brief m_name
     */
    QString m_name;

private slots:

    /**
     * @brief this slot will be calles when the user enters a name. It reads the name  and uses it to set the variable m_name
     */
    void setNameSlot();
};

#endif // CREATEFOLDERDIALOG_H
