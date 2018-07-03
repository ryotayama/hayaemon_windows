/*
	xVideo 1.2.2 C/C++ header file
	Copyright (c) 2010-2011 Cristea Aurel Ionut.
	Check http://surodev.com for updates

*/

#ifndef xVideo_H
#define xVideo_H


#ifdef __cplusplus
extern "C" {
#endif

#define BASS_DSHOW

#ifdef BASS_DSHOW
#include "bass.h"
#endif
#ifndef BASS_DSHOW
    #define xVideo_VERSION 0x010202	// API version
	#define xVideoVERSIONTEXT "1.2.2"
#else
    #define xVideo_VERSION 0x010202	// API version
    #define xVideoVERSIONTEXT "1.2.2"
#endif


#ifndef xVideoDEF
#define xVideoDEF(f) WINAPI f
#endif

#define HWINDOW DWORD   //multi video handle
#define HDVP    DWORD   // DVP handle
#ifndef BASS_DSHOW
 
#define HSTREAM DWORD   // playing sample's channel handle
#define HRECORD DWORD   // recording handle
#define HSYNC   DWORD   // synchronizer handle
#define HDSP    DWORD   // DSP handle
#define HFX     DWORD   // FX Handle
#define HPLUGIN DWORD   // plugin Handle
#endif



//////////////////////////////////////////CALLBACKS///////////////////////////////////////////////////
 
typedef BOOL (CALLBACK CallBackConnectedFilters)(void * Filter, PCHAR FilterName,BOOL pp,void* user);
/*
   Filter- the instance of a IBaseFilter;
   FilterName - The name of the Filter
   pp - Boolean, Filter supports or not Property Pages
   user - The 'user' parameter 
*/
#ifndef BASS_DSHOW

typedef void (CALLBACK DSPPROC)(HDSP handle, DWORD channel, void *buffer, DWORD length, void *user);
/* DSP callback function. NOTE: A DSP function should obviously be as quick as
possible... other DSP functions, streams can not be processed
until it's finished.
handle : The DSP handle
channel: Channel that the DSP is being applied to
buffer : Buffer to apply the DSP to
length : Number of bytes in the buffer
user   : The 'user' parameter given when calling xVideo_ChannelSetDSP */


#endif


typedef void (CALLBACK DVPPROC)(HDVP handle, DWORD channel, void *buffer, DWORD length,DWORD dataType,int width,int height, void *user);
/* DVP callback function. NOTE: A DVP function should obviously be as quick as
possible... other DVP functions, streams can not be processed
until it's finished.
handle     : The DVP handle
channel    : Channel that the DVP is being applied to
buffer     : Buffer to apply the DVP to
length     : Number of bytes in the buffer
dataType   : one of the xVideo_TYPE_xxx
width      : video width
height     : video height
user       : The 'user' parameter given when calling xVideo_ChannelSetDVP 
*/


typedef BOOL (CALLBACK CallBackEnumerator)(char * name,GUID guid,void * user);
/*
  name - the device name
  GUID - the device CLSID
  user - The 'user' parameter
*/


typedef BOOL (CALLBACK CallBackStreamEnumerator)(DWORD format,char * name,DWORD index,BOOL enabled,void * user);
/*
  format - 0: unknown, 1: video , 2: audio , 3: subtitle
  name -  the format name
  index - stream index. Use this index to enable or disable it
  enabled -is this stream enabled??
  user - The 'user' parameter
*/

typedef BOOL (CALLBACK CallBackSync)(HSTREAM chan,DWORD sync,DWORD data,void* user);
/*
  chan - the channel that triggered the sync
  sync - one of the xVideo_SYNC_XXX
  data - sync data
  user - the 'user' parameter 
*/

typedef BOOL (CALLBACK CallBackEnumProfiles)(char * profile,void * user);
/*
  profile - the device profile
  user - The 'user' parameter 
*/




//Stream Creation Flags
#define xVideo_UNICODE			0x80000000 //Use this parameter at flags when create a stream
#define xVideo_STREAM_AUTOFREE  0x40000    //Use this parameter at flags when create a stream
#define xVideo_STREAM_DECODE    0x200000   //Use this parameter at flags when create a stream
#define xVideo_STREAM_MIX       0x1000000  //Use this flag to enable mixing video on a channel
#define xVideo_NOAUDIO_PROC     0x80000    //Use this flag to disable audio processor
#define xVideo_STREAM_AUTODVD   0x4000000  //use this flag to enable auto dvd functions(on mouse down, keys etc)
#define xVideo_STREAM_LOOP      0x8000000  //use this flag to restart stream when it's finished
#define xVideo_STREAM_VIDEOPROC 0x20000    //Use this to enable video processor

//xVideo_CaptureXXX functions flags
//...........................................
#define    xVideo_CaptureAudio          0x10066  
#define    xVideo_CaptureVideo          0x10080

//xVideo_ChannelGetState return values
#define xVideo_STATE_PLAYING	1 //channel is playing
#define xVideo_STATE_PAUSED  	2 //channel is paused
#define xVideo_STATE_STOPPED	3 //channel is stopped

//xVideo_ChannelGetLenght/SetPosition/GetPosition: modes
#define xVideo_POS_SEC 0  //position in seconds
#define xVideo_POS_FRAME 1 //position in frames
#define xVideo_POS_MILISEC 2 //position in miliseconds
#define xVideo_POS_REFTIME 3 //position in reference time


//xVideo_SetConfig configs and values\\ 
//...........................................
#define    xVideo_CONFIG_VideoRenderer         0x1000
#define    xVideo_NULLVideo             6   //pass this to select NULL Video Renderer
#define    xVideo_EVR                   5   //pass this to select Enhanced Video Renderer
#define    xVideo_VMR9WindowsLess       4   //pass this to select VMR9 window less render
#define    xVideo_VMR7WindowsLess       3   //pass this to select VMR7 window less render
#define    xVideo_VMR9                  2  //pass this to select VMR9 Windowed render
#define    xVideo_VMR7                  1  //pass this to select VMR7 Windowed render
#ifndef BASS_DSHOW
 //............................................
#define    xVideo_CONFIG_AudioRenderer  0x1004  //use this to select audio renderer
#define    xVideo_NULLAudio             0x1432  //use this to select NULL Audio Renderer
#define    xVideo_DefaultAudio          0x1433  //use this to select Windows Default Audio Device
//.............................................
#define    xVideo_CONFIG_FLOATDSP       0x1005
#endif
//.............................................
#define    xVideo_CONFIG_WindowLessStreams     0x1002  //use this to set the number of streams in a VMR7/9 Windowsless mode
#define    xVideo_CONFIG_WindowLessHandle      0x1001  //VMR7/VMR9 WindowLess Mode need an initial window so set a HWND to use properly VMR
 
 
//////Color Controls FLAGS////////////////////////////
#define xVideo_ControlBrightness 0x00000001
#define xVideo_ControlContrast   0x00000002
#define xVideo_ControlHue        0x00000004
#define xVideo_ControlSaturation 0x00000008


///////xVideo_ChannelSetAttribute/GetAttribute Constants
#define    xVideo_ATTRIB_VOL   1    //used to set Audio Volume
#define    xVideo_ATTRIB_PAN   2    //used to set Audio Pan
#define    xVideo_ATTRIB_RATE  3    //used to set Graph Rate
#define    xVideo_ATTRIB_ALPHA 4    //use this to set main video alpha blend value

#ifndef BASS_DSHOW
// User file stream callback functions
typedef void (CALLBACK FILECLOSEPROC)(void *user);
typedef __int64 (CALLBACK FILELENPROC)(void *user);
typedef DWORD (CALLBACK FILEREADPROC)(void *buffer, DWORD length, void *user);
typedef BOOL (CALLBACK FILESEEKPROC)(__int64 offset, void *user);

typedef struct {
	FILECLOSEPROC *close;
	FILELENPROC *length;
	FILEREADPROC *read;
	FILESEEKPROC *seek;
} xVideo_FILEPROCS;

#endif

//for Video BMP functions////
struct xVideo_VideoBitmap{
		BOOL visible;
	    int inLeft;
		int inTop;
		int inRight;
		int inBottom;
	    float outLeft;
		float outTop;
		float outRight;
		float outBottom;
		float alphavalue;
		COLORREF transColor;
		HDC bmp;
} ;

 

//xVideo_ChannelGetData 
#define xVideo_DATA_END		   0x80000000	// end of file
#define xVideo_DATA_FLOAT  	   0x40000000	// flag: return floating-point sample data
#define xVideo_DATA_FFT256     0x60000001   // flag: return FFT 256
#define xVideo_DATA_FFT512     0x60000002   // flag: return FFT 512 
#define xVideo_DATA_FFT1024    0x60000003   // flag: return FFT 1024 

//xVideo_CallbackItemByIndex
#define xVideo_CALLBACK_AC     1  //used to get the audio capture device
#define xVideo_CALLBACK_VC     2  //used to get the video capture device
#define xVideo_CALLBACK_AR     3  //used to get the audio renderer device

#ifndef BASS_DSHOW
// FX effect types, use with xVideo_ChannelSetFX
#define xVideo_FX_REVERB      1
#define xVideo_FX_PARAMEQ     2
#define xVideo_FX_CHORUS      3	
#define xVideo_FX_COMPRESSOR  4
#define xVideo_FX_ECHO        5
#define xVideo_FX_FLANGER     6
#define xVideo_FX_PITCHTEMPO  7
#define xVideo_FX_CHANMIX     8

typedef struct {
    float   fCenter;
    float   fBandwidth;
    float   fGain;
} xVideoFX_PARAMEQ;

typedef struct {
    float  tempo;
    float  pitch;
    float  tempoRate;
} xVideoFX_TEMPO;

typedef struct {
   DWORD mode;  //xVideo_CHANMIX_xxx
} xVideoFX_CHANNELMIX;

typedef struct {
    float   fInGain;                // [-96.0,0.0]            default: 0.0 dB
    float   fReverbMix;             // [-96.0,0.0]            default: 0.0 db
    float   fReverbTime;            // [0.001,3000.0]         default: 1000.0 ms
    float   fHighFreqRTRatio;       // [0.001,0.999]          default: 0.001
} xVideoFX_REVERB;

typedef struct
{
    float       fWetDryMix;
    float       fDepth;
    float       fFeedback;
    float       fFrequency;
    LONG        lWaveform;
    float       fDelay;
    LONG        lPhase;
} xVideoFX_FLANGER;

typedef struct  
{
    float       fWetDryMix;
    float       fDepth;
    float       fFeedback;
    float       fFrequency;
    LONG        lWaveform;          // 0=triangle, 1=sine
    float       fDelay;
    LONG        lPhase;   //xVideo_PHASE_xxx
} xVideoFX_CHORUS;

typedef struct 
{
    float   fGain;
    float   fAttack;
    float   fRelease;
    float   fThreshold;
    float   fRatio;
    float   fPredelay;
} xVideoFX_COMPRESSOR;


typedef struct 
{
    float   fWetDryMix;
    float   fFeedback;
    float   fLeftDelay;
    float   fRightDelay;
    LONG    lPanDelay;
} xVideoFX_ECHO;




#define xVideo_PHASE_NEG_180        0
#define xVideo_PHASE_NEG_90         1
#define xVideo_PHASE_ZERO           2
#define xVideo_PHASE_90             3
#define xVideo_PHASE_180            4


//xVideoFX_CHANNELMIX modes 
#define xVideo_CHANMIX_STEREO       0 //unchanged 
#define xVideo_CHANMIX_LEFTRIGHT    1 //copy left audio data to right
#define xVideo_CHANMIX_RIGHTLEFT    2 //copy right audio data to left
#endif


//for xVideo_ChannelGetInfo function////
struct xVideo_ChannelInfo{
		float AvgTimePerFrame;
		int Height;
		int Width; 
		int nChannels;
		DWORD freq;
		DWORD wBits;
		bool floatingpoint;
} ;
//for xVideo_ChannelColorRange function////
struct xVideo_ColorsRange{
		float  MinValue;
        float  MaxValue;
        float  DefaultValue;
        float  StepSize;
		DWORD  type; // one of the xVideo_ControlXXX
} ;

//for xVideo_ChannelSetColors function////
struct xVideo_ColorsSet{
	   float Contrast;
       float Brightness;
       float Hue;
       float Saturation;
} ;


//xVideo_PLUGININFO
typedef struct {
	DWORD version;					// version 
	DWORD decoderType;				// decoder type: 1=audio 2=video
	char * plgdescription;          // plugin description
} xVideo_PLUGININFO;

typedef struct 
{
   DWORD format;  //0: unknown, 1: video , 2: audio , 3: subtitle
   char* name;    // the format name
   DWORD index;   //stream index. Use this index to enable or disable it
   BOOL enabled;  //is this stream enabled??
} xVideo_STREAMS;

 


//DVD function flags
//............................................

//for xVideo_DVDGetProperty function 
#define xVideo_CurentDVDTitle             0x10010
#define xVideo_DVDTitles                  0x10020
#define xVideo_DVDTitleChapters           0x10030
#define xVideo_DVDCurrentTitleDuration    145
#define xVideo_DVDCurrentTitlePosition    146

//for xVideo_DVDSetProperty function 
#define    xVideo_DVD_TITLEMENU        100
#define    xVideo_DVD_ROOT             101      //go to DVD root
#define    xVideo_DVD_NEXTCHAPTER      102      //go to dvd next chapter
#define    xVideo_DVD_PREVCHAPTER      103     //go to dvd previous chapter
#define    xVideo_DVD_TITLE            104     //go to dvd title
#define    xVideo_DVD_TITLECHAPTER     105     //play chapter in current title

//for xVideo_DVDChannelMenu function
#define xVideo_DVDSelectAtPos  21
#define xVideo_DVDActionAtPos  22
#define xVideo_DVDActivateBut  23
#define xVideo_DVDSelectButton 24


//xVideo Error Codes
//.............................................................

#define xVideo_OK                 0
#define xVideo_INVALIDCHAN        1 
#define xVideo_UNKNOWN            2
#define xVideo_NotInitialized     3
#define xVideo_POSNOTAVAILABLE    4
#define xVideo_NODSHOW            5 
#define xVideo_INVALIDWINDOW      6
#define xVideo_NOAUDIO            7
#define xVideo_NOVIDEO            8
#define xVideo_ERRORMEM           9
#define xVideo_ERRORCALLBACK      10
#define xVideo_ERRORFLAG          11
#define xVideo_NOTAVAILABLE       12
#define xVideo_ERRORINIT          13
#define xVideo_ALREADYREGISTERED  14
#define xVideo_INVALIDREG         15


/////xVideo_TYPE_XXX//////////////////////////////////
#define xVideo_TYPE_RGB24         1
#define xVideo_TYPE_RGB32         2
#define xVideo_TYPE_YUYV          3
#define xVideo_TYPE_IYUV          4
#define xVideo_TYPE_YVU9          5
#define xVideo_TYPE_YV12          6
#define xVideo_TYPE_NV12          7
#define xVideo_TYPE_UYVY          8


/////xVideo_SYNC_XXX//////////////////////////////////
#define xVideo_SYNC_END                            1
#define xVideo_SYNC_DVD_CHAPTER_START              2
#define xVideo_SYNC_DVD_TITLE_CHANGE               3
#define xVideo_SYNC_DVD_ERROR                      4
#define xVideo_SYNC_REPAINT                        5
#define xVideo_SYNC_VIDEO_SIZE_CHANGED             6


////////////////////////////Functions\\\\\\\\\\\\\\\\\\\\\\\\\\\\	
DWORD   xVideoDEF(xVideo_ErrorGetCode)();
DWORD   xVideoDEF(xVideo_GetVersion)();	
BOOL    xVideoDEF(xVideo_Init)(HWND handle,DWORD flags);
BOOL    xVideoDEF(xVideo_Free)();
HSTREAM xVideoDEF(xVideo_StreamCreateFile)(void* str,DWORD pos,HWND win,DWORD flags);
BOOL    xVideoDEF(xVideo_ChannelPlay)(HSTREAM chan);
BOOL    xVideoDEF(xVideo_ChannelPause)(HSTREAM chan);
BOOL    xVideoDEF(xVideo_ChannelStop)(HSTREAM chan);
BOOL    xVideoDEF(xVideo_StreamFree)(HSTREAM chan);
HWINDOW xVideoDEF(xVideo_ChannelAddWindow)(HSTREAM chan,HWND win);
BOOL    xVideoDEF(xVideo_ChannelRemoveWindow)(HSTREAM chan,HWINDOW window);
double  xVideoDEF(xVideo_ChannelGetLength)(HSTREAM chan,DWORD mode);
double  xVideoDEF(xVideo_ChannelGetPosition)(HSTREAM chan,DWORD mode);
BOOL    xVideoDEF(xVideo_ChannelSetPosition)(HSTREAM chan ,double pos,DWORD mode);
void *  xVideoDEF(xVideo_GetGraph)(HSTREAM chan);
void    xVideoDEF(xVideo_ChannelResizeWindow)(HSTREAM chan,DWORD hVideo,int left,int top, int right, int bottom);
void    xVideoDEF(xVideo_ChannelSetFullscreen)(HSTREAM chan,BOOL value);
void    xVideoDEF(xVideo_SetConfig)(DWORD config,DWORD value);
void    xVideoDEF(xVideo_ChannelGetInfo)(HSTREAM chan,xVideo_ChannelInfo *info);
HBITMAP xVideoDEF(xVideo_ChannelGetBitmap)(HSTREAM chan);
BOOL    xVideoDEF(xVideo_ChannelColorRange)(HSTREAM chan,DWORD id,xVideo_ColorsRange *ctrl);
BOOL    xVideoDEF(xVideo_ChannelSetColors)(HSTREAM chan,DWORD id,xVideo_ColorsSet *Struct);
BOOL    xVideoDEF(xVideo_SetVideoAlpha)(HSTREAM chan,HWINDOW win,int layer,float alpha);
float   xVideoDEF(xVideo_GetVideoAlpha)(HSTREAM chan,HWINDOW win,int layer);
BOOL    xVideoDEF(xVideo_MIXChannelResize)(HSTREAM chan,int layer,int left,int top,int right, int bottom);
int     xVideoDEF(xVideo_CaptureGetDevices)(DWORD devicetype,CallBackEnumerator *callback,void* user);
int     xVideoDEF(xVideo_CaptureDeviceProfiles)(int device,DWORD devicetype,CallBackEnumProfiles *callback,void * user);
BOOL    xVideoDEF(xVideo_ChannelOverlayBMP)(HSTREAM chan,xVideo_VideoBitmap* Struct);
void    xVideoDEF(xVideo_ChannelSetWindow)(HSTREAM chan,DWORD window,HWND handle);
BOOL    xVideoDEF(xVideo_ChannelAddFile)(HSTREAM chan,void* filename,DWORD flags);
int     xVideoDEF(xVideo_ChannelGetConnectedFilters)(HSTREAM chan,CallBackConnectedFilters * CALLBack,void *user);
void    xVideoDEF(xVideo_ShowFilterPropertyPage)(HSTREAM chan,DWORD filter,HWND parent);
DWORD   xVideoDEF(xVideo_ChannelGetState)(HSTREAM chan);
HFX     xVideoDEF(xVideo_ChannelSetFX)(HSTREAM chan,int fx);
BOOL    xVideoDEF(xVideo_ChannelRemoveFX)(HSTREAM chan,HFX fx);
BOOL    xVideoDEF(xVideo_SetFXParameters)(HSTREAM chan,HFX fx,void* param);
BOOL    xVideoDEF(xVideo_GetFXParameters)(HSTREAM chan,HFX fx,void* param);
void    xVideoDEF(xVideo_ChannelSetAttribute)(HSTREAM chan,DWORD option,float value);
float   xVideoDEF(xVideo_ChannelGetAttribute)(HSTREAM chan,DWORD option);
HRECORD xVideoDEF(xVideo_CaptureCreate)(int audio,int video,int audioprofile,int videoprofile,DWORD flags);
BOOL    xVideoDEF(xVideo_CaptureFree)(HRECORD chan);
int     xVideoDEF(xVideo_GetAudioRenderers)(CallBackEnumerator *callback,void* user);


HSTREAM xVideoDEF(xVideo_StreamCreateFileMem)(void* data,__int64 size,HWND win,DWORD flags);
HSTREAM xVideoDEF(xVideo_StreamCreateFileUser)(DWORD flags,HWND win,const void *proc, void *user);

BOOL    xVideoDEF(xVideo_ChannelRemoveDSP)(HSTREAM chan,HDSP dsp);
HDSP    xVideoDEF(xVideo_ChannelSetDSP)(HSTREAM chan,DSPPROC* proc,void* user);

DWORD   xVideoDEF(xVideo_ChannelGetData)(HSTREAM chan,BYTE* data,DWORD size);
BOOL    xVideoDEF(xVideo_ChannelRepaint)(HSTREAM chan,HWND handle,HDC hDC);
LPCSTR  xVideoDEF(xVideo_CallbackItemByIndex)(DWORD type,DWORD index);
HPLUGIN xVideoDEF(xVideo_LoadPlugin)(void* filename,DWORD flags);
BOOL    xVideoDEF(xVideo_PluginGetInfo)(HPLUGIN plugin,xVideo_PLUGININFO *info);
BOOL    xVideoDEF(xVideo_RemovePlugin)(HPLUGIN plugin);

HSTREAM xVideoDEF(xVideo_StreamCreateDVD)(void* dvd,HWND win,DWORD flags);
DWORD   xVideoDEF(xVideo_DVDGetProperty)(HSTREAM chan,DWORD prop,DWORD value);
BOOL    xVideoDEF(xVideo_DVDSetProperty)(HSTREAM chan,DWORD prop,DWORD value);
BOOL    xVideoDEF(xVideo_DVDChannelMenu)(HSTREAM chan,DWORD option,int value1,int value2);
DWORD   xVideoDEF(xVideo_GetConfig)(DWORD config);
BOOL    xVideoDEF(xVideo_ChannelSetPositionVB)(HSTREAM chan ,LONGLONG pos,DWORD mode);

DWORD   xVideoDEF(xVideo_ChannelGetLevel)(HSTREAM chan);

HSTREAM xVideoDEF(xVideo_StreamCreateFilter)(void* str,void* filter,HWND win,DWORD flags);
HPLUGIN xVideoDEF(xVideo_LoadPluginDS)(void* guid,void* name,DWORD flags);

BOOL    xVideoDEF(xVideo_VCamStreamChannel)(HSTREAM chan,BOOL stream);
BOOL    xVideoDEF(xVideo_VCamPush)(HWND win,BYTE *data);
BOOL    xVideoDEF(xVideo_Register)(void* email,void* reg,DWORD flags);

BOOL    xVideoDEF(xVideo_ChannelCallBackSync)(HSTREAM chan,CallBackSync* callback,void * user);
HDVP    xVideoDEF(xVideo_ChannelSetDVP)(HSTREAM chan,DVPPROC* proc,void* user);
BOOL    xVideoDEF(xVideo_ChannelRemoveDVP)(HSTREAM chan,HDVP dsp);

DWORD   xVideoDEF(xVideo_ChannelStreamsCount)(HSTREAM chan);
BOOL    xVideoDEF(xVideo_ChannelGetStream)(HSTREAM chan,DWORD index, xVideo_STREAMS* pstream);
BOOL    xVideoDEF(xVideo_ChannelEnableStream)(HSTREAM chan,DWORD index);
int     xVideoDEF(xVideo_ChannelEnumerateStreams)(HSTREAM chan,CallBackStreamEnumerator* callback,void* user);
#ifdef __cplusplus
}
#endif

#endif
