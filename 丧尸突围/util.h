#pragma once

#include<graphics.h>

#pragma comment(lib,"WINMM.lib")
#pragma comment(lib,"MSIMG32.LIB")

struct Rect {
	int x, y;// ͼƬ�������Ͻ�λ��
	int w, h;// ͼƬ���ο���
};

inline void putimage_ex(IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr) {
	static BLENDFUNCTION blend_func = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };
	AlphaBlend(GetImageHDC(GetWorkingImage()), rect_dst->x, rect_dst->y, rect_dst->w, rect_dst->h,
		GetImageHDC(img), rect_src ? rect_src->x : 0, rect_src ? rect_src->y : 0,
		rect_src ? rect_src->w : img->getwidth(), rect_src ? rect_src->h : img->getheight(), blend_func);
}

// ��תͼƬ
inline void flip_image(IMAGE* src, IMAGE* dst) {
	int w = src->getwidth();
	int h = src->getheight();

	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx_src = y * w + x;
			int idx_dst = y * w + (w - x - 1);
			dst_buffer[idx_dst] = src_buffer[idx_src];
		}
	}
}

// ������Ƶ������
inline void load_audio(LPCTSTR path, LPCTSTR id) {
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("open %s alias %s"), path, id);
	mciSendString(str_cmd, NULL, 0, NULL);
}

// ������Ƶ
inline void play_audio(LPCTSTR id, bool is_loop = false) {
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("play %s %s from 0"), id, is_loop ? _T("repeat") : _T(""));
	mciSendString(str_cmd, NULL, 0, NULL);
}

// ֹͣ������Ƶ
inline void stop_audio(LPCTSTR id) {
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("stop %s"), id);
	mciSendString(str_cmd, NULL, 0, NULL);
}

// ���������
inline int range_random(int min_num, int max_num) {
	return min_num + rand() % (max_num - min_num + 1);
}