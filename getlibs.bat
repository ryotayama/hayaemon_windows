@echo off
SETLOCAL enabledelayedexpansion

rem ˆê•”‚Ìƒ‰ƒCƒuƒ‰ƒŠ‚Ìƒrƒ‹ƒh‚Ég‚¤Visual Studio“à•”‚Ìbat‚ğ’Tõ
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" (
    SET VSDEVCMD="%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
    echo !VSDEVCMD! ‚ªŒ©‚Â‚©‚è‚Ü‚µ‚½
    echo Visual Studio Community 2022 ‚ğ—˜—p‚µ‚Ü‚·
) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat" (
    SET VSDEVCMD="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
    echo !VSDEVCMD! ‚ªŒ©‚Â‚©‚è‚Ü‚µ‚½
    echo Visual Studio Community 2017 ‚ğ—˜—p‚µ‚Ü‚·
) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat" (
    SET VSDEVCMD="%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat"
    echo !VSDEVCMD! ‚ªŒ©‚Â‚©‚è‚Ü‚µ‚½
    echo Visual Studio Enterprise 2022 ‚ğ—˜—p‚µ‚Ü‚·
) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat" (
    SET VSDEVCMD="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat"
    echo !VSDEVCMD! ‚ªŒ©‚Â‚©‚è‚Ü‚µ‚½
    echo Visual Studio Enterprise 2017 ‚ğ—˜—p‚µ‚Ü‚·
) else (
    echo ƒCƒ“ƒXƒg[ƒ‹Ï‚İ‚ÌVisual Studio‚à‚µ‚­‚Í‚»‚Ì“à•”‚ÌVsDevCmd.bat‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½
    echo Visual Studio‚ÌƒCƒ“ƒXƒg[ƒ‹æ‚ğƒfƒtƒHƒ‹ƒg‚©‚ç•ÏX‚µ‚Ä‚¢‚éê‡“™‚ªl‚¦‚ç‚ê‚Ü‚·
    echo VsDevCmd.bat ‚ÌƒpƒX‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢
    echo —á:
    echo "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat"
    echo "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
    echo "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat"
    echo "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
    SET /P VSDEVCMD="VsDevCmd.bat ‚ÌƒpƒX‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢->"
    if not exist "!VSDEVCMD!" (
        echo "!VSDEVCMD!"
        echo [91m“ü—Í‚³‚ê‚½ƒpƒX‚ÉVsDevCmd.bat‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ[37m
        goto ERROR_VSDEVCMD_NOT_FOUND
    )
)

rem Microsoft Windows SDK for Windows 7 and .NET Framework 4‚ğ’Tõ
if exist "%ProgramFiles(x86)%\Microsoft SDKs\Windows\v7.1A\Include" (
    SET INCLUDE_DIR="%ProgramFiles(x86)%"\"Microsoft SDKs"\Windows\v7.1A\Include
) else if exist "%ProgramW6432%\Microsoft SDKs\Windows\v7.1\Include" (
    SET INCLUDE_DIR="%ProgramW6432%"\"Microsoft SDKs"\Windows\v7.1\Include
) else (
    goto ERROR_SDK_NOT_FOUND
)

rem ƒ‰ƒCƒuƒ‰ƒŠ‚Ìƒ_ƒEƒ“ƒ[ƒh‚Æzip“WŠJ
echo Às’†‚ÍPowerShell‚Ì‰æ–Ê‚ª•\¦‚³‚ê‚Ü‚·
echo ‰æ–Ê‚É‚ÍG‚ç‚¸‚»‚Ì‚Ü‚Ü‚Å‚¨‘Ò‚¿‚­‚¾‚³‚¢
powershell -ExecutionPolicy Unrestricted ./downloadlibs.ps1
if !ERRORLEVEL! equ 1 (
    goto ERROR_FAILED_TO_GET_LIBS
)

echo ƒrƒ‹ƒh‚ª•K—v‚Èˆê•”‚Ìƒ‰ƒCƒuƒ‰ƒŠ‚ğƒrƒ‹ƒh‚µ‚Ü‚·

rem jpeglib‚ğƒrƒ‹ƒh
echo ===========================jpegsr9c‚Ìƒrƒ‹ƒhŠJn===========================
cd ./jpegsr9c/jpeg-9c
call %VSDEVCMD%
SET Include=!Include!;!INCLUDE_DIR!
copy jconfig.vc jconfig.h
nmake /f makefile.vc clean all
cd ../../
echo ===========================jpegsr9c‚Ìƒrƒ‹ƒhŠ®—¹===========================

rem nezplug++‚Ìƒrƒ‹ƒh
echo ===========================nezplug++‚Ìƒrƒ‹ƒhŠJn===========================
powershell -ExecutionPolicy Unrestricted ./makelibs.ps1
cd ./nezplug++/
lib /DEF:npnez.def /MACHINE:x86 /out:npnez.lib
cd ../
echo ===========================nezplug++‚Ìƒrƒ‹ƒhŠ®—¹===========================

echo ƒrƒ‹ƒh‚ª•K—v‚Èˆê•”‚Ìƒ‰ƒCƒuƒ‰ƒŠ‚Ìƒrƒ‹ƒh‚ªŠ®—¹‚µ‚Ü‚µ‚½

rem ƒ‰ƒCƒuƒ‰ƒŠ‚Ì”z’u
echo ƒ‰ƒCƒuƒ‰ƒŠ‚Ì”z’u‚ğŠJn‚µ‚Ü‚·
powershell -ExecutionPolicy Unrestricted ./copylibs.ps1
echo ƒ‰ƒCƒuƒ‰ƒŠ‚Ì”z’u‚ªŠ®—¹‚µ‚Ü‚µ‚½
echo ‰½‚©ƒL[‚ğ‰Ÿ‚·‚ÆI—¹‚µ‚Ü‚·
pause
goto :EOF

rem ƒGƒ‰[ˆ—
:ERROR_VSDEVCMD_NOT_FOUND
echo [91mERROR_VSDEVCMD_NOT_FOUND: VsDevCmd.bat‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½
echo ‚±‚Ìbat‚Å‚Í VisualStudio“à•”‚Ì VsDevCmd.bat ‚ªAˆê•”‚Ìƒ‰ƒCƒuƒ‰ƒŠ‚Ìƒrƒ‹ƒh‚É•K{‚Å‚·
echo ‚±‚ÌƒGƒ‰[‚ÍVisualStudioCommunity‚ğÄƒCƒ“ƒXƒg[ƒ‹‚·‚é“™‚Å‰ğŒˆ‚·‚é‰Â”\«‚ª‚ ‚è‚Ü‚·
echo ‰½‚©ƒL[‚ğ‰Ÿ‚·‚ÆI—¹‚µ‚Ü‚·[37m
pause
goto :EOF

:ERROR_FAILED_TO_GET_LIBS
echo [91mERROR_FAILED_TO_GET_LIBS: ƒ‰ƒCƒuƒ‰ƒŠ‚Ìƒ_ƒEƒ“ƒ[ƒh‚É¸”s‚µ‚Ü‚µ‚½
echo ˆÈ‰º‚Ìƒy[ƒW‚©‚çissue‚ğ‹N•[‚µ‚Ä‚­‚¾‚³‚¢
echo https://github.com/ryotayama/hayaemon_windows/issues
echo ‰½‚©ƒL[‚ğ‰Ÿ‚·‚ÆI—¹‚µ‚Ü‚·[37m
pause
goto :EOF

:ERROR_SDK_NOT_FOUND
cd ../../
echo [91mERROR_SDK_NOT_FOUND: •K—v‚ÈSDK‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½
echo Microsoft Windows SDK for Windows 7 and .NET Framework 4 ‚ğƒCƒ“ƒXƒg[ƒ‹‚µ‚Ä‚­‚¾‚³‚¢
echo https://www.microsoft.com/en-us/download/details.aspx?id=8279
echo ‰½‚©ƒL[‚ğ‰Ÿ‚·‚ÆI—¹‚µ‚Ü‚·[37m
pause
goto :EOF

ENDLOCAL