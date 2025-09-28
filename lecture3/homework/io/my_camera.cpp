#include "my_camera.hpp"

cv::Mat myCamera::transfer(MV_FRAME_OUT &raw)
{
    MV_CC_PIXEL_CONVERT_PARAM cvt_param;
    cv::Mat img(cv::Size(raw.stFrameInfo.nWidth, raw.stFrameInfo.nHeight), CV_8U, raw.pBufAddr);

    cvt_param.nWidth = raw.stFrameInfo.nWidth;
    cvt_param.nHeight = raw.stFrameInfo.nHeight;

    cvt_param.pSrcData = raw.pBufAddr;
    cvt_param.nSrcDataLen = raw.stFrameInfo.nFrameLen;
    cvt_param.enSrcPixelType = raw.stFrameInfo.enPixelType;

    cvt_param.pDstBuffer = img.data;
    cvt_param.nDstBufferSize = img.total() * img.elemSize();
    cvt_param.enDstPixelType = PixelType_Gvsp_BGR8_Packed;

    auto pixel_type = raw.stFrameInfo.enPixelType;
    const static std::unordered_map<MvGvspPixelType, cv::ColorConversionCodes> type_map = {
        {PixelType_Gvsp_BayerGR8, cv::COLOR_BayerGR2RGB},
        {PixelType_Gvsp_BayerRG8, cv::COLOR_BayerRG2RGB},
        {PixelType_Gvsp_BayerGB8, cv::COLOR_BayerGB2RGB},
        {PixelType_Gvsp_BayerBG8, cv::COLOR_BayerBG2RGB}};
    cv::cvtColor(img, img, type_map.at(pixel_type));

    return img;
}

void myCamera::open(){
    ret_ = MV_CC_EnumDevices(MV_USB_DEVICE, &device_list_);
    if (ret_ != MV_OK)
    {
        throw std::runtime_error("Fail to find any connected camera!");
    }

    if (device_list_.nDeviceNum == 0)
    {
        throw std::runtime_error("Fail to find any connected camera!");
    }

    ret_ = MV_CC_CreateHandle(&handle_, device_list_.pDeviceInfo[0]);
    if (ret_ != MV_OK)
    {
        throw std::runtime_error("Fail to create handle!");
    }

    ret_ = MV_CC_OpenDevice(handle_);
    if (ret_ != MV_OK)
    {
        throw std::runtime_error("Fail to open camera!");
    }
}

myCamera::myCamera(){

    open();

    MV_CC_SetEnumValue(handle_, "BalanceWhiteAuto", MV_BALANCEWHITE_AUTO_CONTINUOUS);
    MV_CC_SetEnumValue(handle_, "ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
    MV_CC_SetEnumValue(handle_, "GainAuto", MV_GAIN_MODE_OFF);
    MV_CC_SetFloatValue(handle_, "ExposureTime", 5000);
    MV_CC_SetFloatValue(handle_, "Gain", 15);
    MV_CC_SetFrameRate(handle_, 60);

    ret_ = MV_CC_StartGrabbing(handle_);
    if (ret_ != MV_OK)
    {
        throw std::runtime_error("Fail to start grabbing!");
    }
}

cv::Mat myCamera::read(){

    ret_ = MV_CC_GetImageBuffer(handle_, &raw_, nMsec_);
    if (ret_ != MV_OK)
    {
        throw std::runtime_error("Fail to get image buffer!");
    }

    cv::Mat img = transfer(raw_);

    ret_ = MV_CC_FreeImageBuffer(handle_, &raw_);
    if (ret_ != MV_OK)
    {
        throw std::runtime_error("Fail to free image buffer!");
    }

    return img;
}

void myCamera::close(){
    
    ret_ = MV_CC_StopGrabbing(handle_);
    if (ret_ != MV_OK)
    {
        throw std::runtime_error("Fail to stop grabbing!");
    }

    ret_ = MV_CC_CloseDevice(handle_);
    if (ret_ != MV_OK)
    {
        throw std::runtime_error("Fail to close device!");
    }

    ret_ = MV_CC_DestroyHandle(handle_);
    if (ret_ != MV_OK)
    {
        throw std::runtime_error("Fail to destroy handle!");
    }
}

myCamera::~myCamera(){
    close();
}
