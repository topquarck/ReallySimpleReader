#include "feedmodel.h"
#include "item.h"
#include <QModelIndex>
#include <QVariant>

FeedModel::FeedModel()
{
    this->SetHeaders();
}
FeedModel::~FeedModel()
{
    m_itemsList.clear();
}

void FeedModel::SetHeaders()
{
   /*setHeaderData(0, Qt::Horizontal, QObject::tr("Subject"));
     setHeaderData(1, Qt::Horizontal, QObject::tr("Sender"));
     setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
*/
}

/*QModelIndex FeedModel::index(int row, int column,const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex FeedModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}
*/
int FeedModel::rowCount(const QModelIndex &parent) const
{
    return  m_itemsList.size();
}
int FeedModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}
QVariant FeedModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();

     if (index.row() >= m_itemsList.size())
         return QVariant();

         QVariant var;
         Item& it = const_cast<Item&>(m_itemsList.at(index.row())) ;
         switch (index.column()){
             case 0:            
             //var =  m_itemsList.at(index.row()).getTitle();
            var = it.getTitle();
             break;
             case 1:
             //var = m_itemsList.at(index.row()).getLink();
             var = it.getLink();
             break;
             case 2:
             //var = m_itemsList.at(index.row()).getAuther();
             var = it.getAuther();
             break;
             case 3:
             //var = m_itemsList.at(index.row()).getPubDate();
             var = it.getPubDate();
             default:
             var= "";
         }
         return var;
}

void FeedModel::setItemsList(QList<Item> lista)
{
    m_itemsList = lista;
}
/*
QVariant FeedModel::headerData(int section, Qt::Orientation orientation,int role) const
{
    if (role != Qt::DisplayRole)
         return QVariant();

     if (orientation == Qt::Horizontal)
         return QString("COLUMN %1").arg(section);
     else
         return QString("%1").arg(section);
}
*/

QString FeedModel::GetLink(int row)
{
    qDebug("in feedModel's GetLink");
    //return m_itemsList.at(row).getLink();
    Item& it = const_cast<Item&>(m_itemsList.at(row)) ;
    return it.getLink();
}
