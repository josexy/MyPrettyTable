#include "myTermColor.h"

TermColor::TermColor(CFgColor foregroundColor,CCtlCode controlCode,CBgColor backgroundColor)
{
	if (foregroundColor == CFgColor::None) {
		m_fg_isNone = true;
	}
	if (backgroundColor == CBgColor::None) {
		m_bg_isNone = true;
	}
	if (controlCode == CCtlCode::None) {
		m_cc_isNone = true;
	}
	if (!m_fg_isNone) {
		m_strformat.append("\033[");
		m_strformat.append(std::to_string((int)foregroundColor));
		if (!m_bg_isNone) {
			m_strformat.append(";");
			m_strformat.append(std::to_string((int)backgroundColor));
		}
		if (!m_cc_isNone) {
			m_strformat.append(";");
			if (controlCode == CCtlCode::Highlight) {
				m_strformat.append(std::to_string((int)controlCode));
			}
			else if (controlCode == CCtlCode::UnderLine) {
				m_strformat.append(std::to_string((int)controlCode));
			}
			else if (controlCode != CCtlCode::None) {
				m_strformat.append("1;2");
			}
		}
	}
}