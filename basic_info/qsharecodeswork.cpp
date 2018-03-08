﻿#include "qsharecodeswork.h"
#include <QDebug>
#include <QDateTime>
#include <QRegularExpression>
#include <QRegExp>
#include <QFile>
#include <QDir>
#include "dbservices/hqdatadefines.h"
#include <QTextCodec>
#include "qhttpget.h"
#include "utils/hqutils.h"
#include "utils/sharedata.h"

QShareCodesWork::QShareCodesWork(QObject *parent) : mParent(parent),QRunnable()
{
}

QShareCodesWork::~QShareCodesWork()
{
}

void QShareCodesWork::run()
{
    ShareBaseDataList list;
    QTextCodec *utf8 = QTextCodec::codecForName("UTF8");
    QString result = QString::fromLocal8Bit(QHttpGet::getContentOfURL("http://quote.eastmoney.com/stocklist.html"));
    QRegExp reg(">([\u4e00-\u9fa5A-Z0-9]{1,})\\(([0-9]{6})\\)<");
    QRegExp reg_code("60[013][0-9]{3}|300[0-9]{3}|00[012][0-9]{3}|510[0-9]{3}|1599[0-9]{2}");
    int index = 0;
    while((index = reg.indexIn(result, index)) >= 0)
    {
        QString name = reg.cap(1);
        QString code = reg.cap(2);
        if(reg_code.exactMatch(code))
        {
            ShareBaseData data;
            data.setCode(code);
            data.setName(name);
            //QString PY = HqUtils::GetFirstLetter(utf8->toUnicode( name.toStdString().data()));
            //qDebug()<<"Name:"<<name<<" PY:"<<PY;
            //data.setPY(PY);
            list.append(data);
        }
        index += reg.matchedLength();
    }
    if(list.length() > 0 && mParent)
    {
        QMetaObject::invokeMethod(mParent, "slotUpdateShareCodesList", Qt::DirectConnection, Q_ARG(ShareBaseDataList,list ));
    }
    return;
}

