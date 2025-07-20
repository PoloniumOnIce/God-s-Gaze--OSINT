#include "UI.h"

void UI::drawCenteredText(HDC hdc, RECT rect, const std::wstring& text, COLORREF color, int fontSize) {
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, color);

    HFONT hFont = CreateFontW(
        fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI"
    );
    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

    DrawTextW(hdc, text.c_str(), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    SelectObject(hdc, oldFont);
    DeleteObject(hFont);
}

void UI::drawButton(HDC hdc, RECT rect, const std::wstring& label, bool hovered) {
    COLORREF borderColor = RGB(211, 211, 211);
    COLORREF textColor = RGB(178, 34, 34); // Rouge sang

    HBRUSH brush = CreateSolidBrush(RGB(45, 45, 45));
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);

    HPEN pen = CreatePen(PS_SOLID, 1, borderColor);
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);

    drawCenteredText(hdc, rect, label, textColor, 16);
}