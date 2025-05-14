import supervision as sv
from trackers import SORTTracker
from ultralytics import YOLO

import cv2
import numpy as np

tracker = SORTTracker()
model = YOLO("yolo11n-obb.pt")
annotator = sv.LabelAnnotator(text_position=sv.Position.CENTER)
trace_annotator = sv.TraceAnnotator()

def callback(frame, _):
    result = model(frame)[0]
    print(result.obb.xyxy.cpu().numpy().shape)
    
    #class_id = result.boxes.cls.cpu().numpy()

    '''
    detection = sv.Detections(
        xyxy=result.boxes.xyxy.cpu().numpy().astype(int),
        class_id=result.boxes.cls.cpu().numpy().astype(int),
    )

    xyxy_selected = []
    class_id_selected = []
    confidence_selected = []
    print(result.boxes.conf.cpu().numpy())
    for xyxy, class_id, confidence in zip(
        result.boxes.xyxy.cpu().numpy().astype(int),
        result.boxes.cls.cpu().numpy().astype(int),
        result.boxes.conf.cpu().numpy(),
    ):
        if class_id in [0] and confidence > 0.4:
            xyxy_selected.append(xyxy)
            class_id_selected.append(class_id)
    xyxy_selected = np.array(xyxy_selected)
    class_id_selected = np.array(class_id_selected)
    detection = sv.Detections(
        xyxy=xyxy_selected,
        class_id=class_id_selected,
        confidence=result.boxes.conf.cpu().numpy()[class_id_selected],
    )

    detection = tracker.update(detection)
    return annotator.annotate(frame, detection, labels=detection.tracker_id)
    '''
    
    
    
    
    
    detections = sv.Detections.from_ultralytics(result)
    #detections = detections[detections.class_id == 0]
    #detections = detections[detections.confidence > 0.4]
    #detections = detections[detections.area > 2000]

    
    detections = tracker.update(detections)
    """
    for detection in detections:
        xmin = int(detection[0][0])
        ymin = int(detection[0][1])
        xmax = int(detection[0][2])
        ymax = int(detection[0][3])

        cv2.rectangle(frame, (xmin, ymin), (xmax, ymax), (0, 255, 0), 2)
    """

    annotator.annotate(frame, detections, labels=detections.tracker_id)
    trace_annotator.annotate(frame, detections)
    

video_path = "/home/user/Documents/ros_tensorrt_bridge/video3.mp4"
cap = cv2.VideoCapture(video_path)
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
    if cv2.waitKey(0) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()