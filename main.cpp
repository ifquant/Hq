﻿#include "dialog.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include <QDate>
//#include "qglobalapplication.h"
#include <QFile>
#include <QDesktopWidget>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QRect rect = QApplication::desktop()->screenGeometry();
    qDebug()<<__func__<<rect<<QDir::currentPath();
    //make size as 9:16
    Dialog w;
    w.showMaximized();

    return a.exec();
}
