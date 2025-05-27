// Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "gomokuapplication.h"
#include "gomokumainwindow.h"
#include "ddlog.h"

Gomokuapplication::Gomokuapplication(int &argc, char **argv)
    : DApplication(argc, argv)
{
    qCDebug(appLog) << "Gomoku application initialized";
}

void Gomokuapplication::handleQuitAction()
{
    qCDebug(appLog) << "Handling quit action";
    QWidget *pWgt = activeWindow();
    GomokuMainWindow *pWindow = qobject_cast<GomokuMainWindow *>(pWgt); //在对应的MainWindow操作

    qCInfo(appLog) << "Active window type:" << (pWindow ? "GomokuMainWindow" : "Other");

    // 处理点击退出事件
    if (pWindow) {
        qCDebug(appLog) << "Forwarding quit to main window";
        pWindow->handleQuit();
    } else {
        qCWarning(appLog) << "No valid main window found for quit action";
    }
}
