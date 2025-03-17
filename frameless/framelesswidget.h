#ifndef QWK_FRAMELESSWIDGET_H
#define QWK_FRAMELESSWIDGET_H

#include <QWidget>

class QMenuBar;
namespace QWK {
    class FramelessWidgetPrivate;
    class FramelessWidget : public QWidget {
        Q_OBJECT
        Q_DECLARE_PRIVATE(FramelessWidget)
    public:
        enum Theme {
            Dark,
            Light,
        };
        explicit FramelessWidget(QWidget *parent = nullptr);
        template<typename T>
        void setupUi(T *ui) {
            ui->setupUi(mainWidget());
            setTitle(mainWidget()->windowTitle());
        }
        QWidget *mainWidget();

        void setTitle(const QString &title);
        void setTheme(Theme theme);

        void setMenuBar(QMenuBar *menuBar);

    Q_SIGNALS:
        void themeChanged();

    protected:
        explicit FramelessWidget(QSharedPointer<FramelessWidgetPrivate> &d, QWidget *parent = nullptr);
        bool event(QEvent *event) override;
        QSharedPointer<FramelessWidgetPrivate> d_ptr;
    };

}
#endif //QWK_FRAMELESSWIDGET_H
