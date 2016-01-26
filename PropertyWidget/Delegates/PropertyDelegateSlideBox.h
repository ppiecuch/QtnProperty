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

#ifndef QTN_PROPERTY_DELEGATE_SLIDEBOX_H
#define QTN_PROPERTY_DELEGATE_SLIDEBOX_H

#include "PropertyDelegate.h"

template <typename PropertyClass, typename DelegateClass = QtnPropertyDelegateWithValueEditor>
class QTN_PW_EXPORT QtnPropertyDelegateSlideBox: public QtnPropertyDelegateTyped<PropertyClass, DelegateClass>
{
    Q_DISABLE_COPY(QtnPropertyDelegateSlideBox)

public:
    QtnPropertyDelegateSlideBox(PropertyClass& owner)
        : QtnPropertyDelegateTyped<PropertyClass, DelegateClass>(owner)
    {
        m_boxFillColor = QColor::fromRgb(200, 200, 255);
        m_dragValue = 0;
    }

protected:
    void applyAttributesImpl(const QtnPropertyDelegateAttributes& attributes) override
	{
    	qtnGetAttribute(attributes, "fillColor", m_boxFillColor);
	}
    bool createSubItemValueImpl(QtnPropertyDelegateDrawContext& context, QtnPropertyDelegateSubItem& subItemValue) override
	{
	    subItemValue.trackState();
	    subItemValue.drawHandler = qtnMemFn(this, &QtnPropertyDelegateSlideBox::draw);
	    subItemValue.eventHandler = qtnMemFn(this, &QtnPropertyDelegateSlideBox::event);
	    return true;
	}

protected:
    void draw(QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item)
	{
	    float valueInterval = this->owner().maxValue() - this->owner().minValue();
	    if (valueInterval <= 0)
	        return;
	
	    float value = (item.state() == QtnSubItemStatePushed) ? m_dragValue : this->owner().value();
	    float valuePart = (value - this->owner().minValue())/valueInterval;
	
	    auto boxRect = item.rect;
	    boxRect.adjust(-1, 1, 0, -1);
	    auto valueRect = boxRect;
	    valueRect.setRight(valueRect.left() + int(valuePart * valueRect.width()));
	    valueRect.setTop(valueRect.bottom()-2);
	
	    auto& painter = *context.painter;
	
	    painter.save();
	
	    painter.setPen(m_boxFillColor.lighter(110));
	    painter.drawLine(boxRect.left(),boxRect.bottom(),boxRect.left(),boxRect.bottom()-4);
	    painter.drawLine(boxRect.left()+boxRect.width()/2,boxRect.bottom(),boxRect.left()+boxRect.width()/	2,boxRect.bottom()-4);
	    painter.drawLine(boxRect.right(),boxRect.bottom(),boxRect.right(),boxRect.bottom()-4);
	    painter.drawLine(boxRect.left()+boxRect.width()*0.25,boxRect.bottom(),boxRect.left()+	boxRect.width()*0.25,boxRect.bottom()-3);
	    painter.drawLine(boxRect.left()+boxRect.width()*0.75,boxRect.bottom(),boxRect.left()+	boxRect.width()*0.75,boxRect.bottom()-3);
	
		QLinearGradient gradient(boxRect.topLeft(), boxRect.bottomRight()); // diagonal gradient from top-	left to bottom-right
		gradient.setColorAt(0, m_boxFillColor.lighter(125));
		gradient.setColorAt(1, m_boxFillColor);
	    painter.fillRect(valueRect, gradient);
	
	    painter.restore();
	
	    boxRect.adjust(context.widget->valueLeftMargin(), 0, 0, 0);
	    auto strValue = QString::number(this->owner().value());
	    this->drawValueText(strValue, painter, boxRect, this->state(context.isActive, item.state()), nullptr);
	}
    bool event(QtnPropertyDelegateEventContext& context, const QtnPropertyDelegateSubItem& item)
	{
	    switch (context.eventType())
	    {
	    case QEvent::KeyPress:
	    {
	        int key = context.eventAs<QKeyEvent>()->key();
	
	        if ((key == Qt::Key_Plus) || (key == Qt::Key_Equal))
	            this->owner().incrementValue(1);
	        else if ((key == Qt::Key_Minus) || (key == Qt::Key_Underscore))
	            this->owner().incrementValue(-1);
	        else
	            return false;
	
	        return true;
	    } break;
	
	    case QEvent::Wheel:
	    {
	        int steps = context.eventAs<QWheelEvent>()->angleDelta().y()/120;
	        this->owner().incrementValue(steps);
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
	        this->owner().setValue(m_dragValue);
	        return true;
	    } break;
	
	    default:
	        return false;
	    }
	}
    void updateDragValue(int x, const QRect& rect)
	{
	    float valuePart = float(x - rect.left()) / rect.width();
	    if (valuePart < 0)
	        valuePart = 0;
	    else if (valuePart > 1.f)
	        valuePart = 1.f;
	
	    m_dragValue = this->owner().minValue() + valuePart * (this->owner().maxValue() - this->owner().minValue());
	}

    QColor m_boxFillColor;
    float m_dragValue;
};

#endif // QTN_PROPERTY_DELEGATE_SLIDEBOX_H
