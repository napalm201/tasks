#include "OdDbEclipseGripPointsPe.h"

OdResult OdDbEclipseGripPointsPE::getGripPoints(const OdDbEntity* pEntity, OdGePoint3dArray& gripPoints) const
{
	return OdResult();
}

OdResult OdDbEclipseGripPointsPE::moveGripPointsAt(OdDbEntity* pEntity, const OdIntArray& indices, const OdGeVector3d& offset)
{
	return OdResult();
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
