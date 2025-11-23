import PIL
from PIL import Image
import os

ascii_Chars = ["@", "&", "#", "%", "?", "*", "+", ";", ":", ",", "."]

def resize_img(image, new_width = 100):
    width, height = image.size
    ratio = height/width
    new_height = int(new_width * ratio * 0.55)
    new_image = image.resize((new_width, new_height))
    return new_image

def pixels_to_ascii(image):
        pixels = image.getdata()
        characters = "".join(ascii_Chars[pixel//25] for pixel in pixels)
        return characters

def main(new_width = 100): 
    input_folder = "frames"
    output_folder = "ascii_txt"
    os.makedirs(output_folder, exist_ok=True)

    frame_count = 0
    for filename in sorted(os.listdir(input_folder)):
         
        path_in = os.path.join(input_folder, filename)
        output_filename = os.path.splitext(filename)[0] + ".txt"
        path_out = os.path.join(output_folder, output_filename)

        if filename.endswith(('.jpg', '.png', '.jpeg')):
            image = PIL.Image.open(path_in).convert('L')
            new_img_data = pixels_to_ascii(resize_img(image))

            pixel_count = len(new_img_data)
            ascii_img = "\n".join([new_img_data[index:(index+new_width)] for index in range(0, pixel_count, new_width)])

            with open(path_out, 'w') as f:
                f.write(ascii_img)

            frame_count += 1
            print(f"Processed: {filename} ({frame_count} frames)", end='\r')

main()