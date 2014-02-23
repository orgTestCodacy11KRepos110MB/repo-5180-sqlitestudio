#ifndef MDIWINDOW_H
#define MDIWINDOW_H

#include <QMdiSubWindow>
#include <QPointer>

class MdiChild;
class MdiArea;

class MdiWindow : public QMdiSubWindow
{
    Q_OBJECT

    public:
        MdiWindow(MdiChild* mdiChild, MdiArea *mdiArea, Qt::WindowFlags flags = 0);
        virtual ~MdiWindow();

        virtual QVariant saveSession();
        virtual bool restoreSession(const QVariant& sessionValue);

        MdiChild* getMdiChild() const;
        void setWidget(MdiChild* value);
        bool restoreSessionNextTime();
        void rename(const QString& title);

    protected:
        void changeEvent(QEvent *event);

    private:
        QPointer<QWidget> lastFocusedWidget;
        MdiArea* mdiArea;
};

#endif // MDIWINDOW_H
