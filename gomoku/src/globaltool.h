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
#ifndef GLOBALTOOL_H
#define GLOBALTOOL_H

#include <QPixmap>
#include <QWidget>
#include <QIcon>
#include <QApplication>
#include <QImageReader>

class Globaltool
{
public:
    Globaltool();
    ~Globaltool();
    static Globaltool *getGlobaltool();
    //去除图片锯齿, 可以拉伸大小, 可留做全局功能函数
    /**
     * @brief getDpiPixmap 去除图片锯齿,
     * @param size 需要的图片大小
     * @param filename 图片路径
     * @param w 父窗口
     * @return 图片
     */
    static QPixmap getDpiPixmap(QSize size, const QString filename, QWidget *w);
};

#endif // GLOBALTOOL_H
