#ifndef _BASS_DSHOW_EXPORT_FUNC_H
#define _BASS_DSHOW_EXPORT_FUNC_H

#if __cplusplus
extern "C" {
#endif

	typedef BOOL(WINAPI *LPXVIDEO_REGISTER)(void* email, void* reg, DWORD flags);
	typedef BOOL(WINAPI *LPXVIDEO_INIT)(HWND handle, DWORD flags);
	typedef HSTREAM(WINAPI *LPXVIDEO_STREAMCREATEFILE)(void* str, DWORD pos, HWND win, DWORD flags);
	typedef void(WINAPI *LPXVIDEO_CHANNELRESIZEWINDOW)(HSTREAM chan, DWORD hVideo, int left, int top, int right, int bottom);
	typedef void(WINAPI *LPXVIDEO_CHANNELGETINFO)(HSTREAM chan, xVideo_ChannelInfo *info);
	typedef void(WINAPI *LPXVIDEO_SETCONFIG)(DWORD config, DWORD value);
	typedef void(WINAPI *LPXVIDEO_CHANNELSETWINDOW)(HSTREAM chan, DWORD window, HWND handle);
	typedef BOOL(WINAPI *LPXVIDEO_STREAMFREE)(HSTREAM chan);

#if __cplusplus
}
#endif

#endif //_BASS_DSHOW_EXPORT_FUNC_H
