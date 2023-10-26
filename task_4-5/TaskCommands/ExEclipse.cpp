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
    
}

ExEclipse::~ExEclipse()
{

}


void ExEclipse::setCenter(const OdGePoint3d& center)
{
    this->m_center = center;
}

void ExEclipse::setType(const Type& type)
{
    this->type = type;
}

void ExEclipse::setStartAngle(double startAngle)
{
    this->m_startAngle = startAngle;
}

void ExEclipse::setEndAngle(double endAngle)
{
    this->m_endAngle = endAngle;
}

void ExEclipse::setMajorRadius(double majorRadius)
{
    this->m_majorRadius = majorRadius;
}

void ExEclipse::setMinorRadius(double minorRadius)
{
    this->m_minorRadius = minorRadius;
}

void ExEclipse::setAxises(const OdGeVector3d& major_axis, const OdGeVector3d& minor_axis)
{
    this->m_majorAxis = major_axis;
    this->m_majorAxis.normalize();

    this->m_minorAxis = minor_axis;
    this->m_minorAxis.normalize();
}



OdGePoint3d ExEclipse::center() const
{
    return m_center;
}

double ExEclipse::majorRadius() const
{
    return m_majorRadius;
}

double ExEclipse::minorRadius() const
{
    return m_minorRadius;
}

OdGeVector3d ExEclipse::minorAxis() const
{
    return m_minorAxis;
}

double ExEclipse::startAngle() const
{
    return m_startAngle;
}

double ExEclipse::endAngle() const
{
    return m_endAngle;
}

OdGeVector3d ExEclipse::normal() const
{
    return m_majorAxis.crossProduct(m_minorAxis).normalize();
}



bool ExEclipse::subWorldDraw(OdGiWorldDraw* pWd) const
{
    assertReadEnabled();

    pWd->subEntityTraits().setFillType(kOdGiFillAlways);
    pWd->subEntityTraits().setLineType(linetypeId());

    pWd->subEntityTraits().setSelectionMarker(1);



    //OdGeEllipArc3d eclipse(center(), m_majorAxis, m_minorAxis, majorRadius(), minorRadius(), 0, OdaPI2);

     //pWd->geometry().ellipArc(eclipse);

    //OdDbHatchPtr pHatch = OdDbHatch::createObject();
    ////
    //EdgeArray edges;

    //pHatch->appendLoop(OdDbHatch::kDefault, edges);
    ////

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
    setStartAngle(pFiler->rdDouble());
    setEndAngle(pFiler->rdDouble());

    OdGeVector3d major_axis = pFiler->rdVector3d();
    OdGeVector3d minor_axis = pFiler->rdVector3d();

    setAxises(major_axis, minor_axis);


    return eOk;
}

void ExEclipse::dwgOutFields(OdDbDwgFiler* pFiler) const
{
    OdDbEntity::dwgOutFields(pFiler);

    pFiler->wrInt8(lastKnownVersion);
    pFiler->wrPoint3d(center());
    pFiler->wrDouble(majorRadius());
    pFiler->wrDouble(minorRadius());
    pFiler->wrDouble(startAngle());
    pFiler->wrDouble(endAngle());
    pFiler->wrVector3d(m_majorAxis);
    pFiler->wrVector3d(m_minorAxis);

}

OdResult ExEclipse::dxfInFields(OdDbDxfFiler* pFiler)
{
    return OdResult();
}

void ExEclipse::dxfOutFields(OdDbDxfFiler* pFiler) const
{

}

OdResult ExEclipse::getPointAtParam(double param, OdGePoint3d& pointOnCurve) const
{
    double angleRotate = param;
    OdGeVector3d minorAxis = m_minorAxis;

    OdGeVector2d target1(1, 0);
    double x = minorRadius() * cos(angleRotate);
    double y = majorRadius() * sin(angleRotate);

    OdGeVector2d target2(x, y);

    angleRotate = target2.angleToCCW(target1);

    double k = target2.length();

    minorAxis.rotateBy(angleRotate, normal());
    minorAxis *= k;
  
    pointOnCurve = m_center + minorAxis;

    return eOk;
}

OdResult ExEclipse::getPlane(OdGePlane& gePlane, OdDb::Planarity& gePlanarity) const
{
    gePlane = OdGePlane(center(), normal());
    gePlanarity = OdDb::Planarity::kPlanar;

    return eOk;
}

OdResult ExEclipse::subTransformBy(const OdGeMatrix3d& xfm)
{
    m_majorAxis.transformBy(xfm);
    m_minorAxis.transformBy(xfm);
    return eOk;
}

