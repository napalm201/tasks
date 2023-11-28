
#include "stdAfx.h"

#include <ctime>
#include <sstream>
#include <DbLayerTableRecord.h>
#include "DbBlockTableRecord.h"
#include "DbBlockReference.h"


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


OdDbObjectId greateLayer_2(OdDbDatabasePtr pDb, OdDbUserIO* pIO)
{
    OdDbLayerTablePtr pLayers = pDb->getLayerTableId().safeOpenObject(OdDb::kForWrite);

    OdDbLayerTableRecordPtr pLayer = OdDbLayerTableRecord::createObject();

    OdString nameLayer = "LayerTask";

    pLayer->setName(nameLayer);

    OdCmColor color(OdCmEntityColor::ColorMethod::kByACI);

    color.setColorIndex(OdCmEntityColor::kACIYellow);

    pLayer->setColor(color);

    OdString fname = pIO->getFilePath(OD_T("Enter lin file name :"));

    pDb->loadLineTypeFile("*штриховая", fname);

    OdDbLinetypeTablePtr pLinetypes = pDb->getLinetypeTableId().safeOpenObject(OdDb::kForWrite);

    OdDbObjectId pLinetypeId = pLinetypes->getAt("штриховая");

    pLayer->setLinetypeObjectId(pLinetypeId);

    OdDbObjectId layerId = pLayers->add(pLayer); 

    return layerId;
}



void getAllLinesfromModelSpace(OdDbObjectId pMS_Id, OdDbObjectIdArray& arraysCopyId)
{
    OdDbBlockTableRecordPtr pMS = pMS_Id.safeOpenObject(OdDb::kForWrite);
    OdDbObjectIteratorPtr pEntIter = pMS->newIterator();

    for (; !pEntIter->done(); pEntIter->step())
    {
        OdDbEntityPtr pEntity = pEntIter->entity();
        OdDbObjectId objectId = pEntIter->objectId();

        if (!OdDbLine::cast(pEntity.get()).isNull()) 
        {
            arraysCopyId.append(objectId);
        }

        OdDbBlockReferencePtr blckRef = OdDbBlockReference::cast(pEntity.get());

        if (!blckRef.isNull())
        {
            OdDbObjectId block = blckRef->blockTableRecord();
            getAllLinesfromModelSpace(block, arraysCopyId);
        }

    }
}


OdDbObjectId copyObjectsFromDataBaseToDataBase(OdDbDatabase* pDb_1, OdDbDatabase* pDb_2, const OdDbObjectIdArray& arraysCopyId)
{
    OdDbBlockTablePtr       pBlockTable_2 = pDb_2->getBlockTableId().safeOpenObject(OdDb::kForWrite);
    OdDbBlockTableRecordPtr pMS_2 = pDb_2->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
    
    OdDbBlockTableRecordPtr pCopyLines = OdDbBlockTableRecord::createObject();

    pCopyLines->setName("copyLines");

    
    OdDbObjectId idBlockLines = pBlockTable_2->add(pCopyLines);

    OdDbBlockReferencePtr pBlkRef_2 = OdDbBlockReference::createObject();
    pBlkRef_2->setDatabaseDefaults(pDb_2);


    OdDbObjectId brefId = pMS_2->appendOdDbEntity(pBlkRef_2);
    pBlkRef_2->setBlockTableRecord(pCopyLines->objectId());
    
    

    OdDbIdMappingPtr pMap = OdDbIdMapping::createObject();
    pMap->setDestDb(pDb_2);

    pDb_1->wblockCloneObjects(arraysCopyId, idBlockLines, *pMap, OdDb::kDrcReplace);

    return idBlockLines;
}

void getRGBColor(OdUInt8& red, OdUInt8& green, OdUInt8& blue, OdDbEntityPtr pEn);
void getRGBColor(OdUInt8& red, OdUInt8& green, OdUInt8& blue, OdCmEntityColor color);

void updateEntitys(OdDbObjectId block_id, OdDbObjectId layer)
{
    OdDbBlockTableRecordPtr pCopyLinesBlock = block_id.safeOpenObject(OdDb::kForWrite);

    OdDbObjectIteratorPtr pEntIter = pCopyLinesBlock->newIterator();

    OdCmColor color(OdCmEntityColor::ColorMethod::kByLayer);

    for (; !pEntIter->done(); pEntIter->step())
    {
        OdDbEntityPtr pEn = pEntIter->entity(OdDb::kForWrite);

        OdUInt8 k = 245;

        OdUInt8 red = 0, green = 0, blue = 0;

        getRGBColor(red, green, blue, pEn);
   
        if (green  > k && red > k && blue > k)
        {
            pEn->setLayer(layer);
            pEn->setColor(color);
        }
    }
}

void getRGBColor(OdUInt8 & red, OdUInt8& green, OdUInt8& blue, OdDbEntityPtr pEn)
{
    OdCmEntityColor color = pEn->entityColor();

    if (color.isByLayer())
    {
        OdDbLayerTableRecordPtr layer = pEn->layerId().safeOpenObject(OdDb::kForRead);
        color = layer->color().entityColor();
    }
    else  if (color.isByBlock())
    {
        OdDbBlockTableRecordPtr pBlock = pEn->blockId().safeOpenObject(OdDb::kForRead);

        OdDbObjectIdArray referenceIds;
        pBlock->getBlockReferenceIds(referenceIds);

        if (!referenceIds.isEmpty())
        {
            OdDbBlockReferencePtr block_ref = referenceIds.first().safeOpenObject(OdDb::kForRead);
            getRGBColor(red, green, blue, block_ref);
        }
       
    }

     getRGBColor(red, green, blue, color);

}



void getRGBColor(OdUInt8& red, OdUInt8& green, OdUInt8& blue, OdCmEntityColor color)
{
    if (color.isByColor())
    {
        red = color.red(); green = color.green(); blue = color.blue();

    }
    else if (color.isByACI())
    {
        OdUInt16 indexColor = color.colorIndex();
        OdUInt32 rgb = color.lookUpRGB(indexColor);

        red = ODGETRED(rgb);  green = ODGETGREEN(rgb);  blue = ODGETBLUE(rgb);
    }
}

OdDbObjectId greate_testBlock(OdDbDatabasePtr pDb);
void addEntitys(OdDbObjectId block_id);

void _CopyLines_func(OdEdCommandContext* pCmdCtx)
{
    OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
    OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();

    OdDbDatabasePtr pDb_1 = pDbCmdCtx->database();
    OdDbHostAppServices* svcs = pDb_1->appServices();

    OdString fname = pIO->getFilePath(OD_T("Enter file name :"));

    OdDbDatabasePtr pDb_2 = pDb_1->appServices()->readFile(fname);

    OdDbObjectIdArray arraysCopyId;
    OdDbObjectId pMS_1 = pDb_1->getModelSpaceId();

    getAllLinesfromModelSpace(pMS_1, arraysCopyId);

    OdDbObjectId  pCopyLines_ID = copyObjectsFromDataBaseToDataBase(pDb_1, pDb_2, arraysCopyId);

    OdDbObjectId layer_2 = greateLayer_2(pDb_2, pIO);

    updateEntitys(pCopyLines_ID, layer_2);

    OdDbObjectId testBlock_ID = greate_testBlock(pDb_2);

    addEntitys(testBlock_ID);

    OdDb::SaveType fileType = OdDb::kDwg;
    OdDb::DwgVersion outVer = OdDb::vAC24;

    pDb_2->writeFile(fname, fileType, outVer);
    pDb_2.release();
}


#include "DbLeader.h"


OdDbObjectId greate_testBlock(OdDbDatabasePtr pDb)
{
    OdDbBlockTablePtr       blocks = pDb->getBlockTableId().safeOpenObject(OdDb::kForWrite);
    OdDbBlockTableRecordPtr pMS = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

    OdDbBlockTableRecordPtr testBlock = OdDbBlockTableRecord::createObject();

    testBlock->setName("testBlock");


    OdDbObjectId testBlock_ID = blocks->add(testBlock);

    OdDbBlockReferencePtr pBlkRef = OdDbBlockReference::createObject();
    pBlkRef->setDatabaseDefaults(pDb);

    OdDbObjectId brefId = pMS->appendOdDbEntity(pBlkRef);

    pBlkRef->setBlockTableRecord(testBlock->objectId());

    return brefId;

}

#include "DbTextStyleTable.h"
#include "DbTextStyleTableRecord.h"
#include "DbPolyLine.h"
#include "DbArc.h"
#include "DbMText.h"
#include "DbText.h"
#include "Db3dPolylineVertex.h"
#include "Db3dPolyline.h"

void addEntitys(OdDbObjectId block_id)
{
    OdDbBlockReferencePtr blck_ref = block_id.safeOpenObject(OdDb::kForWrite);
    OdDbBlockTableRecordPtr testBlock = blck_ref->blockTableRecord().safeOpenObject(OdDb::kForWrite);
    OdDbDatabasePtr pDb = blck_ref->database();

    OdDbLinetypeTablePtr pLinetypes = pDb->getLinetypeTableId().safeOpenObject(OdDb::kForRead);
    OdDbObjectId linetypeID = pLinetypes->getAt("штриховая");
    OdDbLinetypeTableRecordPtr linetype = linetypeID.safeOpenObject(OdDb::kForWrite);

    OdDbTextStyleTablePtr pStyles = pDb->getTextStyleTableId().safeOpenObject(OdDb::kForWrite);
    OdDbTextStyleTableRecordPtr pStyleAnotation = OdDbTextStyleTableRecord::createObject();

    pStyleAnotation->setName("anotationtextsyle");
    pStyleAnotation->setFont(OD_T("Calibri"), false, false, 0, 3);

    OdDbObjectId pStyleAnotationID = pStyles->add(pStyleAnotation);


    //Arc
    OdDbArcPtr pArc = OdDbArc::createObject();
    testBlock->appendOdDbEntity(pArc);

    OdGePoint3d center1(0, 0, 0);
    double r1 = 40;

    pArc->setCenter(center1);
    pArc->setRadius(r1);
    pArc->setStartAngle(OdaToRadian(90));
    pArc->setEndAngle(OdaToRadian(360));


    //Circle
    OdDbCirclePtr pCircle = OdDbCircle::createObject();
    testBlock->appendOdDbEntity(pCircle);

    double r2 = 2 * r1;
    OdGePoint3d center2 = center1;

    pCircle->setCenter(center2);
    pCircle->setRadius(r2);



    //Leader
    OdDbLeaderPtr pLeader = OdDbLeader::createObject();
    testBlock->appendOdDbEntity(pLeader);

    OdGePoint3d pointld_start = center1;
    pointld_start.x += r1;

    OdGePoint3d pointld_end = center1;
    pointld_end.x += r2 + 2;
    pointld_end.y -= r2 / 4;

    OdCmColor color_leader;
    color_leader.setRGB(128, 166, 255);

    pLeader->appendVertex(pointld_start);
    pLeader->appendVertex(pointld_end);
    pLeader->setDimscale(40);
    pLeader->setDimtad(0);
    pLeader->enableArrowHead();
    pLeader->setLineWeight(OdDb::kLnWt100);
    pLeader->setColor(color_leader);



    //Text Anotation 1
    OdDbMTextPtr ptext1 = OdDbMText::createObject();
    OdDbObjectId ptext1ID = testBlock->appendOdDbEntity(ptext1);


    OdCmColor color_tx1 = color_leader;

    double wTx1 = 15;
    double hTx1 = 2;
    double txoffen = 0.1 * wTx1;

    OdGePoint3d point_tx1 = pointld_end;
    point_tx1.x += txoffen;

    ptext1->setLocation(point_tx1);
    ptext1->setContents(OD_T("Trim #2"));
    ptext1->setTextHeight(hTx1);
    ptext1->setAttachment(OdDbMText::kMiddleLeft);
    ptext1->setColor(color_tx1);
    ptext1->setTextStyle(pStyleAnotationID);

    pLeader->attachAnnotation(ptext1ID);

    


    //Line
    OdDbLinePtr pline = OdDbLine::createObject();
    testBlock->appendOdDbEntity(pline);

    OdGePoint3d pointln_start = center1;
    OdGePoint3d pointln_end = pointln_start;
    pointln_end.x -= 2 * r2 - r1;

    OdCmColor color_line;
    color_line.setRGB(180, 0, 0);

    pline->setStartPoint(pointln_start);
    pline->setEndPoint(pointln_end);
    pline->setLineWeight(OdDb::kLnWt100);
    pline->setColor(color_line);
    pline->setLinetype(linetype->id());


    //Text Anotation 2
    OdDbTextPtr ptext2 = OdDbText::createObject();
    testBlock->appendOdDbEntity(ptext2);

    OdCmColor color_tx2 = color_leader;

    OdGePoint3d point_tx2 = pointln_end;
    point_tx2.y += 3;

    double hTx2 = (r2 - r1) / 4.5;

    ptext2->setTextString("Center");
    ptext2->setHeight(hTx2);
    ptext2->setPosition(point_tx2);
    ptext2->setColor(color_line);



    //Polyline
    OdDb3dPolylinePtr polyline = OdDb3dPolyline::createObject();
    testBlock->appendOdDbEntity(polyline);

    double wh = 5;

    OdGePoint3d v0 = center1;
    v0.y += r1 + wh / 2;

    OdGePoint3d v1 = v0;
    v1.x -= wh / 2;

    OdGePoint3d v2 = v1;
    v2.y -= wh;

    OdGePoint3d v3 = v2;
    v3.x += wh;

    OdGePoint3d v4 = v3;
    v4.y += wh;

    OdGePoint3d v5 = v0;
    v5.y += r2 - r1 + 10;

    OdGePoint3d v6 = v5;
    v6.x += r2 - r1;

    OdDb3dPolylineVertexPtr vertex0 = OdDb3dPolylineVertex::createObject();
    vertex0->setPosition(v0);

    OdDb3dPolylineVertexPtr vertex1 = OdDb3dPolylineVertex::createObject();
    vertex1->setPosition(v1);

    OdDb3dPolylineVertexPtr vertex2 = OdDb3dPolylineVertex::createObject();
    vertex2->setPosition(v2);

    OdDb3dPolylineVertexPtr vertex3 = OdDb3dPolylineVertex::createObject();
    vertex3->setPosition(v3);

    OdDb3dPolylineVertexPtr vertex4 = OdDb3dPolylineVertex::createObject();
    vertex4->setPosition(v4);

    OdDb3dPolylineVertexPtr vertex5 = OdDb3dPolylineVertex::createObject();
    vertex5->setPosition(v5);

    OdDb3dPolylineVertexPtr vertex6 = OdDb3dPolylineVertex::createObject();
    vertex6->setPosition(v6);

    OdCmColor color_polyline;
    color_polyline.setRGB(0, 250, 0);

    polyline->appendVertex(vertex0); polyline->appendVertex(vertex1);
    polyline->appendVertex(vertex2); polyline->appendVertex(vertex3);
    polyline->appendVertex(vertex4); polyline->appendVertex(vertex0);
    polyline->appendVertex(vertex5); polyline->appendVertex(vertex6);

    polyline->setColor(color_polyline);



    //Text Anotation 3
    OdDbTextPtr ptext3 = OdDbText::createObject();
    testBlock->appendOdDbEntity(ptext3);

    OdCmColor color_tx3;
    color_tx3.setRGB(250, 250, 250);

    OdGePoint3d point_tx3 = v6;
    point_tx3.x += txoffen;
    point_tx3.y -= hTx1 / 2 ;

    ptext3->setTextString("Trim #1");
    ptext3->setPosition(point_tx3);
    ptext3->setHeight(hTx1);
    ptext3->setTextStyle(pStyleAnotationID);
    ptext3->setColor(color_tx3);

    blck_ref->setPosition(OdGePoint3d(300, 0, 0));
}


