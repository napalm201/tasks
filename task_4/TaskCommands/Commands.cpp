
#include "stdAfx.h"
#include "DbHostAppServices.h"


void _SaveDedicatedObjToFile_func(OdEdCommandContext* pCmdCtx)
{
    OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);

    OdEdUserIO* uIO = pCmdCtx->userIO();
    OdDbDatabasePtr pDb = pDbCmdCtx->database();
    OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();
    OdDbHostAppServices* pSvs = pDb->appServices();

    OdDbSelectionSetPtr pSSet = pIO->select(L"Select objects:", OdEd::kSelAllowEmpty);

    if (pSSet->numEntities() == 0)
    {
        uIO->putString(OdString("Will you select objects"));
        return;
    }

    uIO->putString(OdString("Will you select patch"));

    OdString fname = pIO->getFilePath(OD_T("Enter .dwg file name:"),
        OdEd::kGfpForOpen,
        OD_T("Select .dwg file"),
        OD_T("dwg"),
        OdString::kEmpty,
        OD_T("DXF files (*.dwg)|*.dwg|"));

    OdDbDatabasePtr pnDb = pSvs->createDatabase();
    
    try {
        pnDb->readFile(fname);
    }
    catch (const OdError& er)
    {
        uIO->putString(OdString("Greating new file"));
    }

    OdDbBlockTableRecordPtr pMS = pnDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

    OdDbSelectionSetIteratorPtr pIter = pSSet->newIterator();

    while (!pIter->done())
    {
        OdDbObjectId objId = pIter->objectId();
        OdDbEntityPtr pEnt = objId.openObject();

        if (!pEnt.isNull())
            pMS->appendOdDbEntity(pEnt);

        pIter->next();
    }

    OdDb::SaveType fileType = OdDb::kDwg;
    OdDb::DwgVersion outVer = OdDb::vAC24;

    pnDb->writeFile(fname, fileType, outVer, true);

    pnDb.release();

}