import cv2
import numpy as np
import pybind_detections



def convert_grey(image, detection):
    print(dir(detection))
    size_ = detection.size
    print(size_)
    conf = np.array(detection.conf_array).reshape(-1, 4)
    print(conf)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    cv2.imshow("Gri Görüntü", gray)
    cv2.waitKey(0)
    cv2.destroyAllWindows()