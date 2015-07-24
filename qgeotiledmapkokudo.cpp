/****************************************************************************
**
** Copyright (C) 2015 Aaron McCarthy <mccarthy.aaron@gmail.com>
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

#include "qgeotiledmapKokudo.h"
#include "qgeotiledmappingmanagerengineKokudo.h"
#include <QtLocation/private/qgeotilespec_p.h>
#include <QtLocation/private/qgeotilecache_p.h>
#include <QStandardPaths>
#include <QDir>
#include <QStringList>

QT_BEGIN_NAMESPACE

QGeoTiledMapKokudo::QGeoTiledMapKokudo(QGeoTiledMappingManagerEngineKokudo *engine, QObject *parent)
:   QGeoTiledMap(engine, parent), m_mapId(-1), m_customCopyright(engine->customCopyright())
{
}

QGeoTiledMapKokudo::~QGeoTiledMapKokudo()
{
}

void QGeoTiledMapKokudo::evaluateCopyrights(const QSet<QGeoTileSpec> &visibleTiles)
{
    if (visibleTiles.isEmpty())
        return;

    QGeoTileSpec tile = *visibleTiles.constBegin();
    if (tile.mapId() == m_mapId)
        return;

    m_mapId = tile.mapId();

    QString copyrights = tr("<a href='http://www.gsi.go.jp/kikakuchousei/kikakuchousei40182.html'>国土地理院</a>");

    emit copyrightsChanged(copyrights);
}

QT_END_NAMESPACE
