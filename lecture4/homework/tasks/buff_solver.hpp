#ifndef AUTO_BUFF__SOLVER_HPP
#define AUTO_BUFF__SOLVER_HPP
#include "buff_detector.hpp"
#include "tools/img_tools.hpp"
#include "fmt/core.h"

namespace auto_buff
{
class Buff_Solver
{
public:
    Buff_Solver();
    void solvePnP(auto_buff::FanBlade fanblade, cv::Mat &cameraM, cv::Mat &rotationCenterM);

private:
    std::vector<cv::Point2f> img_points_;
    std::vector<cv::Point3f> object_points_;
    double TARGET_HEIGHT_; //单位：米
    double TARGET_WIDTH_;//单位：米
    cv::Mat distort_coeffs_;
    cv::Mat camera_matrix_;
};

}  // namespace auto_buff


#endif  // SOLVER_HPP