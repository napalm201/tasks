#include "ExEclipse.h"
#include "DbProxyEntity.h"


ODRX_DXF_DEFINE_MEMBERS(ExEclipse,                                                              // ClassName
    OdDbEntity,                                                            // ParentClass
    DBOBJECT_CONSTR,                                                       // DOCREATE
    OdDb::vAC15,                                                           // DwgVer
    OdDb::kMRelease0,                                                      // MaintVer
    OdDbProxyEntity::kAllAllowedBits^ OdDbProxyEntity::kTransformAllowed, // nProxyFlags
    EXECLIPSE,                                                              // DxfName
    OdExTaskCommandsModuleName | Description: Teigha Run - time Extension Example)

ExEclipse::ExEclipse()
{

}

ExEclipse::~ExEclipse()
{
}

bool ExEclipse::subWorldDraw(OdGiWorldDraw* pWd) const
{
    return false;
}

OdResult ExEclipse::dwgInFields(OdDbDwgFiler* pFiler)
{
    return OdResult();
}

void ExEclipse::dwgOutFields(OdDbDwgFiler* pFiler) const
{
}

OdResult ExEclipse::dxfInFields(OdDbDxfFiler* pFiler)
{
    return OdResult();
}

void ExEclipse::dxfOutFields(OdDbDxfFiler* pFiler) const
{
}
