#include <bits/stdc++.h>
#include <graphics.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <cmath>
#define PI 3.14159265
#define E 2.718281828

using namespace std;

char op[] = "+-*/:^";
char variabile[200][200];
int nrVar;
int lungimeaFerestrei;

struct nod{
    char c[300];
    nod *st;
    nod *dr;
    nod *mij;
};

struct stiva{
    char ch;
    unsigned int poz;
};

bool esteNumar(char s[])
{
    if(!strcmp(s, "-"))
        return 0;
    unsigned int i, n = strlen(s), nrp = 0, nrv = 0;
    for(i = 0; i < n; i++)
    {
        if(!((s[i] <= '9' && s[i] >= '0') || s[i] == '.' || s[i] == ',' || (s[i] == '-' && i == 0)))
            return 0;
        if(s[i] == '.')
            nrp++;
        if(s[i] == ',')
            nrv++;
        if(nrp + nrv > 1)
            return 0;
    }
    return 1;
}

bool esteVariabila(char s[])
{
    if(s[0] < 'A' || s[0] > 'z')
        return 0;
    if(s[0] == 'A' && (strlen(s) > 1 && s[1] == '{') || strlen(s) == 0)
    if(strchr(s, '('))
        return 0;
    if(strchr(s, '{'))
        return 0;
    if(strchr(s, '['))
        return 0;
    if(strchr(s, '.'))
        return 0;
    if(strchr(s, ','))
        return 0;
    if(strchr(s, '^'))
        return 0;
    if(!strcmp(s, "sin"))
        return 0;
    if(!strcmp(s, "cos"))
        return 0;
    if(!strcmp(s, "C"))
        return 0;
    if(!strcmp(s, "tg"))
        return 0;
    if(!strcmp(s, "ctg"))
        return 0;
    if(!strcmp(s, "ln"))
        return 0;
    if(!strcmp(s, "lg"))
        return 0;
    if(!strcmp(s, "log"))
        return 0;
    return 1;
}

bool estePS(char s[])
{
    int poz = 0;
    for(unsigned int i = 0; i < strlen(s); i++)
    {
        if(s[i] == '=')
            poz = i;
        if(s[i] == '<' || s[i] == '>' || s[i] == '(' || s[i] == '[' || s[i] == '{')
            return 0;
    }
    if(poz == 0)
        return 0;
    char cst[100], cdr[100];
    strcpy(cdr, s + poz + 1);
    for(unsigned int i = 0; s[i] != '='; i++)
        cst[i] = s[i];
    cst[poz] = '\0';
    return esteVariabila(cst) * esteNumar(cdr);
}

double fact(double n)
{
    if(n <= 1)
        return 1;
    return n * fact(n - 1);
}

double aranjamente(double n, double k)
{
    return fact(n) / fact(n - k);
}

double combinari(double n, double k)
{
    return aranjamente(n, k) / fact(k);
}

bool expresieCorecta(char s[])
{
    stiva st[100];
    unsigned int n = strlen(s), j;
    int iSt = -1;
    for(j = 0; j < n; j++)                                                         ///Identificarea operatiei principale
    {
        if(strchr("([{", s[j]))
            st[++iSt].ch = s[j];
        else if(strchr(")]}", s[j]))
            st[iSt--].ch = '\0';
        else if(strchr(op, s[j]) && (iSt == -1 || strchr(op, st[iSt].ch)))
        {
            iSt++;
            st[iSt].ch = s[j];
            st[iSt].poz = j;
        }
    }
    if(iSt > -1)
    {
        char aux[300];
        unsigned int pozitie;
        if(!iSt)
        {
            aux[0] = st[0].ch;
            aux[1] = '\0';
            pozitie = st[0].poz;
        }
        else
        {
            bool exist = 0;
            for(j = 0; j <= unsigned(iSt) && !exist; j++)
                if(st[j].ch == '+' || st[j].ch == '-')
                {
                    pozitie = st[j].poz;
                    exist = 1;
                }
            if(!exist)
            {
                for(j = 0; j <= unsigned(iSt) && !exist; j++)
                    if(st[j].ch == '*' || st[j].ch == '/' || st[j].ch == ':')
                    {
                        pozitie = st[j].poz;
                        exist = 1;
                    }
                if(!exist)
                    for(j = 0; j <= unsigned(iSt) && !exist; j++)
                        if(st[j].ch == '^')
                        {
                            pozitie = st[j].poz;
                            exist = 1;
                        }
            }
        }
        char cst[100];
        char cdr[100];
        if(s[0] == '(' && s[pozitie - 1] == ')')
        {
            for(j = 1; j < pozitie - 1; j++)
                cst[j - 1] = s[j];
            cst[j - 1] = '\0';

        }
        else
        {
            for(j = 0; j < pozitie; j++)
                cst[j] = s[j];
            cst[pozitie] = '\0';
        }
        if(s[pozitie + 1] == '(' && s[n - 1] == ')')
        {
            for(j = pozitie + 2; j < n - 1; j++)
                cdr[j - pozitie - 2] = s[j];
            cdr[j - pozitie - 2] = '\0';
        }
        else
        {
            for(j = pozitie + 1; j < n; j++)
                cdr[j - pozitie - 1] = s[j];
            cdr[j - pozitie - 1] = '\0';
        }
        return expresieCorecta(cst) * expresieCorecta(cdr);
    }
    if(s[0] == 'f' && s[1] ==  'r' && s[2] == 'a' && s[3] == 'c')                  ///FRACTIE
    {
        if(s[4] == '(' || s[4] == '[')
            return 0;
        char cst[100];
        char cdr[100];
        unsigned int i = 5;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 5] = s[i];
            i++;
        }
        if(s[i + 1] != '{')
            return 0;
        cst[i - 5] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cdr[i - nj] = '\0';
        return expresieCorecta(cst) * expresieCorecta(cdr);
    }
    if(s[0] == 'f' && s[1] == 'a' && s[2] == 'c' && s[3] == 't')                   ///FACTORIAL
    {
        if(s[4] == '(' || s[4] == '[')
            return 0;
        char cst[100];
        unsigned int i = 5;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 5] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cst[i - 5] = '\0';
        return expresieCorecta(cst);
    }
    if(s[0] == 'a' && s[1] == 'b' && s[2] == 's')                                  ///MODUL
    {
        if(s[3] == '(' || s[3] == '[')
            return 0;
        char cst[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cst[i - 4] = '\0';
        return expresieCorecta(cst);
    }
    if(s[0] == 's' && s[1] == 'q' && s[2] == 'r' && s[3] == 't' && s[4] == '{')    ///RADICAL
    {
        char cst[100];
        unsigned int i = 5;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 5] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cst[i - 5] = '\0';
        return expresieCorecta(cst);
    }
    if(s[0] == 's' && s[1] == 'q' && s[2] == 'r' && s[3] == 't' && s[4] == '[')    ///RADICAL DE ORDIN N
    {
        char cst[100];
        char cdr[100];
        unsigned int i = 5;
        int nrparanteze = 0;
        while(!(s[i] == ']' && nrparanteze == 0))
        {
            if(s[i] == '[')
                nrparanteze++;
            if(s[i] == ']')
                nrparanteze--;
            cst[i - 5] = s[i];
            i++;
        }
        if(s[i + 1] != '{')
            return 0;
        cst[i - 5] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cdr[i - nj] = '\0';
        return expresieCorecta(cst) * expresieCorecta(cdr);
    }
    if(s[0] == 's' && s[1] == 'u' && s[2] == 'm')                                  ///SUMA DE LA I LA N
    {
        if(s[3] == '(' || s[3] == '{')
            return 0;
        char cst[100];
        char cdr[100];
        char cmij[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == ']' && nrparanteze == 0))
        {
            if(s[i] == '[')
                nrparanteze++;
            if(s[i] == ']')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        if(s[i + 1] != '[')
            return 0;
        cst[i - 4] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == ']' && nrparanteze == 0))
        {
            if(s[i] == '[')
                nrparanteze++;
            if(s[i] == ']')
                nrparanteze--;
            cmij[i - nj] = s[i];
            i++;
        }
        if(s[i + 1] != '{')
            return 0;
        cmij[i - nj] = '\0';
        i += 2;
        nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cdr[i - nj] = '\0';
        return expresieCorecta(cst) * expresieCorecta(cdr) * expresieCorecta(cmij);
    }
    if(s[0] == 'p' && s[1] == 'r' && s[2] == 'o' && s[3] == 'd')                   ///PRODUSUL DE LA I LA N
    {
        if(s[4] == '(' || s[4] == '{')
            return 0;
        char cst[100];
        char cdr[100];
        char cmij[100];
        unsigned int i = 5;
        int nrparanteze = 0;
        while(!(s[i] == ']' && nrparanteze == 0))
        {
            if(s[i] == '[')
                nrparanteze++;
            if(s[i] == ']')
                nrparanteze--;
            cst[i - 5] = s[i];
            i++;
        }
        if(s[i + 1] != '[')
            return 0;
        cst[i - 5] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == ']' && nrparanteze == 0))
        {
            if(s[i] == '[')
                nrparanteze++;
            if(s[i] == ']')
                nrparanteze--;
            cmij[i - nj] = s[i];
            i++;
        }
        if(s[i + 1] != '{')
            return 0;
        cmij[i - nj] = '\0';
        i += 2;
        nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cdr[i - nj] = '\0';
        return expresieCorecta(cst) * expresieCorecta(cdr) * expresieCorecta(cmij);
    }
    if(s[0] == 'e' && s[1] == 'x' && s[2] == 'p')                                  ///EXPONENT
    {
        if(s[3] == '(' || s[3] == '[')
            return 0;
        char cst[100];
        char cdr[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        if(s[i + 1] != '{')
            return 0;
        cst[i - 4] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cdr[i - nj] = '\0';
        return expresieCorecta(cst) * expresieCorecta(cdr);
    }
    if((s[0] == 'A' || s[0] == 'C') && s[1] == '{')                                ///ARANJAMENTE+COMBINARI
    {
        char cst[100];
        char cdr[100];
        unsigned int i = 2;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 2] = s[i];
            i++;
        }
        if(s[i + 1] != '{')
            return 0;
        cst[i - 2] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cdr[i - nj] = '\0';
        return expresieCorecta(cst) * expresieCorecta(cdr);
    }
    if(s[0] == 's' && s[1] == 'i' && s[2] == 'n')                                  ///SINUS
    {
        if(s[3] == '(' || s[3] == '[')
            return 0;
        char cst[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cst[i - 4] = '\0';
        return expresieCorecta(cst);
    }
    if(s[0] == 'c' && s[1] == 'o' && s[2] == 's')                                  ///COSINUS
    {
        if(s[3] == '(' || s[3] == '[')
            return 0;
        char cst[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cst[i - 4] = '\0';
        return expresieCorecta(cst);
    }
    if(s[0] == 'c' && s[1] == 't' && s[2] == 'g')                                  ///COTANGENTA
    {
        if(s[3] == '(' || s[3] == '[')
            return 0;
        char cst[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cst[i - 4] = '\0';
        return expresieCorecta(cst);
    }
    if(s[0] == 't' && s[1] == 'g')                                                 ///TANGENTA
    {
        if(s[2] == '(' || s[2] == '[')
            return 0;
        char cst[100];
        unsigned int i = 3;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 3] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cst[i - 3] = '\0';
        return expresieCorecta(cst);
    }
    if(s[0] == 'l' && s[1] == 'n')                                                 ///LOGARITM NATURAL
    {
        if(s[2] == '(' || s[2] == '[')
            return 0;
        char cst[100];
        unsigned int i = 3;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 3] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cst[i - 3] = '\0';
        return expresieCorecta(cst);
    }
    if(s[0] == 'l' && s[1] == 'g')                                                 ///LOGARITM ZECIMAL
    {
        if(s[2] == '(' || s[2] == '[')
            return 0;
        char cst[100];
        unsigned int i = 3;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 3] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cst[i - 3] = '\0';
        return expresieCorecta(cst);
    }
    if(s[0] == 'l' && s[1] == 'o' && s[2] == 'g')                                  ///LOGARITM IN BAZA B
    {
        if(s[3] == '(' || s[3] == '[')
            return 0;
        char cst[100];
        char cdr[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        if(s[i + 1] != '{')
            return 0;
        cst[i - 4] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        if(s[i + 1] == '{' || s[i + 1] == '[' || s[i + 1] == '(')
            return 0;
        cdr[i - nj] = '\0';
        return expresieCorecta(cst) * expresieCorecta(cdr);
    }
    return estePS(s) || esteNumar(s) || esteVariabila(s);
}

bool expresieCorecta1(char s[])
{
    if(strchr(s, '<') || strchr(s, '>'))
        return 0;
    char st[100];
    unsigned int i, n = strlen(s), k = 0;
    for(i = 0; i < n; i++)                                  ///VERIFIC PARANTEZELE
    {
        if(strchr("{[(", s[i]))
            st[k++] = s[i];
        if(s[i] == ')')
        {
            if(st[k - 1] == '(')
                st[--k] = '\0';
            else
                return 0;
        }
        if(s[i] == ']')
        {
            if(st[k - 1] == '[')
                st[--k] = '\0';
            else
                return 0;
        }
        if(s[i] == '}')
        {
            if(st[k - 1] == '{')
                st[--k] = '\0';
            else
                return 0;
        }
    }
    if(k > 0)
        return 0;
    return expresieCorecta(s);
}

bool expresieCorecta2(char s[])
{
    if(!strchr(s, '<') && !strchr(s, '>') && !strchr(s, '='))
        return 0;
    char cst[200], cdr[200];
    if(strchr(s, '<'))
        strcpy(cdr, strchr(s, '<'));
    else if(strchr(s, '>'))
        strcpy(cdr, strchr(s, '>'));
    else strcpy(cdr, strchr(s, '='));
    strncpy(cst, s, strlen(s) - strlen(cdr));
    cst[strlen(s) - strlen(cdr)] = '0';
    if(cdr[0] == '<' || cdr[0] == '>' || cdr[0] == '=')
    {
        if(cdr[1] == '=')
            strcpy(cdr, cdr + 2);
        else
            strcpy(cdr, cdr + 1);
    }
    return expresieCorecta1(cst) * expresieCorecta1(cdr);
}

void afisareArbore(nod *p)
{
    if(p != NULL)
    {
        cout << p -> c << "\n";
        if(p -> st != NULL)
            cout << "Nodul " << p -> c << " are nodul stang egal cu ";
        afisareArbore(p -> st);
        if(p -> mij != NULL)
            cout << "Nodul " << p -> c << " are nodul din mijloc egal cu ";
        afisareArbore(p -> mij);
        if(p -> dr != NULL)
            cout << "Nodul " << p -> c << " are nodul drept egal cu ";
        afisareArbore(p -> dr);
    }
}

void arborizare(char s[], nod* &p)
{
    nod * q = new nod;
    q -> st = NULL;
    q -> dr = NULL;
    q -> mij = NULL;
    p = q;
    stiva st[100];
    unsigned int n = strlen(s), j;
    int iSt = -1;
    for(j = 0; j < n; j++)                                                         ///Identificarea operatiei principale
    {
        if(strchr("([{", s[j]))
            st[++iSt].ch = s[j];
        else if(strchr(")]}", s[j]))
            st[iSt--].ch = '\0';
        else if(strchr(op, s[j]) && (iSt == -1 || strchr(op, st[iSt].ch)))
        {
            iSt++;
            st[iSt].ch = s[j];
            st[iSt].poz = j;
        }
    }
    if(iSt > -1)
    {
        char aux[300];
        unsigned int pozitie;
        if(!iSt)
        {
            aux[0] = st[0].ch;
            aux[1] = '\0';
            pozitie = st[0].poz;
            strcpy(p -> c, aux);
        }
        else
        {
            bool exist = 0;
            for(j = 0; j <= unsigned(iSt) && !exist; j++)
                if(st[j].ch == '+' || st[j].ch == '-')
                {
                    pozitie = st[j].poz;
                    exist = 1;
                }
            if(!exist)
            {
                for(j = 0; j <= unsigned(iSt) && !exist; j++)
                    if(st[j].ch == '*' || st[j].ch == '/' || st[j].ch == ':')
                    {
                        pozitie = st[j].poz;
                        exist = 1;
                    }
                if(!exist)
                    for(j = 0; j <= unsigned(iSt) && !exist; j++)
                        if(st[j].ch == '^')
                        {
                            pozitie = st[j].poz;
                            exist = 1;
                        }
            }
            aux[0] = s[pozitie];
            aux[1] = '\0';
            strcpy(p->c, aux);
        }
        char cst[100];
        char cdr[100];
        if(s[0] == '(' && s[pozitie - 1] == ')')
        {
            for(j = 1; j < pozitie - 1; j++)
                cst[j - 1] = s[j];
            cst[j - 1] = '\0';
        }
        else
        {
            for(j = 0; j < pozitie; j++)
                cst[j] = s[j];
            cst[pozitie] = '\0';
        }
        if(s[pozitie + 1] == '(' && s[n - 1] == ')')
        {
            for(j = pozitie + 2; j < n - 1; j++)
                cdr[j - pozitie - 2] = s[j];
            cdr[j - pozitie - 2] = '\0';
        }
        else
        {
            for(j = pozitie + 1; j < n; j++)
                cdr[j - pozitie - 1] = s[j];
            cdr[j - pozitie - 1] = '\0';
        }
        arborizare(cst, p->st);
        arborizare(cdr, p->dr);
    }
    else
    if(s[0] == 'f' && s[1] ==  'r' && s[2] == 'a' && s[3] == 'c')                  ///FRACTIE
    {
        strcpy(p->c, "/");
        char cst[100];
        char cdr[100];
        unsigned int i = 5;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 5] = s[i];
            i++;
        }
        cst[i - 5] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        cdr[i - nj] = '\0';
        arborizare(cst, p -> st);
        arborizare(cdr, p -> dr);
    }
    else
    if(s[0] == 'f' && s[1] == 'a' && s[2] == 'c' && s[3] == 't')                   ///FACTORIAL
    {
        strcpy(p -> c, "!");
        char cst[100];
        unsigned int i = 5;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 5] = s[i];
            i++;
        }
        cst[i - 5] = '\0';
        arborizare(cst, p -> st);
    }
    else
    if(s[0] == 'a' && s[1] == 'b' && s[2] == 's')                                  ///MODUL
    {
        strcpy(p -> c, "|");
        char cst[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        cst[i - 4] = '\0';
        arborizare(cst, p -> st);
    }
    else
    if(s[0] == 's' && s[1] == 'q' && s[2] == 'r' && s[3] == 't' && s[4] == '{')    ///RADICAL
    {
        strcpy(p -> c, "$");
        char cst[100];
        unsigned int i = 5;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 5] = s[i];
            i++;
        }
        cst[i - 5] = '\0';
        arborizare(cst, p -> st);
    }
    else
    if(s[0] == 's' && s[1] == 'q' && s[2] == 'r' && s[3] == 't' && s[4] == '[')    ///RADICAL DE ORDIN N
    {
        strcpy(p -> c, "#");
        char cst[100];
        char cdr[100];
        unsigned int i = 5;
        int nrparanteze = 0;
        while(!(s[i] == ']' && nrparanteze == 0))
        {
            if(s[i] == '[')
                nrparanteze++;
            if(s[i] == ']')
                nrparanteze--;
            cst[i - 5] = s[i];
            i++;
        }
        cst[i - 5] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        cdr[i - nj] = '\0';
        arborizare(cst, p -> st);
        arborizare(cdr, p -> dr);
    }
    else
    if(s[0] == 's' && s[1] == 'u' && s[2] == 'm')                                  ///SUMA DE LA I LA N
    {
        strcpy(p -> c, "S");
        char cst[100];
        char cdr[100];
        char cmij[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == ']' && nrparanteze == 0))
        {
            if(s[i] == '[')
                nrparanteze++;
            if(s[i] == ']')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        cst[i - 4] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == ']' && nrparanteze == 0))
        {
            if(s[i] == '[')
                nrparanteze++;
            if(s[i] == ']')
                nrparanteze--;
            cmij[i - nj] = s[i];
            i++;
        }
        cmij[i - nj] = '\0';
        i += 2;
        nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        cdr[i - nj] = '\0';
        arborizare(cst, p -> st);
        arborizare(cmij, p -> mij);
        arborizare(cdr, p -> dr);
    }
    else
    if(s[0] == 'p' && s[1] == 'r' && s[2] == 'o' && s[3] == 'd')                   ///PRODUSUL DE LA I LA N
    {
        strcpy(p -> c, "P");
        char cst[100];
        char cdr[100];
        char cmij[100];
        unsigned int i = 5;
        int nrparanteze = 0;
        while(!(s[i] == ']' && nrparanteze == 0))
        {
            if(s[i] == '[')
                nrparanteze++;
            if(s[i] == ']')
                nrparanteze--;
            cst[i - 5] = s[i];
            i++;
        }
        cst[i - 5] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == ']' && nrparanteze == 0))
        {
            if(s[i] == '[')
                nrparanteze++;
            if(s[i] == ']')
                nrparanteze--;
            cmij[i - nj] = s[i];
            i++;
        }
        cmij[i - nj] = '\0';
        i += 2;
        nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        cdr[i - nj] = '\0';
        arborizare(cst, p -> st);
        arborizare(cmij, p -> mij);
        arborizare(cdr, p -> dr);
    }
    else
    if(s[0] == 'e' && s[1] == 'x' && s[2] == 'p')                                  ///EXPONENT
    {
        strcpy(p -> c, "^");
        char cst[100];
        char cdr[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        cst[i - 4] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        cdr[i - nj] = '\0';
        arborizare(cst, p -> st);
        arborizare(cdr, p -> dr);
    }
    else
    if(s[0] == 'A' && s[1] == '{')                                                 ///ARANJAMENTE
    {
        strcpy(p -> c, "A");
        char cst[100];
        char cdr[100];
        unsigned int i = 2;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 2] = s[i];
            i++;
        }
        cst[i - 2] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        cdr[i - nj] = '\0';
        arborizare(cst, p -> st);
        arborizare(cdr, p -> dr);
    }
    else
    if(s[0] == 'C' && s[1] == '{')                                                 ///COMBINARI
    {
        strcpy(p -> c, "C");
        char cst[100];
        char cdr[100];
        unsigned int i = 2;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 2] = s[i];
            i++;
        }
        cst[i - 2] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        cdr[i - nj] = '\0';
        arborizare(cst, p -> st);
        arborizare(cdr, p -> dr);
    }
    else
    if(s[0] == 's' && s[1] == 'i' && s[2] == 'n')                                  ///SINUS
    {
        strcpy(p->c, "sin");
        char cst[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        cst[i - 4] = '\0';
        arborizare(cst, p->st);
    }
    else
    if(s[0] == 'c' && s[1] == 'o' && s[2] == 's')                                  ///COSINUS
    {
        strcpy(p->c, "cos");
        char cst[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        cst[i - 4] = '\0';
        arborizare(cst, p->st);
    }
    else
    if(s[0] == 'c' && s[1] == 't' && s[2] == 'g')                                  ///COTANGENTA
    {
        strcpy(p->c, "ctg");
        char cst[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        cst[i - 4] = '\0';
        arborizare(cst, p->st);
    }
    else
    if(s[0] == 't' && s[1] == 'g')                                                 ///TANGENTA
    {
        strcpy(p->c, "tg");
        char cst[100];
        unsigned int i = 3;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 3] = s[i];
            i++;
        }
        cst[i - 3] = '\0';
        arborizare(cst, p->st);
    }
    else
    if(s[0] == 'l' && s[1] == 'n')                                                 ///LOGARITM NATURAL
    {
        strcpy(p->c, "ln");
        char cst[100];
        unsigned int i = 3;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 3] = s[i];
            i++;
        }
        cst[i - 3] = '\0';
        arborizare(cst, p->st);
    }
    else
    if(s[0] == 'l' && s[1] == 'g')                                                 ///LOGARITM ZECIMAL
    {
        strcpy(p->c, "lg");
        char cst[100];
        unsigned int i = 3;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 3] = s[i];
            i++;
        }
        cst[i - 3] = '\0';
        arborizare(cst, p->st);
    }
    else
    if(s[0] == 'l' && s[1] == 'o' && s[2] == 'g')                                  ///LOGARITM IN BAZA B
    {
        strcpy(p -> c, "log");
        char cst[100];
        char cdr[100];
        unsigned int i = 4;
        int nrparanteze = 0;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cst[i - 4] = s[i];
            i++;
        }
        cst[i - 4] = '\0';
        i += 2;
        unsigned int nj = i;
        while(!(s[i] == '}' && nrparanteze == 0))
        {
            if(s[i] == '{')
                nrparanteze++;
            if(s[i] == '}')
                nrparanteze--;
            cdr[i - nj] = s[i];
            i++;
        }
        cdr[i - nj] = '\0';
        arborizare(cst, p -> st);
        arborizare(cdr, p -> dr);
    }
    else
    if(estePS(s))                                                                  ///ARGUMENT SUMA/PRODUS
        strcpy(p -> c, s);
    else
    if(esteNumar(s))                                                               ///NUMAR
        strcpy(p -> c, s);
    else
    if(esteVariabila(s))                                                           ///VARIABILA
    {
        strcpy(p -> c, s);
        bool exista = 0;
        for(int i = 0; i < nrVar && !exista; i++)
            if(!strcmp(variabile[i], s))
                exista = 1;
        if(!exista)
        {
            strcpy(variabile[nrVar], p->c);
            nrVar++;
        }
    }
}

void createButton(int left, int top, int right, int bot, char s[])
{
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    rectangle(left, top, right, bot);
    floodfill(left + 5, top + 5, WHITE);
    setcolor(BLACK);
    setbkcolor(LIGHTGRAY);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy((left + right) / 2, (top + bot) / 2 + 10, s);
    setcolor(WHITE);
    setbkcolor(BLACK);
}

bool esteLiteraGreceasca(char s[])
{
    if(!strcmp(s, "pi"))
        return 1;
    return 0;
}

void literaGreceasca(char s[], int xt, int yt, int xb, int yb, int dim, int heia, int wida)
{
    int xc = (xt + xb) / 2;
    int yc = (yt + yb) / 2;
    if(!strcmp(s, "pi"))
    {

        yt = (yt + yc) / 2;
        int ymin = (yt + yc) / 2;
        int xmin = (xt + xc) / 2;
        int xmax = (xc + xb) / 2;
        int j = xmin;
        setlinestyle(0, 3, 2);
        arc(xmin, ymin, 90, 150, 2*wida/8);
        for(int i = xmin, j = ymin - 2*wida/8; i <= xmax + wida/8; i++)
        {
            putpixel(i, j, WHITE);
            putpixel(i, j + 1, WHITE);
        }
        int primalinie = 5;
        int xcentru = 0;
        if(dim == 10 || dim == 9)
            dim = 5;
        else if(dim == 8)
            primalinie = 8;
        else if(dim == 7)
            primalinie = 9;
        else if(dim == 4)
            primalinie = 12;
        else
            primalinie = 11;
        arc(0, ymin - 2*wida/8, 345 + primalinie, -1, xmin + (xc - xmin) / 4);
        setlinestyle(0, 3, 3);
        for(int i = ymin - 2*wida/8 + 4; i <= yc + 2*dim; i++)
        {
            putpixel(xc + (xmax - xc) / 4, i, WHITE);
            putpixel(xc + (xmax - xc) / 4 + 1, i, WHITE);
        }
        int dist = xb - (xmax - xc) / 4;
        setlinestyle(0, 3, 2);
        arc(xc + (xmax - xc) / 4 + (xb - xmax + (xmax - xc) / 4) / 2, yc + 2*dim, 180, -45, (xb - xmax + (xmax - xc) / 4) / 2);
    }
}

int verifyClick(int left, int top, int right, int bottom, int mX, int mY)
{
    return (mX >= left && mX <= right && mY >= top && mY <= bottom);
}

void text()
{
    setcolor(BROWN);
    rectangle(100, 170, 900, 570);
    setfillstyle(SOLID_FILL, BROWN);
    floodfill(500, 500, BROWN);
    setcolor(BLACK);
    setbkcolor(BROWN);
    settextstyle(8, 0, 3);
    settextjustify(LEFT_TEXT, CENTER_LINE);
    int x = 110;
    outtextxy(x, 180, "Pentru fractie => frac{nrt}{num};");
    outtextxy(x, 205, "Pentru modul => abs{};");
    outtextxy(x, 230, "Pentru factorial => fact{};");
    outtextxy(x, 255, "Pentru Aranjamente de n cate k => A{n}{k};");
    outtextxy(x, 280, "Pentru Combinari de n cate k => C{n}{k};");
    outtextxy(x, 305, "Pentru radacina patrata a lui n => sqrt{n};");
    outtextxy(x, 330, "Pentru radacina de ordin k a lui n => sqrt[k]{n};");
    outtextxy(x, 355, "Pentru suma de la i la n => sum[i][n]{};");
    outtextxy(x, 380, "Pentru produs de la i la n => prod[i][n]{};");
    outtextxy(x, 405, "Pentru scrierea unui indice => _i");
    outtextxy(x, 430, "Pentru log in baza a din b => log{a}{b}");
    outtextxy(x, 455, "Pentru sin, cos, tg, ctg, lg si ln => fct{x};");
}

int width(nod* p, int dim)
{
    if(p == NULL)
        return 0;
    settextstyle(8, 0, dim);
    if(!strcmp(p->c, "/"))
        return max(width(p->st, dim - 2), width(p->dr, dim - 2));
    if(!strcmp(p->c, "<=") || !strcmp(p->c, ">="))
        return width(p->st, dim) + width(p->dr, dim) + textwidth(">");
    if(!strcmp(p->c, "|"))
        return width(p->st, dim) + dim + 10;
    if(!strcmp(p->c, "$"))
        return width(p->st, dim) + textwidth(p->c);
    if(!strcmp(p->c, "#"))
        return width(p->dr, dim) + max(textwidth(p->c), width(p->st, max(dim - 3, 1)));
    if(esteLiteraGreceasca(p->c))
        return textwidth("A");
    if(!strcmp(p->c, "^") || !strcmp(p->c, "_"))
    {
        int n = width(p->st, dim) + width(p->dr, max(dim - 3, 1));
        return n;
    }
    if(!strcmp(p->c, "A") || !strcmp(p->c, "C"))
    {
        int n = textwidth("A") + max(width(p->st, max(dim - 3, 1)), width(p->dr, max(dim - 3, 1)));
        return n;
    }
    if(!strcmp(p->c, "sin") || !strcmp(p->c, "cos") || !strcmp(p->c, "tg") || !strcmp(p->c, "ctg") || !strcmp(p->c, "ln") || !strcmp(p->c, "lg"))
        return textwidth(p->c) + width(p->st, dim) + 2 * textwidth("(");
    if(!strcmp(p->c, "log"))
        return textwidth(p->c) + width(p->st, max(dim - 3, 1)) + width(p->dr, dim) +  2 * textwidth("(");
    if(esteVariabila(p->c) && strchr(p->c, '_'))
    {
        settextstyle(8, 0, dim);
        char variabila[50], indice[50];
        strncpy(variabila, p->c, strlen(p->c) - strlen(strchr(p->c, '_')));
        variabila[strlen(p->c) - strlen(strchr(p->c, '_'))] = '\0';
        int wid = textwidth(variabila);
        strcpy(indice, strchr(p->c, '_') + 1);
        settextstyle(8, 0, dim - 3);
        int widind = textwidth(indice);
        settextstyle(8, 0, dim);
        return wid + widind;
    }
    if(!strcmp(p->c, "S") || !strcmp(p->c, "P"))
    {
        return width(p->dr, dim) + textwidth("a") / 4 + width(p->st, max(dim - 6, 1));
    }
    return textwidth(p->c) + width(p->st, dim) + width(p->dr, dim) + width(p->mij, dim);
}

int height(nod* p, int dim)
{
    if(p == NULL)
        return 0;
    settextstyle(8, 0, dim);
    if(!strcmp(p->c, "/"))
        return height(p->st, dim - 2) + height(p->dr, dim - 2) + dim * 9 / 2;
    if(!strcmp(p->c, "^"))
        return height(p->st, dim) + height(p->dr, max(dim - 3, 1));
    if(!strcmp(p->c, "S") || !strcmp(p->c, "P"))
        return textheight(p->c) + height(p->mij, dim);
    if(!strcmp(p->c, "$") || !strcmp(p->c, "#"))
        return dim + height(p->st, dim);
    if(!strcmp(p->c, "|"))
        return dim + height(p->st, dim);
    if(!strcmp(p->c, "A") || !strcmp(p->c, "C"))
    {
        int n = textheight("A") + height(p->st, max(dim - 3, 1));
        return n;
    }
    if(!strcmp(p->c, "log"))
    {
        int n = textheight("log") + height(p->st, max(dim - 3, 1));
        return n;
    }
    if(esteVariabila(p->c) && strchr(p->c, '_'))
        return textheight(p->c);
    if(!strcmp(p->c, "S") || !strcmp(p->c, "P"))
        return height(p->dr, dim) + 2 * height(p->st, max(dim - 6, 1));
    int hei = max(height(p->st, dim), textheight(p->c));
    hei = max(hei, height(p->dr, dim));
    return max(hei, height(p->mij, dim));
}

double charToNumber(char s[])
{
    double nr = 0;
    int n = strlen(s), p = 0;
    for(int i = 0; i < n; i++)
    {
        if(s[i] != ',' && s[i] != '.')
        {
            nr = nr * 10 + (s[i] - '0');
            p *= 10;
        }
        else
            p = 1;
    }
    if(p != 0)
        nr = nr / p;
    return nr;
}

char orez[100];

void NumberToChar(double nr)
{
    bool mi = 0;
    char fr[100], rez[100];
    if(nr < 0)
    {
        mi = 1;
        nr = nr * (-1);
    }
    unsigned int i = 0, n = 0, iz = 0;
    double f = double(nr) - int(nr);
    int nr1 = int(nr);
    char c;
    if(f != 0)
    {
        while(double(f) - int(f) != 0 && iz < 7)
        {
            f = f * 10;
            fr[iz++] = char(int(f) % 10 + '0');
        }
        fr[iz] = '\0';
    }
    if(nr1 == 0)
        rez[n++] = '0';
    while(nr1)
    {
        rez[n++] = char(int(nr1) % 10 + '0');
        nr1 /= 10;
    }
    for(i = 0; i < n / 2; i++)
    {
        c = rez[i];
        rez[i] = rez[n - i - 1];
        rez[n - i - 1] = c;
    }
    rez[n] = '\0';
    if(f)
    {
        strcat(rez, ",");
        strcat(rez, fr);
    }
    if(mi)
    {
        strcpy(fr, rez);
        strcpy(rez, "-");
        strcat(rez, fr);
    }
    n = strlen(rez) - 1;
    if(rez[n] == '0' && f)
    {
        iz = 1;
        n--;
        while(rez[n] == '0')
            n--;
        rez[n + 1] = '\0';
    }
    settextstyle(8, 0, 4);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(WHITE);
    strcpy(orez, rez);
}

void Inlocuire(nod* &p, char s[], char val[])
{
    if(p != NULL)
    {
        if(!strcmp(s, p->c))
            strcpy(p->c, val);
        Inlocuire(p->st, s, val);
        Inlocuire(p->mij, s, val);
        Inlocuire(p->dr, s, val);
    }
}

double evalExp(nod* p, int val)
{
    if(p != NULL)
    {
        if(!esteNumar(p->c))
        {
            if(!strcmp(p->c, "+"))
                return evalExp(p->st, val) + evalExp(p->dr, val);
            if(!strcmp(p->c, "-"))
                return evalExp(p->st, val) - evalExp(p->dr, val);
            if(!strcmp(p->c, "*"))
                return evalExp(p->st, val) * evalExp(p->dr, val);
            if(!strcmp(p->c, "/") || !strcmp(p->c, ":"))
                return evalExp(p->st, val) / evalExp(p->dr, val);
            if(!strcmp(p->c, "^"))
                return pow(evalExp(p->st, val), evalExp(p->dr, val));
            if(!strcmp(p->c, "|"))
                return abs(evalExp(p->st, val));
            if(!strcmp(p->c, "!"))
                return fact(evalExp(p->st, val));
            if(!strcmp(p->c, "$"))
                return sqrt(evalExp(p->st, val));
            if(!strcmp(p->c, "#"))
                return pow(evalExp(p->dr, val), 1 / evalExp(p->st, val));
            if(!strcmp(p->c, "sin"))
                return sin(evalExp(p->st, val) * PI / 180);
            if(!strcmp(p->c, "cos"))
                return cos(evalExp(p->st, val) * PI / 180);
            if(!strcmp(p->c, "tg"))
                return tan(evalExp(p->st, val) * PI / 180);
            if(!strcmp(p->c, "ctg"))
                return 1 / tan(evalExp(p->st, val) * PI / 180);
            if(!strcmp(p->c, "lg"))
                return log10(evalExp(p->st, val));
            if(!strcmp(p->c, "ln"))
                return log(evalExp(p->st, val));
            if(!strcmp(p->c, "log"))
                return log10(evalExp(p->dr, val)) / log10(evalExp(p->st, val));
            if(!strcmp(p->c, "A"))
                return aranjamente(evalExp(p->st, val), evalExp(p->dr, val));
            if(!strcmp(p->c, "C"))
                return combinari(evalExp(p->st, val), evalExp(p->dr, val));
            if(!strcmp(p->c, "i"))
                return val;
            if(!strcmp(p->c, "S"))
            {
                double sum = 0;
                double start = charToNumber(strchr(p->st->c, '=') + 1);
                double finish = charToNumber(p->mij->c);
                for(int i = (int)start; i <= (int)finish; i++)
                    sum += evalExp(p->dr, i);
                return sum;
            }
            if(!strcmp(p->c, "P"))
            {
                double prod = 1;
                double start = charToNumber(strchr(p->st->c, '=') + 1);
                double finish = charToNumber(p->mij->c);
                for(int i = (int)start; i <= (int)finish; i++)
                    prod *= evalExp(p->dr, i);
                return prod;
            }
        }
        return charToNumber(p->c);
    }
}

void desen(int dim, int xt, int yt, int xb, int yb, nod* p)
{
    if(p != NULL)
    {
        settextstyle(8, 0, dim);
        int lungime, lst, ldr, wida, heia;
        wida = textwidth("a");
        heia = textheight("a");
        if(xt == 0 && xb == lungimeaFerestrei)
        {
            int lungimeEc = width(p, dim), inaltimeEc = height(p, dim);
            xt = (lungimeaFerestrei - lungimeEc) / 2;
            xb = xt + lungimeEc;
            yt = (800 - inaltimeEc) / 2;
            yb = yt + inaltimeEc;
        }
        if(esteNumar(p->c))                 ///NUMAR
        {
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(8, 0, dim);
            outtextxy((xt + xb) / 2, (yt + yb) / 2 + heia / 4, p->c);
        }
        else if(estePS(p->c))               ///ARGUMENT SUMA/PRODUS
        {
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(8, 0, dim);
            outtextxy((xt + xb) / 2, (yt + yb) / 2 + heia / 4, p->c);
        }
        else if(!strcmp(p->c, "+") || !strcmp(p->c, "-") || !strcmp(p->c, "*") || !strcmp(p->c, ":") ||
                !strcmp(p->c, "<") || !strcmp(p->c, ">") || !strcmp(p->c, "<=") || !strcmp(p->c, ">=")
                || !strcmp(p->c, "=")) ///SEMN
        {
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(8, 0, dim);
            int widst, widdr;
            widst = width(p->st, dim);
            widdr = width(p->dr, dim);
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(8, 0, dim);
            if(!strcmp(p->c, "<=") || !strcmp(p->c, ">="))
            {
                if(!strcmp(p->c, "<="))
                    outtextxy(xt + widst + wida / 2, (yt + yb) / 2 + heia / 4, "<");
                else
                    outtextxy(xt + widst + wida / 2, (yt + yb) / 2 + heia / 4, ">");
                line(xt + widst + wida / 2 - 32, yb - heia / 3, xt + widst + wida / 2 + 32, yb - heia / 3);
            }
            else
                outtextxy(xt + widst + wida / 2, (yt + yb) / 2 + heia / 4, p->c);
            desen(dim, xt, yt, xt + widst, yb, p->st);
            desen(dim, xt + widst + wida, yt, xb, yb, p->dr);
        }
        else if(!strcmp(p->c, "/"))         ///FRACTIE
        {
            int a = xt, b = xb;
            dim-=2;
            int dim1 = dim, lungime1, lungime2, xt1, xt2, xb1, xb2;
            settextstyle(8, 0, dim);
            lungime1 = width(p->st, dim);
            settextstyle(8, 0, dim);
            lungime2 = width(p->dr, dim);
            settextstyle(8, 0, dim);
            lungime = max(lungime1, lungime2);
            xt = (a + b) / 2 - lungime / 2;
            xb = (a + b) / 2 + lungime / 2;
            xt1 = (a + b) / 2 - lungime1 / 2;
            xb1 = (a + b) / 2 + lungime1 / 2;
            xt2 = (a + b) / 2 - lungime2 / 2;
            xb2 = (a + b) / 2 + lungime2 / 2;
            desen(dim, xt1, yt, xb1, (yt + yb) / 2 - dim1 * 9 / 4, p->st);
            desen(dim, xt2, (yt + yb) / 2 + dim1*10/4, xb2, yb, p->dr);
            setlinestyle(0, 3, dim/2);
            line(xt, (yt + yb) / 2, xb, (yt + yb) / 2);
        }
        else if(!strcmp(p->c, "^"))         ///EXPONENT
        {
            int yc = (yb + yt) / 2;
            int dim1 = dim;
            settextstyle(8, 0, dim);
            int wid = width(p->st, dim);
            int hei = height(p->st, dim);
            int heiexp = height(p->dr, max(dim - 3, 1));
            int widexp = width(p->dr, max(dim - 3, 1));
            yt = yc - (hei + heiexp) / 2;
            yb = yt + hei + heiexp;
            dim = dim1;
            settextstyle(8, 0, dim);
            desen(dim, xt - dim, yt + heiexp/2, xt + wid, yb, p->st);
            settextstyle(8, 0, max(dim - 3, 1));
            desen(max(dim - 3, 1), xt + wid, yt + heiexp / 2, xb, yt + heiexp, p->dr);
        }
        else if(!strcmp(p->c, "|"))         ///MODUL
        {
            int dim1 = dim;
            xb -= 10;
            desen(dim, xt, yt, xb - dim, yb, p->st);
            dim = dim1;
            int wid = width(p->st, dim);
            dim = dim1;
            int hei = height(p->st, dim);
            dim = dim1;
            int nxt = xt + ((xb - xt) / 2) - wid / 2 + 1;
            int nyt = yt + ((yb - yt) / 2) - hei / 2 + 1;
            int nxb = xt + ((xb - xt) / 2) + wid / 2 - 1;
            int nyb = yt + ((yb - yt) / 2) + hei / 2 - 1;
            setlinestyle(0, 3, dim1 / 2);
            line(nxt - 5, nyt - 5, nxt - 5, nyb - 5);
            line(nxb + 5, nyb - 5, nxb + 5, nyt - 5);
        }
        else if(!strcmp(p->c, "S"))         ///SUMA DE LA i LA n
        {
            int dim1 = dim;
            int yt1 = yt, yb1 = yb;
            setlinestyle(0, 3, 3);
            settextstyle(8, 0, max(dim - 6, 1));
            int wid = textwidth(p->st->c);
            dim = dim1;
            settextstyle(8, 0, max(dim - 6, 1));
            int hei = textwidth(p->st->c);
            yt1 += hei;
            yb1 -= hei;
            line(xt, yt1, xt + wid, yt1);
            line(xt, yb1, xt + wid, yb1);
            int ym = (yt + yb) / 2;
            dim = dim1;
            int xm = xt + wid;
            line(xt, yt1, xm - 2 * dim, ym);
            line(xm - 2 * dim, ym, xt, yb1);
            settextstyle(8, 0, max(dim - 6, 1));
            dim = max(dim1 - 6, 1);
            desen(dim, xt, yt, xm, yt1, p->mij);
            nrVar--;
            desen(dim, xt, yb1, xm, yb, p->st);
            dim = dim1;
            desen(dim, xm + wida / 4, yt1, xb, yb1, p->dr);
        }
        else if(!strcmp(p->c, "P"))         ///PRODUS DE LA i LA n
        {
            int dim1 = dim;
            int yt1 = yt, yb1 = yb;
            setlinestyle(0, 3, 3);
            settextstyle(8, 0, max(dim - 6, 1));
            int wid = textwidth(p->st->c);
            dim = dim1;
            settextstyle(8, 0, max(dim - 6, 1));
            int hei = textwidth(p->st->c);
            yt1 += hei;
            yb1 -= hei;
            line(xt, yt1, xt + wid, yt1);
            line(xt + wid/8, yt1, xt + wid/8, yb1);
            line(xt + wid - wid/8, yt1, xt + wid - wid/8, yb1);
            dim = dim1;
            int xm = xt + wid;
            settextstyle(8, 0, max(dim - 6, 1));
            dim = max(dim1 - 6, 1);
            nrVar--;
            desen(dim, xt, yt, xm, yt1, p->mij);
            desen(dim, xt, yb1, xm, yb, p->st);
            dim = dim1;
            desen(dim, xm + wida / 4, yt1, xb, yb1, p->dr);
        }
        else if(!strcmp(p->c, "$"))         ///RADICAL
        {
            desen(dim, xt + wida, yt, xb, yb, p->st);
            int hei = height(p->st, dim);
            yt = (yt + yb) / 2 - hei / 2;
            yb = yt + hei;
            setlinestyle(0, 3, 2);
            line(xt + wida - dim/2 - dim / 4, yt - dim/2, xb, yt - dim/2);
            line(xt + wida - dim/2 - dim / 4, yt - dim/2, xt + wida - wida / 4, yb);
            line(xt + wida - wida / 4, yb, xt + wida / 2, (yb + yt) / 2);
            line(xt + wida / 2, (yb + yt) / 2, xt + wida / 2 - dim, (yb + yt) / 2 + dim * 2);
        }
        else if(!strcmp(p->c, "#"))         ///RADICAL DE ORDIN n
        {
            int dim1 = dim;
            desen(dim, xt + wida, yt, xb, yb, p->dr);
            dim = dim1;
            int hei = height(p->st, dim);
            yt = (yt + yb) / 2 - hei / 2;
            yb = yt + hei;
            setlinestyle(0, 3, 2);
            dim = dim1;
            settextstyle(8, 0, dim - 4);
            hei = textheight(p->st->c);
            desen(dim - 4, xt + wida / 3, yt, xt + wida / 3 + wida / 2, yt + hei / 2, p->st);
            line(xt + wida - dim/2, yt - dim/2, xb + 5, yt - dim/2);
            line(xt + wida - dim/2, yt - dim/2, xt + wida - wida / 4, yb);
            line(xt + wida - wida / 4, yb, xt + wida / 2, (yb + yt) / 2);
            line(xt + wida / 2, (yb + yt) / 2, xt + wida / 2 - dim, (yb + yt) / 2 + dim * 2);
        }
        else if(!strcmp(p->c, "sin") || !strcmp(p->c, "cos") || !strcmp(p->c, "tg") || !strcmp(p->c, "ctg")
                 || !strcmp(p->c, "ln") || !strcmp(p->c, "lg")) ///FUNCTIE
        {
            int dim1 = dim;
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(8, 0, dim);
            int wid = textwidth(p->c), lung;
            lung = width(p, dim) - textwidth("(");
            if(!strcmp(p->st->c, "^"))
                lung += textwidth("(");
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(8, 0, dim);
            outtextxy(xt + wid / 2, (yt + yb) / 2 + heia / 4, p->c);
            outtextxy(xt + wid + wida/2, (yt + yb) / 2 + heia / 4, "(");
            desen(dim, xt + wid + wida, yt, xt + lung, yb, p->st);
            dim = dim1;
            settextstyle(8, 0, dim);
            outtextxy(xt + lung + wida / 2, (yt + yb) / 2 + heia / 4, ")");
        }
        else if(!strcmp(p->c, "log"))                           ///LOGARITM IN BAZA B
        {
            int dim1 = dim;
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(8, 0, dim);
            int wid = textwidth(p->c), lung;
            int heimic = height(p->st, max(dim - 3, 1));
            int widmic = width(p->st, max(dim - 3, 1));
            lung = width(p, dim) - textwidth("(");
            if(!strcmp(p->st->c, "^"))
                lung += textwidth("(");
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(8, 0, dim);
            outtextxy(xt + wid / 2, (yt + yb) / 2 + heia / 4, p->c);
            outtextxy(xt + wid + widmic + wida/2, (yt + yb) / 2 + heia / 4, "(");
            desen(dim, xt + wid + wida + widmic, yt, xt + lung, yb, p->dr);
            dim = dim1;
            settextstyle(8, 0, dim);
            outtextxy(xt + lung + wida / 2, (yt + yb) / 2 + heia / 4, ")");
            settextstyle(8, 0, max(dim - 3, 1));
            outtextxy(xt + wid + widmic / 2, yb - heimic / 2 + heimic / 4, p->st->c);
            settextstyle(8, 0, dim);
        }

        else if(!strcmp(p->c, "A") || !strcmp(p->c, "C"))         ///ARANJAMENTE + COMBINARI
        {
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(8, 0, dim);
            outtextxy(xt + wida / 2, (yt + yb) / 2 + heia / 4, p->c);
            int yc = (yb + yt) / 2;
            int dim1 = dim;
            settextstyle(8, 0, dim);
            int wid = width(p->st, dim);
            int hei = height(p->st, dim);
            int heimic = height(p->dr, max(dim - 3, 1));
            int widmic = max(width(p->dr, max(dim - 3, 1)), width(p->st, max(dim - 3, 1)));
            yt = yc - (hei + heimic) / 2;
            yb = yt + hei + heimic;
            dim = dim1;
            settextstyle(8, 0, max(dim - 3, 1));
            outtextxy(xt + wida + widmic / 2, (yt + yb) / 2 + heimic, p->st->c);
            outtextxy(xt + wida + widmic / 2, yt + heimic / 2 + heimic / 4, p->dr->c);
        }
        else if(!strcmp(p->c, "!"))         ///FACTORIAL
        {
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(8, 0, dim);
            desen(dim, xt, yt, xb - wida, yb, p->st);
            outtextxy(((xb - wida) + xb) / 2, (yt + yb) / 2 + heia / 4, "!");;
        }
        else if(esteVariabila(p->c))        ///VARIABILA
        {
            if(strchr(p->c, '_'))
            {
                char variabila[50], indice[50];
                strncpy(variabila, p->c, strlen(p->c) - strlen(strchr(p->c, '_')));
                variabila[strlen(p->c) - strlen(strchr(p->c, '_'))] = '\0';
                strcpy(indice, strchr(p->c, '_') + 1);
                int dim1 = dim;
                settextstyle(8, 0, dim - 3);
                int widind = textwidth(indice);
                int heiind = textheight(indice);
                settextjustify(CENTER_TEXT, CENTER_TEXT);
                dim = dim1;
                settextstyle(8, 0, dim);
                int wid = textwidth(variabila);
                int hei = textheight(variabila);
                xb = xb - widind;
                outtextxy((xt + xb) / 2, (yt + yb) / 2 + heia / 4, variabila);
                settextstyle(8, 0, dim - 3);
                xt = xt + wid;
                outtextxy((xt + xb + widind) / 2, (yt + yb) / 2 + heiind - heiind / 4, indice);
            }
            else
            {
                if(esteLiteraGreceasca(p->c))
                    literaGreceasca(p->c, xt, yt, xb, yb, dim, heia, wida);
                else
                {
                    settextjustify(CENTER_TEXT, CENTER_TEXT);
                    settextstyle(8, 0, dim);
                    outtextxy((xt + xb) / 2, (yt + yb) / 2 + heia / 4, p->c);
                }
            }
        }
    }
}

void ecuatii()
{
    char inputbuf[300] = "";
    int input_pos = 0;
    cleardevice();
    setcolor(LIGHTGRAY);
    readimagefile("images/ecuatii.jpg", 0, 0, 1000, 600);
    rectangle(0, 0, 1000, 75);
    floodfill(1, 1, LIGHTGRAY);
    setbkcolor(BLACK);
    text();
    settextstyle(8, 0, 5);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextjustify(LEFT_TEXT, CENTER_TEXT);
    int the_end = 0;
    int x = 10, y = 45;
    int p = 0;
    bool ok = true;
    char c;
    do
    {
       outtextxy(x, y, inputbuf + p);
       c = getch();
       switch(c)
       {
            case 8: /* backspace */
              if (input_pos)
              {
                 input_pos--;
                 inputbuf[input_pos] = ' ';
              }
              break;
            case 13: /* return */
              the_end = 1;
              break;
            case 27: /* Escape = Abort */
              inputbuf[0] = 0;
              the_end = 1;
              break;
            default:
              if (input_pos < 299 && c >= ' ' && c <= '~')
              {
                 inputbuf[input_pos] = c;
                 input_pos++;
                 inputbuf[input_pos] = 0;
              }
       }
       if(strlen(inputbuf) > 36 && ok)
       {
           ok = false;
           setcolor(BLACK);
           setbkcolor(LIGHTGRAY);
           rectangle(-1, 75, 1000, 150);
           setfillstyle(SOLID_FILL, LIGHTGRAY);
           floodfill(-1, 75, LIGHTGRAY);
           setcolor(LIGHTGRAY);
           floodfill(1, 76, BLACK);
           line(0, 75, 1000, 75);
           setcolor(BLACK);
           p = 36;
           x = 10;
           y = 120;
       }
    }while(!the_end);
    if(inputbuf[input_pos] != NULL)
        inputbuf[input_pos] = NULL;
    nod *arb;
    bool ecorecta = 1;
    char inputbuf2[300];
    input_pos = 0;
    for(unsigned int i = 0; inputbuf[i]; i++)
        if(inputbuf[i] != ' ')
            inputbuf2[input_pos++] = inputbuf[i];
    inputbuf2[input_pos] = '\0';
    if(expresieCorecta1(inputbuf2))
    {
        arborizare(inputbuf2, arb);
        lungimeaFerestrei = max(width(arb, 10), 800);
    }
    else
    {
        ecorecta = 0;
        arb = NULL;
        lungimeaFerestrei = 800;
    }
    initwindow(lungimeaFerestrei, 800, "Desen", 10, 10);
    setlinestyle(0, 0, 3);
    line(0, 100, lungimeaFerestrei, 100);
    line(lungimeaFerestrei/2, 100, lungimeaFerestrei/2, 0);
    settextstyle(8, 0, 3);
    setcolor(WHITE);
    createButton(25, 25, 375, 75, "Evalueaza");
    ok = 0;
    settextstyle(8, 0, 5);
    if(ecorecta)
        desen(10, 0, 0, lungimeaFerestrei, 800, arb);
    else
    {
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        settextstyle(8, 0, 5);
        outtextxy(400, 400, "Expresie gresita.");
    }
    int var = -1;
    while(var < nrVar)
    {
        char inputbuf3[50] = "           ";
        char text[100] = "Valoarea lui ";
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(verifyClick(25, 25, 375, 75, x, y) && var + 1 < nrVar)
        {
            if(!strcmp(variabile[var + 1], "e"))
            {
                Inlocuire(arb, "e", "2.718281828");
                var++;
            }
            if(!strcmp(variabile[var + 1], "pi"))
            {
                Inlocuire(arb, "pi", "3.14159265");
                var++;
            }
            if(var + 1 < nrVar)
            {
                strcat(text, variabile[var + 1]);
                strcat(text, ":");
                settextstyle(8, 0, 3);
                settextjustify(RIGHT_TEXT, CENTER_TEXT);
                outtextxy(3*lungimeaFerestrei/4+lungimeaFerestrei/16, 52, text);
                settextjustify(LEFT_TEXT, CENTER_TEXT);
                int i = 3*lungimeaFerestrei/4+lungimeaFerestrei/16+2, j = 52;
                input_pos = 0;
                ok = true;
                the_end = 0;
                do
                {
                    outtextxy(i, j, inputbuf3);
                    c = getch();
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if(verifyClick(25, 25, 375, 75, x, y))
                        c = 13;
                    switch(c)
                   {
                        case 8: /* backspace */
                          if (input_pos)
                          {
                             input_pos--;
                             inputbuf3[input_pos] = ' ';
                          }
                          break;
                        case 13: /* return */
                          the_end = 1;
                          break;
                        case 27: /* Escape = Abort */
                          inputbuf[0] = 0;
                          the_end = 1;
                          break;
                        default:
                          if (input_pos < 299 && c >= ' ' && c <= '~')
                          {
                             inputbuf3[input_pos] = c;
                             input_pos++;
                             inputbuf3[input_pos] = 0;
                          }
                   }
                }while(!the_end);
                if(inputbuf3[input_pos] != NULL)
                    inputbuf3[input_pos] = NULL;
                Inlocuire(arb, variabile[var + 1], inputbuf3);
                settextstyle(8, 0, 5);
                var++;
            }
        }
        else if(verifyClick(25, 25, 375, 75, x, y) && var + 1 == nrVar)
        {
            settextstyle(8, 0, 5);
            settextjustify(RIGHT_TEXT, CENTER_TEXT);
            setcolor(GREEN);
            rectangle(lungimeaFerestrei/2+10, 10, lungimeaFerestrei - 10, 90);
            setfillstyle(SOLID_FILL, BLACK);
            floodfill(lungimeaFerestrei/2+15, 15, GREEN);
            setcolor(BLACK);
            rectangle(lungimeaFerestrei/2+10, 10, lungimeaFerestrei - 10, 90);
            setcolor(WHITE);
            settextjustify(LEFT_TEXT, CENTER_TEXT);
            NumberToChar(evalExp(arb, -1));
            outtextxy(3*lungimeaFerestrei/4+3*lungimeaFerestrei/160, 52, orez);
            var++;
        }
    }
}

void arborizareInec(char s[], nod*&p)
{
    int pos = -1;
    char cst[100], cdr[100], op[5];
    int lenst, lendr;
    nod *q = new nod;
    q->st=NULL;
    q->dr=NULL;
    q->mij=NULL;
    if(strchr(s, '<'))
    {
        op[0] = '<';
        lenst = strlen(s) - strlen(strchr(s, '<'));
        strncpy(cst, s, lenst);
        cst[lenst] = '\0';
        if(strchr(s, '=') != NULL)
        {
            strcpy(cdr, strchr(s, '=') + 1);
            op[1] = '=';
            op[2] = '\0';
        }
        else
        {
            op[1] = '\0';
            strcpy(cdr, strchr(s, '<') + 1);
        }
        strcpy(q->c, op);
    }
    else if(strchr(s, '>'))
    {
        op[0] = '>';
        lenst = strlen(s) - strlen(strchr(s, '>'));
        strncpy(cst, s, lenst);
        cst[lenst] = '\0';
        if(strchr(s, '=') != NULL)
        {
            strcpy(cdr, strchr(s, '=') + 1);
            op[1] = '=';
            op[2] = '\0';
        }
        else
        {
            op[1] = '\0';
            strcpy(cdr, strchr(s, '>') + 1);
        }
        strcpy(q->c, op);
    }
    else if(strchr(s, '='))
    {
        op[0] = '=';
        op[1] = '\0';
        lenst = strlen(s) - strlen(strchr(s, '='));
        strncpy(cst, s, lenst);
        cst[lenst] = '\0';
        strcpy(cdr, strchr(s, '=') + 1);
        strcpy(q->c, op);
    }
    p = q;
    arborizare(cst, p->st);
    arborizare(cdr, p->dr);
}

void inecuatii()
{
    char inputbuf[300] = "";
    int input_pos = 0;
    cleardevice();
    setcolor(LIGHTGRAY);
    readimagefile("images/ecuatii.jpg", 0, 0, 1000, 600);
    rectangle(0, 0, 1000, 75);
    floodfill(1, 1, LIGHTGRAY);
    setbkcolor(BLACK);
    text();
    outtextxy(110, 480, "Pentru inecuatii e necesara utilizarea unui operator");
    outtextxy(110, 505, "de tipul <, >, <=, >=. Evaluand expresia, programul");
    outtextxy(110, 530, "va evidentia valoarea de adevar a inecuatiei.");
    settextstyle(8, 0, 5);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextjustify(LEFT_TEXT, CENTER_TEXT);
    int the_end = 0;
    int x = 10, y = 45;
    int p = 0;
    bool ok = true;
    char c;
    do
    {
       outtextxy(x, y, inputbuf + p);
       c = getch();
       switch(c)
       {
            case 8: /* backspace */
              if (input_pos)
              {
                 input_pos--;
                 inputbuf[input_pos] = ' ';
              }
              break;
            case 13: /* return */
              the_end = 1;
              break;
            case 27: /* Escape = Abort */
              inputbuf[0] = 0;
              the_end = 1;
              break;
            default:
              if (input_pos < 299 && c >= ' ' && c <= '~')
              {
                 inputbuf[input_pos] = c;
                 input_pos++;
                 inputbuf[input_pos] = 0;
              }
       }
       if(strlen(inputbuf) > 36 && ok)
       {
           ok = false;
           setcolor(BLACK);
           setbkcolor(LIGHTGRAY);
           rectangle(-1, 75, 1000, 150);
           setfillstyle(SOLID_FILL, LIGHTGRAY);
           floodfill(-1, 75, LIGHTGRAY);
           setcolor(LIGHTGRAY);
           floodfill(1, 76, BLACK);
           line(0, 75, 1000, 75);
           setcolor(BLACK);
           p = 36;
           x = 10;
           y = 120;
       }
    }while(!the_end);
    if(inputbuf[input_pos] != NULL)
        inputbuf[input_pos] = NULL;
    nod *arb;
    bool ecorecta = 0;
    char inputbuf2[300];
    input_pos = 0;
    for(unsigned int i = 0; inputbuf[i]; i++)
    {
        if(inputbuf[i] != ' ')
            inputbuf2[input_pos++] = inputbuf[i];
        if(inputbuf[i] == '<' || inputbuf[i] == '>' || inputbuf[i] == '=')
            ecorecta = 1;
    }
    inputbuf2[input_pos] = '\0';
    if(ecorecta)
    {
        arborizareInec(inputbuf2, arb);
        lungimeaFerestrei = max(800, width(arb, 10));
    }
    else
    {
        lungimeaFerestrei = 800;
        arb = NULL;
    }
    //afisareArbore(arb);
    initwindow(lungimeaFerestrei, 800, "Desen", 10, 10);
    setlinestyle(0, 0, 3);
    line(0, 100, lungimeaFerestrei, 100);
    line(lungimeaFerestrei/2, 100, lungimeaFerestrei/2, 0);
    settextstyle(8, 0, 3);
    setcolor(WHITE);
    createButton(25, 25, 375, 75, "Evalueaza");
    ok = 0;
    settextstyle(8, 0, 5);
    if(ecorecta)
        desen(10, 0, 0, lungimeaFerestrei, 800, arb);
    else
    {
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        settextstyle(8, 0, 5);
        outtextxy(400, 400, "Expresie gresita.");
    }
    int var = -1;
    while(var < nrVar)
    {
        char inputbuf3[50] = "           ";
        char text[100] = "Valoarea lui ";
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(verifyClick(25, 25, 375, 75, x, y) && var + 1 < nrVar)
        {
            if(!strcmp(variabile[var + 1], "e"))
            {
                Inlocuire(arb, "e", "2.718281828");
                var++;
            }
            if(!strcmp(variabile[var + 1], "pi"))
            {
                Inlocuire(arb, "pi", "3.14159265");
                var++;
            }
            if(var + 1 < nrVar)
            {
                strcat(text, variabile[var + 1]);
                strcat(text, ":");
                settextstyle(8, 0, 3);
                settextjustify(RIGHT_TEXT, CENTER_TEXT);
                outtextxy(3*lungimeaFerestrei/4+lungimeaFerestrei/16, 52, text);
                settextjustify(LEFT_TEXT, CENTER_TEXT);
                int i = 3*lungimeaFerestrei/4+lungimeaFerestrei/16+2, j = 52;
                input_pos = 0;
                ok = true;
                the_end = 0;
                do
                {
                    outtextxy(i, j, inputbuf3);
                    c = getch();
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if(verifyClick(25, 25, 375, 75, x, y))
                        c = 13;
                    switch(c)
                   {
                        case 8: /* backspace */
                          if (input_pos)
                          {
                             input_pos--;
                             inputbuf3[input_pos] = ' ';
                          }
                          break;
                        case 13: /* return */
                          the_end = 1;
                          break;
                        case 27: /* Escape = Abort */
                          inputbuf[0] = 0;
                          the_end = 1;
                          break;
                        default:
                          if (input_pos < 299 && c >= ' ' && c <= '~')
                          {
                             inputbuf3[input_pos] = c;
                             input_pos++;
                             inputbuf3[input_pos] = 0;
                          }
                   }
                }while(!the_end);
                if(inputbuf3[input_pos] != NULL)
                    inputbuf3[input_pos] = NULL;
                Inlocuire(arb, variabile[var + 1], inputbuf3);
                settextstyle(8, 0, 5);
                var++;
            }
        }
        else if(verifyClick(25, 25, 375, 75, x, y) && var + 1 == nrVar)
        {
            settextstyle(8, 0, 5);
            settextjustify(RIGHT_TEXT, CENTER_TEXT);
            setcolor(GREEN);
            rectangle(lungimeaFerestrei/2+10, 10, lungimeaFerestrei - 10, 90);
            setfillstyle(SOLID_FILL, BLACK);
            floodfill(lungimeaFerestrei/2+15, 15, GREEN);
            setcolor(BLACK);
            rectangle(lungimeaFerestrei/2+10, 10, lungimeaFerestrei - 10, 90);
            setcolor(WHITE);
            settextjustify(LEFT_TEXT, CENTER_TEXT);
            if(!strcmp(arb->c, "<"))
                if(evalExp(arb->st, -1) < evalExp(arb->dr, -1))
                    strcpy(orez, "ADEVARAT");
                else
                    strcpy(orez, "FALS");
            else if(!strcmp(arb->c, ">"))
                if(evalExp(arb->st, -1) > evalExp(arb->dr, -1))
                    strcpy(orez, "ADEVARAT");
                else
                    strcpy(orez, "FALS");
            else if(!strcmp(arb->c, "<="))
                if(evalExp(arb->st, -1) <= evalExp(arb->dr, -1))
                    strcpy(orez, "ADEVARAT");
                else
                    strcpy(orez, "FALS");
            else if(!strcmp(arb->c, ">="))
                if(evalExp(arb->st, -1) >= evalExp(arb->dr, -1))
                    strcpy(orez, "ADEVARAT");
                else
                    strcpy(orez, "FALS");
            else if(!strcmp(arb->c, "="))
                if(evalExp(arb->st, -1) == evalExp(arb->dr, -1))
                    strcpy(orez, "ADEVARAT");
                else
                    strcpy(orez, "FALS");
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(8, 0, 5);
            outtextxy(3*lungimeaFerestrei/4+3*lungimeaFerestrei/160, 52, orez);
            var++;
        }
    }
}

void interfata(char s[])
{
    initwindow(1000, 600, "Math", 50, 50);
    cleardevice();
    readimagefile("images/mate.jpg", 0, 100, 1000, 600);
    setcolor(BROWN);
    readimagefile("images/lemn.jpeg", 0, 0, 1000, 100);
    rectangle(200, 150, 800, 550);
    setfillstyle(9, BROWN);
    floodfill(500, 500, BROWN);
    setcolor(WHITE);
    setbkcolor(GREEN);
    outtextxy(210, 145, "MENIU");
    settextstyle(8, 0, 5);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setbkcolor(LIGHTGRAY);
    createButton(300, 170, 700, 270, "ECUATII");
    createButton(300, 300, 700, 400, "INECUATII");
    createButton(300, 430, 700, 530, "IESIRE");
    bool ok = false;
    int x, y;
    while(!ok)
    {
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(verifyClick(300, 430, 700, 530, x, y)) /// IESIRE
        {
            exit(0);
            ok = true;
        }
        else if(verifyClick(300, 170, 700, 270, x, y)) /// ECUATII
        {
            ecuatii();
            ok = true;
        }
        else if(verifyClick(300, 300, 700, 400, x, y)) /// INECUATII
        {
            inecuatii();
            ok = true;
        }
    }
}

int main()
{
    char s[300];
    interfata(s);
    getch();
    closegraph();
    return 0;
}
