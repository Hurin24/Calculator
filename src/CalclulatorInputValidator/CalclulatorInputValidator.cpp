#include "CalclulatorInputValidator.h"

CalclulatorInputValidator::CalclulatorInputValidator(QObject* ptrParent):
                           QObject(ptrParent)
{

}

bool CalclulatorInputValidator::tryAppendText(QString text)
{
    m_text.append(text);
    emit textChanged();

    return true;
}

QString CalclulatorInputValidator::getText()
{
    return m_text;
}

void CalclulatorInputValidator::setText(QString text)
{
    if(m_text != text)
    {
        m_text = text;

        emit textChanged();
    }
}
