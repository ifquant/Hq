﻿#include "qsharehistorycounterwork.h"
#include "dbservices/dbservices.h"

QShareHistoryCounterWork::QShareHistoryCounterWork(const QString& code,const ShareDataList& list, QObject* parent)
    :mCode(code),mList(list),mParent(parent),QRunnable()
{

}

QShareHistoryCounterWork::~QShareHistoryCounterWork()
{

}

void QShareHistoryCounterWork::run()
{
    qSort(mList.begin(), mList.end(), ShareData::sortByDateDesc);
    int size = mList.size();
    double lastColse = 0;
    double lastMoney = 0.0;
    double last3Change = 0.0;
    double last5Change = 0.0;
    double last10Change = 0.0;
    double lastMonthChange = 0.0;
    double lastYearChange = 0.0;
    qint64 vol_change = 0;
    qint64 vol = 0;

    if(size > 0)
    {
        lastMoney = mList[0].mMoney;
        lastColse = mList[0].mClose;
        int day[] = {DAYS_3, DAYS_5, DAYS_10, DAYS_MONTH, DAYS_YEARS};
        for(int i=0; i<5; i++)
        {
            ShareData curData;
            if(size >= day[i]+1)
            {
                curData = mList[day[i]];
            } else
            {
                curData = mList[size-1];
            }
            if(mCode == "600804")
            {
                qDebug()<<"array size:"<<size<<i<<lastMoney<<lastColse<<curData.mClose<<QDateTime::fromMSecsSinceEpoch(curData.mTime);
            }
            if(i==0)
            {
                last3Change = (lastColse - curData.mClose) *100.0 / curData.mClose;
            }else if(i==1)
            {
                last5Change = (lastColse - curData.mClose)*100.0 / curData.mClose;
            }else if(i==2)
            {
                last10Change = (lastColse - curData.mClose)*100.0 / curData.mClose;
            }else if(i==3)
            {
                lastMonthChange = (lastColse - curData.mClose)*100.0 / curData.mClose;
            }else if(i==4)
            {
                lastYearChange = (lastColse - curData.mClose)*100.0 / curData.mClose;
            }
        }

        vol = mList[0].mForeignVol;
        vol_change = vol;
        if(size >=2)
        {
            vol_change -= mList[1].mForeignVol;
        }
    }
    DATA_SERVICE->signalUpdateShareinfoWithHistory(mCode, lastMoney, last3Change, last5Change, last10Change, lastMonthChange, lastYearChange, vol, vol_change);

 //   qDebug()<<mCode<<lastMoney<<last3Change<<last5Change<<last10Change<<lastMonthChange<<lastYearChange<<vol<<vol_change;

    if(mParent)
    {
        QMetaObject::invokeMethod(mParent,\
                                  "slotUpdateShareHistoryInfoFinished",\
                                  Q_ARG(QString, mCode));
    }
}