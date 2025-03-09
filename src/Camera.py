import sensor, image, struct, time
from pyb import UART

# pin 4 and 5
uart = UART(2, 115200)

COLOR_THRESHOLDS = {
    b'R': (30, 65, 25, 60, 10, 50), 
    b'G': (35, 70, -50, -20, 0, 30), 
    b'B': (20, 50, -10, 20, -60, -20), 
    b'Y': (60, 90, -10, 10, 40, 80)  
}

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_auto_gain(False)  
sensor.set_auto_whitebal(False)

while True:
    if uart.any():  
        requested_color = uart.read(1) 
        
        if requested_color in COLOR_THRESHOLDS:
            color_threshold = COLOR_THRESHOLDS[requested_color]
            
            img = sensor.snapshot()
            blobs = img.find_blobs([color_threshold], pixels_threshold=100, area_threshold=100)
            
            if blobs:
                largest_blob = max(blobs, key=lambda b: b.pixels())
                cx = largest_blob.cx()  
                
                # assuming 60-degree FOV)
                angle = (cx - img.width() / 2) * (60 / (img.width() / 2))

                print(f"Detected {requested_color.decode()}: Angle {angle:.2f}")

                uart.write(struct.pack('d', angle))


# Optimized Japanese Method

# import sensor, image, time, math, ustruct
# from pyb import UART

# # Initialize UART (baud rate 115200, adjust as needed)
# uart = UART(3, 115200, timeout_char=1000)  # UART3 is used on OpenMV

# # Initialize camera
# sensor.reset()
# sensor.set_pixformat(sensor.RGB565)  # Use RGB for color detection
# sensor.set_framesize(sensor.QVGA)  # 320x240 resolution
# sensor.skip_frames(time=2000)
# clock = time.clock()

# # Define the goal color threshold (Yellow in HSV)
# goal_threshold = (30, 100, 100, 255, 100, 255)  # Adjust based on testing

# CENTER_X = 160  # Image center (for QVGA 320x240)
# CENTER_Y = 120

# NUM_ANGLES = 36  # How many angles to check (every 10 degrees)
# MAX_RADIUS = 100  # How far out to scan from the center

# while True:
#     clock.tick()
#     img = sensor.snapshot()

#     goal_positions = []  # Store goal detection distances per angle

#     # Scan radially outward in multiple directions
#     for i in range(NUM_ANGLES):
#         angle = (i * 10)  # Every 10 degrees
#         radian = math.radians(angle)
#         found_goal = False

#         # Move outward from the center
#         for r in range(5, MAX_RADIUS, 5):  # Step in increments of 5 pixels
#             x = int(CENTER_X + r * math.cos(radian))
#             y = int(CENTER_Y + r * math.sin(radian))

#             if 0 <= x < img.width() and 0 <= y < img.height():
#                 pixel = img.get_pixel(x, y)

#                 # Check if the pixel matches the goal color
#                 if (goal_threshold[0] <= pixel[0] <= goal_threshold[1] and
#                     goal_threshold[2] <= pixel[1] <= goal_threshold[3] and
#                     goal_threshold[4] <= pixel[2] <= goal_threshold[5]):

#                     goal_positions.append((angle, r))  # Store angle and radius
#                     found_goal = True
#                     break  # Stop scanning outward

#     # Process detected goal positions
#     best_angle = -1.0  # Default to -1 (no goal detected)

#     if goal_positions:
#         # Find the best shooting angle (longest open space)
#         max_distance = 0
#         for angle, distance in goal_positions:
#             if distance > max_distance:
#                 max_distance = distance
#                 best_angle = float(angle)  # Convert to double

#         print("Best shooting angle:", best_angle)

#     # Send best_angle over UART as a double (4 bytes in IEEE 754 format)
#     uart.write(ustruct.pack('f', best_angle))  # 'f' = 4-byte float format

#     print("FPS:", clock.fps())
