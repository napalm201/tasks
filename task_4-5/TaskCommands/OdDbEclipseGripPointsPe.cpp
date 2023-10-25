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
    case 1:
    {
        double start_angle = eclipse->startAngle();
        double epsilan_angle = 0.001;

        double xx = gripPoint.x - eclipse->center().x; 
        double yy = gripPoint.y - eclipse->center().y; 
        double zz = gripPoint.z - eclipse->center().z;

        OdGeVector3d start_v(xx, yy, zz); 

        OdGePoint3d p;
        eclipse->getPointAtParam(start_angle + epsilan_angle, p);

        xx = p.x - eclipse->center().x;
        yy = p.y - eclipse->center().y;
        zz = p.z - eclipse->center().z;

        OdGeVector3d target = OdGeVector3d(xx, yy, zz) - start_v;

        gripPoint +=  offset;

        xx = gripPoint.x - eclipse->center().x;
        yy = gripPoint.y - eclipse->center().y;
        zz = gripPoint.z - eclipse->center().z;
        
        OdGeVector3d end_v(xx, yy, zz);

        double delta_angle = end_v.isCodirectionalTo(target) ? end_v.angleTo(start_v) : -end_v.angleTo(start_v);

        eclipse->setStartAngle(start_angle + delta_angle);
    }

    case 2:
    {
        double end_angle = eclipse->endAngle();
        double epsilan_angle = 0.001;

        double xx = gripPoint.x - eclipse->center().x;
        double yy = gripPoint.y - eclipse->center().y;
        double zz = gripPoint.z - eclipse->center().z;

        OdGeVector3d start_v(xx, yy, zz);

        OdGePoint3d p;
        eclipse->getPointAtParam(end_angle + epsilan_angle, p);

        xx = p.x - eclipse->center().x;
        yy = p.y - eclipse->center().y;
        zz = p.z - eclipse->center().z;

        OdGeVector3d target = OdGeVector3d(xx, yy, zz) - start_v;

        gripPoint += offset;

        xx = gripPoint.x - eclipse->center().x;
        yy = gripPoint.y - eclipse->center().y;
        zz = gripPoint.z - eclipse->center().z;

        OdGeVector3d end_v(xx, yy, zz);

        double delta_angle = end_v.isCodirectionalTo(target) ? end_v.angleTo(start_v) : -end_v.angleTo(start_v);

        eclipse->setEndAngle(end_angle + delta_angle);
    
    }
    case 3:
    {
        OdGePoint3d point = gripPoint + offset;
        eclipse->setMajorRadius(eclipse->center().distanceTo(point));
    }
    case 4: 
    {
        OdGePoint3d point = gripPoint + offset;
        eclipse->setMinorRadius(eclipse->center().distanceTo(point));
    }
    
    }

	return eOk;
}

OdResult OdDbEclipseGripPointsPE::getStretchPoints(const OdDbEntity* pEntity, OdGePoint3dArray& stretchPoints) const
{
	return OdResult();
}

OdResult OdDbEclipseGripPointsPE::moveStretchPointsAt(OdDbEntity* pEntity, const OdIntArray& indices, const OdGeVector3d& offset)
{
	return OdResult();
}

OdResult OdDbEclipseGripPointsPE::getOsnapPoints(const OdDbEntity* pEntity, OdDb::OsnapMode osnapMode, OdGsMarker gsSelectionMark, const OdGePoint3d& pickPoint, const OdGePoint3d& lastPoint, const OdGeMatrix3d& xWorldToEye, OdGePoint3dArray& snapPoints) const
{
	return OdResult();
}
