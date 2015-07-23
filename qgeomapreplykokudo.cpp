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

#include "qgeomapreplyKokudo.h"
#include "QFile"
#include "QDir"
#include <QtLocation/private/qgeotilespec_p.h>
#include <QStandardPaths>

QGeoMapReplyKokudo::QGeoMapReplyKokudo(QNetworkReply *reply, const QGeoTileSpec &spec, QObject *parent)
:   QGeoTiledMapReply(spec, parent), m_reply(reply)
{
    connect(m_reply, SIGNAL(finished()), this, SLOT(networkReplyFinished()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(networkReplyError(QNetworkReply::NetworkError)));

    m_datadir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);// + "/mapdata";
    QDir dir;
    if (! dir.exists(m_datadir)){
        dir.mkdir(m_datadir);
    }
    m_datadir += "/";
}

QGeoMapReplyKokudo::~QGeoMapReplyKokudo()
{
    if (m_reply) {
        m_reply->deleteLater();
        m_reply = 0;
    }
}

void QGeoMapReplyKokudo::abort()
{
    if (!m_reply)
        return;

    m_reply->abort();
}

QNetworkReply *QGeoMapReplyKokudo::networkReply() const
{
    return m_reply;
}

void QGeoMapReplyKokudo::networkReplyFinished()
{
    if (!m_reply)
        return;

    if (m_reply->error() != QNetworkReply::NoError)
        return;

//    QString url = m_reply->url().toString();
//    url.replace("/", "_");
//    url.replace("http:", "");
//    QString filename = m_datadir + url;
//    qDebug() << filename << endl;

    QByteArray a = m_reply->readAll();

//    if (true & ! QFile::exists(filename)){ // use cache
//        QFile tmpfile(filename);
//        tmpfile.open(QIODevice::WriteOnly);
//        tmpfile.write(a);
//        tmpfile.close();
//    }

    setMapImageData(a);
    setMapImageFormat("png");
    setFinished(true);

    m_reply->deleteLater();
    m_reply = 0;
}

void QGeoMapReplyKokudo::networkReplyError(QNetworkReply::NetworkError error)
{
    if (!m_reply)
        return;

//    QString url = m_reply->url().toString();
//    url.replace("/", "_");
//    url.replace("http:", "");

//    QString filename = m_datadir + url;

//    if (QFile::exists(filename)){
//        QFile tmpfile(filename);
//        tmpfile.open(QIODevice::ReadOnly);
//        QByteArray a = tmpfile.readAll();
//        tmpfile.close();

//        setMapImageData(a);
//        setMapImageFormat("png");

//        setFinished(true);
//        m_reply->deleteLater();
//        m_reply = 0;
//        return;
//    }

    if (error != QNetworkReply::OperationCanceledError)
        setError(QGeoTiledMapReply::CommunicationError, m_reply->errorString());

    setFinished(true);
    m_reply->deleteLater();
    m_reply = 0;
}
