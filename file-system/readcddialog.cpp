#include "readcddialog.h"
#include "ui_readcddialog.h"
#import "QDir"
#import "QStandardPaths"
#import "QMessageBox"
#import "QCheckBox"
#import "QHBoxLayout"



readCdDialog::readCdDialog(QWidget *parent, Disk* disk) :
    QDialog(parent),
    ui(new Ui::readCdDialog),
    m_disk(disk)
{

    ui->setupUi(this);
    this->setWindowTitle("");
    ui->fileTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    for(int i = 0; i < m_disk->numPartitions(); i++){
            ui->partitionComboBox->addItem(m_disk->partitions[i]->getName());
    }
    ui->partitionComboBox->setCurrentIndex(-1);

    connect(ui->readCDButton, &QPushButton::clicked, this, &readCdDialog::readCD);
    connect(ui->fileNameComboBox, &QComboBox::currentIndexChanged, this, &readCdDialog::setFilePath);
    connect(ui->copyFileButton, &QPushButton::clicked, this, &readCdDialog::copyFiles);
    connect(ui->partitionComboBox, &QComboBox::currentIndexChanged, this, &readCdDialog::setPartitionType);

    desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    qDebug() << desktopPath << Qt::endl;

    //assume the directory exists and contains some files and you want all jpg and JPG files
    QDir directory(desktopPath);
    QStringList files = directory.entryList(QStringList() << "CD*.txt" ,QDir::Files);

    foreach(QString filename, files) {
        ui->fileNameComboBox->addItem(filename);
    }
}

readCdDialog::~readCdDialog()
{
    delete ui;
}


void readCdDialog::readCD(){

    if(ui->partitionComboBox->currentIndex() == -1){
        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please select a partition first");
        box.exec();
        return;
    }
    ui->partitionComboBox->setEnabled(false);


    m_files.clear();

    QFile file = QFile(desktopPath + "\\" + filePath);

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        if(line.startsWith("|")){
            qDebug() << line << Qt::endl;
            continue;
        }
        stringToFile(line);

    }

    file.close();
    createTable();
    for(File* f : m_files){
        qDebug() << f->toString() << Qt::endl;
    }
}

void readCdDialog::setFilePath(){
    filePath = ui->fileNameComboBox->currentText();
    ui->fileTable->setRowCount(0);
}

void readCdDialog::stringToFile(QString fileString){
    fileString = fileString.mid(5,-1);
    fileString = fileString.replace("}", "");
    qDebug() << fileString << Qt::endl;
    QStringList attributes = fileString.split(";");

    File* testFile;
    if(m_partitionType == Partition::partitionType::Fat){

        testFile = (File*) new FatFile(attributes[0], attributes[1], attributes[2].toInt(), (bool) attributes[3].toInt(), attributes[4]);

    }else{

        testFile = (File*) new InodeFile(attributes[0], attributes[1], attributes[2].toInt(), (bool) attributes[3].toInt(), attributes[4]);
    }
    m_files.append(testFile);
}

void readCdDialog::createTable(){

    ui->fileTable->setRowCount(0);
    ui->fileTable->setRowCount(m_files.length());
    for(int i = 0; i < m_files.length(); i++){
        ui->fileTable->setItem(i, 0, new QTableWidgetItem(m_files[i]->name()));
        ui->fileTable->setItem(i, 1, new QTableWidgetItem(QString::number(m_files[i]->size())));
        QCheckBox* checkBox = new QCheckBox();
        ui->fileTable->setCellWidget(i,2,checkBox);
    }

}

void readCdDialog::copyFiles(){



    if(ui->partitionComboBox->currentIndex() == -1){
        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please select a partition first");
        box.exec();
        qDebug() << "Please select a partition first" << Qt::endl;
        return;
    }
    int partitionIndex = ui->partitionComboBox->currentIndex();

    for(int i = 0; i < ui->fileTable->rowCount(); i++){
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(ui->fileTable->cellWidget(i, 2));
        if(checkBox->isChecked()){


            m_disk->partitions[partitionIndex]->addFile(m_disk->partitions[partitionIndex]->getName() + "/", m_files[i]);
        }
    }

    //reset Window and Data

    ui->fileTable->setRowCount(0);

    ui->partitionComboBox->setEnabled(true);

    ui->fileNameComboBox->setCurrentIndex(-1);

    ui->partitionComboBox->setCurrentIndex(-1);
    qDebug() << "resetting" << Qt::endl;

    m_files.clear();
}

void readCdDialog::setPartitionType(){

    if(ui->partitionComboBox->currentIndex() == -1){
        return;
    }
    int partitionIndex = ui->partitionComboBox->currentIndex();
    m_partitionType = m_disk->partitions[partitionIndex]->type();
}
