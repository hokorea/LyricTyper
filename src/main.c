#include <stdio.h>
#include <windows.h>

void type_print(const char *text, int delay_ms);
void set_working_directory_to_exe_path();

int main(void){
    set_working_directory_to_exe_path();

    // 콘솔을 UTF-8로 설정 (한글 안깨지게)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    FILE *fp = fopen("../assets/lyrics.txt", "r");
    if (fp == NULL) {
        printf("lyrics.txt 파일을 열 수 없습니다.\n");
        printf("assets 폴더에 lyrics.txt를 만들어 주세요.\n");
        system("pause");
        return 1;
    }

    char line[1024];

    printf("=== LyricTyper ===\n\n");

    // 파일에서 한 줄씩 읽어서 출력
    while (fgets(line, sizeof(line), fp) != NULL) {
        type_print(line, 60);   // 글자 하나당 60ms
        Sleep(300);             // 한 줄과 다음 줄 사이 잠깐 쉬기
    }

    fclose(fp);

    printf("\n\n=== 끝! 프로그램을 종료하려면 아무 키나 누르세요. ===\n");
    system("pause"); // 윈도우에서 콘솔 바로 닫히지 않게

    return 0;
}

void type_print(const char *text, int delay_ms){
    for (int i = 0; text[i] != '\0'; i++) {

        // 줄 끝 개행 문자까지 같이 보여주고 싶으면 이대로 두고,
        // '\n'에서만 살짝 쉬고 싶으면 여기 분기 넣어도 됨.
        putchar(text[i]);
        fflush(stdout);     // 출력 버퍼 바로 비우기

        // 줄바꿈 문자는 그냥 빨리 넘기고 싶으면 이렇게도 가능:
        // if (text[i] == '\n' || text[i] == '\r') continue;

        Sleep(delay_ms);    // 글자 사이 딜레이(ms)
    }
}

void set_working_directory_to_exe_path() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    // exe 경로에서 파일명 제거 → 디렉토리만 남김
    char *slash = strrchr(path, '\\');
    if (slash) {
        *slash = '\0';
        SetCurrentDirectoryA(path);
    }
}