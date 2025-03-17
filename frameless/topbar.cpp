#include "topbar.h"
#include "windowbutton.h"

#include <QWKWidgets/widgetwindowagent.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyle>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtCore/QTimer>

static inline void emulateLeaveEvent(QWidget *widget) {
    Q_ASSERT(widget);
    if (!widget) {
        return;
    }
    QTimer::singleShot(0, widget, [widget]() {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        const QScreen *screen = widget->screen();
#else
        const QScreen *screen = widget->windowHandle()->screen();
#endif
        const QPoint globalPos = QCursor::pos(screen);
        if (!QRect(widget->mapToGlobal(QPoint{0, 0}), widget->size()).contains(globalPos)) {
            QCoreApplication::postEvent(widget, new QEvent(QEvent::Leave));
            if (widget->testAttribute(Qt::WA_Hover)) {
                const QPoint localPos = widget->mapFromGlobal(globalPos);
                const QPoint scenePos = widget->window()->mapFromGlobal(globalPos);
                static constexpr const auto oldPos = QPoint{};
                const Qt::KeyboardModifiers modifiers = QGuiApplication::keyboardModifiers();
#if (QT_VERSION >= QT_VERSION_CHECK(6, 4, 0))
                const auto event =
                        new QHoverEvent(QEvent::HoverLeave, scenePos, globalPos, oldPos, modifiers);
                Q_UNUSED(localPos);
#elif (QT_VERSION >= QT_VERSION_CHECK(6, 3, 0))
                const auto event =  new QHoverEvent(QEvent::HoverLeave, localPos, globalPos, oldPos, modifiers);
                Q_UNUSED(scenePos);
#else
                const auto event =  new QHoverEvent(QEvent::HoverLeave, localPos, oldPos, modifiers);
                Q_UNUSED(scenePos);
#endif
                QCoreApplication::postEvent(widget, event);
            }
        }
    });
}

QWK::TopBar::TopBar(QWidget *parent) :
    WindowBar(parent)
{
    Q_ASSERT(parent);
    // Setup title and buttons
    auto titleLabel = new QLabel();
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName(QStringLiteral("win-title-label"));

#ifndef Q_OS_MAC
    auto iconButton = new QWK::WindowButton();
    iconButton->setObjectName(QStringLiteral("icon-button"));
    iconButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto pinButton = new QWK::WindowButton();
    pinButton->setCheckable(true);
    pinButton->setObjectName(QStringLiteral("pin-button"));
    pinButton->setProperty("system-button", true);
    pinButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto minButton = new QWK::WindowButton();
    minButton->setObjectName(QStringLiteral("min-button"));
    minButton->setProperty("system-button", true);
    minButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto maxButton = new QWK::WindowButton();
    maxButton->setCheckable(true);
    maxButton->setObjectName(QStringLiteral("max-button"));
    maxButton->setProperty("system-button", true);
    maxButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto closeButton = new QWK::WindowButton();
    closeButton->setObjectName(QStringLiteral("close-button"));
    closeButton->setProperty("system-button", true);
    closeButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
#endif

#ifndef Q_OS_MAC
    setIconButton(iconButton);
    setPinButton(pinButton);
    setMinButton(minButton);
    setMaxButton(maxButton);
    setCloseButton(closeButton);
#endif

    setTitleLabel(titleLabel);
    setHostWidget(parent);

#ifndef Q_OS_MAC
    connect(this, &QWK::WindowBar::pinRequested, this, [parent, pinButton](bool pin){
        if (parent->isHidden() || parent->isMinimized() || parent->isMaximized() || parent->isFullScreen()) {
            return;
        }
        parent->setWindowFlag(Qt::WindowStaysOnTopHint, pin);
        QTimer::singleShot(100, [parent]() {
            parent->show();
        });
        pinButton->setChecked(pin);
    });
    connect(this, &QWK::WindowBar::minimizeRequested, parent, &QWidget::showMinimized);
    connect(this, &QWK::WindowBar::maximizeRequested, this, [this, parent, maxButton](bool max) {
        if (max) {
            parent->showMaximized();
        } else {
            parent->showNormal();
        }

        // It's a Qt issue that if a QAbstractButton::clicked triggers a window's maximization,
        // the button remains to be hovered until the mouse move. As a result, we need to
        // manually send leave events to the button.
        emulateLeaveEvent(maxButton);
    });
    connect(this, &QWK::WindowBar::closeRequested, parent, &QWidget::close);
#endif
}

void QWK::TopBar::setTitle(const QString &title) {
    auto titleLabel = this->titleLabel();
    if (titleLabel) {
        titleLabel->setText(title);
    }
}
