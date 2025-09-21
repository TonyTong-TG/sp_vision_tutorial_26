#include"tools.hpp"

cv::Mat resize(cv::Mat img, int target_size)
{
    int original_w = img.cols;
    int original_h = img.rows;
    // Calculate scale
    double scale = std::min(
        (double)target_size / original_w,
        (double)target_size / original_h);

    int new_w = (int)(original_w * scale);
    int new_h = (int)(original_h * scale);
    fmt::print("Resize scale: {}\n", scale);
    fmt::print("Original size: width={}, height={}\n", original_w, original_h);
    fmt::print("Scaled size: width={}, height={}\n", new_w, new_h);

    cv::resize(img, img, cv::Size(new_w, new_h));

    // Background
    cv::Mat bg = cv::Mat::zeros(target_size, target_size, img.type());

    // Center the img
    int x_offset = (target_size - new_w) / 2;
    int y_offset = (target_size - new_h) / 2;
    fmt::print("Offset: x_offset={}, y_offset={}\n", x_offset, y_offset);

    img.copyTo(bg(cv::Rect(x_offset, y_offset, new_w, new_h)));
    
    return bg;
}