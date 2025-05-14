import supervision as sv
from trackers import SORTTracker
from ultralytics import YOLO

import cv2
import numpy as np
import time


tracker = SORTTracker()
model = YOLO("yolo11m.pt", verbose=True)
annotator = sv.LabelAnnotator(text_position=sv.Position.CENTER)
trace_annotator = sv.TraceAnnotator()

def callback(frame, _):
    result = model(frame, verbose=False)[0]
    
    #detections = sv.Detections.from_ultralytics(result)

    #detections = tracker.update(detections)
    #detections = detections[detections.class_id == 0]
    
    #annotator.annotate(frame, detections, labels=detections.tracker_id)
    #trace_annotator.annotate(frame, detections)
    
    
'''
video_path = "/home/user/Documents/ros_tensorrt_bridge/video2.mp4"
cap = cv2.VideoCapture(0)
if not cap.isOpened():
    print("Error: Could not open video.")
    exit()
while True:
    ret, frame = cap.read()
    #frame = cv2.resize(frame, (640, 640))
    if not ret:
        print("Error: Could not read frame.")
        break
    
    tr = callback(frame, None)
    

    # Display the frame
    cv2.imshow('Video Frame', frame)

    # Exit on 'q' key press
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()
'''

dummy_input = np.zeros((640, 640, 3), dtype=np.uint8)
start_time = time.time()
for i in range(15000):
    callback(dummy_input, None)
    if i % 100 == 0:
        print(i)
    #cv2.imshow('Video Frame', dummy_input)
    #cv2.waitKey(1)
    
end_time = time.time()
print("FPS: ", 15000 / (end_time - start_time))