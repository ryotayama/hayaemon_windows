@echo off
if exist ".backup\7za920\7za.exe" (
	cd readme\jp
	..\..\.backup\7za920\7za.exe a ..\..\Hayaemon%1.zip readme.txt
	cd ..\..\
	
	cd readme\en
	..\..\.backup\7za920\7za.exe a ..\..\Hayaemon%1_en.zip readme.txt
	cd ..\..\

	cd manual\jp
	..\..\.backup\7za920\7za.exe a ..\..\Hayaemon%1.zip manual\
	cd ..\..\
	
	cd manual\en
	..\..\.backup\7za920\7za.exe a ..\..\Hayaemon%1_en.zip manual\
	cd ..\..\

	if exist "Release_jp" (
		cd Release_jp
		..\.backup\7za920\7za.exe a ..\Hayaemon%1.zip Hayaemon.exe *.dll sound\
		cd ..
	) else (
		echo Release_jp Folder is Not Found.
	)

	if exist "Release_en" (
		cd Release_en
		..\.backup\7za920\7za.exe a ..\Hayaemon%1_en.zip Hayaemon.exe *.dll sound\
		cd ..
	) else (
		echo Release_en Folder is Not Found.
	)

	echo Releaseファイルのzipファイル化が完了しました
	mkdir zipfile_%1
	move Hayaemon*.zip zipfile_%1
) else (
	echo 7z.exe file is Not Found.
)
echo 何かキーを押すと終了します
pause
