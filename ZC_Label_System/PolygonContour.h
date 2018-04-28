#pragma once

#include <QPolygon>
#include <QImage>
#include <QMap>
#include "opencv2/core/core.hpp"    
#include "opencv2/highgui/highgui.hpp"    
#include "opencv2/imgproc/imgproc.hpp"  

class PolygonContour
{
public:
	PolygonContour();
	virtual ~PolygonContour();

	QPolygonF getPolygonContour(int width, int height, const QPolygonF& polygon);

	QPolygonF getPolygonContourFromWeb(const cv::Mat &image);
};

