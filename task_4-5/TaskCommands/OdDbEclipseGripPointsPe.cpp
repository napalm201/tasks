#include "OdDbEclipseGripPointsPe.h"
#include "AbstractViewPE.h"
#include "DbViewport.h"

bool projectOffset(const OdDbDatabase* pDb, const OdGeVector3d& vNormal, OdGeVector3d& vOffset)
{
    OdDbObjectId idVp = pDb->activeViewportId();
    OdDbObjectPtr pVp(idVp.openObject());
    OdAbstractViewPEPtr pAVp(pVp);
    if (!pAVp.isNull())
    {
        OdGeVector3d vViewDir = pAVp->direction(pVp);
        if (!vViewDir.isPerpendicularTo(vNormal))
        {
            OdGePlane pln(OdGePoint3d::kOrigin, vNormal);
            OdGeMatrix3d mProj;
            mProj.setToProjection(pln, vViewDir);
            vOffset.transformBy(mProj);
            return true;
        }
    }
    return false;
}


OdResult OdDbEclipseGripPointsPE::getGripPoints(const OdDbEntity* pEntity, OdGePoint3dArray& gripPoints) const
{
    ExEclipsePtr eclipse = pEntity;
    unsigned int size = gripPoints.size();

    gripPoints.resize(size + 5);

    gripPoints[size + 0] = eclipse->center();                            

    eclipse->getPointAtParam(eclipse->startAngle(), gripPoints[size + 1]);
    eclipse->getPointAtParam(eclipse->endAngle(), gripPoints[size + 2]);
    eclipse->getPointAtParam(OdaPI2, gripPoints[size + 3]);           
    eclipse->getPointAtParam(OdaPI, gripPoints[size + 4]);            

	return eOk;
}

OdResult OdDbEclipseGripPointsPE::moveGripPointsAt(OdDbEntity* pEntity, const OdIntArray& indices, const OdGeVector3d& off)
{
    if (indices.size() == 0)                                     
        return eOk;

    OdGeVector3d offset(off);
    ExEclipsePtr eclipse = pEntity;
                                           
    if (!projectOffset(eclipse->database(), eclipse->normal(), offset))
        return eOk;
      
    OdGePoint3dArray gripPoints;
    eclipse->getGripPoints(gripPoints);

    int index = indices[0];
    OdGePoint3d gripPoint = gripPoints[index];

    switch (index) {
    case 0 :
        eclipse->setCenter(eclipse->center() + offset);
        break;
    case 1:
    {
        double start_angle = eclipse->startAngle();

        double xx = gripPoint.x - eclipse->center().x; 
        double yy = gripPoint.y - eclipse->center().y; 
        double zz = gripPoint.z - eclipse->center().z;

        OdGeVector3d start_v(xx, yy, zz); 

        gripPoint +=  offset;

        xx = gripPoint.x - eclipse->center().x;
        yy = gripPoint.y - eclipse->center().y;
        zz = gripPoint.z - eclipse->center().z;
        
        OdGeVector3d end_v(xx, yy, zz);

        double delta_angle = end_v.angleTo(start_v, eclipse->normal());

        eclipse->setStartAngle(start_angle + delta_angle);

        ExEclipse::Type type = start_v.isCodirectionalTo(end_v) ? ExEclipse::Type::eArc : ExEclipse::Type::nArc;

        eclipse->setType(type);
        break;
    }

    case 2:
    {
        double end_angle = eclipse->endAngle();

        double xx = gripPoint.x - eclipse->center().x;
        double yy = gripPoint.y - eclipse->center().y;
        double zz = gripPoint.z - eclipse->center().z;

        OdGeVector3d start_v(xx, yy, zz);

        gripPoint += offset;

        xx = gripPoint.x - eclipse->center().x;
        yy = gripPoint.y - eclipse->center().y;
        zz = gripPoint.z - eclipse->center().z;

        OdGeVector3d end_v(xx, yy, zz);

        double delta_angle = end_v.angleTo(start_v, eclipse->normal());

        eclipse->setEndAngle(end_angle + delta_angle);
    
        ExEclipse::Type type = start_v.isCodirectionalTo(end_v) ? ExEclipse::Type::eArc : ExEclipse::Type::nArc;
 
        eclipse->setType(type);
        break;
    }
    case 3:
    {
        OdGePoint3d point = gripPoint + offset;
        eclipse->setMajorRadius(eclipse->center().distanceTo(point));
        break;
    }
    case 4: 
    {
        OdGePoint3d point = gripPoint + offset;
        eclipse->setMinorRadius(eclipse->center().distanceTo(point));
        break;
    }
    
    }

	return eOk;
}

OdResult OdDbEclipseGripPointsPE::getStretchPoints(const OdDbEntity* pEntity, OdGePoint3dArray& stretchPoints) const
{
	return eOk;
}

OdResult OdDbEclipseGripPointsPE::moveStretchPointsAt(OdDbEntity* pEntity, const OdIntArray& indices, const OdGeVector3d& offset)
{
    return eOk;
}

OdResult OdDbEclipseGripPointsPE::getOsnapPoints(const OdDbEntity* pEntity, OdDb::OsnapMode osnapMode, OdGsMarker gsSelectionMark, const OdGePoint3d& pickPoint, const OdGePoint3d& lastPoint, const OdGeMatrix3d& xWorldToEye, OdGePoint3dArray& snapPoints) const
{
	return OdResult();
}
