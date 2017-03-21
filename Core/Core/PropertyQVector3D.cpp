/*
   Copyright (c) 2012-2016 Alex Zhondin <lexxmark.dev@gmail.com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "PropertyQVector3D.h"
#include "PropertyInt.h"

QtnPropertyQVector3DBase::QtnPropertyQVector3DBase(QObject *parent)
    : QtnSinglePropertyBase<QVector3D>(parent)
{
}

bool QtnPropertyQVector3DBase::fromStrImpl(const QString& str)
{
    static QRegExp parserPoint("^\\s*QVector3D\\s*\\(([^\\)]+)\\)\\s*$", Qt::CaseInsensitive);
    static QRegExp parserParams("^\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*$", Qt::CaseInsensitive);

    if (!parserPoint.exactMatch(str))
        return false;

    QStringList params = parserPoint.capturedTexts();
    if (params.size() != 3)
        return false;

    if (!parserParams.exactMatch(params[1]))
        return false;

    params = parserParams.capturedTexts();
    if (params.size() != 4)
        return false;

    bool ok = false;
    int x = params[1].toInt(&ok);
    if (!ok)
        return false;

    int y = params[2].toInt(&ok);
    if (!ok)
        return false;

    int z = params[3].toInt(&ok);
    if (!ok)
        return false;

    setValue(QVector3D(x, y, z));
    return true;
}

bool QtnPropertyQVector3DBase::toStrImpl(QString& str) const
{
    QVector3D v = value();
    str = QString("QVector3D(%1, %2, %3)").arg(v.x()).arg(v.y()).arg(v.z());
    return true;
}

QtnProperty* qtnCreateXProperty(QObject *parent, QtnPropertyQVector3DBase *propertyPoint)
{
    QtnPropertyIntCallback *xProperty = new QtnPropertyIntCallback(parent);
    xProperty->setName(QObject::tr("X"));
    xProperty->setDescription(QObject::tr("X coordinate of the %1.").arg(propertyPoint->name()));
    xProperty->setCallbackValueGet([propertyPoint]()->int { return propertyPoint->value().x(); });
    xProperty->setCallbackValueSet([propertyPoint](int newX) {
        QVector3D point = propertyPoint->value();
        point.setX(newX);
        propertyPoint->setValue(point);
    });
    QtnPropertyBase::connectMasterSignals(*propertyPoint, *xProperty);

    return xProperty;
}

QtnProperty* qtnCreateYProperty(QObject *parent, QtnPropertyQVector3DBase *propertyPoint)
{
    QtnPropertyIntCallback *yProperty = new QtnPropertyIntCallback(parent);
    yProperty->setName(QObject::tr("Y"));
    yProperty->setDescription(QObject::tr("Y coordinate of the %1.").arg(propertyPoint->name()));
    yProperty->setCallbackValueGet([propertyPoint]()->int { return propertyPoint->value().y(); });
    yProperty->setCallbackValueSet([propertyPoint](int newY) {
        QVector3D point = propertyPoint->value();
        point.setY(newY);
        propertyPoint->setValue(point);
    });
    QtnPropertyBase::connectMasterSignals(*propertyPoint, *yProperty);

    return yProperty;
}

QtnProperty* qtnCreateZProperty(QObject *parent, QtnPropertyQVector3DBase *propertyPoint)
{
    QtnPropertyIntCallback *zProperty = new QtnPropertyIntCallback(parent);
    zProperty->setName(QObject::tr("Z"));
    zProperty->setDescription(QObject::tr("Z coordinate of the %1.").arg(propertyPoint->name()));
    zProperty->setCallbackValueGet([propertyPoint]()->int { return propertyPoint->value().z(); });
    zProperty->setCallbackValueSet([propertyPoint](int newZ) {
        QVector3D point = propertyPoint->value();
        point.setZ(newZ);
        propertyPoint->setValue(point);
    });
    QtnPropertyBase::connectMasterSignals(*propertyPoint, *zProperty);

    return zProperty;
}
