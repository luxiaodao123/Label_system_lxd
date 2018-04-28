#ifndef ZOOM_H
#define ZOOM_H

#include <QUndoCommand>
#include "imageinfo.h"

class BigCommand 
{
public:
    BigCommand(ImageInfo info);

private:
    float m_oldStep;
    float m_newStep;

};

class SmallCommand 
{
public:
    SmallCommand(ImageInfo info);

private:
    float m_oldStep;
    float m_newStep;

};

#endif // ZOOM_H
