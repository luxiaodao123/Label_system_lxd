#ifndef DCM2IMAGE_H
#define DCM2IMAGE_H

#include<QImage>

class Dcm2Image
{
public:
    Dcm2Image(QString path);

    const QImage *getImage() const;
private:
    QImage *m_image;
};

#endif // DCM2IMAGE_H
