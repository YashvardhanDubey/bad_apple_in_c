#include <stdio.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
    void sleep_ms(int milliseconds) {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
    void sleep_ms(int milliseconds) {
        usleep(milliseconds * 1000);
    }
#endif

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[2J\033[H");
        fflush(stdout);
    #endif
}

void play_frame(const char* filepath);

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("Correct usage is %s <folder> <fps> <num_of_frames>\n", argv[0]);
        printf("Example: %s ascii_txt 30 6572\n", argv[0]);
        return 1;
    }

    const char* folder_name = argv[1];
    int fps = atoi(argv[2]);
    int frames = atoi(argv[3]);

    if (fps <= 0 || frames <= 0)
    {
        printf("Error: fps and number of frames cannot be negative or zero!");
        return 1;
    }

    int delay_ms = 1000/fps;
    printf("Playing %d frames from %s at %d fps\n", frames, argv[1], fps);
    printf("Press ctrl+c at any point to stop.\n");
    sleep_ms(1000);

    clock_t start_time = clock();

    for (int i = 1; i <= frames; i++)
    {
        clock_t frame_start = clock();

        char filepath[512];
        snprintf(filepath, sizeof(filepath), "%s/frame_%04d.txt", folder_name, i);
        
        clear_screen();             //Clears the scrren but only works on windows
        play_frame(filepath);

        clock_t frame_end = clock();
        int elapsed_ms = (int) (((double)(frame_end - frame_start)/CLOCKS_PER_SEC) * 1000);

        int sleep_time = delay_ms - elapsed_ms;     //sleeping for the remaining amount of time such that fps doesnt go haywire
        if (sleep_time > 0)
            sleep_ms(sleep_time);
    }

    clock_t end_time = clock();
    double total_seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\nPlayback Complete dawg!\n");
    printf("Total time taken: %.2f seconds\n", total_seconds);
    printf("Average FPS throughout: %.2f\n", frames / total_seconds);

    return 0;
}

void play_frame(const char* filepath)
{
    FILE* f = fopen(filepath, "r");
    if (!f)
    {
        printf("Couldn't open file.");
        return;
    }
    
    char buffer_line[256];
    while (fgets(buffer_line, sizeof(buffer_line), f))
        printf("%s", buffer_line);

    fclose(f);
    fflush(stdout);
}