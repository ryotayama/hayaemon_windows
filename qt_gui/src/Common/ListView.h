//----------------------------------------------------------------------------
// ListView.h : リストビューの管理を行う
//----------------------------------------------------------------------------
#ifndef ListViewH
#define ListViewH

#include <vector>
#include <QIcon>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "Define.h"
//----------------------------------------------------------------------------
// リストビューの管理を行うクラス
//----------------------------------------------------------------------------
class CListView : public QTableWidget
{
public: // 関数

	explicit CListView(QWidget * parent) : QTableWidget(parent) { }
	virtual ~CListView() { }

	virtual BOOL DeleteAllItems() {
		clearContents();
		setRowCount(0);
		return TRUE;
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
			item->setFlags(item->flags() & (~Qt::ItemIsEditable));
			setItem(i, iSubItem, item);
		}
		item->setText(pszText);
		item->setIcon(GetItemIcon(iImage));
	}
	virtual void SetItemState(int i, UINT state, UINT mask) {
		if (state == LVIS_SELECTED) {
			for (int j = 0; j < this->columnCount(); j++) {
				auto item = this->item(i, j);
				if (item != nullptr) {
					item->setSelected(true);
				}
			}
		}
	}
	virtual int InsertColumn(int nCol, const QString & lpszColumnHeading,
								int nFormat = LVCFMT_LEFT, int nWidth = -1,
								int nSubItem = -1) {
		auto item = new QTableWidgetItem(lpszColumnHeading);
		item->setTextAlignment(
				nFormat == LVCFMT_RIGHT ? Qt::AlignRight : Qt::AlignLeft);
		this->setHorizontalHeaderItem(nCol, item);
		this->setColumnWidth(nCol, nWidth);
		return nCol;
	}
	virtual int InsertItem(int nItem) {
		insertRow(nItem);
		return nItem;
	}
	virtual void Show(int nCmdShow) {
		this->setVisible(nCmdShow != SW_HIDE);
	}

protected:

	// 選択されたアイテムを取得する。ただし、列の重複はないリストを返す。
	std::vector<int> GetSelectedRows();
	virtual QIcon GetItemIcon(int idx) const { return QIcon(); }
};
//----------------------------------------------------------------------------

#endif
