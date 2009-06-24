#ifndef FEEDMODEL_H
#define FEEDMODEL_H
#include <QAbstractTableModel>
class QModelIndex;
#include <QList>
class Item;
class FeedModel : public QAbstractTableModel
{
public:
    FeedModel();
    virtual ~FeedModel();
    void SetHeaders();
    //QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex())const;
    //QModelIndex parent(const QModelIndex &child)const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    //QVariant headerData(int section, Qt::Orientation orientation,int role) const;
    void setItemsList(QList<Item>);
    // just for testing
    QList<Item> GetList(){return m_itemsList;}
    QString GetLink(int);
private:
    QList<Item> m_itemsList;
};

#endif // FEEDMODEL_H
