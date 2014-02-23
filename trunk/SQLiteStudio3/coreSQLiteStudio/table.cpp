#include "table.h"
#include <QHash>

Table::Table()
{
}

Table::Table(const QString& database, const QString& table)
{
    setDatabase(database);
    setTable(table);
}

Table::Table(const Table& other)
{
    database = other.database;
    table = other.table;
}

Table::~Table()
{
}

int Table::operator ==(const Table &other) const
{
    return other.database == this->database && other.table == this->table;
}

QString Table::getTable() const
{
    return table;
}

void Table::setTable(const QString& value)
{
    table = value;
}

QString Table::getDatabase() const
{
    return database;
}

void Table::setDatabase(const QString& value)
{
    database = value.isEmpty() ? "main" : value;
}

int qHash(Table table)
{
    return qHash(table.getDatabase() + "." + table.getTable());
}
