# bad_apple_in_c
Trying to run bad apple in c as a classic programming problem/excersise
First:
I extracted the frames from the video using:
ffmpeg -i badapple.mp4 -vf fps=30 frames/frame_%04d.png

Second:
I have made a simple python script which does this in order
1. Opened the image for processing while grayscaling it
2. Process the image to get ascii values
3. Print the ascii file to a txt file

You can refer to the python script in the repo for the same

Third:
I have use C as for the playback, you can see the source code file for how i did it.


If you want to test out this program, you need to first create the frames using ffmpeg as i did in the same place where all the other assets are, and then use the python script to generate the ascii art and when you have both the folder in the same directory as the c_player file, for ex you might have a folder "frames" from which you generated the ascii art in "ascii.txt" so you would run in terminal:
./c_player ascii_txt 30 6573
