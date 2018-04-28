#ifndef IMAGEINFO_H
#define IMAGEINFO_H

#include <QImage>
#include <QMap>
#include <QPolygonF>
#include <QPixmap>
#include <QJsonValue>

class Shape
{
public:
    Shape();

    Shape(Shape *temp);

    ~Shape();

	const int getCX() { return m_cx; }

	const int getCY() { return m_cy; }

	const int getR() { return m_r; }

    void setCX(int x);

    void setCY(int y);

    void setR(int r);

private:
    int m_cx;
    int m_cy;
    int m_r;

};

class ImageInfo
{
public:
    ImageInfo();

    ImageInfo(ImageInfo *temp);

    ~ImageInfo();

public:
    const QMap<int, QPolygonF> getPoly() const;

    const float getStep() const;

    const int getIndex() const;

	const bool getState() const;

	const bool getJsonFlag() const;

	QImage *getOrigin();

    const QString getPath() const;

	const QJsonValue getJsonValue() const;

    const QMap<QString, Shape> getShape() const;

    const QMap<QString, QString> getFocusInfo() const;

    const QMap<QString, QString> getOneEye() const;

	const QList<QString> getDisease() const;

    void setPoly(QMap<int, QPolygonF> poly);

    void setFocusInfo(QMap<QString, QString> OneEye);

    void setOneEye(QMap<QString, QString> OneEye);

	void setDisease(QList<QString> dis);

    void setShape(QMap<QString, Shape> shape);

    void setOrigin(QImage pix);

    void setStep(float step);

    void setIndex(int index);

	void setState(bool save);

	void setJsonFlag(bool flag);

	void setJsonValue(QJsonValue value);


private:
    QMap<int, QPolygonF> m_poly;
    float m_step;
    QImage *m_origin;
    int m_index;
	QJsonValue m_jsonValue;
    QMap<QString, QString> m_focusInfo;
    QMap<QString, Shape> m_shape;
    QMap<QString, QString> m_oneEye;
	QList<QString> m_disease;
    QString m_path;
	bool m_save;
	bool m_jsonFlag;
};

#endif // IMAGEINFO_H
