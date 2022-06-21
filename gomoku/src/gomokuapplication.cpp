/*
   * Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
   *
   * Author:     zhengxiaokang <zhengxiaokang@uniontech.com>
   *
   * Maintainer: zhengxiaokang <zhengxiaokang@uniontech.com>
   *
   * This program is free software: you can redistribute it and/or modify
   * it under the terms of the GNU General Public License as published by
   * the Free Software Foundation, either version 3 of the License, or
   * any later version.
   *
   * This program is distributed in the hope that it will be useful,
   * but WITHOUT ANY WARRANTY; without even the implied warranty of
   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   * GNU General Public License for more details.
   *
   * You should have received a copy of the GNU General Public License
   * along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */
#include "gomokuapplication.h"
#include "gomokumainwindow.h"

Gomokuapplication::Gomokuapplication(int &argc, char **argv)
    : DApplication(argc, argv)
{

}

void Gomokuapplication::handleQuitAction()
{
    QWidget *pWgt = activeWindow();
    GomokuMainWindow *pWindow = qobject_cast<GomokuMainWindow *>(pWgt); //在对应的MainWindow操作

    // 处理点击退出事件
    if (pWindow)
        pWindow->handleQuit();
}
