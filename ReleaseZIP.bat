@echo off
if exist ".backup\7za920\7za.exe" (
	.backup\7za920\7za.exe a Hayaemon%1.zip readme.txt
	.backup\7za920\7za.exe a Hayaemon%1_XP.zip readme.txt

	rename readme.txt readme_jp.txt
	rename readme_en.txt readme.txt

	.backup\7za920\7za.exe a Hayaemon%1_en.zip readme.txt
	.backup\7za920\7za.exe a Hayaemon%1_XP_en.zip readme.txt

	rename readme.txt readme_en.txt
	rename readme_jp.txt readme.txt

	cd manual
	rename manual_jp manual
	..\.backup\7za920\7za.exe a ..\Hayaemon%1.zip manual
	..\.backup\7za920\7za.exe a ..\Hayaemon%1_XP.zip manual
	rename manual manual_jp

	rename manual_en manual
	..\.backup\7za920\7za.exe a ..\Hayaemon%1_en.zip manual
	..\.backup\7za920\7za.exe a ..\Hayaemon%1_XP_en.zip manual
	rename manual manual_en


	if exist "..\Release_jp" (
		cd ..\Release_jp
		..\.backup\7za920\7za.exe a ..\Hayaemon%1.zip Hayaemon.exe *.dll sound\
	) else (
		echo Release_jp Folder is Not Found.
	)


	if exist "..\Release_XP_jp" (
		cd ..\Release_XP_jp
		..\.backup\7za920\7za.exe a ..\Hayaemon%1_XP.zip Hayaemon.exe *.dll sound\
	) else (
		echo Release_XP_jp Folder is Not Found.
	)

	if exist "..\Release_en" (
		cd ..\Release_en
		..\.backup\7za920\7za.exe a ..\Hayaemon%1_en.zip Hayaemon.exe *.dll sound\
	) else (
		echo Release_en Folder is Not Found.
	)

	if exist "..\Release_XP_en" (
		cd ..\Release_XP_en
		..\.backup\7za920\7za.exe a ..\Hayaemon%1_XP_en.zip Hayaemon.exe *.dll sound\
	) else (
		echo Release_XP_en Folder is Not Found.
	)
	cd ..
		echo Releaseファイルのzipファイル化が完了しました
	mkdir zipfile_%1
	move Hayaemon*.zip zipfile_%1
	) else (
		echo 7z.exe file is Not Found.
)
echo 何かキーを押すと終了します
pause
