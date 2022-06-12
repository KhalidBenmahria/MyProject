#include "directory.h"


Directory::Directory(QString name): Entry(name, true){

    m_item->setText(1, "/");
}

const QList<Entry *> &Directory::getEntryList() const
{
    return m_entryList;
}

void Directory::setEntryList(const QList<Entry *> &newEntryList)
{
    m_entryList = newEntryList;
}


void Directory::addFile(File* file){

    //Directories can't be added to a normal Directory
    if(file->isDirectory() == true){
        return;
    }

    //item()->addChild(file->item());

    Entry* entry = (Entry*) file;

    m_entryList.push_back(entry);
}

void Directory::removeFile(File* entry){

    for(int index = 0; index < m_entryList.length(); index++){

        if(m_entryList[index] == entry){
            m_entryList.remove(index);
        }
    }
}

File* Directory::getFile(QString filename){

    for(Entry* entry : m_entryList){
        if(!QString::compare(entry->name(), filename)){
            return (File*) entry;
        }
    }
    return nullptr;
}
