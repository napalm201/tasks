
#include "stdAfx.h"

#include <ctime>
#include <sstream>
#include <DbLayerTableRecord.h>


void _SaveDedicatedObjToFile_func(OdEdCommandContext* pCmdCtx)
{
    OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);

    OdDbDatabasePtr pDb = pDbCmdCtx->database();
    OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();

    OdString fname = pIO->getString(OD_T("Enter file name :"));

    OdDbDatabasePtr pnDb;

    try
    {
        pnDb = pDb->appServices()->readFile(fname);
    }
    catch (const OdError& er)
    {
        pnDb = pDb->appServices()->createDatabase();

        pIO->putString("File will greate" + er.code() + er.description());
    }

    OdDbSelectionSetPtr pSSet = pIO->select(L"Select objects:", OdEd::kSelAllowEmpty);
    OdDbObjectIdArray arraysId = pSSet->objectIdArray();

    if (arraysId.empty())
    {
        pIO->putString("No select objects");
        return;
    }

    OdDbIdMappingPtr pMap = OdDbIdMapping::createObject();
    pMap->setDestDb(pnDb);

    pDb->wblockCloneObjects(arraysId, pnDb->getModelSpaceId(), *pMap, OdDb::kDrcReplace);

    OdDb::SaveType fileType = OdDb::kDwg;
    OdDb::DwgVersion outVer = OdDb::vAC24;

    try
    {
        pnDb->writeFile(fname, fileType, outVer, true);
        pIO->putString("Saved");
    }
    catch (const OdError& er)
    {
        pIO->putString("NO Saved");
    }

    pnDb.release();

}

void _ChangeColorNoSelect_func(OdEdCommandContext* pCmdCtx)
{
    clock_t start_time = clock();

    OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
    OdDbDatabasePtr pDb = pDbCmdCtx->database();
    OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();

    OdDbSelectionSetPtr pSSet = pIO->select(L"Select objects:", OdEd::kSelAllowEmpty);
    OdDbObjectIdArray arraysId = pSSet->objectIdArray();

    OdDbBlockTablePtr pBlockTbl = pDb->getBlockTableId().openObject();
    OdDbSymbolTableIteratorPtr  blockIt = pBlockTbl->newIterator();

    const OdCmColor exampleColor(OdCmEntityColor::kByColor);

    OdCmColor color = pIO->getColor("Enter color", 0, &exampleColor);

    for (; !blockIt->done(); blockIt->step())
    {
        OdDbBlockTableRecordPtr block = blockIt->getRecordId().safeOpenObject(OdDb::kForRead);

        OdDbObjectIteratorPtr pEntIter = block->newIterator();

        for (; !pEntIter->done(); pEntIter->step())
        {
            OdDbEntityPtr pEn = pEntIter->entity(OdDb::kForWrite);

            if (!arraysId.contains(pEntIter->objectId()))
            {
                pEn->setColor(color);
            }

        }
    }

    clock_t end_time = clock();

    double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    char buffer[sizeof(double)];
    snprintf(buffer, sizeof(buffer), "%.4f", elapsed_time);

    OdString resT(buffer);

    pIO->putString(resT);
}



OdDbObjectId greateLineType(OdDbDatabasePtr pDb, OdDbUserIO* pIO)
{
    OdDbLinetypeTablePtr pLinetypes = pDb->getLinetypeTableId().safeOpenObject(OdDb::kForWrite);

    OdDbLinetypeTableRecordPtr pLinetype = OdDbLinetypeTableRecord::createObject();

    OdString name = pIO->getString("Name for linetype");

    pLinetype->setName(name);

    OdDbObjectId linetypeId = pLinetypes->add(pLinetype);

    pLinetype->setNumDashes(4);

    pLinetype->setDashLengthAt(0, 0.5);
    pLinetype->setDashLengthAt(1, 0.25);
    pLinetype->setDashLengthAt(2, 0.25);
    pLinetype->setDashLengthAt(3, 0.25);

    pLinetype->setTextAt(0, "-");
    pLinetype->setTextAt(1, " ");
    pLinetype->setTextAt(2, "A");
    pLinetype->setTextAt(3, " ");

    pLinetype->setShapeIsUcsOrientedAt(2, true);

    return linetypeId;
}

OdDbObjectId greateLayer(OdDbDatabasePtr pDb, OdDbUserIO* pIO)
{
    OdDbLayerTablePtr pLayers = pDb->getLayerTableId().safeOpenObject(OdDb::kForWrite);

    OdDbLayerTableRecordPtr pLayer = OdDbLayerTableRecord::createObject();

    OdString name = pIO->getString("Name for layer");

    pLayer->setName(name);

    OdCmColor color = pIO->getColor("Enter color");

    pLayer->setColor(color);

    OdDbObjectId linetype = greateLineType(pDb, pIO);

    pLayer->setLinetypeObjectId(linetype);

    OdDbObjectId layerId = pLayers->add(pLayer);

    return layerId;
}

void _AssignLayerToLine_func(OdEdCommandContext* pCmdCtx)
{
    OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
    OdDbDatabasePtr pDb = pDbCmdCtx->database();
    OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();

    OdDbObjectId layer = greateLayer(pDb, pIO);

    OdDbBlockTablePtr pBlockTbl = pDb->getBlockTableId().openObject();
    OdDbSymbolTableIteratorPtr  blockIt = pBlockTbl->newIterator();

    for (; !blockIt->done(); blockIt->step())
    {
        OdDbBlockTableRecordPtr block = blockIt->getRecordId().safeOpenObject(OdDb::kForRead);

        OdDbObjectIteratorPtr pEntIter = block->newIterator();

        for (; !pEntIter->done(); pEntIter->step())
        {
            OdDbEntityPtr pEn = pEntIter->entity(OdDb::kForWrite);

            if (!OdDbLine::cast(pEn.get()).isNull())
                pEn->setLayer(layer);

        }
    }

}


void _ExCreateEclipse_func(OdEdCommandContext* pCmdCtx)
{
    OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
    OdDbDatabasePtr pDb = pDbCmdCtx->database();
    OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();

    OdDbBlockTableRecordPtr pMS = pDb->getModelSpaceId().openObject(OdDb::kForWrite);

    ExEclipsePtr pEclipse = ExEclipse::createObject();
    pEclipse->setDatabaseDefaults(pDb);

    pEclipse ->setCenter(pIO->getPoint(OD_T("Enter circle center:"), true));

    struct MinorRadiusTracker : OdStaticRxObject<OdEdRealTracker>
    {
        ExEclipsePtr _ent;
        MinorRadiusTracker(ExEclipsePtr _ent) : _ent(_ent) {}

        virtual void setValue(double r)
        {
            _ent->setMinorRadius(r);
        }

        virtual int addDrawables(OdGsView* pView)
        {
            pView->add(_ent, 0);
            return 1;
        }

        virtual void removeDrawables(OdGsView* pView)
        {
            pView->erase(_ent);
        }
    }
    tracker_minor(pEclipse);

    struct MajorRadiusTracker : OdStaticRxObject<OdEdRealTracker>
    {
        ExEclipsePtr _ent;
        MajorRadiusTracker(ExEclipsePtr _ent) : _ent(_ent) {}

        virtual void setValue(double r)
        {
            _ent->setMajorRadius(r);
        }

        virtual int addDrawables(OdGsView* pView)
        {
            pView->add(_ent, 0);
            return 1;
        }

        virtual void removeDrawables(OdGsView* pView)
        {
            pView->erase(_ent);
        }
    }
    tracker_major(pEclipse);

    pEclipse->setMinorRadius(pIO->getDist(OD_T("\n Specify minor radius of eclipse: "), OdEd::kGdsFromLastPoint, 0.0, OdString::kEmpty, &tracker_minor));
    pEclipse->setMajorRadius(pIO->getDist(OD_T("\n Specify major radius of eclipse: "), OdEd::kGdsFromLastPoint, 0.0, OdString::kEmpty, &tracker_major));

    pMS->appendOdDbEntity(pEclipse);
}