#include "inodepartition.h"




void InodePartition::addFile(QString path, File* f){

    qDebug() << "Adding a file:" << Qt::endl;
    int fileBlocks = (int) ceil((double)f->size() / m_blockSize);


    if(m_freeBlocks < fileBlocks){
        qDebug() << "There is no enough space." << Qt::endl;
        return;
    }

    m_freeBlocks -= fileBlocks;
    qDebug() << "Path to file: " << path << Qt::endl;
    Directory* dir = getDirectory(path);
    qDebug() << "Check point"<< Qt::endl;

    dir->addFile(f);

    //cast to FatFile
    InodeFile* inodeFile = (InodeFile*) f;

    //special inode section

    //end special fat section

    /* initialize random seed: */
    srand (time(NULL));

    for(int counter = 0; counter < fileBlocks;){

       int blockIndex = rand() % m_numBlocks;
       Block* current = getBlock(blockIndex);

       if(current->status() == Block::blockStatus::Free){
            current->writeBlock(QString::number(inodeFile->fileIndex()));

            //special inode section
            inodeFile->addIndex(blockIndex);
            //end special fat section

            counter++;
        }
    }

     qDebug() << "First CheckPoint inoteTable length:" << inodeFile->length() << Qt::endl;
    calulateFragmentation();
}

void InodePartition::deleteFile(QString filePath){

    File* f = getFile(filePath);
    if(f == nullptr){
        qDebug() << "Error: File does not exist or path is invalid " << Qt::endl;
        return;
    }

    int fileBlocks = (int) ceil((double)f->size() / m_blockSize);
    m_freeBlocks += fileBlocks;
    Directory* dir = getDirectory(filePath);
    dir->removeFile(f);

    //cast to FatFile
    InodeFile* inodeFile = (InodeFile*) f;



    for(int i = 0; i < inodeFile->length(); i++){

        Block* current = getBlock(inodeFile->itemAt(i));
        current->freeBlock();

    }
    delete(inodeFile);
    calulateFragmentation();
}



void InodePartition::deleteDirectory(QString path){

    Directory* dp = getDirectory(path);

    //Delete all files within the directory
    QList<Entry*> list = dp->getEntryList();
    for(Entry* entry : list){
        QString filePath = path + "/" + entry->name();
        deleteFile(filePath);
    }

    m_rootDirectory->deleteDirectory(dp);
    calulateFragmentation();
}



void InodePartition::moveFileToFront(Entry* fp){

    InodeFile* inodeFile = (InodeFile*) fp;

    int blockindex;



    qDebug() << "First CheckPoint inoteTable length:" << inodeFile->length()<< Qt::endl;
    qDebug() << "First item: " << inodeFile->itemAt(0) << Qt::endl;
    for(int i = 0; i < inodeFile->length(); i++){

        //get index
        blockindex = getFirstFreeBlock();


        //set Block occupied
        getBlock(blockindex)->writeBlock(QString::number(inodeFile->fileIndex()));

                qDebug() << "First free Block: " << blockindex << Qt::endl;

        //set Block free
        getBlock(inodeFile->itemAt(i))->freeBlock();

                        qDebug() << "CheckPoint1"  << Qt::endl;

        //update file
        inodeFile->setItemAt(i, blockindex);
                                qDebug() << "CheckPoint1"  << Qt::endl;

    }
}
