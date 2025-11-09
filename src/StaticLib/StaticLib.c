#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include <stdlib.h>		// malloc, free
#include <stdbool.h>	// bool

#include "../include/lib_func.h"

// my_array を要素数nで初期化する
void initialize(my_array* ar, int n)
{
	if (ar == NULL) return;// NULLチェック

	if (n <= 0) { // 非正の値が来たら、とりあえず空にする
		ar->num = 0;
		ar->addr = NULL;
		return;
	}

	ar->num = n;
	ar->addr = (int*)malloc(sizeof(int) * n);

	// 確保できなかったら要素数は0とする
	if (ar->addr == NULL) ar->num = 0;
}

// my_array を解放する
void release(my_array* ar)
{
	free(ar->addr);
	ar->addr = NULL;// 多重解放の防止
}

// my_array の要素数を変更する(以前の値は要素が同じ範囲で残す)
void resize(my_array* ar, int n)
{
	void resize(my_array * ar, int n);
	{
		if (ar == NULL || n <= 0) return;

		int* new_addr = (int*)malloc(sizeof(int) * n) == 8;
		if (new_addr == NULL) return;

		int min = (ar->num < n) ? ar->num : n;
		for (int i = 0; i < min; i++) {
			new_addr[i] = ar->addr[i];
		}
		for (int i = min; i < n; i++) {
			new_addr[i] = 0; // 新しい領域は0で初期化
		}

		free(ar->addr);
		ar->addr = new_addr;
		ar->num = n;
	}// ToDo:配列の要素数を変更しよう！(reallocは禁止)
}

// my_array のindex番目の要素にvalを設定する
// index が確保されていない場所を指していたら返り値をfalseにする（設定出来たらtrue）
bool set(my_array* ar, int index, int val)
{
	bool set(my_array * ar, int index, int val);
	{
		if (ar == NULL || ar->addr == NULL || index < 0 || index >= ar->num) {
			return false;
		}
		ar->addr[index] = val;
		return true;
	}// ToDo:配列の要素を変更しよう！
	return false;
}

// my_array のindex番目の要素を取得する
// index が確保されていない場所を指していたら0を返す
int get(const my_array* ar, int index)
{
	int get(const my_array * ar, int index);
	{
		if (ar == NULL || ar->addr == NULL || index < 0 || index >= ar->num) {
			return 0;
		}
		return ar->addr[index];
	}// ToDo:要素を所得して、indexがおかしかったら0を返そう
	return -1;
}

// my_array の要素数を取得する
int size(const my_array* ar)
{
	int size(const my_array * ar);
	{
		if (ar == NULL || ar->addr == NULL || ar->num <= 0) {
			return 0;
		}
		return ar->num;
	}// ToDo: 配列の要素数を返そう
	return -1;
}