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
#include "Ge\GeEllipArc3d.h"

class ExEclipse : public OdDbEntity
{
	static const int lastKnownVersion;
public:
	ODDB_DECLARE_MEMBERS(ExEclipse);

	enum Type
	{
		eArc,
		nArc
	};

	ExEclipse();
	virtual ~ExEclipse();
	int getVersion();

	void setCenter(const OdGePoint3d& center);
	void setType(const Type& type);

	void setStartAngle(double startAngle);
	void setEndAngle(double endAngle);

	void setMajorRadius(double major_r);
	void setMinorRadius(double minor_r);

	void setAxises(const OdGeVector3d& major_axis, const OdGeVector3d& minor_axis);

	OdGePoint3d center() const;

	double majorRadius() const;
	double minorRadius() const;

	OdGeVector3d minorAxis() const;

	double startAngle() const;
	double endAngle() const;

	OdGeVector3d normal() const;

	bool subWorldDraw(OdGiWorldDraw* pWd) const;

	OdResult dwgInFields(OdDbDwgFiler* pFiler);
	void dwgOutFields(OdDbDwgFiler* pFiler) const;
	OdResult dxfInFields(OdDbDxfFiler* pFiler);
	void dxfOutFields(OdDbDxfFiler* pFiler) const;

	virtual OdResult getPointAtParam(
		double param,
		OdGePoint3d& pointOnCurve) const;

	virtual OdResult getPlane(OdGePlane& gePlane, 
		OdDb::Planarity& gePlanarity) const;

	virtual OdResult subTransformBy(
		const OdGeMatrix3d& xfm);


	virtual bool colisionPoint(const OdGePoint3d& pointOnCurve) const;
	

private:
	OdGePoint3d m_center = OdGePoint3d(0, 0, 0);
	double m_majorRadius = 2; double m_minorRadius = 1;
	double m_endAngle = Oda2PI-0.0001; double m_startAngle = 0;
	Type type = eArc;
	OdGeVector3d m_majorAxis = OdGeVector3d(0, 1, 0);
	OdGeVector3d m_minorAxis = OdGeVector3d(1, 0, 0);
};
typedef OdSmartPtr<ExEclipse> ExEclipsePtr;


inline int ExEclipse::getVersion()
{
	return lastKnownVersion;
}