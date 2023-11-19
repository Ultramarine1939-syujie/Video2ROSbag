#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "calibrate.h"


using namespace std;
using namespace cv;




Calibrate::Calibrate(void){
 	
  cout << "Starting mono_calibrate." << endl;
}


void Calibrate::run(void){

  // 标定板图像存放位置
  #define PATH "../pic/*"

  // 定义棋盘上角点的分布，注意我这里是 9*6 的棋盘
  int corners_xn = 9, corners_yn = 6;

  // 定义棋盘上小方块的边长，这个的数值不影响标定的内参矩阵与畸变矩阵的结果，具体看算法原理，可以当做一个比例因子被约去了
  double corners_step = 1;

  // 定义用来保存导入的图片
  Mat image_in; 

  // 定义用来保存文件路径的容器
  std::vector<cv::String> filelist;

  // 定义用来保存旋转和平移矩阵的容器
  vector<Mat> rvecs, tvecs;

  // 定义相机矩阵，畸变矩阵
  Mat cameraMatrix;
  Mat distCoeffs;
  int flags = 0;

  // 定义保存图像二维角点的容器，即点在像素坐标系下的二维像素坐标
  vector<Point2f> corners;

  // 定义保存图像二维角点的容器，即点在像素坐标系下的二维像素坐标。第一层vector代表每张图像的角点，第二层vector代表不同的图像
  vector<vector<Point2f> > corners2;

  // 定义保存图像三维角点的容器，即点在相机坐标系下的三维位置坐标
  vector<Point3f> worldPoints;

  // 定义保存图像三维角点的容器，即点在相机坐标系下的三维位置坐标。第一层vector代表每张图像的角点，第二层vector代表不同的图像
  vector<vector<Point3f> > worldPoints2;


//*********************** 1.根据棋盘格式，计算棋盘标定板上三维点的坐标，注意排列：逐行从左到右 *************************
  for(int j = 0; j < corners_yn; j++){
      for(int k = 0; k < corners_xn; k++){
          worldPoints.push_back(Point3f(k*corners_step ,j*corners_step ,0.0f));           
      }
  }


//*************** 1.读取一个文件夹中的所有图片（所有标定图片）**********************
  glob(PATH, filelist); 


//*************************** 2.遍历图像，为每一张图像找角点 **********************
  for(int i = 0; i < filelist.size(); i++){

    std::cout << filelist[i] << std::endl;

    // 一张张读入图片；
    image_in = imread(filelist[i]);

    // 找图片的角点，参数分别为：
    // 输入图片，图片内角点数（不算棋盘格最外层的角点），输出角点，注意我这里是 9*6 的棋盘，角点排列：逐行从左到右
    bool found = findChessboardCorners(image_in, Size(9,6),corners,CALIB_CB_ADAPTIVE_THRESH|CALIB_CB_NORMALIZE_IMAGE);

    // 将每一张图片上找到的角点在像素坐标系上的二维像素坐标作为一个vector保存
    corners2.push_back(corners);

    //画出角点
    drawChessboardCorners(image_in,Size(9,6),corners, found);

    //显示图像
    imshow("test",image_in);

    // 图像刷新等待时间，单位ms
    waitKey(100);

    // 将每一张图片上找到的角点在相机坐标系下的三维坐标作为一个vector保存
    worldPoints2.push_back(worldPoints);
  }


//*********************** 4.标定 *************************
calibrateCamera(worldPoints2,corners2,image_in.size(),cameraMatrix,distCoeffs,
                    rvecs,tvecs);


//************************************* 5.查看参数 *****************************************
  cout << endl;
  cout << " Camera intrinsic: " << cameraMatrix.rows << "x" << cameraMatrix.cols << endl;
  cout << cameraMatrix.at<double>(0,0) << " " << cameraMatrix.at<double>(0,1) << " " << cameraMatrix.at<double>(0,2) << endl;
  cout << cameraMatrix.at<double>(1,0) << " " << cameraMatrix.at<double>(1,1) << " " << cameraMatrix.at<double>(1,2) << endl;
  cout << cameraMatrix.at<double>(2,0) << " " << cameraMatrix.at<double>(2,1) << " " << cameraMatrix.at<double>(2,2) << endl;

  cout << endl;
  cout << "DistCoeffs: " << endl;
  cout << distCoeffs.rows << "x" <<distCoeffs.cols << endl;
  for(int i = 0;i < distCoeffs.cols;i++)
  {
      cout << distCoeffs.at<double>(0,i) << " " ;
  }
  cout <<endl;
}


Calibrate::~Calibrate(void){
  cout << "byby ~~~ I'm jianbao" << endl;
}





