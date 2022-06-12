#include "createfolderdialog.h"
#include "ui_createfolderdialog.h"


CreateFolderDialog::CreateFolderDialog(QWidget *parent, Partition* partition) :
    QDialog(parent),
    ui(new Ui::CreateFolderDialog),
    m_partition(partition)
{

    ui->setupUi(this);


    connect(ui->nameLineEdit, &QLineEdit::textChanged, this, &CreateFolderDialog::setNameSlot);

}

CreateFolderDialog::~CreateFolderDialog()
{
    delete ui;
}



const QString &CreateFolderDialog::name() const
{
    return m_name;
}



void CreateFolderDialog::setNameSlot()
{
    m_name = ui->nameLineEdit->text();
}
