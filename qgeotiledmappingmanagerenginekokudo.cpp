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

#include "qgeotiledmappingmanagerenginekokudo.h"
#include "qgeotilefetcherkokudo.h"
#include "qgeotiledmapkokudo.h"

#include <QtLocation/private/qgeocameracapabilities_p.h>
#include <QtLocation/private/qgeomaptype_p.h>
#include <QtLocation/private/qgeotiledmap_p.h>

QT_BEGIN_NAMESPACE

QGeoTiledMappingManagerEngineKokudo::QGeoTiledMappingManagerEngineKokudo(const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString)
:   QGeoTiledMappingManagerEngine()
{
    QGeoCameraCapabilities cameraCaps;
    cameraCaps.setMinimumZoomLevel(0.0);
    cameraCaps.setMaximumZoomLevel(18.0);
    setCameraCapabilities(cameraCaps);

    setTileSize(QSize(256, 256));

    QList<QGeoMapType> mapTypes;
    // See map type implementations in QGeoTiledMapKokudo and QGeoTileFetcherKokudo.
    mapTypes << QGeoMapType(QGeoMapType::StreetMap, tr("標準地図"), tr("地理院タイル　標準地図"), false, false, 1);
    mapTypes << QGeoMapType(QGeoMapType::SatelliteMapDay, tr("衛星写真"), tr("地理院タイル　国土画像情報"), false, false, 2);
    mapTypes << QGeoMapType(QGeoMapType::TerrainMap, tr("標高地図"), tr("地理院タイル　標高地図"), false, false, 3);
    setSupportedMapTypes(mapTypes);

    QGeoTileFetcherKokudo *tileFetcher = new QGeoTileFetcherKokudo(this);
    if (parameters.contains(QStringLiteral("kokudo.useragent"))) {
        const QByteArray ua = parameters.value(QStringLiteral("Kokudo.useragent")).toString().toLatin1();
        tileFetcher->setUserAgent(ua);
    }
    if (parameters.contains(QStringLiteral("kokudo.mapping.host"))) {
        const QString up = parameters.value(QStringLiteral("Kokudo.mapping.host")).toString().toLatin1();
        tileFetcher->setUrlPrefix(up);
    }
    if (parameters.contains(QStringLiteral("kokudo.mapping.copyright")))
        m_customCopyright = parameters.value(QStringLiteral("Kokudo.mapping.copyright")).toString().toLatin1();

    setTileFetcher(tileFetcher);

    *error = QGeoServiceProvider::NoError;
    errorString->clear();
}

QGeoTiledMappingManagerEngineKokudo::~QGeoTiledMappingManagerEngineKokudo()
{
}

QGeoMap *QGeoTiledMappingManagerEngineKokudo::createMap()
{
    return new QGeoTiledMapKokudo(this);
}

QString QGeoTiledMappingManagerEngineKokudo::customCopyright() const
{
    return m_customCopyright;
}

QT_END_NAMESPACE
