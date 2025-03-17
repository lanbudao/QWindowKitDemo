#include "framelesswidget.h"
#include "private/framelesswidget_p.h"
#include "topbar.h"
#include "windowbutton.h"

#include <QWKWidgets/widgetwindowagent.h>
#include <QtCore/QFile>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyle>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets//QVBoxLayout>

namespace QWK {
    void FramelessWidgetPrivate::installWindowAgent() {
        Q_Q(FramelessWidget);

        // Setup window agent
        windowAgent = new QWK::WidgetWindowAgent(q);
        windowAgent->setup(q);

        topBar = new QWK::TopBar(q);

        windowAgent->setTitleBar(topBar);
#ifndef Q_OS_MAC
        windowAgent->setHitTestVisible(topBar->pinButton(), true);
        windowAgent->setSystemButton(QWK::WindowAgentBase::WindowIcon, topBar->iconButton());
        windowAgent->setSystemButton(QWK::WindowAgentBase::Minimize, topBar->minButton());
        windowAgent->setSystemButton(QWK::WindowAgentBase::Maximize, topBar->maxButton());
        windowAgent->setSystemButton(QWK::WindowAgentBase::Close, topBar->closeButton());
#endif

#ifdef Q_OS_MAC
        windowAgent->setSystemButtonAreaCallback([](const QSize &size) {
            static constexpr const int width = 75;
            return QRect(QPoint(size.width() - width, 0), QSize(width, size.height())); //
        });
#endif
        mainWidget = new QWidget(q);
        mainWidget->setObjectName(QStringLiteral("main-widget"));
        mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        mainLayout = new QVBoxLayout();
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);
        mainLayout->addWidget(topBar);
        mainLayout->addWidget(mainWidget);
        q->setLayout(mainLayout);
//    setMenuWidget(topBar);
//    loadStyleSheet(FramelessWidget::Light);
    }

    void FramelessWidgetPrivate::loadStyleSheet(FramelessWidget::Theme theme) {
        Q_Q(FramelessWidget);
        if (!q->styleSheet().isEmpty() && theme == currentTheme)
            return;
        currentTheme = theme;

        if (QFile qss(theme == FramelessWidget::Dark ? QStringLiteral(":/style/dark")
                                                     : QStringLiteral(":/style/light"));
                qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qApp->setStyleSheet(QString::fromUtf8(qss.readAll()));
            Q_EMIT q->themeChanged();
        }
    }

    FramelessWidget::FramelessWidget(QWidget *parent) :
            QWidget(parent), d_ptr(new FramelessWidgetPrivate(this)) {
        setAttribute(Qt::WA_DontCreateNativeAncestors);
        Q_D(FramelessWidget);
        d->installWindowAgent();
    }

    FramelessWidget::FramelessWidget(QSharedPointer<FramelessWidgetPrivate> &d, QWidget *parent) :
            QWidget(parent), d_ptr(d) {
        setAttribute(Qt::WA_DontCreateNativeAncestors);
        d->installWindowAgent();
    }

    QWidget *FramelessWidget::mainWidget() {
        Q_D(FramelessWidget);
        return d->mainWidget;
    }

    void FramelessWidget::setTitle(const QString &title) {
        Q_D(FramelessWidget);
        d->topBar->setTitle(title);
    }

    void FramelessWidget::setTheme(FramelessWidget::Theme theme) {
        Q_D(FramelessWidget);
        d->loadStyleSheet(theme);
    }

    void FramelessWidget::setMenuBar(QMenuBar *menuBar) {
        Q_D(FramelessWidget);
        d->topBar->setMenuBar(menuBar);
    }

    bool FramelessWidget::event(QEvent *event) {
        Q_D(FramelessWidget);
        switch (event->type()) {
            case QEvent::WindowActivate: {
                if (d->topBar) {
                    d->topBar->setProperty("bar-active", true);
                    style()->polish(d->topBar);
                }
                break;
            }

            case QEvent::WindowDeactivate: {
                if (d->topBar) {
                    d->topBar->setProperty("bar-active", false);
                    style()->polish(d->topBar);
                }
                break;
            }

            default:
                break;
        }
        return QWidget::event(event);
    }
}