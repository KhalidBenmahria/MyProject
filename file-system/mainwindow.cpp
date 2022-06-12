#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "createpartitiondialog.h"
#include "QMessageBox"
#include <QDebug>
#include <QDialog>
#include <partition.h>
#include <disk.h>
#include <partitiondetaisdialog.h>
#include <readcddialog.h>
#include <writecddialog.h>

#include <fatpartition.h>
#include <inodepartition.h>
#include <QDebug>
#include <partitiondetaisdialog.h>

#include <fatfile.h>
#include <inodefile.h>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{




    ui->setupUi(this);
    this->setWindowTitle("File System simulator");



    connect(ui->createDiskAction, &QAction::triggered, this, &MainWindow::createDiskTriggered);
    connect(ui->deleteDiskAction, &QAction::triggered, this, &MainWindow::deleteDiskTriggered);
    connect(ui->showDetailsPartition1Button,&QPushButton::clicked, this, &MainWindow::on_showDetailsButton_partition1_clicked);


    connect(ui->writeCDAction, &QAction::triggered, this, &MainWindow::writeCDtriggered);
    connect(ui->readCDAction, &QAction::triggered, this, &MainWindow::readCDtriggered);

    connect(ui->createPartitionAction, &QAction::triggered, this, &MainWindow::createPartitionTriggered);
    connect(ui->removePartitionAction_2, &QAction::triggered, this, &MainWindow::removePartitionTriggered);

    connect(ui->sample1Action, &QAction::triggered, this, &MainWindow::sample1Triggered);

    connect(ui->defragPartition1Button, &QPushButton::pressed, this, &MainWindow::defragPartition1);
    connect(ui->defragPartition2Button, &QPushButton::pressed, this, &MainWindow::defragPartition2);

    m_diskTable = ui->MainWindow::diskTable;
    m_partition1Table = ui->MainWindow::partition1Table;
    m_partition2Table = ui->MainWindow::partition2Table;
    setupTable(m_diskTable);
    setupTable(m_partition1Table);
    setupTable(m_partition2Table);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::setupTable(QTableWidget* table){


    table->setStyleSheet("QTableWidget {background-color: transparent;}"
              "QHeaderView::section {background-color: transparent;}"
              "QHeaderView {background-color: transparent;}"
              "QTableCornerButton::section {background-color: transparent;}");





    // make table look pretty
    table->horizontalHeader()->setMinimumSectionSize(0);
    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setFocusPolicy(Qt::NoFocus);
    table->setSelectionMode(QAbstractItemView::NoSelection);




}


void MainWindow::createDiskTriggered(){


    if(m_disk != nullptr){
        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning", "You can only create one disk.");
        box.exec();
        return;
    }

    FestplatteErstellenDialog diskDialog;

    int diskSize;

    if(diskDialog.exec() == QDialog::Accepted) {
        qDebug() << "Dialog was accepted" << Qt::endl;
        diskSize = diskDialog.diskSize();
        generateDisk(diskSize);
    }else{
        qDebug() << "Dialog was rejected" << Qt::endl;
    }

}


void MainWindow::deleteDiskTriggered(){
    if(m_disk == nullptr){
        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please create a Disk first");
        box.exec();
        qDebug() << "Please create a Disk first" << Qt::endl;
        return;
    }
    if(m_disk->numPartitions() > 0){
        for(int i = 0; i <= m_disk->numPartitions(); i++){
            removePartitionTriggered();
        }

    }



    QAbstractItemModel* const mdl = m_diskTable->model();
    mdl->removeRows(0,mdl->rowCount());
    mdl->removeColumns(0,mdl->columnCount());



    updateGUI();
    free(m_disk);
    m_disk = nullptr;


}



void MainWindow::createPartitionTriggered(){

    if( m_disk == nullptr || m_disk->numPartitions() == 2){
        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please create a Disk first or delete a Partition");
        box.exec();
        qDebug() << "Please create a Disk first" << Qt::endl;
        return;
    }else if (m_disk->unallocatedSpace() == 0) {
        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","There is no unallocated space left. Please delete a partition fisrt.");
        box.exec();
        return;

    }

    QString namePartition1 = "";
    if(m_disk->numPartitions() == 1){
        namePartition1 = m_disk->partitions[0]->getName();
    }
    createPartitionDialog partitionDialog = createPartitionDialog(nullptr, m_disk->unallocatedSpace(), namePartition1);



    if(partitionDialog.exec() == QDialog::Accepted) {
        qDebug() << "Dialog was accepted" << Qt::endl;

        QString name;
        int partitionSize;
        int blockSize;
        int type;
        bool status;


        name = partitionDialog.name();
        partitionSize = partitionDialog.partitionSize();
        qDebug() << "Size Partition = " << partitionSize << Qt::endl;
        blockSize = partitionDialog.blockSize();
        qDebug() << "Size Block = " << blockSize << Qt::endl;
        type = partitionDialog.type();
        status = true;
        if(name == nullptr || partitionSize == 0){
            if(name == nullptr){
                 QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please check if you select a name");
                  box.exec();
            }else if(partitionSize == 0){
                QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please select a partition size greater than zero");
                 box.exec();
            }

            return;

        }else{
                generatePartition(name, partitionSize, blockSize, type, status);
        }
    }
}



void MainWindow::generateDisk(int diskSize){

    generateColums(m_diskTable, 20);
    m_disk = new Disk(diskSize, m_diskTable);
    updateGUI();

}



void MainWindow::generatePartition(QString name, int partitionSize, int blockSize, int type, bool status){

    int index = m_disk->numPartitions();
    QTableWidget* table;
    if(index == 0){
        table = m_partition1Table;
        ui->partition1GroupBox->setTitle(name);
    }else{
        table = m_partition2Table;
        ui->partition2GroupBox->setTitle(name);
    }

    int numBlocks = partitionSize / blockSize;
    qDebug() << numBlocks << Qt::endl;
    generateColums(table, numBlocks);


    m_disk->addPartition(name, partitionSize, blockSize, type, status, table);
    updateGUI();

}

void MainWindow::on_showDetailsButton_partition1_clicked()
{

    if( m_disk == nullptr || m_disk->numPartitions() == 0){
        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please create a Disk or Partition first");
        box.exec();
        return;
    }
    m_disk->partitions[0]->m_fileList.clear();

    PartitionDetaisDialog* dialog = new PartitionDetaisDialog(nullptr, m_disk->partitions[0]);
    dialog->exec();

    delete(dialog);
    updateGUI();

}

void MainWindow::readCDtriggered(){

    if( m_disk == nullptr || m_disk->numPartitions() == 0){
        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please create a Disk or Partition first");
        box.exec();
        return;
    }
    readCdDialog dialog(nullptr, m_disk);
    dialog.exec();

    updateGUI();
}


void MainWindow::writeCDtriggered(){

    if( m_disk == nullptr || m_disk->numPartitions() == 0){
        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please create a Disk or Partition first");
        box.exec();
        return;
    }


    writeCdDialog* dialog = new writeCdDialog(nullptr, m_disk);
    dialog->exec();
}


void MainWindow::generateColums(QTableWidget* table, int blockNumber){

    table->setRowCount(1);
    table->setColumnCount(blockNumber);
}

void MainWindow::removePartitionTriggered(){

    qDebug() << "Removing partition" << Qt::endl;


    if( m_disk == nullptr || m_disk->numPartitions() == 0){
        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please create a Disk or Partition first");
        box.exec();
        return;
    }

    int current = m_disk->numPartitions();
    QAbstractItemModel* const mdl = m_disk->partitions[current-1]->table()->model();
    mdl->removeRows(0,mdl->rowCount());
    mdl->removeColumns(0,mdl->columnCount());


    m_disk->removePartition();
    updateGUI();
}


void MainWindow::sample1Triggered(){

    if(m_disk != nullptr){
        deleteDiskTriggered();
    }

    //generate disk
    generateDisk(200);

    //generate partition 1
    generatePartition("C:", 100, 2, 0, true);

    Partition* partition1 = m_disk->partitions[0];

    File* file1  = new FatFile("testFile1", "FAT", 18, true, "Sara Salha");
    File* file2  = new FatFile("testFile2", "INODE", 1, true, "Sara Salha");
    File* file3  = new FatFile("testFile3", "FAT", 8, true, "Sara Salha");

    partition1->addFile(partition1->getName(), file3);

    Directory* dir = new Directory("usr");
    Directory* dir1 = new Directory("bin");

    partition1->addDirectory( dir);
    partition1->addDirectory(dir1);


    QString path = partition1->getName() + "/bin/";
    qDebug() << "Pfad: " << path << Qt::endl;
    partition1->addFile( path, file1);
    partition1->addFile( path, file2);


    //generate partition 2
    generatePartition("D:", 99, 5, 1, true);
    Partition* partition2 = m_disk->partitions[1];

    File* file4  = new InodeFile("testFile1", "FAT", 18, true, "Sara Salha");
    File* file5  = new InodeFile("testFile2", "INODE", 1, true, "Sara Salha");
    File* file6  = new InodeFile("testFile3", "FAT", 8, true, "Sara Salha");

    partition2->addFile(partition2->getName(), file4);
    partition2->addFile(partition2->getName(), file5);
    partition2->addFile(partition2->getName(), file6);

    Directory* dir3 = new Directory("usr");
    Directory* dir4 = new Directory("bin");


    partition2->addDirectory(dir3);
    partition2->addDirectory(dir4);

    updateGUI();

}


void MainWindow::on_showDetailsPartition2Button_clicked()
{

    if( m_disk == nullptr || m_disk->numPartitions() < 2){
        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please create a Disk or Partition first");
        box.exec();
        return;
    }
    m_disk->partitions[1]->m_fileList.clear();
    PartitionDetaisDialog* dialog = new PartitionDetaisDialog(nullptr, m_disk->partitions[1]);
    dialog->exec();

    delete(dialog);
    updateGUI();


}


void MainWindow::updateGUI(){

    if(m_disk == nullptr){
        //Disk
        ui->diskSizeLabel->setText("--- GB");
        ui->unallocatedSpaceLabel->setText("--- GB");

        //Partition 1
        ui->partition1GroupBox->setTitle("Partition 1");
        ui->sizePartition1Label->setText("---");
        ui->freeBlocksPartition1Label->setText("---");
        ui->blockSizePartition1Label->setText("---");
        ui->defragPartition1Label->setText("---");

        //Partition 2
        ui->partition1GroupBox->setTitle("Partition 1");
        ui->sizePartition2Label->setText("---");
        ui->freeBlocksPartition2Label->setText("---");
        ui->blockSizePartition2Label->setText("---");
        ui->defragPartition2Label->setText("0%");

        return;
    }

    //Disk
    ui->diskSizeLabel->setText(QString::number(m_disk->size()) + " GB");
    ui->unallocatedSpaceLabel->setText(QString::number(m_disk->unallocatedSpace()) + " GB");

    if(m_disk->numPartitions() == 0){
        //Partition 1
        ui->partition1GroupBox->setTitle("Partition 1");
        ui->sizePartition1Label->setText("---");
        ui->freeBlocksPartition1Label->setText("---");
        ui->blockSizePartition1Label->setText("---");
        ui->defragPartition1Label->setText("---");

        //Partition 2
        ui->partition1GroupBox->setTitle("Partition 1");
        ui->sizePartition2Label->setText("---");
        ui->freeBlocksPartition2Label->setText("---");
        ui->blockSizePartition2Label->setText("---");
        ui->defragPartition2Label->setText("---");
        return;
    }

    //Partition 1
    ui->partition1GroupBox->setTitle(m_disk->partitions[0]->getName() + " (" + m_disk->partitions[0]->typeString() + ")" );
    ui->sizePartition1Label->setText(QString::number(m_disk->partitions[0]->size()) + " GB");
    ui->freeBlocksPartition1Label->setText(QString::number(m_disk->partitions[0]->freeBlocks()));
    ui->blockSizePartition1Label->setText(QString::number(m_disk->partitions[0]->blockSize()));
    ui->defragPartition1Label->setText(QString::number(m_disk->partitions[0]->fragmentation())+ " %");


    if(m_disk->numPartitions() == 1){

        //Partition 2
        ui->partition2GroupBox->setTitle("Partition 2");
        ui->sizePartition2Label->setText("---");
        ui->freeBlocksPartition2Label->setText("---");
        ui->blockSizePartition2Label->setText("---");
        ui->defragPartition2Label->setText("---");
        return;
    }

    //Partition 2
    ui->partition2GroupBox->setTitle(m_disk->partitions[1]->getName() + " (" + m_disk->partitions[1]->typeString() + ")" );
    ui->sizePartition2Label->setText(QString::number(m_disk->partitions[1]->size()) + " GB");
    ui->freeBlocksPartition2Label->setText(QString::number(m_disk->partitions[1]->freeBlocks()));
    ui->blockSizePartition2Label->setText(QString::number(m_disk->partitions[1]->blockSize()));
    ui->defragPartition2Label->setText(QString::number(m_disk->partitions[1]->fragmentation()) + " %");
    return;


}

void MainWindow::defragPartition1(){
    if(m_disk == nullptr || m_disk ->numPartitions() == 0){

        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please create the Partition first");
        box.exec();
        return;
    }

    m_disk->partitions[0]->defrag();
    updateGUI();
}
void MainWindow::defragPartition2(){
    if(m_disk == nullptr || m_disk ->numPartitions() != 2){

        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please create the Partition first");
        box.exec();
        return;
    }

    m_disk->partitions[1]->defrag();
    updateGUI();
}

