#ifndef FESTPLATTEERSTELLENDIALOG_H
#define FESTPLATTEERSTELLENDIALOG_H

#include <QDialog>

namespace Ui {

class FestplatteErstellenDialog;
}
/**
 * @brief The FestplatteErstellenDialog class represents a dialog, which will be seen when the user creats a disk
 */

class FestplatteErstellenDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief FestplatteErstellenDialog Constructor
     * @param parent
     */
    explicit FestplatteErstellenDialog(QWidget *parent = nullptr);
    ~FestplatteErstellenDialog();

    // Settter and Getter
    void setDiskSize(int size);
    int diskSize() const;


private:
    /**
     * @brief user interface which represents the festpalttenerstellenDialog
     */
    Ui::FestplatteErstellenDialog *ui;
};

#endif // FESTPLATTEERSTELLENDIALOG_H
