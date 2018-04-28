#include "PolygonContour.h"
#include <QBrush>
#include <QPainter>
#include "QtCvConvert.h"


PolygonContour::PolygonContour()
{
}


PolygonContour::~PolygonContour()
{
}


QPolygonF
PolygonContour::getPolygonContour(int width, int height, const QPolygonF& polygon)
{
	if (width > 0 && height > 0 && polygon.size() > 0)
	{
		const int polygonSize = polygon.size();
		cv::Point* oldPolygonPoints = new cv::Point[polygonSize];
		memset(oldPolygonPoints, 0, sizeof(cv::Point) * polygonSize);
		for (int i = 0; i < polygonSize; i++)
		{
			oldPolygonPoints[i].x = polygon[i].x();
			oldPolygonPoints[i].y = polygon[i].y();
		}
		cv::Mat mat = cv::Mat(height, width, CV_8UC1, cv::Scalar(0));
		const cv::Point* ppt[1] = { oldPolygonPoints };
		cv::fillPoly(mat, ppt, &polygonSize, 1, cv::Scalar(255));
		//cv::imwrite("1.jpg", mat);

		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;
		findContours(mat, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, cv::Point());
		if (contours.size() >= 1)
		{
			std::vector<cv::Point> points = contours[0];
			QPolygonF pf;
			for (int pointIndex = 0; pointIndex < points.size(); pointIndex++)
			{
				QPoint point = QPoint(points[pointIndex].x, points[pointIndex].y);
				pf.append(point);
			}
			return pf;
		}
	}
	return QPolygonF();
}

QPolygonF
PolygonContour::getPolygonContourFromWeb(const cv::Mat &image)
{
	if (image.rows > 0 && image.cols > 0)
	{
		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;
		findContours(image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, cv::Point());
		if (contours.size() >= 1)
		{
			std::vector<cv::Point> points = contours[0];
			QPolygonF pf;
			for (int pointIndex = 0; pointIndex < points.size(); pointIndex++)
			{
				QPoint point = QPoint(points[pointIndex].x, points[pointIndex].y);
				pf.append(point);
			}
			return pf;
		}
	}
	return QPolygonF();
}



