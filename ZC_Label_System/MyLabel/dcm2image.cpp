#include "dcm2image.h"
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/dcistrmf.h"
#include "dcmtk/dcmdata/dcrledrg.h"
#include "dcmtk/dcmdata/dcpxitem.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "dcmtk/dcmjpeg/djdecode.h"
#include "dcmtk/dcmimage/diregist.h"

Dcm2Image::Dcm2Image(QString path)
{
    //std::string file_path = "C:\\Users\\liyan\\Desktop\\chaosheng\\1.dcm";                                      //dcm文件
    m_image = 0;
    ///register RLE decompression codecs
    DcmRLEDecoderRegistration::registerCodecs(OFFalse, OFTrue);
    /// register JPEG decompression codecs
    DJDecoderRegistration::registerCodecs();

    DcmFileFormat *fileFormat = new DcmFileFormat();
    OFCondition condition = fileFormat->loadFile(path.toStdString().c_str());
    if (!condition.good()) {
        std::cout << "DcmConvert::set file fail:" << std::endl;
        return;
    }
    else {
        m_image = 0;
        DcmDataset * dset = fileFormat->getDataset();
        DcmObject *object = NULL;
        DiRegister r;
        DicomImage *dcmImage = new DicomImage(dset, dset->getOriginalXfer(), CIF_MayDetachPixelData);
        if (dcmImage != NULL) {
            if (dcmImage->getStatus() == EIS_Normal) {
                dcmImage->setNoDisplayFunction();
                dcmImage->hideAllOverlays();
                dcmImage->setNoVoiTransformation();
                int width = dcmImage->getWidth();
                int height = dcmImage->getHeight();
                ulong size = width * height;
                if (dcmImage->isMonochrome()) {
                    uchar *data = new uchar[size];
                    dcmImage->setMinMaxWindow();
                    dcmImage->getOutputData(data, size, 8);
                    m_image = new QImage(data, width, height, 8, QImage::Format_Mono);
                }
                else {
                    size = size * 4;
                    uchar *data = new uchar[size];
                    uchar* pixelData = (uchar *)(dcmImage->getOutputData(8));
                    unsigned long y = 0;
                    for (unsigned long x = 0; x < size; x += 4) {
                        data[x] = pixelData[y];     //R
                        data[x + 1] = pixelData[y + 1]; //G
                        data[x + 2] = pixelData[y + 2]; //B
                        data[x + 3] = 0xFF; //Alpha
                        y += 3;
                    }
                    m_image = new QImage(data, width, height, QImage::Format_RGBA8888);
                    //ui.label->setPixmap(QPixmap::fromImage(*image));
                }
            }
            else {
                std::cout << "Error: cannot load DICOM image (" << DicomImage::getString(dcmImage->getStatus()) << ")" << std::endl;
            }
            delete dcmImage;
            dcmImage = 0;
            }
        }
}

const QImage *Dcm2Image::getImage() const
{
    return m_image;
}
