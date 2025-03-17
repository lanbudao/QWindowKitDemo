#ifndef TOPBAR_H
#define TOPBAR_H

#include "windowbar.h"

namespace QWK {
    class TopBar : public WindowBar {
    public:
        explicit TopBar(QWidget *parent = nullptr);

        void setTitle(const QString &title);
    };
}
#endif //TOPBAR_H
