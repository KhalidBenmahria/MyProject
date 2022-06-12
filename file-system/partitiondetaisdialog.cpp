#include "partitiondetaisdialog.h"
#include "ui_partitiondetaisdialog.h"
#include <QList>
#include "directory.h"
#include "deletedialog.h"
#include <QLatin1Char>



PartitionDetaisDialog::PartitionDetaisDialog(QWidget *parent, Partition* partition) :
    QDialog(parent),ui(new Ui::PartitionDetaisDialog), m_partition(partition)
{
    ui->setupUi(this);
    generateTreeView(partition->rootDirectory());
    connect(ui->addFileButton, &QPushButton::clicked, this, &PartitionDetaisDialog::addFillButtonClicked);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

PartitionDetaisDialog::~PartitionDetaisDialog()
{
    delete ui;
}

void PartitionDetaisDialog::generateTreeView(Directory* rootDirectory){



    QList <QStandardItem*> list;
    QStandardItem* item = new QStandardItem(m_partition->getName());
    item->setColumnCount(4);
    ui->treeView->reset();

    QStringList labels = {"Name", "Type", "Size", "Creator"};
    m_model.setHorizontalHeaderLabels(labels);

    for (int i = 0; i <rootDirectory->getEntryList().length(); i++){


        if(rootDirectory->getEntryList().at(i)->isDirectory() == true){

             QStandardItem* dirItem = new QStandardItem(rootDirectory->getEntryList().at(i)->name() + "/");
             QList <QStandardItem*> dirList = {dirItem};

             Directory* dir = (Directory*)rootDirectory->getEntryList().at(i);
              if(dir->getEntryList().length() != 0){

                  for(Entry* e: dir->getEntryList()){

                      QList <QStandardItem*> filInDirlist = {new QStandardItem(((File*)e)->name()),new QStandardItem(((File*)e)->typ()), new QStandardItem(QString::number(((File*)e)->size())), new QStandardItem(((File*)e)->creator())};
                      qDebug()<<((File*)e)->size()<<Qt::endl;
                      dirItem->appendRow(filInDirlist);

                 }

              }
              item->appendRow(dirList);


        }else{

            QList <QStandardItem*> filList = {new QStandardItem(rootDirectory->getEntryList().at(i)->name()), new QStandardItem(((File*)rootDirectory->getEntryList().at(i))->typ()), new QStandardItem(QString::number(((File*)rootDirectory->getEntryList().at(i))->size())), new QStandardItem(((File*)rootDirectory->getEntryList().at(i))->creator())};
            item->appendRow(filList);

        }

    }

    list.push_back(item);

    m_model.appendRow(list);


    ui->treeView->setModel(&m_model);
    ui->treeView->expandAll();


}

const QStandardItemModel &PartitionDetaisDialog::model() const
{
    return m_model;
}


void PartitionDetaisDialog::addFillButtonClicked()
{


    CreatFileDialog* dialog = new CreatFileDialog(nullptr, m_partition);

    File* createdFile;
    if(dialog->exec() == QDialog::Accepted){
        int fileBlocks = (int) ceil((double)dialog->size() / m_partition->blockSize());
        qDebug() << "file size: " <<(double) dialog->size() << Qt::endl;
        qDebug() << "fileBlocks: " << fileBlocks << Qt::endl;
        qDebug() << "partition size " << m_partition->size() << Qt::endl;

        if(fileBlocks > m_partition->freeBlocks()){
            QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning", "There is no enough space.");
            box.exec();
            return;

        }


        if(dialog->name() != nullptr || dialog->creator() != nullptr|| fileBlocks <= m_partition->blockSize()){
             qDebug() << "file Size = " << dialog->size();

            if(m_partition->type() == Partition::partitionType::Fat){

                createdFile = new FatFile(dialog->name(), "FAT", dialog->size(), true, dialog->creator());

            }else {
                createdFile = new InodeFile(dialog->name(), "INODE", dialog->size(), true, dialog->creator());

            }
            m_partition->addFile(dialog->path(),createdFile);

        }else{


            QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning", "please enter a vaild name or creator");
            box.exec();
            return;

        }


    }

}





void PartitionDetaisDialog::on_addFolderButton_clicked()
{
    CreateFolderDialog* dialog = new CreateFolderDialog(nullptr, m_partition);
    //dialog->exec();
    if(dialog->exec() == QDialog::Accepted){
        if(dialog->name() != nullptr){
            Directory* createdDir = new Directory(dialog->name());
            //name, typ, size, status, creato
            //File* file = new File("hii", "INODE",30, true, "Sara SAlha");
            //createdDir->addFile(file);
            m_partition->addDirectory(createdDir);

        }else{
            QMessageBox box = QMessageBox(QMessageBox::Icon::Warning, "Warning", "please enter a valid name before creating a folder");
            box.exec();
            return;
        }

    }

}


void PartitionDetaisDialog::on_deleteButton_clicked()
{
    deleteDialog* dialog = new deleteDialog(nullptr, m_partition);

    if(dialog->exec() == QDialog::Accepted){
        QString path = dialog->path();
        int pathLength = path.length()-1;
         //qDebug() << pathLength<< Qt::endl;

         //QString type = m_partition->fileList();


         if(((path.at(pathLength)) == QLatin1Char('/'))){

             m_partition->deleteDirectory(path);


         }else{
              m_partition->deleteFile(path);
         }

    }

}

