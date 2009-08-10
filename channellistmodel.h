#ifndef CHANNELLISTMODEL_H
#define CHANNELLISTMODEL_H

#include <QAbstractListModel>
//class Channel;
class QModelIndex;
class QVariant;
//class QList;
#include "channel.h"
/**
  this is the model that holds the channels list in the UI
  it is used by the mainWindow's List view to display
  channels names.
  */
class ChannelListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ChannelListModel();
    ~ChannelListModel();
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    Channel GetChannel(int index);
    void SetChannelsList (QList<Channel>);

private:
    QList<Channel> m_channelsList;
};

#endif // CHANNELLISTMODEL_H
