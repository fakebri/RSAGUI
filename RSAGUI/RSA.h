#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <vector>

typedef unsigned long long ll;

ll getD(ll L, ll E);
int getE(ll L);
int generate_key();

typedef unsigned long long ULL;
ULL RSAEnc(ULL num, ULL Z, ULL N);