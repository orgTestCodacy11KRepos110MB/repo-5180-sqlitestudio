#ifndef COLUMNDEFAULTPANEL_H
#define COLUMNDEFAULTPANEL_H

#include "constraintpanel.h"
#include "parser/ast/sqliteconflictalgo.h"
#include "guiSQLiteStudio_global.h"
#include <QWidget>

namespace Ui {
    class ColumnDefaultPanel;
}

class GUI_API_EXPORT ColumnDefaultPanel : public ConstraintPanel
{
        Q_OBJECT

    public:
        explicit ColumnDefaultPanel(QWidget *parent = 0);
        ~ColumnDefaultPanel();

        bool validate();
        bool validateOnly();

    protected:
        void changeEvent(QEvent *e);
        void constraintAvailable();
        void storeConfiguration();

    private:
        void init();
        void readConstraint();
        void updateVirtualSql();
        SqliteExprPtr parseExpression(const QString& sql);

        Ui::ColumnDefaultPanel *ui = nullptr;

    private slots:
        void updateState();
};

#endif // COLUMNDEFAULTPANEL_H
