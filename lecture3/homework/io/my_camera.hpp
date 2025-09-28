#ifndef _MY_CAMERA_H_
#define _MY_CAMERA_H_

#include "hikrobot/include/MvCameraControl.h"
#include <opencv2/opencv.hpp>
#include <stdexcept>

class myCamera{
private:
    cv::Mat transfer(MV_FRAME_OUT &raw);
    void open();
    void close();

    void *handle_;
    int ret_;
    MV_CC_DEVICE_INFO_LIST device_list_;
    MV_FRAME_OUT raw_;
    unsigned int nMsec_ = 100;
    
public:
    myCamera();
    cv::Mat read();
    ~myCamera();
};

#endif