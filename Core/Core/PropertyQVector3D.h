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

#ifndef PROPERTYQVECTOR3D_H
#define PROPERTYQVECTOR3D_H

#include "../Auxiliary/PropertyTemplates.h"
#include <QVector3D>

class QTN_PE_CORE_EXPORT QtnPropertyQVector3DBase: public QtnSinglePropertyBase<QVector3D>
{
    Q_OBJECT
    QtnPropertyQVector3DBase(const QtnPropertyQVector3DBase& other) Q_DECL_EQ_DELETE;

public:
    explicit QtnPropertyQVector3DBase(QObject *parent);

protected:
    // string conversion implementation
    bool fromStrImpl(const QString& str) override;
    bool toStrImpl(QString& str) const override;

    P_PROPERTY_DECL_MEMBER_OPERATORS(QtnPropertyQVector3DBase)
};

P_PROPERTY_DECL_EQ_OPERATORS(QtnPropertyQVector3DBase, QVector3D)

QTN_PE_CORE_EXPORT QtnProperty* qtnCreateXProperty(QObject *parent, QtnPropertyQVector3DBase *propertyPoint);
QTN_PE_CORE_EXPORT QtnProperty* qtnCreateYProperty(QObject *parent, QtnPropertyQVector3DBase *propertyPoint);

class QTN_PE_CORE_EXPORT QtnPropertyQVector3DCallback: public QtnSinglePropertyCallback<QtnPropertyQVector3DBase>
{
    Q_OBJECT
    QtnPropertyQVector3DCallback(const QtnPropertyQVector3DCallback& other) Q_DECL_EQ_DELETE;

public:
    explicit QtnPropertyQVector3DCallback(QObject *parent)
        : QtnSinglePropertyCallback<QtnPropertyQVector3DBase>(parent)
    {
    }

    P_PROPERTY_DECL_MEMBER_OPERATORS2(QtnPropertyQVector3DCallback, QtnPropertyQVector3DBase)
};

class QTN_PE_CORE_EXPORT QtnPropertyQVector3D: public QtnSinglePropertyValue<QtnPropertyQVector3DBase>
{
    Q_OBJECT
    QtnPropertyQVector3D(const QtnPropertyQVector3D& other) Q_DECL_EQ_DELETE;

public:
    explicit QtnPropertyQVector3D(QObject *parent)
        : QtnSinglePropertyValue<QtnPropertyQVector3DBase>(parent)
    {
    }

    P_PROPERTY_DECL_MEMBER_OPERATORS2(QtnPropertyQVector3D, QtnPropertyQVector3DBase)
};

#endif // PROPERTYQVECTOR3D_H
