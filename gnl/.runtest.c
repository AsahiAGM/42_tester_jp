#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

// GNLプロジェクトのファイルからインクルードしてください
// char *get_next_line(int fd);

#define FILE_COUNT 3

// ファイルの状態を保持する構造体
typedef struct s_file_info {
  int fd;
  int file_num;
  int line_num;
  char *path;
  int is_eof; // EOFに達したかどうか
} t_file_info;

// --- ユーティリティ関数 ---
void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	c = n % 10 + '0';
	write(fd, &c, 1);
}

// リストから指定インデックスの要素を削除し、リストサイズを減らす
void remove_file_info(t_file_info **list, int *size, int index_to_remove) {
  t_file_info *new_list; // reallocの新しいポインタを保持する変数

  // 削除対象のFDを閉じ、メモリを解放
  close((*list)[index_to_remove].fd);
  free((*list)[index_to_remove].path);

  // 削除対象以降の要素を前に詰める
  for (int i = index_to_remove; i < *size - 1; i++)
    (*list)[i] = (*list)[i + 1];

  // サイズを1減らす
  (*size)--;

  if (*size > 0) {
    // reallocの結果を一時変数で受け取る
    new_list = realloc(*list, sizeof(t_file_info) * (*size));
    if (new_list == NULL) {
      // realloc失敗時のエラー処理 (非常に重要)
      perror("realloc failed in remove_file_info");
      exit(1);
    }
    // 成功した場合のみ、元のポインタを更新
    *list = new_list;
  } else {
    free(*list);
    *list = NULL; // サイズ0になったらNULLを設定
  }
}

// --- メイン関数 ---

int main(void) {
  char *initial_files[FILE_COUNT] = {(char *)".src/srcA.txt",
                                     (char *)".src/srcB.txt",
                                     (char *)".src/srcC.txt"};

  // ファイル情報を動的に保持するリスト
  t_file_info *file_list = NULL;
  int current_file_count = 0;

  // 乱数シードの設定
  srand(time(NULL));

  // 1. 初期化: 全ファイルをオープンし、リストに格納
  file_list = malloc(sizeof(t_file_info) * FILE_COUNT);
  if (!file_list)
    return (1);
  current_file_count = FILE_COUNT;

  for (int i = 0; i < FILE_COUNT; i++) {
    file_list[i].fd = open(initial_files[i], O_RDONLY);
    if (file_list[i].fd == -1) {
      perror(initial_files[i]);
      // エラーが発生したファイルはリストに入れない
      current_file_count--;
      continue;
    }
    file_list[i].file_num = i + 1; // ファイル番号 (1, 2, 3...)
    file_list[i].line_num = 0;
    file_list[i].path = strdup(initial_files[i]);
    file_list[i].is_eof = 0;
  }

  // オープンエラーで全て失敗した場合
  if (current_file_count == 0) {
    free(file_list);
    return (0);
  }
  // リストサイズを実際にオープンできた数に調整
  file_list = realloc(file_list, sizeof(t_file_info) * current_file_count);

  printf("%s--- Random GNL Start (Total %d files) ---\n\n%s", ANSI_GREEN,
         current_file_count, ANSI_RESET); fflush(stdout);

  // 2. メインループ: リストが空になるまで繰り返す
  while (current_file_count > 0) {
    // 2-1. ランダムなファイルを選択
    if (current_file_count == 0) // 理論上は到達しないが安全策として
      break;
    int random_index = rand() % current_file_count;
    // t_file_info *current_file = &file_list[random_index];

    // 2-2. get_next_lineを呼び出し
    char *line = get_next_line(file_list[random_index].fd);

    // 2-3. 結果の出力
    if (line != NULL) {
      // 🚨 修正点3: ポインタではなく、配列要素を更新
      file_list[random_index].line_num++;

      // ----------------------------------------------------
      // 修正箇所: printf から write への変更
      // ----------------------------------------------------

      char buffer[1024]; // 出力メッセージを構築するためのバッファ
      unsigned long len = 0;

      // 1. 出力文字列をバッファに構築（snprintfでprintfと同じ書式を適用）
      // snprintfは文字列の長さを返し、バッファオーバーフローを防止します。
      len = snprintf(buffer, sizeof(buffer), "[fd %d:%dc] %s",
                     file_list[random_index].file_num,
                     file_list[random_index].line_num, line);  

      // 2. 構築した文字列全体を write 関数で標準出力 (STDOUT_FILENO) に書き出す
      if (len > 0 && len < sizeof(buffer)) {
        write(STDOUT_FILENO, buffer, (size_t)len);
      }

      if (strrchr(line, '\n') == NULL)
        write(STDOUT_FILENO, "\n", 1); 

      // 3. get_next_lineで割り当てられたメモリを解放
      free(line);
    } else // line == NULL (EOFまたはエラー)
    {
      int removed_file_num = file_list[random_index].file_num;

      // 🚨 修正点4: ポインタではなく、配列要素のfile_numを使用
      // printf("[%d:EOF] EOF\n", file_list[random_index].file_num);

      // 2-4. EOFとなったファイルをリストから除外
      // 135行目 (エラーの直前)
      remove_file_info(&file_list, &current_file_count, random_index);
      // 136行目 (エラー箇所):
      // remove_file_info内でリストがreallocで移動/解放されたため、
      // その後で古いポインタ(current_file)を参照するとInvalid Readが発生する。
      if (file_list == NULL) // current_file_countが0になった時
      {
        // printf("--- All files processed. ---\n"); // 最終出力をここで出すか
        break; // ループを抜ける
      }

      // 🚨 修正点5: 必要な情報もポインタを使わず、直接配列要素から取得
      // (remove_file_infoの中で出力済みのためここでは不要)
      write(STDOUT_FILENO, ANSI_GREEN, strlen(ANSI_GREEN));
      write(STDOUT_FILENO, "--- File", 9);
      ft_putnbr_fd(removed_file_num, STDOUT_FILENO);
      write(STDOUT_FILENO, " finished. Remaining: ", 23);
      ft_putnbr_fd(current_file_count, STDOUT_FILENO);
      write(STDOUT_FILENO, " ---\n", 6);
      write(STDOUT_FILENO, ANSI_RESET, strlen(ANSI_RESET));
      // continue; // 次のループへ
    }
    // 処理の区切りとして少し待機する（オプション）
    usleep(100000);
  }

  printf("\n%s--- All files processed. ---\n%s", ANSI_GREEN, ANSI_RESET);

  // 3. 終了処理: メモリ解放
  // current_file_countが0になった時点で全てのfdは閉じられているはず

  return (0);
}