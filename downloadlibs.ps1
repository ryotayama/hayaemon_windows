echo @off
$ErrorActionPreference = "Stop"
#���s���ꂽ�f�B���N�g���Ƀt�@�C����ۑ����܂�
#PowerShell (ps1)�Ŏ��s���Ă�������
#�C���^�[�l�b�g�ɂȂ����Ă邩�m�F
$networkListManager = [Activator]::CreateInstance([Type]::GetTypeFromCLSID([Guid]"{DCB00C01-570F-4A9B-8D69-199FDBA5723B}"))
$connections = $networkListManager.GetNetworkConnections()
$connections = $connections | ForEach-Object {$_.isConnectedToInternet}
if ($connections -eq $TRUE) {
	Write-Host '�e�탉�C�u�����̃_�E�����[�h���J�n���܂�'
}
else {
	Write-Warning '�C���^�[�l�b�g�ڑ����m�F���Ă�������'
	exit 1
}
#�_�E�����[�h�J�n
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
try {
	Invoke-WebRequest -Uri http://us.un4seen.com/files/bass24.zip -OutFile bass24.zip
	Invoke-WebRequest -Uri http://uk.un4seen.com/files/z/2/bass_aac24.zip -OutFile bass_aac24.zip
	Invoke-WebRequest -Uri http://uk.un4seen.com/files/bassalac24.zip -OutFile bassalac24.zip
	Invoke-WebRequest -Uri http://uk.un4seen.com/files/z/2/bass_ape24.zip -OutFile bass_ape24.zip
	Invoke-WebRequest -Uri https://hayaemon.jp/Hayaemon276.zip -OutFile Hayaemon276.zip
	Invoke-WebRequest -Uri http://uk.un4seen.com/files/z/0/bass_fx24.zip -OutFile bass_fx24.zip
	Invoke-WebRequest -Uri http://uk.un4seen.com/files/bassasio13.zip -OutFile bassasio13.zip
	Invoke-WebRequest -Uri http://uk.un4seen.com/files/basscd24.zip -OutFile basscd24.zip
	Invoke-WebRequest -Uri http://uk.un4seen.com/files/bassenc24.zip -OutFile bassenc24.zip
	Invoke-WebRequest -Uri http://uk.un4seen.com/files/bassflac24.zip -OutFile bassflac24.zip
	Invoke-WebRequest -Uri http://uk.un4seen.com/files/bassmix24.zip -OutFile bassmix24.zip
	Invoke-WebRequest -Uri http://uk.un4seen.com/files/basswasapi24.zip -OutFile basswasapi24.zip
	Invoke-WebRequest -Uri http://uk.un4seen.com/files/basswm24.zip -OutFile basswm24.zip
	Invoke-WebRequest -Uri http://uk.un4seen.com/files/z/3/tags18.zip -OutFile tags18.zip
	Invoke-WebRequest -Uri http://offgao.net/program/nezplug++.zip -OutFile nezplug++.zip
	Invoke-WebRequest -Uri http://www.ijg.org/files/jpegsr9c.zip -OutFile jpegsr9c.zip
	Invoke-WebRequest -Uri http://iij.dl.osdn.jp/sevenzip/64455/7za920.zip -OutFile 7za920.zip
	Invoke-WebRequest -Uri https://github.com/k-takata/mp3infp/releases/download/mp3infp_u_2.55_beta3/mp3infpu_dll_255-beta3.7z -OutFile mp3infpu_dll_255-beta3.7z
}
catch {
	if ( ($error | ForEach-Object {$_.Exception.Status}) -eq "ConnectFailure" ) {
		Write-Warning $Error[0] |ForEach-Object {$_.Exception}
		$errorhost = $Error[0] |ForEach-Object {$_.TargetObject.RequestUri.Host}
		Write-Output $errorhost '�֐ڑ��ł��鎖���m�F���Ă�������'
	}
	elseif ( ($error | ForEach-Object {$_.Exception.Status}) -eq "ProtocolError" ) {
		Write-Warning $Error[0] |ForEach-Object {$_.Exception}
		$errorfile = $error | ForEach-Object {$_.TargetObject.Address.OriginalString}
		Write-Output $errorfile
		Write-Output '��������܂���ł���'
	}
	else {
		Write-Warning $Error[0] |ForEach-Object {$_.Exception}
	}
	exit 1
}
Write-Output '�e�탉�C�u�����̃_�E�����[�h���������܂���'
#�W�J�J�n
Write-Output '�e�탉�C�u������zip�𓀂��J�n���܂�'
try {
	Expand-Archive bass24.zip -Force
	Expand-Archive bass_aac24.zip -Force
	Expand-Archive bassalac24.zip -Force
	Expand-Archive bass_ape24.zip -Force
	Expand-Archive Hayaemon276.zip -Force
	Expand-Archive bass_fx24.zip -Force
	Expand-Archive bassasio13.zip -Force
	Expand-Archive basscd24.zip -Force
	Expand-Archive bassenc24.zip -Force
	Expand-Archive bassflac24.zip -Force
	Expand-Archive bassmix24.zip -Force
	Expand-Archive basswasapi24.zip -Force
	Expand-Archive basswm24.zip -Force
	Expand-Archive tags18.zip -Force
	Expand-Archive nezplug++.zip -Force
	Expand-Archive jpegsr9c.zip -Force
	Expand-Archive 7za920.zip -Force
}
catch {
	if( ($Error[0] |ForEach-Object {$_.CategoryInfo.Category}) -eq "InvalidOperation") {
		Write-Warning '�t�@�C������Ɏ��s���܂���'
		Write-Output '�t�@�C�����j�����Ă���\��������܂�'
	}
	elseif( ($Error[0] |ForEach-Object {$_.CategoryInfo.Category}) -eq "InvalidArgument") {
		Write-Warning '�t�@�C����������܂���'
		Write-Output '�폜���ꂽ�\��������܂�'
	}
	exit 1
}
Start-Process -FilePath ./7za920/7za.exe -ArgumentList "x mp3infpu_dll_255-beta3.7z -o./mp3infp" -Wait
#�A�[�J�C�u���o�b�N�A�b�v�t�H���_�Ɉړ����ďI��
New-Item .backup -ItemType "directory" -Force| Out-Null
Move-Item ./*.zip ./.backup/ -Force
Move-Item ./mp3infpu_dll_*.7z ./.backup/ -Force
Write-Output '�e�탉�C�u������zip�𓀂��������܂���'