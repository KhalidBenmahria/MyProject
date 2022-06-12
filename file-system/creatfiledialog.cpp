#include "creatfiledialog.h"
#include "ui_creatfiledialog.h"
#include <QString>

CreatFileDialog::CreatFileDialog(QWidget *parent, Partition* partition) :
    QDialog(parent), ui(new Ui::CreatFileDialog), m_partition(partition)
{
    ui->setupUi(this);
    ui->sizeSpinBox->setValue(1);
    ui->sizeSpinBox->setMinimum(1);
    ui->sizeSpinBox->setMaximum(m_partition->size());

    connect(ui->nameLineEdit, &QLineEdit::textChanged, this, &CreatFileDialog::setNameSlot);
    //connect(ui->formatComboBox, &QComboBox::currentTextChanged, this, &CreatFileDialog::);
    connect(ui->sizeSpinBox, &QSpinBox::valueChanged, this, &CreatFileDialog::setSizeSlot);
    connect(ui->creatorLineEdit, &QLineEdit::textChanged, this, &CreatFileDialog::setCreatorSlot);
    connect(ui->pathComboBox, &QComboBox::currentTextChanged, this, &CreatFileDialog::setPathSlot);
    Directory* dir = partition->rootDirectory();
    ui->pathComboBox->addItem(m_partition->getName()+"/");
    for(Entry* e: dir->getEntryList()){       
        if(e->isDirectory()){
            ui->pathComboBox->addItem(m_partition->getName() + "/" + e->name() + "/");
        }

    }



}

CreatFileDialog::~CreatFileDialog()
{

}

const QString &CreatFileDialog::name() const
{
    return m_name;
}

int CreatFileDialog::size() const
{
    return m_size.toInt();
}

const QString &CreatFileDialog::creator() const
{
    return m_creator;
}

const QString &CreatFileDialog::path() const
{
    return m_path;
}



void CreatFileDialog::setSizeSlot()
{
    m_size = ui->sizeSpinBox->text();


}

void CreatFileDialog::setNameSlot()
{
     m_name = ui->nameLineEdit->text();

}

void CreatFileDialog::setCreatorSlot()
{
    m_creator = ui->creatorLineEdit->text();
}

void CreatFileDialog::setPathSlot()
{
     m_path = ui->pathComboBox->currentText();

}
