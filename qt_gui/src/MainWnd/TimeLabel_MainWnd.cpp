//----------------------------------------------------------------------------
// TimeLabel_MainWnd.cpp : 再生時間表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include "TimeLabel_MainWnd.h"
#include "MainWnd.h"
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CTimeLabel_MainWnd::Create()
{
	connect(m_rMainWnd.timeLabel, &CStaticCore::OnLButtonDown,
					this, &CTimeLabel_MainWnd::OnLButtonDown);
	return TRUE;
}
//----------------------------------------------------------------------------
// 表示する時間を秒単位で設定
//----------------------------------------------------------------------------
void CTimeLabel_MainWnd::SetTime(double time, double totalTime, BOOL bResetPos)
{
	if(time < 0) time = 0;
	if(totalTime < 0) totalTime = 0;
	if(bRemainMode) time = totalTime - time;

	int hour = (int)(time / 3600) % 60;
	int second = (int)(time / 60) % 60;
	int minute = (int)time % 60;

	int totalHour = (int)(totalTime / 3600) % 60;
	int totalSecond = (int)(totalTime / 60) % 60;
	int totalMinute = (int)totalTime % 60;

	char text[20];
	if(totalHour > 0)
		sprintf(text, "%02d:%02d:%02d / %02d:%02d:%02d", hour, second,
					minute, totalHour, totalSecond, totalMinute);
	else
	{
		if(totalTime == 0.0 && time != 0.0)
			sprintf(text, "%02d:%02d / --:--", second, minute);
		else
			sprintf(text, "%02d:%02d / %02d:%02d", second, minute,
					totalSecond, totalMinute);
	}

	if(strLast == text) return;
	strLast = text;

	m_rMainWnd.timeLabel->setText(QString::fromStdString(strLast));
}
//----------------------------------------------------------------------------
