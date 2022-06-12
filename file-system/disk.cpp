#include "disk.h"



Disk::Disk(int size, QTableWidget* diskTable){

    m_size = size;
    m_table = diskTable;
    m_numPartitions = 0;
    m_unallocatedSpace = size - 1;


    startBlockPartition1 = 0;
    startBlockPartition2 = 0;
    endBlockPartition1 = 0;
    endBlockPartition2 = 0;

    fillDisk();


}

Disk::~Disk(){
    m_numPartitions = 0;
    m_table->setRowCount(0);

    delete(partitions[0]);
    delete(partitions[1]);

}

int Disk::numPartitions() const
{
    return m_numPartitions;
}

void Disk::setNumPartitions(int newNumPartitions)
{
    m_numPartitions = newNumPartitions;
}




int Disk::size() const
{
    return m_size;
}

void Disk::setSize(int size)
{
    m_size = size;
}


void Disk::fillBlock(int index, QString text, QBrush color){

    QTableWidgetItem* item = new QTableWidgetItem;
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    m_table->setItem(0, index, item);
    item->setText(text);
    m_table->item(0, index)->setBackground(color);

}

void Disk::fillDisk(){

    fillBlock(0, "MBR", Qt::gray);

    for(int i = 1; i < 20; i++)

        if(i <= endBlockPartition1 && i >= startBlockPartition1){
            fillBlock(i, partitions[0]->getName(), Qt::yellow);
        }
        else if(i <= endBlockPartition2 && i >= startBlockPartition2){
            fillBlock(i, partitions[1]->getName(), Qt::blue);
        }else{
            fillBlock(i, "Free", Qt::transparent);
        }

}

int Disk::unallocatedSpace() const{
    return m_unallocatedSpace;
}

void Disk::addPartition(QString name, int partitionSize, int blockSize, int type, bool status, QTableWidget* table){


    m_unallocatedSpace = m_unallocatedSpace - partitionSize;
    if(type == 0){
        partitions[m_numPartitions] = new FatPartition(name, partitionSize, status, blockSize, table);

       }else{
        partitions[m_numPartitions] = new InodePartition(name, partitionSize, status, blockSize, table);

    }

    int blocksPartition = (int) floor((float) partitionSize / m_size * 19);

    if(m_numPartitions == 0){
        startBlockPartition1 = 1;
        endBlockPartition1 = 1 + blocksPartition;

    }else{
        startBlockPartition2 = endBlockPartition1 + 1;
        endBlockPartition2 = startBlockPartition2 + blocksPartition;
   }

   fillDisk();
   m_numPartitions++;


}

void Disk::removePartition(){

    int current = m_numPartitions;
    m_unallocatedSpace = m_unallocatedSpace + partitions[current-1]->size();

    if(current == 1){
        startBlockPartition1 = 0;
        endBlockPartition1 = 0;
    }else{
        startBlockPartition2 = 0;
        endBlockPartition2 = 0;
    }

    fillDisk();
    m_numPartitions--;


}



