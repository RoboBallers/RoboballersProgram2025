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
