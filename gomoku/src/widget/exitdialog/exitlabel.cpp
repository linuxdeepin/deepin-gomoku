/*
   * Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
   *
   * Author:     liyucheng <liyucheng@uniontech.com>
   *
   * Maintainer:  liyucheng <liyucheng@uniontech.com>
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
#include "exitlabel.h"

ExitLabel::ExitLabel(QWidget *parent) : DLabel(parent)
{

    setWordWrap(true);
    setMinimumWidth(204);
    setMinimumHeight(66);
    setText(tr("Are you sure want to exit the game?"));
    setAlignment(Qt::AlignHCenter | Qt::AlignBottom);

    QPalette palCancel;
    palCancel.setColor(QPalette::WindowText, QColor("#024526"));
    setPalette(palCancel);

    QFont tipFont;
    tipFont.setFamily("Yuanti SC");
    tipFont.setPointSize(18); //字体大小
    tipFont.setWeight(63); //中粗
    setFont(tipFont);
}
