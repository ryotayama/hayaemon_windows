cd Debug
set PATH=C:\Program Files (x86)\Microsoft Visual Studio 10.0\Team Tools\Performance Tools;%PATH%
set _NT_SYMBOL_PATH=symsrv*symsrv.dll*C:\localsymbols*http://msdl.microsoft.com/download/symbols
start %ComSpec%
VSPerfCmd /start:sample /output:profile
VSPerfCmd /launch:Hayaemon.exe
exit
