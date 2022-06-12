#include "partition.h"



Partition::Partition(QString name, int size, bool status, int blockSize, QTableWidget* table, partitionType type)
{

    m_type = type;
    m_size = size;
    m_status = status;
    m_blockSize = blockSize;
    m_table = table;
    m_numBlocks = (size / blockSize);
    m_freeBlocks = m_numBlocks;
    m_name = name;
    m_rootDirectory = new RootDirectory("root");
    m_treeWidget = new QTreeWidget();
    m_fragmentation = 0;


    //1st Block
    m_blockList = new Block(0, Block::blockStatus::Free, "F");
    Block* previous = m_blockList;

    //all other blocks
    for(int i = 1; i < m_numBlocks; i++){
        Block* currentBlock = new Block(i, Block::blockStatus::Free, "F");
        if(i == m_numBlocks - 1){

        }
        previous->setNextBlock(currentBlock);
        currentBlock->setPrevBlock(previous);
        if(i == m_numBlocks - 1){
         currentBlock->setNextBlock(nullptr);
        }
        previous = currentBlock;
    }

    fillTable();

}


int Partition::numBlocks() const
{
    return m_numBlocks;
}

void Partition::setNumBlocks(int numBlocks)
{
    m_numBlocks = numBlocks;
}

int Partition::size() const {
    return m_size;
}




void Partition::fillTable(){

    Block* current = m_blockList;
    for(int i = 0; i < m_numBlocks; i++){

        m_table->setItem(0, i, current->item());
        current = current->nextBlock();
    }
}

int Partition::freeBlocks() const
{
    return m_freeBlocks;
}

void Partition::setFreeBlocks(int newFreeBlocks)
{
    m_freeBlocks = newFreeBlocks;
}



int Partition::blockSize() const
{
    return m_blockSize;
}

void Partition::setBlockSize(int newBlockSize)
{
    m_blockSize = newBlockSize;
}

const QString &Partition::getName() const
{
    return m_name;
}

void Partition::setName(const QString &newName)
{
    m_name = newName;
}

const QList<File> &Partition::fileList() const
{
    return m_fileList;
}

void Partition::setFileList(const QList<File> &newFileList)
{
    m_fileList = newFileList;
}

QTableWidget *Partition::table() const
{
    return m_table;
}

void Partition::setTable(QTableWidget *newTable)
{
    m_table = newTable;
}


/**
 * @brief Partition::getDirectory
 * @param path: The path to a directory or to a file eg.: C:/usr/test.txt
 * @return The directory
 */
Directory* Partition::getDirectory(QString path){

    QList<QString> pathList = path.split("/");

    //remove empty item: ""
    for(int i = 0; i < pathList.length(); i++){
        if(!QString::compare(pathList[i], "")){
                pathList.remove(i);
        }
        //qDebug() << "Check0:" << pathList[i] << Qt::endl;
    }

     //check if partition Name is correct : C:
    if(QString::compare(m_name, pathList[0])){
        qDebug() << "Check1"<< Qt::endl;
        return nullptr;


        //
    }else if(pathList.length() == 1){
        qDebug() << "Check2"<< Qt::endl;
        return m_rootDirectory;

    }else if(pathList.length() == 2){

        //sepereation between C:/test/ and C:/test.txt
        if(path.lastIndexOf("/") == (path.length()-1)){
            qDebug() << "Check3"<< Qt::endl;
            return m_rootDirectory->getDirectory(pathList[1]);;
        }
        qDebug() << "Check3"<< Qt::endl;
        return m_rootDirectory;

    }else{
        qDebug() << "Check4"<< Qt::endl;
        return m_rootDirectory->getDirectory(pathList[1]);
    }

}


void Partition::addDirectory(Directory* f){

    m_rootDirectory->addDirectory(f);

}

Block* Partition::getBlock(int index){

    if(index > m_numBlocks){
        qDebug() << "getBlock: Index out of range";
        return nullptr;
    }
    Block* current = m_blockList;
    for(int i = 0; i < index; i++){

        current = current->nextBlock();
    }
    return current;
}

int Partition::fragmentation() const
{
    return m_fragmentation;
}

Partition::partitionType Partition::type() const
{
    return m_type;
}

QTreeWidget *Partition::treeWidget() const
{
    return m_treeWidget;
}

void Partition::setTreeWidget(QTreeWidget *newTreeWidget)
{
    m_treeWidget = newTreeWidget;
}

RootDirectory *Partition::rootDirectory() const
{
    return m_rootDirectory;
}

void Partition::setRootDirectory(RootDirectory *newRootDirectory)
{
    m_rootDirectory = newRootDirectory;
}

File* Partition::getFile(QString filePath){


    //File* fp = nullptr;
    QList<QString> pathList = filePath.split("/");
    Directory* dp = getDirectory(filePath);


    qDebug() << "Filename: " << pathList.last() << Qt::endl;
    return dp->getFile(pathList.last());
}

void Partition::addDirectory(QString name){

    Directory* dp = new Directory(name);
    m_rootDirectory->addDirectory(dp);

};

QString Partition::typeString(){
    if(m_type == partitionType::Fat)
        return "FAT";
    else{
        return "INODE";
    }

}

void Partition::calulateFragmentation(){
    int free = m_freeBlocks;
    //If there are no free Blocks
    if(m_freeBlocks == 0){
        m_fragmentation = 100;
        return;
    }

       float freemax = 0;
       float counter = 0;
       for(int i = 0; i < m_numBlocks; i++){

          if(getBlock(i)->status() == Block::blockStatus::Free){
              counter++;
              if(counter > freemax){
                  freemax = counter;
              }
          }else{
              counter = 0;
          }
       }
       //m_fragmentation = (int) (((free - freemax) / free) * 100);
       m_fragmentation = (int) ((freemax / free) * 100);

}

int Partition::getFirstFreeBlock(){

    Block* bp;
    for(int i = 0; i < m_numBlocks; i++){
        bp = getBlock(i);
        if(bp->status() == Block::Free){
            return i;
        }
    }
    return -1;
}
int Partition::getLastFreeBlock(){
    Block* bp;
    for(int i = (m_numBlocks-1); i >= 0; i--){
        bp = getBlock(i);
        if(bp->status() == Block::Free){
            return i;
        }
    }
    return -1;

}

void Partition::defrag(){

    qDebug() << "Defrag INODE" << Qt::endl;

   for(Entry * ep : m_rootDirectory->getEntryList()){

           qDebug() << "Defrag INODE1" << Qt::endl;
       if(ep->isDirectory()){
           Directory* dp = (Directory*) ep;
           for(Entry * directoryItem : dp->getEntryList()){
               //move file to back
               moveFileToFront(directoryItem);
           }
        }else{
           //move file to back
           moveFileToFront(ep);


       }
   }
   calulateFragmentation();
}






