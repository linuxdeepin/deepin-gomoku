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
#ifndef SELECTCHESS_H
#define SELECTCHESS_H

#include "selectbutton.h"

#include <QDialog>
#include <QObject>

class Selectchess : public QDialog
{
    Q_OBJECT
public:
    explicit Selectchess(QWidget *parent = nullptr);

    void selectChessShow();
    void setSelectChess(int chessColor);
    int getSelsectChess();
    void selectClose();

signals:
    void signalSelectWhiteChess();
    void signalSelectBlackChess();
    void signalButtonOKClicked();
    void signalDialogClose();

public slots:
    void slotCloseSelectPopup();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void initUI();

private slots:
    void slotButtonOKClicked();

private:
    QPixmap backgroundPixmap; //背景图片
    int selectChessColor = 0; //选择的棋子颜色
    bool chessHasSelected = false; //是否选择了棋子
    Selectbutton *selectLButton = nullptr; //左边选项
    Selectbutton *selectRButton = nullptr; //右边选项
};

#endif // SELECTCHESS_H
