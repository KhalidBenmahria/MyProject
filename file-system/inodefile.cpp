#include "inodefile.h"


int InodeFile::length(){
    return  m_inodeTable.length();
}
int InodeFile::itemAt(int index){

    return m_inodeTable[index];
}
void InodeFile::setItemAt(int index, int item){

    m_inodeTable[index] = item;

}

void InodeFile::addIndex(int index){

    m_inodeTable.push_back(index);
}
