#ifdef WIN32

#ifndef _TERMINAL_COLOR_H_
#define _TERMINAL_COLOR_H_
#include <windows.h>
enum class FColor {
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	White = Red | Green | Blue,
	Black = ~White,
	Yellow = Red | Green,
	Other1 = Red | Blue,
	Other2 = Green | Blue
};
enum class BColor {
	Red = BACKGROUND_RED,
	Green = BACKGROUND_GREEN,
	Blue = BACKGROUND_BLUE,
	White = Red | Green | Blue,
	Black = ~White,
	Yellow = Red | Green,
	Other1 = Red | Blue,
	Other2 = Green | Blue
};
class TerminalColor {
public:
	TerminalColor(bool fg_highlight = false, bool bg_highlight = false) :m_NewConsoleAttribute{ 0 }, m_OldConsoleAttribute{0}{
		m_HConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO scbi;
		::GetConsoleScreenBufferInfo(m_HConsole, &scbi);
		m_OldConsoleAttribute = scbi.wAttributes;

		if (fg_highlight) {
			m_NewConsoleAttribute |= FOREGROUND_INTENSITY;
		}
		if (bg_highlight) {
			m_NewConsoleAttribute |= BACKGROUND_INTENSITY;
		}
	}
	~TerminalColor() {
		this->ResetConsoleColor();
	}
	/**
	 * Set foreground color
	 */
	void SetForegroundColor(FColor foreground_color) {
		m_NewConsoleAttribute |= static_cast<WORD>(foreground_color);
		SetConsoleTextAttribute(m_HConsole, m_NewConsoleAttribute);
	}
	/**
	 * Set background color
	 */
	void SetBackgroundColor(BColor background_color) {
		m_NewConsoleAttribute |= static_cast<WORD>(background_color);
		SetConsoleTextAttribute(m_HConsole, m_NewConsoleAttribute);
	}
	/**
	 * Set the console color by a special value
	 * Such as, 1-254
	 */
	void SetColorbyValue(WORD color_value) {
		m_NewConsoleAttribute = (WORD)color_value;
		SetConsoleTextAttribute(m_HConsole, m_NewConsoleAttribute);
	}
	/**
	 * restore the console color
	 */
	void ResetConsoleColor() {
		SetConsoleTextAttribute(m_HConsole, m_OldConsoleAttribute);
	}
private:
	HANDLE m_HConsole;
	WORD m_OldConsoleAttribute;
	WORD m_NewConsoleAttribute;
};
#endif 

#endif
