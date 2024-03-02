@echo off
SETLOCAL enabledelayedexpansion

rem �ꕔ�̃��C�u�����̃r���h�Ɏg��Visual Studio������bat��T��
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" (
    SET VSDEVCMD="%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
    echo !VSDEVCMD! ��������܂���
    echo Visual Studio Community 2022 �𗘗p���܂�
) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat" (
    SET VSDEVCMD="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
    echo !VSDEVCMD! ��������܂���
    echo Visual Studio Community 2017 �𗘗p���܂�
) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat" (
    SET VSDEVCMD="%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat"
    echo !VSDEVCMD! ��������܂���
    echo Visual Studio Enterprise 2022 �𗘗p���܂�
) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat" (
    SET VSDEVCMD="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat"
    echo !VSDEVCMD! ��������܂���
    echo Visual Studio Enterprise 2017 �𗘗p���܂�
) else (
    echo �C���X�g�[���ς݂�Visual Studio�������͂��̓�����VsDevCmd.bat��������܂���ł���
    echo Visual Studio�̃C���X�g�[������f�t�H���g����ύX���Ă���ꍇ�����l�����܂�
    echo VsDevCmd.bat �̃p�X����͂��Ă�������
    echo ��:
    echo "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat"
    echo "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
    echo "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat"
    echo "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
    SET /P VSDEVCMD="VsDevCmd.bat �̃p�X����͂��Ă�������->"
    if not exist "!VSDEVCMD!" (
        echo "!VSDEVCMD!"
        echo [91m���͂��ꂽ�p�X��VsDevCmd.bat��������܂���[37m
        goto ERROR_VSDEVCMD_NOT_FOUND
    )
)

rem Microsoft Windows SDK for Windows 7 and .NET Framework 4��T��
if exist "%ProgramFiles(x86)%\Microsoft SDKs\Windows\v7.1A\Include" (
    SET INCLUDE_DIR="%ProgramFiles(x86)%"\"Microsoft SDKs"\Windows\v7.1A\Include
) else if exist "%ProgramW6432%\Microsoft SDKs\Windows\v7.1\Include" (
    SET INCLUDE_DIR="%ProgramW6432%"\"Microsoft SDKs"\Windows\v7.1\Include
) else (
    goto ERROR_SDK_NOT_FOUND
)

rem ���C�u�����̃_�E�����[�h��zip�W�J
echo ���s����PowerShell�̉�ʂ��\������܂�
echo ��ʂɂ͐G�炸���̂܂܂ł��҂���������
powershell -ExecutionPolicy Unrestricted ./downloadlibs.ps1
if !ERRORLEVEL! equ 1 (
    goto ERROR_FAILED_TO_GET_LIBS
)

echo �r���h���K�v�Ȉꕔ�̃��C�u�������r���h���܂�

rem jpeglib���r���h
echo ===========================jpegsr9c�̃r���h�J�n===========================
cd ./jpegsr9c/jpeg-9c
call %VSDEVCMD%
SET Include=!Include!;!INCLUDE_DIR!
copy jconfig.vc jconfig.h
nmake /f makefile.vc clean all
cd ../../
echo ===========================jpegsr9c�̃r���h����===========================

rem nezplug++�̃r���h
echo ===========================nezplug++�̃r���h�J�n===========================
powershell -ExecutionPolicy Unrestricted ./makelibs.ps1
cd ./nezplug++/
lib /DEF:npnez.def /MACHINE:x86 /out:npnez.lib
cd ../
echo ===========================nezplug++�̃r���h����===========================

echo �r���h���K�v�Ȉꕔ�̃��C�u�����̃r���h���������܂���

rem ���C�u�����̔z�u
echo ���C�u�����̔z�u���J�n���܂�
powershell -ExecutionPolicy Unrestricted ./copylibs.ps1
echo ���C�u�����̔z�u���������܂���
echo �����L�[�������ƏI�����܂�
pause
goto :EOF

rem �G���[����
:ERROR_VSDEVCMD_NOT_FOUND
echo [91mERROR_VSDEVCMD_NOT_FOUND: VsDevCmd.bat��������܂���ł���
echo ����bat�ł� VisualStudio������ VsDevCmd.bat ���A�ꕔ�̃��C�u�����̃r���h�ɕK�{�ł�
echo ���̃G���[��VisualStudioCommunity���ăC���X�g�[�����铙�ŉ�������\��������܂�
echo �����L�[�������ƏI�����܂�[37m
pause
goto :EOF

:ERROR_FAILED_TO_GET_LIBS
echo [91mERROR_FAILED_TO_GET_LIBS: ���C�u�����̃_�E�����[�h�Ɏ��s���܂���
echo �ȉ��̃y�[�W����issue���N�[���Ă�������
echo https://github.com/ryotayama/hayaemon_windows/issues
echo �����L�[�������ƏI�����܂�[37m
pause
goto :EOF

:ERROR_SDK_NOT_FOUND
cd ../../
echo [91mERROR_SDK_NOT_FOUND: �K�v��SDK��������܂���ł���
echo Microsoft Windows SDK for Windows 7 and .NET Framework 4 ���C���X�g�[�����Ă�������
echo https://www.microsoft.com/en-us/download/details.aspx?id=8279
echo �����L�[�������ƏI�����܂�[37m
pause
goto :EOF

ENDLOCAL