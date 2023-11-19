# Video2ROSbag
一个mp4转rosbag的python脚本
一个图片尺寸转换处理的python脚本

### Usage: 

```shell
python3 Video2ROSbag.py video.mp4 video.bag
rosbag info video.bag  # 查看 bag 包信息
rosbag play -l video.bag camera/image_raw:=image_raw0   # 循环播放图片，并重命名成自己需要的话题名
rqt_image_view  # 显示播放的图片，能正常显示说明ros包制作成功。
```

