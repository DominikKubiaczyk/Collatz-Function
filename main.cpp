#include <iostream>
#include <stdio.h>
using namespace std;
#define MAXUNSIGNEDINT 4294967295

void swap(int &a, int &b)
{
        int temp = a;
        a = b;
        b = temp;
}

void heapifyMax(unsigned int *tabLiczb, int *tabIndex, int current, int size)
{
        int L = current * 2;
        int R = (current * 2) + 1;
        int maxps;
        if (L <= size && (tabLiczb[tabIndex[L - 1]] > tabLiczb[tabIndex[current - 1]] || (tabLiczb[tabIndex[L - 1]] == tabLiczb[tabIndex[current - 1]] && tabIndex[L - 1] < tabIndex[current - 1])))
        {
                maxps = L;
        }
        else
        {
                maxps = current;
        }
        if (R <= size && (tabLiczb[tabIndex[R - 1]] > tabLiczb[tabIndex[maxps - 1]] || (tabLiczb[tabIndex[R - 1]] == tabLiczb[tabIndex[maxps - 1]] && tabIndex[R - 1] < tabIndex[maxps - 1])))
        {
                maxps = R;
        }
        if (maxps != current)
        {
                swap(tabIndex[current - 1], tabIndex[maxps - 1]);
                heapifyMax(tabLiczb, tabIndex, maxps, size);
        }
}

void heapifyMin(unsigned int *tabLiczb, int *tabIndex, int current, int size)
{
        int L = current * 2;
        int R = (current * 2) + 1;
        int maxps;
        if (L <= size && (tabLiczb[tabIndex[L - 1]] < tabLiczb[tabIndex[current - 1]] || (tabLiczb[tabIndex[L - 1]] == tabLiczb[tabIndex[current - 1]] && tabIndex[L - 1] < tabIndex[current - 1])))
        {
                maxps = L;
        }
        else
        {
                maxps = current;
        }
        if (R <= size && (tabLiczb[tabIndex[R - 1]] < tabLiczb[tabIndex[maxps - 1]] || (tabLiczb[tabIndex[R - 1]] == tabLiczb[tabIndex[maxps - 1]] && tabIndex[R - 1] < tabIndex[maxps - 1])))
        {
                maxps = R;
        }
        if (maxps != current)
        {
                swap(tabIndex[current - 1], tabIndex[maxps - 1]);
                heapifyMin(tabLiczb, tabIndex, maxps, size);
        }
}

void buildHeapMax(unsigned int *tabLiczb, int *tabIndex, int size)
{
        for (int i = size / 2; i > 0; i--)
        {
                heapifyMax(tabLiczb, tabIndex, i, size);
        }
}

void buildHeapMin(unsigned int *tabLiczb, int *tabIndex, int size)
{
        for (int i = size / 2;i > 0;i--)
        {
                heapifyMin(tabLiczb, tabIndex, i, size);
        }
}

int main()
{
        int n, ilosc_komend, powtorzenie, dlugosc_max, dlugosc_min,j=0,k=0;
        char komenda, prev='a';
        unsigned long long int test;
        scanf("%d", &n);
        unsigned int *TablicaLiczb = new unsigned int[n];
        for (int i = 0;i < n;i++)
        {
                scanf(" %u", &TablicaLiczb[i]);
        }
        int *TablicaMax = new int[n];
        int *TablicaMin = new int[n];
        dlugosc_max = n;
        dlugosc_min = n;
        for (int i = 0;i < n;i++)
        {
                if (TablicaLiczb[i] == 1)
                {
                        dlugosc_max -= 1;
                }
                else
                {
                        TablicaMax[j] = i;
                        j++;
                }
        }
        for (int i = 0;i < n;i++)
        {
                if (TablicaLiczb[i] == 1)
                {
                        dlugosc_min -= 1;
                }
                else
                {
                        TablicaMin[k] = i;
                        k++;
                }
        }
        buildHeapMax(TablicaLiczb, TablicaMax, dlugosc_max);
        buildHeapMin(TablicaLiczb, TablicaMin, dlugosc_min);
        scanf("%d", &ilosc_komend);
        while (ilosc_komend > 0)
        {
                scanf("%d ", &powtorzenie);
                komenda = getchar();
                while (powtorzenie > 0 && dlugosc_max > 0 && dlugosc_min > 0)
                {
                        switch (komenda)
                        {
                        case 'l':
                                if (prev == 's')
                                {
                                        buildHeapMax(TablicaLiczb, TablicaMax, dlugosc_max);
                                        for (int i = 0;i < dlugosc_max;i++)
                                        {
                                                if (TablicaLiczb[TablicaMax[0]] <= 1)
                                                {
                                                        swap(TablicaMax[0], TablicaMax[dlugosc_max - 1]);
                                                        dlugosc_max -= 1;
                                                        if (dlugosc_max < 1) { break; }
                                                        heapifyMax(TablicaLiczb, TablicaMax, 1, dlugosc_max);
                                                }
                                        }
                                }

                                if (TablicaLiczb[TablicaMax[0]] % 2 == 0)
                                {
                                        TablicaLiczb[TablicaMax[0]] /= 2;
                                        if (TablicaLiczb[TablicaMax[0]] == 1)
                                        {
                                                swap(TablicaMax[0], TablicaMax[dlugosc_max-1]);
                                                dlugosc_max -= 1;
                                                if (dlugosc_max < 1) { break; }
                                                heapifyMax(TablicaLiczb, TablicaMax, 1, dlugosc_max);
                                        }
                                        else
                                        {
                                                heapifyMax(TablicaLiczb, TablicaMax, 1, dlugosc_max);
                                        }
                                }
                                else
                                {
                                        test = (unsigned long long int)(TablicaLiczb[TablicaMax[0]]);
                                        test = (test * 3) + 1;
                                        if (test > MAXUNSIGNEDINT)
                                        {
                                                TablicaLiczb[TablicaMax[0]] = 0;
                                                swap(TablicaMax[0], TablicaMax[dlugosc_max - 1]);
                                                dlugosc_max -= 1;
                                                if (dlugosc_max < 1) { break; }
                                                heapifyMax(TablicaLiczb, TablicaMax, 1, dlugosc_max);
                                        }
                                        else
                                        {
                                                TablicaLiczb[TablicaMax[0]] = (TablicaLiczb[TablicaMax[0]] * 3) + 1;
                                        }
                                }
                                prev = 'l';
                                break;
                        case 's':
                                if (prev == 'l')
                                { 
                                        buildHeapMin(TablicaLiczb, TablicaMin, dlugosc_min);
                                        for (int i = 0;i < dlugosc_min;i++)
                                        {
                                                if (TablicaLiczb[TablicaMin[0]] <= 1)
                                                {
                                                        swap(TablicaMin[0], TablicaMin[dlugosc_min - 1]);
                                                        dlugosc_min -= 1;
                                                        if (dlugosc_min < 1) { break; }
                                                        heapifyMin(TablicaLiczb, TablicaMin, 1, dlugosc_min);
                                                }
                                        }
                                }

                                if (TablicaLiczb[TablicaMin[0]] % 2 == 0)
                                {
                                        TablicaLiczb[TablicaMin[0]] = TablicaLiczb[TablicaMin[0]] / 2;
                                        if (TablicaLiczb[TablicaMin[0]] == 1)
                                        {
                                                swap(TablicaMin[0], TablicaMin[dlugosc_min - 1]);
                                                dlugosc_min -= 1;
                                                if (dlugosc_min < 1) { break; }
                                                heapifyMin(TablicaLiczb, TablicaMin, 1, dlugosc_min);
                                        }
                                }
                                else
                                {
                                        test = (unsigned long long int)(TablicaLiczb[TablicaMin[0]]);
                                        test = (test * 3) + 1;
                                        if (test > MAXUNSIGNEDINT)
                                        {
                                                TablicaLiczb[TablicaMin[0]] = 0;
                                                swap(TablicaMin[0], TablicaMin[dlugosc_min - 1]);
                                                dlugosc_min -= 1;
                                                if (dlugosc_min < 1) { break; }
                                                heapifyMin(TablicaLiczb, TablicaMin, 1, dlugosc_min);
                                        }
                                        else
                                        {
                                                TablicaLiczb[TablicaMin[0]] = (TablicaLiczb[TablicaMin[0]] * 3) + 1;
                                                heapifyMin(TablicaLiczb, TablicaMin, 1, dlugosc_min);
                                        }
                                }
                                prev = 's';
                                break;
                        default:
                                break;
                        }
                        powtorzenie -= 1;
                }
                ilosc_komend -= 1;
        }

        for (int i = 0;i < n;i++)
        {
                if (TablicaLiczb[i] == 0 || TablicaLiczb[i] == MAXUNSIGNEDINT)
                {
                        printf("m ");
                }
                else
                {
                        printf("%u ", TablicaLiczb[i]);
                }
        }

        delete[] TablicaLiczb;
        delete[] TablicaMax;
        delete[] TablicaMin;

        return 0;
}