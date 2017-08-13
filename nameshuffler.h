#ifndef NAMESHUFFLER_H
#define NAMESHUFFLER_H

#include <QObject>
#include <QVector>
#include <QStack>

#include "matchhistory.h"

class NameShuffler : public QObject
{
    Q_OBJECT
public:
    // Default ctor
    explicit NameShuffler(QObject* parent = nullptr);
    // Gets shuffled list of name matches
    QString get_names(QString input);

private:

    // Contains data and algorithms for name history.
    MatchHistory prev;
    // Parses input from a single string into a vector of strings.
    QVector<QString> parse_input(QString input);
    // Shuffles names into random order.
    QVector<QString> shuffle_names(QVector<QString> names );
    // Matches each name in the input list to one other name in said list.
    QVector<QString> match_names(QVector<QString> names);
};

#endif // NAMESHUFFLER_H
