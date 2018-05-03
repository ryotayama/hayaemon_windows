//----------------------------------------------------------------------------
// ListView.cpp : リストビューの管理を行う
//----------------------------------------------------------------------------
#include "ListView.h"
#include <algorithm>
//----------------------------------------------------------------------------
// 選択されたアイテムを取得する。ただし、列の重複はないリストを返す。
//----------------------------------------------------------------------------
std::vector<int> CListView::GetSelectedRows()
{
	auto indexes = selectedIndexes();
	std::sort(indexes.begin(), indexes.end(),
						[] (auto lhs, auto rhs) { return lhs.row() < rhs.row(); });
	auto end = std::unique(indexes.begin(), indexes.end(),
												 [] (auto &lhs, auto &rhs) {
													 return lhs.row() == rhs.row();
												 });
	std::vector<int> rows;
	for(auto it = indexes.begin(); it != end; ++it) {
		rows.push_back(it->row());
	}
	return rows;
}
//----------------------------------------------------------------------------
