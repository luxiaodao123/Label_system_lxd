#ifndef PROCESS_H
#define PROCESS_H

#include <QWidget>

namespace Ui {
class Process;
}

class Process : public QWidget
{
    Q_OBJECT

public:
    explicit Process(int range, QWidget *parent = 0);

    ~Process();

	void setCurrentValue();

	void setMyRange(int);


private:
    Ui::Process *ui;
	int m_value;
};

#endif // PROCESS_H
