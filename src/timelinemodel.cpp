#include "timelinemodel.h"

TimelineModel::TimelineModel(TwitterApi *twitterApi)
{
    this->twitterApi = twitterApi;

    connect(twitterApi, SIGNAL(homeTimelineError(QString)), this, SLOT(handleHomeTimelineError(QString)));
    connect(twitterApi, SIGNAL(homeTimelineSuccessful(QVariantList)), this, SLOT(handleHomeTimelineSuccessful(QVariantList)));
}

int TimelineModel::rowCount(const QModelIndex &) const
{
    return timelineTweets.size();
}

QVariant TimelineModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }
    if(role == Qt::DisplayRole) {
        return QVariant(timelineTweets.value(index.row()));
    }
    return QVariant();
}

void TimelineModel::update()
{
    twitterApi->homeTimeline();
}

void TimelineModel::handleHomeTimelineSuccessful(const QVariantList &result)
{
    qDebug() << "TimelineModel::handleHomeTimelineSuccessful";
    beginResetModel();
    timelineTweets.clear();
    timelineTweets.append(result);
    endResetModel();
    emit homeTimelineUpdated();
}

void TimelineModel::handleHomeTimelineError(const QString &errorMessage)
{
    emit homeTimelineError(errorMessage);
}