#pragma once

#include <QImage>
#include "opencv2/core.hpp"

class QtCvConvert
{
public:
	QtCvConvert();
	~QtCvConvert();

	static QImage cvMat2QImage(const cv::Mat& mat);

	static cv::Mat QImage2cvMat(const QImage& image);
};

