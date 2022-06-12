#include "writecddialog.h"
#include "ui_writecddialog.h"
#include "QMessageBox"
#include "QStandardPaths"
#include "QCheckBox"
#include "QFile"

writeCdDialog::writeCdDialog(QWidget *parent, Disk* disk) :
    QDialog(parent),
    ui(new Ui::writeCdDialog)
{
    ui->setupUi(this);

    m_disk = disk;

    m_sizeLeft = m_maxSize;
    m_tree = ui->treeWidget;


    ui->nameLineEdit->setMaxLength(5);
    //ui->fileTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i = 0; i < disk->numPartitions(); i++){
        ui->partitionComboBox->addItem(disk->partitions[i]->getName());
    }
    ui->partitionComboBox->setCurrentIndex(-1);

    connect(ui->partitionComboBox, &QComboBox::currentIndexChanged, this, &writeCdDialog::generateTree);
    connect(ui->writeCDButton, &QPushButton::clicked, this, &writeCdDialog::writeCd);
    connect(ui->treeWidget, &QTreeWidget::itemChanged, this, &writeCdDialog::handleItemChanged);

    desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);


}

writeCdDialog::~writeCdDialog()
{
    delete ui;
}

void writeCdDialog::generateTree(){

    //reset GUI and settings
    m_tree->clear();
    m_files.clear();
    m_sizeLeft = m_maxSize;


    m_partition = m_disk->partitions[ui->partitionComboBox->currentIndex()];
    QTreeWidgetItem* ip = new QTreeWidgetItem();
    ip->setText(0, m_partition->getName() + "/");

    //generate rootitem
    QList<Entry*> rootList = m_partition->rootDirectory()->getEntryList();

    for(Entry* ep : rootList){
        if(ep->isDirectory()){
            ip->addChild(generateDirectory(ep));

        }else{
            File* fp = (File*) ep;
            QTreeWidgetFile* file = new QTreeWidgetFile(fp);
            file->setText(0, fp->name());
            file->setText(1, QString::number(fp->size()));
            file->setCheckState(2, Qt::Unchecked);
            ip->addChild(file);
        }
    }

    m_tree->addTopLevelItem(ip);
    m_tree->expandAll();
}


QTreeWidgetItem* writeCdDialog::generateDirectory(Entry* ep){

    QTreeWidgetItem* directoryItem = new QTreeWidgetItem();
    directoryItem->setText(0, ep->name() + "/");
    Directory* dp = (Directory*) ep;
    for(Entry* entryPointer : dp->getEntryList()){
        File* fp = (File*) entryPointer;
        QTreeWidgetFile* ip = new QTreeWidgetFile(fp);
        ip->setText(0, fp->name());
        ip->setText(1, QString::number(fp->size()));
        ip->setCheckState(2, Qt::Unchecked);
        directoryItem->addChild(ip);
    }
    return directoryItem;
}



void writeCdDialog::writeCd(){

    if(m_sizeLeft < 0){
        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Too many files selected");
        box.exec();
        return;
    }



    if(ui->nameLineEdit->text() == ""){
        QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning","Please enter a name first");
        box.exec();
        qDebug() << "Please enter a name first" << Qt::endl;
        return;

    }


    int blockCounter = 0;
    QString path = desktopPath + "\\CD" + ui->nameLineEdit->text() + ".txt";
    QString cdContent = "";
    QString blockString = "|";
    for(File* fp : m_files){
        cdContent += fp->toString() + "\n";
        for(int i = 0; i < fp->size(); i++){
            blockString += QString::number(fp->fileIndex()) +   "|";
            blockCounter++;
        }

    }

    for(;blockCounter < m_maxSize; blockCounter++){
        blockString += "F|";
    }

    blockString += "\n";

    QFile file( path );
    file.resize(0);
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << blockString;
        stream << cdContent;
    }

    QMessageBox box = QMessageBox(QMessageBox::Icon::Information, "Information", "CD" + ui->nameLineEdit->text() + " has been created");
    box.exec();

}

void writeCdDialog::handleItemChanged(QTreeWidgetItem* item, int column){


    if(item->checkState(column) == Qt::Checked){
        QTreeWidgetFile* tp = (QTreeWidgetFile*) item;
        QString name = tp->file()->name();
        m_files.push_back(tp->file());
        m_sizeLeft -= tp->file()->size();
        qDebug() << name <<  " is checked" << Qt::endl;
    }else{
        QTreeWidgetFile* tp = (QTreeWidgetFile*) item;
        QString name = tp->file()->name();
        m_sizeLeft += tp->file()->size();
        for(int i = 0; i < m_files.length(); i++){
            if(m_files[i] == tp->file()){
                m_files.remove(i);
            }
        }
        qDebug() << name <<  " is unchecked" << Qt::endl;
    }
}

