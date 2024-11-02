from ultralytics import YOLO
import cv2
import serial

# Load a pretrained YOLO model
model = YOLO("bestt.pt")

# Open the webcam (change the argument to 0 or 1 depending on your camera index)
cap = cv2.VideoCapture(0)

# Initialize serial communication (adjust COM port and baud rate if needed)
ser = serial.Serial('COM5', 9600)  # Ensure this is the correct COM port and baud rate

# Check if the webcam opened successfully
if not cap.isOpened():
    print("Error: Could not open webcam.")
    exit()

# Set the confidence threshold
confidence_threshold = 0.9

# Loop to continuously get frames from the webcam
while True:
    ret, frame = cap.read()
    if not ret:
        print("Error: Failed to capture image.")
        break

    # Perform object detection on the current frame
    results = model(frame)

    # Check if any detection with a score >= confidence_threshold occurred
    detection_found = any(box.conf >= confidence_threshold for box in results[0].boxes)

    # Send '1' if a high-confidence detection is found, otherwise send '0'
    if detection_found:
        ser.write(b'1')  # Send byte '1' over serial to COM8
    else:
        ser.write(b'0')  # Send byte '0' over serial to COM8

    # Visualize the results on the frame
    annotated_frame = results[0].plot()

    # Display the annotated frame
    cv2.imshow("YOLO Real-Time Detection", annotated_frame)

    # Break the loop if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

# Release the webcam, close all OpenCV windows, and close the serial connection
cap.release()
cv2.destroyAllWindows()
ser.close()
