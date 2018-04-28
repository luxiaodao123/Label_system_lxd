#include "imageinfo.h"

Shape::Shape()
{
    m_cx = -1;
    m_cy = -1;
    m_r = -1;
}

Shape::Shape(Shape *temp)
{
    m_cx = temp->getCX();
    m_cy = temp->getCY();
    m_r = temp->getR();
}

Shape::~Shape()
{

}

void Shape::setCX(int x)
{
    m_cx = x;
}

void Shape::setCY(int y)
{
    m_cy = y;
}

void Shape::setR(int r)
{
    m_r = r;
}

ImageInfo::ImageInfo()
{
    m_step = 1.0;
    m_index = 0;
	m_save = false;
	m_jsonFlag = true;
}

ImageInfo::ImageInfo(ImageInfo *temp)
{
    m_poly = temp->getPoly();
    m_step = temp->getStep();
    m_index = temp->getIndex();
    m_origin = temp->getOrigin();
    m_path = temp->getPath();
    m_focusInfo = temp->getFocusInfo();
    m_oneEye = temp->getOneEye();
    m_shape = temp->getShape();
	m_save = temp->getState();
	m_jsonFlag = temp->getJsonFlag();
	m_jsonValue = temp->getJsonValue();
	m_disease = temp->getDisease();
}


ImageInfo::~ImageInfo()
{

}

const QMap<int, QPolygonF> ImageInfo::getPoly() const
{
    return m_poly;
}

const float ImageInfo::getStep() const
{
    return m_step;
}

const int ImageInfo::getIndex() const
{
    return m_index;
}

const bool ImageInfo::getState() const
{
	return  m_save;
}

const bool ImageInfo::getJsonFlag() const
{
	return m_jsonFlag;
}

QImage *ImageInfo::getOrigin()
{
    return m_origin;
}

const QString ImageInfo::getPath() const
{
    return m_path;
}

const QJsonValue ImageInfo::getJsonValue() const
{
	return m_jsonValue;
}

const QMap<QString, Shape> ImageInfo::getShape() const
{
    return m_shape;
}

const QMap<QString, QString> ImageInfo::getFocusInfo() const
{
    return m_focusInfo;
}

const QMap<QString, QString> ImageInfo::getOneEye() const
{
    return m_oneEye;
}

const QList<QString> ImageInfo::getDisease() const
{
	return m_disease;
}

void ImageInfo::setPoly(QMap<int, QPolygonF> poly)
{
    m_poly = poly;
}

void ImageInfo::setFocusInfo(QMap<QString, QString> focusInfo)
{
    m_focusInfo = focusInfo;
}

void ImageInfo::setOneEye(QMap<QString, QString> OneEye)
{
    m_oneEye = OneEye;
}

void ImageInfo::setDisease(QList<QString> dis)
{
	m_disease = dis;
}

void ImageInfo::setOrigin(QImage pix)
{
    m_origin = new QImage(pix);
}

void ImageInfo::setShape(QMap<QString, Shape> shape)
{
    m_shape = shape;
}

void ImageInfo::setStep(float step)
{
    m_step = step;
}

void ImageInfo::setIndex(int index)
{
   m_index = index;
}

void ImageInfo::setState(bool save)
{
	m_save = save;
}

void ImageInfo::setJsonFlag(bool flag)
{
	m_jsonFlag = flag;
}

void ImageInfo::setJsonValue(QJsonValue value)
{
	m_jsonValue = value;
}

