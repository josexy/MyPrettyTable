#ifndef _MY_TERMCOLOR_H_
#define _MY_TERMCOLOR_H_

#include <string>
#include "Sign.h"

using std::string;

typedef Color::ForegroundColor CFgColor;
typedef Color::BackgroundColor CBgColor;
typedef Color::ControlCode CCtlCode;

class TermColor {
private:
	string m_strformat;
	bool m_fg_isNone = false;
	bool m_bg_isNone = false;
	bool m_cc_isNone = false;
public:
	TermColor(CFgColor foregroundColor = CFgColor::None,
	          CCtlCode controlCode = CCtlCode::None,
	          CBgColor backgroundColor = CBgColor::None);
	/**
	 * return the prepared string
	 */
	const string& operator()(const string& text) {
		if (!m_fg_isNone) {
			m_strformat.append("m");
		}
		m_strformat.append(text);
		if (!m_fg_isNone) {
			m_strformat.append("\033[0m");
		}
		return m_strformat;
	}
};

#endif