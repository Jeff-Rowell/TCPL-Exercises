#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000 		/* max #lines to be sorted */
#define MAXLEN 1000 		/* max length of any input line */
#define ALLOCSIZE 10000 	/* size of available space */

char *lineptr[MAXLINES];		 /* pointers to text lines */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

int get_line(char *, int);
char *alloc(int);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void quicksort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int num_cmp(const char *, const char *);
int str_cmp(const char *s, const char *t);
int rev_num_cmp(const char *, const char *);
int rev_str_cmp(const char *s, const char *t);

/* Exercise 5-14.
 *
 * Modify the sort program to handle a -r flag, which indicates sorting in reverse
 * (decreasing) order. Be sure that -r works with -n.
 *
 * NOTE: This exercise has intentionally skimped on error checking as specified in K & R 2.
 * 		 The assumption is that the command will always be run as:
 *
 * 		 	./sort -n -r
 *
 * 		 This is to demonstrate the main goal of understanding pointers to functions, not error
 * 		 checking.
 */

/* sort input lines */
int main(int argc, char *argv[])
{
	int nlines; 	 /* number of input lines read */
	int numeric = 0; /* 1 if numeric sort */
	int reverse = 0; /* 1 if reverse sort */

	if (argc > 2 && str_cmp(argv[1], "-n") == 0 && str_cmp(argv[2], "-r") == 0)
	{
		numeric = 1;
		reverse = 1;
	}
	else if (argc > 1 && str_cmp(argv[1], "-n") == 0)
		numeric = 1;
	else if (argc > 1 && str_cmp(argv[1], "-r") == 0)
		reverse = 1;

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
	{
		if (numeric && reverse)
			quicksort((void**) lineptr, 0, nlines-1, (int (*)(void*, void*))(rev_num_cmp));
		else if (numeric)
			quicksort((void**) lineptr, 0, nlines-1, (int (*)(void*, void*))(num_cmp));
		else if (reverse)
			quicksort((void**) lineptr, 0, nlines-1, (int (*)(void*, void*))(rev_str_cmp));
		else
			quicksort((void**) lineptr, 0, nlines-1, (int (*)(void*, void*))(str_cmp));

		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("input too big to sort\n");
		return 1;
	}
}

/* return pointer to n characters */
char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) /* it fits */
	{
		allocp += n;
		return allocp - n; /* old p */
	}
	else /* not enough room */
		return 0;
}

/* num_cmp: compare s1 and s2 numerically */
int num_cmp(const char *s1, const char *s2)
{
	int v1, v2;
	v1 = strlen(s1);
	v2 = strlen(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

/* rev_num_cmp: compare s1 and s2 numerically, in reverse order */
int rev_num_cmp(const char *s1, const char *s2)
{
	int v1, v2;
	v1 = strlen(s1);
	v2 = strlen(s2);
	if (v1 > v2)
		return -1;
	else if (v1 < v2)
		return 1;
	else
		return 0;
}

/* str_cmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int str_cmp(const char *s, const char *t)
{
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

/* rev_str_cmp: return <0 if s>t, 0 if s==t, >0 if s<t */
int rev_str_cmp(const char *s, const char *t)
{
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *t - *s;
}

/* swap: swaps to elements in v[] */
void swap(void *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim)
{
	int c, i;
	for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = get_line(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else
		{
			line[len-1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

/* quicksort: sort v[left]...v[right] into increasing order */
void quicksort(void *v[], int left, int right, int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	quicksort(v, left, last-1, comp);
	quicksort(v, last+1, right, comp);
}
