#ifndef _ODDBECLIPSEGRIPPOINTS_INCLUDED
#define _ODDBECLIPSEGRIPPOINTS_INCLUDED
#include "OdaCommon.h"
#include "stdAfx.h"
#include "Ge/GeLine3d.h"
#include "DbGripPoints.h"
#include "ExEclipse.h"

class OdDbEclipseGripPointsPE : public OdDbGripPointsPE
{

public:
    virtual OdResult getGripPoints(const OdDbEntity* pEntity, OdGePoint3dArray& gripPoints) const;
    virtual OdResult moveGripPointsAt(OdDbEntity* pEntity, const OdIntArray& indices, const OdGeVector3d& offset);
    virtual OdResult getStretchPoints(const OdDbEntity* pEntity, OdGePoint3dArray& stretchPoints) const;
    virtual OdResult moveStretchPointsAt(OdDbEntity* pEntity, const OdIntArray& indices, const OdGeVector3d& offset);
    virtual OdResult getOsnapPoints(
        const OdDbEntity* pEntity,
        OdDb::OsnapMode osnapMode,
        OdGsMarker gsSelectionMark,
        const OdGePoint3d& pickPoint,
        const OdGePoint3d& lastPoint,
        const OdGeMatrix3d& xWorldToEye,
        OdGePoint3dArray& snapPoints) const;
};

#endif 
