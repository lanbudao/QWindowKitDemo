#ifndef QWK_FRAMELESSWIDGET_P_H
#define QWK_FRAMELESSWIDGET_P_H

#include "../framelesswidget.h"
class QVBoxLayout;
namespace QWK {
    class TopBar;
    class WidgetWindowAgent;
    class FramelessWidgetPrivate : public QObject {
        Q_OBJECT
        Q_DECLARE_PUBLIC(FramelessWidget)
    public:
        explicit FramelessWidgetPrivate(FramelessWidget *q) : q_ptr(q) {}

        void installWindowAgent();

        void loadStyleSheet(FramelessWidget::Theme theme);

    private:
        FramelessWidget *q_ptr = nullptr;
        FramelessWidget::Theme currentTheme = FramelessWidget::Light;
        QWidget *mainWidget = nullptr;
        QVBoxLayout *mainLayout = nullptr;
        QWK::TopBar *topBar = nullptr;
        QWK::WidgetWindowAgent *windowAgent = nullptr;
    };
}
#endif //QWK_FRAMELESSWIDGET_P_H
