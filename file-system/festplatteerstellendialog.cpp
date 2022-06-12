#include "festplatteerstellendialog.h"
#include "ui_festplatteerstellendialog.h"

FestplatteErstellenDialog::FestplatteErstellenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FestplatteErstellenDialog)
{

    ui->setupUi(this);



}

FestplatteErstellenDialog::~FestplatteErstellenDialog()
{
    delete ui;
}


void FestplatteErstellenDialog::setDiskSize(int size){
       ui->diskSizeComboBox->setCurrentIndex(-1);
}


int  FestplatteErstellenDialog::diskSize() const{
    return ui->diskSizeComboBox->currentText().toInt();
}

