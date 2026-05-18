#ifndef CALCLULATOR_INPUT_VALIDATOR_H
#define CALCLULATOR_INPUT_VALIDATOR_H

#include <QObject>
#include <QString>

class CalclulatorInputValidator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)

public:
    CalclulatorInputValidator(QObject* ptrParent = nullptr);

    Q_INVOKABLE bool tryAppendText(QString text);

    QString getText();
    void setText(QString text);

private:
    QString m_text;

signals:
    void textChanged();
};

#endif //CALCLULATOR_INPUT_VALIDATOR_H
