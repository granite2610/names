#include "nameshuffler.h"
#include <random>
#include <assert.h>

// Default ctor -- calls QObject ctor as well.
NameShuffler::NameShuffler(QObject *parent) : QObject(parent)
{

}

/**
 * @brief NameShuffler::get_names
 * @pre A list of names in string form. The names must be new-line separated
 * @post Should have a list of parsed names.
 * @return Parsed and shuffled list of names
 * @bug Fixed sig-sev error. Input variable was empty.
 */
QString NameShuffler::get_names( QString input )
{
    QVector<QString> names = parse_input( input );
    if (names.size() < 3) {
        return "Too few names -- must enter at least three names.";
    }
    names = shuffle_names( names );


    QVector<QString> output = match_names( names );

    // Make sure we get an original name, but halt execution if it can't after five tries.
    int tries = 0;
    while ( prev.is_match(output) and tries < 5 ) {
        output = match_names( names );
        tries++;
    }

    QString string_out;

    prev.set_history( output );

    for (QString i: output)
        string_out += i + "\n";

    return string_out;
}



/**
 * @brief NameShuffler::parse_input
 * @pre A list of names delimited by new-lines
 * @post Should have a little less memory on the stack from the names being parsed.
 * @param input
 * @return parsed list of names.
 */
QVector<QString> NameShuffler::parse_input( QString input )
{
    QString name;
    QVector<QString> names;

    for (QChar c: input) {
        if (c == '\n' and name.size() > 0) {
            names.push_back(name);
            name.clear();
        } else {
            name += c;
        }
    }

    if (!name.isEmpty())
        names.push_back(name);
    return names;
}



/**
 * @brief NameShuffler::shuffle_names
 * @param names
 * @return Each name in list.
 */
QVector<QString> NameShuffler::shuffle_names( QVector<QString> names )
{
    assert( !names.empty() );

    // Randomly shuffle names list for specified amount of times
    for (int i = 0; i < names.size()*13; i++) {
        int pos_one = random() % (names.size());
        int pos_two = random() % (names.size());

        QString temp = names.at(pos_one);
        names[pos_one] = names[pos_two];
        names[pos_two] = temp;
    }
    return names;
}


/**
 * @brief NameShuffler::match_names
 * Matches names by stack computations.
 * @pre A list of names with each name being an element of a vector
 * @post Returns a list of names shuffled in random order.
 *  The original list of names is unchanged.
 */
QVector<QString> NameShuffler::match_names( QVector<QString> names )
{
    QStack<QString> name_stack;

    for (QString i: names)
        name_stack.push(i);

    QString first = name_stack.pop();
    QString prev = first;
    QString curr;
    QVector<QString> output;

    while (!name_stack.isEmpty()) {
        curr = name_stack.pop();
        output.push_back( prev + " -> " + curr );
        prev = curr;
    }

    output.push_back( curr + " -> " + first );
    return output;
}
