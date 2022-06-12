#include "rootdirectory.h"

RootDirectory::RootDirectory(QString name):Directory(name)
{

}


void RootDirectory::addDirectory(Directory* dir){

    //check if directory name exists
    for(Entry* entry: m_entryList){
        if(!QString::compare(entry->name(), dir->name())){

            qDebug() << "Error: Name already exists" << Qt::endl;
            free(dir);
            return;
        }
    }

    Entry* entry = dir;
    m_entryList.push_back(entry);

}



Directory* RootDirectory::getDirectory(QString folderName){

    Directory* dp = nullptr;

    for(Entry* e : m_entryList){
        if(!QString::compare(e->name(), folderName)){
            if(e->isDirectory() == true){
                dp = (Directory*) e;
            }
        }
    }
    return dp;
}

void RootDirectory::deleteDirectory(Directory* dir){

    QString folderName = dir->name();
    for(int i = 0; i < m_entryList.length(); i++){
        if(!QString::compare(m_entryList[i]->name(), folderName)){
            if(m_entryList[i]->isDirectory() == true){
                m_entryList.remove(i);
                delete dir;
                return;
            }
        }
    }


}
