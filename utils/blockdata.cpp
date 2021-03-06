﻿#include "blockdata.h"
#include <QDebug>

BlockData::BlockData()
{
    mBlockType = BLOCK_NONE;
}

BlockData::~BlockData()
{
    //qDebug()<<"block data descontruction.";
}

bool BlockData::sortByChangeAsc(const BlockData& d1, const BlockData& d2)
{
    return d1.mChangePer < d2.mChangePer;
}

bool BlockData::sortByChangeDesc(const BlockData& d1, const BlockData& d2)
{
    return d1.mChangePer > d2.mChangePer;
}

//BlockDataList BlockData::BlockDataListFromCodesList(const QStringList &codes)
//{
//    BlockDataList list;
//    foreach (QString code, codes) {
//        BlockData *data = new BlockData;
//        data->mCode = code;
//        list.append(data);
//    }

//    return list;
//}

//QStringList BlockData::BlockCodsListFromBlockData(const BlockDataList &list)
//{
//    QStringList codes;
//    foreach (BlockData *data, list) {
//        codes.append(data->mCode);
//    }

//    return codes;
//}

