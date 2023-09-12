
#include "stdAfx.h"
#include "DbHostAppServices.h"

void _SaveDedicatedObjToFile_func(OdEdCommandContext* pCmdCtx)
{
    OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);

    OdEdUserIO* uIO = pCmdCtx->userIO();
    OdDbDatabasePtr pDb = pDbCmdCtx->database();
    OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();
    OdDbHostAppServices* pSvs = pDb->appServices();


    OdString fname = pIO->getString(OD_T("Enter file name :"));
    OdDbDatabasePtr pnDb = pSvs->createDatabase();


    if (odSystemServices()->accessFile(fname, Oda::kFileRead)) {
     
        try {
            pnDb->readFile(fname);
        }
        catch (const OdError* er)
        {
            uIO->putString("Greate new file");
        }

     
    }
    OdDbBlockTableRecordPtr pMS = pnDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
    OdDbSelectionSetPtr pSSet = pIO->select(L"Select objects:", OdEd::kSelAllowEmpty);
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

    try
    {
        pnDb->writeFile(fname, fileType, outVer, true);
        uIO->putString("ok");
    }
    catch (const OdError& er)
    {
        uIO->putString("no greate");
    }

    pnDb.release();

}