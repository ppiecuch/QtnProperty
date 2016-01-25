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

#include "PropertyDelegate.h"

#include <QLineEdit>
#include <QKeyEvent>

QString qtnElidedText(const QPainter& painter, const QString& text, const QRect& rect, bool* elided)
{
    QString newText = painter.fontMetrics().elidedText(text, Qt::ElideRight, rect.width());

    if (elided)
        *elided = (newText != text);

    return newText;
}

QtnPropertyBase* QtnPropertyDelegate::property()
{
    return propertyImpl();
}

const QtnPropertyBase* QtnPropertyDelegate::propertyImmutable() const
{
    return propertyImmutableImpl();
}

int QtnPropertyDelegate::subPropertyCount() const
{
    return subPropertyCountImpl();
}

QtnPropertyBase* QtnPropertyDelegate::subProperty(int index)
{
    Q_ASSERT(index >= 0 && index < subPropertyCount());
    return subPropertyImpl(index);
}

void QtnPropertyDelegate::applyAttributes(const QtnPropertyDelegateAttributes& attributes)
{
    applyAttributesImpl(attributes);
}

void QtnPropertyDelegate::createSubItems(QtnPropertyDelegateDrawContext& context, QList<QtnPropertyDelegateSubItem>& subItems)
{
    createSubItemsImpl(context, subItems);
}

QStyle::State QtnPropertyDelegate::state(bool isActive, QtnPropertyDelegateSubItemState subState) const
{
    QStyle::State state = QStyle::State_Active;
    if (propertyImmutable()->isEditableByUser())
        state |= QStyle::State_Enabled;
    if (isActive)
    {
        state |= QStyle::State_Selected;
        state |= QStyle::State_HasFocus;
    }

    if (subState == QtnSubItemStateUnderCursor)
        state |= QStyle::State_MouseOver;
    else if (subState == QtnSubItemStatePushed)
        state |= QStyle::State_Sunken;

    return state;
}

void QtnPropertyDelegateWithValue::createSubItemsImpl(QtnPropertyDelegateDrawContext& context, QList<QtnPropertyDelegateSubItem>& subItems)
{
    addSubItemBackground(context, subItems);
    addSubItemSelection(context, subItems);
    addSubItemBranchNode(context, subItems);
    addSubItemName(context, subItems);
    addSubItemValue(context, subItems);
}

void QtnPropertyDelegateWithValue::addSubItemBackground(QtnPropertyDelegateDrawContext& context, QList<QtnPropertyDelegateSubItem>& subItems)
{
    QtnPropertyDelegateSubItem bgItem;
    bgItem.rect = context.rect;

    if (!bgItem.rect.isValid())
        return;

    bgItem.drawHandler = [this](QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item) {

        auto& painter = *context.painter;
        const auto& rect = item.rect;
        auto splitPos = context.splitPos;

        QPen oldPen = painter.pen();
        QPen linesPen(context.widget->palette().color(QPalette::Button));
        painter.setPen(linesPen);

        // draw item borders
        painter.drawLine(rect.bottomLeft(), rect.bottomRight());
        painter.drawLine(splitPos, rect.top(), splitPos, rect.bottom());

        painter.setPen(oldPen);
    };

    subItems.append(bgItem);
}

void QtnPropertyDelegateWithValue::addSubItemSelection(QtnPropertyDelegateDrawContext& context, QList<QtnPropertyDelegateSubItem>& subItems)
{
    QtnPropertyDelegateSubItem selItem;
    selItem.rect = context.rect;
    selItem.rect.setRight(context.splitPos);

    if (!selItem.rect.isValid())
        return;

    selItem.drawHandler = [this](QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item) {
        // highlight background if active property
        if (context.isActive)
            context.painter->fillRect(item.rect, context.widget->palette().color(QPalette::Highlight));
    };

    subItems.append(selItem);
}

void QtnPropertyDelegateWithValue::addSubItemBranchNode(QtnPropertyDelegateDrawContext& context, QList<QtnPropertyDelegateSubItem>& subItems)
{
    if (!context.hasChildren)
        return;

    QtnPropertyDelegateSubItem brItem(true);
    brItem.rect = context.rect.marginsRemoved(context.margins);
    brItem.rect.setWidth(brItem.rect.height());
    context.margins.setLeft(context.margins.left() + brItem.rect.height());

    if (!brItem.rect.isValid())
        return;

    brItem.drawHandler = [this](QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item) {
        auto& painter = *context.painter;
        QRectF branchRect = item.rect;
        qreal side = branchRect.height() / 3.5f;
        QColor fillClr = context.widget->palette().color(QPalette::Text);
        QColor outlineClr = (item.state() != QtnSubItemStateNone)
                    ? Qt::blue
                    : context.widget->palette().color(QPalette::Text);

        painter.save();
        painter.setPen(outlineClr);

        QPainterPath branchPath;
        if (propertyImmutable()->stateLocal() & QtnPropertyStateCollapsed)
        {
            branchPath.moveTo(branchRect.left() + side, branchRect.top() + side);
            branchPath.lineTo(branchRect.right() - side - 1, branchRect.top() + branchRect.height() / 2.f);
            branchPath.lineTo(branchRect.left() + side, branchRect.bottom() - side);
            branchPath.closeSubpath();
        }
        else
        {
            branchPath.moveTo(branchRect.left() + side, branchRect.top() + side);
            branchPath.lineTo(branchRect.right() - side, branchRect.top() + side);
            branchPath.lineTo(branchRect.left() + branchRect.width() / 2.f, branchRect.bottom() - side - 1);
            branchPath.closeSubpath();
        }

        if (painter.testRenderHint(QPainter::Antialiasing))
        {
            painter.fillPath(branchPath, fillClr);
            painter.drawPath(branchPath);
        }
        else
        {
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.fillPath(branchPath, fillClr);
            painter.drawPath(branchPath);
            painter.setRenderHint(QPainter::Antialiasing, false);
        }

        painter.restore();
    };

    brItem.eventHandler = [this](QtnPropertyDelegateEventContext& context, const QtnPropertyDelegateSubItem&) -> bool {
        if ((context.eventType() == QEvent::MouseButtonPress) || (context.eventType() == QEvent::MouseButtonDblClick))
        {
            property()->switchStateAuto(QtnPropertyStateCollapsed);
            return true;
        }

        return false;
    };

    subItems.append(brItem);
}

void QtnPropertyDelegateWithValue::addSubItemName(QtnPropertyDelegateDrawContext& context, QList<QtnPropertyDelegateSubItem>& subItems)
{
    QtnPropertyDelegateSubItem nameItem;
    nameItem.rect = context.rect.marginsRemoved(context.margins);
    nameItem.rect.setRight(context.splitPos);

    if (!nameItem.rect.isValid())
        return;

    nameItem.drawHandler = [this](QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item) {
        context.painter->save();

        QPalette::ColorGroup cg = property()->isEditableByUser() ? QPalette::Active : QPalette::Disabled;
        context.painter->setPen(context.widget->palette().color(cg, (context.isActive) ? QPalette::HighlightedText : QPalette::Text));

        context.painter->drawText(item.rect, Qt::AlignLeading|Qt::AlignVCenter|Qt::TextSingleLine
                                , qtnElidedText(*context.painter, property()->name(), item.rect));

        context.painter->restore();
    };

    subItems.append(nameItem);
}

void QtnPropertyDelegateWithValue::addSubItemValue(QtnPropertyDelegateDrawContext& context, QList<QtnPropertyDelegateSubItem>& subItems)
{
    QtnPropertyDelegateSubItem valueItem;
    valueItem.rect = context.rect.marginsRemoved(context.margins);
    valueItem.rect.setLeft(context.splitPos + context.widget->valueLeftMargin());

    if (valueItem.rect.isValid() && createSubItemValueImpl(context, valueItem))
        subItems.append(valueItem);
}

bool QtnPropertyDelegateWithValueEditor::createSubItemValueImpl(QtnPropertyDelegateDrawContext&, QtnPropertyDelegateSubItem& subItemValue)
{
    subItemValue.drawHandler = [this](QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item) {
        // draw property value
       drawValueImpl(*context.painter, item.rect, state(context.isActive, item.state()), nullptr);
    };

    subItemValue.eventHandler = [this](QtnPropertyDelegateEventContext& context, const QtnPropertyDelegateSubItem& item) -> bool {
        bool doEdit = false;
        switch (context.eventType())
        {
        case QEvent::MouseButtonDblClick:
            doEdit = (context.widget->propertyViewStyle() & QtnPropertyViewStyleDblClickActivation);
            break;

        case QEvent::MouseButtonRelease:
            doEdit = !(context.widget->propertyViewStyle() & QtnPropertyViewStyleDblClickActivation);
            break;

        case QEvent::KeyPress:
            doEdit = acceptKeyPressedForInplaceEditImpl(context.eventAs<QKeyEvent>());
            break;
        }

        if (doEdit)
        {
            QtnInplaceInfo inplaceInfo;
            inplaceInfo.activationEvent = context.event;
            QWidget* editor = createValueEditorImpl(context.widget->viewport(), item.rect, &inplaceInfo);
            if (!editor)
                return false;

            if (editor->objectName().isEmpty())
                editor->setObjectName("QtnPropertyValueEditor");

            if (!editor->isVisible())
                editor->show();

            qtnStartInplaceEdit(editor);

            return true;
        }

        return false;
    };

    return true;
}

void QtnPropertyDelegateWithValueEditor::drawValueImpl(QStylePainter& painter, const QRect& rect, const QStyle::State& state, bool* needTooltip) const
{
    QString strValue;
    if (propertyValueToStrImpl(strValue))
    {
        drawValueText(strValue, painter, rect, state, needTooltip);
    }
}

bool QtnPropertyDelegateWithValueEditor::acceptKeyPressedForInplaceEditImpl(QKeyEvent* keyEvent) const
{
    int key = keyEvent->key();
    return (key == Qt::Key_F2) || (key == Qt::Key_Space) || (key == Qt::Key_Return);
}

void QtnPropertyDelegate::drawValueText(const QString& text, QStylePainter& painter, const QRect& rect, QStyle::State state, bool* needTooltip)
{
    Q_UNUSED(state);

    if (text.isEmpty())
        return;

    painter.drawText(rect, Qt::AlignLeading | Qt::AlignVCenter
                     , qtnElidedText(painter, text, rect, needTooltip));
}

QWidget* QtnPropertyDelegateWithValueEditor::createValueEditorLineEdit(QWidget* parent, const QRect& rect, bool readOnly, QtnInplaceInfo* inplaceInfo)
{
    QLineEdit* lineEdit = new QLineEdit(parent);
    lineEdit->setGeometry(rect);
    lineEdit->setReadOnly(readOnly);

    QString strValue;
    propertyValueToStrImpl(strValue);
    lineEdit->setText(strValue);

    if (inplaceInfo)
    {
        lineEdit->selectAll();
    }

    return lineEdit;
}

void QtnPropertyDelegateSlideBox::applyAttributesImpl(const QtnPropertyDelegateAttributes& attributes)
{
    qtnGetAttribute(attributes, "fillColor", m_boxFillColor);
}

bool QtnPropertyDelegateSlideBox::createSubItemValueImpl(QtnPropertyDelegateDrawContext&, QtnPropertyDelegateSubItem& subItemValue)
{
    subItemValue.trackState();
    subItemValue.drawHandler = qtnMemFn(this, &QtnPropertyDelegateFloatSlideBox::draw);
    subItemValue.eventHandler = qtnMemFn(this, &QtnPropertyDelegateFloatSlideBox::event);
    return true;
}

void QtnPropertyDelegateSlideBox::draw(QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item)
{
    float valueInterval = owner().maxValue() - owner().minValue();
    if (valueInterval <= 0)
        return;

    float value = (item.state() == QtnSubItemStatePushed) ? m_dragValue : owner().value();
    float valuePart = (value - owner().minValue())/valueInterval;

    auto boxRect = item.rect;
    boxRect.adjust(-1, 1, 0, -1);
    auto valueRect = boxRect;
    valueRect.setRight(valueRect.left() + int(valuePart * valueRect.width()));
    valueRect.setTop(valueRect.bottom()-2);

    auto& painter = *context.painter;

    painter.save();

    painter.setPen(m_boxFillColor.lighter(110));
    painter.drawLine(boxRect.left(),boxRect.bottom(),boxRect.left(),boxRect.bottom()-4);
    painter.drawLine(boxRect.left()+boxRect.width()/2,boxRect.bottom(),boxRect.left()+boxRect.width()/2,boxRect.bottom()-4);
    painter.drawLine(boxRect.right(),boxRect.bottom(),boxRect.right(),boxRect.bottom()-4);
    painter.drawLine(boxRect.left()+boxRect.width()*0.25,boxRect.bottom(),boxRect.left()+boxRect.width()*0.25,boxRect.bottom()-3);
    painter.drawLine(boxRect.left()+boxRect.width()*0.75,boxRect.bottom(),boxRect.left()+boxRect.width()*0.75,boxRect.bottom()-3);

	QLinearGradient gradient(boxRect.topLeft(), boxRect.bottomRight()); // diagonal gradient from top-left to bottom-right
	gradient.setColorAt(0, m_boxFillColor.lighter(125));
	gradient.setColorAt(1, m_boxFillColor);
    painter.fillRect(valueRect, gradient);

    painter.restore();

    boxRect.adjust(context.widget->valueLeftMargin(), 0, 0, 0);
    auto strValue = QString::number(owner().value());
    drawValueText(strValue, painter, boxRect, state(context.isActive), nullptr);
}

bool QtnPropertyDelegateSlideBox::event(QtnPropertyDelegateEventContext& context, const QtnPropertyDelegateSubItem& item)
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

void QtnPropertyDelegateSlideBox::updateDragValue(int x, const QRect& rect)
{
    float valuePart = float(x - rect.left()) / rect.width();
    if (valuePart < 0)
        valuePart = 0;
    else if (valuePart > 1.f)
        valuePart = 1.f;

    m_dragValue = owner().minValue() + valuePart * (owner().maxValue() - owner().minValue());
}
