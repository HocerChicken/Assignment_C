//============================================================================
// Name        : maiantiem.c
// Author      : Nguyen Quoc Thuan
// Version     : 1.0
//============================================================================
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

void ghi_File(float p)
{
	FILE *ghi;
	ghi = fopen("output.out", "w");
	fprintf(ghi, "%.3f", p);
	fclose(ghi);
}

bool snt(int hp)
{
	if (hp < 2)
		return false;
	int i;
	for (i = 2; i <= sqrt(hp); i++)
	{
		if (hp % i == 0)
		{
			return false;
		}
	}
	return true;
}

void kiemtrahp(int d, int s, int hp, float *P1, float *P2)
{
	if (snt(hp))
	{
		*P1 = 1000;
		*P2 = (hp + s) % 1000;
	}
	else
	{
		*P1 = hp;
		*P2 = (hp + d) % 100;
	}
}

int fb(int n)
{
	if (n == 0 || n == 1 || n == 2 || n == 3)
		return n;
	return fb(n - 2) + fb(n - 1);
}

float TH2(int d, int s, float *f, char t[])
{
	float p, g;
	if (s % 6 == 0)
		g = s / 2.0;
	if (s % 6 == 1)
		g = 2.0 * s;
	if (s % 6 == 2)
		g = -(s % 9) * (s % 9) * (s % 9) / 5.0;
	if (s % 6 == 3)
		g = -(s % 30) * (s % 30) + 3.0 * s;
	if (s % 6 == 4)
		g = -s * 1.0;
	if (s % 6 == 5)
		g = -((s % 5) + 5) * (((s % 5) + 5 + 1) / 2.0);
	if (strcmp(t, "Flood") == 0)
	{
		if (s % 6 == 5)
			p = 0.00;
		if (s % 6 == 4)
			p = -0.05;
		if (s % 6 == 0)
			p = -0.10;
		if (s % 6 == 1)
			p = -0.15;
		if (s % 6 == 2)
			p = -0.20;
		if (s % 6 == 3)
			p = -0.25;
	}
	if (strcmp(t, "Storm") == 0)
	{
		if (s % 6 == 5)
			p = 0.05;
		if (s % 6 == 4)
			p = 0.00;
		if (s % 6 == 0)
			p = -0.05;
		if (s % 6 == 1)
			p = -0.10;
		if (s % 6 == 2)
			p = -0.15;
		if (s % 6 == 3)
			p = -0.20;
	}
	if (strcmp(t, "Rain") == 0)
	{
		if (s % 6 == 5)
			p = 0.10;
		if (s % 6 == 4)
			p = 0.05;
		if (s % 6 == 0)
			p = 0.00;
		if (s % 6 == 1)
			p = -0.05;
		if (s % 6 == 2)
			p = -0.10;
		if (s % 6 == 3)
			p = -0.15;
	}
	if (strcmp(t, "Shower") == 0)
	{
		if (s % 6 == 5)
			p = 0.15;
		if (s % 6 == 4)
			p = 0.10;
		if (s % 6 == 0)
			p = 0.05;
		if (s % 6 == 1)
			p = 0.00;
		if (s % 6 == 2)
			p = -0.05;
		if (s % 6 == 3)
			p = -0.10;
	}
	if (strcmp(t, "Drizzle") == 0)
	{
		if (s % 6 == 5)
			p = 0.20;
		if (s % 6 == 4)
			p = 0.15;
		if (s % 6 == 0)
			p = 0.10;
		if (s % 6 == 1)
			p = 0.05;
		if (s % 6 == 2)
			p = 0.00;
		if (s % 6 == 3)
			p = -0.05;
	}
	if (strcmp(t, "Cloudy") == 0)
	{
		if (s % 6 == 5)
			p = 0.25;
		if (s % 6 == 4)
			p = 0.20;
		if (s % 6 == 0)
			p = 0.15;
		if (s % 6 == 1)
			p = 0.10;
		if (s % 6 == 2)
			p = 0.05;
		if (s % 6 == 3)
			p = 0.00;
	}
	*f = (40.0 - (fabs(d - 500.0)) / 20.0 + g) * (1.0 + p);
	return *f;
}

int THDB(int *hp, int d, float P1, float P2)
{
	float p = (d + P1 + P2) / 1000.0;
	if (p > 0.8)
		return 0;
	if (p <= 0.8 && p > 0.6)
		*hp = *hp - 50;
	else if (p <= 0.6 && p > 0.4)
		*hp = *hp - 30;
	else if (p <= 0.4 && p > 0.2)
		*hp = *hp - 20;
	else
		*hp = *hp;
	return *hp;
}

float TH4(int d, int s, float *f)
{
	*f = (-d * s) / 1000.0;
	return *f;
}

int main()
{
	int hp, d, s;
	char t[100];
	float P1 = 0, P2 = 0, p = -1;

	FILE *doc;
	doc = fopen("input.inp", "r");
	fscanf(doc, "%d", &hp);
	fscanf(doc, "%d", &d);
	fscanf(doc, "%d", &s);
	fscanf(doc, "%s", t);
	fclose(doc);

	kiemtrahp(d, s, hp, &P1, &P2);
	float f = 0;
	if (d < 200)
	{
		int i;
		for (i = 0; i < 16; i++)
		{
			if ((d + s) == fb(i))
				TH2(d, s, &f, t);
		}
	}
	else if (d >= 200 && d <= 800)
	{
		if (d >= 200 && d < 300)
		{
			if (THDB(&hp, d, P1, P2) == 0)
				p = 0;
			else
			{
				kiemtrahp(d, s, hp, &P1, &P2);
				TH2(d, s, &f, t);
			}
		}
		else
			TH2(d, s, &f, t);
	}
	else
		TH4(d, s, &f);
	if (p == 0)
		p = 0;
	else if ((hp >= 1 && hp <= 999) && (d >= 1 && d <= 1000) && (s >= 1 && s <= 100) && (strcmp(t, "Flood") == 0 || strcmp(t, "Storm") == 0 || strcmp(t, "Rain") == 0 || strcmp(t, "Shower") == 0 || strcmp(t, "Drizzle") == 0 || strcmp(t, "Cloudy") == 0))
	{
		p = (P1 + P2 * f) / (1000.0 + fabs(P2 * f));
		if (p < 0)
			p = 0;
		if (p > 1)
			p = 1;
	}
	else
		p = -1;
	ghi_File(p);
	return 2020;
}
