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

void QtnPropertyDelegateValued::createSubItemsImpl(QtnPropertyDelegateDrawContext& context, QList<QtnPropertyDelegateSubItem>& subItems)
{
    // background
    {
        QtnPropertyDelegateSubItem bgItem;
        bgItem.rect = context.rect;

        if (bgItem.rect.isValid())
        {
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
    }

    // active selection
    {
        QtnPropertyDelegateSubItem selItem;
        selItem.rect = context.rect;
        selItem.rect.setRight(context.splitPos);

        if (selItem.rect.isValid())
        {
            selItem.drawHandler = [this](QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item) {
                // highlight background if active property
                if (context.isActive)
                    context.painter->fillRect(item.rect, context.widget->palette().color(QPalette::Highlight));
            };

            subItems.append(selItem);
        }
    }

    // branch node sign
    if (context.hasChildren)
    {
        QtnPropertyDelegateSubItem brItem;
        brItem.rect = context.rect.marginsRemoved(context.margins);
        brItem.rect.setRight(brItem.rect.left() + brItem.rect.height());
        context.margins.setLeft(context.margins.left() + brItem.rect.height());

        if (brItem.rect.isValid())
        {
            brItem.drawHandler = [this](QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item) {
                auto& painter = *context.painter;
                QRectF branchRect = item.rect;
                qreal side = branchRect.height() / 3.5f;

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
                    painter.fillPath(branchPath, context.widget->palette().color(QPalette::Text));
                }
                else
                {
                    painter.setRenderHint(QPainter::Antialiasing, true);
                    painter.fillPath(branchPath, context.widget->palette().color(QPalette::Text));
                    painter.setRenderHint(QPainter::Antialiasing, false);
                }
            };

            brItem.eventHandler = [this](QtnPropertyDelegateEventContext& context, const QtnPropertyDelegateSubItem&) -> bool {
                if (context.event->type() == QEvent::MouseButtonPress)
                {
                    property()->switchStateAuto(QtnPropertyStateCollapsed);
                    return true;
                }

                return false;
            };

            subItems.append(brItem);
        }
    }

    // property name
    {
        QtnPropertyDelegateSubItem nameItem;
        nameItem.rect = context.rect.marginsRemoved(context.margins);
        nameItem.rect.setRight(context.splitPos);

        if (nameItem.rect.isValid())
        {
            nameItem.drawHandler = [this](QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item) {
                QPalette::ColorGroup cg = property()->isEditableByUser() ? QPalette::Active : QPalette::Disabled;
                QPen oldPen = context.painter->pen();
                context.painter->setPen(context.widget->palette().color(cg, (context.isActive) ? QPalette::HighlightedText : QPalette::Text));

                context.painter->drawText(item.rect, Qt::AlignLeading|Qt::AlignVCenter|Qt::TextSingleLine
                                        , qtnElidedText(*context.painter, property()->name(), item.rect));

                context.painter->setPen(oldPen);
            };

            subItems.append(nameItem);
        }
    }

    // property value
    {
        int valueMargin = context.widget->style()->pixelMetric(QStyle::PM_CheckBoxLabelSpacing);
        QtnPropertyDelegateSubItem valueItem;
        valueItem.rect = context.rect.marginsRemoved(context.margins);
        valueItem.rect.setLeft(context.splitPos + valueMargin);

        if (valueItem.rect.isValid())
        {
            valueItem.drawHandler = [this](QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item) {
                QStyle::State state = QStyle::State_Active;
                if (property()->isEditableByUser())
                    state |= QStyle::State_Enabled;
                if (context.isActive)
                {
                    state |= QStyle::State_Selected;
                    state |= QStyle::State_HasFocus;
                }

                // draw property value
               drawValueImpl(*context.painter, item.rect, state, nullptr);
            };

            valueItem.eventHandler = [this](QtnPropertyDelegateEventContext& context, const QtnPropertyDelegateSubItem& item) -> bool {
                bool doEdit = false;
                switch (context.event->type())
                {
                case QEvent::MouseButtonDblClick:
                    doEdit = (context.widget->propertyViewStyle() & QtnPropertyViewStyleDblClickActivation);
                    break;

                case QEvent::MouseButtonRelease:
                    doEdit = !(context.widget->propertyViewStyle() & QtnPropertyViewStyleDblClickActivation);
                    break;

                case QEvent::KeyPress:
                    doEdit = acceptKeyPressedForInplaceEditImpl((QKeyEvent*)context.event);
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

            subItems.append(valueItem);
        }
    }
}

void QtnPropertyDelegateValued::drawValueImpl(QStylePainter& painter, const QRect& rect, const QStyle::State& state, bool* needTooltip) const
{
    QString strValue;
    if (propertyValueToStrImpl(strValue))
    {
        drawValueText(strValue, painter, rect, state, needTooltip);
    }
}

bool QtnPropertyDelegateValued::acceptKeyPressedForInplaceEditImpl(QKeyEvent* keyEvent) const
{
    int key = keyEvent->key();
    return (key == Qt::Key_F2) || (key == Qt::Key_Space) || (key == Qt::Key_Return);
}

QString QtnPropertyDelegateValued::toolTipImpl() const
{
    QString strValue;
    propertyValueToStrImpl(strValue);
    return strValue;
}

void QtnPropertyDelegate::drawValueText(const QString& text, QStylePainter& painter, const QRect& rect, const QStyle::State &state, bool* needTooltip)
{
    Q_UNUSED(state);

    if (text.isEmpty())
        return;

    painter.drawText(rect, Qt::AlignLeading | Qt::AlignVCenter
                     , qtnElidedText(painter, text, rect, needTooltip));
}

QWidget* QtnPropertyDelegateValued::createValueEditorLineEdit(QWidget* parent, const QRect& rect, bool readOnly, QtnInplaceInfo* inplaceInfo)
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

