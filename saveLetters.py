# November 8, 2025
# Runs MediaPipe and stores coordinate data into a csv for model training

import cv2
import mediapipe as mp
import csv
import time

# declare vars
LABEL = input("Enter the letter you're recording (A-Z): ").strip().upper() # ask for asl letter
DURATION = 10
FILENAME = "asl_data.csv"

# initialize MediaPipe Hands and drawing utilities
mp_hands = mp.solutions.hands
mp_draw = mp.solutions.drawing_utils

# initialize webcam
cap = cv2.VideoCapture(0)

# prepare CSV file (create header if not exists)
with open(FILENAME, 'a', newline='') as f:
    writer = csv.writer(f)
    # If file is empty, write header
    if f.tell() == 0:
        header = [f"x{i}" for i in range(21)] + [f"y{i}" for i in range(21)] + [f"z{i}" for i in range(21)] + ["label"]
        writer.writerow(header)

#---------GET COORDINATES----------#

with mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=1,
    min_detection_confidence=0.7,
    min_tracking_confidence=0.7) as hands:

    # run the program for 10 sec
    start_time = time.time()
    print(f"\nRecording for letter '{LABEL}'... Hold your hand steady!\n")
    while time.time() - start_time < DURATION:
        success, img = cap.read()
        if not success:
            print("could not read from camera")
            break
        
        img = cv2.flip(img, 1)

        # convert to RGB for MediaPipe processing
        img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

        # process the frame and detect hands
        results = hands.process(img_rgb)

        # if a hand is detected, draw landmarks
        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                mp_draw.draw_landmarks(img, hand_landmarks, mp_hands.HAND_CONNECTIONS)

                # get wrist landmark
                wrist = hand_landmarks.landmark[0]
                coords = []

                for lm in hand_landmarks.landmark:
                    coords.extend([lm.x - wrist.x, lm.y - wrist.y, lm.z - wrist.z])
                
                # write to csv file
                row = coords + [LABEL]
                with open(FILENAME, 'a', newline='') as f:
                    writer = csv.writer(f)
                    writer.writerow(row)      
        
        # display the video
        cv2.imshow("ASL Hand Tracker", img)  
        cv2.setWindowProperty("ASL Hand Tracker", cv2.WND_PROP_TOPMOST, 1)
        
        # press 'ESC KEY' to quit or 'X' button
        if cv2.waitKey(1) & 0xFF == 27 or cv2.getWindowProperty("ASL Hand Tracker", cv2.WND_PROP_VISIBLE) < 1:
            break 

# Release resources
print("\n✅ Recording complete! Data saved to:", FILENAME)
cap.release()
cv2.destroyAllWindows()
