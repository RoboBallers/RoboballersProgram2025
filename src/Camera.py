import sensor
import time
import struct
from pyb import UART
from machine import LED

led = LED("LED_BLUE")

threshold_index = 0  # 0 for yellow, 1 for blue

thresholds = [
    (27, 68, -10, 4, 14, 51),  # Yellow threshold
    (0, 0, 0, 0, 0, 0)         # Blue threshold
]

FOV_HORIZONTAL = 70  # degrees
DEADZONE_PIXELS = 5
BLOB_MIN_PIXELS = 150  # <-- minimum size in pixels to accept blob (low value, you can adjust)

uart = UART(3, 9600, timeout_char=200)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()

while True:
    clock.tick()
    img = sensor.snapshot()

    if uart.any():
        char = uart.readchar()
        if char == ord('b'):
            threshold_index = 1
            print("Tracking Blue Goal")
        elif char == ord('y'):
            threshold_index = 0
            print("Tracking Yellow Goal")

    center_x = img.width() // 2
    degrees_per_pixel = FOV_HORIZONTAL / img.width()

    blobs = img.find_blobs(
        [thresholds[threshold_index]],
        pixels_threshold=150,
        area_threshold=150,
        merge=True,
    )

    if blobs:
        biggest_blob = max(blobs, key=lambda b: b.pixels())

        if biggest_blob.pixels() >= BLOB_MIN_PIXELS:  # Check if blob is big enough
            # Draw rectangle and cross at the center
            img.draw_rectangle(biggest_blob.rect(), color=(255, 0, 0))  # red rectangle
            img.draw_cross(biggest_blob.cx(), biggest_blob.cy(), color=(0, 255, 0))  # green cross

            error_x = biggest_blob.cx() - center_x

            if abs(error_x) > DEADZONE_PIXELS:
                degrees_to_turn = int(error_x * degrees_per_pixel)
            else:
                degrees_to_turn = 0

            print("Degrees to Turn:", degrees_to_turn)

            uart.write(b'\xAA')  # SYNC BYTE
            uart.write(struct.pack("<i", degrees_to_turn))

        else:
            # Blob too small → treat as "no target"
            print(999)
            uart.write(b'\xAA')
            uart.write(struct.pack("<i", 999))

    else:
        print(999)
        uart.write(b'\xAA')
        uart.write(struct.pack("<i", 999))

    # led.on()
    # time.sleep_ms(15)
    # led.off()
    # time.sleep_ms(10)
    # led.on()
    # time.sleep_ms(15)
    # led.off()
    # time.sleep_ms(100)
