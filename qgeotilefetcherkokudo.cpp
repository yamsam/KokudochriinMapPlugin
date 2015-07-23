/****************************************************************************
**
** Copyright (C) 2013 Aaron McCarthy <mccarthy.aaron@gmail.com>
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qgeotilefetcherKokudo.h"
#include "qgeomapreplyKokudo.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtLocation/private/qgeotilespec_p.h>

QT_BEGIN_NAMESPACE

QGeoTileFetcherKokudo::QGeoTileFetcherKokudo(QObject *parent)
:   QGeoTileFetcher(parent), m_networkManager(new QNetworkAccessManager(this)),
    m_userAgent("Qt Location based application")
{
}

void QGeoTileFetcherKokudo::setUserAgent(const QByteArray &userAgent)
{
    m_userAgent = userAgent;
}

void QGeoTileFetcherKokudo::setUrlPrefix(const QString &urlPrefix)
{
    m_urlPrefix = urlPrefix;
}

QGeoTiledMapReply *QGeoTileFetcherKokudo::getTileImage(const QGeoTileSpec &spec)
{
    QNetworkRequest request;
    request.setRawHeader("User-Agent", m_userAgent);

    QString urlPrefix;

    switch (spec.mapId()) {
    case 1:
        urlPrefix = QStringLiteral("http://cyberjapandata.gsi.go.jp/xyz/std/"); // 標準地図
        break;
    case 2:
        urlPrefix = QStringLiteral("http://cyberjapandata.gsi.go.jp/xyz/ort/");  // 衛星写真
        break;
    case 3:
        urlPrefix = QStringLiteral("http://cyberjapandata.gsi.go.jp/xyz/relief/"); // 標高地図
        break;
    default:
        qWarning("Unknown map id %d\n", spec.mapId());
    }

    request.setUrl(QUrl(urlPrefix + QString::number(spec.zoom()) + QLatin1Char('/') +
                        QString::number(spec.x()) + QLatin1Char('/') +
                        QString::number(spec.y()) + QStringLiteral(".png")));

    QNetworkReply *reply = m_networkManager->get(request);

    return new QGeoMapReplyKokudo(reply, spec);
}

QT_END_NAMESPACE
