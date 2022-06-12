#include "deletedialog.h"
#include "ui_deletedialog.h"

deleteDialog::deleteDialog(QWidget *parent, Partition* partition) :
    QDialog(parent),
    ui(new Ui::deleteDialog),
    m_partition(partition)
{

    ui->setupUi(this);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &deleteDialog::setPathSlot);
    Directory* dir = m_partition->rootDirectory();
    //ui->comboBox->addItem(m_partition->getName()+"/");
    for(Entry* e: dir->getEntryList()){

        if(e->isDirectory()){
            ui->comboBox->addItem(m_partition->getName() + "/" + e->name() + "/");
            QString dirName = e->name();
            if(((Directory*)e)->getEntryList().length() != 0){
                for(Entry* e:((Directory*)e)->getEntryList()){
                    ui->comboBox->addItem(m_partition->getName() + "/" + dirName + "/" + e->name());

                }

            }


        }else{
            ui->comboBox->addItem(m_partition->getName() + "/" + e->name());
        }



    }

}

deleteDialog::~deleteDialog()
{
    delete ui;
}

const QString &deleteDialog::path() const
{
    return m_path;
}

void deleteDialog::setPathSlot()
{
    m_path = ui->comboBox->currentText();
    qDebug() << m_path << Qt::endl;
}
