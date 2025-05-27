// Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "buttonagain.h"
#include "globaltool.h"
#include "ddlog.h"

#include <DHiDPIHelper>

#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

#include <QDebug>

Buttonagain::Buttonagain(QWidget *parent)
    : DWidget(parent)
    , againNormal(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/again_normal.svg"))
    , againHover(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/anain_hover.svg"))
    , againPress(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/again_press.svg"))
    , failAgainPress(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/fail_rest_press.svg"))
    , mResult(false)
{
    qCDebug(appLog) << "Buttonagain initializing";
    //设置大小
    setFixedSize(160, 42);
    currentPixmap = againNormal;
}

/**
 * @brief Buttonagain::setResult 设置对局结果
 * @param result 对局结果:true为赢, false为输
 */
void Buttonagain::setResult(bool result)
{
    qCDebug(appLog) << "Setting button result:" << result;
    mResult = result;
}

/**
 * @brief Buttonagain::mousePressEvent 鼠标点击事件
 * @param event
 */
void Buttonagain::mousePressEvent(QMouseEvent *event)
{
    qCDebug(appLog) << "Buttonagain pressed, result:" << mResult;
    if (event->button() & Qt::LeftButton) {
        buttonPressed = true;
        //根据输赢情况设置不同图片
        if (mResult) {
            currentPixmap = againPress;
        } else {
            currentPixmap = failAgainPress;
        }
        DWidget::mousePressEvent(event);
        update();
    }
}

/**
 * @brief Buttonagain::mouseReleaseEvent 鼠标释放事件
 * @param event
 */
void Buttonagain::mouseReleaseEvent(QMouseEvent *event)
{
    qCDebug(appLog) << "Buttonagain released, position valid:" << this->rect().contains(event->pos());
    if (event->button() & Qt::LeftButton) {
        buttonPressed = false;
        currentPixmap = againNormal;
        //发送鼠标点击信号
        if (this->rect().contains(event->pos()))
            emit signalButtonAnginClicked();
        DWidget::mouseReleaseEvent(event);
        update();
    }
}

/**
 * @brief Buttonagain::enterEvent 鼠标进入区域事件
 * @param event
 */
#if QT_VERSION_MAJOR > 5
void Buttonagain::enterEvent(QEnterEvent *event)
#else
void Buttonagain::enterEvent(QEvent *event)
#endif
{
    currentPixmap = againHover;
    DWidget::enterEvent(event);
    update();
}

/**
 * @brief Buttonagain::leaveEvent 鼠标离开区域事件
 * @param event
 */
void Buttonagain::leaveEvent(QEvent *event)
{
    currentPixmap = againNormal;
    DWidget::leaveEvent(event);
    update();
}

/**
 * @brief Buttonagain::paintEvent 绘图事件
 * @param event
 */
void Buttonagain::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(QRect(0, 0, 160, 42), currentPixmap);
    QFont font;
    font.setFamily(Globaltool::instacne()->loadFontFamilyFromFiles(":/resources/font/ResourceHanRoundedCN-Bold.ttf"));
    font.setWeight(QFont::Bold);
    font.setPixelSize(Globaltool::instacne()->getFontSize().dialogButton
                      - Globaltool::instacne()->getFontSize().dialogOffset);
    painter.setPen("#492c04");
    if (buttonPressed) {
#if QT_VERSION_MAJOR > 5
        if (currentPixmap.cacheKey() == againPress.cacheKey()) {
            painter.setPen("#ffdb9e");
        } else if (currentPixmap.cacheKey() == failAgainPress.cacheKey()) {
            painter.setPen("#d2d2d2");
        }
#else
        if (currentPixmap == againPress) {
            painter.setPen("#ffdb9e");
        } else if (currentPixmap == failAgainPress) {
            painter.setPen("#d2d2d2");
        }
#endif
    }
    painter.setFont(font);
    QFontMetrics fontMetrics(font);
    QString text = tr("Play Again");
    int fontWidth;
#if QT_VERSION_MAJOR > 5
    fontWidth = fontMetrics.boundingRect(text).width();
#else
    fontWidth = fontMetrics.width(text);
#endif
    if (fontWidth > (this->rect().width() - 20)) {
        setToolTip(text);
        text = fontMetrics.elidedText(text, Qt::ElideRight, this->rect().width() - 20);
    }
#if QT_VERSION_MAJOR > 5
    fontWidth = fontMetrics.boundingRect(text).width();
#else
    fontWidth = fontMetrics.width(text);
#endif
    painter.drawText(QPointF((rect().width() - fontWidth) / 2,
                             (rect().height() - fontMetrics.height()) / 2 + fontMetrics.ascent() - fontMetrics.descent() / 4), text);
//    painter.drawText(this->rect(), Qt::AlignHCenter | Qt::AlignVCenter, text);
    painter.restore();
    DWidget::paintEvent(event);
}
