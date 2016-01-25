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

#include "PropertyDelegateButton.h"
#include "../../../Core/GUI/PropertyButton.h"
#include "../PropertyDelegateFactory.h"
#include <QStyleOptionButton>

void regButtonDelegates()
{
    QtnPropertyDelegateFactory::staticInstance()
      .registerDelegateDefault(&QtnPropertyButton::staticMetaObject
                   , &qtnCreateDelegate<QtnPropertyDelegateButton, QtnPropertyButton>
                   , "Button");

    QtnPropertyDelegateFactory::staticInstance()
      .registerDelegate(&QtnPropertyButton::staticMetaObject
                   , &qtnCreateDelegate<QtnPropertyDelegateButtonLink, QtnPropertyButton>
                   , "Link");
}

QtnPropertyDelegateButton::QtnPropertyDelegateButton(QtnPropertyButton& owner)
    : QtnPropertyDelegateTyped<QtnPropertyButton, QtnPropertyDelegate>(owner)
{
    m_title = owner.name();
}

void QtnPropertyDelegateButton::applyAttributesImpl(const QtnPropertyDelegateAttributes& attributes)
{
    qtnGetAttribute(attributes, "title", m_title);
}

void QtnPropertyDelegateButton::createSubItemsImpl(QtnPropertyDelegateDrawContext& context, QList<QtnPropertyDelegateSubItem>& subItems)
{
    QtnPropertyDelegateSubItem buttonItem(true);
    buttonItem.rect = context.rect;

    buttonItem.drawHandler = [this](QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item) {

        auto style = context.style();

        QStyleOptionButton option;
        context.initStyleOption(option);

        option.state = state(context.isActive, item.state());

        // dont initialize styleObject from widget for QWindowsVistaStyle
        // this disables buggous animations
        if (style->inherits("QWindowsVistaStyle"))
            option.styleObject = nullptr;

        option.rect = item.rect;
        option.text = m_title;

        owner().invokePreDrawButton(&option);

        // draw button
        style->drawControl(QStyle::CE_PushButton, &option, context.painter, context.widget);
    };

    buttonItem.eventHandler = [this](QtnPropertyDelegateEventContext& context, const QtnPropertyDelegateSubItem&) -> bool {
        bool doClick = false;
        switch (context.eventType())
        {
        case QtnPropertyDelegateSubItem::SubItemReleaseMouse:
            doClick = true;
            break;

        case QEvent::KeyPress:
            int key = context.eventAs<QKeyEvent>()->key();
            doClick = (key == Qt::Key_Space) || (key == Qt::Key_Return);
            break;
        }

        if (doClick)
        {
            owner().invokeClick();
            return true;
        }

        return false;
    };

    subItems.append(buttonItem);
}

QtnPropertyDelegateButtonLink::QtnPropertyDelegateButtonLink(QtnPropertyButton& owner)
    : QtnPropertyDelegateButton(owner)
{
}

void QtnPropertyDelegateButtonLink::createSubItemsImpl(QtnPropertyDelegateDrawContext& context, QList<QtnPropertyDelegateSubItem>& subItems)
{
    QtnPropertyDelegateSubItem linkItem(true);
    linkItem.rect = context.rect.marginsRemoved(context.margins);
    linkItem.rect.setWidth(context.painter->fontMetrics().width(m_title));

    linkItem.drawHandler = [this](QtnPropertyDelegateDrawContext& context, const QtnPropertyDelegateSubItem& item) {

        context.painter->save();

        QColor linkColor = context.palette().color(context.colorGroup(), QPalette::Link);
        switch (item.state())
        {
        case QtnSubItemStateUnderCursor:
            linkColor = linkColor.lighter();
            break;

        case QtnSubItemStatePushed:
            linkColor = linkColor.darker();
            break;

        default:;
        }

        context.painter->setPen(linkColor);

        context.painter->drawText(item.rect, Qt::AlignLeading | Qt::AlignVCenter, m_title);

        context.painter->restore();
    };

    linkItem.eventHandler = [this](QtnPropertyDelegateEventContext& context, const QtnPropertyDelegateSubItem&) -> bool {
        bool doClick = false;
        switch (context.eventType())
        {
        case QEvent::KeyPress:
        {
            int key = context.eventAs<QKeyEvent>()->key();
            doClick = (key == Qt::Key_Space) || (key == Qt::Key_Return);
        } break;

        case QtnPropertyDelegateSubItem::SubItemActivated:
        {
            m_widgetCursor = context.widget->cursor();
            context.widget->setCursor(Qt::PointingHandCursor);
        } break;

        case QtnPropertyDelegateSubItem::SubItemDeactivated:
        {
            context.widget->setCursor(m_widgetCursor);
        } break;

        case QtnPropertyDelegateSubItem::SubItemReleaseMouse:
        {
            doClick = true;
        } break;

        default:
            ;
        }

        if (doClick)
        {
            owner().invokeClick();
            return true;
        }

        return false;
    };

    subItems.append(linkItem);
}
