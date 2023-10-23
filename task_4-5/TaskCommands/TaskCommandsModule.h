
#ifndef TASKCOMMAND_INCLUDED
#define TASKCOMMAND_INCLUDED

#include "RxDynamicModule.h"
#include "Ed/EdCommandStack.h"
#include "OdDbEclipseGripPointsPe.h"
#include "StaticRxObject.h"

//#define _TOOLKIT_IN_DLL_
#define ODDB_COMMANDS_GROUP_NAME OD_T("ODDB_EDIT")

#define CMD_DEF(CmdName, GroupName) \
class _##CmdName##_cmd : public OdEdCommand \
{ \
public: \
   const OdString groupName() const ;\
   const OdString globalName() const ;\
   void execute(OdEdCommandContext* pCmdCtx) ;\
};

#include "TaskCmdDef.h"

#undef CMD_DEF


class TaskCommandsModule : public OdRxModule
{

#define CMD_DEF(CmdName, GroupName) \
  OdStaticRxObject<_##CmdName##_cmd> m_##CmdName##_cmd;
#include "TaskCmdDef.h"
#undef CMD_DEF

	OdStaticRxObject<OdDbEclipseGripPointsPE> _egp;

public:
	void initApp();
	void uninitApp();
};


#endif



