#pragma once
#include <Windows.h>
#include <time.h>

extern HBITMAP hw, hs, ha, hd, hf, hb, hh;
extern HDC hdc, hMenDc, hTempDc;
extern int map[40][40];
extern char head;

void initl(int map[40][40],char &head);

void display();

void randfood();

int  move();

