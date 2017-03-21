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

#ifndef PROPERTYQVECTOR4D_H
#define PROPERTYQVECTOR4D_H

#include "../Auxiliary/PropertyTemplates.h"
#include <QVector4D>

class QTN_PE_CORE_EXPORT QtnPropertyQVector4DBase: public QtnSinglePropertyBase<QVector4D>
{
    Q_OBJECT
    QtnPropertyQVector4DBase(const QtnPropertyQVector4DBase& other) Q_DECL_EQ_DELETE;

public:
    explicit QtnPropertyQVector4DBase(QObject *parent);

protected:
    // string conversion implementation
    bool fromStrImpl(const QString& str) override;
    bool toStrImpl(QString& str) const override;

    P_PROPERTY_DECL_MEMBER_OPERATORS(QtnPropertyQVector4DBase)
};

P_PROPERTY_DECL_EQ_OPERATORS(QtnPropertyQVector4DBase, QVector4D)

QTN_PE_CORE_EXPORT QtnProperty* qtnCreateXProperty(QObject *parent, QtnPropertyQVector4DBase *propertyPoint);
QTN_PE_CORE_EXPORT QtnProperty* qtnCreateYProperty(QObject *parent, QtnPropertyQVector4DBase *propertyPoint);

class QTN_PE_CORE_EXPORT QtnPropertyQVector4DCallback: public QtnSinglePropertyCallback<QtnPropertyQVector4DBase>
{
    Q_OBJECT
    QtnPropertyQVector4DCallback(const QtnPropertyQVector4DCallback& other) Q_DECL_EQ_DELETE;

public:
    explicit QtnPropertyQVector4DCallback(QObject *parent)
        : QtnSinglePropertyCallback<QtnPropertyQVector4DBase>(parent)
    {
    }

    P_PROPERTY_DECL_MEMBER_OPERATORS2(QtnPropertyQVector4DCallback, QtnPropertyQVector4DBase)
};

class QTN_PE_CORE_EXPORT QtnPropertyQVector4D: public QtnSinglePropertyValue<QtnPropertyQVector4DBase>
{
    Q_OBJECT
    QtnPropertyQVector4D(const QtnPropertyQVector4D& other) Q_DECL_EQ_DELETE;

public:
    explicit QtnPropertyQVector4D(QObject *parent)
        : QtnSinglePropertyValue<QtnPropertyQVector4DBase>(parent)
    {
    }

    P_PROPERTY_DECL_MEMBER_OPERATORS2(QtnPropertyQVector4D, QtnPropertyQVector4DBase)
};

#endif // PROPERTYQVECTOR4D_H
