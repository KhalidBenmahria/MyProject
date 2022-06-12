#include "createpartitiondialog.h"
#include "ui_createpartitiondialog.h"
#include "partition.h"
#include "disk.h"

createPartitionDialog::createPartitionDialog(QWidget *parent, int diskSize, QString nameTaken) :
    QDialog(parent),
    m_nameTaken(nameTaken),
    ui(new Ui::createPartitionDialog)
{
    ui->setupUi(this);
    ui->typeComboBox->addItem("INODE");
    ui->typeComboBox->addItem("FAT");
    //ui->typeComboBox->setCurrentIndex(-1);


    for(int i = 0; i < m_numPossibleNames; i++){
        if(!QString::compare(m_possiblePartitionNames[i], m_nameTaken)){
            continue;
        }
        ui->nameComboBox->addItem(m_possiblePartitionNames[i]);
    }
    ui->nameComboBox->setCurrentIndex(-1);

    for (int i = 0; i <= 5; i++){
        ui->sizeComboBox->addItem(QString::number((int) (diskSize * i * 0.2)));
    }
    ui->sizeComboBox->setCurrentIndex(-1);
    ui->blockSizeSpinBox->setValue(8);
    ui->blockSizeSpinBox->setRange(1, 100);
    m_blockSize = 8;

    //connections
    connect(ui->sizeComboBox, &QComboBox::currentIndexChanged, this, &createPartitionDialog::partitionSizeSlot);
    connect(ui->blockSizeSpinBox, &QSpinBox::valueChanged, this, &createPartitionDialog::blockSizeSlot);
    connect(ui->typeComboBox, &QComboBox::currentIndexChanged, this, &createPartitionDialog::partitionTypSlot);
    connect(ui->nameComboBox, &QComboBox::currentIndexChanged, this, &createPartitionDialog::partitionNameSlot);

}

void createPartitionDialog::partitionSizeSlot(){

    m_partitionSize = ui->sizeComboBox->currentText().toInt();

}


void createPartitionDialog::blockSizeSlot()
{
    int blockSize = ui->blockSizeSpinBox->value();
    setBlockSize(blockSize);
}

void createPartitionDialog::partitionTypSlot()
{


    QString type = ui->typeComboBox->currentText();
    qDebug() << type << Qt::endl;

    if (!QString::compare(type, "FAT")){

         m_type = Partition::Fat;
         return;
    }else if (!QString::compare(type, "INODE")){

         m_type = Partition::Inode;
         return;
    }

    qDebug() << "There was a problem" << Qt::endl;


}


createPartitionDialog::~createPartitionDialog()
{
    delete ui;
}

int createPartitionDialog::partitionSize() const
{
    return m_partitionSize;
}

void createPartitionDialog::setPartitionSize(int newPartitionSize)
{
    m_partitionSize = newPartitionSize;
}

int createPartitionDialog::blockSize() const
{
    return m_blockSize;
}

void createPartitionDialog::setBlockSize(int newBlockSize)
{
    m_blockSize = newBlockSize;
}

const QString &createPartitionDialog::name() const
{
    return m_name;
}

void createPartitionDialog::setName(const QString &newName)
{
    m_name = newName;
}

Partition::partitionType createPartitionDialog::type() const
{
    return m_type;
}

void createPartitionDialog::setType(Partition::partitionType newType)
{
    m_type = newType;
}

void createPartitionDialog::partitionNameSlot(){
    m_name = ui->nameComboBox->currentText();
}
