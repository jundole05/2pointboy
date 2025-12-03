#pragma once
#include <Windows.h>
#include <string>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

class AudioManager
{
public:
    // 오디오 초기화
    static void init();
    
    // 배경음악 재생 (반복)
    static void playBackgroundMusic(const std::wstring& filename);
    
    // 게임 오버 음악 재생 (한 번만)
    static void playGameOverMusic(const std::wstring& filename);
    
    // 효과음 재생
    static void playSoundEffect(const std::wstring& filename);
    
    // 현재 재생 중인 음악 정지
    static void stopMusic();
    
    // 모든 오디오 정지 및 정리
    static void cleanup();
    
    // PlaySound API 사용 (더 간단하고 확실한 방법)
    static void playBackgroundMusicSimple(const std::wstring& filename);
    static void playGameOverMusicSimple(const std::wstring& filename);

private:
    static bool isInitialized;
    static std::wstring currentMusic;
};
