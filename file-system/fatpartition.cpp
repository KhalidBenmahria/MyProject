#include "fatpartition.h"
#include <iostream>
#include <random>
#include <QDebug>


FatPartition::FatPartition(QString name, int size, bool status, int blockSize, QTableWidget* table):
    Partition(name, size, status, blockSize, table, partitionType::Fat){

    m_fatTable = new int[m_numBlocks];

    for(int i = 0; i < m_numBlocks; i++){
        m_fatTable[i] = -1;
    }

};

FatPartition::~FatPartition(){

    for(int i = m_numBlocks-1; i >= 0; i++){
        delete(getBlock(i));
    }
}

void FatPartition::addFile(QString path, File* f){



    qDebug() << "Adding a file:" << Qt::endl;
    int fileBlocks = (int) ceil((double)f->size() / m_blockSize);


    if(m_freeBlocks < fileBlocks){
        qDebug() << "There is no enough space." << Qt::endl;
        return;
    }

    m_freeBlocks -= fileBlocks;
    qDebug() << "Path to file: " << path << Qt::endl;
    Directory* dir = getDirectory(path);


    dir->addFile(f);

    //cast to FatFile
    FatFile* fatFile = (FatFile*) f;


    /* initialize random seed: */
    srand (time(NULL));


    int prevBlockIndex = -2;
    for(int counter = 0; counter < fileBlocks;){

       int blockIndex = rand() % m_numBlocks;
       Block* current = getBlock(blockIndex);

       if(current->status() == Block::blockStatus::Free){
            current->writeBlock(QString::number(fatFile->fileIndex()));

            //special fat section
            if(counter == 0){
                fatFile->setStartIndex(blockIndex);

           }else{
                m_fatTable[prevBlockIndex] = blockIndex;
            }
            prevBlockIndex = blockIndex;
            //end special fat section

            counter++;
        }
    }

    qDebug() << "File "<< fatFile->fileIndex() << ": first block = " << fatFile->startIndex() << Qt::endl;
    printfFatTable();
}

void FatPartition::printfFatTable(){

    qDebug() << "   index   |   value   " << Qt::endl;
    qDebug() << "-----------|-----------" << Qt::endl;
    for(int i = 0; i < m_numBlocks; i++){
        if(i >= 10){
            qDebug() << "  "<< i << "     |     " << m_fatTable[i] << Qt::endl;
            continue;
        }
        qDebug() << "   "<< i << "     |     " << m_fatTable[i] << Qt::endl;

    }
    calulateFragmentation();
}


void FatPartition::deleteFile(QString filePath){

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
    FatFile* fatFile = (FatFile*) f;

    int nextIndex = fatFile->startIndex();
    int helper = 0;

    while(nextIndex != -1){

        Block* current = getBlock(nextIndex);
        current->freeBlock();
        helper = m_fatTable[nextIndex];
        m_fatTable[nextIndex] = -1;
        nextIndex = helper;
    }
    delete(fatFile);
}



void FatPartition::deleteDirectory(QString path){

    Directory* dp = getDirectory(path);

    //Delete all files within the directory
    QList<Entry*> list = dp->getEntryList();
    for(Entry* entry : list){
        QString filePath = path + "/" + entry->name();
        deleteFile(filePath);
    }

    m_rootDirectory->deleteDirectory(dp);
    calulateFragmentation();

};



void FatPartition::moveFileToFront(Entry* fp){

    FatFile* fatFile = (FatFile*) fp;

    int blockindex;
    int current = fatFile->startIndex();
    qDebug() << "File: " << fatFile->fileIndex() << " first BlockIndex: " << current << Qt::endl;

        blockindex = getFirstFreeBlock();
        getBlock(blockindex)->writeBlock(QString::number(fatFile->fileIndex()));
        getBlock(current)->freeBlock();

        fatFile->setStartIndex(blockindex);


    if(m_fatTable[current] == -1){

        qDebug() << "current: " << current << ", next: " << m_fatTable[current] << Qt::endl;
        return;
    }

    while(current != -1){
        blockindex = getFirstFreeBlock();
        getBlock(current)->freeBlock();
        getBlock(blockindex)->writeBlock(QString::number(fatFile->fileIndex()));
        m_fatTable[blockindex] = m_fatTable[current];
        m_fatTable[current] = -1;
        current = m_fatTable[blockindex];

    }
}
