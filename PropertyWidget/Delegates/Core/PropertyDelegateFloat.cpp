/*
   Copyright (c) 2012-1015 Alex Zhondin <qtinuum.team@gmail.com>

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

#include "PropertyDelegateFloat.h"
#include "../../../Core/Core/PropertyFloat.h"
#include "../PropertyDelegateFactory.h"
#include "../PropertyEditorHandler.h"

#include <QDoubleSpinBox>
#include <QKeyEvent>

void regFloatDelegates()
{
    QtnPropertyDelegateFactory::staticInstance()
        .registerDelegateDefault(&QtnPropertyFloatBase::staticMetaObject
                                , &qtnCreateDelegate<QtnPropertyDelegateFloat, QtnPropertyFloatBase>
                                , "SpinBox");

    QtnPropertyDelegateFactory::staticInstance()
        .registerDelegate(&QtnPropertyFloatBase::staticMetaObject
                                , &qtnCreateDelegate<QtnPropertyDelegateFloatSlideBox, QtnPropertyFloatBase>
                                , "SliderBox");
}

class QtnPropertyFloatSpinBoxHandler: public QtnPropertyEditorHandler<QtnPropertyFloatBase, QDoubleSpinBox>
{
public:
    QtnPropertyFloatSpinBoxHandler(QtnPropertyFloatBase& property, QDoubleSpinBox& editor)
        : QtnPropertyEditorHandlerType(property, editor)
    {
        if (!property.isEditableByUser())
            editor.setReadOnly(true);

        editor.setRange(property.minValue(), property.maxValue());
        editor.setSingleStep(property.stepValue());
        editor.setDecimals(6);

        updateEditor();

        QObject::connect(  &editor, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)
                         , this, &QtnPropertyFloatSpinBoxHandler::onValueChanged);
    }

private:
    void updateEditor() override
    {
        editor().setValue((float)property());
    }

    void onValueChanged(double value)
    {
        property() = (float)value;
    }
};

QWidget* QtnPropertyDelegateFloat::createValueEditorImpl(QWidget* parent, const QRect& rect, QtnInplaceInfo* inplaceInfo)
{
    QDoubleSpinBox *spinBox = new QDoubleSpinBox(parent);
    spinBox->setGeometry(rect);

    new QtnPropertyFloatSpinBoxHandler(owner(), *spinBox);

    if (inplaceInfo)
    {
        spinBox->selectAll();
    }

    return spinBox;
}

bool QtnPropertyDelegateFloat::propertyValueToStrImpl(QString& strValue) const
{
    strValue = QString::number(owner().value());
    return true;
}


bool QtnPropertyDelegateFloatSlideBox::createSubItemValueImpl(QtnPropertyDelegateDrawContext&, QtnPropertyDelegateSubItem& subItemValue)
{
    subItemValue.trackState();
    subItemValue.drawHandler = qtnMemFn(this, &QtnPropertyDelegateFloatSlideBox::draw);
    subItemValue.eventHandler = qtnMemFn(this, &QtnPropertyDelegateFloatSlideBox::event);
    return true;
}

void QtnPropertyDelegateFloatSlideBox::draw(QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item)
{
    float valueInterval = owner().maxValue() - owner().minValue();
    if (valueInterval <= 0)
        return;

    float value = (item.state() == QtnSubItemStatePushed) ? m_dragValue : owner().value();
    float valuePart = (value - owner().minValue())/valueInterval;

    auto boxBorderColor = (item.state() == QtnSubItemStateNone) ? m_boxFillColor : m_boxFillColor.darker(150);

    auto boxRect = item.rect;
    boxRect.adjust(1, 1, -1, -1);

    auto valueRect = boxRect;
    valueRect.setWidth(int(valuePart * valueRect.width()));

    auto& painter = *context.painter;

    painter.save();

    painter.fillRect(valueRect, m_boxFillColor);

    painter.setPen(boxBorderColor);
    painter.drawRect(valueRect);
    painter.drawRect(boxRect);

    painter.restore();

    boxRect.adjust(context.widget->valueLeftMargin(), 0, 0, 0);
    auto strValue = QString::number(value);
    drawValueText(strValue, painter, boxRect, state(context.isActive, item.state()), nullptr);
}

bool QtnPropertyDelegateFloatSlideBox::event(QtnPropertyDelegateEventContext& context, const QtnPropertyDelegateSubItem& item)
{
    switch (context.eventType())
    {
    case QEvent::KeyPress:
    {
        int key = context.eventAs<QKeyEvent>()->key();

        if ((key == Qt::Key_Plus) || (key == Qt::Key_Equal))
            owner().incrementValue(1);
        else if ((key == Qt::Key_Minus) || (key == Qt::Key_Underscore))
            owner().incrementValue(-1);
        else
            return false;

        return true;
    } break;

    case QEvent::Wheel:
    {
        int steps = context.eventAs<QWheelEvent>()->angleDelta().y()/120;
        owner().incrementValue(steps);
        return true;
    } break;


    case QEvent::MouseMove:
    {
        if (item.state() == QtnSubItemStatePushed)
        {
            updateDragValue(context.eventAs<QMouseEvent>()->x(), item.rect);
            context.widget->viewport()->update();
        }
        return true;
    } break;

    case QtnPropertyDelegateSubItem::SubItemReleaseMouse:
    {
        //updateDragValue(context.eventAs<QMouseEvent>()->x(), item.rect);
        owner().setValue(m_dragValue);
        return true;
    } break;

    default:
        return false;
    }
}

void QtnPropertyDelegateFloatSlideBox::updateDragValue(int x, const QRect& rect)
{
    float valuePart = float(x - rect.left()) / rect.width();
    if (valuePart < 0)
        valuePart = 0;
    else if (valuePart > 1.f)
        valuePart = 1.f;

    m_dragValue = owner().minValue() + valuePart * (owner().maxValue() - owner().minValue());
}
