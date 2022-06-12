#include "block.h"

Block::Block(int index, blockStatus status, QString data){

    m_index = index;
    m_status = status;
    m_data = data;

    m_item = new QTableWidgetItem();
    m_item->setFlags(m_item->flags() ^ Qt::ItemIsEditable);
    m_item->setText(data);
    m_item->setBackground(Qt::green);

}

Block::~Block(){
    free(m_item);
}

void Block::writeBlock(QString data){

    m_data = data;
    m_status = Block::blockStatus::Occupied;
    m_item->setText(m_data);
    m_item->setBackground(Qt::red);
}

void Block::freeBlock(){

    qDebug() << "CheckPoint9" << Qt::endl;
    m_data = "F";
    m_status = Block::Free;
    m_item->setText(m_data);
    m_item->setBackground(Qt::green);
}


Block *Block::nextBlock() const
{
    return m_nextBlock;
}

void Block::setNextBlock(Block *nextBlock)
{
    m_nextBlock = nextBlock;
}

Block *Block::prevBlock() const
{
    return m_prevBlock;
}

void Block::setPrevBlock(Block *prevBlock)
{
    m_prevBlock = prevBlock;
}

int Block::index() const
{
    return m_index;
}

void Block::setIndex(int index)
{
    m_index = index;
}

QString Block::data() const
{
    return m_data;
}

void Block::setData(const QString &data)
{
    m_data = data;
}

QTableWidgetItem *Block::item() const
{
    return m_item;
}

void Block::setItem(QTableWidgetItem *newItem)
{
    m_item = newItem;
}

Block::blockStatus Block::status() const
{
    return m_status;
}

void Block::setStatus(blockStatus newStatus)
{
    m_status = newStatus;
}


