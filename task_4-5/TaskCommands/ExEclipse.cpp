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

    pWd->subEntityTraits().setSelectionMarker(1);

    OdGeMatrix3d elispe_axis;
    elispe_axis.setCoordSystem(center(),
        m_minorAxis,
        m_majorAxis,
        normal());

    OdGeVector3d normal = OdGeVector3d(0, 0, 1);

    OdGeVector3d start_vector(1, 0,0);
    start_vector.rotateBy(m_startAngle, normal);

    OdGeVector3d end_vector(1, 0, 0);
    end_vector.rotateBy(m_endAngle, normal);
    
    double delta_angle = start_vector.angleTo(end_vector, normal);

    OdInt32 numSegments = 200;

    OdGePoint3dArray points(numSegments);


    for (OdInt32 i = 0; i <= numSegments; ++i)
    {
        double angle = m_startAngle + i * delta_angle / numSegments;;

        start_vector.set(1,0,0);
        start_vector.rotateBy(angle, normal);

        double phase = atan(minorRadius() * tan(angle) / majorRadius());

        start_vector *= OdGeVector2d(minorRadius() * cos(phase), majorRadius() * sin(phase)).length();
        // TODO
        
        start_vector.transformBy(elispe_axis);

        points.append(m_center + start_vector);
    }

    if (type == Type::eArc)
        points.append(center());

    pWd->geometry().polygon(points.size(), points.getPtr());
   

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

    OdGeMatrix3d elispe_axis;
    elispe_axis.setCoordSystem(center(),
       m_minorAxis,
       m_majorAxis,
        normal());
    
    OdGeVector3d start_vector(1, 0, 0);

    start_vector.rotateBy(angleRotate, OdGeVector3d(0,0,1));

    double phase = atan(minorRadius() * tan(angleRotate) / majorRadius());

    start_vector *= OdGeVector2d(minorRadius() * cos(phase), majorRadius() * sin(phase)).length();
    // TODO

    start_vector.transformBy(elispe_axis);

    pointOnCurve = m_center + start_vector;

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

bool ExEclipse::colisionPoint(const OdGePoint3d& pointOnCurve) const
{
    OdGeVector3d target = pointOnCurve - this->center();
    double angle_target = m_minorAxis.angleTo(target, normal());

    OdGePoint3d p;
    getPointAtParam(angle_target, p);

    OdGeVector3d radius = p - this->center();
    return target.length() >= radius.length();
}

