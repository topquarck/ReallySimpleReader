#include "channellistmodel.h"

#include <QList>
#include <QVariant>
ChannelListModel::ChannelListModel()
{
    qDebug("in the constructor of the ChannelListModel ");
}
int ChannelListModel::rowCount( const QModelIndex & parent) const
{
    return m_channelsList.size();
}
QVariant ChannelListModel::data(const QModelIndex& index,int role) const
{
    if (!index.isValid() || index.row() >= m_channelsList.size())
         return QVariant();
     //else
    QVariant var ;
    int i = index.row();
    Channel ch = m_channelsList.at(i);
     if (role == Qt::DisplayRole){
         //var = m_channelsList.at(index.row()).getTitle();
         var = ch.getTitle();
     }
     return var;
}
Channel ChannelListModel::GetChannel(int index)
{
    return m_channelsList.at(index);
}
void ChannelListModel::SetChannelsList(QList<Channel> lista)
{
    m_channelsList = lista;
}
