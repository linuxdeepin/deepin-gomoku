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
#include "exitdialog.h"
#include "cancelbutton.h"
#include "exitbutton.h"
#include "exitlabel.h"
#include "resultpopup/closepopup.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <DHiDPIHelper>
#include <DApplication>
#include <QPainter>
ExitDialog::ExitDialog(QWidget *parent)
    : QDialog(parent)
    , result(BTType::BTCancel)
    , backgroundQPixmap(DHiDPIHelper::loadNxPixmap(":/resources/exitdialog/close-dialog.svg"))
{
    setFixedSize(371, 219); //弹窗尺寸大小
//    setContentsMargins(0, 0, 0, 0);
//    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground); //背景透明
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); //取消标题栏

    initUI();
}

/**
 * @brief ExitDialog::initUI
 * 初始化ui界面
 */
void ExitDialog::initUI()
{


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addSpacing(7);//上层布局离中间布局的距离

    QHBoxLayout *titleLayout = new QHBoxLayout();
    Closepopup *closeButton = new Closepopup(this);
    connect(closeButton, &Closepopup::signalCloseClicked, this, /*&ExitDialog::soltDialogClose*/[=]{
        this->close();
    });

    closeButton->setFixedSize(34,34);//关闭按钮的大小

    titleLayout->addStretch();
    titleLayout->addWidget(closeButton);
    titleLayout->addSpacing(15); //关闭按钮距离右边界的距离

    mainLayout->addLayout(titleLayout);


    QHBoxLayout *textLayout = new QHBoxLayout();
    textLayout->addStretch();

    ExitLabel *exitLabel = new ExitLabel(this);
    textLayout->addWidget(exitLabel);
    textLayout->addSpacing(72); //提示语句距离右边界的距离

    mainLayout->addLayout(textLayout);
    mainLayout->addStretch();


    QHBoxLayout *BTLayout = new QHBoxLayout();
    BTLayout->addSpacing(10); //按钮距离左边界的距离

    CancelButton *cancelButton = new CancelButton();
    ExitButton *exitButton = new ExitButton();
    connect(cancelButton, &CancelButton::signalButtonOKClicked, this, &ExitDialog::soltDialogClose);
    connect(exitButton, &ExitButton::signalButtonOKClicked, this, &ExitDialog::soltGameExit);

    BTLayout->addWidget(cancelButton);
    BTLayout->addSpacing(10);//两按钮中间的距离
    BTLayout->addWidget(exitButton);
    BTLayout->addSpacing(21);//按钮距离右边界的距离

    mainLayout->addLayout(BTLayout);
    mainLayout->addSpacing(21); //按钮距离下边界的距离
}

/**
 * @brief ExitDialog::soltDialogClose
 * 槽函数：处理取消按钮和关闭dialog的信号
 */
void ExitDialog::soltDialogClose() {
    setResult(BTType::BTCancel); //将状态设置为取消
    this->done(0);
}

/**
 * @brief ExitDialog::soltGameExit
 * 槽函数：处理退出游戏的信号
 */
void ExitDialog::soltGameExit() {
    setResult(BTType::BTExit); //将状态设置为退出
    this->done(0);
}

void ExitDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(this->rect(), backgroundQPixmap);
    painter.restore();
    QDialog::paintEvent(event);
}
