/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:44:39 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/16 21:05:13 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*xmalloc(size_t size)
{
	void *p = malloc(size);
	if(!p)
	{
		fprintf(stderr,"minishell: allocation error\n");
		exit(1);
	}
	return p;
}
// utils.c内 xrealloc関数のみ修正
void	*xrealloc(void *ptr, size_t size)
{
	if(!ptr)
		return xmalloc(size);

	if(size == 0) {
		xfree(ptr);
		return NULL;
	}

	// ptrはnull終端char**を想定
	// 要素数を数える
	char **old = (char**)ptr;
	size_t old_count = 0;
	while(old[old_count])
		old_count++;

	// 新領域確保
	void *newp = xmalloc(size);
	// コピーする要素数は元々の個数と新しい要素数に応じて決まるが、
	// 基本的に呼び出し側は常にsizeがoldより大きいケース。
	// 安全策としてコピーサイズはold_count+1(ヌル終端分) * sizeof(char*)
	size_t new_count = size / sizeof(char*);
	size_t copy_count = (old_count+1 < new_count) ? old_count+1 : new_count;
	memcpy(newp, old, copy_count*sizeof(char*));

	xfree(old);
	return newp;
}

void	xfree(void *ptr)
{
	if(ptr)
		free(ptr);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *res=ft_strjoin(s1,s2);
	xfree(s1);
	xfree(s2);
	return res;
}

int ft_fprintf(FILE *stream, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int fd = fileno(stream);
	int saved_stdout = -1;
	if(fd != STDOUT_FILENO) {
		saved_stdout = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
	}

	// 簡易フォーマット処理はここで行う
	// フォーマット文字列を走査してwriteやprintfで出力
	// ただしprintfはstdoutのみ、既にdup2でstderrをstdoutにしたのでprintfで出力可能
	// よってfmt内に%があれば対応、なければそのまま出力

	// 簡易処理(すべてprintfに任せる)
	// dup2でstderr->stdoutにしたので printf(fmt, args...)できないがva_listは使えない
	// → 仕方なく%が少ない想定なので簡易パーサ記述
	// ここではフォーマット文字が%sや%dの単純なケースのみ対応する。

	// シンプルに:
	// 1. フォーマット文字列を1文字ずつ読んで、%があれば次文字チェック
	// 2. %s -> char*取得してprintf("%s", str)
	// 3. %d -> int取得してprintf("%d", d)
	// 4. %c -> int取得しchar変換
	// 5. %% -> '%'
	// 普通文字はそのままputchar
	// これで十分なはず(エラー時メッセージで複雑なフォーマットは使わないと仮定)

	int written = 0;
	const char *p=fmt;
	while(*p) {
		if(*p=='%') {
			p++;
			if(*p=='s') {
				char* s = va_arg(args,char*);
				if(!s)s="(null)";
				written += printf("%s",s);
				p++;
			} else if(*p=='d') {
				int d = va_arg(args,int);
				written += printf("%d",d);
				p++;
			} else if(*p=='c') {
				int c = va_arg(args,int);
				written += printf("%c",(char)c);
				p++;
			} else if(*p=='%') {
				written += printf("%%");
				p++;
			} else {
				// 未対応フォーマットはそのまま出力
				written += printf("%%");
				// %の次の文字も出す
				if(*p) {
					written+=printf("%c",*p);
					p++;
				}
			}
		} else {
			written += printf("%c", *p);
			p++;
		}
	}
	va_end(args);

	if(saved_stdout != -1) {
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}

	return written;
}

