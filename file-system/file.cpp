#include "file.h"



int File::m_fileIndexCounter = 0;

File::File(QString name, QString typ, int size, bool status, QString creator):Entry(name, false),m_name(name), m_typ(typ), m_size(size), m_status(status), m_creator(creator){

    m_item->setText(1, QString::number(m_size));
    m_fileIndex = m_fileIndexCounter++;
}

QString File::name() const
{
    return m_name;
}

void File::setName(const QString &name)
{
    m_name = name;
}

QString File::typ() const
{
    return m_typ;
}

void File::setTyp(const QString &typ)
{
    m_typ = typ;
}

int File::size() const
{
    return m_size;
}

void File::setSize(int size)
{
    m_size = size;
}

bool File::status() const
{
    return m_status;
}

void File::setStatus(bool status)
{
    m_status = status;
}

QString File::creator() const
{
    return m_creator;
}

void File::setCreator(const QString &creator)
{
    m_creator = creator;
}

QString File::toString(){
    QString fileString = "File{";
    fileString += m_name + ";";
    fileString += m_typ + ";";
    fileString += QString::number(m_size) + ";";
    fileString += QString::number(m_status) + ";";
    fileString += m_creator + "}";

    return fileString;

}

int File::fileIndex() const
{
    return m_fileIndex;
}

void File::setFileIndex(int newFileIndex)
{
    m_fileIndex = newFileIndex;
}

std::ostream& operator<<(std::ostream& os, const File file){
    os << "File{" << file.m_name.constData() << ";" << file.m_typ.constData() << ";" << file.m_size << ";" << file.m_status << ";" << file.m_creator.constData() << "}";
        return os;
}
