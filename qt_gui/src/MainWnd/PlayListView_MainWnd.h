//----------------------------------------------------------------------------
// PlayListView_MainWnd.h : プレイリスト用リストビューの管理を行う
//----------------------------------------------------------------------------
#ifndef PlayListView_MainWndH
#define PlayListView_MainWndH

class CMainWnd;
#include <stdint.h>
#include <vector>
#include <QIcon>
#include <QList>
#include <QTableWidget>
#include "../Common/Define.h"
class QUrl;
//----------------------------------------------------------------------------
// プレイリスト用リストビューの管理を行うクラス
//----------------------------------------------------------------------------
class CPlayListView_MainWnd : public QTableWidget
{
	Q_OBJECT

public: // 関数
	CPlayListView_MainWnd(CMainWnd & mainWnd, QWidget * parent = nullptr);

	virtual void AddFile(const QString & filePath, int nPos = -1);
	virtual BOOL Create();
	virtual BOOL DeleteAllItems();
	virtual int GetMaxPlayOrder() const;
	virtual void SetPlaying(int iItem);
	virtual void SetPausing(int iItem);
	virtual void SetPlayOrder(int iItem);
	virtual void SetPlayOrder(int iItem, int nOrder);
	virtual void ClearPlayOrder();
	virtual void ResetNumber();
	virtual void ScrollToItem(int nItem);

	virtual void OnDropFiles(const QList<QUrl> & urls);

public: // メンバ変数の取得・設定

	virtual std::vector<int> GetOrders() const
	{
		return orders;
	}

public:
	// Qtのラッパー
	virtual BOOL DeleteItem(int nItem) {
		if (nItem < this->rowCount()) {
			this->removeRow(nItem);
		}
		return nItem < this->rowCount();
	}
	virtual BOOL EnsureVisible(int nItem, BOOL fPartialOK) {
		if (nItem < this->rowCount()) {
			this->scrollToItem(this->item(nItem, 0));
		}
		return nItem < this->rowCount();
	}
	virtual int GetItemCount() const { return rowCount(); }
	virtual void GetItemText(int iItem, int iSubItem, QString * pszText) const {
		*pszText = this->item(iItem, iSubItem)->text();
	}
	virtual void SetItem(int i, int iSubItem, const QString & pszText) {
		SetItem(i, iSubItem, pszText, -1);
	}
	virtual void SetItem(int i, int iSubItem, const char16_t * pszText,
											 int iImage) {
		SetItem(i, iSubItem, QString::fromUtf16(pszText), iImage);
	}
	virtual void SetItem(int i, int iSubItem, const wchar_t * pszText,
											 int iImage) {
		SetItem(i, iSubItem, QString::fromWCharArray(pszText), iImage);
	}
	virtual void SetItem(int i, int iSubItem, const QString & pszText,
											 int iImage) {
		auto item = this->item(i, iSubItem);
		if (item == nullptr) {
			item = new QTableWidgetItem();
			setItem(i, iSubItem, item);
		}
		item->setText(pszText);
		item->setIcon(iImage >= 0 ? m_icons[iImage] : QIcon());
	}
	virtual int InsertColumn(int nCol, const QString & lpszColumnHeading,
								int nFormat = LVCFMT_LEFT, int nWidth = -1,
								int nSubItem = -1);
	virtual int InsertItem(int nItem) {
		insertRow(nItem);
		return nItem;
	}

protected:
  void dragEnterEvent(QDragEnterEvent * e) override;
  void dropEvent(QDropEvent * e) override;
	QStringList mimeTypes() const override {
		return QTableWidget::mimeTypes() << QStringLiteral("text/uri-list");
	}

private: // メンバ変数

	CMainWnd & m_rMainWnd;

	std::vector<int> orders; // 再生順
	QIcon m_icons[2];
};
//----------------------------------------------------------------------------

#endif
