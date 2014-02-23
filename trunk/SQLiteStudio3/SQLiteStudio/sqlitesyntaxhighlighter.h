#ifndef SQLITESYNTAXHIGHLIGHTER_H
#define SQLITESYNTAXHIGHLIGHTER_H

#include "parser/token.h"
#include "syntaxhighlighterplugin.h"
#include "genericplugin.h"
#include <QSyntaxHighlighter>
#include <QRegularExpression>

class QWidget;

class TextBlockData : public QTextBlockUserData
{
    public:
        struct Parenthesis
        {
            char character;
            int position;
            int operator==(const Parenthesis& other);
        };

        QList<const Parenthesis*> parentheses();
        void insertParenthesis(int pos, char c);
        const Parenthesis* parenthesisForPosision(int pos);

        bool getEndsWithError() const;
        void setEndsWithError(bool value);

        bool getEndsWithQuerySeparator() const;
        void setEndsWithQuerySeparator(bool value);

    private:
        QList<Parenthesis> parData;
        bool endsWithError = false;
        bool endsWithQuerySeparator = false;
};

class SqliteSyntaxHighlighter : public QSyntaxHighlighter
{
        Q_OBJECT
    public:
        enum class State
        {
            STANDARD,
            PARENTHESIS,
            STRING,
            KEYWORD,
            BIND_PARAM,
            BLOB,
            COMMENT,
            NUMBER
        };

        explicit SqliteSyntaxHighlighter(QTextDocument *parent);

        void setSqliteVersion(int version);
        void setFormat(State state, QTextCharFormat format);
        QTextCharFormat getFormat(State state) const;

        void addError(int from, int to, bool limitedDamage = false);
        void clearErrors();
        bool haveErrors();

        void addDbObject(int from, int to);
        void clearDbObjects();

        bool getObjectLinksEnabled() const;
        void setObjectLinksEnabled(bool value);

    protected:
        void highlightBlock(const QString &text);

    private:
        enum class TextBlockState
        {
            REGULAR = -1, // default, the -1 is default of QSyntaxHighlighter
            BLOB,         // x'blob'
            STRING,       // 'string'
            COMMENT,      // /* comment */
            ID_1,         // [id]
            ID_2,         // "id"
            ID_3          // `id`
        };

        struct Error
        {
            Error(int from, int to, bool limitedDamage = false);

            int from;
            int to;
            bool limitedDamage = false; // if it's just an invalid token, but parser dealt with it, mark only this token
        };

        struct DbObject
        {
            DbObject(int from, int to);

            int from;
            int to;
        };

        void setupMapping();

        /**
         * @brief getPreviousStatePrefix Provides prefix for previous block's state.
         * @param textBlockState Previous text block's state.
         * @return Prefix string (if any) for lexer to provide proper tokens according to previous state.
         */
        QString getPreviousStatePrefix(TextBlockState textBlockState);

        /**
         * @brief handleToken Highlights token.
         * @param token Token to handle.
         * @param idxModifier Modifier for text highlighting in case of previous state defined by multi-character token. See getPreviousStatePrefix() for details.
         * @return true if the token is being marked as invalid (syntax error).
         */
        bool handleToken(TokenPtr token, qint32 idxModifier, int errorStart, TextBlockData* currBlockData, TextBlockData* previousBlockData);

        bool isError(int start, int lgt, bool* limitedDamage);
        bool isValid(int start, int lgt);

        /**
         * @brief markUncheckedErrors Marks text as being uncheck for possible errors.
         * @param errorStart Start index of unchecked text.
         * Unchecked text is all text after first error, becuase it could not be parser, therefore could not be checked.
         */
        void markUncheckedErrors(int errorStart, int length);
        void setStateForUnfinishedToken(TolerantTokenPtr tolerantToken);

        /**
         * @brief applyErrorFormat Applies error format properties to given format.
         * @param format Format to apply properties to.
         * @param isError true if error was detected and error format needs to be applied.
         * @param wasError true if there was an error already in previous token.
         */
        void applyErrorFormat(QTextCharFormat& format, bool isError, bool wasError, Token::Type tokenType);

        /**
         * @brief applyValidObjectFormat Applies valid database object format properties to given format.
         * @param format Format to apply properties to.
         * @param isValid true if we're about to mark valid database object
         * @param qtextdisError true if error was detected and error format needs to be applied.
         * @param wasError true if there was an error already in previous token.
         */
        void applyValidObjectFormat(QTextCharFormat& format, bool isValid, bool isError, bool wasError);

        void handleParenthesis(TokenPtr token, TextBlockData* data);

        static const int regulartTextBlockState = static_cast<int>(TextBlockState::REGULAR);
        int sqliteVersion = 3;
        QHash<State,QTextCharFormat> formats;
        QHash<Token::Type,State> tokenTypeMapping;
        QList<Error> errors;
        QList<DbObject> dbObjects;
        bool objectLinksEnabled = false;

    private slots:
        void setupFormats();
};

class SqliteHighlighterPlugin : public GenericPlugin, public SyntaxHighlighterPlugin
{
    Q_OBJECT

    SQLITESTUDIO_PLUGIN
    SQLITESTUDIO_PLUGIN_TITLE("SQL highlighter")
    SQLITESTUDIO_PLUGIN_DESC("SQL (SQLite) syntax highlighter.")
    SQLITESTUDIO_PLUGIN_VERSION(10000)
    SQLITESTUDIO_PLUGIN_AUTHOR("sqlitestudio.pl")

    public:
        QString getLanguageName() const;
        QSyntaxHighlighter* createSyntaxHighlighter(QWidget* textEdit) const;
};

int qHash(SqliteSyntaxHighlighter::State state);

#endif // SQLITESYNTAXHIGHLIGHTER_H
