/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: http://www.qt-project.org/
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**************************************************************************/

#ifndef OUTLINE_H
#define OUTLINE_H

#include <texteditor/ioutlinewidget.h>
#include <coreplugin/inavigationwidgetfactory.h>
#include <QStackedWidget>
#include <QMenu>

namespace Core {
class IEditor;
}

namespace TextEditor {
namespace Internal {

class OutlineFactory;

class OutlineWidgetStack : public QStackedWidget
{
    Q_OBJECT
public:
    OutlineWidgetStack(OutlineFactory *factory);
    ~OutlineWidgetStack();

    QToolButton *toggleSyncButton();
    QToolButton *filterButton();

    void saveSettings(int position);
    void restoreSettings(int position);

private:
    bool isCursorSynchronized() const;
    QWidget *dummyWidget() const;
    void updateFilterMenu();

private slots:
    void toggleCursorSynchronization();
    void updateCurrentEditor(Core::IEditor *editor);

private:
    QStackedWidget *m_widgetStack;
    OutlineFactory *m_factory;
    QToolButton *m_toggleSync;
    QToolButton *m_filterButton;
    QMenu *m_filterMenu;
    bool m_syncWithEditor;
    int m_position;
};

class OutlineFactory : public Core::INavigationWidgetFactory
{
    Q_OBJECT
public:
    OutlineFactory() {}

    QList<IOutlineWidgetFactory*> widgetFactories() const;
    void setWidgetFactories(QList<IOutlineWidgetFactory*> factories);

    // from INavigationWidgetFactory
    virtual QString displayName() const;
    virtual int priority() const;
    virtual Core::Id id() const;
    virtual QKeySequence activationSequence() const;
    virtual Core::NavigationView createWidget();
    virtual void saveSettings(int position, QWidget *widget);
    virtual void restoreSettings(int position, QWidget *widget);
private:
    QList<IOutlineWidgetFactory*> m_factories;
};

} // namespace Internal
} // namespace TextEditor

#endif // OUTLINE_H
