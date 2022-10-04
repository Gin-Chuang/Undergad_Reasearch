import cv2
import numpy as np

low_H = 5 #3
low_S = 50 #80
low_V = 35 #28

high_H = 25 #16
high_S = 230 #200
high_V = 110 #85

def modify_lightness_saturation(img):

    origin_img = img

    # 圖像歸一化，且轉換為浮點型
    fImg = img.astype(np.float32)
    fImg = fImg / 255.0

    # 顏色空間轉換 BGR -> HLS
    hlsImg = cv2.cvtColor(fImg, cv2.COLOR_BGR2HLS)
    hlsCopy = np.copy(hlsImg)

    lightness = 0 # lightness 調整為  "1 +/- 幾 %"
    saturation = 100 # saturation 調整為 "1 +/- 幾 %"

    # 亮度調整
    hlsCopy[:, :, 1] = (1 + lightness / 100.0) * hlsCopy[:, :, 1]
    hlsCopy[:, :, 1][hlsCopy[:, :, 1] > 1] = 1  # 應該要介於 0~1，計算出來超過1 = 1

    # 飽和度調整
    hlsCopy[:, :, 2] = (1 + saturation / 100.0) * hlsCopy[:, :, 2]
    hlsCopy[:, :, 2][hlsCopy[:, :, 2] > 1] = 1  # 應該要介於 0~1，計算出來超過1 = 1

    # 顏色空間反轉換 HLS -> BGR 
    result_img = cv2.cvtColor(hlsCopy, cv2.COLOR_HLS2BGR)
    result_img = ((result_img * 255).astype(np.uint8))
    #result_img = cv2.resize(result_img, (1320, 630))
    cv2.namedWindow("modify",0)#建立視窗
    cv2.resizeWindow("modify", 1600, 900)#建立一個500*500大小的視窗
    cv2.imshow("modify", result_img)
    return result_img


def getpos(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        print(frame_HSV[y,x])
        #show HSV value

cv2.namedWindow("modify!",0)#建立視窗
cv2.resizeWindow("modify!", 1600, 900)#建立一個500*500大小的視窗
cv2.namedWindow("imageHSV",0)#建立視窗
cv2.resizeWindow("imageHSV", 1600, 900)#建立一個500*500大小的視窗

img = cv2.imread("test_1.jpg", cv2.IMREAD_UNCHANGED)
img_1 = modify_lightness_saturation(img)
frame_HSV = cv2.cvtColor(img_1, cv2.COLOR_BGR2HSV)
frame_threshold = cv2.inRange(frame_HSV, (low_H, low_S, low_V), (high_H, high_S, high_V))
frame_HSV = cv2.bitwise_and(frame_HSV, frame_HSV, mask = frame_threshold)
#img_2 = cv2.resize(frame_HSV, ( 1320, 630)) 
#img_2 = cv2.resize(frame_HSV, (  630, 1320)) 
#frame_BGR = cv2.cvtColor(img_2, cv2.COLOR_HSV2BGR)


frame_BGR = cv2.cvtColor(frame_HSV, cv2.COLOR_HSV2BGR)



cv2.imshow("imageHSV", frame_HSV)
cv2.setMouseCallback("imageHSV", getpos)
cv2.imshow("modify!", frame_BGR)



cv2.waitKey(0)
