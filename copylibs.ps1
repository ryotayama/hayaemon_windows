#LIBファイルを直下に、DLLファイルをReleaseフォルダにコピー
Copy-Item bass24/c/bass.lib ./ -Force
Copy-Item bass_aac24/c/bass_aac.lib ./ -Force
Copy-Item bassalac24/c/bassalac.lib ./ -Force
Copy-Item bass_ape24/c/bass_ape.lib ./ -Force
Copy-Item BASS_DSHOW/C/xVideo.lib ./ -Force
Copy-Item bass_fx24/C/bass_fx.lib ./ -Force
Copy-Item bassasio13/c/bassasio.lib ./ -Force
Copy-Item basscd24/c/basscd.lib ./ -Force
Copy-Item bassenc24/c/bassenc.lib ./ -Force
Copy-Item bassflac24/c/bassflac.lib ./ -Force
Copy-Item bassmix24/c/bassmix.lib ./ -Force
Copy-Item basswasapi24/c/basswasapi.lib ./ -Force
Copy-Item basswm24/c/basswma.lib ./ -Force
Copy-Item tags18/c/tags.lib ./ -Force
Copy-Item nezplug++/npnez.lib ./ -Force
Copy-Item jpegsr9c/jpeg-9c/libjpeg.lib ./ -Force
New-Item Release -ItemType "directory" -Force| Out-Null
Copy-Item bass24/bass.dll ./Release -Force
Copy-Item bass_aac24/bass_aac.dll ./Release -Force
Copy-Item bassalac24/bassalac.dll ./Release -Force
Copy-Item bass_ape24/bass_ape.dll ./Release -Force
Copy-Item BASS_DSHOW/xVideo.dll ./Release -Force
Copy-Item bass_fx24/bass_fx.dll ./Release -Force
Copy-Item bassasio13/bassasio.dll ./Release -Force
Copy-Item basscd24/basscd.dll ./Release -Force
Copy-Item bassenc24/bassenc.dll ./Release -Force
Copy-Item bassflac24/bassflac.dll ./Release -Force
Copy-Item bassmix24/bassmix.dll ./Release -Force
Copy-Item basswasapi24/basswasapi.dll ./Release -Force
Copy-Item basswm24/basswma.dll ./Release -Force
Copy-Item tags18/tags.dll ./Release -Force
Copy-Item nezplug++/npnez.dll ./Release -Force
Copy-Item mp3infp/x86/mp3infp.dll ./Release -Force

#各展開ファイルをバックアップフォルダに移動して終了
Remove-Item ./.backup/bass24 -Recurse -Force
Remove-Item ./.backup/bass_aac24 -Recurse -Force
Remove-Item ./.backup/bassalac24 -Recurse -Force
Remove-Item ./.backup/bass_ape24 -Recurse -Force
Remove-Item ./.backup/BASS_DSHOW -Recurse -Force
Remove-Item ./.backup/bass_fx24 -Recurse -Force
Remove-Item ./.backup/bassasio13 -Recurse -Force
Remove-Item ./.backup/basscd24 -Recurse -Force
Remove-Item ./.backup/bassenc24 -Recurse -Force
Remove-Item ./.backup/bassflac24 -Recurse -Force
Remove-Item ./.backup/bassmix24 -Recurse -Force
Remove-Item ./.backup/basswasapi24 -Recurse -Force
Remove-Item ./.backup/basswm24 -Recurse -Force
Remove-Item ./.backup/tags18 -Recurse -Force
Remove-Item ./.backup/nezplug++ -Recurse -Force
Remove-Item ./.backup/jpegsr9c -Recurse -Force
Remove-Item ./.backup/7za920 -Recurse -Force
Remove-Item ./.backup/mp3infp -Recurse -Force
Move-Item ./bass24 ./.backup/ -Force
Move-Item ./bass_aac24 ./.backup/ -Force
Move-Item ./bassalac24 ./.backup/ -Force
Move-Item ./bass_ape24 ./.backup/ -Force
Move-Item ./BASS_DSHOW ./.backup/ -Force
Move-Item ./bass_fx24 ./.backup/ -Force
Move-Item ./bassasio13 ./.backup/ -Force
Move-Item ./basscd24 ./.backup/ -Force
Move-Item ./bassenc24 ./.backup/ -Force
Move-Item ./bassflac24 ./.backup/ -Force
Move-Item ./bassmix24 ./.backup/ -Force
Move-Item ./basswasapi24 ./.backup/ -Force
Move-Item ./basswm24 ./.backup/ -Force
Move-Item ./tags18 ./.backup/ -Force
Move-Item ./nezplug++ ./.backup/ -Force
Move-Item ./jpegsr9c ./.backup/ -Force
Move-Item ./7za920 ./.backup/ -Force
Move-Item ./mp3infp ./.backup/ -Force
