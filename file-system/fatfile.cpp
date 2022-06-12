#include "fatfile.h"



int FatFile::startIndex() const
{
    return m_startIndex;
}

void FatFile::setStartIndex(int startIndex)
{
    m_startIndex = startIndex;
}
