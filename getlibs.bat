@echo off
SETLOCAL enabledelayedexpansion

rem 一部のライブラリのビルドに使うVisual Studio内部のbatを探索
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" (
    SET VSDEVCMD="%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
    echo !VSDEVCMD! が見つかりました
    echo Visual Studio Community 2022 を利用します
) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat" (
    SET VSDEVCMD="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
    echo !VSDEVCMD! が見つかりました
    echo Visual Studio Community 2017 を利用します
) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat" (
    SET VSDEVCMD="%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat"
    echo !VSDEVCMD! が見つかりました
    echo Visual Studio Enterprise 2022 を利用します
) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat" (
    SET VSDEVCMD="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat"
    echo !VSDEVCMD! が見つかりました
    echo Visual Studio Enterprise 2017 を利用します
) else (
    echo インストール済みのVisual Studioもしくはその内部のVsDevCmd.batが見つかりませんでした
    echo Visual Studioのインストール先をデフォルトから変更している場合等が考えられます
    echo VsDevCmd.bat のパスを入力してください
    echo 例:
    echo "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat"
    echo "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
    echo "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat"
    echo "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
    SET /P VSDEVCMD="VsDevCmd.bat のパスを入力してください->"
    if not exist "!VSDEVCMD!" (
        echo "!VSDEVCMD!"
        echo [91m入力されたパスにVsDevCmd.batが見つかりません[37m
        goto ERROR_VSDEVCMD_NOT_FOUND
    )
)

rem Microsoft Windows SDK for Windows 7 and .NET Framework 4を探索
if exist "%ProgramFiles(x86)%\Microsoft SDKs\Windows\v7.1A\Include" (
    SET INCLUDE_DIR="%ProgramFiles(x86)%"\"Microsoft SDKs"\Windows\v7.1A\Include
) else if exist "%ProgramW6432%\Microsoft SDKs\Windows\v7.1\Include" (
    SET INCLUDE_DIR="%ProgramW6432%"\"Microsoft SDKs"\Windows\v7.1\Include
) else (
    goto ERROR_SDK_NOT_FOUND
)

rem ライブラリのダウンロードとzip展開
echo 実行中はPowerShellの画面が表示されます
echo 画面には触らずそのままでお待ちください
powershell -ExecutionPolicy Unrestricted ./downloadlibs.ps1
if !ERRORLEVEL! equ 1 (
    goto ERROR_FAILED_TO_GET_LIBS
)

echo ビルドが必要な一部のライブラリをビルドします

rem jpeglibをビルド
echo ===========================jpegsr9cのビルド開始===========================
cd ./jpegsr9c/jpeg-9c
call %VSDEVCMD%
SET Include=!Include!;!INCLUDE_DIR!
copy jconfig.vc jconfig.h
nmake /f makefile.vc clean all
cd ../../
echo ===========================jpegsr9cのビルド完了===========================

rem nezplug++のビルド
echo ===========================nezplug++のビルド開始===========================
powershell -ExecutionPolicy Unrestricted ./makelibs.ps1
cd ./nezplug++/
lib /DEF:npnez.def /MACHINE:x86 /out:npnez.lib
cd ../
echo ===========================nezplug++のビルド完了===========================

echo ビルドが必要な一部のライブラリのビルドが完了しました

rem ライブラリの配置
echo ライブラリの配置を開始します
powershell -ExecutionPolicy Unrestricted ./copylibs.ps1
echo ライブラリの配置が完了しました
echo 何かキーを押すと終了します
pause
goto :EOF

rem エラー処理
:ERROR_VSDEVCMD_NOT_FOUND
echo [91mERROR_VSDEVCMD_NOT_FOUND: VsDevCmd.batが見つかりませんでした
echo このbatでは VisualStudio内部の VsDevCmd.bat が、一部のライブラリのビルドに必須です
echo このエラーはVisualStudioCommunityを再インストールする等で解決する可能性があります
echo 何かキーを押すと終了します[37m
pause
goto :EOF

:ERROR_FAILED_TO_GET_LIBS
echo [91mERROR_FAILED_TO_GET_LIBS: ライブラリのダウンロードに失敗しました
echo 以下のページからissueを起票してください
echo https://github.com/ryotayama/hayaemon_windows/issues
echo 何かキーを押すと終了します[37m
pause
goto :EOF

:ERROR_SDK_NOT_FOUND
cd ../../
echo [91mERROR_SDK_NOT_FOUND: 必要なSDKが見つかりませんでした
echo Microsoft Windows SDK for Windows 7 and .NET Framework 4 をインストールしてください
echo https://www.microsoft.com/en-us/download/details.aspx?id=8279
echo 何かキーを押すと終了します[37m
pause
goto :EOF

ENDLOCAL