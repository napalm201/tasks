#include "stdAfx.h"

#include "RxSysRegistry.h"

#include "RxDynamicModule.h"

#include "TaskCommandsModule.h"


#define CMD_DEF(CmdName, GroupName) \
  extern void _##CmdName##_func(OdEdCommandContext* pCmdCtx);\
  const OdString _##CmdName##_cmd::globalName() const { return OD_T(#CmdName); }\
  const OdString _##CmdName##_cmd::groupName() const { return GroupName; }\
  void _##CmdName##_cmd::execute(OdEdCommandContext* pCmdCtx) { _##CmdName##_func(pCmdCtx); }

#include "TaskCmdDef.h"

#undef CMD_DEF

ODRX_DEFINE_DYNAMIC_MODULE(TaskCommandsModule);

void TaskCommandsModule::initApp()
{
    OdEdCommandStackPtr pCommands = odedRegCmds();

#define CMD_DEF(CmdName, GroupName) \
         pCommands->addCommand(&m_##CmdName##_cmd);
#include "TaskCmdDef.h"
#undef CMD_DEF
}

void TaskCommandsModule::uninitApp()
{
    OdEdCommandStackPtr pCommands = odedRegCmds();

#define CMD_DEF(CmdName, GroupName) \
       pCommands->removeCmd(GroupName, OD_T(#CmdName));
#include "TaskCmdDef.h"
#undef CMD_DEF
}
