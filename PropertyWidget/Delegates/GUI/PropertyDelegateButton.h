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

#ifndef PROPERTY_DELEGATE_BUTTON_H
#define PROPERTY_DELEGATE_BUTTON_H

#include "../PropertyDelegate.h"

class QtnPropertyButton;

class QTN_PW_EXPORT QtnPropertyDelegateButton: public QtnPropertyDelegateTyped<QtnPropertyButton, QtnPropertyDelegate>
{
    Q_DISABLE_COPY(QtnPropertyDelegateButton)

public:
    QtnPropertyDelegateButton(QtnPropertyButton& owner);

protected:
    void applyAttributesImpl(const QtnPropertyDelegateAttributes& attributes) override;
    void createSubItemsImpl(QtnPropertyDelegateDrawContext& context, QList<QtnPropertyDelegateSubItem>& subItems) override;

    QString m_title;
};

class QTN_PW_EXPORT QtnPropertyDelegateButtonLink: public QtnPropertyDelegateButton
{
    Q_DISABLE_COPY(QtnPropertyDelegateButtonLink)

public:
    QtnPropertyDelegateButtonLink(QtnPropertyButton& owner);

protected:
    void createSubItemsImpl(QtnPropertyDelegateDrawContext& context, QList<QtnPropertyDelegateSubItem>& subItems) override;

private:
    QCursor m_widgetCursor;
};

#endif // PROPERTY_DELEGATE_BUTTON_H
