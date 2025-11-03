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
	// ToDo:配列の要素数を変更しよう！(reallocは禁止)
	if (ar == NULL) return;
	// n <= 0 の場合は空にする
	if (n <= 0) {
		free(ar->addr);
		ar->addr = NULL;
		ar->num = 0;
		return;
	}

	// 新しい配列を確保
	int* new_addr = (int*)malloc(sizeof(int) * n); // malloc
	if (new_addr == NULL) {

		return; //メモリ確保失敗時は何もしない
	}
	//小さい方をコピー
	int copy_size = 0;
	if (ar->addr != NULL && ar->num > 0) { // ar->addrがNULLの場合はコピーしない
		copy_size = (n < ar->num) ? n : ar->num; //三項演算子
	}

	// 古い配列の先頭からcopy_size個分のデータを、新しい配列にコピー
	if (copy_size > 0) {
		memcpy(new_addr, ar->addr, (size_t)copy_size * sizeof(int));
	}
	// memcpy(コピー先, コピー元, コピーするバイト数);
	// for (int i = 0; i < copy_size; i++) { new_addr[i] = ar->addr[i]; }では安全性(Error:C6386)に欠けていた

	// 古い配列を解放
	free(ar->addr);
	// ポインタを更新
	ar->addr = new_addr;
	ar->num = n;
}

// my_array のindex番目の要素にvalを設定する
// index が確保されていない場所を指していたら返り値をfalseにする（設定出来たらtrue）
bool set(my_array* ar, int index, int val)
{
	// ToDo:配列の要素を変更しよう！
	if (ar == NULL || index < 0 || index >= ar->num) return false; //ar->num <= index < 0

	ar->addr[index] = val; // index番目の要素にvalを設定
	return true;
}

// my_array のindex番目の要素を取得する
// index が確保されていない場所を指していたら0を返す
int get(const my_array* ar, int index)
{
	// ToDo:要素を所得して、indexがおかしかったら0を返そう
	if (ar == NULL || index < 0 || index >= ar->num) return 0; // 0を返す
	return ar->addr[index]; // 要素取得
}

// my_array の要素数を取得する
int size(const my_array* ar)
{
	// ToDo: 配列の要素数を返そう
	if (ar == NULL) return 0; // 0を返す
	return ar->num; // 要素数取得
}
