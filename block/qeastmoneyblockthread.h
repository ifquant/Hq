﻿#ifndef QEASTMONEYBLOCKTHREAD_H
#define QEASTMONEYBLOCKTHREAD_H

#include <QThread>
#include <QMap>
#include <QList>
#include "utils/blockdata.h"


typedef enum enBlockDisplayRule
{
    BLOCK_DISPLAY_SORT_NONE = 0,
    BLOCK_DISPLAY_SORT_DESCEND = -1,
    BLOCK_DISPLAY_SORT_ASCEND = 1,
    BLOCK_DISPLAY_SORT_END = 3,
}BLOCK_DISPLAY_RULE;

class QEastMoneyBlockThread : public QObject
{
    Q_OBJECT
public:
    explicit QEastMoneyBlockThread(int pBlockID, QObject *parent = 0);
    ~QEastMoneyBlockThread();
    void    setSortRule(BLOCK_DISPLAY_RULE rule);
    void    reverseSortRule();
    void    stop();
signals:
    void    sendBlockDataList(const BlockDataPList& list);
    void    sendStkinfoUpdateProgress(int cur, int total);
    void    signalUpdateMsg(const QString& msg);
    void    start();
    void    sendShareBlockDataMap(const QMap<QString, BlockDataPList>& map);
public slots:
    void    slotUpdateBlockShare();
    void    slotUpdateBlockInfos();
    void    slotUpdateBlockShareCodeList(const QString& pBlockCode, const QStringList& pShareCodesList);
    void    slotBlockShareThreadFinished();

private:
    int         mSortRule;
    int         mUserBlockType;
    int         mWebBlockType;
    QMap<QString,   BlockData*> mBlockDataList;
    QThread     mWorkthread;
    bool        mUpdateRealInfo;
};

#endif // QEASTMONEYBLOCKTHREAD_H
