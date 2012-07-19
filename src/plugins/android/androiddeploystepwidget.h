/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 BogDan Vatra <bog_dan_ro@yahoo.com>
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

#ifndef ANDROIDDEPLOYSTEPWIDGET_H
#define ANDROIDDEPLOYSTEPWIDGET_H

#include <projectexplorer/buildstep.h>

QT_BEGIN_NAMESPACE
namespace Ui {
    class AndroidDeployStepWidget;
}
QT_END_NAMESPACE

namespace Android {
namespace Internal {
class AndroidDeployStep;

class AndroidDeployStepWidget : public ProjectExplorer::BuildStepConfigWidget
{
    Q_OBJECT

public:
    AndroidDeployStepWidget(AndroidDeployStep *step);
    ~AndroidDeployStepWidget();

private slots:
    void resetAction();
    void setDeployLocalQtLibs();
    void setQASIPackagePath();
    void useLocalQtLibsStateChanged(int);
    void editRulesFile();

private:
    virtual QString summaryText() const;
    virtual QString displayName() const;

    Ui::AndroidDeployStepWidget *ui;
    AndroidDeployStep *m_step;
};

} // namespace Internal
} // namespace Android

#endif // ANDROIDDEPLOYSTEPWIDGET_H
