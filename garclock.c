#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>


#ifdef _WIN32
    #include <windows.h>
#elif defined(__unix__)
    #include <sys/time.h>
#else
    #warning "Only written to support windows and unix-like systems."
#endif



const char ascii_zero[10][14]  = { "  00000000  ", \
                                   " 0000000000 ", \
                                   " 000    000 ", \
                                   " 00      00 ", \
                                   " 00      00 ", \
                                   " 00      00 ", \
                                   " 00      00 ", \
                                   " 000    000 ", \
                                   " 0000000000 ", \
                                   "  00000000  " };

const char ascii_one[10][14]   = { "    1111    ", \
                                   "  111111    ", \
                                   "    1111    ", \
                                   "    1111    ", \
                                   "    1111    ", \
                                   "    1111    ", \
                                   "    1111    ", \
                                   "    1111    ", \
                                   "  11111111  ", \
                                   " 1111111111 " };

const char ascii_two[10][14]   = { "   22222    ", \
                                   "   222222   ", \
                                   " 222    222 ", \
                                   " 222    222 ", \
                                   "       2222 ", \
                                   "     2222   ", \
                                   "    2222    ", \
                                   "   2222     ", \
                                   " 2222222222 ", \
                                   " 2222222222 " };

const char ascii_three[10][14] = { "  333333333 ", \
                                   " 3333333333 ", \
                                   "         33 ", \
                                   "        333 ", \
                                   "  333333333 ", \
                                   " 3333333333 ", \
                                   "         33 ", \
                                   "        333 ", \
                                   "  333333333 ", \
                                   " 3333333333 " };

const char ascii_four[10][14]  = { "     444444 ", \
                                   "    4444444 ", \
                                   "   444  444 ", \
                                   "  444   444 ", \
                                   " 444    444 ", \
                                   " 4444444444 ", \
                                   " 4444444444 ", \
                                   "        444 ", \
                                   "        444 ", \
                                   "        444 " };

const char ascii_five[10][14]  = { " 5555555555 ", \
                                   " 5555555555 ", \
                                   " 555        ", \
                                   " 555        ", \
                                   "  55555555  ", \
                                   "    5555555 ", \
                                   "        555 ", \
                                   " 555    555 ", \
                                   " 5555555555 ", \
                                   "  55555555  " };

const char ascii_six[10][14]   = { "  66666666  ", \
                                   " 6666666666 ", \
                                   " 666    666 ", \
                                   " 666        ", \
                                   " 666666666  ", \
                                   " 6666666666 ", \
                                   " 66      66 ", \
                                   " 66      66 ", \
                                   " 6666666666 ", \
                                   "  66666666  " };

const char ascii_seven[10][14] = { " 777777777  ", \
                                   " 7777777777 ", \
                                   "        777 ", \
                                   "        777 ", \
                                   "        777 ", \
                                   "       777  ", \
                                   "      777   ", \
                                   "      777   ", \
                                   "      777   ", \
                                   "      777   " };

const char ascii_eight[10][14] = { "  88888888  ", \
                                   " 8888888888 ", \
                                   " 88      88 ", \
                                   " 88      88 ", \
                                   "  88888888  ", \
                                   "  88888888  ", \
                                   " 88      88 ", \
                                   " 88      88 ", \
                                   " 8888888888 ", \
                                   "  88888888  " };

const char ascii_nine[10][14]  = { "  99999999  ", \
                                   " 9999999999 ", \
                                   " 99      99 ", \
                                   " 99      99 ", \
                                   " 9999999999 ", \
                                   "  999999999 ", \
                                   "        999 ", \
                                   " 999    999 ", \
                                   " 9999999999 ", \
                                   "  99999999  " };


const char ascii_colon[10][14]   = { "   ::::::   ", \
                                     "   ::::::   ", \
                                     "   ::::::   ", \
                                     "   ::::::   ", \
                                     "            ", \
                                     "            ", \
                                     "   ::::::   ", \
                                     "   ::::::   ", \
                                     "   ::::::   ", \
                                     "   ::::::   " };

const char ascii_slash[10][14]   = { "         ///", \
                                     "        /// ", \
                                     "       ///  ", \
                                     "      ///   ", \
                                     "     ///    ", \
                                     "    ///     ", \
                                     "   ///      ", \
                                     "  ///       ", \
                                     " ///        ", \
                                     "///         " };

const char ascii_period[10][14]  = { "            ", \
                                     "            ", \
                                     "            ", \
                                     "            ", \
                                     "            ", \
                                     "            ", \
                                     "            ", \
                                     "    ....    ", \
                                     "    ....    ", \
                                     "    ....    " };

const char ascii_space[10][14]   = { "            ", \
                                     "            ", \
                                     "            ", \
                                     "            ", \
                                     "            ", \
                                     "            ", \
                                     "            ", \
                                     "            ", \
                                     "            ", \
                                     "            " };



void reset_cursor(void);
void get_time_string(char *buffer, size_t buffer_size);
void get_date_string(char *buffer, size_t buffer_size);
void print_ascii_string(char *src_buffer,  size_t src_buffer_size);
void handle_signal(int sig);



int main(void)
{

    // Microshit wants us to explicitly enable ANSI functionality.
    #ifdef _WIN32

        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return 1;

        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) return 1;

        dwMode |= 0x0004;

        if (!SetConsoleMode(hOut, dwMode)) return 1;


        signal(SIGINT, handle_signal);

    #else

        struct sigaction sa;

        sa.sa_handler = handle_signal;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;

        // Register the signal handler using sigaction
        sigaction(SIGINT, &sa, NULL);

    #endif


    setvbuf(stdout, NULL, _IOFBF, 1024); // disable auto-flush on newline


    printf("\033[?25l"); // hide cursor


    while (1)
    {
        reset_cursor();

        char time_buffer[13] = {'\0'};
        get_time_string(time_buffer, 13);
        print_ascii_string(time_buffer, 12);

        char date_buffer[11] = {'\0'};
        get_date_string(date_buffer, 12);
        print_ascii_string(date_buffer, 10);

        fflush(stdout);
    }


    return 0;
}



inline void reset_cursor(void)
{
    printf("\033[H");
}



void get_time_string(char *buffer, size_t buffer_size)
{
    #ifdef _WIN32

        SYSTEMTIME st;
        GetLocalTime(&st);

        // Format hh:mm:ss.mmm
        snprintf(buffer, buffer_size, "%02d:%02d:%02d.%03d",
                 st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

    #else

        struct timeval tv;
        struct tm *tm_info;
        char time_string[16];

        gettimeofday(&tv, NULL);
        tm_info = localtime(&tv.tv_sec);
        strftime(time_string, sizeof(time_string), "%H:%M:%S", tm_info);
        snprintf(buffer, buffer_size, "%s.%03ld", time_string, tv.tv_usec / 1000);

    #endif
}



void get_date_string(char *buffer, size_t buffer_size)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    // Format date as dd/mm/yyyy
    strftime(buffer, buffer_size, "%d/%m/%Y", tm_info);
}



void print_ascii_string(char *src_buffer,  size_t src_buffer_size)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < src_buffer_size; j++)
        {
            switch (src_buffer[j])
            {
            case '0':
                printf("%s", ascii_zero[i]);
                break;
            case '1':
                printf("%s", ascii_one[i]);
                break;
            case '2':
                printf("%s", ascii_two[i]);
                break;
            case '3':
                printf("%s", ascii_three[i]);
                break;
            case '4':
                printf("%s", ascii_four[i]);
                break;
            case '5':
                printf("%s", ascii_five[i]);
                break;
            case '6':
                printf("%s", ascii_six[i]);
                break;
            case '7':
                printf("%s", ascii_seven[i]);
                break;
            case '8':
                printf("%s", ascii_eight[i]);
                break;
            case '9':
                printf("%s", ascii_nine[i]);
                break;
            case ':':
                printf("%s", ascii_colon[i]);
                break;
            case '/':
                printf("%s", ascii_slash[i]);
                break;
            case '.':
                printf("%s", ascii_period[i]);
                break;
            case ' ':
                printf("%s", ascii_space[i]);
                break;
            default:
                return;
            }
        }
        printf("\n");
    }
        printf("\n");
}



void handle_signal(int sig)
{
    reset_cursor();
    printf("\033[2J\033[?25h"); //  clear screen, enable cursor
    fflush(stdout);
    exit(0);
}