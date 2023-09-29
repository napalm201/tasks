#pragma once

#define WIN32_LEAN_AND_MEAN		

#include "OdaCommon.h"
#include "DbEntity.h"

class ExEclipse : public OdDbEntity
{
public:
	ODDB_DECLARE_MEMBERS(ExEclipse);

	ExEclipse();
	virtual ~ExEclipse();

	bool subWorldDraw(OdGiWorldDraw* pWd) const;
	OdResult dwgInFields(OdDbDwgFiler* pFiler);
	void dwgOutFields(OdDbDwgFiler* pFiler) const;
	OdResult dxfInFields(OdDbDxfFiler* pFiler);
	void dxfOutFields(OdDbDxfFiler* pFiler) const;
};

