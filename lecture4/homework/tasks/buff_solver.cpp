#include "buff_solver.hpp"


namespace auto_buff
{
    void Buff_Solver::solvePnP(auto_buff::FanBlade fanblade, cv::Mat &cameraM, cv::Mat &rotationCenterM)
    {
        cv::Mat rvec, tvec;
        img_points_ = {fanblade.points[0], fanblade.points[1], fanblade.points[2], fanblade.points[3],fanblade.points[4],fanblade.points[5]};
        cv::solvePnP(object_points_, img_points_, camera_matrix_, distort_coeffs_, rvec, tvec);

        cv::Mat R;
        cv::Rodrigues(rvec, R);
        cameraM = -R.t() * tvec;

        cv::Mat L_B = (cv::Mat_<double>(3, 1) << 0.0, -1.4, 0.0);
        rotationCenterM = R * L_B + tvec;
    }
    Buff_Solver::Buff_Solver(){
        TARGET_HEIGHT_ = 0.300;
        TARGET_WIDTH_ = 0.308;
        camera_matrix_ = (cv::Mat_<double>(3, 3) << 1286.307063384126, 0, 645.34450819155256,
                          0, 1288.1400736562441, 483.6163720308021,
                          0, 0, 1);
        distort_coeffs_ = (cv::Mat_<double>(1, 5) << -0.47562935060124745, 0.21831745829617311, 0.0004957613589406044, -0.00034617769548693592, 0);
        object_points_ = {
            {0, TARGET_HEIGHT_ / 2, 0}, {-TARGET_WIDTH_ / 2, 0, 0}, {0, -TARGET_HEIGHT_ / 2, 0}, {TARGET_WIDTH_ / 2, 0, 0},{0,0,0},{0,-0.520,0}};
        
    }

}  // namespace auto_buff
