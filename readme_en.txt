------------------------------------------------------------------------------
 Hayaemon Version 2.77 beta 7
------------------------------------------------------------------------------
                                                        Last update: 2020/7/27
                                      Ryota Yamauchi <ryota.yamauch@gmail.com>
                                 Hayaemon Official Website:http://hayaemon.jp/
------------------------------------------------------------------------------
 After reading all of the following, please use this software.
------------------------------------------------------------------------------

 Thank you for downloading Hayaemon.

 Hayaemon is a freeware audio player that can change the song's speed,
 frequency, and pitch at your will.

 This software supports the most popular audio files formats as WAV, CDA, MP3,
 MP2, MP1, OGG, AIFF, AIF, APE, FLAC, M4A, MP4, AAC, etc.

 Feature requests and Bug reports are welcome. Please post on wiki.

------------------------------------------------------------------------------
 Disclaimer
------------------------------------------------------------------------------

 This software is Irresponsibility, no warranty. Only if you agree to the
 following conditions, you can use this software.

　・Respect of damages caused by this software, the author do not accept any
    responsibility.
　・Author does not undertake any obligation in any manner whatsoever for any
    support (such as bug fix, version up) of this software.

 If you do not agree to these terms, please delete this software.

------------------------------------------------------------------------------
 Requirement
------------------------------------------------------------------------------

 Supports the OS since Windows XP. Reported to work are welcome.
 DirectX 3 or later is required.

------------------------------------------------------------------------------
 Development Environment
------------------------------------------------------------------------------

 Windows 10 / Visual Studio Community 2017, Windows SDK.

 Hayaemon's sound engine is using the high performance audio library "BASS.DLL".
 Mr. Ian Luck that has provided useful libraries, thank you deeply.

	Un4seen Developments : http://www.un4seen.com/

------------------------------------------------------------------------------
 Installation
------------------------------------------------------------------------------

 There is no installer, so extract on any directory.

 To uninstall this software, delete all files you downloaded. This software
 don't write to the registry.
------------------------------------------------------------------------------
 Manual
------------------------------------------------------------------------------

 See index.html in "manual" directory.

------------------------------------------------------------------------------
 History
------------------------------------------------------------------------------

2020/7/27
 Fixed a case where the behavior is strange when using the menu that returns
 the specified number of seconds at the beginning of the song.

2020/7/25
 Unified the format of the function to copy current position to clipboard to
 the "hh:mm:ss" format.

2020/7/23
 Added "Rewind n sec. and play/pause" short cut menu.

2020/2/8
 Fixed that one song loop was not working.

2018/7/4 Version 2.77 beta 3
 Fixed that there was a case that the sound did not come out competing with
 ASIO even when ASIO was not selected.

2018/7/3 Version 2.77 beta 2
 Fixed an error message has been shown "d3dx9_43.dll is not found" when booting.

2018/6/27 Version 2.77 beta 1
 Updated external libraries to latest version.

2018/6/12 Version 2.76 stable
 Stable version is released.

2018/6/4 Version 2.75 beta 6
 Changed the normal icon from the cherry blossom icon.

2018/5/14 Version 2.75 beta 5
 Changed the icon to the cherry blossom icon.

2017/8/30 Version 2.75 beta 4
 Fixed not booting in Windows XP environment.

2017/8/23 Version 2.75 beta 3
 Changed the development environment from Visual C ++ 2010 Express to
 Visual Studio Community 2017.
 @12guitar21 and Sakaguchi reflected the icon designed
 by @UmeboshiKantaro for iOS.

2013/5/27 Version 2.75 beta 2
 Japanese version only updated.

2013/5/20 Version 2.75 beta 1
 Added the "Same Artist" menu as "Play" menu.

2013/5/19 Version 2.74 stable
 Stable version is released.

2013/5/15 Version 2.73 beta 18
 Bug-fix: there was the case that the playlist has not restored when rebooting
 after application exit.

2013/5/6 Version 2.73 beta 17
 Bug-fix: there was the case that the behavior is strange when reading the NSF
 file.

2013/5/5 Version 2.73 beta 16
 Supports NSF format files.

2013/4/29 Version 2.73 beta 15
 Improved the boot time.

2013/4/28 Version 2.73 beta 14
 Bug-fix: could not enter the space key when using tweet screen.

2013/4/28 Version 2.73 beta 13
 Bug-fix: when you associate files to Hayaemon, automatic playback had not
 worked well.

2013/4/22 Version 2.73 beta 12
 Fixed a memory leak had caused.

2013/4/22 Version 2.73 beta 11
 Improve the speed of showing the lyrics.

2013/4/22 Version 2.73 beta 10
 Improved the speed of the pitch analyzer.

2013/4/21 Version 2.73 beta 9
 Fixed that pitch analyzer process also works when video screen is not
 visible, and processing had become heavy.

2013/4/6 Version 2.73 beta 8
 Fixed to be able to set volume by clicking the right-click menu.

2013/4/5 Version 2.73 beta 7
 Fixed to be able to reset volume by clicking the right-click menu.

2013/4/4 Version 2.73 beta 6
 Added the "Set Volume" menu as "Effect" menu.

2013/4/3 Version 2.73 beta 5
 Added the "Reset Volume" menu as "Effect" menu.

2013/4/2 Version 2.73 beta 4
 Added the "WASAPI" menu as "Quality" menu.

2013/4/1 Version 2.73 beta 3
 Added the "Normal" and "ASIO" menu as "Quality" menu.

2013/3/31 Version 2.73 beta 2
 Added the "Add URL" menu to the "File" menu.

2013/3/30 Version 2.73 beta 1
 Added the "Open URL" menu to the "File" menu.

2013/3/29 Version 2.72 stable
 Stable version is released.

2013/3/28 Version 2.71 beta 29
 Fixed to be able to switch "Lyrics" "Pitch Analyser" by clicking the
 right-click menu on the Video Screen.

2013/3/27 Version 2.71 beta 28
 Fixed to be able to restore the contents of the video screen to previous
 setting.

2013/3/26 Version 2.71 beta 27
 Added "Pitch Analyser".

2013/3/25 Version 2.71 beta 26
 Bug-Fix: There was the case that the play list view was strange.

2013/3/24 Version 2.71 beta 25
 Supports the display of the background image ( JPEG ) using the "bgfolder"
 tag of LRC files.

2013/3/23 Version 2.71 beta 24
 Bug-Fix: There was the case that the selection status of "Transcribe bass"
 was strange.

2013/3/22 Version 2.71 beta 23
 Added the "Decimal digit" menu as right-click menu of pitch control.

2013/3/21 Version 2.71 beta 22
 Added the "Flat" "Sharp" etc menu as right-click menu of pitch control, and
 now we can change song pitch more easily.

2013/3/20 Version 2.71 beta 21
 Added the "Set Pitch" menu as right-click menu of pitch control, and now we
 can change song pitch more easily.

2013/3/19 Version 2.71 beta 20
 Fixed that the all EQ had not restored.

2013/3/18 Version 2.71 beta 19
 Fixed that was no longer able to save the AB loop range.

2013/3/17 Version 2.71 beta 18
 Added the "Decimal digit" menu as right-click menu of frequency control.

2013/3/16 Version 2.71 beta 17
 Added the "Increase", "Decrease" menu as right-click menu of frequency
 control.

2013/3/15 Version 2.71 beta 16
 Added the "Turn down X%", "Turn up X%" menu as right-click menu of frequency
 control, and now we can change song frequency more easily.

2013/3/14 Version 2.71 beta 15
 Added the "Set Frequency" menu as right-click menu of frequency control,
 and now we can change song frequency more easily.

2013/3/13 Version 2.71 beta 14
 Added the "Decimal digit" menu as right-click menu of speed control.

2013/3/12 Version 2.71 beta 13
 Added the "Increase", "Decrease" menu as right-click menu of speed control.

2013/3/11 Version 2.71 beta 12
 Added the "Turn down X%", "Turn up X%" menu as right-click menu of speed
 control, and now we can change song speed more easily.

2013/3/10 Version 2.71 beta 11
 Added the "Set Speed" menu as right-click menu of speed control, and now we
can change song speed more easily.

2013/3/9 Version 2.71 beta 10
 Fixed to be able to restore the state of the marker play to the previous
 setting.

2013/3/8 Version 2.71 beta 9
 Fixed not to show the video screen when booting first time.

2013/3/7 Version 2.71 beta 8
 Added "Update Check" menu.

2013/3/6 Version 2.71 beta 7
 Improve the speed of showing the tags of the playlist.

2013/3/5 Version 2.71 beta 6
 Improve the speed of showing the lyrics.

2013/3/4 Version 2.71 beta 5
 Improve the speed of updating the playback time.

2013/3/3 Version 2.71 beta 4
 Bug-Fix: there was the case that a strange value set to the Setting.ini.

2013/3/2 Version 2.71 beta 3
 Bug-Fix: There was the case that the restoring of the playlist did not work
 well.

2013/3/1 Version 2.71 beta 2
 Improve exit time.

2013/2/28 Version 2.71 beta 1
 Improve boot time.

2013/2/27 Version 2.70 stable
 Stable version is released.

2013/2/26 Version 2.69 beta 15
 Bug-Fix: There was the case that the restoring of EQ did not work well.

2013/2/25 Version 2.69 beta 14
 Bug-Fix: There was the case that the restoring of speed, frequency, pitch did
 not work well.

2013/2/24 Version 2.69 beta 13
 Fixed to be able to edit "Year" tag by selecting right-click menu of the
playlist.

2013/2/23 Version 2.69 beta 12
 Fixed to be able to edit "Artist" tag by selecting right-click menu of the
playlist.

2013/2/22 Version 2.69 beta 11
 Fixed to be able to edit "Title" tag by selecting right-click menu of the
playlist.

2013/2/21 Version 2.69 beta 10
 Bug-Fix: couldn't update the tags of the playing song.

2013/2/20 Version 2.69 beta 9
 Fixed to be able to open ".m4b" extension files.

2013/2/19 Version 2.69 beta 8
 Bug-Fix: couldn't use space key while editing the tags.

2013/2/18 Version 2.69 beta 7
 Fixed that there was the case to end abnormally when deleting the tab.

2013/2/17 Version 2.69 beta 6
 Fixed to move where you want to edit by pressing the cursor key while editing
 the tags.

2013/2/16 Version 2.69 beta 5
 Fixed to be able to cancel the editing of the tag by pressing the Esc key
 while editing the tags.

2013/2/15 Version 2.69 beta 4
 By using the mp3infp.dll, writing tag information is available.

2013/2/14 Version 2.69 beta 3
 By using the mp3infp.dll, reading tag information is now faster.

2013/2/13 Version 2.69 beta 2
 Improve boot time.

2013/2/12 Version 2.69 beta 1
 By the video screen drag and drop, you can resize the video screen size.

2013/2/11 Version 2.68 stable
 Stable version is released.

2013/2/10 Version 2.67 beta 24
 Added a customize menu of distortion. Now, we can change the distortion
 freely by adjusting each parameter.

2013/2/9 Version 2.67 beta 23
 Added a customize menu of gargle. Now, we can change the gargle freely by
 adjusting each parameter.

2013/2/8 Version 2.67 beta 22
 Added a customize menu of flanger. Now, we can change the flanger freely by
 adjusting each parameter.

2013/2/7 Version 2.67 beta 21
 Added a customize menu of compressor. Now, we can change the compressor
 freely by adjusting each parameter.

2013/2/6 Version 2.67 beta 20
 Fixed to be able to reset pitch by clicking the right-click menu.

2013/2/5 Version 2.67 beta 19
 Fixed that the sound had been played at the application exit.

2013/2/4 Version 2.67 beta 18
 Fixed to be able to reset frequency by clicking the right-click menu.

2013/2/3 Version 2.67 beta 17
 Fixed to be able to reset speed by clicking the right-click menu.

2013/2/2 Version 2.67 beta 16
 Fixed to be able to hide the EQ control by clicking the right-click menu.

2013/2/1 Version 2.67 beta 15
 Fixed to be able to hide the pan control by clicking the right-click menu.

2013/1/31 Version 2.67 beta 14
 Fixed to be able to hide the volume control by clicking the right-click menu.

2013/1/30 Version 2.67 beta 13
 Fixed to be able to hide the pitch control by clicking the right-click menu.

2013/1/29 Version 2.67 beta 12
 Fixed to be able to hide the frequency control by clicking the right-click
 menu.

2013/1/28 Version 2.67 beta 11
 Fixed to be able to hide the speed control by clicking the right-click menu.

2013/1/27 Version 2.67 beta 10
 Fixed to be able to hide the tab by clicking the right-click menu.

2013/1/26 Version 2.67 beta 9
 Fixed to be able to hide the position slider by clicking the right-click menu.

2013/1/25 Version 2.67 beta 8
 Fixed to be able to hide the explorer by clicking the right-click menu.

2013/1/24 Version 2.67 beta 7
 Fixed to be able to hide the play list by clicking the right-click menu.

2013/1/23 Version 2.67 beta 6
 Fixed to be able to hide the video screen by clicking the right-click menu.

2013/1/22 Version 2.67 beta 5
 Added a customize menu of chorus. Now, we can change the chorus freely by
 adjusting each parameter.

2013/1/21 Version 2.67 beta 4
 Fixed to speed up the response at the application exit.

2013/1/20 Version 2.67 beta 3
 Added a customize menu of delay. Now, we can change the delay freely by
 adjusting each parameter.

2013/1/19 Version 2.67 beta 2
 Added a customize menu of 3D reverb. Now, we can change the 3D reverb freely
 by adjusting each parameter.

2013/1/18 Version 2.67 beta 1
 Added a customize menu of reverb. Now, we can change the reverb freely by
 adjusting each parameter.

2013/1/17 Version 2.66 stable
 Stable version is released.

2013/1/16 Version 2.65 beta 24
 Fixed that the behavior had been strange if you set reverse mode when using
AB loop.

2013/1/15 Version 2.65 beta 23
 Fixed to be able to specify the command-line options when exporting MP3 by
using LAME.

2013/1/14 Version 2.65 beta 22
 Added the function that can search the song's lyrics on Lyrics Master by
 selecting right-click menu of the playlist.

2013/1/13 Version 2.65 beta 21
 Fixed that when setting the maximum / minimum value, the value has become
strange.

2013/1/12 Version 2.65 beta 20
 Added "Set Pitch" menu, so you can set pitch more easily.

2013/1/11 Version 2.65 beta 19
 Added "Set Frequency" menu, so you can set frequency more easily.

2013/1/10 Version 2.65 beta 18
 Added "Set Speed" menu, so you can set speed more easily.

2013/1/9 Version 2.65 beta 17
 Fixed to display only readable files in the playlist.

2013/1/8 Version 2.65 beta 16
 Fixed the both ends of the video screen had ended up in gray.

2013/1/7 Version 2.65 beta 15
 Fixed that the display size of the video had been funny.

2013/1/6 Version 2.65 beta 14
 Supports FLV format files. (Required ffdshow and FLV Splitter)

2013/1/5 Version 2.65 beta 13
 Fixed to display only readable files in the Explorer pane.

2013/1/4 Version 2.65 beta 12
 Fixed that the sound effects had not been turned off when the "Reset all"
 menu selected.

2013/1/3 Version 2.65 beta 11
 Fixed that when the "No Sense" menu selected, some of the effects had not
 been turned off.

2013/1/2 Version 2.65 beta 10
 Fixed to be able to set play position 0.001 sec by clicking "Play position"
menu.

2013/1/1 Version 2.65 beta 9
 Fixed to be able to restore the state of the AB loop to the previous setting.

2012/12/31 Version 2.65 beta 8
 As one of sound effects, added the "Wave" menu.

2012/12/31 Version 2.65 beta 7
 As one of sound effects, added the "Record Noise" menu.

2012/12/30 Version 2.65 beta 6
 Added "AB Loop(A) Pos Setting", "AB Loop(B) Pos Setting" menu.

2012/12/30 Version 2.65 beta 5
 Added "Set AB Loop(A) To Current Position", "Set AB Loop(B) To Current
Position" menu.

2012/12/30 Version 2.65 beta 4
 Fixed that all buttons had not been reset when you reset the toolbar.

2012/12/30 Version 2.65 beta 3
 Fixed to be able to select between 1-10 seconds, the fade-out time at the
 time of stopping of the song.

2012/12/29 Version 2.65 beta 2
 Fixed to be able to select between 1-10 seconds, the fade-out time at the
 time of switching of the song.

2012/12/28 Version 2.65 beta 1
 Added "Play Range" menu.

2012/12/27 Version 2.64 stable
 Stable version is released.

2012/12/26 Version 2.63 beta 16
 Added "High Cut(ultra-strong)" menu.

2012/12/26 Version 2.63 beta 15
 Added "Middle Cut(ultra-strong)" menu.

2012/12/25 Version 2.63 beta 14
 Fixed that the All Loop had not work normally.

2012/12/25 Version 2.63 beta 13
 Added "Low Cut(ultra-strong)" menu.

2012/12/25 Version 2.63 beta 12
 Added "Transcribe Drums (Hi-Hat, Cymbals)" menu.

2012/12/24 Version 2.63 beta 11
 Added "Boost high(ultra-strong)" menu.

2012/12/24 Version 2.63 beta 10
 Added "Boost middle(ultra-strong)" menu.

2012/12/24 Version 2.63 beta 9
 Improved the quality of the "Transcribe bass", you can transcribe bass more
easy.

2012/12/24 Version 2.63 beta 8
 Added "Boost low(ultra-strong)" menu.

2012/12/24 Version 2.63 beta 7
 Changed the EQ adjustment range from "-15 - 15" to "-30 - 30".

2012/12/23 Version 2.63 beta 6
 Added "Up 1 Octave", "Down 1 Octave" menu.

2012/12/23 Version 2.63 beta 5
 Added the function to Tweet on Twitter.

2012/12/23 Version 2.63 beta 4
 Fixed that have not exit normally.

2012/12/19 Version 2.63 beta 3
 When selecting "Transcribe bass", fixed to show check mark in the menu.

2012/12/18 Version 2.63 beta 2
 Fixed that during random play the last song has played repeatedly when all
song is finished.

2012/12/17 Version 2.63 beta 1
 Fixed that the random play has stopped when unreadable file is exist.

2012/12/16 Version 2.62 stable
 Stable version is released.

2012/12/15 Version 2.61 beta 20
 Fixed that vocal cancel function has been working when selected "normalize"
menu.

2012/12/14 Version 2.61 beta 19
 Added resume function.
 Fixed that had gone back to the first track of the playlist when you stopped
 playback.

2012/12/13 Version 2.61 beta 18
 Fixed that you could not adjust the explorer width when tab is hidden.

2012/12/12 Version 2.61 beta 17
 Supports ALAC format files.

2012/12/11 Version 2.61 beta 16
 Added the function that can search the song's artist by iTunes Store by
 selecting right-click menu of the playlist.

2012/12/10 Version 2.61 beta 15
 Added the function that can search the song's lyrics by internet by selecting
 right-click menu of the playlist.

2012/12/9 Version 2.61 beta 14
 Fixed that the noise sound had occurred when changing the song.

2012/12/8 Version 2.61 beta 13
 Fixed that when switching visible state of explorer, the control position
 might had been wrong.

2012/12/7 Version 2.61 beta 12
 Added the function that can search the song's artist by amazon by selecting
 right-click menu of the playlist.

2012/12/6 Version 2.61 beta 11
 Fixed to be able to add files by selecting right-click menu of the explorer.

2012/12/5 Version 2.61 beta 10
 Fixed to be able to open files by selecting right-click menu of the explorer.

2012/12/4 Version 2.61 beta 9
 Fixed to be able to open the folder that the file exists by selecting
 right-click menu of the explorer.

2012/12/3 Version 2.61 beta 8
 Fixed to be able to show the file properties by selecting right-click menu of
 the explorer.

2012/12/2 Version 2.61 beta 7
 Fixed to be able to open the folder that the audio file exists by selecting
 right-click menu of the playlist.

2012/12/1 Version 2.61 beta 6
 Fixed that can switch explorer visibility by clicking toolbar button.

2012/11/29 Version 2.61 beta 5
 Fixed to be able to show the file properties by selecting right-click menu of
 the playlist.

2012/11/29 Version 2.61 beta 4
 Fixed that when switching visible state of the control, the window size might
 had been wrong.

2012/11/28 Version 2.61 beta 3
 Fixed there was an extra space at the top of the list when hiding tab.

2012/11/26 Version 2.61 beta 2
 Added Explorer function. Now, we can open songs easily by using Explorer
 control.

2012/11/21 Version 2.61 beta 1
 Fixed to be able to  hide the tab.

2012/11/21 Version 2.60 stable
 Stable version is released.

2012/11/19 Version 2.59 beta 12
 Added effect preset function. Now, you can call instantly favorite effects.

2012/11/19 Version 2.59 beta 11
 Bug fix. Hayemon has might not boot depending on the environment.

2012/11/11 Version 2.59 beta 10
 Bug fix. Settings file had not been read normally depending on the
 environment difference.

2012/11/10 Version 2.59 beta 9
 Added the "read / write a settings" function

2012/11/10 Version 2.59 beta 8
 Revived the reverb of Version 2.46.

2012/11/10 Version 2.59 beta 7
 Added "Close all" menu to the View menu.

2012/11/9 Version 2.59 beta 6
 Added "High Cut" menu to the Effect menu.

2012/11/9 Version 2.59 beta 5
 Added "Middle Cut" menu to the Effect menu.

2012/11/9 Version 2.59 beta 4
 Added "Low Cut" menu to the Effect menu.

2012/11/8 Version 2.59 beta 3
 Added "Ear Training" menu to the Effect menu.

2012/11/7 Version 2.59 beta 2
 Bug fix. Some of the graphic equalizer was not been restored.

2012/11/6 Version 2.59 beta 1
 "_h001" in the filename was not to be added, when using "Save all" menu.

2012/11/4 Version 2.58 stable
 Stable version is released.

2012/11/4 Version 2.57 beta 16
 Bug fix. The playlist control had become larger when switching each controls
 visibility.

2012/11/4 Version 2.57 beta 15
 Bug fix. Song name had not been reflected in the window title when opening a
 previous file on random play mode.

2012/11/3 Version 2.57 beta 14
 Bug fix. The video screen might have become gradually larger still when
 switching the playlist visibility.

2012/10/31 Version 2.57 beta 13
 Bug fix. The video screen had become gradually larger every time switching
 the playlist visibility.

2012/10/30 Version 2.57 beta 12
 Bug fix. Number of decimal places of the playback speed control remains of
 two digits.

2012/10/30 Version 2.57 beta 11
 Bug fix. Song name had not been reflected in the window title when opening a
 previous file.

2012/10/29 Version 2.57 beta 10
 Supports to switch visibility of all controls independently.

2012/10/28 Version 2.57 beta 9
 Reduced the size of the executable file with optimizing the source code.

2012/10/28 Version 2.57 beta 8
 Supports resizing the window smaller depending on toolbar buttons count.

2012/10/27 Version 2.57 beta 7
 Supports switching each equalizer controls visibility.

2012/10/16 Version 2.57 beta 6
 Supports the 31-band graphic equalizer.

2012/10/8 Version 2.57 beta 5
 Fix that the window size had been become strange when switching the controls
 visible state.

2012/10/6 Version 2.57 beta 4
 Fixed that the window had not been activated after using "Play position"
 menu.

2012/10/4 Version 2.57 beta 3
 Added "No sense" menu.

2012/10/4 Version 2.57 beta 2
 Added "Medium" menu for the Toolbar size.

2012/10/2 Version 2.57 beta 1
 Fixed to be able to change the size of the toolbar buttons.

2012/9/20 Version 2.56 stable
 Stable version is released.

2012/9/18 Version 2.55 beta 5
 Added "Low battery" menu to the Effect menu.

2012/9/18 Version 2.55 beta 4
 Bug fix. behavior of "Reset speed" or "Reset frequency" menu was strange.

2012/9/17 Version 2.55 beta 3
 Bug fix. There was the case that "increase speed 5%" or "10%" menu did not
 work.

2012/9/14 Version 2.55 beta 2
 Added "Transcribe bass" menu to the Effect menu.

2012/9/12 Version 2.55 beta 1
 Added "Reset all" menu to the Effect menu.

2012/9/11 Version 2.54 stable
 Stable version is released.

2012/9/9 Version 2.53 beta 12
 Added "Play" to the right-click menu in the playlist.

2012/9/9 Version 2.53 beta 11
 Added "FullScreen" to the right-click menu in the video screen.

2012/9/9 Version 2.53 beta 10
 Added "Rename" to the right-click menu in the playlist tab.

2012/9/9 Version 2.53 beta 9
 Fixed that behavior of using the mouse wheel was strange still.

2012/9/9 Version 2.53 beta 8
 Fixed that the graphic equalizer did not function since beta 2.

2012/9/8 Version 2.53 beta 7
 Fixed that behavior of using the mouse wheel was strange.

2012/9/5 Version 2.53 beta 6
 Fixed that the settings of pitch / frequency / playback speed might not work
 well.

2012/9/4 Version 2.53 beta 5
 Added "selecting the decimal point of pitch" function.

2012/9/2 Version 2.53 beta 4
 Added "selecting the decimal point of frequency" function.

2012/9/2 Version 2.53 beta 3
 Added "selecting the decimal point of speed" function.

2012/8/26 Version 2.53 beta 2
 Unify the source along with the English and Japanese versions, Overhaul the
code, and reduced the size of the executable file.

2012/8/24 Version 2.53 beta 1
 Reduced the size of the executable file with optimizing the source code.

2012/8/24 Version 2.52 stable
 Stable version is released.

2012/8/24 Version 2.51 beta 12
 Added "Minimize to system tray" function.

2012/8/23 Version 2.51 beta 11
 Fixed a memory leak had caused.

2012/8/23 Version 2.51 beta 10
 Added "Gargle" effect.

2012/8/23 Version 2.51 beta 9
 Added "Flanger" effect.

2012/8/22 Version 2.51 beta 8
 Added "Compressor" effect.

2012/8/22 Version 2.51 beta 7
 Added "Chorus" effect.

2012/8/21 Version 2.51 beta 6
 Added "Distortion" effect.

2012/8/19 Version 2.51 beta 5
 Summarized as the effect menu, to organize the system menu of effects.

2012/8/19 Version 2.51 beta 4
 Change japanese version only.

2012/8/14 Version 2.51 beta 3
 Fix to display the title of the currently playing song in the title bar.

2012/8/12 Version 2.51 beta 2
 Fix that the window position might be not restored correctly.

2012/8/12 Version 2.51 beta 1
 Fix that the play list item may cause strange when sorting the item order.

2012/8/10 Version 2.50 stable
 Stable version is released.

2012/8/8 Version 2.49 beta 17
 Fix that many dialog box may appear when using "Save all" function.

2012/8/7 Version 2.49 beta 16
 Fix that all opened files had been locked.

2012/8/7 Version 2.49 beta 15
 Fix that the window size become smaller when switching the controls visible
 state.

2012/8/6 Version 2.49 beta 14
 Fix that the "untitled" tab is created unnecessary when booting.

2012/8/5 Version 2.49 beta 13
 Fix that the playlist does not display when fullscreen.

2012/8/4 Version 2.49 beta 12
 Fix that "Length" of the playlist is garbled.

2012/8/1 Version 2.49 beta 11
 Fix the bug that could not play videos.

2012/7/28 Version 2.49 beta 10
 If the song is stopped, fixed to not fade out.

2012/7/28 Version 2.49 beta 9
 Improve the lyrics font size.

2012/7/28 Version 2.49 beta 8
 Add a 'Fade out next' function.

2012/7/28 Version 2.49 beta 7
 Add a 'Fade out stop' function.

2012/7/22 Version 2.49 beta 6
 Improve boot time.

2012/7/16 Version 2.49 beta 5
 Reduced the size of the executable file with optimizing the source code.

2012/7/15 Version 2.49 beta 4
 Add a 'Change LR' function.

2012/7/15 Version 2.49 beta 3
 Supports changing the focus with Ctrl + Tab key.

2012/7/14 Version 2.49 beta 2
 Fix the bug that when opening a directory when multiple tabs exist, the
 opened file won't play.

2012/7/14 Version 2.49 beta 1
 Improve boot time.

2012/7/13 Version 2.48 stable
 Stable version is released.

2012/7/8 Version 2.47 beta 8
 Added 12 types of preset "Delay" effect.

2012/7/7 Version 2.47 beta 7
 Fixed a bug that the video screen may cause strange.

2012/7/7 Version 2.47 beta 6
 Added 29 types of preset "Reverb" effect.

2012/7/1 Version 2.47 beta 5
 Fixed a bug that the display of the lyrics may cause strange when the play
 position is changed.

2012/7/1 Version 2.47 beta 4
 Improved the font size auto-detection function for displaying the lyrics.

2012/6/30 Version 2.47 beta 3
 Fixed a bug that the display of the lyrics may cause strange when using the
 'offset' tag.

2012/6/30 Version 2.47 beta 2
 Fixed a bug that the lyrics did not disappear after playback end.

2012/6/30 Version 2.47 beta 1
 Supports the LRC format lyrics files for displaying the lyrics. Current version
 supports the Shift_JIS format. The LRC lyrics format file needs to be placed in
 the same folder as the audio file. The LRC lyrics format file's extension is lrc,
 kra or txt. File name must be the same as audio file.

2012/6/7 Version 2.46 stable
 Stable version is released.

2012/6/2 Version 2.45 beta 10
 Fixed a bug that playback might stops when you drop the file to the playlist.

2012/5/27 Version 2.45 beta 9
 Fixed a bug that tab label state was not back from edit state when clicking
 another tab.

2012/5/27 Version 2.45 beta 8
 Fixed a bug that playback stop occurred when removing a file from the playlist.

2012/5/27 Version 2.45 beta 7
 By drag and drop a tab, you can sort tabs of the playlist.

2012/5/26 Version 2.45 beta 6
 Improve the speed when removing the item from the playlist.

2012/5/23 Version 2.45 beta 5
 Improved the behavior of fast-forward, rewind.

2012/5/20 Version 2.45 beta 4
 Add a metronome function.

2012/5/16 Version 2.45 beta 3
 Improve boot time.

2012/5/13 Version 2.45 beta 2
 Fix the play position label flicker.

2012/5/12 Version 2.45 beta 1
 Reduce the deviation of the video and audio.

2012/5/10 Version 2.44 stable
 Stable version is released.

2012/5/10 Version 2.43 beta 12
 Fix the application freeze when the video playback was complete.

2012/5/5 Version 2.43 beta 11
 Supports changing the video playback speed, pitch and graphic equalizer.

2012/5/4 Version 2.43 beta 10
 Fix the bug that could not play videos on Windows XP.

2012/5/3 Version 2.43 beta 9
 Fix the screen flicker when changing to the next file.

2012/4/30 Version 2.43 beta 8
 Fix the bug that could not do the AB loop by shortcut key.

2012/4/30 Version 2.43 beta 7
 Fix the bug that when droping a file when multiple tabs exist, the dropped
 file won't play.

2012/4/30 Version 2.43 beta 6
 Fix the bug that when opening a file when multiple tabs exist, the opened file
 won't play.

2012/4/30 Version 2.43 beta 5
 Delete selected items on the playlist by right-clicking the item and selecting
 "Delete" menu.

2012/4/30 Version 2.43 beta 4
 Create a new tab by right-clicking on the tab and selecting the menu "NEW Tab".

2012/4/30 Version 2.43 beta 3
 Change fullscreen by double-clicking the video screen during video playing.

2012/4/25 Version 2.43 beta 2
 Fixed it did not start playing the next file even if the video is done playing.

2012/4/24 Version 2.43 beta 1
 Supports video file formats.

2012/4/1 Version 2.42 stable
 English version is released.

------------------------------------------------------------------------------
