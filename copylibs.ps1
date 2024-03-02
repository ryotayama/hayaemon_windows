function removeIfExists($dir) {
    if (Test-Path $dir) {
        Remove-Item $dir -Recurse -Force
    }
}

#LIBファイルを直下に、DLLファイルをdllフォルダにコピー
Copy-Item bass24/c/bass.lib ./ -Force
Copy-Item bass_aac24/c/bass_aac.lib ./ -Force
Copy-Item bassalac24/c/bassalac.lib ./ -Force
Copy-Item bass_ape24/c/bass_ape.lib ./ -Force
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
New-Item dll -ItemType "directory" -Force| Out-Null
Copy-Item bass24/bass.dll ./dll -Force
Copy-Item bass_aac24/bass_aac.dll ./dll -Force
Copy-Item bassalac24/bassalac.dll ./dll -Force
Copy-Item bass_ape24/bass_ape.dll ./dll -Force
Copy-Item Hayaemon276/Hayaemon276/BASS_DSHOW.dll ./dll -Force
Copy-Item bass_fx24/bass_fx.dll ./dll -Force
Copy-Item bassasio13/bassasio.dll ./dll -Force
Copy-Item basscd24/basscd.dll ./dll -Force
Copy-Item bassenc24/bassenc.dll ./dll -Force
Copy-Item bassflac24/bassflac.dll ./dll -Force
Copy-Item bassmix24/bassmix.dll ./dll -Force
Copy-Item basswasapi24/basswasapi.dll ./dll -Force
Copy-Item basswm24/basswma.dll ./dll -Force
Copy-Item tags18/tags.dll ./dll -Force
Copy-Item nezplug++/npnez.dll ./dll -Force
Copy-Item mp3infp/x86/mp3infp.dll ./dll -Force

#各展開ファイルをバックアップフォルダに移動して終了
removeIfExists ./.backup/bass24
removeIfExists ./.backup/bass_aac24
removeIfExists ./.backup/bassalac24
removeIfExists ./.backup/bass_ape24
removeIfExists ./.backup/Hayaemon276
removeIfExists ./.backup/bass_fx24
removeIfExists ./.backup/bassasio13
removeIfExists ./.backup/basscd24
removeIfExists ./.backup/bassenc24
removeIfExists ./.backup/bassflac24
removeIfExists ./.backup/bassmix24
removeIfExists ./.backup/basswasapi24
removeIfExists ./.backup/basswm24
removeIfExists ./.backup/tags18
removeIfExists ./.backup/nezplug++
removeIfExists ./.backup/jpegsr9c
removeIfExists ./.backup/7za920
removeIfExists ./.backup/mp3infp
Move-Item ./bass24 ./.backup/ -Force
Move-Item ./bass_aac24 ./.backup/ -Force
Move-Item ./bassalac24 ./.backup/ -Force
Move-Item ./bass_ape24 ./.backup/ -Force
Move-Item ./Hayaemon276 ./.backup/ -Force
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
