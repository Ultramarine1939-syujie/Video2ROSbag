import os
import cv2

# 获取当前文件夹下所有图片文件的文件名
image_files = [f for f in os.listdir('.') if os.path.isfile(f) and f.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp'))]

# 遍历每个图片文件并更改分辨率
for image_file in image_files:
    # 读取图片
    image = cv2.imread(image_file)
    
    if image is not None:
        # 更改分辨率为640x480
        resized_image = cv2.resize(image, (640, 480))
        
        # 保存更改分辨率后的图片
        new_image_file = 'resized_' + image_file
        cv2.imwrite(new_image_file, resized_image)
        print(f'{image_file} 已经更改分辨率并保存为 {new_image_file}')
    else:
        print(f'无法读取 {image_file}')

print('所有图片处理完成！')
