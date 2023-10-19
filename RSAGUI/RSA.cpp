#include "RSA.h"

ll gcd(ll x, ll y)//x>y
{
	ll t;
	if (x < y)
	{
		t = x;
		x = y;
		y = x;
	}
	return y == 0 ? x : gcd(y, x % y);
}

int get_random(int start,int end)
{
	// ʹ������豸��Ϊ����
	std::random_device rd;
	// ����һ����������棬ʹ������豸��Ϊ����
	std::mt19937 gen(rd());
	// ����һ�����ȷֲ��������������
	std::uniform_int_distribution<int> dist(start, end);

	// �����������
	int random_number = dist(gen);
	return random_number;
}

ll getD(ll L, ll E)
{
	for (ll D = 2;D <= L;D++)
	{
		if ((E % L) * (D % L) % L == 1)	return D;
	}
}

int getE(ll L)
{
	std::vector<int> arrayE;

	for (int E = 2;E <= L;E++)//EҪ��L���ʣ��Ҳ�����L
	{
		if (gcd(L, E) == 1) arrayE.push_back(E);
	}
	return arrayE[get_random(0, arrayE.size())];
}

const int N = 10000100;
//primes���������������
int primes[N], cnt;
//st[i], iΪ������Ϊfalse����Ϊtrue
bool st[N];
void get_primes(int n)
{
	for (int i = 2; i <= n; i++)
	{
		if (!st[i]) primes[cnt++] = i;
		for (int j = 0; primes[j] <= n / i; j++)
		{
			st[primes[j] * i] = true;
			if (i % primes[j] == 0) break;
		}
	}
}

int p, q, n, L, E, D;
int generate_key()
{
	n = get_random(100,1000);
	get_primes(n);
	p = primes[--cnt];
	cnt = 0;
	n = get_random(100,1000);
	get_primes(n);
	q = primes[--cnt];

	L = (p - 1) * (q - 1);
	
	n = p * q;

	E = getE(L);

	D = getD(L,E);
	return 0;
}

ULL RSAEnc(ULL num, ULL Z, ULL N)//RSA�ӽ���  numΪ���� ZΪָ���� 
{

	ULL ans = 1;
	ULL i = Z;
	while (i > 0)
	{
		if (i & 1)
		{
			ans = ((ans % N) * (num % N)) % N;
		}
		num = ((num % N) * (num % N)) % N;
		i = i >> 1;
	}
	return ans % N;
}
