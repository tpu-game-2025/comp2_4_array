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
void resize(my_array* ar, int n) {
	// ... (n <= 0 の処理)

	// 1. 新しいメモリを確保
	int* new_addr = (int*)malloc(sizeof(int) * n);
	if (new_addr == NULL) return; // 確保失敗時はここで終了

	// 2. コピーする要素数を決定
	int copy_count = (ar->num < n) ? ar->num : n;

	// ★★★ 3. データを新しいメモリへコピー (解放前に行う！) ★★★
	for (int i = 0; i < copy_count; i++) {
		new_addr[i] = ar->addr[i];
	}

	// ★★★ 4. 古いメモリを解放 ★★★
	if (ar->addr != NULL) {
		free(ar->addr);
	}

	// 5. 構造体のメンバーを新しい値で更新
	ar->addr = new_addr;
	ar->num = n;
}

	

bool set(my_array* ar, int index, int val)
{
if (index >= 0 && index < ar->num) {
		
		ar->addr[index] = val;
		return true;
	}
	
	return false;
}


int get(const my_array* ar, int index)
{
	if (index >= 0 && index < ar->num) {
		
		return ar->addr[index];
	}
	
	return 0;
}


int size(const my_array* ar)
{
	
	return ar->num;
}