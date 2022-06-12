#ifndef FILE_H
#define FILE_H

#include <QString>
#include <iostream>
#include "entry.h"
/**
 * @brief This class represents a file
 */

class File: public Entry
{
public:
    /**
     * @brief File Constructor
     * @param name
     * @param typ
     * @param size
     * @param status
     * @param creator
     */
    File(QString name, QString typ, int size, bool status, QString creator);
    // Setter and Getter
    QString name() const;
    void setName(const QString &name);
    QString typ() const;
    void setTyp(const QString &typ);
    int size() const;
    void setSize(int size);
    bool status() const;
    void setStatus(bool status);
    QString creator() const;
    void setCreator(const QString &creator);
    int fileIndex() const;
    void setFileIndex(int newFileIndex);

    QString toString();
    /**
    * @brief operator << displays the information of the file
    * @param os
    * @param file
    * @return
    */
   friend std::ostream& operator<<(std::ostream& os, const File file);


private:
   /**
    * @brief m_fileIndexCounter
    */

   static int m_fileIndexCounter;
   /**
    * @brief m_fileIndex
    */
   int m_fileIndex;
   /**
    * @brief name of the file
    */
   QString m_name;
   /**
    * @brief typ of the file
    */
   QString m_typ;
   /**
    * @brief size of the file
    */
   int m_size;
   /**
    * @brief status of the file
    */
   bool m_status;
   /**
    * @brief creator of the file
    */
   QString m_creator;
};

#endif // FILE_H{
