#pragma once

#define WIN32_LEAN_AND_MEAN		

#include "OdaCommon.h"
#include "DbEntity.h"
#include "Gi/GiCommonDraw.h"
#include "Gi/GiGeometry.h"
#include "Ge/GeEllipArc3d.h"
#include "Gi/GiWorldDraw.h"
#include "DbFiler.h"
#include "CmColorBase.h"

class ExEclipse : public OdDbEntity
{
	static const int lastKnownVersion;
public:
	ODDB_DECLARE_MEMBERS(ExEclipse);

	ExEclipse();
	virtual ~ExEclipse();
	int getVersion();

	void setCenter(const OdGePoint3d& center);

	void setMajorRadius(double majorRadius);
	void setMinorRadius(double majorRadius);

	void setAxis(const OdGeVector3d& majorAxis, const OdGeVector3d& minorAxis);

	void setColorFill(const OdCmEntityColor& color);

	OdGePoint3d center() const;

	double majorRadius() const;
	double minorRadius() const;

	OdGeVector3d majorAxis() const;
	OdGeVector3d minorAxis() const;

	OdCmEntityColor colorF() const;

	bool subWorldDraw(OdGiWorldDraw* pWd) const;
	OdResult dwgInFields(OdDbDwgFiler* pFiler);
	void dwgOutFields(OdDbDwgFiler* pFiler) const;
	OdResult dxfInFields(OdDbDxfFiler* pFiler);
	void dxfOutFields(OdDbDxfFiler* pFiler) const;

private:
	OdGeEllipArc3d m_ellip;
	OdCmEntityColor colorFill;
};

typedef OdSmartPtr<ExEclipse> ExEclipsePtr;

inline int ExEclipse::getVersion()
{
	return lastKnownVersion;
}