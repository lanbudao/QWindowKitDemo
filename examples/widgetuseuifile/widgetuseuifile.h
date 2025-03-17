#ifndef QWINDOWKITDEMO_WIDGETUSEUIFILEDEMO_H
#define QWINDOWKITDEMO_WIDGETUSEUIFILEDEMO_H

#include <QtWidgets/QLabel>
#include <QtCore/QTime>

#include "frameless/framelesswidget.h"

class ClockWidget : public QLabel {
public:
    explicit ClockWidget(QWidget *parent = nullptr) : QLabel(parent) {
        startTimer(100);
        setAlignment(Qt::AlignCenter);
    }

    ~ClockWidget() override = default;

protected:
    void timerEvent(QTimerEvent *event) override {
        QLabel::timerEvent(event);
        setText(QTime::currentTime().toString(QStringLiteral("hh:mm:ss")));
    }
};

QT_BEGIN_NAMESPACE
namespace Ui { class WidgetUseUiFile; }
QT_END_NAMESPACE

class WidgetUseUiFile : public QWK::FramelessWidget {
    Q_OBJECT
public:
    explicit WidgetUseUiFile(QWidget *parent = nullptr);

    ~WidgetUseUiFile() override;

private:
    Ui::WidgetUseUiFile *ui;
};


#endif //QWINDOWKITDEMO_WIDGETUSEUIFILEDEMO_H
