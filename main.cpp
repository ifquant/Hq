﻿#include "dialog.h"
#include <QApplication>
#include <QTextCodec>
#include "qexchangedatamanage.h"
#include <QDebug>
#include <QDate>
//#include "qglobalapplication.h"
#include "qhttpget.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    Dialog w;
    w.showMaximized();

    return a.exec();
}
