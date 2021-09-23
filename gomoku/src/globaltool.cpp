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
#include "globaltool.h"

#include <DFontSizeManager>
#include <QFile>
#include <QFontDatabase>

DWIDGET_USE_NAMESPACE

Globaltool::Globaltool()
{
}

Globaltool::~Globaltool()
{
}

QPixmap Globaltool::getDpiPixmap(QSize size, const QString &filename, QWidget *w)
{
    QPixmap pixmap;
    qreal devicePixelRatio = qApp->devicePixelRatio();
    if (w) {
        devicePixelRatio = w->devicePixelRatioF();
    }

    qreal ratio = 1.0;
    QImageReader reader;
    reader.setFileName(qt_findAtNxFile(filename, devicePixelRatio, &ratio));

    if (!qFuzzyCompare(ratio, devicePixelRatio)) {
        if (reader.canRead()) {
            QSize picSize;
            if (size != QSize(0, 0)) {
                picSize = size;
            } else {
                picSize = reader.size();
            }

            reader.setScaledSize(picSize * (devicePixelRatio / ratio));
            pixmap = QPixmap::fromImage(reader.read());
            pixmap.setDevicePixelRatio(devicePixelRatio);
        }
    } else {
        if (size != QSize(0, 0)) {
            reader.setScaledSize(size * (devicePixelRatio / ratio));
            pixmap = QPixmap::fromImage(reader.read());
        } else {
            pixmap.load(filename);
        }
    }
    return pixmap;
}

QString Globaltool::AutoFeed(const QString &text, const int fontSize, const int textWidth)
{
    QString strText = text;
    QString resultStr = nullptr;
    QFont labelF;
    labelF.setFamily(Globaltool::loadFontFamilyFromFiles(":/resources/font/ResourceHanRoundedCN-Bold.ttf"));
    labelF.setWeight(QFont::Black);
    labelF.setPixelSize(fontSize);
    QFontMetrics fm(labelF);
    int titlewidth = fm.width(strText);
    QStringList strList;
    QString str;
    strList.clear();

    if (titlewidth < textWidth) {
        strList.append(strText);
        resultStr += strText;
    } else {
        for (int i = 0; i < strText.count(); i++) {
            str += strText.at(i);

            if (fm.width(str) > textWidth) {
                str.remove(str.count() - 1, 1);
                strList.append(str);
                resultStr += str + "\n";
                str.clear();
                --i;
            }
        }
        strList.append(str);
        resultStr += str;
    }

    return resultStr;
}

QString Globaltool::loadFontFamilyFromFiles(const QString &fontFileName)
{
    static QHash<QString, QString> tmd;
    if (tmd.contains(fontFileName)) {
        return tmd.value(fontFileName);
    }
    QString font = "";
    QFile fontFile(fontFileName);
    if (!fontFile.open(QIODevice::ReadOnly)) {
        qDebug() << __FUNCTION__ << "Open font file error";
        return font;
    }

    int loadedFontID = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
    QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
    if (!loadedFontFamilies.empty()) {
        font = loadedFontFamilies.at(0);
    }
    fontFile.close();

    if (!(font.isEmpty()))
        tmd.insert(fontFileName, font);
    return font;
}
