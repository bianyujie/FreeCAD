/***************************************************************************
 *   Copyright (c) 2017 Stefan Tröger <stefantroeger@gmx.net>              *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#include "PreCompiled.h"
#ifndef _PreComp_
#include <QMessageBox>
#endif

#include "App/Part.h"
#include "Command.h"
#include "Application.h"
#include "MDIView.h"


using namespace Gui;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===========================================================================
// Std_Part
//===========================================================================
DEF_STD_CMD_A(StdCmdPart);

StdCmdPart::StdCmdPart()
  : Command("Std_Part")
{
    sGroup        = QT_TR_NOOP("Structure");
    sMenuText     = QT_TR_NOOP("Create part");
    sToolTipText  = QT_TR_NOOP("Create a new part and make it active");
    sWhatsThis    = sToolTipText;
    sStatusTip    = sToolTipText;
    sPixmap       = "Geofeaturegroup.svg";
}

void StdCmdPart::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    openCommand("Add a part");
    std::string FeatName = getUniqueObjectName("Part");

    std::string PartName;
    PartName = getUniqueObjectName("Part");
    doCommand(Doc,"App.activeDocument().Tip = App.activeDocument().addObject('App::Part','%s')",PartName.c_str());
    // TODO We really must to set label ourselfs? (2015-08-17, Fat-Zer)
    doCommand(Doc,"App.activeDocument().%s.Label = '%s'", PartName.c_str(),
            QObject::tr(PartName.c_str()).toUtf8().data());
    doCommand(Gui::Command::Gui, "Gui.activeView().setActiveObject('%s', App.activeDocument().%s)",
            PARTKEY, PartName.c_str());

    updateActive();
}

bool StdCmdPart::isActive(void)
{
    return hasActiveDocument();
}

//===========================================================================
// Std_Group
//===========================================================================
DEF_STD_CMD_A(StdCmdGroup);

StdCmdGroup::StdCmdGroup()
  : Command("Std_Group")
{
    sGroup        = QT_TR_NOOP("Structure");
    sMenuText     = QT_TR_NOOP("Create group");
    sToolTipText  = QT_TR_NOOP("Create a new group for ordering objects");
    sWhatsThis    = sToolTipText;
    sStatusTip    = sToolTipText;
    sPixmap       = "Group.svg";
}

void StdCmdGroup::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    openCommand("Add a group");
    std::string FeatName = getUniqueObjectName("Group");

    std::string GroupName;
    GroupName = getUniqueObjectName("Group");
    doCommand(Doc,"App.activeDocument().Tip = App.activeDocument().addObject('App::DocumentObjectGroup','%s')",GroupName.c_str());
    doCommand(Doc,"App.activeDocument().%s.Label = '%s'", GroupName.c_str(),
            QObject::tr(GroupName.c_str()).toUtf8().data());
}

bool StdCmdGroup::isActive(void)
{
    return hasActiveDocument();
}

namespace Gui {

void CreateStructureCommands(void)
{
    CommandManager &rcCmdMgr = Application::Instance->commandManager();

    rcCmdMgr.addCommand(new StdCmdPart());
    rcCmdMgr.addCommand(new StdCmdGroup());
}

} // namespace Gui