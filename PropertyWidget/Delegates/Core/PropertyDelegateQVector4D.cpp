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

#include "PropertyDelegateQVector4D.h"
#include "../../../Core/Core/PropertyQVector4D.h"
#include "../PropertyDelegateFactory.h"

void regQVector4DDelegates(QtnPropertyDelegateFactory &factory)
{
    factory.registerDelegateDefault(&QtnPropertyQVector4DBase::staticMetaObject
			     , &qtnCreateDelegate<QtnPropertyDelegateQVector4D, QtnPropertyQVector4DBase>
			     , "XYZW");
}

QtnPropertyDelegateQVector4D::QtnPropertyDelegateQVector4D(QtnPropertyQVector4DBase& owner)
    : QtnPropertyDelegateTypedEx<QtnPropertyQVector4DBase>(owner)
{
    addSubProperty(qtnCreateXProperty(0, &owner));
    addSubProperty(qtnCreateYProperty(0, &owner));
    addSubProperty(qtnCreateZProperty(0, &owner));
    addSubProperty(qtnCreateWProperty(0, &owner));
}

QWidget* QtnPropertyDelegateQVector4D::createValueEditorImpl(QWidget* parent, const QRect& rect, QtnInplaceInfo* inplaceInfo)
{
    return createValueEditorLineEdit(parent, rect, true, inplaceInfo);
}

bool QtnPropertyDelegateQVector4D::propertyValueToStrImpl(QString& strValue) const
{
    QVector4D value = owner().value();
    strValue = QString("%1 , %2 , %3, %4").arg(value.x()).arg(value.y()).arg(value.z()).arg(value.w());
    return true;
}
