#ifndef CREATFILEDIALOG_H
#define CREATFILEDIALOG_H
#include <QStandardItemModel>

#include <QDialog>
#include <QList>
#include "partition.h"
#include "file.h"
#include "inodefile.h"
#include "fatfile.h"

namespace Ui {

class CreatFileDialog;
}
/**
 * @brief The CreatFileDialog class represents adialog which will be seen when the user adds a file to the Partition
 */

class CreatFileDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief CreatFileDialog Constructor
     * @param parent
     * @param partition
     */
    explicit CreatFileDialog(QWidget *parent = nullptr, Partition* partition = nullptr);
    // Destructor
    ~CreatFileDialog();

    // Getter

    const QString &name() const;
    int size() const;
    const QString &creator() const;
    const QString &path() const;


private:
    /**
     * @brief ui
     */
    Ui::CreatFileDialog *ui;
    /**
     * @brief m_partition
     */
    Partition* m_partition;
    /**
     * @brief m_name
     */
    QString m_name;
    /**
     * @brief m_size
     */
    QString m_size;
    /**
     * @brief m_creator
     */
    QString m_creator;
    /**
     * @brief m_path
     */
    QString m_path;



private slots:

    /**
     * @brief this slot sets the member variable m_size depending on the input of the user
     */
    void setSizeSlot();
    /**
     * @brief this slot sets the member variable m_name depending on the input of the user
     */
    void setNameSlot();
    /**
     * @brief this slot sets the member variable m_creator depending on the input of the user
     */
    void setCreatorSlot();
    /**
     * @brief this slot sets the member variable m_path depending on the input of the user
     */
    void setPathSlot();

};

#endif // CREATFILEDIALOG_H
