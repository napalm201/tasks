#include "ExEclipse.h"
#include "DbProxyEntity.h"
#include "DbHatch.h"

ODRX_DXF_DEFINE_MEMBERS(ExEclipse,                                                            
    OdDbEntity,                                                        
    DBOBJECT_CONSTR,                                                   
    OdDb::vAC18,                                                     
    OdDb::kMReleaseCurrent,
    OdDbProxyEntity::kTransformAllowed |
    OdDbProxyEntity::kColorChangeAllowed |
    OdDbProxyEntity::kLayerChangeAllowed,
    EXECLIPSE,                                                           
    OdExTaskCommandsModuleName | Description: Teigha Run - time Extension Example)

    const int ExEclipse::lastKnownVersion = 1;

ExEclipse::ExEclipse()
{
    m_ellip.setAxes(OdGeVector3d(1, 0, 0), OdGeVector3d(0, 1, 0));
}

ExEclipse::~ExEclipse()
{

}


void ExEclipse::setCenter(const OdGePoint3d& center)
{
    m_ellip.setCenter(center);
}

void ExEclipse::setMajorRadius(double majorRadius)
{

    m_ellip.setMajorRadius(majorRadius);
}

void ExEclipse::setMinorRadius(double minorRadius)
{
    m_ellip.setMinorRadius(minorRadius);
}

void ExEclipse::setAxis(const OdGeVector3d& majorAxis, const OdGeVector3d& minorAxis)
{
    m_ellip.setAxes(majorAxis, minorAxis);
}

void ExEclipse::setColorFill(const OdCmEntityColor& color)
{
    this->colorFill = color;
}


OdGePoint3d ExEclipse::center() const
{
    return m_ellip.center();
}

double ExEclipse::majorRadius() const
{
    return m_ellip.majorRadius();
}

double ExEclipse::minorRadius() const
{
    return m_ellip.minorRadius();
}

OdGeVector3d ExEclipse::majorAxis() const
{
    return m_ellip.majorAxis();
}

OdGeVector3d ExEclipse::minorAxis() const
{
    return m_ellip.minorAxis();
}

OdCmEntityColor ExEclipse::colorF() const
{
    return colorFill;
}




bool ExEclipse::subWorldDraw(OdGiWorldDraw* pWd) const
{
    assertReadEnabled();

    pWd->subEntityTraits().setTrueColor(entityColor());
    pWd->subEntityTraits().setFillType(kOdGiFillAlways);
    pWd->subEntityTraits().setLineType(linetypeId());

    pWd->subEntityTraits().setSelectionMarker(1);
    pWd->geometry().ellipArc(m_ellip);

    OdDbHatchPtr pHatch = OdDbHatch::createObject();
    //
    EdgeArray edges;

    pHatch->appendLoop(OdDbHatch::kDefault, edges);
    //

    return true;
}

OdResult ExEclipse::dwgInFields(OdDbDwgFiler* pFiler)
{
    assertReadEnabled();
 
    OdResult res = OdDbEntity::dwgInFields(pFiler);
    if (res != eOk)
        return res;

    int nVersion = pFiler->rdInt8();
    if (nVersion > lastKnownVersion)
        return eMakeMeProxy;

    setCenter(pFiler->rdPoint3d());
    setMajorRadius(pFiler->rdDouble());
    setMinorRadius(pFiler->rdDouble());

    OdGeVector3d majorAxis = pFiler->rdVector3d();
    OdGeVector3d minorAxis = pFiler->rdVector3d();

    setAxis(majorAxis, minorAxis);

    colorFill.setColor(pFiler->rdInt32());


    return eOk;
}

void ExEclipse::dwgOutFields(OdDbDwgFiler* pFiler) const
{
    OdDbEntity::dwgOutFields(pFiler);

    pFiler->wrInt8(lastKnownVersion);
    pFiler->wrPoint3d(center());
    pFiler->wrDouble(majorRadius());
    pFiler->wrDouble(minorRadius());
    pFiler->wrVector3d(majorAxis());
    pFiler->wrVector3d(minorAxis());
    pFiler->wrInt32(colorF().color());

}

OdResult ExEclipse::dxfInFields(OdDbDxfFiler* pFiler)
{
    return OdResult();
}

void ExEclipse::dxfOutFields(OdDbDxfFiler* pFiler) const
{

}

