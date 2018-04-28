#include "paintlabel.h"
#include <QDebug>

#include "PolygonContour.h"

PaintLabel::PaintLabel(QWidget* parent):
    QLabel(parent)
{
    this->resize(631, 451);
    m_pix = new QImage(this->width(), this->height(), QImage::Format_RGB32);
    m_pix->fill(Qt::white);
    m_isNullImage = true;
    m_index = 1;

	m_white = new QImage(1000, 666, QImage::Format_RGB32);
	m_white->fill(Qt::white);
	m_lastIndex = -1;

}

PaintLabel::~PaintLabel()
{
    delete m_pix;
}

void PaintLabel::paintEvent(QPaintEvent *e)
{
     QPainter wp(this);
	 wp.setOpacity(1);
     wp.drawImage(0, 0, *m_pix);
}

void PaintLabel::mousePressEvent(QMouseEvent *e)
{
    if(m_isNullImage == true)
        return;
    m_PosStart = QPointF(e->pos().x(), e->pos().y());
    m_Poscurrent = m_PosStart;
    m_PointPool.append(m_Poscurrent);

	if (m_lastIndex != -1)
	{
		QPolygonF lastPoint = m_polyPool.value(m_lastIndex);
		_paintPen(lastPoint);
		m_lastIndex = -1;
	}
}

void PaintLabel::mouseMoveEvent(QMouseEvent *e)
{
    if(m_isNullImage == true)
        return;
    QPainter *painter = new QPainter;
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::black);

    painter->begin(m_pix);
    painter->setPen(pen);
    painter->drawLine(m_Poscurrent, QPoint(e->pos().x(), e->pos().y()));
    m_Poscurrent = QPointF(e->pos().x(), e->pos().y());
    painter->end();

    m_PointPool.append(m_Poscurrent);

    update();
    delete painter;

}

void PaintLabel::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_isNullImage == true)
        return;

	m_Poscurrent = QPointF(e->pos().x(), e->pos().y());
	m_PointPool.append(m_Poscurrent);
    if(e->button() == Qt::LeftButton)
    {
        _leftButtomRelaese();
    }

    if(e->button() == Qt::RightButton)
    {
        _rightButtomRelaese();
    }

	*m_pix = m_Ori.scaled(m_Ori.width() * m_step, m_Ori.height() * m_step);
	QMap<int, QPolygonF>::Iterator it = m_polyPool.begin();
	while (it != m_polyPool.end())
	{
		QPainter *painter = new QPainter;
		QPolygonF temp = it.value();
		_paintPen(temp);
		painter->begin(m_pix);

		QPainterPath path;
		path.addPolygon(temp);
		painter->setOpacity(0);
		painter->fillPath(path, QBrush(Qt::white));
		painter->end();
		update();
		it++;
		delete painter;
	}
    m_PointPool.clear();
}

void PaintLabel::wheelEvent(QWheelEvent *e)
{
    if(m_isNullImage == true)
        return;
    float step;
    if(e->delta() > 0)
        step = 1.1;
    else
        step = 0.9;

    changeSize(step);

}

void PaintLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
     QMap<int,QPolygonF>::Iterator i = m_polyPool.begin();
     while(i != m_polyPool.end())
     {
           if(i.value().containsPoint(e->pos(), Qt::OddEvenFill))
           {
               emit currentLabel(i.key());
           }
           ++i;
     }
	 if (m_lastIndex != -1)
	 {
		 QPolygonF lastPoint = m_polyPool.value(m_lastIndex);
		 _paintPen(lastPoint);
		 m_lastIndex = -1;
	 }

}

void PaintLabel::_leftButtomRelaese()
{
	// 补全点的信息
	m_PointPool.append(m_PosStart);
	QPolygonF polygon(m_PointPool);
	// 清除原路径的信息
	_cleanPen(polygon);
	if (polygon.count() == 2)
	{
		return;
	}

	PolygonContour polygonContour;
	QPolygonF p = polygonContour.getPolygonContour(width(), height(), polygon);

	if (p.boundingRect().width() < 5)
	{
		qDebug() << "Poly width less than 5";
		return;
	}

	_addPolygon(p);

    update();
}

void PaintLabel::_rightButtomRelaese()
{
	// 补全点的信息
	m_PointPool.append(m_PosStart);
	QPolygonF polygon(m_PointPool);
	// 清除原路径的信息
	_cleanPen(polygon);

	PolygonContour polygonContour;
	QPolygonF p = polygonContour.getPolygonContour(width(), height(), polygon);

	_erasePolygon(p);

	update();
}

void PaintLabel::_cleanPen(const QPolygonF& pointPool)
{
    QPainter *painter = new QPainter;
    for(int i = 0 ; i < pointPool.count(); i++)
    {
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(2);
        pen.setColor(Qt::white);
        painter->begin(m_pix);
        painter->setPen(pen);
        if(i == pointPool.count() - 1 )
        {
           painter->drawLine(pointPool.at(i), pointPool.at(0));
        }
        else
        {
           painter->drawLine(pointPool.at(i), pointPool.at(i + 1));
        }
        painter->end();
    }

    update();
    delete painter;
}

void PaintLabel::_paintPen(const QPolygonF& pointPool)
{
    QPainter *painter = new QPainter;
    for(int i = 0 ; i< pointPool.count(); i++)
    {
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(2);
        pen.setColor(Qt::black);

        painter->begin(m_pix);
        painter->setPen(pen);
        if(i == 0 )
        {
            painter->drawLine(pointPool.at(pointPool.count() - 1), pointPool.at(0));
        }
        else
        {
            painter->drawLine(pointPool.at(i-1), pointPool.at(i));
        }
        painter->end();
    }
    update();
    delete painter;
}

void PaintLabel::_myIntersect(int flag)
{
    QMap<int, QPolygonF>::Iterator it = m_polyPool.begin();
    QMap<int, QPolygonF>::Iterator itTemp;
    QPolygonF temp;
    int tempIndex = 0;
    while(it != m_polyPool.end())
    {
          itTemp = it++;
          if(itTemp.value().containsPoint(m_PosStart, Qt::OddEvenFill))
          {
              temp = itTemp.value();
              for(int i = 0; i < m_PointPool.count() - 1; i++)
              {
                  if(temp.containsPoint(temp[i], Qt::OddEvenFill) && !temp.containsPoint(temp[i + 1], Qt::OddEvenFill))
                  {

                  }
              }
//              *m_Poly = temp.united(*m_Poly);
//              tempIndex = itTemp.key();
//              m_polyPool.erase(itTemp);
          }
    }
}

bool 
PaintLabel::_addPolygon(const QPolygonF& polygon)
{
	std::vector<int> m_vecIntersectIndex;
	std::vector<QPolygonF> m_vecIntersectPolygon;
	for (QMap<int, QPolygonF>::Iterator it = m_polyPool.begin();
		it != m_polyPool.end(); it++)
	{
		if (!it.value().intersected(polygon).isEmpty())
		{
			m_vecIntersectIndex.push_back(it.key());
			m_vecIntersectPolygon.push_back(it.value());
		}
	}
	bool bAddPolygon = true;
	QPolygonF addPolygon = polygon;
	int intersectCount = m_vecIntersectIndex.size();
	for (int i = 0; i < intersectCount; i++)
	{
		// 求合并区域
		addPolygon = addPolygon.united(m_vecIntersectPolygon[i]);
		// 擦除原绘制区域
		_cleanPen(m_vecIntersectPolygon[i]);
		// 重列表中删除
		m_polyPool.remove(m_vecIntersectIndex[i]);
	}
	if (intersectCount > 0)
	{
		PolygonContour polygonContour;
		addPolygon = polygonContour.getPolygonContour(width(), height(), addPolygon);
		// 如果只有一个相交区域，则重新插回到原ID位置
		if (1 == intersectCount)
		{
			bAddPolygon = false;
			m_polyPool.insert(m_vecIntersectIndex[0], addPolygon);
		}
		else
		{
			for (int i = 0; i < intersectCount; i++) {
				emit removeLabel(m_vecIntersectIndex[i]);
			}
		}
	}
	// 绘制区域
	_paintPen(addPolygon);
	// 需要新增区域
	if (bAddPolygon)
	{
		m_polyPool.insert(m_index, addPolygon);
		emit addLabel(m_index++);
	}
	return false;
}

bool 
PaintLabel::_erasePolygon(const QPolygonF& polygon)
{
	std::vector<int> m_vecIntersectIndex;
	std::vector<QPolygonF> m_vecIntersectPolygon;
	for (QMap<int, QPolygonF>::Iterator it = m_polyPool.begin();
		it != m_polyPool.end(); it++)
	{
		if (!it.value().intersected(polygon).isEmpty())
		{
			m_vecIntersectIndex.push_back(it.key());
			m_vecIntersectPolygon.push_back(it.value());
		}
	}
	for (int i = 0; i < m_vecIntersectIndex.size(); i++)
	{
		QPolygonF p = m_vecIntersectPolygon[i].subtracted(polygon);
		_cleanPen(m_vecIntersectPolygon[i]);
		if (!p.isEmpty())
		{
			PolygonContour polygonContour;
			p = polygonContour.getPolygonContour(width(), height(), p);
			_paintPen(p);
			m_polyPool[m_vecIntersectIndex[i]] = p;
		}
		else
		{
			m_polyPool.remove(m_vecIntersectIndex[i]);
			emit removeLabel(m_vecIntersectIndex[i]);
		}
	}
	return false;
}

void PaintLabel::changeSize(float step)
{
	if (m_isNullImage == true)
		return;
    float origin = m_step;
    m_step = m_step * step;

    if(m_step < 1)
    {
        m_step = 1.0;
        origin = m_step / origin;
    }

    if(m_step > 5)
    {
        //qDebug() << m_step << "now";
        m_step = origin;
        return;
    }

    cleanPainter();
	_changePoint(step, origin);
	emit  changeImageSize(m_step);
    

}

void PaintLabel::_changePoint(float step, float origin)
{
	*m_pix = m_Ori.scaled(m_Ori.width() * m_step, m_Ori.height() * m_step);
	this->resize(m_pix->size());

	QMap<int, QPolygonF>::Iterator it = m_polyPool.begin();
	while (it != m_polyPool.end())
	{

		QPolygonF temp = it.value();
		//_cleanPen(temp);
		int count = temp.count();
		for (int i = 0; i < count; i++)
		{
			qDebug() << temp[i];
			if (m_step > 1)
				temp[i] = QPointF(temp[i].x() * step, temp[i].y() * step);
			else
				temp[i] = QPointF(temp[i].x() * origin, temp[i].y() * origin);
			qDebug() << temp[i] << "one";
		}

		QPainter *painter = new QPainter;
		m_polyPool[it.key()] = temp;
		_paintPen(temp);
		painter->begin(m_pix);

		QPainterPath path;
		path.addPolygon(temp);
		painter->setOpacity(0);
		painter->fillPath(path, QBrush(Qt::white));
		painter->end();
		update();
		it++;
		delete painter;
	}

	
}

void PaintLabel::cleanPainter()
{
	delete m_pix;
	m_pix = new QImage(this->width(), this->height(), QImage::Format_RGB32);
	m_pix->fill(Qt::white);
}

void PaintLabel::Resize(QSize size)
{
	this->resize(size.width(), size.height());
	*m_pix = m_pix->scaled(size.width(), size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	update();
}

QMap<int, QPolygonF> PaintLabel::labelInfo()
{
    return m_polyPool;
}

void PaintLabel::isNullImage(bool null)
{
    m_isNullImage = null;
}

void PaintLabel::setStep(float step)
{
    m_step = step;
}

void PaintLabel::cleanPolyPool()
{
    m_polyPool.clear();
}

float PaintLabel::getStep()
{
    return m_step;
}

void PaintLabel::paint(QPolygonF poly, int index)
{
    _paintPen(poly);
    m_polyPool.insert(index, poly);
}

void PaintLabel::setIndex(int index)
{
    m_index = index;
}

const int PaintLabel::getIndex() const
{
    return m_index;
}

void PaintLabel::BackImage(QString path)
{
	m_pix->load(path);
	int width = m_pix->width();
	int height = m_pix->height();
	if (width == 0)
		return;
	*m_pix = m_pix->scaled(1000, height * 1000 / width);
	this->resize(m_pix->size());
	m_Ori = QImage(*m_pix);
	update();
}

void PaintLabel::BackImage(QImage pix)
{
	*m_pix = QImage(pix);
	int width = m_pix->width();
	int height = m_pix->height();
	*m_pix = m_pix->scaled(1000, height * 1000 / width);
	m_Ori = QImage(*m_pix);
	this->resize(m_pix->size());
	update();
}

QImage PaintLabel::OriPic()
{
	return m_Ori;
}

void PaintLabel::clean()
{
	*m_pix = QImage(*m_white);
	update();
}

void PaintLabel::showLabel(int index)
{
	QPainter *painter = new QPainter;
	QPolygonF pointPool = m_polyPool.value(index);
	if (m_lastIndex != -1)
	{
		QPolygonF lastPoint = m_polyPool.value(m_lastIndex);
		_paintPen(lastPoint);
	}

	for (int i = 0; i < pointPool.count(); i++)
	{
		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(2);
		pen.setColor(Qt::green);

		painter->begin(m_pix);
		painter->setPen(pen);
		if (i == 0)
		{
			painter->drawLine(pointPool.at(pointPool.count() - 1), pointPool.at(0));
		}
		else
		{
			painter->drawLine(pointPool.at(i - 1), pointPool.at(i));
		}
		painter->end();
	}
	m_lastIndex = index;
	update();
	delete painter;
}